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


* <a href="http://www.ti.com/lit/ug/sprui04c/sprui04c.pdf" target="_blank">TI c6000 compiler manual</a>
* <a href="https://thrillfighter.tistory.com/383" target="_blank">https://thrillfighter.tistory.com/383</a>
