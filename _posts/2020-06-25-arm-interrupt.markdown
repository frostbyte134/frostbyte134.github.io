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
  - <a href="http://jake.dothome.co.kr/arm-exception-vector/" target="_blank">http://jake.dothome.co.kr/arm-exception-vector/</a>
- <a href="https://blog.naver.com/PostView.nhn?blogId=eom913&logNo=123249122" target="_blank">https://blog.naver.com/PostView.nhn?blogId=eom913&logNo=123249122</a>
- <a href="https://www.linux.com/training-tutorials/beaglebone-black-how-get-interrupts-through-linux-gpio/" target="_blank">https://www.linux.com/training-tutorials/beaglebone-black-how-get-interrupts-through-linux-gpio/</a>
- <a href="https://blog.dasomoli.org/tag/gpio_to_irq/" target="_blank">https://blog.dasomoli.org/tag/gpio_to_irq/</a>



### Embedded recipes


#### ARM exception과 Modes (124p)
<a href="http://recipes.egloos.com/4986862" target="_blank">http://recipes.egloos.com/4986862</a>

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


#### ARM은 어떻게 interrupt 냄새를 맡는가? (138p)
<a href="http://recipes.egloos.com/4986862" target="_blank">http://recipes.egloos.com/4988641</a>


1. Interrupt가 걸리면 실행 주소가 Exception vector중 IRQ/FIQ vector로 강제로 바뀜 (CPSR 모드도)
2. 해당 vector에는 각 handler (`ISR` : Interrupt Service Routine)로 branch하기 위한 code가 들어 있음
3. 몇 번 ISR이 들어왔는지 register를 읽어 확인 가능하므로 (139p의 n IRQ / FIQ 그림) branch가능
4. `DPC` = `APC` = `Bottom Half`

#### Pipeline과 Exception의 관계, 그리고 ^접미사
- Exception의 종류. 원래대로 돌아가려먼 PC (fetch해 온 곳)를 어느만큼 보정해줘야 하는가
- `^` : SPSR을 CPSR에 넣어라. register를 stack에서 복원할 때 (원래로 돌아갈 때) 많이 쓰는듯
  - `ldmfd sp!, {r0-r12, PC}^ ; Register restore`

#### Exception vector table과 각 Handler의 구현
<a href="http://recipes.egloos.com/5035801" target="_blank">http://recipes.egloos.com/5035801</a>

```
AREA    INIT_VECTOR, CODE, READONLY   → INIT_VECTOR라는 부분 기억해 두세요.
      CODE32                         ; 32 bit ARM instruction set.        
      
      ENTRY 
      B       Reset_Handler                       ; 0x0 
      B       Undefined_Handler                   ; 0x4        
      B       SWI_Handler                         ; 0x8        
      B       Prefetch_Handler                    ; 0xC        
      B       Abort_Handler                       ; 0x10        
      B       Nothing_Handler                     ; 0x14        
      B       IRQ_Handler                         ; 0x18        
      B       FIQ_Handler                         ; 0x1C
```

- Branch하게 되어있음 (ARM mode)
- Scatter loading을 이용해서 컴파일 시 0x0부터 자리잡게 하고, Flash에 저장할 때 0x0부터 차례대로 Flashing 하면 된다고 함
- 또는 SDRAM이 0x0부터 시작하는 거라면 0x0부터 복사하면 됨
- B 대신, `ldr pc, memory_position` 을 넣고 memory_position에 그때그떄 다른 handler를 넣으면 flashing하는 수고를 덜 수도 있다고 함

`Undefined handler`
- 정말 undefined opcode를 읽었을 시
- coprocessor에 뭔가 시키고 싶을 시, 일부러 발생시킴


`SWI handler`  
```
SWI_Handler
  stmfd sp!, {r0-r12, r14} ; Register backup
  - things to implement
  ldmfd sp!, {r0-r12, PC}^ ; Register restore
```

