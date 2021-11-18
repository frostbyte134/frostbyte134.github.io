---
layout: post
title:  "Kubernetes"
date:   2021-03-25 08:00:05 +0800
categories: coding
use_math: true
tags: coding kubernetes docker
---

> 쿠버네티스 인 액션, 마르코 록샤

### 팟 스케쥴링
<a href="https://velog.io/@jayoh/%EC%BF%A0%EB%B2%84%EB%84%A4%ED%8B%B0%EC%8A%A4-%ED%8C%A8%ED%84%B4-6%EC%9E%A5-%EC%9E%90%EB%8F%99-%EB%B0%B0%EC%B9%98" target="_blank">참고사이트 1</a>
<a href="https://blog.naver.com/PostView.naver?blogId=alice_k106&logNo=221511412970&redirect=Dlog&widgetTypeCall=true&directAccess=false" target="_blank">참고2</a>

taint, toleration
  - 마스터 노드에 `node-role.kubernetes.io/master:NoSchedule` 테인트가 등록되어 있어 보통 스케쥴링이 안됨
  - 팟 toleration에
  ```
  toleration:
    - effect: Noschedule
      key: node-role.kubernetes.io/master
  ```
  라고 할 시 taint를 약간 무시하고 스케쥴링됨.

effect 필드에 해당하는 값은 세 가지가 있으며 다음과 같습니다.
- NoSchedule
  - Taints 에 일치하지 않는 파드는 해당 노드에 예약되지 않음
  - 노드의 기존 파드들은 유지
- PreferNoSchedule
  - Taints 에 일치하지 않는 파드는 해당 노드에 최대한 예약 되지 않도록 함
  - 다른 노드의 자원 부족 시 예약 될 수도 있음
- NoExecute
  - Taints 에 일치하지 않는 파드는 해당 노드에 예약되지 않음
  - 노드의 기존 파드들도 Taints 에 일치하지 않으면 제거

nodeAffinity
- required 는 Filtering 에 해당하며 조건을 만족하는 노드만 파드를 스케줄 하도록 합니다.
- preferred 는 Scoring 에 해당하며 우선 순위를 통해서 보장하지 않지만 조건을 만족하는 파드를 최대한 스케줄 하도록 합니다.


<a href="https://coffeewhale.com/kubernetes/mistake/2020/11/29/mistake-10/" target="_blank">사람들은 대부분 다음 두가지 설정의 차이를 잘 구분하지 못합니다.</a>
- Liveness 체크는 당신의 Pod가 linvess 검사를 통과하지 못할 경우 재시작됩니다.
- Readiness 체크는 검사를 통과하지 못하는 경우 더 이상 요청을 받지 못하게 Service로 부터 오는 트래픽을 끊습니다.
- 두가지 검사 모두 Pod의 생명주기 전체 기간동안 지속적으로 검사합니다. 이것은 중요한 부분입니다. 사람들은 주로 ReadinessProbe의 경우 Pod를 시작할 시점에만 검사를 진행하여 트래픽의 전달 여부를 결정한다고 생각합니다. 하지만 그것은 단지 하나의 사용사례에 불과합니다.
- Anti Affinity 설정
  - 가용성을 위해 3개 Pod 레플리카를 생성하였지만 노드가 죽을 때 3개 Pod 모두 한꺼번에 죽었습니다. 어떻게 된 일인가요? 3개 Pod가 전부 한개 노드 위에서 돌았군요. 쿠버네티스가 알아서 고가용성(HA)을 보장해주는 것이 아니었나요?
  - 쿠버네티스 스케줄러가 강제로 anti-affinity를 설정해 주진 않습니다. 명시적으로 선언해야 합니다. (와 개신기)

<a href="https://kubernetes.io/ko/docs/concepts/scheduling-eviction/pod-priority-preemption/" target="_blank">파드 우선순위, preamption</a> (축출시키기)

