# Photo Controller Cleanup Script

Write-Host "Cleaning up Photo Controller resources..." -ForegroundColor Yellow

# Remove sample resources
Write-Host "Removing sample Photo resources..." -ForegroundColor Yellow
kubectl delete -f manifests/photo_01.yaml --ignore-not-found=true
kubectl delete -f manifests/photo_02.yaml --ignore-not-found=true

# Remove controller deployment if exists
Write-Host "Removing controller deployment..." -ForegroundColor Yellow
kubectl delete -f deploy/controller.yaml --ignore-not-found=true

# Remove CRD (this will also remove all Photo resources)
Write-Host "Removing Photo CRD..." -ForegroundColor Yellow
kubectl delete -f manifests/photo.crd.yaml --ignore-not-found=true

# Clean up built binaries
Write-Host "Cleaning up built binaries..." -ForegroundColor Yellow
if (Test-Path "bin") {
    Remove-Item -Recurse -Force "bin"
    Write-Host "✓ Removed bin directory" -ForegroundColor Green
}

Write-Host "Cleanup completed!" -ForegroundColor Green
