## NGHTTP-K8s

### Docker images:
1. dockerClientCurl   - container with curl command avaialable. Can be used for testing purposes as a temporary pod
2. dockerInnerService - container with server, that accepts all requests and returns json. In this context, should only be accessible via clusterIP (from other services) (new = service#2)
3. dockerOuterService - container with server and client, that accepts *all* requests and returns the result of it's own request(via additional executable) to the inner service(which is accessible by the env variable *DNS_INNER_SERVICE*) (old = service1)

### HowTO:
0. Install minikube, docker, helm
2. Build docker images *recommendation: build them at the same time*
    1. build from dockerInnerService folder `docker build --tag inner:1 .`
    2. build from dockerOuterService folder `docker build --tag outer:1 .`
    <br/>*optional:*
    3. build from dockerClientCurl folder `docker build --tag client-curl:1 .`
2. Change `K8s/values.yaml` parameters
3. Minikube has no idea about local images, so: 
    1. `minikube cache add inner:1`
    2. `minikube cache add outer:1`
    <br/>*optional:*
    3. `minikube cache add client-curl:1`
4. `helm install nghttp nghttpServer`
5. Check everything with `kubectl get all`
6. `minikube addons enable ingress`
<br/>*optional for loadbalancer tests*
7. `minikube addons enable metallb`
8. `minikube addons configure metallb`
9. Enter two IPs, based on the minikube ip value (for example minikube ip = 192.168.1.10 => startIp = 192.168.1.20 and endIp = 192.168.1.35)

### Testing
✅ Curl 
1. From inside the pod (nah)
2. From custom pod in the cluster
    - `kubectl run curltester -it --rm --image=client-curl:1 -- sh`
    - #`curl `**`--http2-prior-knowledge`**`http://outer-old-service:3000`
3. From dockerhub minipod temporary installed in the cluster
    - `kubectl run curl-foreign-tester -it --rm --image=badouralix/curl-http2 -- sh`
    - #`curl `**`--http2-prior-knowledge`**`http://outer-old-service:3000`
4. From NodePort
    - `minikube service outer-old-service-exposed --url | xargs curl --http2-prior-knowledge`
5. ❌ From ingress (tbd)

P.S. minikube cache add image_name:v takes some time
