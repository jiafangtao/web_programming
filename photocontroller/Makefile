# Image URL to use all building/pushing image targets
IMG ?= photo-controller:latest

# Get the currently used golang install path (in GOPATH/bin, unless GOBIN is set)
ifeq (,$(shell go env GOBIN))
GOBIN=$(shell go env GOPATH)/bin
else
GOBIN=$(shell go env GOBIN)
endif

# Setting SHELL to work on Windows PowerShell
SHELL = powershell.exe
.SHELLFLAGS = -Command

.PHONY: all
all: build

##@ General

# The help target prints out all targets with their descriptions organized
# beneath their categories. The categories are represented by '##@' and the
# target descriptions by '##'. The awk commands is responsible for reading the
# entire set of makefiles included in this invocation, looking for lines of the
# file as xyz: ## something, and then pretty-format the target and help. Then,
# if there's a line with ##@ something, that gets pretty-printed as a category.
# More info on the usage of ANSI control characters for terminal formatting:
# https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_parameters
# More info on the awk command:
# http://linuxcommand.org/lc3_adv_awk.php

.PHONY: help
help: ## Display this help.
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m<target>\033[0m\n"} /^[a-zA-Z_0-9-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

##@ Development

.PHONY: fmt
fmt: ## Run go fmt against code.
	go fmt ./src/...

.PHONY: vet
vet: ## Run go vet against code.
	go vet ./src/...

.PHONY: test
test: fmt vet ## Run tests.
	go test ./src/... -coverprofile cover.out

##@ Build

.PHONY: build
build: fmt vet ## Build manager binary.
	if (!(Test-Path "bin")) { New-Item -ItemType Directory -Path "bin" }; go build -o bin/manager.exe src/main.go

.PHONY: run
run: fmt vet ## Run a controller from your host.
	go run src/main.go

.PHONY: docker-build
docker-build: test ## Build docker image with the manager.
	docker build -t ${IMG} .

.PHONY: docker-push
docker-push: ## Push docker image with the manager.
	docker push ${IMG}

##@ Deployment

.PHONY: install
install: ## Install CRDs into the K8s cluster specified in ~/.kube/config.
	kubectl apply -f manifests/photo.crd.yaml

.PHONY: uninstall
uninstall: ## Uninstall CRDs from the K8s cluster specified in ~/.kube/config.
	kubectl delete -f manifests/photo.crd.yaml

.PHONY: deploy-samples
deploy-samples: ## Deploy sample Photo resources.
	kubectl apply -f manifests/photo_01.yaml
	kubectl apply -f manifests/photo_02.yaml

.PHONY: undeploy-samples
undeploy-samples: ## Remove sample Photo resources.
	kubectl delete -f manifests/photo_01.yaml --ignore-not-found=true
	kubectl delete -f manifests/photo_02.yaml --ignore-not-found=true

.PHONY: logs
logs: ## Show controller logs
	kubectl logs -f deployment/photo-controller -n photo-controller-system
