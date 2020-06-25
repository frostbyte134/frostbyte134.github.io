---
layout: post
title:  "ARM Exception, Interrupt"
date:   2020-06-24 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

목표1 : 6/28까지 BBB 임베디드 리눅스에 ISR 더하는 실습까지 완료하기 (ftrace로 체크). 

- <a href="http://jake.dothome.co.kr/exception-1/" target="_blank">http://jake.dothome.co.kr/exception-1/</a>
- <a href="https://blog.naver.com/PostView.nhn?blogId=eom913&logNo=123249122" target="_blank">https://blog.naver.com/PostView.nhn?blogId=eom913&logNo=123249122</a>



### Embedded recipes


#### ARM exception과 Modes (124p)

`Exceptions list`
| Low vector | High vector | Exception | Entry mode |
|-------|--------|---------|---------|
| 0x00000000 | 0xFFFF0000 | Reset | SVC | 
| 0x00000004 | 0xFFFF0004 | Undefined instruction | UNDEF | 
| 0x00000008 | 0xFFFF0008 | SWI | SVC | 
| 0x0000000C | 0xFFFF000C | Abort (prefetch) | ABT | 
| 0x00000010 | 0xFFFF0010 | Abort (data) | ABT | 
| 0x00000014 | 0xFFFF0014 | Reserved | Reserved | 
| 0x00000018 | 0xFFFF0018 | IRQ | IRQ | 
| 0x0000001C | 0xFFFF001C | FIQ | FIQ | 

`Modes and exceptions`
| CPSR(4:0) | Mode | Register | 진입유발자 |
|-------|--------|---------|---------|
| 10000 | user | user |  | 
| 10001 | FIQ | _fir | Fast interrupts | 
| 10010 | IRQ | _irq | Standard interrupts | 
| 10011 | SVC | _svc | Reset. Power on. SWI | 
| 10111 | Abort | _abt | Memory faults | 
| 11011 | Undef | _und | Undefined instructions | 
| 11111 | System | user |  | 



- CPSR: NZCV(4) unused IF(4) T(1) mode(4)
- Interrupt는 Exception의 한 종류
- `Exception vectors`: 보통 메모리 맨 처음에 있음 (Low든 high든..).
  - Exception이 일어났을 때 jump하는 addr = `Exception vector`
    - Exception vector들을 모은 테이블 : `Exception Vector table`
  - USER 모드에서 previliage mode로 보통은 못 넘어가며, Exception으로만 가능 (반대 or 자기들끼리는 가능)
    - SYS, USER모드는 진입점이 되는 exception이 없음 : SPSR도 따로 없음
  - Exception끼리 순위 : reset이 최상위, SWI가 최하위
  - Exception 에서 실행되는 부분은 Thumb모드로 실행하면 안됨

EX) SVC -> IRQ 모드
1. CPSR을 SPSR_irq에 복사 (SVC에서 실행중이던 CPSR값)
2. CPSR모드를 IRQ로 변경 (sp도 자동으로 변경됨)
3. IRQ disable, set to ARM-state (non-thumb) (I=1, T=0)
4. R14_irq(LR) := 현재 PC
5. PC := IRQ excetion vector
6. 현재 R0~R12를 R13_irq가 가르키는 stack에 저장
7. R14_irq에 넣은 주소 보정 (pipeline고려해서, 1번(?) 뒤로 = `sub lr, lr, #4`)
8. 이제 복원준비
   1.  CPSR := SPSR_irq (이전 모드인 SVC로 복귀됨)
   2.  스택을 참고해서 register값들 복원 (irq stack에 저장했으므로 1번 이전 아닌가?)
   3.  PC := R14_irq


#### ARM은 어떻게 interrupt 냄새를 맡는가?