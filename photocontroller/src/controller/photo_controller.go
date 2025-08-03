package controller

import (
	"context"
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
	"strings"
	"time"

	"k8s.io/apimachinery/pkg/api/errors"
	metav1 "k8s.io/apimachinery/pkg/apis/meta/v1"
	"k8s.io/apimachinery/pkg/runtime"
	ctrl "sigs.k8s.io/controller-runtime"
	"sigs.k8s.io/controller-runtime/pkg/client"
	"sigs.k8s.io/controller-runtime/pkg/controller"
	"sigs.k8s.io/controller-runtime/pkg/log"

	photov1 "github.com/photocontroller/src/api/v1"
)

// PhotoReconciler reconciles a Photo object
type PhotoReconciler struct {
	client.Client
	Scheme *runtime.Scheme
}

//+kubebuilder:rbac:groups=sce.trainings.com,resources=photos,verbs=get;list;watch;create;update;patch;delete
//+kubebuilder:rbac:groups=sce.trainings.com,resources=photos/status,verbs=get;update;patch
//+kubebuilder:rbac:groups=sce.trainings.com,resources=photos/finalizers,verbs=update

// Reconcile is part of the main kubernetes reconciliation loop which aims to
// move the current state of the cluster closer to the desired state.
func (r *PhotoReconciler) Reconcile(ctx context.Context, req ctrl.Request) (ctrl.Result, error) {
	logger := log.FromContext(ctx)
	logger.Info("Reconciling Photo", "namespace", req.Namespace, "name", req.Name)

	// Fetch the Photo instance
	photo := &photov1.Photo{}
	err := r.Get(ctx, req.NamespacedName, photo)
	if err != nil {
		if errors.IsNotFound(err) {
			// Request object not found, could have been deleted after reconcile request.
			logger.Info("Photo resource not found. Ignoring since object must be deleted")
			return ctrl.Result{}, nil
		}
		// Error reading the object - requeue the request.
		logger.Error(err, "Failed to get Photo")
		return ctrl.Result{}, err
	}

	// Handle deletion
	if photo.DeletionTimestamp != nil {
		return r.handleDeletion(ctx, photo)
	}

	// Process the Photo resource
	return r.processPhoto(ctx, photo)
}

// processPhoto handles the main logic for processing a Photo resource
func (r *PhotoReconciler) processPhoto(ctx context.Context, photo *photov1.Photo) (ctrl.Result, error) {
	logger := log.FromContext(ctx)

	// Validate the photo spec
	if err := r.validatePhotoSpec(photo); err != nil {
		logger.Error(err, "Photo spec validation failed")

		// Update status to reflect validation error
		photo.Status.ProcessingStatus = "ValidationFailed"
		photo.Status.Message = err.Error()
		photo.Status.LastUpdated = metav1.Now()

		if updateErr := r.Status().Update(ctx, photo); updateErr != nil {
			if errors.IsNotFound(updateErr) {
				// Resource was deleted between read and status update - this is normal
				logger.Info("Photo resource was deleted during validation, skipping status update", "name", photo.Spec.Name)
				return ctrl.Result{}, nil
			}
			logger.Error(updateErr, "Failed to update Photo status")
			return ctrl.Result{RequeueAfter: time.Second * 30}, updateErr
		}

		return ctrl.Result{RequeueAfter: time.Minute * 5}, nil
	}

	// Simulate photo processing logic
	logger.Info("Processing photo", "name", photo.Spec.Name, "url", photo.Spec.URL, "score", photo.Spec.Score)

	// Download the photo
	downloadPath, err := r.downloadPhoto(ctx, photo)
	if err != nil {
		logger.Error(err, "Failed to download photo", "url", photo.Spec.URL)
		// Update status to reflect download error
		photo.Status.ProcessingStatus = "DownloadFailed"
		photo.Status.Message = fmt.Sprintf("Failed to download photo from %s: %v", photo.Spec.URL, err)
		photo.Status.LastUpdated = metav1.Now()

		if updateErr := r.Status().Update(ctx, photo); updateErr != nil {
			if errors.IsNotFound(updateErr) {
				logger.Info("Photo resource was deleted during download error handling, skipping status update", "name", photo.Spec.Name)
				return ctrl.Result{}, nil
			}
			logger.Error(updateErr, "Failed to update Photo status")
			return ctrl.Result{RequeueAfter: time.Second * 30}, updateErr
		}
		return ctrl.Result{RequeueAfter: time.Minute * 5}, nil
	}

	logger.Info("Photo downloaded successfully", "name", photo.Spec.Name, "path", downloadPath)

	// Update status to reflect successful processing
	photo.Status.ProcessingStatus = "Processed"
	photo.Status.Message = fmt.Sprintf("Photo '%s' processed and downloaded successfully to %s with score %d", photo.Spec.Name, downloadPath, photo.Spec.Score)
	photo.Status.LastUpdated = metav1.Now()

	if err := r.Status().Update(ctx, photo); err != nil {
		if errors.IsNotFound(err) {
			// Resource was deleted between read and status update - this is normal
			logger.Info("Photo resource was deleted during processing, skipping status update", "name", photo.Spec.Name)
			return ctrl.Result{}, nil
		}
		logger.Error(err, "Failed to update Photo status")
		return ctrl.Result{RequeueAfter: time.Second * 30}, err
	}

	logger.Info("Photo processed successfully", "name", photo.Spec.Name)
	return ctrl.Result{}, nil
}

