---
layout: post
title:  "ARM assembly (ADS, GCC)"
date:   2020-06-12 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

책에는 돈내고 하는 수업이 직빵이라고 하는데..가면 디버거 같은것도 주고 실습 시켜주나...?

* <a href="https://rednine.tistory.com/attachment/cfile5.uf@1508CB334EC4D3C70858A0.pdf" target="_blank">GNU ARM Assembler quick ref</a>
* <a href="https://developer.arm.com/docs/ddi0487/latest/arm-architecture-reference-manual-armv8-for-armv8-a-architecture-profile"> ARM arch ref manual</a>. 2700페이진데...ㄷㄷ

### Directive
- `AREA` : 코드의 묶음. 속성 및 `LABEL`을 가질 수 있음. linker의 최소 단위 (AREA단위로 메모리 할당)
  - 속성: ALIGN (default 4), CODE (machine instruction), DATA, COMDEF, COMMON (common data), NOINIT (.bss), READONLY, READWRITE
  - `LABEL` : 1개 area가 여러 label을 가질 수 있음. ELF file에서의 `.section`. 
  - `ENTRY` : AREA에서 수행되어야 하는 첫 번째 위치
- `CODE32` / `CODE16` : ARM / thumb mode
- 함수명 `proc` : 함수 선언
  - `ENDP` : 함수의 끝
- `ALIGN` b : 이후부터 b로 데이터 얼라인
- `EQU` : define
  - `#define SDRAM_BASE 0x20000000` = `SDRAM_BASE  EQU  0x20000000`
- `MACRO` : C의 매크로처럼 인자를 받을 수도 있음
```
MACRO
mmu_page_table $address
ldr r0, = %address
mcr p15, 0, r0, c2, c0, 0
MEND
```
이렇게 하고 mmu_page_table 0x80000 으로 불러 쓰면, $address에 0x80000이 대입

### Assembly
`명령어 Rd, etc` 포멧
- etc를 명령어 해서 Rd에 넣는다 (`STR`은 반대)
- 이건 레시피 책 282page를 읽는 게 빠를 듯
- `SWP` : 버스에 락을 걸고 스왑. 이거 없어졌다고 하던데?

### ADS vs GNU
C = `#define SDRAM_BASE 0x20000000`

1. `ADS (RVCT)` assembly
```
SDRAM_BASE  EQU  0x20000000
```
2. `GNU` assembly
```
.equ SDRAM_BASE, 0x20000000
```


AREA 표기
1. `ADS (RVCT)` assembly
```
CODE16
AREA main,  CODE, READONLY
```
2. `GNU` assembly
```
  .global main
main:
  .section .text, "x" @ x means executable
  .code 16
```