#### SWI의 진실
- 구현하기 전에 다시 읽어 보기


#### GPIO(Tristate Buffer)의 정체와  GPIO ISR (557p)
- ARM base의 입장에서의 GPIO는 AMBA bus에 연결된 SOC peripheral
  - =ARM bus에 연결된 slave이므로 register를 통해서 control가능



### 비글본 블랙에서 gpio 인터럽트 만들기
- <a href="{{site.url}}/coding/2020/06/30/beaglebone-black.html#gpio" target="_blank">링크</a>
- gpio 30번하고 60번을 이어주고, 30번에 sysfs (`/sys/class/gpio/gpio30/value`)  로 값을 넣어 줘야 함. 난 edge인터럽트 만들었으니 0에서 1로. (down edge는 없나?)

### 디버깅을 통해 배우는 리눅스 커널의 구조와 원리
- eMMC 리눅스엔 otg인터럽트가 없음. 근데 이게 뭐지.
- `cat /proc/interrupts` : 인터럽트 기록
- `in_interrupt()` 커널 함수 : 인터럽트 컨텍스트에 있는지 여부 반환 (CPU는 IRQ/FIQ 모드로 되겠지? 잘 모르지만..디버거가 있어야 확인가능한가.)
- `BUG_ON()` 커널 함수 : 커널 패닉 유발 (시스템 리셋의 의도). 코어 덤프 출력하고 종료하겠다.
- `register unsigned long current_stack_pointer asm ("sp")`
  - <a href="https://gcc.gnu.org/onlinedocs/gcc/Local-Register-Variables.html#Local-Register-Variables" target="_blank">You can define a global register variable and associate it with a specified register like this</a> : 
- 인터럽트 컨텍스트에서 스케쥴링 시도 시 (뮤택스 선언도 포함), 보통 BUG()함수를 호출해 강제종료한다 함
  - 뮤텍스는 스케쥴링을 지원하는 기능이기 떄문 (lock걸린 뮤텍스에 다른 프로세스가 접근하면 휴면상태갸 됨)
- `__irq_svc` : 인터럽트 벡터. 커널로그에 이거 뜨면 인터럽트임
  ```
  __irq_svc:
	  svc_entry
	  irq_handler
  ```
  - `KERNEL/arch/arm.kernel/entry-armv.S` 에 `__irq_svc` 레이블이 있음. 이 레이블의 svc_entry 매크로를 따라가면 (`.macro	svc_entry`),  
  ```
  stmia	sp, {r1 - r12}

	ldmia	r0, {r3 - r5}
	add	r7, sp, #S_SP - 4	@ here for interlock avoidance
	mov	r6, #-1			@  ""  ""      ""       ""
	add	r2, sp, #(SVC_REGS_SIZE + \stack_hole - 4)
 SPFIX(	addeq	r2, r2, #4	)
	str	r3, [sp, #-4]!		@ save the "real" r0 copied
					@ from the exception stack

	mov	r3, lr

	@
	@ We are now ready to fill in the remaining blanks on the stack:
	@
	@  r2 - sp_svc
	@  r3 - lr_svc
	@  r4 - lr_<exception>, already fixed up for correct return/restart
	@  r5 - spsr_<exception>
	@  r6 - orig_r0 (see pt_regs definition in ptrace.h)
	@
	stmia	r7, {r2 - r6}
  ```
  부분이 나옴. 아직 완벽하게 해석은 어렵네...
  - 결국 다 처리하고 난 뒤 `irq_handler` 에서 `handle_arch_irq`로 브랜치함. 여기에 인터럽트를 처리하는 커널 내부 함수가 있는 듯
  - `인터럽트 디스크립터`를 읽어 어떤 인터럽트인지 안 뒤, 핸들러를 호출한다고 함 (`KERNEL/kernel/irq/handle.c - __handle_irq_event_percpu` 부분)

