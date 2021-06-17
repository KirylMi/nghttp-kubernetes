## NGHTTP-K8s
### HowTO:
0. Install minikube, docker, helm
1. Build docker images
    1. build from dockerServer folder `docker build --tag nghttp-server:1 .`
    2. build from dockerClientNghttp folder `docker build --tag nghttp-client:1 .`
    3. build from dockerClientCurl folder `docker build --tag nghttp-client-curl:1 .`
2. Change `K8s/values.yaml` parameters if needed
3. Minikube has no idea about local images, so: 
    1. `minikube image load nghttp-server:1`
    2. `minikube image load nghttp-client:1`
    3. `minikube image load nghttp-client-curl:1`
4. `helm install nghttp nghttpServer`
5. Check everything with `kubectl get all`
6. `minikube addons enable ingress`
7. `minikube addons enable metallb`
8. `minikube addons configure metallb`
9. Enter two IPs, based on the minikube ip value (for example minikube ip = 192.168.1.10 => startIp = 192.168.1.20 and endIp = 192.168.1.35)

### Testing
✅ Curl 
1. From inside the pod (nah)
2. From custom pod in the cluster
    - `kubectl run curltester -it --rm --image=nghttp-client-curl:2 -- sh`
    - #`curl `**`--http2-prior-knowledge`**`http://nghttp-service:3000`
3. From dockerhub minipod temporary installed in the cluster
    - `kubectl run curl-foreign-tester -it --rm --image=badouralix/curl-http2 -- sh`
    - #`curl `**`--http2-prior-knowledge`**`http://nghttp-service:3000`
4. From NodePort
    - `minikube service nghttp-service-exposed --url | xargs curl --http2-prior-knowledge`
5. ❌ From ingress (tbd)

<br/><br/>
✅ Nghttp
1. From inside the pod. 
    - `kubectl exec -it pod/POD_NAME -- sh`
    - #`nghttp http://0.0.0.0:3000`
2. From custom pod in the cluster *(to be fixed to look like #3)*
    - `kubectl run testing23 --image=nghttp-client:2 http://nghttp-service:3000`
    - `kubectl logs testing23`
3. From dockerhub minipod in the cluster
    - `kubectl run tester-1 --image=svagi/nghttp2 -i --tty --rm -- sh`
    - #`nghttp http://nghttp-service:3000`
4. From NodePort
    - `minikube service nghttp-service-exposed --url | xargs nghttp` if you have nghttp installed.
5. ❌ From ingress (tbd)


P.S. dockerServer Dockerfile looks ridicilous, i know that. Was trying to compress it a bit, but 50mb aren't worth it.<br/>Traefik configuration was taken from https://github.com/marcel-dempers/docker-development-youtube-series/tree/master/kubernetes/ingress/controller/traefik
