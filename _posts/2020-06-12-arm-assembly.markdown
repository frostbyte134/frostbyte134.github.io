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
* <a href="https://cseweb.ucsd.edu/~airturk/CSE30/topic07.pdf" target="_blank">Control flow insructions</a> 
* <a href="http://recipes.egloos.com/5028421" target="_blank"> Embedded recipies. </a>. bgt
* <a href="http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0068b/CIHIDDID.html" target="_blank">ARM info center</a>

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
`명령어 Rd, etc` 형태
- etc를 명령어 해서 Rd에 넣는다 (`STR`은 반대)
- 이건 __레시피 책 282p__ 를 읽는 게 빠를 듯
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


### Example 1. gcd
* <a href="http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0204ik/CEGIHJGH.html" target="_blank">http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0204ik/CEGIHJGH.html</a>
* Why not do it myself?!

#### gcd.c
```c
#include <stdio.h>
 
int gcd(int lhs, int rhs){
	if(rhs <= 1)return lhs;
	return gcd(rhs, lhs%rhs);
}
 
int main(void) {
	// your code goes here
	printf("hello world!\n");
	int val = gcd(32, 24);
	printf("gcd = %d\n", val);
	return 0;
}
```

#### gcd.s
```
        .syntax unified
        .arch armv7-a
        .eabi_attribute 27, 3
        .eabi_attribute 28, 1
        .fpu vfpv3-d16
        .eabi_attribute 20, 1
        .eabi_attribute 21, 1
        .eabi_attribute 23, 3
        .eabi_attribute 24, 1
        .eabi_attribute 25, 1
        .eabi_attribute 26, 2
        .eabi_attribute 30, 6
        .eabi_attribute 34, 1
        .eabi_attribute 18, 4
        .thumb
        .file   "gcd.c"
        .global __aeabi_idivmod
        .text
        .align  2
        .global gcd
        .thumb
        .thumb_func
        .type   gcd, %function
gcd:
        @ args = 0, pretend = 0, frame = 8
        @ frame_needed = 1, uses_anonymous_args = 0
        push    {r7, lr}
        sub     sp, sp, #8
        add     r7, sp, #0
        str     r0, [r7, #4]
        str     r1, [r7]
        ldr     r3, [r7]
        cmp     r3, #1
        bgt     .L2
        ldr     r3, [r7, #4]
        b       .L3
.L2:
        ldr     r3, [r7, #4]
        mov     r0, r3
        ldr     r1, [r7]
        bl      __aeabi_idivmod
        mov     r3, r1
        ldr     r0, [r7]
        mov     r1, r3
        bl      gcd
        mov     r3, r0
.L3:
        mov     r0, r3
        adds    r7, r7, #8
        mov     sp, r7
        @ sp needed
        pop     {r7, pc}
        .size   gcd, .-gcd
        .section        .rodata
        .align  2
.LC0:
        .ascii  "hello world!\000"
        .align  2
.LC1:
        .ascii  "gcd = %d\012\000"
        .text
        .align  2
        .global main
        .thumb
        .thumb_func
        .type   main, %function
main:
        @ args = 0, pretend = 0, frame = 8
        @ frame_needed = 1, uses_anonymous_args = 0
        push    {r7, lr}
        sub     sp, sp, #8
        add     r7, sp, #0
        movw    r0, #:lower16:.LC0
        movt    r0, #:upper16:.LC0
        bl      puts
        movs    r0, #32
        movs    r1, #24
        bl      gcd
        str     r0, [r7, #4]
        movw    r0, #:lower16:.LC1
        movt    r0, #:upper16:.LC1
        ldr     r1, [r7, #4]
        bl      printf
        movs    r3, #0
        mov     r0, r3
        adds    r7, r7, #8
        mov     sp, r7
        @ sp needed
        pop     {r7, pc}
        .size   main, .-main
        .ident  "GCC: (Debian 4.9.2-10) 4.9.2"
        .section        .note.GNU-stack,"",%progbits
```


#### gdb, layout asm
```
   x0x10444 <gcd+12>        cmp    r3, #1                                                                                                                                                                                                                                      x
   x0x10446 <gcd+14>        bgt.n  0x1044c <gcd+20>                                                                                                                                                                                                                            x
   x0x10448 <gcd+16>        ldr    r3, [r7, #4]                                                                                                                                                                                                                                x
   x0x1044a <gcd+18>        b.n    0x10462 <gcd+42>                                                                                                                                                                                                                            x
   x0x1044c <gcd+20>        ldr    r3, [r7, #4]                                                                                                                                                                                                                                x
   x0x1044e <gcd+22>        mov    r0, r3                                                                                                                                                                                                                                      x
   x0x10450 <gcd+24>        ldr    r1, [r7, #0]                                                                                                                                                                                                                                x
   x0x10452 <gcd+26>        bl     0x10734 <__aeabi_idivmod>                                                                                                                                                                                                                   x
   x0x10456 <gcd+30>        mov    r3, r1                                                                                                                                                                                                                                      x
   x0x10458 <gcd+32>        ldr    r0, [r7, #0]                                                                                                                                                                                                                                x
   x0x1045a <gcd+34>        mov    r1, r3                                                                                                                                                                                                                                      x
   x0x1045c <gcd+36>        bl     0x10438 <gcd>                                                                                                                                                                                                                               x
   x0x10460 <gcd+40>        mov    r3, r0                                                                                                                                                                                                                                      x
   x0x10462 <gcd+42>        mov    r0, r3                                                                                                                                                                                                                                      x
   x0x10464 <gcd+44>        adds   r7, #8                                                                                                                                                                                                                                      x
   x0x10466 <gcd+46>        mov    sp, r7                                                                                                                                                                                                                                      x
   x0x10468 <gcd+48>        pop    {r7, pc}                                                                                                                                                                                                                                    x
   x0x1046a                 nop                                                                                                                                                                                                                                                x
   x0x1046c <main>          push   {r7, lr}                                                                                                                                                                                                                                    x
   x0x1046e <main+2>        sub    sp, #8                                                                                                                                                                                                                                      x
   x0x10470 <main+4>        add    r7, sp, #0                                                                                                                                                                                                                                  x
   x0x10472 <main+6>        movw   r0, #1964       ; 0x7ac                                                                                                                                                                                                                     x
   x0x10476 <main+10>       movt   r0, #1                                                                                                                                                                                                                                      x
   x0x1047a <main+14>       blx    0x10324                                                                                                                                                                                                                                     x
   x0x1047e <main+18>       movs   r0, #32                                                                                                                                                                                                                                     x
   x0x10480 <main+20>       movs   r1, #24                                                                                                                                                                                                                                     x
   x0x10482 <main+22>       bl     0x10438 <gcd>                                                                                                                                                                                                                               x
   x0x10486 <main+26>       str    r0, [r7, #4]                                                                                                                                                                                                                                x
   x0x10488 <main+28>       movw   r0, #1980       ; 0x7bc                                                                                                                                                                                                                     x
   x0x1048c <main+32>       movt   r0, #1                                                                                                                                                                                                                                      x
   x0x10490 <main+36>       ldr    r1, [r7, #4]                                                                                                                                                                                                                                x
   x0x10492 <main+38>       blx    0x10318                                                                                                                                                                                                                                     x
   x0x10496 <main+42>       movs   r3, #0                                                                                                                                                                                                                                      x
   x0x10498 <main+44>       mov    r0, r3                                                                                                                                                                                                                                      x
   x0x1049a <main+46>       adds   r7, #8                                                                                                                                                                                                                                      x
   x0x1049c <main+48>       mov    sp, r7                                                                                                                                                                                                                                      x
   x0x1049e <main+50>       pop    {r7, pc}                                                                                                                                                                                                                                    x
   x0x104a0 <__divsi3>      cmp    r1, #0                                                                                                                                                                                                                                      x
   x0x104a2 <__divsi3+2>    beq.w  0x10722 <__divsi3+642>                                                                                                                                                                                                                      x
   x0x104a6 <__divsi3+6>    eor.w  r12, r0, r1                                                                                                                                                                                                                                 x
   x0x104aa <__divsi3+10>   it     mi                                                                                                                                                                                                                                          x
   x0x104ac <__divsi3+12>   negmi  r1, r1                                                                                                                                                                                                                                      x
   x0x104ae <__divsi3+14>   subs   r2, r1, #1                                                                                                                                                                                                                                  x
   x0x104b0 <__divsi3+16>   beq.w  0x106f2 <__divsi3+594>                                                                                                                                                                                                                      x
   x0x104b4 <__divsi3+20>   movs   r3, r0                                                                                                                                                                                                                                      x
   x0x104b6 <__divsi3+22>   it     mi                                                                                                                                                                                                                                          x
   x0x104b8 <__divsi3+24>   negmi  r3, r0                                                                                                                                                                                                                                      x
   x0x104ba <__divsi3+26>   cmp    r3, r1                                                                                                                                                                                                                                      x
   x0x104bc <__divsi3+28>   bls.w  0x106fc <__divsi3+604>                                                                                                                                                                                                                      x
   x0x104c0 <__divsi3+32>   tst    r1, r2                                                                                                                                                                                                                                      x
   x0x104c2 <__divsi3+34>   beq.w  0x1070c <__divsi3+620> 
```


