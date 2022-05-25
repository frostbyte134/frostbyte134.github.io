---
layout: post
title:  "Streaming Systems Chap 5 - Exatly Once"
date:   2022-05-25 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---

와...개바쁨 ㄷㄷ 이제 그래도 여유가 좀 생길 듯...
- TODO [여기](https://github.com/nailbrainz/nailbrainz.github.io/issues)이전 챕터 봐논거 정리하기 (워터마크, 트리거 등 개념 정리)

Conventional streaming systems
- best effort - at-least-once
    - performed aggr at memory -> lost when machine crashes
    - low latency, speculative rlts
    - This lead to `lambda architecture`

### Lambda Architecture
streaming (fast) + batch (slow, but accurate, refer later)
- inaccuracy: provides only half a gurantee (? 배치 쪽만 정확도 보장이 된다는 건가)
- Inconsistency: 두 시스템이 inherently 다르므로, 두개를 조합해서 같은 결과를 내기가 생각보다 어렵다고 함 (어케?)
- Complexity: 딱 보기에도 복잡해 보이긴 함 ㅋㅋ 분산 시스템이 2개나
- Unpredictability: comes from streaming part mainly
- Latency - Batch system is rather slow


-> exactly once가 어느정도 해결책이 된다

### Side Effect
- Dataflow (? 빔의 구현체인가)는 custom function이 record별로 exactly once하게 실행되는 것을 보장 X
    - Only one of these invocations can win and produce output further down the pipeline 
    - 따라서 연산이 멱등하면 exactly once (인 듯)
    - nonidempotent side effects are not uaranteed to execute exactly once
    - 중간에 custom 함수로 외부 서비스를 호출하는 side effect가 있으면, 파이프라인 결과에 와서는 exactly once인데 이 호출은 그렇지 않은 듯
    - 외부 서비스도 멱등하고 commit logic이 있으면 어케 해볼 여지는 있을 듯

### Problem definition

<a href="http://streamingbook.net/fig/5-1" target="_blank">http://streamingbook.net/fig/5-1</a>

2개 파이프라인이 동작
1. Shuffle by user - RPC를 이용해서, 유저가 같으면 같은 machine에 있게 shuffle
2. count per key
3. count globally

### Exactly Once in Shuffle (RPC)
- RPC can fail for many reasons (순단, timeout, server 500 err) -> __retrying__ gives at least once
- for RPC return status,
  - FP does not exists. If it said it is successful than it is
  - FN exists. Even when it says it is negative, it could actually have succeeded (ACK lost, ...)
  - __The only status that a sender can really trust is a successful one__ -> at least once. 대처할 방법이 필요
- 각 msg는 UID를 가짐 -> receiver는 처리한 UID를 저장했다가, 오면 처리 안함

### Addressing Determinism
- Beam model은 non-deterministic한 유저함수도 허용 -> 전체를 nondeterministic하게 만듬
  - ex) 현재 시간에 의존하는 코드, event time에 의존하는 코드 (이 레코드가 언제 도착할지 모름)
  - 위와 같이 레코드별로 각 유저함수의 결과를 저장 -> 2번째 실행되려고 하는 건 1번째껄 씀 ㄷㄷ

### Optimization
- 그래프 최적화 - 실행노드 2개를 합치거나, count -> sum이면 count에서 이미 좀 합치고 보냄
- bloom filter
  - FP는 있으나 FN은 없음
  - 없다고 하면 진짜 없음
  - 위의 확인 과정에서, 스토리지에 저장하기 전에 블룸필터를 먼저 돌림. 없다고 하면 진짜 없으므로 바로 insert하면 됨. 있다고 하면 lookup필요
  - tends to fill up -> FP rate goes up
    - 타임스탬프 range별로 블룸필터를 만듬
    - 레코드별로 시스템 타임스탬프별로 나눠서 record query -> fillup 방지