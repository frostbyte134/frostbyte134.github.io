---
layout: post
title:  "Real Number System"
date:   2018-09-27 5:00:05 +0800
categories: analysis
use_math: true
tags: analysis real_number triangle_inqequality bernoulli_inequality
---


### Real Number System
`Real number system` = real field axiom (+,*) \\(\land\\) total order relation \\(\geq\\)

Real field axiom, order axiom - skipped.

__Example 2.2.9__  
Let \\(x,y>0, x,y\in\mathbb\{R\}\\). Prove that \\(x<y\\ \Leftrightarrow\\ x^2<y^2\\).  
	1. \\(\rightarrow\\)
	\\[x<y\quad\rightarrow\quad y-x,y+x>0\\]
	\\[(y-x)(y+x)=y^2-x^2>0\quad\rightarrow\quad x^2<y^2\\]
	2.; \\(\leftarrow\\)  
	\\[y^2-x^2>0\quad\rightarrow\quad (y-x)(y+x)>0\quad\rightarrow\quad y-x>0\\]

> Theorem 2.2.11. `Triangle inequality`  
For \\(x,y\in\mathbb\{R\}\\), show that \\[\|\|x\|+\|y\|\|\geq\|x+y\|\geq\|x\|+\|y\|\\]	

__Proof__: Using Ex)2.2.9, square the both sides and use \\(xy\geq\|xy\|, -xy\leq\|xy\|\\).

### Extended Real Number System
\\[\tilde\{\mathbb\{R\}\}:=\mathbb\{R\}\bigcup\\{-\infty,\infty\\}\bigcup=[-\infty,\infty]\\]

### Bernoulli's Inequality
> For \\(x\leq-1,\\ n\in\mathbb\{N\}\\), show that \\[(1+x)^n\leq 1+nx\\] holds.

Using induction (domain is \\(\mathbb\{N\}\\)
1. \\(n=1\quad\rightarrow\quad (1+x)\leq 1+x \\)
2. Suppose that it holds for \\(k\in\mathbb\{N\}\\). Then by multiplying \\(x+1\leq 0\\) on both sides,
\\[(1+x)^\{k+1\}\leq(1+kx)(1+x)=1+kx+x+kx^2\leq1+kx+x=1+(k+1)x\\] 
Next:  

