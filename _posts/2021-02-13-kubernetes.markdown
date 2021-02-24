---
layout: post
title:  "Kubernetes"
date:   2021-02-13 08:00:05 +0800
categories: coding
use_math: true
tags: analysis
---

일단 외워야 할 것들 먼저. 기본적인 걸 알게 되면 다시 쓰자
- <a href="https://bcho.tistory.com/1256?category=731548">조대협의 블로그 - 쿠버네티스</a> 내용을 정리


1. 마스터 : 클러스터 전체를 관리하는 "컨트롤러"
   - API서버, 스케쥴러, 컨틀롤러 매니저, etcd 
   - DNS : 쿠버네티스는 리소스의 엔드포인트(Endpoint)를 DNS로 맵핑하고 관리. pod는 동적 오브젝트이기 때문에, `service discovery`패턴 + DNS를 이용해 pod들의 리스트를 관리
2. 노드 : 컨테이너가 배포되는 (가상/물리) 머신
   - `Kubelet` : 노드에 배포되는 에이전트. 마스터의 API서버와 통신
   - `Kube-proxy` : 노드로 들어오는 트래픽을 라우팅 / LB등 기능 수행
### 오브젝트 - 기본적인 구성단위
pod, service, volume, namespace 등  
 - `spec` : 오브젝트의 설정. yaml/json으로 관리
 - `service`
   - 일반적으로 분산환경에서는 여러 pod을 `LB`로 __하나의 IP/PORT로__ 묶어서 서비스함
     - pod은 동적으로 생성/삭제됨 (장애 시 리스타트, `오토 스케일링` 등) -> LB에서 pod list를 IP로 갖고있으면 안됨. 
       - \\(\rightarrow\\) 라벨, 라벨 셀렉터를 이용해 대응
       - `라벨` : 쿠버네티스의 리소스를 선택하는데 사용됨
         - "labels": {k1:v1, k2:v2} 처럼 여러 라벨 부여가능 
       - `라벨 셀렉터` : 어떤 pod를 서비스로 묶을 것인지
         - pod생성시 스펙 메타데이터에 라벨 기술
       - port: 노출할 포트 \\(\leftrightarrow\\) targetPort: pod내의 컨테이너들에서 사용할 포트
 - `volume` : 그 볼륨
 - `pod` : 컨테이너화된 어플리케이션 
   - pod내의 컨테이너간에는 ip,, port를 공유하며, localhost로 서로 통신가능
     - 이 때 로드벨런싱은 누가?
   - pod내의 컨테이너간에는 볼륨 공유 가능. ex) 로그 수집기와 앱을 다른 컨테이너에서 돌리나 같은 pod으로 묶으면 , 쉽게 데이터 공유 가능 = `사이드카 패턴` (주변 프로그램을 같이 배포)
 - `namespace` : 쿠버네티스 클러스터 내의 논리적인 분리단위 (pod, service)
   - 접근권한, 리소스 쿼타, 오브젝트  분할 가능

### 컨트롤러 - 오브젝트를 관리
replication controller (RC), Replication Set, daemonset, job, statefulset, deployment 등
1. Replication Controller, RC / Replication Set
    - 지정된 replication만큼 pod를 가동시키고 관리함
    - 쿠버네티스 클러스터에서 특정 노드에 장애 발생 시, 
      - RC/RS에 의해서 관리되고 있는 Pod는 자동으로 다른 노드에서 다시 생성되서 시작
      - 컨트롤러에 의해 관리되고 있지 않은 Pod는 다른 노드에서 기동되지 않고 사라짐
2. Deployment : RC, RS의 추상화 (?).  
   업데이트 시, RC를 하나 더 만들고 한번에 교체 (블루/그린 배포)하던지 RC/RS내의 pod를 하나씩 교체하던지 (롤링 업데이트)하는데, 이런 것들을 해준다고 함
3. Daemonset 
   - Daemonset에 의해 관리되는 pod는 노드(들)에 1개씩만 배포됨 (RC/RS는 노드 상황에 따라 배포)
     - 로깅, 모니터링 등으로, 프로세스의 데몬처럼 활용가능
4. job
   - 원타임 커맨드를 실행하는 컨트롤러
   - `cronjob`도 있음
   - Job에 의해서 관리되는 Pod는 Job이 종료되면 Pod 를 같이 종료
   - Job을 정의할때는 컨테이너 스펙 부분에 image 뿐만 아니라, 컨테이너에서 Job을 수행하기 위한 커맨드를 같이 입력
   - 해당 커맨드의 exit code로 job 성공여부 판단
     - 실패 시 restart 하게 가능 (resume이 아님)
5. StatefulSet
   RC/RS등으로는 상태를 가지는 어플리케이션을 관리하기 어려워 만든 컨트롤러

### Service
<a href="https://bcho.tistory.com/1262?category=731548" target="_blank">조대협의 블로그 쿠버네티스 7</a>
- 여러 pod를 묶어 로드밸런싱. 고유한 DNS이름 보유가능
- label selector를 이용해 관리하고자 하는 pod들을 정의할 수 있음
- 로드밸런싱은 기본적으로 랜덤
  - `Session Affinity`를 주면 특정 pod에만 연결가능. 웹에서 HTTP Session을 사용하는 경우와 같이 각 서버에 각 클라이언트의 상태정보가 저장되어 있는 경우에 유용하게 사용가능
- 서비스의 종류 : ClusterIP, Load Balancer, NodePort, External name
  1. ClusterIP : 디폴트. 내부용 클러스터 IP를 할당. 클러스터 내에서만 접근되고, 외부에서는 안됨
  2. Load Balancer : 외부 IP를 가진 로드밸런서를 할당
  3. NodePort : 모든 노드의 포트로 직접 접근가능하게 해 줌? 이건 잘 모르겠네
  4. ExternalNamel : 외부 서비스를 쉽게 호출가능 (NAT통하지 않고도)  
    - ex) AWS에서 아마존 클라우드 밖 서비스 호출. 프록시처럼 동작
    - DNS나 IP(추가설정 필요) 사용가능

#### Headless service
- 이런 서비스들에 대한 접근을 위해, 각자 cluster ip (클러스터 내부에서 사용) 또는 external ip(외부에서 해당 서비스를 접근)를 할당받음
- 이런 서비스들은 etcd등을 이용해, 실제 엔드포인트 주소 등을 관리
  - 클러스터 내에서 nslookup등으로 서비스의 dns를 조회해보면, 서비스에 의해 제공되는 pod들의 실재 (and 임시) ip목록이 나옴
  - 생성된 서비스의 ip 또한 임시이며 동적으로 바뀜 - dns로 관리함


#### ingress-nginx
- <a href="https://github.com/kubernetes/ingress-nginx/blob/master/README.md" target="_blank">https://github.com/kubernetes/ingress-nginx/blob/master/README.md</a>
- <a href="https://bcho.tistory.com/1263?category=731548" target="_blank">조대협의 블로그 - ingress</a>
- 서비스 : L4레이어, TCP단에서 pod 로드밸런싱
- 인그레스 : HTTPS기반의 L7 로드밸런싱. App단. (URL기반?)
- Ingress를 사용하려면 서비스는 Load Balancer 타입이 아니라, NodePort 타입으로 배포해야 한다
