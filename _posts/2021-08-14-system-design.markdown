---
layout: post
title:  "System Design Interview"
date:   2021-08-14 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---


### Chap 4 Rate Limiter
- [참고](https://stripe.com/blog/rate-limiters)

response header에 `X-Ratelimit-Remaining`, `X-Ratelimit-Limit` 등 넣어 줌. 표준은 아닌 것 같은데?

1. 클라 vs 미들웨어 vs 서버
   - 클라에 적용하긴 보통 쉽지않음. 누가 무슨 클라를 쓸 줄 알고?
   - 서버에 부담주기도 싫음
   - 그럼 미들웨어지 ^^ 대신 1홉이 더 생기는 듯
2. 알고리즘
   - 시간측정을 어떻게 하느냐가 문제되는 듯
   - `token bucket` / `leaky bucket` : 리필되는 토큰이 있어야 전송해 줌. 토큰 리필 처리가 중요. leaky bucket은 끝부분에 큐를 둬서 request나가는 속도를 조절
   - 토큰 리필 처리
      1. 카운트 - 누군가 주기적으로 채워줘야 함
      2. timestamp저장 - timestamp만으로 대략적인 rate 게산 가능
   - 윈도우 기반 : 윈도우 경계쪽에서 burst로 나가는 경우 문제되는 듯. 경계에선 윈도우를 쪼개 시간 비율로 계산하는 법도 있음
3. 문제
   - 동기화가 제일 큰 문제인듯. 보통 redis로 atomic하게 하지만 요청이 너무 몰리면?
     - soft limit 정도가 괜찮아 보임
   - 룰 저장은 어디에 하고 어떻게 업데이트 할 것인가? 보통 디비에 넣고 메모리에 저장해두는게 일반적일테지만..



### Chap 5 consistent hasing
- ex) 몽고디비. 키를 서버에 나눠서 저장 밑 hashing으로 찾아가기
  - 나머지 연산자는 서버 추가/삭제 시 모든 키를 재배치해야 함
  - 링 방식으로, 키는 "자기와 제일 가까운 서버"에 저장된다고 할 시 키 개수 / 서버 수 정도만 재배치하면 됨. 굳


### Chap 6 A Key-value Store

별 내용 없었음..

#### CAP theorem

<a href="https://stackoverflow.com/questions/12346326/cap-theorem-availability-and-partition-tolerance" target="_blank">참고</a>

<a href="http://eincs.com/2013/07/misleading-and-truth-of-cap-theorem/" target="_blank">좋은 글인듯?</a> 다른글도 좋네

> In a distributed data store, at the time of network partition you have to chose either Consistency or Availability and cannot get both"
 
- Newer NoSQL systems are trying to focus on Availability while traditional ACID databases had a higher focus on Consistency
- C: Consistency (분산 node간 데이터 일치 여부)
- A: Availability (일부 노드 다운시에도 잘 동작하는가)
- P: Partition Tolerance: cluster continues to function even if there is a "partition" (communication break) between two nodes (both nodes are up, but can't communicate).
  - CA - consistent하고, 노드 한두개 죽어도 / partition 발생해도 응답은 잘 함. 다만 partition발생 시 문제 (어떻게?)
    - availability가 있으니 응답은 하지만, 파티션 해소 후에도 resync가 잘 안 되는 듯
  - CP - data is consistent between all nodes, and maintains partition tolerance (preventing data desync) by __becoming unavailable__ when a node goes down.
    - A가 없으면 그냥 다운시키면 되는 듯 ㅋㅋ
    - EX - bank systems
  - AP - nodes remain online even if they can't communicate with each other and will resync data once the partition is resolved, but you aren't guaranteed that all nodes will have the same data (either during or after the partition)

In real world, partitions cannot be avoided (CA never exists)


#### Data partitions + replication
- 서버 하나 말고 여러 노드에 데이터를 나눠서 저장 + 복사
- `consistent hasing` (+virtual node)
  - N replication - 서버를 링에서 시계방향으로 가장 가까운 N개 선택


#### Consistenty
- quorum (local / 2, 3, 4)
- `coordinator`가 프록시 역할을 하면서 통제
- inconsistency : versioning으로 해결 (vector clocks? 깃처럼 뭐 어떻게 하는 듯)


#### Failures
- `gossip protocol`: 노드 내부를 몇개의 헬스체크 패킷이 돌아다님. 일정시간동안 응답안하면 report (여러 댜른 노드에서 리포트가 들어와야 노드 다운 인정)

#### Merkle tree
- 리프노드는 데이터들이 해시값
- 부모는 자기 자손들의 총 해시값
  - 어느 데이터가 다른지 빠르게 비교가능

write path: commit log - memory cahce - SSTables
- sstable는 한번 봐야겠다. 맨날 나오네
read path - cache - bloom filter (데이터가 어느 sstable에 있는지?) - sstables (disk)



| Goal/problems       | Technique                                       |
| ------------------- | ----------------------------------------------- |
| Store big data      | consistent hashing to spread load across severs |
| HA reads            | data replication / multi-data center            |
| HA writes           | versioning with vector clocks                   |
| Dataset replication | consistent hashing                              |

### Chap 7 Unique ID Generator in Distributed System

#### 질문 리스트
- TPS (시스템의 스케일)
- 포멧, 길이
- 1씩 늘어나야 하는가? 시간에 따라 늘어나야 하는가?

#### 1. 디비
- db의 auto_increment - 분산환경에서 dirty write 고려?
- 속도가 느릴 듯 (불필요한 기능들 보유, B+트리 or 해싱 등)
- 여러 디비를 둘 수도 있지만..

#### 2. UUID
- 콜리전 확률?
- 128비트 크기 고정임
- 시간에 따라 늘어나지 않음 / 숫자 값 없음

#### 3. 티켓 서버
- SPOF
- 결국 어디엔가는 크리티컬 섹션이 있어야 함

#### 트위터 snowflake

<img src="https://programmer.help/images/blog/1ece2065a34118cda2f22db221294057.jpg" width="800">

- 41bits timestamp - 5bits datacenter id - 5bits machine id - sequence number




