---
layout: post
title:  "임베디드 시스템을 위한 C프로그래밍 기법"
date:   2020-02-01 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

도서관에서 빌림. 좀 된 책인듯

띵언
> 자신밖에 알 수 없는 프로그램은 얼마 지나지 않아 자신도 알 수 없게 된다.


### Why C?
* 소멸자, 가비지 콜렉터로 메모리 관리가 되는 C++, Java = memory fragmentation이 일어남
* C는 비교적 순차적 (스택=위에서 아래, heap=아래서 위)이기 때문에, 이런 현상이 덜 일어님
* 가비지 콜렉션은 리얼타임 조건이 엄격할 시 부담이 됨

`마이컴`: 타깃 CPU

설계 재검토 필요
* 함수의 기능을 설명하면 x와 y한다. 그리고 z를 k한다 라고 복수의 문장이 되는 모듈
* 기능 설명 문장 속에 `처음에`, `다음에` 등 순서를 나타내는 표현이 있는 모듈

```
char ary[10];
```
- 9개+0

### 싸이클
- `CISC`: 1개 instruction이 복수의 `사이클`(=CPU클록 신호의 1개 주기. 20MH clock - 1/(20 * 1e6))로 실행됨
- `RISC`: 대부분이 1개 싸이클
- 곱샘/나눗샘은 risc라도 35사이클 정도가 필요 (각 기기의 manual 참조)
- 함수 호출 - 8사이클, control statement 4사이클
- `FPU`: double - 배정도, float - 단정도
  - FPU가 없을 시, sw적으로 수행 : 100~1000배 정도 차이가 남.
  - 관련 라이브러리 링크 - 코드사이즈 크기
  - 링커(링키지 에디터)에서 출력된 맵파일의 크기를 보면, 코드사이즈 크기 분석가능
  - printf 링크시, 소수점 라이브러리를 자동으로 링크하는 경우도 있다고 함.


### 프로그램 실행
노이만형 CPU는
- CPU레지스터와 메모리의 지정된 어드레스 사이의, 데이터 R/W
- CPU 내부에서 데이터 연산을 하여, 그 결과를 CPU 레지스터에 저장
- CPU 레지스터와 디바이스 레지스터 (?) 사이에서 데이터 R/W
- 레지스터는 8/16bit등 크기가 다양하고, 특정주소에 포인터로 엑세스 + bit마스킹으로 값 얻음

디바이스 레지스터
 - 데이터 저장용, 상태 알림용 레지스터 등 있다 함.

.data segment
- static으로 선언된 변수나 문자열의 초깃값
- Where your statics go depends on if they are zero-initialized or not. __zero-initialized static data goes in .BSS (Block Started by Symbol), non zero-initialized data goes in .DATA__
  

### 인터럽트
- 인터럽트 벡터 테이블: 각 인터럽트별로 함수 시작주소가 있는 address table
- 인터럽트도 결국 함수이니까, stack구조로 동작 (근데 리눅스를 예로 들면, 커널 인터럽트는 커널 스택을 쓰지 않나)

### 스타트업 루틴
- On 인터럽트 - main() 사이의 과정
- 인터럽트 벡터테이블의 On 인터럽트 부분에 존재
- 처리되는 것들
  - 인터럽트 벡터테이블의 설정
  - 스택 영역의 설정
  - C언어 라이브러리를 위한 초기값 (힙 크기 등)
  - ROM의 프로그램을 RAM에 복사
  - ROM에 있는 변수의 초기값 데이터를 RAM에 복사
  - 하드웨어 초기화 (POST?, register 초기화)
  - main기동


### 코드 최적화
- `global optimize` (대역적 최적화) : 타깃 기기 이용 X
  - `copy propagation`: 값 변경없이 대입되는 경우, 대입 -> 초기화로
  - 공통식 부분의 삭제, 루프 최적화
- `local optimize` (pipehole optimize, scheduling) : 타깃 기기에 의존적
    - 명령어 단위의 최적화


### 링키지 에디터 (링커)
- 기계어 프로그램에서 참조관계 작성
- 각 섹션으로의 할당이 결정됨 (`배치한다` : 메모리 맵 작성하는 것 말하는듯)

실행 가능한 프로그램은 `relocatable` 한 것과 아닌 것으로 나뉨.
