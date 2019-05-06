---
layout: post
title:  "Complex Field"
date:   2018-09-28 5:00:05 +0800
categories: analysis
use_math: true
tags: analysis complex_field
---

### The Complex Field

A `complex number` \\(c\in\mathbb\{C\}\\) is an ordered pair \\((a,b)\\) of real numbers. The numbers in this pages are in \\(\mathbb\{C\}\\), unless stated otherwise.

Let \\(x=(a,b), y=(c,d)\\). We write
* \\(x=y\\) i.i.f \\(a=c \land b=d\\)
* \\(x+y=(a+c,b+d)\\)
* \\(xy=(ac-bd, ad+bc)\\)

Above 3 properties let \\(\mathbb\{C\}\\) to satisfy the `field axiom`, with \\[0=(0,0)\quad 1=(1,0).\\]__Thus__ \\(\mathbb\{C\}\\) __is a field__. (proof skipped, field axiom of Rudin 1.12)

Furthermore, we see that by the mapping 
\\[\phi:\mathbb\{C\}\mapsto \mathbb\{R\},\quad (a,0)\mapsto a,\\]the field axiom of \\(\mathbb\{R\}\\) holds for the subset 
\\[\bar\{\mathbb\{R\}\}:=\\{(a,b)\in\mathbb\{C\}\\ \| \\ b=0\\}\\]
of the \\(\mathbb\{C\}\\). __Thus__ \\(\mathbb\{C\}\\) __contains__ \\(\mathbb\{R\}\\) __as a subfield.__


### Conjugate of a complex number

For \\(x=(a,b)\\),
1.  \\(\text\{Re\}(x)=a\\), \\(\text\{Im\}(x)=b\\)
2. Define `conjugate` of \\(a\in\mathbb\{C\}\\) as
\\[\bar\{a\} = (a,-b)\\] 

> __Theorem__: Let \\(x=(a,b), y=(c,d)\\). Then  
(a) \\(\|z\|=0\quad\leftrightarrow\quad z=(0,0)=0\\)  
(b) \\(\|\bar\{z\}\|=\|z\|\\)  
(c) \\(\|zw\|=\|z\|\|w\|\\)  
(d) \\(\|\text\{Re\}(z)\leq\|z\|\|\\)  
(e) \\(\|z+w\|\leq\|z\|+\|w\|\\)

__Proof__:
1. \\(\rightarrow\\): take contrapositive  
\\(\leftarrow\\): trivial
2. \\(\|\bar\{z\}\|=\bar\{z\}z=z\bar\{z\}=\|z\|\\)
3. \\[\{\|zw\|\}^2=\left((ac-bd,bc+ad)(ac-bd-bc-ad)\right)^2\\]
\\[=(ac-bd)^2+(bc+ad)^2=a^2c^2+b^2+d^2+b^2c^2+a^2d^2+2abdc-2abcd\\]
\\[=(a^2+b^2)(c^2+d^2)=\|z\|^2\|w\|^2\\]
Taking sqrt on each side, by the theorem (uniqueness of sqrt) it is clear that the equation bedomes (c)
4. Trivial
5. Note that \\(\bar\{z\bar\{w\}\}=\bar\{z\}w\\), so that \\(z\bar\{w\}+\bar\{z\}w=\text\{Re\}(z\bar\{w\})\\).
\\[\|z+w\|^2=(z+w)(\bar\{z\}+\bar\{w\})\\]
\\[=\|z\|^2+\bar\{z\}w+z\bar\{w\}+\|w\|^2=\|z\|^2+2\text\{Re\}(z\bar\{w\})+\|w\|^2\\]
Now using (d), (c) and (b) sequentially, \\(\text\{Re\}(z\bar\{w\})\leq \|z\bar\{w\}\|\leq \|z\|\|\bar\{w\}\|=\|z\|\|w\|\\) holds, and
\\[\leq \|z\|^2+2\|z\|\|w\|+\|w\|^2=(\left(\|z\|+\|w\|\right)^2\\]
Again by taking square root, the theorem follows.  

Next:  

