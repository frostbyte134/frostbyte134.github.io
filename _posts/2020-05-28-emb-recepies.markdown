---
layout: post
title:  "임베디드 레시피"
date:   2020-05-28 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---



### Clock
- `edge trigger` : clock이 High, Low일 시 IC가 동작하는 게 아니라, 올라갈 떄 또는 내려갈 때 동작
- `level trigger`: clock이 High, Low일 시 IC가 동작


### BUS
- 보통 CPU의 `CU`가 아비터 역, CU가 안하고 Arbiter가 할때도 있다고 함 (언제?)

### Memory
- `NAND` flash vs `XOR` flash : 낸드는 page단위 (512bytes~2KB)로만 r/w가 가능 (random access 불가). XOR는 word단위의 read가 되어서 코드 실행이 됨 (`XIP`!)
- 잘 알다시피, 주소 1개에 1byte (8bit). 예를 들어 메모리 offset이 `#define GPIO_OE 0x134` 인 곳을 int* arr로 접근하려면, `arr[GPIO_OE/4]`로 가야 됨.


<a href="https://namu.wiki/w/CISC" target="_blank">https://namu.wiki/w/CISC</a>  
> 현재의 x86 CPU는 내부적으로 RISC로 동작하면서 CISC 명령을 에뮬레이션하는 형태를 취하고 있기 때문에 CISC 아키텍처가 아직까지 살아남아 있다고 주장하기는 어렵다. 즉 CISC는 RISC와 섞여 혼종처럼 남아있는 상태라, 순수한 CISC는 현재 찾아볼 수 없다.


### Linker

#### Scatter loading
용어
* GNU: `Linker Description Script`
* ADS: `scatter loading file`

내용
* `input section`: RO/RW/ZI중 하나의 속성을 가짐. scatter loading의 최소 단위. Output으로 나오지는 않음 (링커 내부에서 소비되는 정보)
* `output sections`: input section의 집합 (ZI의 집합, RO의 집합 등...). 링커가 생성하는 중간 정보
* `region`: output section의 집합. output section들을 묶을때 알아서 sorting이 됨. 

> 결국 scatter loading에 표시해 줘야 하는 정보는 input section / region. 링커가 알아서 input section -> output seciton -> region 과정을 수행

* Load view: Flash에 있을 때의 메모리 구조. RO/RW만 있음
* Execution view: 메모리에서 실행중일 때의 메모리 구조. XIP지원하는 flash일 경우, RO는 그대로 (flash에) 있고, 나머지는 메모리로 옮겨 감 (write가 random access로 되어야 하기 때문)\

scatter loading 예시
```
LOAD_ROM 0x0
{
    EXEC_ROM 0x0
    {  
        spaghetti.o (+RO)
    }

    EXEC_RAM 0x8000
    {
        spaghetti.o (+RW)
    }

    EXEC_RAM2 0xA000
    {
        spaghetti.o (+ZI)
    }
}
```

이러면 `load view`에서는 괄호를 다 생략하고
```
LOAD_ROM 0x0
{
    spaghetti.o (+RO)
    spaghetti.o (+RW) 
}
```
로 되며 (ZI는 0초기화에 실행중도 아니므로 불필요), `execution view`에서는 위 대로 배치됨


