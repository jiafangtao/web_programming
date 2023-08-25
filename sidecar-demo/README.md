# sidecar demo

Demonstrate sidecar concepts

# how to build

docker build -t sidecar:1.0.0 .

# how to run it

kubectl create namespace sandbox

kubectl apply -n sandbox -f pod.yaml

# clean up

kubectl delete -n sandbox -f pod.yaml
kubectl delete namespace sandbox
