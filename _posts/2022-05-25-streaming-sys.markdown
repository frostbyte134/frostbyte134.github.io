---
layout: post
title:  "Streaming Systems Chap 5~8"
date:   2022-05-25 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---

와...개바쁨 ㄷㄷ 이제 그래도 여유가 좀 생길 듯...
- TODO [여기](https://github.com/frostbyte134/nailbrainz.github.io/issues)이전 챕터 봐논거 정리하기 (워터마크, 트리거 등 개념 정리)

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
- Dataflow (빔을 사용한 뭔가 데이터 플랫폼이라고 제리가 말씀주심)는 custom function이 record별로 exactly once하게 실행되는 것을 보장 X
    - Only one of these invocations can win and produce output further down the pipeline 
    - 따라서 custom 연산이 멱등해야 exactly once를 생각해 보기라도 하는 듯 (nonidempotent side effects are not guaranteed to execute exactly once) 
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

### 가비지 콜렉션
- 시스템 타임스탬프 (processing time)을 이용한 triggering -> 파이프라인별로 어디가 느린지도 이걸로 확인 가능


### Chap 6 - A General Theory of Stream and Table Relativity

- Data processing pipelines (both batch and streaming) consist of tables, streams, and operations upon those tables and streams
- `Tables are data at rest`, and act as a container for data to accumulate and be observed over time
- `Streamms are data in motion`, and encode a discretized view of the evolution of a table over time
- `Operations` on a stream/table yield a new stream/table
  - stream -> stream: nongrouping, element-wise operations (data is still in motion)
  - stream -> table: grouping operation (group by key?)
    - windowing = incorporates the dim of event time into such groupings
    - merging windows dynamically
  - table -> stream: ungrouping (triggering) operations
    - `watermarks` provide a notion of input completeness relative to event time (useful when griggering event-timestamped data)
    - `accumulation mode` - ?
  - table -> table - None

They codify the fact that data exist in one of two constitutions (table/stream) at any given time
windowing = slight modification of grouping


### Chap 7 The Practicalities of Persistent State

Persistent state is, quite literally, the tables (...) with the additional requirements that it must be robustly stored in a media relative immune to loss
- Stored on local disk counts, as long as you don't ask your Site Reliability Engineers (lol)
- Stored on a replicated set of dists is better, in distinct physical locations is better still
- Stored in memory definitely doesn't count
- Stored in replicated memory across multiple machines with UPS power backup and generators onsite maybe does (..)

Long running pipelines will inevitably fail
- To ensure that they can resume, they need some sort of durable recollection of where they were before the interruption. Thats where persistent state comes in

#### motivation
- Do batch pipelines use persistent state, and why or why not?
- Bounded dataset are finite in size, by nature -> often asume that they can be reproduced in its entirety upon failure
- Unbounded dataset - assumes infinite size. systems that process this data (__historically__ streaming systems) have been tailored to that use case
  - exactly once / at least once = need checkpointing, at most once = does not
  - there's nothing batch- or streaming-specific about persistent state
  - it happends to be critical when processing unbounded data

Persistent state provide two things
- a basis for correctness wrt ephemeral inputs (checkpointing)
- a way to minimize work duplicated wrt failures

> At the end of the day, persistent state is really just a means of providing correctness and efficient fault tolorance in data processing pipelines

#### Implicit state
- not much can do to reduce the size of input \\(\rightarrow\\) persist the intermediate state tables within a pipeline (=implicit?)

Raw grouping
- \\(\sim\\) appending to the list for each group
- data: user/score kv pair
- apply `GroupByKey` of beam -> `user: list of int` PCollection
- sum the scores for users using lambda func
- http://streamingbook.net/fig/7-1
- 각 윈도우별로 int가 아니고 배열을 중간에 들고 있음
- 트리거링이 여러개 (early / on-time / late)있을 경우, sum을 매번 다시 함
- grouping을 체크포인팅한다고 했을 때, 쓸대없는 sum을 다시 해야 함 (너무 당연한 거 아닌가)

Incremental Combining
- associative, commutative 한 연산에 대해 최적화 해 줌 (걍 다 더하는 듯). 어떤 순서로 더하던 완전 상관없으니 최적화 가능한 듯
- incremental combining is a form of automatic state built upon a user-defined associative and commutative combining operator
- ex) mean = 중간 형태 (sum, associative & commutative) / 최종 (전체 수로 나누기)
  - window merging할때도 중간형태끼리 합하면 되서 좋음
- `incrementalization`: b/c the order of individual inputs doesnt matter, we dont need to buffer all the inputs in some strict order
- `parallelization`: we're free to spread computation of those subgroups across a plurality of machines
- one shortcoming: grouping operations are restricted (sums, means, ...)

