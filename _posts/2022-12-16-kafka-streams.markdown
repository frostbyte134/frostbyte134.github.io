---
layout: post
title:  "streaming migration"
date:   2022-12-16 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---


### 스파크 스트리밍 정리
https://medium.com/naver-biz-dev/spark-%EC%8A%A4%ED%8A%B8%EB%A6%AC%EB%B0%8D%EA%B3%BC-session-window-%EC%86%8C%EA%B0%9C-6471b2ffa102

`append mode`
- watermark로 프로세싱 타임 처리. 워터마크 이전에 온 것들은 반영 안하고 버려서, 그냥 고정된 결과가 계속 append되는 형태임

`Update mode`
- 워터마크 딱히 없이 무한 반영인 듯? 이 방식은 Spark Structured Streaming을 통해 제공

Spart structured streaming
- 



아니 ㅡ,.ㅡ 연말에 일이 좀 줄어야 하는 거 아닌가...ㄷㄷ

req
- 프레임워크가 아니고 라이브러리면 좋겠음. 카프카 스트림스가 딱인데...파이썬이 안되네
- 로컬테스트가 쉬우면 젤 좋을 듯
- fail시 통지가 가능해야 함. 표준출력으로 나가는걸 로깅에이전트가 받으면 젤 좋겠지만. 에러나면 표준출력으로도 쏘고, 환경변수로 옵셔널하게 특정url에 json post정도는 보낼 수 있어여 할 듯. 팀의 표준 모델이 있으면 좋겠는데..



현상황 정리
- 카프카 스트림스 - 파이썬으로 안되고 지원할 계획도 없슴 (https://github.com/confluentinc/confluent-kafka-python/issues/38#issuecomment-1017217407)
- 스파크 스트리밍 - yaml로 선언적 배포를 하기가 꽤 힘들어 보임 (crd가 좀 구글클라우드 specific한 느낌). 유지보수가 불편할 거 같음....
    - 로컬테스트같은 것도 쉽게 할 수 있어야 하는데 것도 어려워 보임
    - 아니 근데 길이 이거밖에 없어 보이는데....?ㅎㅎㅎ....
- 파우스트
    - 흠...너무 마이너해서 인수인계받는 사람들이 별로 안좋아 할 것 같음...ㅎㅎ

또 생각해 볼 것 - fail/fault시 얼럿이 잘 가야 함. 스트리밍 프로세싱 내부에서 이런 얼럿을 처리하거나...stdout으로 별도로 쏘거나? -> fluentd같은거에서 읽어서..? 복잡해지네

일단 이슈 만들고 한 의견도 물어보자

### Spark streaming

실행환경 구성에서 필요한 게 넘 많아 보여서 유지보수에 안좋을 것 같았음. -> 카프카 스트림즈로 넘어감 ㅋㅋ 이 포스트를 다시 건드릴 일이 있을까나...

[Running Spark on Kubernetes](https://spark.apache.org/docs/latest/running-on-kubernetes.html)에는 뭔가 job을 submit하는 형식인데, 경험상 유지보수에 엄청 안좋음. 거의 불가능?
- 어딘가에 야믈로 선안되고 그거대로 돌아가는지 argocd/각종 diff로 체크할 수 있는 게 젤 좋아보임. 결국 쓸 수 있을 지 모르겠지만...[spark crd](https://github.com/GoogleCloudPlatform/spark-on-k8s-operator)를 봐야 할 듯

- <a href="https://spark.apache.org/docs/latest/api/python/user_guide/python_packaging.html" target="_blank">스파크 - 파이썬</a>
- [pyspark and spark](https://stackoverflow.com/questions/72666716/pyspark-vs-scala-spark-vs-spark-sql-which-one-is-performance-efficient-are-ud)

#### structured spark

스파크 스트리밍이 <a href="https://spark.apache.org/docs/latest/structured-streaming-programming-guide.html" target="_blank">structured spark?</a> 이걸로 바뀐 듯

Overview
- can use the`Dataset/DataFrame API` in Scala, Java, `Python` or R to express streaming aggregations, event-time windows, stream-to-batch joins, etc
- computation is executed on the same optimized Spark SQL engine
- the system ensures exactly-once fault-tolerance guarantees through checkpointing and Write-Ahead Logs
- internally uses `micro-batch` processing engine (processes data streams as a series of small batch jobs) thereby achieving e2e latencies under 100 milliseconds and __exactly-once__ fault-tolerance guarantees
    - 마이크로배칭이랑 exactly-once랑 뭔상관?
- since Spark 2.3, introduced a new low-latency processing mode called `Continuous Processing`, which can achieve e2e latencies as low as 1 millisecond with __at-least-once__ guarantees


실행환경 구성 - 결국 이 환경을 실제로도 쓰게 될 것 같아서...잘 말려있는 이미지가 있나 봐야 할 듯
- 아니근데 이거 crd도 그렇고 좀...복잡한데? 간단한 로깅 파이프라인인데 이렇게 복잡할 필요가 있는지 모르겠음.
- crd을 dkos에 적용했을 때 무리가 없을까? crd업데이트는? 이걸 공용클러스터에 깔았을 때 다른사람들이 미래에라도 영향을 안받나?
- 실행이 좀 복잡해보임. 프레임워크라 그런가..
- 카프카 스트림즈...?


#### spark crd
<a href="https://github.com/GoogleCloudPlatform/spark-on-k8s-operator" target="_blank">link</a>



### Kafka streams
파이썬이랑 연동계획이 엄슴
- https://github.com/confluentinc/confluent-kafka-python/issues/38#issuecomment-1017217407
- 난 자바도 되긴 하는데......좀 그렇네

Initially was thinking of using spark streaming
- but as it is framework rather than a library, there were many pre-required things needed to be set up to run it on inhouse k8s cluster
- spark streaming CRD mainly supports google cloud. Not sure it is supported on other places - bad cond for maintanence

After reading [the article](https://engineering.linecorp.com/ko/blog/applying-kafka-streams-for-internal-message-delivery-pipeline/) from Line tech blog, began to consider spark streaming

뭔 영어임 ㅡ,.ㅡ

카프카 스트리밍 특징
- 카프카와 당연히 연동이 잘 됨
- 롤링 리스타트 지원? 뭐 시그텀 처리 그런거도 다 되어 있나?
- masterless - 브로커의 파티션 할당 메커니즘에 많은 것을 의존한 ㄴ듯
- 로컬 상태가 있다? 이걸 락스디비에 저장하는 듯.
    - 이 부분을 좀 더 봐야 할 것 같음
    - Kafka Streams의 프로세스가 다른 호스트로 failover시 state DB도 함께 새 프로세서로 이전
    - 이 로컬상태는 inmemory / rocksdb 등 pluggable가능
    - 'changelog' topic을 위한 특수한 메시지를 생성 -> changelog topic은 로컬 state의 WAL(Write-Ahead-Log)로 간주할 수 있습니다
    - 토픽이 하나 필요한 듯?


https://www.confluent.io/blog/getting-started-with-apache-kafka-in-python/

https://kafka.apache.org/33/documentation/streams/
- 파이썬이 없네??

https://www.confluent.io/blog/how-kafka-streams-works-guide-to-stream-processing/

sink
- 제일 없을거같은데 프로메테우스 커넥터인데 있네?ㅋㅋ https://docs.confluent.io/kafka-connectors/prometheus-metrics/current/overview.html#features
- mysql, ES는 당연히 있겠지...