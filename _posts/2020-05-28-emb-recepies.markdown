---
layout: post
title:  "임베디드 레시피"
date:   2020-05-28 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

* <a href="http://recipes.egloos.com/" target="_blank">http://recipes.egloos.com/</a> 크롬에서 깨지네...?
* 이런 책이 있어서 정말 다행인듯

### Clock
- `edge trigger` : clock이 High, Low일 시 IC가 동작하는 게 아니라, 올라갈 떄 또는 내려갈 때 동작
- `level trigger`: clock이 High, Low일 시 IC가 동작


### BUS
- 보통 CPU의 `CU`가 아비터 역, CU가 안하고 Arbiter가 할때도 있다고 함 (언제?)

### Register
- `R13` : SP
- `R14` : LR (Link register). BL 후 복귀 용. 복귀 시 MOV로 LR값을 PC에 복원


### Memory
- `NAND` flash vs `XOR` flash : 낸드는 page단위 (512bytes~2KB)로만 r/w가 가능 (random access 불가). XOR는 word단위의 read가 되어서 코드 실행이 됨 (`XIP`!)
- 잘 알다시피, 주소 1개에 1byte (8bit). 예를 들어 메모리 offset이 `#define GPIO_OE 0x134` 인 곳을 int* arr로 접근하려면, `arr[GPIO_OE/4]`로 가야 됨.


<a href="https://namu.wiki/w/CISC" target="_blank">https://namu.wiki/w/CISC</a>  
> 현재의 x86 CPU는 내부적으로 RISC로 동작하면서 CISC 명령을 에뮬레이션하는 형태를 취하고 있기 때문에 CISC 아키텍처가 아직까지 살아남아 있다고 주장하기는 어렵다. 즉 CISC는 RISC와 섞여 혼종처럼 남아있는 상태라, 순수한 CISC는 현재 찾아볼 수 없다.


### Compile
- `ADS` : ARM Developers' Suit compliler.
- 그러고보면 TI는 맨날 `ARM GCC`만 주네.
- Assembly와 기계어는 1:1이나, 아닌 경우도 나옴 (뒤에)
- `.c` -> preprocessor -> `.s` (assembler. gcc의 -S 옵션) -> `.o` -> linking (+`scl` : scatter loading) -> elf / map -> bin

#### library
1. `armar -zs f_t.b` : f_t.b 라이브러리 파일의 object 파일들을 list함
2. `armar -d f_t.b printf2.o` : 그 중 printf2.o를 제거
3. `armar -c f_t.b printf2.o` : 새로 만든 printf2.o를  f_t.b에 삽입


#### 컴파일러 옵션 (187p)
- `-g` : Debugging 정보. 즉 DWARF정보를 ELF 파일에 넣음  
  > elf형식은 실제 기계어 binary와 symbol 정보, 그리고 마지막 -g option에 의한 debugging 정보까지 포함시켜, debugging을 할 수 있는 여건을 만들 수 있습니다.

#### 변수의 scope와 그 생애 (memory map) (191p)
- 변수의 유형 : `auto`, `extern`, `static`, `volatile`
- `static` 정리 :  값은 항상 유지하되, 해당 변수를 선언한 함수 (`{}`또는 파일에서만 사용하도록 함
- `volatile` : "보통 device driver를 design할 때 이런 volatile을 많이 쓰게 되는데, 왜냐하면 Memory mapped I/O의 경우 같은 주소에 다른 값들을 연숙하서 쓰기 때문


### Linker

#### Memory map과 symbol (199p)
 - `symbol` (global)
   - linker가 식별하는 기본 단위. linking 후 자신만의 주소를 가짐
   - linker만의 pointer. 실제 메모리에 적재되지는 않으며, 모두 주소로 변환됨
 - symbol이 아닌 것 = local.
   - `global` : 함수, 전역변수, static 변수 (함수 내의 static 변수도 global임) (RO, RW, ZI 전부 포함)
   - `local` : 나머지 (stack, heap)

> symbol인 것 = local vs symbol이 아닌 것 = global (자기 자신만의 주소를 가짐)


RO, RW, ZI는 Flash MCP에서 어디에 위치할 것인가
- RO: Flash에만 있으면 됨
- RW: Flash에도 있고 (loading view), RAM에도 있음 (execution view)
- ZI: RAM에만 있음

#### ELF - Linking view (relocatable file) (205p)
- `.o` 파일. 어셈블러의 출력. `relocatable file`. 
- ex) `fromelf -c spaghetti.o`

`.o` 파일의 구조
- ELF 헤더 (엔디안, CPU, ...)
- opcode - 기계어
- data
- __sections__
  - `.text` : complile된 기계어
  - `.rel.text` : 구멍 난 `.text`들. 링킹거쳐야 실행가능
  - `.data` : 초기값 있는 전역변수들
  - `.rel.data` : 구멍 난 `.data`들. 링킹거쳐야 실행가능
  - `.rodata` : const데이터, switch case문에 의한 jump table?
  - `.symtab` : symbol table. 심볼의 목록/주소 (각 section에서의 해당 symbol의 시작 offset) / 크기 / type, scope 보유 링킹시 이부분을 참고. -`-g`를 쓰지 않아도 생성됨. 링킹시 필요하니까
  - `.debug` : DWARF. 지역/젼역 변수들에 대한 디버깅 심볼 포함
  - `.bss` : ZI
- `section header table`

`segment`: sum of sections

### ELF - Execution view (after linking) (216p)

위 .o파일이 링킹 후 executable view로 바뀌면, `.rel.x`가 전부 없어지고, segment별로 section들이 정리되고, `.init` 섹션이 생김. 임베디드 시스템에서는 위 중 ELF header / symbol table / debug 정보 등은 제외하고, `.text` + `.rodata` 를 `RO`, `.data` 를 `RW` 라는 2개의 section으로 나눈 binary를 flash memory에 burining함.

Global symbol이 겹칠 시
- `strong` global symbol : 함수, 초기화가 된 전역변수
- `weak` global symbol : 초기화가 되지 않은 전역변수

__Cases__
1. multiple strong symbols : link error
2. 1 strong symbol : multiple weak symbol - choose 1 strong symbol
3. multiple weak symbol : randomly selects one


#### Scatter loading

최종 실행 이미지를 구성하는 방법 (`XIP`가 가능한 메모리에는 code를, Data는 R/W가 가능한 영역에). 

용어
* GNU: `Linker Description Script`
* ADS: `scatter loading file`

내용
* `input section`: RO/RW/ZI중 하나의 속성을 가짐. scatter loading의 최소 단위. 출력결과에 나오지는 않음 (링커 내부에서 소비되는 정보)
* `output sections`: input section의 집합 (ZI의 집합, RO의 집합 등...). 링커가 생성하는 중간 정보
* `region`: output section의 집합. output section들을 묶을때 알아서 sorting이 됨. 

> 결국 scatter loading에 표시해 줘야 하는 정보는 input section / region. 링커가 알아서 input section -> output seciton -> region 과정을 수행

* Load view: Flash에 있을 때의 메모리 구조. RO/RW만 있음
* Execution view: 메모리에서 실행중일 때의 메모리 구조. XIP지원하는 flash일 경우, RO는 그대로 (flash에) 있고, 나머지는 메모리로 옮겨 감 (write가 random access로 되어야 하기 때문)\

scatter loading 예시 (`.scl`파일)
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