// validatePhotoSpec validates the photo specification
func (r *PhotoReconciler) validatePhotoSpec(photo *photov1.Photo) error {
	if photo.Spec.Name == "" {
		return fmt.Errorf("photo name cannot be empty")
	}

	if photo.Spec.URL == "" {
		return fmt.Errorf("photo URL cannot be empty")
	}

	if photo.Spec.Score < 0 || photo.Spec.Score > 100 {
		return fmt.Errorf("photo score must be between 0 and 100, got %d", photo.Spec.Score)
	}

	return nil
}

// handleDeletion handles the cleanup when a Photo resource is being deleted
func (r *PhotoReconciler) handleDeletion(ctx context.Context, photo *photov1.Photo) (ctrl.Result, error) {
	logger := log.FromContext(ctx)
	logger.Info("Handling Photo deletion", "name", photo.Name)

	// Clean up downloaded photo file
	if err := r.cleanupPhotoFile(photo); err != nil {
		logger.Error(err, "Failed to cleanup photo file", "name", photo.Name)
		// Don't fail deletion if cleanup fails, just log the error
	}

	logger.Info("Photo deletion handled successfully", "name", photo.Name)
	return ctrl.Result{}, nil
}

// SetupWithManager sets up the controller with the Manager.
func (r *PhotoReconciler) SetupWithManager(mgr ctrl.Manager) error {
	return ctrl.NewControllerManagedBy(mgr).
		For(&photov1.Photo{}).
		WithOptions(controller.Options{
			MaxConcurrentReconciles: 2,
		}).
		Complete(r)
}

// downloadPhoto downloads the photo from the specified URL to the local photo folder
func (r *PhotoReconciler) downloadPhoto(ctx context.Context, photo *photov1.Photo) (string, error) {
	logger := log.FromContext(ctx)

	// Create photo folder if it doesn't exist
	photoFolder := "/photo_folder"
	if err := os.MkdirAll(photoFolder, 0755); err != nil {
		return "", fmt.Errorf("failed to create photo folder: %v", err)
	}

	// Extract file extension from URL
	urlParts := strings.Split(photo.Spec.URL, "/")
	fileName := urlParts[len(urlParts)-1]
	if fileName == "" {
		fileName = fmt.Sprintf("%s.jpg", photo.Name)
	}

	// Create full file path
	filePath := filepath.Join(photoFolder, fileName)

	// Check if file already exists
	if _, err := os.Stat(filePath); err == nil {
		logger.Info("Photo already exists, skipping download", "path", filePath)
		return filePath, nil
	}

	// Create HTTP client with timeout
	client := &http.Client{
		Timeout: 30 * time.Second,
	}

	// Download the photo
	logger.Info("Downloading photo", "url", photo.Spec.URL, "destination", filePath)

	resp, err := client.Get(photo.Spec.URL)
	if err != nil {
		return "", fmt.Errorf("failed to download photo: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return "", fmt.Errorf("failed to download photo: HTTP %d", resp.StatusCode)
	}

	// Create the file
	file, err := os.Create(filePath)
	if err != nil {
		return "", fmt.Errorf("failed to create file: %v", err)
	}
	defer file.Close()

	// Copy the response body to the file
	_, err = io.Copy(file, resp.Body)
	if err != nil {
		return "", fmt.Errorf("failed to save photo: %v", err)
	}

	logger.Info("Photo download completed", "path", filePath)
	return filePath, nil
}

// cleanupPhotoFile removes the downloaded photo file when the resource is deleted
func (r *PhotoReconciler) cleanupPhotoFile(photo *photov1.Photo) error {
	// Extract file name from URL
	urlParts := strings.Split(photo.Spec.URL, "/")
	fileName := urlParts[len(urlParts)-1]
	if fileName == "" {
		fileName = fmt.Sprintf("%s.jpg", photo.Name)
	}

	// Create full file path
	photoFolder := "/photo_folder"
	filePath := filepath.Join(photoFolder, fileName)

	// Remove the file if it exists
	if _, err := os.Stat(filePath); err == nil {
		if err := os.Remove(filePath); err != nil {
			return fmt.Errorf("failed to remove photo file %s: %v", filePath, err)
		}
	}

	return nil
}
