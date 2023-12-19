# knative memo

Install knative on windows with docker (just because I didn't find a bin release for Windows.)

docker run --rm -v "$HOME/.kube/config:/root/.kube/config" gcr.io/knative-releases/knative.dev/client/cmd/kn:latest service list


knative client code: https://github.com/knative/client.git