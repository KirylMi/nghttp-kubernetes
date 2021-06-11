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

### Testing
❌ Curl *(still no clue what is wrong)*<br/><br/>
✅ Nghttp
1. From inside the pod. 
    - `kubectl exec -it pod/POD_NAME -- sh`
    - #`nghttp http://0.0.0.0:3000`
2. From custom pod in the cluster *(to be fixed to look like #3)*
    - `kubectl run testing23 --image=nghttp-client:2 http://nghttp1-service:3000`
    - `kubectl logs testing23`
3. From dockerhub minipod in the cluster
    - `kubectl run tester-1 --image=svagi/nghttp2 -i --tty --rm -- sh`
    - #`nghttp http://nghttp1-service:3000`
4. From NodePort
    - `minikube service nghttp1-service-exposed --url | xargs nghttp` if you have nghttp installed.
5. ❌ From ingress *(bug ???)*

### PS
dockerClientNghttp looks really weird, i was trying to comporess images a bit, but somehow they are 400mb - 1.4gb