#### objdump -d
```
gcd.out:     file format elf32-littlearm


Disassembly of section .init:

000102ec <_init>:
   102ec:	e92d4008 	push	{r3, lr}
   102f0:	eb000024 	bl	10388 <call_weak_fn>
   102f4:	e8bd8008 	pop	{r3, pc}

Disassembly of section .plt:

000102f8 <raise@plt-0x14>:
   102f8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
   102fc:	e59fe004 	ldr	lr, [pc, #4]	; 10308 <_init+0x1c>
   10300:	e08fe00e 	add	lr, pc, lr
   10304:	e5bef008 	ldr	pc, [lr, #8]!
   10308:	000105c0 	.word	0x000105c0

0001030c <raise@plt>:
   1030c:	e28fc600 	add	ip, pc, #0, 12
   10310:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10314:	e5bcf5c0 	ldr	pc, [ip, #1472]!	; 0x5c0

00010318 <printf@plt>:
   10318:	e28fc600 	add	ip, pc, #0, 12
   1031c:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10320:	e5bcf5b8 	ldr	pc, [ip, #1464]!	; 0x5b8

00010324 <puts@plt>:
   10324:	e28fc600 	add	ip, pc, #0, 12
   10328:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   1032c:	e5bcf5b0 	ldr	pc, [ip, #1456]!	; 0x5b0

00010330 <__libc_start_main@plt>:
   10330:	e28fc600 	add	ip, pc, #0, 12
   10334:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10338:	e5bcf5a8 	ldr	pc, [ip, #1448]!	; 0x5a8

0001033c <__gmon_start__@plt>:
   1033c:	e28fc600 	add	ip, pc, #0, 12
   10340:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10344:	e5bcf5a0 	ldr	pc, [ip, #1440]!	; 0x5a0

00010348 <abort@plt>:
   10348:	e28fc600 	add	ip, pc, #0, 12
   1034c:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10350:	e5bcf598 	ldr	pc, [ip, #1432]!	; 0x598

Disassembly of section .text:

00010358 <_start>:
   10358:	f04f 0b00 	mov.w	fp, #0
   1035c:	f04f 0e00 	mov.w	lr, #0
   10360:	bc02      	pop	{r1}
   10362:	466a      	mov	r2, sp
   10364:	b404      	push	{r2}
   10366:	b401      	push	{r0}
   10368:	f8df c010 	ldr.w	ip, [pc, #16]	; 1037c <_start+0x24>
   1036c:	f84d cd04 	str.w	ip, [sp, #-4]!
   10370:	4803      	ldr	r0, [pc, #12]	; (10380 <_start+0x28>)
   10372:	4b04      	ldr	r3, [pc, #16]	; (10384 <_start+0x2c>)
   10374:	f7ff efdc 	blx	10330 <__libc_start_main@plt>
   10378:	f7ff efe6 	blx	10348 <abort@plt>
   1037c:	0001079d 	.word	0x0001079d
   10380:	0001046d 	.word	0x0001046d
   10384:	0001075d 	.word	0x0001075d

00010388 <call_weak_fn>:
   10388:	e59f3014 	ldr	r3, [pc, #20]	; 103a4 <call_weak_fn+0x1c>
   1038c:	e59f2014 	ldr	r2, [pc, #20]	; 103a8 <call_weak_fn+0x20>
   10390:	e08f3003 	add	r3, pc, r3
   10394:	e7932002 	ldr	r2, [r3, r2]
   10398:	e3520000 	cmp	r2, #0
   1039c:	012fff1e 	bxeq	lr
   103a0:	eaffffe5 	b	1033c <__gmon_start__@plt>
   103a4:	00010530 	.word	0x00010530
   103a8:	00000024 	.word	0x00000024

000103ac <deregister_tm_clones>:
   103ac:	4b07      	ldr	r3, [pc, #28]	; (103cc <deregister_tm_clones+0x20>)
   103ae:	f640 00f8 	movw	r0, #2296	; 0x8f8
   103b2:	f2c0 0002 	movt	r0, #2
   103b6:	1a1b      	subs	r3, r3, r0
   103b8:	2b06      	cmp	r3, #6
   103ba:	d905      	bls.n	103c8 <deregister_tm_clones+0x1c>
   103bc:	f240 0300 	movw	r3, #0
   103c0:	f2c0 0300 	movt	r3, #0
   103c4:	b103      	cbz	r3, 103c8 <deregister_tm_clones+0x1c>
   103c6:	4718      	bx	r3
   103c8:	4770      	bx	lr
   103ca:	bf00      	nop
   103cc:	000208fb 	.word	0x000208fb

000103d0 <register_tm_clones>:
   103d0:	f640 03f8 	movw	r3, #2296	; 0x8f8
   103d4:	f640 00f8 	movw	r0, #2296	; 0x8f8
   103d8:	f2c0 0302 	movt	r3, #2
   103dc:	f2c0 0002 	movt	r0, #2
   103e0:	1a19      	subs	r1, r3, r0
   103e2:	1089      	asrs	r1, r1, #2
   103e4:	eb01 71d1 	add.w	r1, r1, r1, lsr #31
   103e8:	1049      	asrs	r1, r1, #1
   103ea:	d005      	beq.n	103f8 <register_tm_clones+0x28>
   103ec:	f240 0300 	movw	r3, #0
   103f0:	f2c0 0300 	movt	r3, #0
   103f4:	b103      	cbz	r3, 103f8 <register_tm_clones+0x28>
   103f6:	4718      	bx	r3
   103f8:	4770      	bx	lr
   103fa:	bf00      	nop

000103fc <__do_global_dtors_aux>:
   103fc:	b510      	push	{r4, lr}
   103fe:	f640 04f8 	movw	r4, #2296	; 0x8f8
   10402:	f2c0 0402 	movt	r4, #2
   10406:	7823      	ldrb	r3, [r4, #0]
   10408:	b91b      	cbnz	r3, 10412 <__do_global_dtors_aux+0x16>
   1040a:	f7ff ffcf 	bl	103ac <deregister_tm_clones>
   1040e:	2301      	movs	r3, #1
   10410:	7023      	strb	r3, [r4, #0]
   10412:	bd10      	pop	{r4, pc}

00010414 <frame_dummy>:
   10414:	f240 70dc 	movw	r0, #2012	; 0x7dc
   10418:	b508      	push	{r3, lr}
   1041a:	f2c0 0002 	movt	r0, #2
   1041e:	6803      	ldr	r3, [r0, #0]
   10420:	b913      	cbnz	r3, 10428 <frame_dummy+0x14>
   10422:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
   10426:	e7d3      	b.n	103d0 <register_tm_clones>
   10428:	f240 0300 	movw	r3, #0
   1042c:	f2c0 0300 	movt	r3, #0
   10430:	2b00      	cmp	r3, #0
   10432:	d0f6      	beq.n	10422 <frame_dummy+0xe>
   10434:	4798      	blx	r3
   10436:	e7f4      	b.n	10422 <frame_dummy+0xe>

00010438 <gcd>:
   10438:	b580      	push	{r7, lr}
   1043a:	b082      	sub	sp, #8
   1043c:	af00      	add	r7, sp, #0
   1043e:	6078      	str	r0, [r7, #4]
   10440:	6039      	str	r1, [r7, #0]
   10442:	683b      	ldr	r3, [r7, #0]
   10444:	2b01      	cmp	r3, #1
   10446:	dc01      	bgt.n	1044c <gcd+0x14>
   10448:	687b      	ldr	r3, [r7, #4]
   1044a:	e00a      	b.n	10462 <gcd+0x2a>
   1044c:	687b      	ldr	r3, [r7, #4]
   1044e:	4618      	mov	r0, r3
   10450:	6839      	ldr	r1, [r7, #0]
   10452:	f000 f96f 	bl	10734 <__aeabi_idivmod>
   10456:	460b      	mov	r3, r1
   10458:	6838      	ldr	r0, [r7, #0]
   1045a:	4619      	mov	r1, r3
   1045c:	f7ff ffec 	bl	10438 <gcd>
   10460:	4603      	mov	r3, r0
   10462:	4618      	mov	r0, r3
   10464:	3708      	adds	r7, #8
   10466:	46bd      	mov	sp, r7
   10468:	bd80      	pop	{r7, pc}
   1046a:	bf00      	nop

0001046c <main>:
   1046c:	b580      	push	{r7, lr}
   1046e:	b082      	sub	sp, #8
   10470:	af00      	add	r7, sp, #0
   10472:	f240 70ac 	movw	r0, #1964	; 0x7ac
   10476:	f2c0 0001 	movt	r0, #1
   1047a:	f7ff ef54 	blx	10324 <puts@plt>
   1047e:	2020      	movs	r0, #32
   10480:	2118      	movs	r1, #24
   10482:	f7ff ffd9 	bl	10438 <gcd>
   10486:	6078      	str	r0, [r7, #4]
   10488:	f240 70bc 	movw	r0, #1980	; 0x7bc
   1048c:	f2c0 0001 	movt	r0, #1
   10490:	6879      	ldr	r1, [r7, #4]
   10492:	f7ff ef42 	blx	10318 <printf@plt>
   10496:	2300      	movs	r3, #0
   10498:	4618      	mov	r0, r3
   1049a:	3708      	adds	r7, #8
   1049c:	46bd      	mov	sp, r7
   1049e:	bd80      	pop	{r7, pc}

000104a0 <__aeabi_idiv>:
   104a0:	2900      	cmp	r1, #0
   104a2:	f000 813e 	beq.w	10722 <.divsi3_skip_div0_test+0x27c>

000104a6 <.divsi3_skip_div0_test>:
   104a6:	ea80 0c01 	eor.w	ip, r0, r1
   104aa:	bf48      	it	mi
   104ac:	4249      	negmi	r1, r1
   104ae:	1e4a      	subs	r2, r1, #1
   104b0:	f000 811f 	beq.w	106f2 <.divsi3_skip_div0_test+0x24c>
   104b4:	0003      	movs	r3, r0
   104b6:	bf48      	it	mi
   104b8:	4243      	negmi	r3, r0
   104ba:	428b      	cmp	r3, r1
   104bc:	f240 811e 	bls.w	106fc <.divsi3_skip_div0_test+0x256>
   104c0:	4211      	tst	r1, r2
   104c2:	f000 8123 	beq.w	1070c <.divsi3_skip_div0_test+0x266>
   104c6:	fab3 f283 	clz	r2, r3
   104ca:	fab1 f081 	clz	r0, r1
   104ce:	eba0 0202 	sub.w	r2, r0, r2
   104d2:	f1c2 021f 	rsb	r2, r2, #31
   104d6:	a004      	add	r0, pc, #16	; (adr r0, 104e8 <.divsi3_skip_div0_test+0x42>)
   104d8:	eb00 1202 	add.w	r2, r0, r2, lsl #4
   104dc:	f04f 0000 	mov.w	r0, #0
   104e0:	4697      	mov	pc, r2
   104e2:	bf00      	nop
   104e4:	f3af 8000 	nop.w
   104e8:	ebb3 7fc1 	cmp.w	r3, r1, lsl #31
   104ec:	bf00      	nop
   104ee:	eb40 0000 	adc.w	r0, r0, r0
   104f2:	bf28      	it	cs
   104f4:	eba3 73c1 	subcs.w	r3, r3, r1, lsl #31
   104f8:	ebb3 7f81 	cmp.w	r3, r1, lsl #30
   104fc:	bf00      	nop
   104fe:	eb40 0000 	adc.w	r0, r0, r0
   10502:	bf28      	it	cs
   10504:	eba3 7381 	subcs.w	r3, r3, r1, lsl #30
   10508:	ebb3 7f41 	cmp.w	r3, r1, lsl #29
   1050c:	bf00      	nop
   1050e:	eb40 0000 	adc.w	r0, r0, r0
   10512:	bf28      	it	cs
   10514:	eba3 7341 	subcs.w	r3, r3, r1, lsl #29
   10518:	ebb3 7f01 	cmp.w	r3, r1, lsl #28
   1051c:	bf00      	nop
   1051e:	eb40 0000 	adc.w	r0, r0, r0
   10522:	bf28      	it	cs
   10524:	eba3 7301 	subcs.w	r3, r3, r1, lsl #28
   10528:	ebb3 6fc1 	cmp.w	r3, r1, lsl #27
   1052c:	bf00      	nop
   1052e:	eb40 0000 	adc.w	r0, r0, r0
   10532:	bf28      	it	cs
   10534:	eba3 63c1 	subcs.w	r3, r3, r1, lsl #27
   10538:	ebb3 6f81 	cmp.w	r3, r1, lsl #26
   1053c:	bf00      	nop
   1053e:	eb40 0000 	adc.w	r0, r0, r0
   10542:	bf28      	it	cs
   10544:	eba3 6381 	subcs.w	r3, r3, r1, lsl #26
   10548:	ebb3 6f41 	cmp.w	r3, r1, lsl #25
   1054c:	bf00      	nop
   1054e:	eb40 0000 	adc.w	r0, r0, r0
   10552:	bf28      	it	cs
   10554:	eba3 6341 	subcs.w	r3, r3, r1, lsl #25
   10558:	ebb3 6f01 	cmp.w	r3, r1, lsl #24
   1055c:	bf00      	nop
   1055e:	eb40 0000 	adc.w	r0, r0, r0
   10562:	bf28      	it	cs
   10564:	eba3 6301 	subcs.w	r3, r3, r1, lsl #24
   10568:	ebb3 5fc1 	cmp.w	r3, r1, lsl #23
   1056c:	bf00      	nop
   1056e:	eb40 0000 	adc.w	r0, r0, r0
   10572:	bf28      	it	cs
   10574:	eba3 53c1 	subcs.w	r3, r3, r1, lsl #23
   10578:	ebb3 5f81 	cmp.w	r3, r1, lsl #22
   1057c:	bf00      	nop
   1057e:	eb40 0000 	adc.w	r0, r0, r0
   10582:	bf28      	it	cs
   10584:	eba3 5381 	subcs.w	r3, r3, r1, lsl #22
   10588:	ebb3 5f41 	cmp.w	r3, r1, lsl #21
   1058c:	bf00      	nop
   1058e:	eb40 0000 	adc.w	r0, r0, r0
   10592:	bf28      	it	cs
   10594:	eba3 5341 	subcs.w	r3, r3, r1, lsl #21
   10598:	ebb3 5f01 	cmp.w	r3, r1, lsl #20
   1059c:	bf00      	nop
   1059e:	eb40 0000 	adc.w	r0, r0, r0
   105a2:	bf28      	it	cs
   105a4:	eba3 5301 	subcs.w	r3, r3, r1, lsl #20
   105a8:	ebb3 4fc1 	cmp.w	r3, r1, lsl #19
   105ac:	bf00      	nop
   105ae:	eb40 0000 	adc.w	r0, r0, r0
   105b2:	bf28      	it	cs
   105b4:	eba3 43c1 	subcs.w	r3, r3, r1, lsl #19
   105b8:	ebb3 4f81 	cmp.w	r3, r1, lsl #18
   105bc:	bf00      	nop
   105be:	eb40 0000 	adc.w	r0, r0, r0
   105c2:	bf28      	it	cs
   105c4:	eba3 4381 	subcs.w	r3, r3, r1, lsl #18
   105c8:	ebb3 4f41 	cmp.w	r3, r1, lsl #17
   105cc:	bf00      	nop
   105ce:	eb40 0000 	adc.w	r0, r0, r0
   105d2:	bf28      	it	cs
   105d4:	eba3 4341 	subcs.w	r3, r3, r1, lsl #17
   105d8:	ebb3 4f01 	cmp.w	r3, r1, lsl #16
   105dc:	bf00      	nop
   105de:	eb40 0000 	adc.w	r0, r0, r0
   105e2:	bf28      	it	cs
   105e4:	eba3 4301 	subcs.w	r3, r3, r1, lsl #16
   105e8:	ebb3 3fc1 	cmp.w	r3, r1, lsl #15
   105ec:	bf00      	nop
   105ee:	eb40 0000 	adc.w	r0, r0, r0
   105f2:	bf28      	it	cs
   105f4:	eba3 33c1 	subcs.w	r3, r3, r1, lsl #15
   105f8:	ebb3 3f81 	cmp.w	r3, r1, lsl #14
   105fc:	bf00      	nop
   105fe:	eb40 0000 	adc.w	r0, r0, r0
   10602:	bf28      	it	cs
   10604:	eba3 3381 	subcs.w	r3, r3, r1, lsl #14
   10608:	ebb3 3f41 	cmp.w	r3, r1, lsl #13
   1060c:	bf00      	nop
   1060e:	eb40 0000 	adc.w	r0, r0, r0
   10612:	bf28      	it	cs
   10614:	eba3 3341 	subcs.w	r3, r3, r1, lsl #13
   10618:	ebb3 3f01 	cmp.w	r3, r1, lsl #12
   1061c:	bf00      	nop
   1061e:	eb40 0000 	adc.w	r0, r0, r0
   10622:	bf28      	it	cs
   10624:	eba3 3301 	subcs.w	r3, r3, r1, lsl #12
   10628:	ebb3 2fc1 	cmp.w	r3, r1, lsl #11
   1062c:	bf00      	nop
   1062e:	eb40 0000 	adc.w	r0, r0, r0
   10632:	bf28      	it	cs
   10634:	eba3 23c1 	subcs.w	r3, r3, r1, lsl #11
   10638:	ebb3 2f81 	cmp.w	r3, r1, lsl #10
   1063c:	bf00      	nop
   1063e:	eb40 0000 	adc.w	r0, r0, r0
   10642:	bf28      	it	cs
   10644:	eba3 2381 	subcs.w	r3, r3, r1, lsl #10
   10648:	ebb3 2f41 	cmp.w	r3, r1, lsl #9
   1064c:	bf00      	nop
   1064e:	eb40 0000 	adc.w	r0, r0, r0
   10652:	bf28      	it	cs
   10654:	eba3 2341 	subcs.w	r3, r3, r1, lsl #9
   10658:	ebb3 2f01 	cmp.w	r3, r1, lsl #8
   1065c:	bf00      	nop
   1065e:	eb40 0000 	adc.w	r0, r0, r0
   10662:	bf28      	it	cs
   10664:	eba3 2301 	subcs.w	r3, r3, r1, lsl #8
   10668:	ebb3 1fc1 	cmp.w	r3, r1, lsl #7
   1066c:	bf00      	nop
   1066e:	eb40 0000 	adc.w	r0, r0, r0
   10672:	bf28      	it	cs
   10674:	eba3 13c1 	subcs.w	r3, r3, r1, lsl #7
   10678:	ebb3 1f81 	cmp.w	r3, r1, lsl #6
   1067c:	bf00      	nop
   1067e:	eb40 0000 	adc.w	r0, r0, r0
   10682:	bf28      	it	cs
   10684:	eba3 1381 	subcs.w	r3, r3, r1, lsl #6
   10688:	ebb3 1f41 	cmp.w	r3, r1, lsl #5
   1068c:	bf00      	nop
   1068e:	eb40 0000 	adc.w	r0, r0, r0
   10692:	bf28      	it	cs
   10694:	eba3 1341 	subcs.w	r3, r3, r1, lsl #5
   10698:	ebb3 1f01 	cmp.w	r3, r1, lsl #4
   1069c:	bf00      	nop
   1069e:	eb40 0000 	adc.w	r0, r0, r0
   106a2:	bf28      	it	cs
   106a4:	eba3 1301 	subcs.w	r3, r3, r1, lsl #4
   106a8:	ebb3 0fc1 	cmp.w	r3, r1, lsl #3
   106ac:	bf00      	nop
   106ae:	eb40 0000 	adc.w	r0, r0, r0
   106b2:	bf28      	it	cs
   106b4:	eba3 03c1 	subcs.w	r3, r3, r1, lsl #3
   106b8:	ebb3 0f81 	cmp.w	r3, r1, lsl #2
   106bc:	bf00      	nop
   106be:	eb40 0000 	adc.w	r0, r0, r0
   106c2:	bf28      	it	cs
   106c4:	eba3 0381 	subcs.w	r3, r3, r1, lsl #2
   106c8:	ebb3 0f41 	cmp.w	r3, r1, lsl #1
   106cc:	bf00      	nop
   106ce:	eb40 0000 	adc.w	r0, r0, r0
   106d2:	bf28      	it	cs
   106d4:	eba3 0341 	subcs.w	r3, r3, r1, lsl #1
   106d8:	ebb3 0f01 	cmp.w	r3, r1
   106dc:	bf00      	nop
   106de:	eb40 0000 	adc.w	r0, r0, r0
   106e2:	bf28      	it	cs
   106e4:	eba3 0301 	subcs.w	r3, r3, r1
   106e8:	f1bc 0f00 	cmp.w	ip, #0
   106ec:	bf48      	it	mi
   106ee:	4240      	negmi	r0, r0
   106f0:	4770      	bx	lr
   106f2:	ea9c 0f00 	teq	ip, r0
   106f6:	bf48      	it	mi
   106f8:	4240      	negmi	r0, r0
   106fa:	4770      	bx	lr
   106fc:	bf38      	it	cc
   106fe:	2000      	movcc	r0, #0
   10700:	bf04      	itt	eq
   10702:	ea4f 70ec 	moveq.w	r0, ip, asr #31
   10706:	f040 0001 	orreq.w	r0, r0, #1
   1070a:	4770      	bx	lr
   1070c:	fab1 f281 	clz	r2, r1
   10710:	f1c2 021f 	rsb	r2, r2, #31
   10714:	f1bc 0f00 	cmp.w	ip, #0
   10718:	fa23 f002 	lsr.w	r0, r3, r2
   1071c:	bf48      	it	mi
   1071e:	4240      	negmi	r0, r0
   10720:	4770      	bx	lr
   10722:	2800      	cmp	r0, #0
   10724:	bfc8      	it	gt
   10726:	f06f 4000 	mvngt.w	r0, #2147483648	; 0x80000000
   1072a:	bfb8      	it	lt
   1072c:	f04f 4000 	movlt.w	r0, #2147483648	; 0x80000000
   10730:	f000 b80e 	b.w	10750 <__aeabi_idiv0>

00010734 <__aeabi_idivmod>:
   10734:	2900      	cmp	r1, #0
   10736:	d0f4      	beq.n	10722 <.divsi3_skip_div0_test+0x27c>
   10738:	e92d 4003 	stmdb	sp!, {r0, r1, lr}
   1073c:	f7ff feb3 	bl	104a6 <.divsi3_skip_div0_test>
   10740:	e8bd 4006 	ldmia.w	sp!, {r1, r2, lr}
   10744:	fb02 f300 	mul.w	r3, r2, r0
   10748:	eba1 0103 	sub.w	r1, r1, r3
   1074c:	4770      	bx	lr
   1074e:	bf00      	nop

00010750 <__aeabi_idiv0>:
   10750:	b502      	push	{r1, lr}
   10752:	f04f 0008 	mov.w	r0, #8
   10756:	f7ff edda 	blx	1030c <raise@plt>
   1075a:	bd02      	pop	{r1, pc}

0001075c <__libc_csu_init>:
   1075c:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
   10760:	4607      	mov	r7, r0
   10762:	4e0c      	ldr	r6, [pc, #48]	; (10794 <__libc_csu_init+0x38>)
   10764:	4688      	mov	r8, r1
   10766:	4d0c      	ldr	r5, [pc, #48]	; (10798 <__libc_csu_init+0x3c>)
   10768:	4691      	mov	r9, r2
   1076a:	447e      	add	r6, pc
   1076c:	f7ff edbe 	blx	102ec <_init>
   10770:	447d      	add	r5, pc
   10772:	1b76      	subs	r6, r6, r5
   10774:	10b6      	asrs	r6, r6, #2
   10776:	d00a      	beq.n	1078e <__libc_csu_init+0x32>
   10778:	3d04      	subs	r5, #4
   1077a:	2400      	movs	r4, #0
   1077c:	3401      	adds	r4, #1
   1077e:	f855 3f04 	ldr.w	r3, [r5, #4]!
   10782:	4638      	mov	r0, r7
   10784:	4641      	mov	r1, r8
   10786:	464a      	mov	r2, r9
   10788:	4798      	blx	r3
   1078a:	42b4      	cmp	r4, r6
   1078c:	d1f6      	bne.n	1077c <__libc_csu_init+0x20>
   1078e:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
   10792:	bf00      	nop
   10794:	0001006a 	.word	0x0001006a
   10798:	00010060 	.word	0x00010060

0001079c <__libc_csu_fini>:
   1079c:	4770      	bx	lr
   1079e:	bf00      	nop

Disassembly of section .fini:

000107a0 <_fini>:
   107a0:	e92d4008 	push	{r3, lr}
   107a4:	e8bd8008 	pop	{r3, pc}
```

