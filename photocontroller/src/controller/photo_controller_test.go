package controller

import (
	"context"
	"testing"

	metav1 "k8s.io/apimachinery/pkg/apis/meta/v1"
	"k8s.io/apimachinery/pkg/runtime"
	"k8s.io/apimachinery/pkg/types"
	clientgoscheme "k8s.io/client-go/kubernetes/scheme"
	"sigs.k8s.io/controller-runtime/pkg/client/fake"
	"sigs.k8s.io/controller-runtime/pkg/reconcile"

	photov1 "github.com/photocontroller/src/api/v1"
)

func TestPhotoReconciler_Reconcile(t *testing.T) {
	// Setup the test scheme
	scheme := runtime.NewScheme()
	_ = clientgoscheme.AddToScheme(scheme)
	_ = photov1.AddToScheme(scheme)

	// Create a valid photo resource with a local file URL to avoid network calls
	validPhoto := &photov1.Photo{
		ObjectMeta: metav1.ObjectMeta{
			Name:      "test-photo",
			Namespace: "default",
		},
		Spec: photov1.PhotoSpec{
			Name:        "Test Photo",
			Description: "A test photo",
			URL:         "file://test.jpg", // Use a file:// URL to avoid network calls in tests
			Score:       85,
		},
	}

	// Create a fake client with the photo
	client := fake.NewClientBuilder().WithScheme(scheme).WithObjects(validPhoto).WithStatusSubresource(&photov1.Photo{}).Build()

	// Create the reconciler
	reconciler := &PhotoReconciler{
		Client: client,
		Scheme: scheme,
	}

	// Create the reconcile request
	req := reconcile.Request{
		NamespacedName: types.NamespacedName{
			Name:      "test-photo",
			Namespace: "default",
		},
	}

	// Test reconciliation - expect requeue due to download failure for file:// URL
	ctx := context.Background()
	result, err := reconciler.Reconcile(ctx, req)

	// Verify the result - we expect a requeue because file:// URL will fail to download
	if err != nil {
		t.Errorf("Reconcile() error = %v", err)
	}

	if result.RequeueAfter == 0 {
		t.Errorf("Expected requeue due to download failure")
	}

	// Verify the status was updated to DownloadFailed
	updatedPhoto := &photov1.Photo{}
	err = client.Get(ctx, req.NamespacedName, updatedPhoto)
	if err != nil {
		t.Errorf("Failed to get updated photo: %v", err)
	}

	if updatedPhoto.Status.ProcessingStatus != "DownloadFailed" {
		t.Errorf("Expected status 'DownloadFailed', got '%s'", updatedPhoto.Status.ProcessingStatus)
	}
}

func TestPhotoReconciler_Reconcile_ValidationFailure(t *testing.T) {
	// Setup the test scheme
	scheme := runtime.NewScheme()
	_ = clientgoscheme.AddToScheme(scheme)
	_ = photov1.AddToScheme(scheme)

	// Create an invalid photo resource (empty name)
	invalidPhoto := &photov1.Photo{
		ObjectMeta: metav1.ObjectMeta{
			Name:      "invalid-photo",
			Namespace: "default",
		},
		Spec: photov1.PhotoSpec{
			Name:        "", // Invalid: empty name
			Description: "A test photo",
			URL:         "https://example.com/photo.jpg",
			Score:       85,
		},
	}

	// Create a fake client with the photo
	client := fake.NewClientBuilder().WithScheme(scheme).WithObjects(invalidPhoto).WithStatusSubresource(&photov1.Photo{}).Build()

	// Create the reconciler
	reconciler := &PhotoReconciler{
		Client: client,
		Scheme: scheme,
	}

	// Create the reconcile request
	req := reconcile.Request{
		NamespacedName: types.NamespacedName{
			Name:      "invalid-photo",
			Namespace: "default",
		},
	}

	// Test reconciliation
	ctx := context.Background()
	result, err := reconciler.Reconcile(ctx, req)

	// Verify the result
	if err != nil {
		t.Errorf("Reconcile() error = %v", err)
	}

	if result.RequeueAfter == 0 {
		t.Errorf("Expected requeue due to validation failure")
	}

	// Verify the status was updated to ValidationFailed
	updatedPhoto := &photov1.Photo{}
	err = client.Get(ctx, req.NamespacedName, updatedPhoto)
	if err != nil {
		t.Errorf("Failed to get updated photo: %v", err)
	}

	if updatedPhoto.Status.ProcessingStatus != "ValidationFailed" {
		t.Errorf("Expected status 'ValidationFailed', got '%s'", updatedPhoto.Status.ProcessingStatus)
	}
}

func TestPhotoReconciler_validatePhotoSpec(t *testing.T) {
	reconciler := &PhotoReconciler{}

	tests := []struct {
		name    string
		photo   *photov1.Photo
		wantErr bool
	}{
		{
			name: "valid photo",
			photo: &photov1.Photo{
				Spec: photov1.PhotoSpec{
					Name:  "Test Photo",
					URL:   "https://example.com/photo.jpg",
					Score: 85,
				},
			},
			wantErr: false,
		},
		{
			name: "empty name",
			photo: &photov1.Photo{
				Spec: photov1.PhotoSpec{
					Name:  "",
					URL:   "https://example.com/photo.jpg",
					Score: 85,
				},
			},
			wantErr: true,
		},
		{
			name: "empty URL",
			photo: &photov1.Photo{
				Spec: photov1.PhotoSpec{
					Name:  "Test Photo",
					URL:   "",
					Score: 85,
				},
			},
			wantErr: true,
		},
		{
			name: "invalid score - negative",
			photo: &photov1.Photo{
				Spec: photov1.PhotoSpec{
					Name:  "Test Photo",
					URL:   "https://example.com/photo.jpg",
					Score: -1,
				},
			},
			wantErr: true,
		},
		{
			name: "invalid score - too high",
			photo: &photov1.Photo{
				Spec: photov1.PhotoSpec{
					Name:  "Test Photo",
					URL:   "https://example.com/photo.jpg",
					Score: 101,
				},
			},
			wantErr: true,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			err := reconciler.validatePhotoSpec(tt.photo)
			if (err != nil) != tt.wantErr {
				t.Errorf("validatePhotoSpec() error = %v, wantErr %v", err, tt.wantErr)
			}
		})
	}
}