### 2021.11.16 다시보기
- 컨테이너는 단일프로세스를 실행하는 것을 목적으로 설계됐다. 단일컨테이너에서 관련없는 다른 프로세스를 실행하는 경우, 프로세스 실행 관리 (재시작등), 로깅 등은 __모두 사용자 책임이다__ (넘모 맞말이구요). 또한 이 경우 모든 프로세스는 stdout으로 로그를 쏘기 떄문에 구분하기 피곤함
- 1개 팟 - 여러 컨테이너 포함 가능 (1:1이 아님!)
  - 다만 모든 동일한 네임스페이스를 사용 = 같은 호스트명과 네트워크 인터페이스 사용 (파일시스템은 각 컨테이너 이미지의 UFS때문에 분리됨), 포트충돌 조심
  - 팟끼린 NAT필요없음 (같은 로컬네트워크에 있음)
  - 파드는 상대적으로 가볍기 때문에, 앱의 모든 것을 팟1개에 넣는 대신 여러 파드로 앱을 구성해야 한다.
  - 사이드카 컨테이너의 다른 예제로는 로그로테이터, 로그수집기, 테이터 프로세서, 통신 어댑터 등이 있다
- label vs annotation
  - label: 스케쥴러에 의해 사용
  - annotation: 설명, 내부 앱이 사용
- `livenessprobe`
  - http, exec, tcp 등으로 체크가능
  - 초기 지연시간 (`initialDelaySeconds`)를 설정해 주는 것이 좋음
  - 프로브 실패 시 __재시작__
- `readinessprobe`
  - 파드를 엔드포인트에 포함시켜야 하는지 결정함!
  - `initialdelayseconds`로 초기 시간 떄울 수 있음
  - 파드가 준비되지 않음 - 서비스에서 제거됨 __(종료되지는 않음!!)__
  - 이거에 잘 응답해야 트래픽이 라우팅됨
    - 파드가 트래픽을 받는지 준비됐는지 여부를 반환! (처음 시작할때만은 아님)
    - __레디니스 프로브를 잘못 정의했으면, 파드는 서비스에 포함되지 않음__ 
- 서비스
  - 서비스로 curl은 가능하지만 핑은 안됨: 가상 아이피라 서비스 포트와 결합된 경우에만 의미가 있음 (?), 11장에서 설명
  - (잘 알듯이) 서비스는 팟에 직접 연결되지 않으며, 엔드포인트 리소스가 그 사이에 있음
  - __외부 서비스를 위한 DNS생성__: DNS를 통해 서비스의 `extername`을 주소처럼 사용가능
  - 서비스에도 `세션 어피니티`가 있음
    - 세션 어피니티가 없어도 http keepalive가 적용되어 있으면 같은 팟에 연결되는 듯
- 컨피그맵
  - 컨피그맵을 볼륨마운트 할 수 있음 -> 파일 변화를 감지하고 업데이트 가능할 듯. 이 외에 자동감지는 마스터 폴링...? 정도밖에 없어보임
- 롤링 업데이트 전략의 properties (밑에도 있지만 그4948)
  - `maxsurge` : 의도된 파드 수 보다 얼마나 많은 파드를 순간적으로 가질 수 있나
  - `maxUnavailable` : 사용할 수 없는 최대한의 파드 인스턴스 수. __이걸 0으로 하면 파드를 한번에 하나만 교체함__
- 잘못된 버전의 롤아웃 방지
  - `minReadySeconds` 설정 -> 여기서 지정된 시간 이후 레디니스 프로브 호출하고 롤아웃 진행됨
  - 충분히 크게 설정하면, 실제 트래픽을 수신한 뒤 레디니스 프로브 호출 가능!
  - 새 파드가 만들어 지고, old 파드와 충분한 시간 같이 돌다가 레디니스 프로브 실패 시
    - `maxUnavailable=0`이면 새 파드만 제거됨. 아니면 몇 개 제거될 수도 있음
    