#### objdump -x
```
gcd.out:     file format elf32-littlearm
gcd.out
architecture: arm, flags 0x00000112:
EXEC_P, HAS_SYMS, D_PAGED
start address 0x00010359

Program Header:
0x70000001 off    0x000007c8 vaddr 0x000107c8 paddr 0x000107c8 align 2**2
         filesz 0x00000008 memsz 0x00000008 flags r--
    PHDR off    0x00000034 vaddr 0x00010034 paddr 0x00010034 align 2**2
         filesz 0x00000100 memsz 0x00000100 flags r-x
  INTERP off    0x00000134 vaddr 0x00010134 paddr 0x00010134 align 2**0
         filesz 0x00000019 memsz 0x00000019 flags r--
    LOAD off    0x00000000 vaddr 0x00010000 paddr 0x00010000 align 2**16
         filesz 0x000007d4 memsz 0x000007d4 flags r-x
    LOAD off    0x000007d4 vaddr 0x000207d4 paddr 0x000207d4 align 2**16
         filesz 0x00000124 memsz 0x00000128 flags rw-
 DYNAMIC off    0x000007e0 vaddr 0x000207e0 paddr 0x000207e0 align 2**2
         filesz 0x000000e8 memsz 0x000000e8 flags rw-
    NOTE off    0x00000150 vaddr 0x00010150 paddr 0x00010150 align 2**2
         filesz 0x00000044 memsz 0x00000044 flags r--
   STACK off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**4
         filesz 0x00000000 memsz 0x00000000 flags rw-

Dynamic Section:
  NEEDED               libc.so.6
  INIT                 0x000102ec
  FINI                 0x000107a0
  INIT_ARRAY           0x000207d4
  INIT_ARRAYSZ         0x00000004
  FINI_ARRAY           0x000207d8
  FINI_ARRAYSZ         0x00000004
  GNU_HASH             0x00010194
  STRTAB               0x00010238
  SYMTAB               0x000101c8
  STRSZ                0x0000004e
  SYMENT               0x00000010
  DEBUG                0x00000000
  PLTGOT               0x000208c8
  PLTRELSZ             0x00000030
  PLTREL               0x00000011
  JMPREL               0x000102bc
  REL                  0x000102b4
  RELSZ                0x00000008
  RELENT               0x00000008
  VERNEED              0x00010294
  VERNEEDNUM           0x00000001
  VERSYM               0x00010286

Version References:
  required from libc.so.6:
    0x0d696914 0x00 02 GLIBC_2.4
private flags = 5000402: [Version5 EABI] [hard-float ABI] [has entry point]

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .interp       00000019  00010134  00010134  00000134  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.ABI-tag 00000020  00010150  00010150  00000150  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .note.gnu.build-id 00000024  00010170  00010170  00000170  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .gnu.hash     00000034  00010194  00010194  00000194  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .dynsym       00000070  000101c8  000101c8  000001c8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .dynstr       0000004e  00010238  00010238  00000238  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .gnu.version  0000000e  00010286  00010286  00000286  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .gnu.version_r 00000020  00010294  00010294  00000294  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .rel.dyn      00000008  000102b4  000102b4  000002b4  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .rel.plt      00000030  000102bc  000102bc  000002bc  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 10 .init         0000000c  000102ec  000102ec  000002ec  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 11 .plt          0000005c  000102f8  000102f8  000002f8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .text         00000448  00010358  00010358  00000358  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .fini         00000008  000107a0  000107a0  000007a0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .rodata       00000020  000107a8  000107a8  000007a8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 15 .ARM.exidx    00000008  000107c8  000107c8  000007c8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 16 .eh_frame     00000004  000107d0  000107d0  000007d0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 17 .init_array   00000004  000207d4  000207d4  000007d4  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 18 .fini_array   00000004  000207d8  000207d8  000007d8  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 19 .jcr          00000004  000207dc  000207dc  000007dc  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 20 .dynamic      000000e8  000207e0  000207e0  000007e0  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 21 .got          00000028  000208c8  000208c8  000008c8  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 22 .data         00000008  000208f0  000208f0  000008f0  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 23 .bss          00000004  000208f8  000208f8  000008f8  2**0
                  ALLOC
 24 .comment      00000039  00000000  00000000  000008f8  2**0
                  CONTENTS, READONLY
 25 .ARM.attributes 00000035  00000000  00000000  00000931  2**0
                  CONTENTS, READONLY
 26 .debug_aranges 00000020  00000000  00000000  00000966  2**0
                  CONTENTS, READONLY, DEBUGGING
 27 .debug_info   000000d4  00000000  00000000  00000986  2**0
                  CONTENTS, READONLY, DEBUGGING
 28 .debug_abbrev 0000007e  00000000  00000000  00000a5a  2**0
                  CONTENTS, READONLY, DEBUGGING
 29 .debug_line   00000043  00000000  00000000  00000ad8  2**0
                  CONTENTS, READONLY, DEBUGGING
 30 .debug_frame  00000058  00000000  00000000  00000b1c  2**2
                  CONTENTS, READONLY, DEBUGGING
 31 .debug_str    000000c3  00000000  00000000  00000b74  2**0
                  CONTENTS, READONLY, DEBUGGING
SYMBOL TABLE:
00010134 l    d  .interp	00000000              .interp
00010150 l    d  .note.ABI-tag	00000000              .note.ABI-tag
00010170 l    d  .note.gnu.build-id	00000000              .note.gnu.build-id
00010194 l    d  .gnu.hash	00000000              .gnu.hash
000101c8 l    d  .dynsym	00000000              .dynsym
00010238 l    d  .dynstr	00000000              .dynstr
00010286 l    d  .gnu.version	00000000              .gnu.version
00010294 l    d  .gnu.version_r	00000000              .gnu.version_r
000102b4 l    d  .rel.dyn	00000000              .rel.dyn
000102bc l    d  .rel.plt	00000000              .rel.plt
000102ec l    d  .init	00000000              .init
000102f8 l    d  .plt	00000000              .plt
00010358 l    d  .text	00000000              .text
000107a0 l    d  .fini	00000000              .fini
000107a8 l    d  .rodata	00000000              .rodata
000107c8 l    d  .ARM.exidx	00000000              .ARM.exidx
000107d0 l    d  .eh_frame	00000000              .eh_frame
000207d4 l    d  .init_array	00000000              .init_array
000207d8 l    d  .fini_array	00000000              .fini_array
000207dc l    d  .jcr	00000000              .jcr
000207e0 l    d  .dynamic	00000000              .dynamic
000208c8 l    d  .got	00000000              .got
000208f0 l    d  .data	00000000              .data
000208f8 l    d  .bss	00000000              .bss
00000000 l    d  .comment	00000000              .comment
00000000 l    d  .ARM.attributes	00000000              .ARM.attributes
00000000 l    d  .debug_aranges	00000000              .debug_aranges
00000000 l    d  .debug_info	00000000              .debug_info
00000000 l    d  .debug_abbrev	00000000              .debug_abbrev
00000000 l    d  .debug_line	00000000              .debug_line
00000000 l    d  .debug_frame	00000000              .debug_frame
00000000 l    d  .debug_str	00000000              .debug_str
00000000 l    df *ABS*	00000000              /usr/lib/gcc/arm-linux-gnueabihf/4.9/../../../arm-linux-gnueabihf/crt1.o
00000000 l    df *ABS*	00000000              /usr/lib/gcc/arm-linux-gnueabihf/4.9/../../../arm-linux-gnueabihf/crti.o
00010388 l     F .text	00000000              call_weak_fn
00000000 l    df *ABS*	00000000              /usr/lib/gcc/arm-linux-gnueabihf/4.9/../../../arm-linux-gnueabihf/crtn.o
00000000 l    df *ABS*	00000000              crtstuff.c
000207dc l     O .jcr	00000000              __JCR_LIST__
000103ac l     F .text	00000000              deregister_tm_clones
000103d0 l     F .text	00000000              register_tm_clones
000103fc l     F .text	00000000              __do_global_dtors_aux
000208f8 l     O .bss	00000001              completed.9004
000207d8 l     O .fini_array	00000000              __do_global_dtors_aux_fini_array_entry
00010414 l     F .text	00000000              frame_dummy
000207d4 l     O .init_array	00000000              __frame_dummy_init_array_entry
00000000 l    df *ABS*	00000000              gcd.c
00000000 l    df *ABS*	00000000              _divsi3.o
000104a6 l       .text	00000000              .divsi3_skip_div0_test
00000000 l       *ABS*	00000000              shift
00000000 l    df *ABS*	00000000              _dvmd_lnx.o
00000000 l    df *ABS*	00000000              elf-init.oS
00000000 l    df *ABS*	00000000              crtstuff.c
000107d0 l     O .eh_frame	00000000              __FRAME_END__
000207dc l     O .jcr	00000000              __JCR_END__
00000000 l    df *ABS*	00000000              
000207d8 l       .init_array	00000000              __init_array_end
000207e0 l     O .dynamic	00000000              _DYNAMIC
000207d4 l       .init_array	00000000              __init_array_start
000208c8 l     O .got	00000000              _GLOBAL_OFFSET_TABLE_
0001079c g     F .text	00000002              __libc_csu_fini
00000000       F *UND*	00000000              raise@@GLIBC_2.4
00000000  w      *UND*	00000000              _ITM_deregisterTMCloneTable
000208f0  w      .data	00000000              data_start
00000000       F *UND*	00000000              printf@@GLIBC_2.4
000208f8 g       .bss	00000000              __bss_start__
000208fc g       .bss	00000000              _bss_end__
000208f8 g       .data	00000000              _edata
000107a0 g     F .fini	00000000              _fini
000208fc g       .bss	00000000              __bss_end__
00010734 g     F .text	0000001a              .hidden __aeabi_idivmod
00010750  w    F .text	0000000c              .hidden __aeabi_ldiv0
000208f0 g       .data	00000000              __data_start
00000000       F *UND*	00000000              puts@@GLIBC_2.4
00000000       F *UND*	00000000              __libc_start_main@@GLIBC_2.4
00000000  w      *UND*	00000000              __gmon_start__
000208f4 g     O .data	00000000              .hidden __dso_handle
000107a8 g     O .rodata	00000004              _IO_stdin_used
000104a0 g     F .text	00000294              .hidden __divsi3
0001075c g     F .text	00000040              __libc_csu_init
000208fc g       .bss	00000000              _end
00010358 g     F .text	00000000              _start
000208fc g       .bss	00000000              __end__
00010750  w    F .text	0000000c              .hidden __aeabi_idiv0
000208f8 g       .bss	00000000              __bss_start
0001046c g     F .text	00000034              main
00010438 g     F .text	00000032              gcd
00000000  w      *UND*	00000000              _Jv_RegisterClasses
000208f8 g     O .data	00000000              .hidden __TMC_END__
000104a0 g     F .text	00000000              .hidden __aeabi_idiv
00000000  w      *UND*	00000000              _ITM_registerTMCloneTable
00000000       F *UND*	00000000              abort@@GLIBC_2.4
000102ec g     F .init	00000000              _init
```