Generalized State (빔 광고타임?)
- raw grouping: requires to buffer up the raw inputs to the grouping opereation - no way for partial processing
- incremental: allows partial processing, but is restricted
- we need flexibility in 3 dims
  - data structure (grouping = list, incremental = single value. 보통 이것보단 많이 필요)
  - write/read granularity - 입력을 언제 읽어 (중간)상태를 언제 쓸 수 있는지?
  - flexibility in scheduling processing
    - triggers
      - `completeness trigger` provide a way to bind processing to the watermark (=end of window)
      - `repeated update trigger`: periodic
    - 이것만으론 불충분해서 timer를 도입했다 함 (ex - 전체 input completeness말고 일부 record의 input completeness만 있어도 되는 join?)

#### Conversion Attribution


- pooly served by raw grouping / incremental, so we need to go to low lvl (with generalized state)
- to provide concrete feedback on the effectiveness of advertisement
- http://streamingbook.net/fig/7-3
  - Building up conversion attributions over an unbounded, out-of-order stream of data requires keeping tack of impressions, visits, goals. That's where persistent state comes in
  - `impression`: click ad. is a visit
  - `visits`: single page view
  - `goal`: purchase. is a visit
  - `watermark`: purchased event time
- `conversion attribution`: identify imporession which resulted in goal
  - goal -> list of visits (trail) -> impression (this is our target)

(rather general) required property of data pipeline
- handle out of order data (ad imp, website traffic데이터가 이벤트타임대로 들어오지 않음)
- handle high volume of data
- protect against spam
  - ex) a single ad that is clicked multiple times in a row by single user - as long as those clicks occur within a certain amount of time of one another they must be considered as one
- optimize for performance
  - 병렬화가 beam에 지정한 키 별로 된다는데. 카프카로 이거 짜려면 일단 같은 파티션에 동일 유저 데이터를 몰아넣을 수 있어야 하나?...

<a href="https://github.com/takidau/streamingbook/blob/master/src/main/java/net/streamingbook/StateAndTimers.java" target="_blank">code</a> - use Beam's State, Timers API
- POJO (plane old java object) def (with getter, setters)
- `static class AttributionFn extends DoFn<KV<String, VisitOrImpression>, Attribution>` part: consume a flattened collection of Visits, and Impressions (여기서 flattened = VisitOrImpression 클래스로 묶였단 예기), keyed by user \\(\rightarrow\\) yield a collection of Attributions
  1. save all visits, imps in a dict keyed by the URL
- 아니 persistent state 저장하는 곳이 어디야?

### Chap 8

- things discussed here is still hypothetical - 아직도?
- the vision for stream SQL presented here is the result of discussion between Calcite, Flink and Beam communities
- `relation`: conceptual table
- `relational algebra` - mathematical way to describe relationships between relations
  - `closure property` of relational algebra: applying any operation from relational algebra to relation yields another relation
  - historic failures in stream SQL (`sSQL`): failed to satisfy this property
    - treat stream separately from classic relation. users need to learn 4 types of operations (relations <-> streams) - SQL같은 명령형? 언어에서는 치명적이었을 듯

what we need is a way for stream to become a first-class citizen within the relational algebra itself
- not that they (relations, streams) are treated exactly same - but the core operations must apply to them cleanly
- the key to integrate streaming into SQL - extend relation to 3d (`time-varying relations` = `TVR`)
  - `select TVR * FROM UserScores`; -> 시간별로 다 나옴
  - TVR essentially consists of a sequence of classic relations -> __if we apply (classical) relation algebra on TVR, it yields TVR__
  - closure property holds on this extended relations

but TVRs are not practical 

#### Streams and Table
The SQL 2011 standard (already) provides temporal tables
- + `AS OF SYSTEM TIME` construct - explcit query snapshot of table at certain time

SELECT TVR vs SELECT STREAM
- encode하는 데이터는 동일하지만, STREAM은 upsert시 row2개가 더 생김 (기존값 포함) + 현재진행형


Table과 stream은 dual (!) relation
- 보통 full fidelity를 유지하진 않고 loss가 있음 (람다 아키텍처?)


Inherent stream bias in the Beam Model
- all of the logical transformations are connected by streams, even it includes grouping (which results in a temporary table somewhere as noted in Chap6)
  - these transformations are `PTransforms`
  - streams are the common currency in a Beam pipeline (even batch pipelines), and tables are always treated specially, either abstracted behind sources and sinks at the edge of the pipeline or hidden away beneath a grouping and triggering operation somewhere in the pipeline
  - whenever the table is involced, some sort of conversion is required
  - __source__ that consumes tables are hardcoded - no way for a user to specify custom triggering of a table
  - __sinks__ that write tables are also hardcoded - in a way which they group ther input streams
    - explicit grouping - by user key (some customization possible)
    - impicit grouping (by partition, for example)
  - grouping to table / ungrouping to stream - provide complete flexibility