### Kubectl 모음
#### Chap 9
- `kubectl set selector` 로 서비스의 파드 셀렉터 변경가능 (블루-그린 deployment : 잠시 파드가 2배 됨)
- `kubectl rolling-update <old_pod_name> <new_pad_name>` : old_pod_name는 이미 노드에서 돌고 있는 pod의 metadata.name이고, new_pod_name은 yaml에 있을 필요 없음 (이럼 로컬 yaml하고 name이 달라지긴 하는 듯)
- YAML에서는 __대시 3개로__ 여러 object를 구분
- `--v` __옵션으로 추가 로그 확인가능__
- `kubectl delect rc -all` : 모든 rc 삭제 (레플리카셋이 더 최신임)
- `kubectl create -f kubia-deployment-v1.yaml --record` : --record 옵션은 revision history에 명령어를 기록해 나중에 유용하게 쓸 수 있다고 함
  - `kubectl rollout status deployment <deployment name>` : `kubectl get deployment` / `kubectl describe deployment` 보다 업데이트 상태를 더 잘 볼 수 있다고 함
- `kubectl patch deployment depname -p '{"spec":{"minReadySeconds":10}}'` : `kubectl patch`로 속성 1개 (롤링 업데이트 속도 늦게)만 조절
- `kubectl set image deployment depname container=image`로 이미지 교체하여 업데이트 수행
    - `kubectl set image` : 파드, RC 템플릿, 디플로이먼트, 데몬셋, 잡 또는 레플리카셋에 정의된 컨테이너 이미지 변경
    - 디플로이먼트에 소속된 "파드 템플릿"을 새로운 이미지를 쓰도록 업데이트 하는 것
- `kubectl rollout undo deployment depname` : 이전 배포된 버전으로 롤백
  - `kubectl rollout history objtype objname` : 버전업 히스토리 (--record로 디플로이먼트 만들어야 CHANGE-CAUSE에 세부사항이 나옴)
- `kubectl rollout pause objtype objname ` : 적당한 타이밍에 멈췄다면, 원본 파드 / 새 파드가 혼재된 상태 (`canary release` : 버킷 테스트 비슷)
  - 근데 이걸로 버킷테스트 하기는 좀...minReadySeconds를 크게 줘서 
- `kubectl rollout resume objtype objname ` : 계속 진행


#### Chap 11
- `kubectl get componentstatus` : 스케쥴러, 컨트롤러 매니저, etcd등의 상태 확인
- `etcdctl ls /registry` : etcd에 저장된 오브젝트들 ls
  - `etcdctl ls /registry/pods/` : 등록된 파드들의 네임스페이스 (디렉토리) 가 나옴
  - 계속 찾아가면, pod 관리에 필요한 key-value값들이 나옴
- `kubectl get pods --watch` : 와치 명령어 비슷
- `kubectl get events --watch` : 이벤트 (파드에 대한 명세가 컨트록ㄹ 플레인에서 생성, 스케쥴링되어 노드가 할당, 해당 노드의 kubelet에서 감시하다가 이를 발견하고 이미지 다운로드 밑 파드 리소스 생성 등) 감시가능

------------------------------------------



### Chap 9 (디플로이먼트, 선언적 앱 업데이트)
- `kubectl set selector` 로 서비스의 파드 셀렉터 변경가능 (블루-그린 deployment : 잠시 파드가 2배 됨)
- kubectl에서 `--v` 옵션으로 추가 로그 확인가능
- 롤링 업데이트 : 서비스의 레이블 셀렉터가 파드 버전 2개 (죽어가는 구버전 / 새로 생기는 신버전)를 동시에 지원
  - `kubectl rolling-update <old_pod_name> <new_pad_name>` : 옛날 방식이라고 함. old_pod_name는 이미 노드에서 돌고 있는 pod의 metadata.name이고, new_pod_name은 yaml에 있을 필요 없음 (이럼 로컬 yaml하고 name이 달라지긴 하는 듯) (398p)
  - 쿠버네티스는 pod label, select label에 deployment항목을 추가하여 old rc가 old pod만 물고, new rc가 new pod만 물게 함 (값을 다르게)
  - selector는 old pod, new pod이 공유하는 레이블을 물어서, 둘 다에게 외부 요청 등을 보낼 수 있게 함
  - 이제 scale up(new), down(old)를 차례로 수행
  - 왜 이젠 안 쓰이나?
    - 쿠버네티스 스스로가 사용자가 만든 object를 수정하는 것은 좋지 않다고 함
    - 모든 동작을 kubectl client가 트리거해 수행 -> 네트워크가 끊어질 시 업데이트 도중 중단될 수 있음
    - `imperative` 함 : 선언 (`declaritive`) 하고 쿠버네티스가 최상의 상태를 찾아내어서 해당 상태를 달성하는 것이 쿠버네티스의 철학
    - \\(\rightarrow\\) `deployment`라는 새로운 리소스 도입