#### objdump -S --disassemble gcd.out > gcd.dump
```
gcd.out:     file format elf32-littlearm


Disassembly of section .init:

000102ec <_init>:
   102ec:	e92d4008 	push	{r3, lr}
   102f0:	eb000024 	bl	10388 <call_weak_fn>
   102f4:	e8bd8008 	pop	{r3, pc}

Disassembly of section .plt:

000102f8 <raise@plt-0x14>:
   102f8:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
   102fc:	e59fe004 	ldr	lr, [pc, #4]	; 10308 <_init+0x1c>
   10300:	e08fe00e 	add	lr, pc, lr
   10304:	e5bef008 	ldr	pc, [lr, #8]!
   10308:	000105c0 	.word	0x000105c0

0001030c <raise@plt>:
   1030c:	e28fc600 	add	ip, pc, #0, 12
   10310:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10314:	e5bcf5c0 	ldr	pc, [ip, #1472]!	; 0x5c0

00010318 <printf@plt>:
   10318:	e28fc600 	add	ip, pc, #0, 12
   1031c:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10320:	e5bcf5b8 	ldr	pc, [ip, #1464]!	; 0x5b8

00010324 <puts@plt>:
   10324:	e28fc600 	add	ip, pc, #0, 12
   10328:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   1032c:	e5bcf5b0 	ldr	pc, [ip, #1456]!	; 0x5b0

00010330 <__libc_start_main@plt>:
   10330:	e28fc600 	add	ip, pc, #0, 12
   10334:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10338:	e5bcf5a8 	ldr	pc, [ip, #1448]!	; 0x5a8

0001033c <__gmon_start__@plt>:
   1033c:	e28fc600 	add	ip, pc, #0, 12
   10340:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10344:	e5bcf5a0 	ldr	pc, [ip, #1440]!	; 0x5a0

00010348 <abort@plt>:
   10348:	e28fc600 	add	ip, pc, #0, 12
   1034c:	e28cca10 	add	ip, ip, #16, 20	; 0x10000
   10350:	e5bcf598 	ldr	pc, [ip, #1432]!	; 0x598

Disassembly of section .text:

00010358 <_start>:
   10358:	f04f 0b00 	mov.w	fp, #0
   1035c:	f04f 0e00 	mov.w	lr, #0
   10360:	bc02      	pop	{r1}
   10362:	466a      	mov	r2, sp
   10364:	b404      	push	{r2}
   10366:	b401      	push	{r0}
   10368:	f8df c010 	ldr.w	ip, [pc, #16]	; 1037c <_start+0x24>
   1036c:	f84d cd04 	str.w	ip, [sp, #-4]!
   10370:	4803      	ldr	r0, [pc, #12]	; (10380 <_start+0x28>)
   10372:	4b04      	ldr	r3, [pc, #16]	; (10384 <_start+0x2c>)
   10374:	f7ff efdc 	blx	10330 <__libc_start_main@plt>
   10378:	f7ff efe6 	blx	10348 <abort@plt>
   1037c:	0001079d 	.word	0x0001079d
   10380:	0001046d 	.word	0x0001046d
   10384:	0001075d 	.word	0x0001075d

00010388 <call_weak_fn>:
   10388:	e59f3014 	ldr	r3, [pc, #20]	; 103a4 <call_weak_fn+0x1c>
   1038c:	e59f2014 	ldr	r2, [pc, #20]	; 103a8 <call_weak_fn+0x20>
   10390:	e08f3003 	add	r3, pc, r3
   10394:	e7932002 	ldr	r2, [r3, r2]
   10398:	e3520000 	cmp	r2, #0
   1039c:	012fff1e 	bxeq	lr
   103a0:	eaffffe5 	b	1033c <__gmon_start__@plt>
   103a4:	00010530 	.word	0x00010530
   103a8:	00000024 	.word	0x00000024

000103ac <deregister_tm_clones>:
   103ac:	4b07      	ldr	r3, [pc, #28]	; (103cc <deregister_tm_clones+0x20>)
   103ae:	f640 00f8 	movw	r0, #2296	; 0x8f8
   103b2:	f2c0 0002 	movt	r0, #2
   103b6:	1a1b      	subs	r3, r3, r0
   103b8:	2b06      	cmp	r3, #6
   103ba:	d905      	bls.n	103c8 <deregister_tm_clones+0x1c>
   103bc:	f240 0300 	movw	r3, #0
   103c0:	f2c0 0300 	movt	r3, #0
   103c4:	b103      	cbz	r3, 103c8 <deregister_tm_clones+0x1c>
   103c6:	4718      	bx	r3
   103c8:	4770      	bx	lr
   103ca:	bf00      	nop
   103cc:	000208fb 	.word	0x000208fb

000103d0 <register_tm_clones>:
   103d0:	f640 03f8 	movw	r3, #2296	; 0x8f8
   103d4:	f640 00f8 	movw	r0, #2296	; 0x8f8
   103d8:	f2c0 0302 	movt	r3, #2
   103dc:	f2c0 0002 	movt	r0, #2
   103e0:	1a19      	subs	r1, r3, r0
   103e2:	1089      	asrs	r1, r1, #2
   103e4:	eb01 71d1 	add.w	r1, r1, r1, lsr #31
   103e8:	1049      	asrs	r1, r1, #1
   103ea:	d005      	beq.n	103f8 <register_tm_clones+0x28>
   103ec:	f240 0300 	movw	r3, #0
   103f0:	f2c0 0300 	movt	r3, #0
   103f4:	b103      	cbz	r3, 103f8 <register_tm_clones+0x28>
   103f6:	4718      	bx	r3
   103f8:	4770      	bx	lr
   103fa:	bf00      	nop

000103fc <__do_global_dtors_aux>:
   103fc:	b510      	push	{r4, lr}
   103fe:	f640 04f8 	movw	r4, #2296	; 0x8f8
   10402:	f2c0 0402 	movt	r4, #2
   10406:	7823      	ldrb	r3, [r4, #0]
   10408:	b91b      	cbnz	r3, 10412 <__do_global_dtors_aux+0x16>
   1040a:	f7ff ffcf 	bl	103ac <deregister_tm_clones>
   1040e:	2301      	movs	r3, #1
   10410:	7023      	strb	r3, [r4, #0]
   10412:	bd10      	pop	{r4, pc}

00010414 <frame_dummy>:
   10414:	f240 70dc 	movw	r0, #2012	; 0x7dc
   10418:	b508      	push	{r3, lr}
   1041a:	f2c0 0002 	movt	r0, #2
   1041e:	6803      	ldr	r3, [r0, #0]
   10420:	b913      	cbnz	r3, 10428 <frame_dummy+0x14>
   10422:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
   10426:	e7d3      	b.n	103d0 <register_tm_clones>
   10428:	f240 0300 	movw	r3, #0
   1042c:	f2c0 0300 	movt	r3, #0
   10430:	2b00      	cmp	r3, #0
   10432:	d0f6      	beq.n	10422 <frame_dummy+0xe>
   10434:	4798      	blx	r3
   10436:	e7f4      	b.n	10422 <frame_dummy+0xe>

00010438 <gcd>:
#include <stdio.h>
 
int gcd(int lhs, int rhs){
   10438:	b580      	push	{r7, lr}
   1043a:	b082      	sub	sp, #8
   1043c:	af00      	add	r7, sp, #0
   1043e:	6078      	str	r0, [r7, #4]
   10440:	6039      	str	r1, [r7, #0]
	if(rhs <= 1)return lhs;
   10442:	683b      	ldr	r3, [r7, #0]
   10444:	2b01      	cmp	r3, #1
   10446:	dc01      	bgt.n	1044c <gcd+0x14>
   10448:	687b      	ldr	r3, [r7, #4]
   1044a:	e00a      	b.n	10462 <gcd+0x2a>
	return gcd(rhs, lhs%rhs);
   1044c:	687b      	ldr	r3, [r7, #4]
   1044e:	4618      	mov	r0, r3
   10450:	6839      	ldr	r1, [r7, #0]
   10452:	f000 f96f 	bl	10734 <__aeabi_idivmod>
   10456:	460b      	mov	r3, r1
   10458:	6838      	ldr	r0, [r7, #0]
   1045a:	4619      	mov	r1, r3
   1045c:	f7ff ffec 	bl	10438 <gcd>
   10460:	4603      	mov	r3, r0
}
   10462:	4618      	mov	r0, r3
   10464:	3708      	adds	r7, #8
   10466:	46bd      	mov	sp, r7
   10468:	bd80      	pop	{r7, pc}
   1046a:	bf00      	nop

0001046c <main>:
 
int main(void) {
   1046c:	b580      	push	{r7, lr}
   1046e:	b082      	sub	sp, #8
   10470:	af00      	add	r7, sp, #0
	// your code goes here
	printf("hello world!\n");
   10472:	f240 70ac 	movw	r0, #1964	; 0x7ac
   10476:	f2c0 0001 	movt	r0, #1
   1047a:	f7ff ef54 	blx	10324 <puts@plt>
	int val = gcd(32, 24);
   1047e:	2020      	movs	r0, #32
   10480:	2118      	movs	r1, #24
   10482:	f7ff ffd9 	bl	10438 <gcd>
   10486:	6078      	str	r0, [r7, #4]
	printf("gcd = %d\n", val);
   10488:	f240 70bc 	movw	r0, #1980	; 0x7bc
   1048c:	f2c0 0001 	movt	r0, #1
   10490:	6879      	ldr	r1, [r7, #4]
   10492:	f7ff ef42 	blx	10318 <printf@plt>
	return 0;
   10496:	2300      	movs	r3, #0
   10498:	4618      	mov	r0, r3
   1049a:	3708      	adds	r7, #8
   1049c:	46bd      	mov	sp, r7
   1049e:	bd80      	pop	{r7, pc}

000104a0 <__aeabi_idiv>:
   104a0:	2900      	cmp	r1, #0
   104a2:	f000 813e 	beq.w	10722 <.divsi3_skip_div0_test+0x27c>

000104a6 <.divsi3_skip_div0_test>:
   104a6:	ea80 0c01 	eor.w	ip, r0, r1
   104aa:	bf48      	it	mi
   104ac:	4249      	negmi	r1, r1
   104ae:	1e4a      	subs	r2, r1, #1
   104b0:	f000 811f 	beq.w	106f2 <.divsi3_skip_div0_test+0x24c>
   104b4:	0003      	movs	r3, r0
   104b6:	bf48      	it	mi
   104b8:	4243      	negmi	r3, r0
   104ba:	428b      	cmp	r3, r1
   104bc:	f240 811e 	bls.w	106fc <.divsi3_skip_div0_test+0x256>
   104c0:	4211      	tst	r1, r2
   104c2:	f000 8123 	beq.w	1070c <.divsi3_skip_div0_test+0x266>
   104c6:	fab3 f283 	clz	r2, r3
   104ca:	fab1 f081 	clz	r0, r1
   104ce:	eba0 0202 	sub.w	r2, r0, r2
   104d2:	f1c2 021f 	rsb	r2, r2, #31
   104d6:	a004      	add	r0, pc, #16	; (adr r0, 104e8 <.divsi3_skip_div0_test+0x42>)
   104d8:	eb00 1202 	add.w	r2, r0, r2, lsl #4
   104dc:	f04f 0000 	mov.w	r0, #0
   104e0:	4697      	mov	pc, r2
   104e2:	bf00      	nop
   104e4:	f3af 8000 	nop.w
   104e8:	ebb3 7fc1 	cmp.w	r3, r1, lsl #31
   104ec:	bf00      	nop
   104ee:	eb40 0000 	adc.w	r0, r0, r0
   104f2:	bf28      	it	cs
   104f4:	eba3 73c1 	subcs.w	r3, r3, r1, lsl #31
   104f8:	ebb3 7f81 	cmp.w	r3, r1, lsl #30
   104fc:	bf00      	nop
   104fe:	eb40 0000 	adc.w	r0, r0, r0
   10502:	bf28      	it	cs
   10504:	eba3 7381 	subcs.w	r3, r3, r1, lsl #30
   10508:	ebb3 7f41 	cmp.w	r3, r1, lsl #29
   1050c:	bf00      	nop
   1050e:	eb40 0000 	adc.w	r0, r0, r0
   10512:	bf28      	it	cs
   10514:	eba3 7341 	subcs.w	r3, r3, r1, lsl #29
   10518:	ebb3 7f01 	cmp.w	r3, r1, lsl #28
   1051c:	bf00      	nop
   1051e:	eb40 0000 	adc.w	r0, r0, r0
   10522:	bf28      	it	cs
   10524:	eba3 7301 	subcs.w	r3, r3, r1, lsl #28
   10528:	ebb3 6fc1 	cmp.w	r3, r1, lsl #27
   1052c:	bf00      	nop
   1052e:	eb40 0000 	adc.w	r0, r0, r0
   10532:	bf28      	it	cs
   10534:	eba3 63c1 	subcs.w	r3, r3, r1, lsl #27
   10538:	ebb3 6f81 	cmp.w	r3, r1, lsl #26
   1053c:	bf00      	nop
   1053e:	eb40 0000 	adc.w	r0, r0, r0
   10542:	bf28      	it	cs
   10544:	eba3 6381 	subcs.w	r3, r3, r1, lsl #26
   10548:	ebb3 6f41 	cmp.w	r3, r1, lsl #25
   1054c:	bf00      	nop
   1054e:	eb40 0000 	adc.w	r0, r0, r0
   10552:	bf28      	it	cs
   10554:	eba3 6341 	subcs.w	r3, r3, r1, lsl #25
   10558:	ebb3 6f01 	cmp.w	r3, r1, lsl #24
   1055c:	bf00      	nop
   1055e:	eb40 0000 	adc.w	r0, r0, r0
   10562:	bf28      	it	cs
   10564:	eba3 6301 	subcs.w	r3, r3, r1, lsl #24
   10568:	ebb3 5fc1 	cmp.w	r3, r1, lsl #23
   1056c:	bf00      	nop
   1056e:	eb40 0000 	adc.w	r0, r0, r0
   10572:	bf28      	it	cs
   10574:	eba3 53c1 	subcs.w	r3, r3, r1, lsl #23
   10578:	ebb3 5f81 	cmp.w	r3, r1, lsl #22
   1057c:	bf00      	nop
   1057e:	eb40 0000 	adc.w	r0, r0, r0
   10582:	bf28      	it	cs
   10584:	eba3 5381 	subcs.w	r3, r3, r1, lsl #22
   10588:	ebb3 5f41 	cmp.w	r3, r1, lsl #21
   1058c:	bf00      	nop
   1058e:	eb40 0000 	adc.w	r0, r0, r0
   10592:	bf28      	it	cs
   10594:	eba3 5341 	subcs.w	r3, r3, r1, lsl #21
   10598:	ebb3 5f01 	cmp.w	r3, r1, lsl #20
   1059c:	bf00      	nop
   1059e:	eb40 0000 	adc.w	r0, r0, r0
   105a2:	bf28      	it	cs
   105a4:	eba3 5301 	subcs.w	r3, r3, r1, lsl #20
   105a8:	ebb3 4fc1 	cmp.w	r3, r1, lsl #19
   105ac:	bf00      	nop
   105ae:	eb40 0000 	adc.w	r0, r0, r0
   105b2:	bf28      	it	cs
   105b4:	eba3 43c1 	subcs.w	r3, r3, r1, lsl #19
   105b8:	ebb3 4f81 	cmp.w	r3, r1, lsl #18
   105bc:	bf00      	nop
   105be:	eb40 0000 	adc.w	r0, r0, r0
   105c2:	bf28      	it	cs
   105c4:	eba3 4381 	subcs.w	r3, r3, r1, lsl #18
   105c8:	ebb3 4f41 	cmp.w	r3, r1, lsl #17
   105cc:	bf00      	nop
   105ce:	eb40 0000 	adc.w	r0, r0, r0
   105d2:	bf28      	it	cs
   105d4:	eba3 4341 	subcs.w	r3, r3, r1, lsl #17
   105d8:	ebb3 4f01 	cmp.w	r3, r1, lsl #16
   105dc:	bf00      	nop
   105de:	eb40 0000 	adc.w	r0, r0, r0
   105e2:	bf28      	it	cs
   105e4:	eba3 4301 	subcs.w	r3, r3, r1, lsl #16
   105e8:	ebb3 3fc1 	cmp.w	r3, r1, lsl #15
   105ec:	bf00      	nop
   105ee:	eb40 0000 	adc.w	r0, r0, r0
   105f2:	bf28      	it	cs
   105f4:	eba3 33c1 	subcs.w	r3, r3, r1, lsl #15
   105f8:	ebb3 3f81 	cmp.w	r3, r1, lsl #14
   105fc:	bf00      	nop
   105fe:	eb40 0000 	adc.w	r0, r0, r0
   10602:	bf28      	it	cs
   10604:	eba3 3381 	subcs.w	r3, r3, r1, lsl #14
   10608:	ebb3 3f41 	cmp.w	r3, r1, lsl #13
   1060c:	bf00      	nop
   1060e:	eb40 0000 	adc.w	r0, r0, r0
   10612:	bf28      	it	cs
   10614:	eba3 3341 	subcs.w	r3, r3, r1, lsl #13
   10618:	ebb3 3f01 	cmp.w	r3, r1, lsl #12
   1061c:	bf00      	nop
   1061e:	eb40 0000 	adc.w	r0, r0, r0
   10622:	bf28      	it	cs
   10624:	eba3 3301 	subcs.w	r3, r3, r1, lsl #12
   10628:	ebb3 2fc1 	cmp.w	r3, r1, lsl #11
   1062c:	bf00      	nop
   1062e:	eb40 0000 	adc.w	r0, r0, r0
   10632:	bf28      	it	cs
   10634:	eba3 23c1 	subcs.w	r3, r3, r1, lsl #11
   10638:	ebb3 2f81 	cmp.w	r3, r1, lsl #10
   1063c:	bf00      	nop
   1063e:	eb40 0000 	adc.w	r0, r0, r0
   10642:	bf28      	it	cs
   10644:	eba3 2381 	subcs.w	r3, r3, r1, lsl #10
   10648:	ebb3 2f41 	cmp.w	r3, r1, lsl #9
   1064c:	bf00      	nop
   1064e:	eb40 0000 	adc.w	r0, r0, r0
   10652:	bf28      	it	cs
   10654:	eba3 2341 	subcs.w	r3, r3, r1, lsl #9
   10658:	ebb3 2f01 	cmp.w	r3, r1, lsl #8
   1065c:	bf00      	nop
   1065e:	eb40 0000 	adc.w	r0, r0, r0
   10662:	bf28      	it	cs
   10664:	eba3 2301 	subcs.w	r3, r3, r1, lsl #8
   10668:	ebb3 1fc1 	cmp.w	r3, r1, lsl #7
   1066c:	bf00      	nop
   1066e:	eb40 0000 	adc.w	r0, r0, r0
   10672:	bf28      	it	cs
   10674:	eba3 13c1 	subcs.w	r3, r3, r1, lsl #7
   10678:	ebb3 1f81 	cmp.w	r3, r1, lsl #6
   1067c:	bf00      	nop
   1067e:	eb40 0000 	adc.w	r0, r0, r0
   10682:	bf28      	it	cs
   10684:	eba3 1381 	subcs.w	r3, r3, r1, lsl #6
   10688:	ebb3 1f41 	cmp.w	r3, r1, lsl #5
   1068c:	bf00      	nop
   1068e:	eb40 0000 	adc.w	r0, r0, r0
   10692:	bf28      	it	cs
   10694:	eba3 1341 	subcs.w	r3, r3, r1, lsl #5
   10698:	ebb3 1f01 	cmp.w	r3, r1, lsl #4
   1069c:	bf00      	nop
   1069e:	eb40 0000 	adc.w	r0, r0, r0
   106a2:	bf28      	it	cs
   106a4:	eba3 1301 	subcs.w	r3, r3, r1, lsl #4
   106a8:	ebb3 0fc1 	cmp.w	r3, r1, lsl #3
   106ac:	bf00      	nop
   106ae:	eb40 0000 	adc.w	r0, r0, r0
   106b2:	bf28      	it	cs
   106b4:	eba3 03c1 	subcs.w	r3, r3, r1, lsl #3
   106b8:	ebb3 0f81 	cmp.w	r3, r1, lsl #2
   106bc:	bf00      	nop
   106be:	eb40 0000 	adc.w	r0, r0, r0
   106c2:	bf28      	it	cs
   106c4:	eba3 0381 	subcs.w	r3, r3, r1, lsl #2
   106c8:	ebb3 0f41 	cmp.w	r3, r1, lsl #1
   106cc:	bf00      	nop
   106ce:	eb40 0000 	adc.w	r0, r0, r0
   106d2:	bf28      	it	cs
   106d4:	eba3 0341 	subcs.w	r3, r3, r1, lsl #1
   106d8:	ebb3 0f01 	cmp.w	r3, r1
   106dc:	bf00      	nop
   106de:	eb40 0000 	adc.w	r0, r0, r0
   106e2:	bf28      	it	cs
   106e4:	eba3 0301 	subcs.w	r3, r3, r1
   106e8:	f1bc 0f00 	cmp.w	ip, #0
   106ec:	bf48      	it	mi
   106ee:	4240      	negmi	r0, r0
   106f0:	4770      	bx	lr
   106f2:	ea9c 0f00 	teq	ip, r0
   106f6:	bf48      	it	mi
   106f8:	4240      	negmi	r0, r0
   106fa:	4770      	bx	lr
   106fc:	bf38      	it	cc
   106fe:	2000      	movcc	r0, #0
   10700:	bf04      	itt	eq
   10702:	ea4f 70ec 	moveq.w	r0, ip, asr #31
   10706:	f040 0001 	orreq.w	r0, r0, #1
   1070a:	4770      	bx	lr
   1070c:	fab1 f281 	clz	r2, r1
   10710:	f1c2 021f 	rsb	r2, r2, #31
   10714:	f1bc 0f00 	cmp.w	ip, #0
   10718:	fa23 f002 	lsr.w	r0, r3, r2
   1071c:	bf48      	it	mi
   1071e:	4240      	negmi	r0, r0
   10720:	4770      	bx	lr
   10722:	2800      	cmp	r0, #0
   10724:	bfc8      	it	gt
   10726:	f06f 4000 	mvngt.w	r0, #2147483648	; 0x80000000
   1072a:	bfb8      	it	lt
   1072c:	f04f 4000 	movlt.w	r0, #2147483648	; 0x80000000
   10730:	f000 b80e 	b.w	10750 <__aeabi_idiv0>

00010734 <__aeabi_idivmod>:
   10734:	2900      	cmp	r1, #0
   10736:	d0f4      	beq.n	10722 <.divsi3_skip_div0_test+0x27c>
   10738:	e92d 4003 	stmdb	sp!, {r0, r1, lr}
   1073c:	f7ff feb3 	bl	104a6 <.divsi3_skip_div0_test>
   10740:	e8bd 4006 	ldmia.w	sp!, {r1, r2, lr}
   10744:	fb02 f300 	mul.w	r3, r2, r0
   10748:	eba1 0103 	sub.w	r1, r1, r3
   1074c:	4770      	bx	lr
   1074e:	bf00      	nop

00010750 <__aeabi_idiv0>:
   10750:	b502      	push	{r1, lr}
   10752:	f04f 0008 	mov.w	r0, #8
   10756:	f7ff edda 	blx	1030c <raise@plt>
   1075a:	bd02      	pop	{r1, pc}

0001075c <__libc_csu_init>:
   1075c:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
   10760:	4607      	mov	r7, r0
   10762:	4e0c      	ldr	r6, [pc, #48]	; (10794 <__libc_csu_init+0x38>)
   10764:	4688      	mov	r8, r1
   10766:	4d0c      	ldr	r5, [pc, #48]	; (10798 <__libc_csu_init+0x3c>)
   10768:	4691      	mov	r9, r2
   1076a:	447e      	add	r6, pc
   1076c:	f7ff edbe 	blx	102ec <_init>
   10770:	447d      	add	r5, pc
   10772:	1b76      	subs	r6, r6, r5
   10774:	10b6      	asrs	r6, r6, #2
   10776:	d00a      	beq.n	1078e <__libc_csu_init+0x32>
   10778:	3d04      	subs	r5, #4
   1077a:	2400      	movs	r4, #0
   1077c:	3401      	adds	r4, #1
   1077e:	f855 3f04 	ldr.w	r3, [r5, #4]!
   10782:	4638      	mov	r0, r7
   10784:	4641      	mov	r1, r8
   10786:	464a      	mov	r2, r9
   10788:	4798      	blx	r3
   1078a:	42b4      	cmp	r4, r6
   1078c:	d1f6      	bne.n	1077c <__libc_csu_init+0x20>
   1078e:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
   10792:	bf00      	nop
   10794:	0001006a 	.word	0x0001006a
   10798:	00010060 	.word	0x00010060

0001079c <__libc_csu_fini>:
   1079c:	4770      	bx	lr
   1079e:	bf00      	nop

Disassembly of section .fini:

000107a0 <_fini>:
   107a0:	e92d4008 	push	{r3, lr}
   107a4:	e8bd8008 	pop	{r3, pc}
```