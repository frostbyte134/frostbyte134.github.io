---
layout: post
title:  "Real Number System + density"
date:   2018-09-27 5:00:05 +0800
categories: analysis
use_math: true
tags: analysis
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

> Theorem 2.2.11. __Triangular inequality__  
For \\(x,y\in\mathbb\{R\}\\), show that \\[\| \|x\| - \|y\| \| \leq \|x+y\|\leq\|x\|+\|y\|\\]	


__Proof__: Preliminary : Ex)2.2.9 and \\(xy\leq\|xy\|, -xy\leq\|xy\|\\).


\\(\|x+y\| \leq \|x\|+\|y\|\\)  
Square both sides. Firstly, using that \\(\|x\|\|y\| = \|xy\|,\\ \|x+y\|^2 = (x+y)^2 = x^2+2xy+y^2\\\)  and
\\((\|x\|+\|y\|) = x^2+2\|xy\|+y^2\\)  
using preliminary, we see that the inequality indeed holds. \\(\| \|x\| - \|y\| \| \leq \|x+y\|\\) can be proved similarly


### Extended Real Number System
\\[\tilde\{\mathbb\{R\}\}:=\mathbb\{R\}\bigcup\\{-\infty,\infty\\}\bigcup=[-\infty,\infty]\\]

### Irrational Numbers

Preliminaries: upper bound, least upper bound property, supremum (<a href="{{site.url}}/analysis/2018/09/25/ordered-set.html#maximum" target="_blank">link</a>)

> __Rudin__: The rational number system is inadequate for many purposes, both as a field and as an ordered set. For instance, there is no rational p such that \\(p^2=2\\). This leads to the introduction of so-called “irrational numbers”.

Both \\(\mathbb\{Q\}\\) field and \\(\mathbb\{R\}\\) field satisfies field/order axiom. However \\(\exists\\) numbers not in \\(\mathbb\{Q\}\\), and if we ignore such numbers there is infinite "holes" in the line of numbers.  
\\(\rightarrow\\) we need a axiom to comptete the line

> __Completeness axiom__  (<a href="{{site.url}}/analysis/2018/09/25/ordered-set.html#lub_lbp" target="_blank">Least Upper Bound property</a> - also implies Greatest lower bound)
If \\(S\subseteq\mathbb\{R\}\\) is not empty and bounded above, its supremum exists.

EX) Let \\(E=\\{x\in \mathbb\{Q\}\\ \| \\ x^2<2\\}\\). In \\(\mathbb\{Q\},\\ E\\) has no supremum. However thanks to the axiom, \\(\sup E\\) exists in \\(\mathbb\{R\}\\).

> __Archimedeas Property__  
For arbitrary \\(a\in\mathbb\{R\}, b>0\\), there exists \\(n\in\mathbb\{N\}\\) such that
\\[a<nb\\]
holds.

Proof. 
1. \\(a\leq 0\\): trivial
2. \\(a>0\\): Suppose not. Then \\(a\geq nb\\) for all \\(n\in\mathbb\{N\}\\), so that \\(a/b\\) is a upper bound of \\(\mathbb\{N\}\\). Then by the completeness axiom, there exists a supremum \\(c\\) of \\(\mathbb\{N\}\subset \mathbb\{R\}\\).  
Considering \\(\epsilon=1\\), there exists \\(k\in\mathbb\{N\}\\) such that \\(c-1<k\leq c\\).  
Since \\(\mathbb\{N\}\\) is a inductive set, \\(k+1\in\mathbb\{N\}\\), which gives a contradiction on above inequality. 
  

#### Density of Rational, Irrational Numbers 

> Theorem: __Density of Rational, Irrational Numbers__  
The set of rational numbers and irrational numbers are dense in \\(\mathbb\{R\}\\). 

Proof: use Archimedeas property. (맛있는 해석학, 54p)

It can be alternatively expressed as, __Any nonempty open subset of__ \\(\mathbb\{R\}\\) __has rational numbers and irrational numbers as its element__

- Archimedeas property가 필요하므로, Completeness axiom (실수계의 완비성 = 상한 공리) 또한 필요함 (자연수의 귀납적 정의도)


### Bernoulli's Inequality

For \\(x\geq -1\\) and \\(\forall\\ n\in \mathbb{N}\\),
\\[(1+x)^n\geq 1+nx \tag{1}\\]


__proof__: Denote the inequality (1) as \\(p(n)\\). 

1. Base case : we see that for \\(=1\\) it holds trivially
2. For arbitrary \\(k\in \mathbb{N}\\), suppose that \\(p(k)\\) holds. Then  
   \\[p(k) = (1+x)^k \geq 1+xk\\]
   by multiplying \\(1+x\\) (by the given condition, \\(1+x\geq 0\\)),
   \\[(1+x)^{k+1} \geq (1+xk)(1+x) = 1+(k+1)x+kx^2 \geq 1+(k+1)x\\]
   we see that \\(p(k+1)\\) holds.

	
Next:  

