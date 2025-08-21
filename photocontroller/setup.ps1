# Photo Controller Setup Script

Write-Host "Setting up Photo Controller..." -ForegroundColor Green

# Check if kubectl is available
try {
    kubectl version --client | Out-Null
    Write-Host "✓ kubectl is available" -ForegroundColor Green
} catch {
    Write-Host "✗ kubectl is not available. Please install kubectl first." -ForegroundColor Red
    exit 1
}

# Check if Go is available
try {
    go version | Out-Null
    Write-Host "✓ Go is available" -ForegroundColor Green
} catch {
    Write-Host "✗ Go is not available. Please install Go 1.21+ first." -ForegroundColor Red
    exit 1
}

# Install CRD
Write-Host "Installing Photo CRD..." -ForegroundColor Yellow
kubectl apply -f manifests/photo.crd.yaml

# Wait a moment for CRD to be established
Start-Sleep -Seconds 2

# Verify CRD installation
$crd = kubectl get crd photos.sce.trainings.com 2>$null
if ($crd) {
    Write-Host "✓ Photo CRD installed successfully" -ForegroundColor Green
} else {
    Write-Host "✗ Failed to install Photo CRD" -ForegroundColor Red
    exit 1
}

# Build the controller
Write-Host "Building controller..." -ForegroundColor Yellow
go build -o bin/manager.exe src/main.go

if (Test-Path "bin/manager.exe") {
    Write-Host "✓ Controller built successfully" -ForegroundColor Green
} else {
    Write-Host "✗ Failed to build controller" -ForegroundColor Red
    exit 1
}

# Deploy sample resources
Write-Host "Deploying sample Photo resources..." -ForegroundColor Yellow
kubectl apply -f manifests/photo_01.yaml
kubectl apply -f manifests/photo_02.yaml

Write-Host "Setup completed successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "To run the controller locally:" -ForegroundColor Cyan
Write-Host "  .\bin\manager.exe" -ForegroundColor White
Write-Host ""
Write-Host "To view the Photo resources:" -ForegroundColor Cyan
Write-Host "  kubectl get photos" -ForegroundColor White
Write-Host ""
Write-Host "To view detailed information:" -ForegroundColor Cyan
Write-Host "  kubectl describe photo photo-01" -ForegroundColor White
