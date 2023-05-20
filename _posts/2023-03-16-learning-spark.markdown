---
layout: post
title:  "Learning Spark"
date:   2023-03-16 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---

### Chap 1

Spark Driver
- SparkSession 객체 초기화
- Cluster Manager와 통신하여 Executor들이 필요한 자원 요청
- 모든 스파크 작업을 DAG형태료 변환 및 스케쥴링
  - 각 실행 단위를 태스크로 분해해 executor에 분배

Spark Session
- 모든 스파크 연산과 데이터에 대한 통합 채널

Spark Executor
- 드라이버와 통신하며 워커에서 태스크를 실행


파티션
- 물리적으로 실제로 분산된 데이터
- `.repartition(8)`: 데이터를 8개의 파티션으로 나누고, 각 executor가 파티션을 나눠가짐
- 각 executor가 쓰는 코어는 작업해야 하는 데이터의 파티션에 할당되게 됨


프레임워크의 목적
- 분산작업에 있어서 개발자가 익히느라 고생해야 하는 개념들의 개수를 줄이는 것

### Chap 2

job은 태스크라고 분리는 저수준 RDD 바이트 코드로 변환되며, 실행을 위해 executor에 분산됨
- 생성된 RDD코드는 RDD API와는 좀 다르긴 함

Spark shell을 쓸 때 드라이버는 shell에 포함된 형태이며, SparkSession객체가 미리 만들어져 있음

(스파크 엡 ) 내부에 (스파크 드라이버) 가 초기화 (스파크 세션)

#### Job

"드라이버가 스파크 App을 1개 이상의 Job으로 분해"
- 각 job은 DAG로 변환
- 이 DAG그래프에서 1개 노드 = 1개 스테이지

#### Stage
- 1개 잡 : 1개 이상의 스테이지
- 노드에 나눠져서 실행

#### Task
- __최소 실행 단위__
- 각 대스크는 개별 CPU코어에 할당되고, 개별 파티션을 갖고 작업한다
- 16코어 executor = 16개 __이상__ 의 파티션을 갖는 16개 이상의 태스크를 할당받아 작업


트랜스포메이션
- 모든 트랜스포메이션은 액션을 호출할 때 까지 기록됨 (lineage로 변환되어)


### Chap 3 정형화 API

RDD - 3개의 핵심 특성 보유
- 의존성: (현재 RDD가 어떻게 만들어지는지)
- 파티션: 로컬 파티션 정보
- iteraotr: RDD에 저장된 데이터들을 `Iterator[T]` 형태로 만들어주는 compute function

RDD는 최적화 여지가 적고 (저수준) 어려워서 사용자 입장에선 잘 안쓰이게 됨
- 고수준: 언어끼리 일반화도 쉬움

#### Dataframe API
- DataFrame: named column과 schema를 가진, 분산 인메모리 테이블처럼 동작
- `schema`: 데이터 프레임을 위해 칼럼 이름과 연관된 데이터 타입을 정의한 것
  - 외부 데이터 소스에서 구조화된 데이터를 읽을 때 자주 쓰임

미리 스키마를 정의하는 것의 장점
- 추측에 들어가는 리소스 절약
- 스키마 확정을 위해 데이터를 미리 읽는 job 생성 방지 (데이터가 크면 꽤 부담)

API/DDL (진짜 DDL)로 정의 가능

`withcolumn`: 새 컬럼 추가 (왜 with이지..)

row
- ordered set of fields


그림 3-3, 4

### Chap 4
스파크는 각 테이블에 대한 메타데이터를 보유
- 스키마, 설명, 테이블명, db명, 컬럼명, 파티션, 실제 물리 위치 등

디폴트로 `/user/hive/warehouse`의 하파치 `하이브 메타스토어`를 사용하여 테이블 메타데이터 관리
- `spark.sql.warehouse.dir`을 외부 분산저장소로 설정해 변경가능

관리형/비관리형 테이블
- 관리형: 메타데이터 + 데이터
- 비관리형: 메타데이터만 관리 (drop table시 메타만 날아감)

`view`
- 임시테이블? 전역뷰 (앱에 속하는 모든 sparksession들이 공유가능) / 세션범위

테이블 캐싱 가능

DataFrameReader
- `DataFrameReader.format(args).option("key", "value").schema(args).load()`
- format: avro, parquet, txt, json, csv
- schema: DDL 또는 StructType

parquet
- 컬럼기반 스토리지 (?)

avro: 카프카쪽 표준포멧? json과 빠르게 대응가