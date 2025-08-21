# Photo Controller

A Kubernetes controller for managing Photo custom resources. This controller watches for Photo CRs and manages their lifecycle, including validation, processing, and status updates.

## Project Structure

```
photocontroller/
├── src/                          # Source code
│   ├── api/v1/                   # API definitions
│   │   ├── groupversion_info.go  # Group version info
│   │   └── photo_types.go        # Photo CRD types
│   ├── controller/               # Controller logic
│   │   └── photo_controller.go   # Main controller implementation
│   └── main.go                   # Entry point
├── manifests/                    # CRD and sample resources
│   ├── photo.crd.yaml           # Photo Custom Resource Definition
│   ├── photo_01.yaml            # Sample Photo resource 1
│   └── photo_02.yaml            # Sample Photo resource 2
├── deploy/                       # Deployment manifests
│   └── controller.yaml           # Controller deployment
├── Dockerfile                    # Container image build
├── Makefile                      # Build automation
├── go.mod                        # Go module definition
└── README.md                     # This file
```

## Custom Resource Definition

The Photo CRD defines resources with the following structure:

```yaml
apiVersion: sce.trainings.com/v1
kind: Photo
metadata:
  name: photo-example
spec:
  name: "Photo Name"
  description: "Photo Description"
  url: "https://example.com/photo.jpg"
  score: 85
```

### Spec Fields

- `name`: Display name of the photo
- `description`: Additional information about the photo
- `url`: Location where the photo can be accessed
- `score`: Rating or quality score (0-100)

### Status Fields

- `lastUpdated`: Timestamp when the photo was last processed
- `processingStatus`: Current processing state (ValidationFailed, Processed)
- `message`: Additional information about the current state

## Controller Features

The Photo controller provides the following functionality:

1. **Validation**: Ensures Photo resources have valid specifications
2. **Processing**: Simulates photo processing workflow
3. **Status Updates**: Maintains current state information
4. **Error Handling**: Graceful handling of validation and processing errors
5. **Reconciliation**: Ensures desired state matches actual state

## Prerequisites

- Go 1.21+
- Kubernetes cluster (v1.25+)
- kubectl configured to access the cluster
- Docker (for building container images)

## Quick Start

### 1. Install the CRD

```bash
make install
```

or manually:

```bash
kubectl apply -f manifests/photo.crd.yaml
```

### 2. Build and Run the Controller

#### Option A: Run locally

```bash
make run
```

#### Option B: Deploy to cluster

Build the Docker image:

```bash
make docker-build
```

Deploy the controller:

```bash
kubectl apply -f deploy/controller.yaml
```

### 3. Create Sample Photo Resources

```bash
make deploy-samples
```

or manually:

```bash
kubectl apply -f manifests/photo_01.yaml
kubectl apply -f manifests/photo_02.yaml
```

### 4. Verify the Resources

Check the Photo resources:

```bash
kubectl get photos
```

Check the status of a specific photo:

```bash
kubectl describe photo photo-01
```

## Development

### Building

```bash
# Format code
make fmt

# Run static analysis
make vet

# Run tests
make test

# Build binary
make build
```

### Testing

Create a test Photo resource:

```yaml
apiVersion: sce.trainings.com/v1
kind: Photo
metadata:
  name: test-photo
spec:
  name: "Test Photo"
  description: "A test photo for validation"
  url: "https://example.com/test.jpg"
  score: 95
```

Apply it and watch the controller logs:

```bash
kubectl apply -f test-photo.yaml
kubectl logs -f deployment/photo-controller -n photo-controller-system
```

### Debugging

View controller logs:

```bash
make logs
```

or directly:

```bash
kubectl logs -f deployment/photo-controller -n photo-controller-system
```

## Validation Rules

The controller enforces the following validation rules:

- `name` field cannot be empty
- `url` field cannot be empty
- `score` must be between 0 and 100

If validation fails, the controller will:
1. Set `status.processingStatus` to "ValidationFailed"
2. Include error details in `status.message`
3. Requeue the resource for retry after 5 minutes

## Cleanup

Remove sample resources:

```bash
make undeploy-samples
```

Remove the controller:

```bash
kubectl delete -f deploy/controller.yaml
```

Remove the CRD:

```bash
make uninstall
```

## Customization

To extend the controller functionality:

1. **Add new fields**: Modify `PhotoSpec` and `PhotoStatus` in `src/api/v1/photo_types.go`
2. **Custom validation**: Update `validatePhotoSpec` in `src/controller/photo_controller.go`
3. **Processing logic**: Enhance `processPhoto` method with your business logic
4. **Finalizers**: Add cleanup logic in `handleDeletion` method

## Troubleshooting

### Common Issues

1. **CRD not found**: Ensure the CRD is installed with `kubectl get crd photos.sce.trainings.com`
2. **Permission denied**: Check RBAC permissions in `deploy/controller.yaml`
3. **Controller not starting**: Check logs with `kubectl logs` command
4. **Resource stuck**: Check for finalizers with `kubectl get photo <name> -o yaml`

### Useful Commands

```bash
# Check CRD installation
kubectl get crd photos.sce.trainings.com

# List all Photo resources
kubectl get photos --all-namespaces

# Get detailed resource information
kubectl describe photo <photo-name>

# Check controller status
kubectl get deployment photo-controller -n photo-controller-system

# View controller metrics
kubectl port-forward svc/photo-controller-metrics-service 8080:8080 -n photo-controller-system
```