#### 디플로이먼트
- replicaset (rc 대체), 롤아웃 업데이트용 컨트롤러 프로세스 등을 포함하는 고수준의 오브젝트 
- 직접 파드를 관리하지 않음. 디플로이먼트에 소속된 레플리카셋이 직접 관리
  - 파드명 podname_somenumber_randomchar 에서 somenumber는 레플리카셋이 파드를 관리할 때 쓰는 해시값
- `Recreate` (blue-green), `RollingUpdate` 업데이트 방식 보유 (기본)
- `kubectl set image deployment depname container=image`로 업데이트 수행 (이미지 교체)
  - 결국 이미지 교체가 업데이트인듯?
  - `kubectl set image` : 파드, RC 템플릿, 디플로이먼트, 데몬셋, 잡 또는 레플리카셋에 정의된 컨테이너 이미지 변경
  - kubectl에서 선언, 순차적으로 명령이 전달되지 않음. 클러스터 자체에서 수행
  - 하는 일은 비슷 (레플리카셋 추가 등) - 신경쓸 필요 없음
- `kubectl rollout undo deployment depname` 으로 간단하게 롤백가능
  - `kubectl rollout history deployment depname` : 버전업 히스토리 (--record로 디플로이먼트 만들어야 CHANGE-CAUSE에 세부사항이 나옴)
  - 버전업 할 때 마다 old 레플리카셋을 유지함 (이걸로 복구하는 듯)
  - 디플로이먼트 리소스의 `editionHistoryLimit`속성으로 제한 (기본=2 or 10)
- 롤링 업데이트 전략의 properties
  - `maxsurge` : 의도된 파드 수 보다 얼마나 많은 파드를 순간적으로 가질 수 있나
  - `maxUnavailable` : 사용할 수 없는 최대한의 파드 인스턴스 수. __이걸 0으로 하면 파드를 한번에 하나만 교체함__
- 잘못된 버전의 롤아웃 방지
  - `minReadySeconds` 설정 -> 여기서 지정된 시간 이후 레디니스 프로브 호출하고 롤아웃 진행됨
  - 충분히 크게 설정하면, 실제 트래픽을 수신한 뒤 레디니스 프로브 호출 가능!
  - 새 파드가 만들어 지고, old 파드와 충분한 시간 같이 돌다가 레디니스 프로브 실패 시
    - `maxUnavailable=0`이면 새 파드만 제거됨. 아니면 몇 개 제거될 수도 있음


### Chap 11
쿠버네티스 클러스터의 구성요소
1. 쿠버네티스 컨트롤 플레인 (마스터 노드)
   - etcd
   - api서버
   - 스케쥴러
   - 컨트롤러 매니저
2. 워커 노드
   - kublet
   - kube-proxy (쿠버네티스 서비스 프록시)
   - 컨테이너 런타임 (docker or rkt or ...)
3. 애드온
   - 쿠버네티스 dns 서버
   - 대시보드
   - 인그레스 컨트롤러
   - 힙스터 (?)
   - 컨트롤러 네트워크 인터페이스

이거..뭔가 적기에는 너무 많네


2021-02-13 때 작성


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
