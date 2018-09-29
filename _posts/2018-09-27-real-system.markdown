---
layout: post
title:  "Real Number System"
date:   2018-09-27 5:00:05 +0800
categories: analysis
use_math: true
tags: analysis real_number triangle_inqequality bernoulli_inequality completeness_axiom
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
For \\(x,y\in\mathbb\{R\}\\), show that \\[\|\|x\|+\|y\|\|\leq\|x+y\|\leq\|x\|+\|y\|\\]	

__Proof__: Using Ex)2.2.9, square the both sides and use \\(xy\leq\|xy\|, -xy\leq\|xy\|\\).

### Extended Real Number System
\\[\tilde\{\mathbb\{R\}\}:=\mathbb\{R\}\bigcup\\{-\infty,\infty\\}\bigcup=[-\infty,\infty]\\]

### Irrational Numbers

Preliminaries: upper bound, least upper bound property, supremum (<a href="{{site.url}}/analysis/2018/09/25/ordered-set.html#maximum" target="_blank">link</a>)

> __Rudin__: The rational number system is inadequate for many purposes, both as a field and as an ordered set. For instance, there is no rational p such that \\(p^2=2\\). This leads to the introduction of so-called “irrational numbers”.

Both \\(\mathbb\{Q\}\\) field and \\(\mathbb\{R\}\\) field satisfies field/order axiom. However \\(\exists\\) numbers not in \\(\mathbb\{Q\}\\), and if we ignore such numbers there is infinite "holes" in the line of numbers.  
\\(\rightarrow\\) we need a axiom to comptete the line

> `Completeness axiom`  (<a href="{{site.url}}/analysis/2018/09/25/ordered-set.html#lub_lbp" target="_blank">Least Upper Bound property</a> - also implies Greatest lower bound)
If \\(S\subseteq\mathbb\{R\}\\) is not empty and bounded above, its supremum exists.

EX) Let \\(E=\\{x\in \mathbb\{Q\}\\ \| \\ x^2<2\\}\\). In \\(\mathbb\{Q\},\\ E\\) has no supremum. However thanks to the axiom, \\(\sup E\\) exists in \\(\mathbb\{R\}\\).

> `Archimedeas Property`  
For arbitrary \\(a\in\mathbb\{R\}, b>0\\), there exists \\(n\in\mathbb\{N\}\\) such that
\\[a<nb\\]
holds.

Proof. 
1. \\(a\leq 0\\): trivial
2. \\(a>0\\): Suppose not. Then \\(a\geq nb\\) for all \\(n\in\mathbb\{N\}\\), so that \\(a/b\\) is a upper bound of \\(\mathbb\{N\}\\). Then by the completeness axiom, there exists a supremum \\(c\\) of \\(\mathbb\{N\}\subset \mathbb\{R\}\\).  
Considering \\(\epsilon=1\\), there exists \\(k\in\mathbb\{N\}\\) such that \\(c-1<k\leq c\\).  
Since \\(\mathbb\{N\}\\) is a inductive set, \\(k+1\in\mathbb\{N\}\\), which gives a contradiction on above inequality. 
  
> Theorem: `Compactness of Real Numbers`  
In \\(\mathbb\{R\}\\) (as a universe), the (sub)set of rational numbers and irrational numbers are compact.

Proof: use Archimedeas property. (book, 54p)

It can be alternatively expressed as, "Any nonempty open subset of \\(\mathbb\{R\}\\ has rational numbers and irrational numbers as its element"

Next:  

