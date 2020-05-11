---
layout: post
title:  "Data alignment in C (+TI dsp!)"
date:   2020-04-10 09:01:05 +0800
categories: coding
use_math: true
tags: coding C
---

* <a href="http://www.catb.org/esr/structure-packing/#_who_should_read_this" target="_blank">http://www.catb.org/esr/structure-packing/#_who_should_read_this</a>

```
struct foo3 {
    char *p;     /* 8 bytes */
    char c;      /* 1 byte */
};

struct foo3 {
    char *p;     /* 8 bytes */
    char c;      /* 1 byte */
    char pad[7];
};
```

```
struct foo5 {
    char c;
    struct foo5_inner {
        char *p;
        short x;
    } inner;
};

struct foo5 {
    char c;           /* 1 byte*/
    char pad1[7];     /* 7 bytes */
    struct foo5_inner {
        char *p;      /* 8 bytes */
        short x;      /* 2 bytes */
        char pad2[6]; /* 6 bytes */
    } inner;
};
```


* <a href="https://thrillfighter.tistory.com/383" target="_blank">https://thrillfighter.tistory.com/383</a>



### TI Intrinsics

http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/vxlib_c66x_1_1_4_0/docs/doxygen/html/vxlib_html/group___v_x_l_i_b__color_convert___i_y_u_vto_r_g_b__i8u__o8u.html

* <a href="http://www.ti.com/lit/ug/sprui04c/sprui04c.pdf" target="_blank">TI c6000 compiler manual</a>
* https://training.ti.com/kr/system/files/docs/c66x-corepac-slides.pdf

* <a href="https://www.ti.com/lit/an/spraa75/spraa75.pdf" target="_blank">https://www.ti.com/lit/an/spraa75/spraa75.pdf</a>
> intrinsic operators are built-in functions in the compiler that can be directly translated to assembly code(assembly instruction), for faster execution

__Unaligned load of 64-bit values__
* `_mem8_const`: Allows unaligned loads of 8 bytes from memory
* `_packh4`, `packl4`: Packs alternate bytes into return value. Can pack high or low bytes.
* `_hill`: Returns the high (odd) register of a long long register pair
* `_sub4`: Performs 2s-complement subtraction between pairs of packed 8-bit values
* `__x128_t _dmpy2`: Four-way SIMD multiply of signed 16-bit values producing four signed 32-bit results. (Two-way _mpy2