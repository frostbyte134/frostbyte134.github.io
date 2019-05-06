---
layout: post
title:  "Metric Space"
date:   2018-10-03 5:00:05 +0800
categories: analysis
use_math: true
tags: analysis metric_space schwartz_inequality
---

Metric space = field + distance

### Metric space
`Real number system` = real field axiom (+,*) \\(\land\\) total order relation \\(\geq\\)

Note that every subset of a metric space is a metric space in its own right.

### Complex Euclidean Space

In the Complex Euclidean space \\(\mathbb\{C\}^k\\), which subsumes the Euclidean space \\(\mathbb\{R\}^k\\). 
The distance used in it is defined by
\\[d(x,y)=\|x-y\|\\]
We now show that the `Schwartz inequality` holds in \\(\mathbb\{C\}^k\\), and from it prove that \\(d(x,y)\\) is indeed a distance.

> Theorem: `Schwartz inequality`  
If \\(a_1,...,a_n\\) and \\(b_1,...,b_n\\) are complex numbers, then
\\[\left\|\sum\_\{i=1\}^na\_i\bar\{b\}_i\right\|^2\leq\left\|\sum\_\{i=1\}^na_i\right\|^2\left\|\sum\_\{i=1\}^nb_i\right\|^2\\]

__Proof__: Define
* \\(A:=\sum\|a_j\|^2\\)
* \\(B:=\sum\|b_j\|^2\\)
* \\(C:=\sum a_j\bar\{b\}_j\\)

If \\(B=0\\), then \\(b_j=0\\) so that the theorem holds trivially.  
If not (\\(B>0\\)), by the basic property of the distance \\(\|a\|\\) in \\(\mathbb\{C\}^k\\) we have
\\[\sum\|Ba\_j-Cb\_j\|^2=\sum(Ba\_j-Cb\_j)(B\bar\{a\}\_j-\bar\{C\}\bar\{b\}\_j)\\]
\\[B^2\sum a\_j\bar\{a\}\_j-BC\sum\bar\{a\}_jb\_j-B\bar\{C\}\sum a\_j\bar\{b\}\_j+C\bar\{C\}\sum b\_j\bar\{b\}_j\\]
\\[A^2B^2-B\|C\|^2-B\|C\|^2+B\|C\|^2\\]
\\[=B(BA-\|C\|^2)\geq 0\quad\rightarrow\quad BA-\|C\|^2\geq 0\\]
QED

> Theorem: \\(\mathbb\{C\}^k\\) with above distance is a metric space.  
For \\(x,y\in \mathbb\{C\}^k,\alpha\in\mathbb\{C\}\\)  
(a) \\(\|x\|\leq0\\)  
(b) \\(\|x\|=0 \quad\leftrightarrow\quad x=0\\)  
(c) \\(\|\alpha x\|=\|\alpha\|\|x\|\\)  
(d) \\(\|x\cdot y\|\leq\|x\|\|y\|\\)  
(e) \\(\|x+y\|\leq\|x\|+\|y\|\\)  
(f) \\(\|x-y\|\leq\|x-y\|+\|y-z\|\\)  

__Proof__: (a), (b), and (c) comes directly from (link), and (d) is another representation of `Schwartz inequality`.  
To proce (e)
\\[\|x+y\|^2=(x+y)(\bar\{x\}+\bar\{y\})\\]
\\[=\|x\|^2+x\bar\{y\}+\bar\{x\}y+\|y\|^2\\]
\\[\leq \|x\|^2+2\|x\|\|y\|+\|y\|^2=(\|x\|+\|y\|)^2\\]
where the last inequality follows from (d).  
(f) is another form of (e) (y to x <= y to z to x)

With the definition of the distance, we can talk about (the openness and closedness of a set)(link) in it.


