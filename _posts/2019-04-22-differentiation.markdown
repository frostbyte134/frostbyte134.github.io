---
layout: post
title:  "Differentiation"
date:   2019-4-22 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis continuity limit function compact differentiation derivative
---



### Derivative of a function
> __Definition__ 5.1 (PMA):  
Let \\(f\\) be defined (and __real-valued__) on \\([a,b]\\). For any \\(x\in [a,b]\\) (including the boundary) form the quotient
\\[\phi(t)=\frac\{f(t)-f(x)\}\{t-x\},\quad (a<t<b,\\ t\neq x)\tag\{1\}\\]
and define
\\[f'(x):=\lim\_\{t\rightarrow x\}\phi(t)\tag\{2\}\\]
provided that __the limit exists__ in accordance with <a href="https://nailbrainz.github.io/analysis/2018/12/19/limit.html" target="_blank">its definition</a>.

Note that,
1. We thus associate with the function \\(f\\) a function \\(f'\\) whose domain is the set of points \\(x\\) at which the limit 2 exists. We call \\(f'\\) as the derivative of \\(f\\).
2. derivative of a function \\(f\\) is defined as a limit of the function \\(\phi\\). 
3. `gradient` = transpose of the derivative
4. If \\(f'\\) is defined at a point \\(x\\), we say that \\(f\\) is `differentiable` at \\(x\\) (pointwise property). 
5. It is possible to consider right(left)-hand derivatives, using the definition of right(left) limits.

Using 1, we see that when \\(f,\\ g\\) are differentiable, the differentiability of \\(f+g, f/g, fg\\) follows using the linearity of the limit.

> __Theorem__ 5.2 (PMA):  
Let \\(f\\) be defined on \\([a,b]\\). If \\(f\\) is differentiable at a point \\(x\in [a,b]\\), then \\(f\\) is continuous at \\([a,b]\\).

__proof__:  
If \\(f\\) is differentiable at \\([a,b]\\), then \\(\forall x\in [a,b],\\ \epsilon > 0, \exists \delta > 0 :\\)
Note that 
\\[f(t)-f(x)=\frac\{f(t)-f(x)\}\{t-x\}(t-x)=\phi(t)(t-x).\\]
As \\(t\rightarrow x,\\ f(t)-f(x)=\phi(t)(t-x)\rightarrow f'(x)\cdot (0)=0\\).  
__The converse is not true__.

> __Theorem__ 5.2 (PMA): __Chain rule of derivatives__   
Suppose that \\(f\\) is continuous at \\([a,b]\\), \\(f'(x)\\) exists at some point \\(x\in [a,b\]\\), \\(g\\) is defined in the \\(I\\), range of \\(f\\), and \\(g\\) is defferentiable at \\(f(x)\\).  
Then, the function \\(f\\) defined as
\\[h(x)=g(f(x))\\]
is differentiable at \\(x\\), and its derivative at \\(x\\) is
\\[h'(x)=g'(f(x))f'(x)\\]

Let \\(y=f(x)\\), so that \\(g\\) is differentiable at \\(y\\).  
By the definition of derivatives, we have
\\[ f(t)-f(x)=[ f'(x)-u(t) ] (t-x) \tag\{4\} \\]
\\[ g(s)-g(y)=[ g'(y)-v(s) ] (s-y) \tag\{5\} \\]
where \\(t\in [a,b],\\ s\in I\\), and \\(\lim\_\{t\rightarrow x\}u(t)=0,\\ \lim\_\{s\rightarrow y\}v(s)=0\\).  
Let \\(s=f(t)\\). Using first (5) and then (4) we obtain
\\[h(t)-h(x)=g(f(t))-g(f(x))\\]
\\[=[f(t)-f(x)][g'(y)+v(s)]\\]
\\[=(t-x)[f'(x)-u(t)][g'(y)+v(s)]\\]
or, if \\(t\neq x\\),
\\[\frac\{h(t)-h(x)\}\{t-x\}=[g'(y)+v(s)][f'(x)-u(t)]\\]

Note that, by the continuity (and continuity of the composed functions), \\[\lim\_\{t\rightarrow x\}v(f(t))=0.\\]so that the rhs of (6) tends to \\(g'(y)f'(x)\\).

### Mean value theorems

> __Definition__ 5.7 (PMA):\\(\quad\\)Local Maximum   
Let \\(f\\) be a real function defined on a metric space \\(X\\). We say that \\(f\\) has a local maximum at a point \\(p\\) if there eixsts \\(\delta>0\\) such that, \\(f(q)\leq f(p)\\) for all \\(q\in X\\) with \\(d(p,q)<\delta\\).

> __Definition__ 5.8 (PMA): \\(f'(x)=0\\) at local minimum  
Let \\(f\\) be defined on \\([a,b]\\); if \\(f\\) has a local maximum at a point \\(x\in(a,b)\\), and if \\(f'(x)\\) exists, then \\(f'(x)=0\\).

__proof__ Choose \\(\delta>0\\) in accordance with `Def 5.7`, so that
\\[a<x-\delta<x+\delta<b.\\] If \\(x-\delta < t < x\\), then \\[\frac\{f(t)-f(x)\}\{t-x\}\leq 0\\] Letting \\(t\rightarrow x\\), we see that \\(f'(x)\leq 0\\) (which is a limit of \\(\phi\\)).  
On the other side \\(x< t < x+\delta,\quad f'(x) \geq 0\\) holds, so that \\(f'(x)=0\\).

> __Theorem__ 5.9 (PMA): \\(\quad\\) Generalized Mean value theorem  
If \\(f,q\\) are continuous real functions on \\([a,b]\\) which are differentiable in \\((a,b)\\), then there is a point \\(x\in (a,b)\\) at which
\\[ [ f(b)-f(a) ] g\'(x) = [ g(b)-g(a) ] f\'(x) \\]
\\[\rightarrow \frac\{f(b)-f(a)\}\{g(b)-g(a)\}=\frac\{f'(x)\}\{g'(x)\}\\]

__proof__ Put
\\[h(t)=[f(b)-f(a)]g(t)-[g(b)-g(a)]f(t)\quad (a\leq t \leq b)\\]
Then \\(h\\) is continuous on \\([a,b]\\), \\(h\\) is differentiable in \\((a,b)\\), and
\\[h(a)=h(b)=f(b)g(a)-f(a)g(b) \tag\{12\}\\]
To prove the theorem, we have to show that \\(h'(x)=0\\) at some \\(x\in (a,b)\\)
1. If \\(h\\) is constant, this holds for all \\(x\in(a,b)\\)
2. If \\(h(t)>h(a)\\) for some \\(t\in (a,b)\\), let \\(x\\) be a point on \\([a,b]\\) at which \\(h\\) attains its maximum (`Thm 4.16`: continous function on compact set achieves its maximum/minimum). By (12), \\(x\in (a,b)\\), and `Thm 5.8` shows that \\(h'(x)=0\\).
3. If \\(h(t)< h(a)\\), then the same argument with minimum can be applied. 


> __Theorem__ 5.10 (PMA): \\(\quad\\) The Mean value theorem  
If \\(f\\) is a real continuous function on \\([a,b]\\) which is differentiable in \\((a,b)\\), then there exists a point \\(x\\) in which
\\[\frac\{h(b)-h(a)\}\{b-a\}=f'(x)\\]

__proof__: let \\(g(x)=x\\) on `Thm 5.9`.

### The Continuity of derivatives

TODO: add link on 4.23 (connectedness)
> Not every function is a derivative. ... intermediate values are assumed (Compare Thm 4.23) 

> __Theorem__ 5.12 (PMA)  
Suppose \\(f\\) is a real differentiable function on \\([a,b]\\) and suppose \\(f'(a)<\lambda < f'(b)\\). Then there is a point \\(x\in (a,b)\\) such that \\(f'(x)=\lambda\\). 

__proof__: Put \\[g(t)=f(t)-\lambda t.\\]
1. Then \\(g'(a)=f'(a)-\lambda < 0\\), so that \\(g(a) > g(t\_1)\\) for some right neighbors of \\(a\\).  
2. Similarly, \\(g(t\_2) < g(b)\\) for some left neighbor of \\(b\\).
3. Hence, \\(g\\) (which is a continuous function) attains its minimum at \\(x\in (a,b)\\) (`Thm 4.16`). By `Thm 5.8`, \\[g'(x)=0\quad\rightarrow\quad f'(x)=\lambda.\\]

__Corollary__: If \\(f\\) is differentiable on \\([a,b]\\), then \\(f'\\) cannot have any simple discontinuities on \\([a,b]\\) But it may very well have discontinuity of second kind

__proof__: by contradiction, assume not so ans work on \\(x,x\\).

### L'Hospital's Rule
Skipped

### Derivatives of Higher Order
> __Definition__ 5.13 (PMA)  
If \\(f\\) has a derivative \\(f'\\) on an interval, and if \\(f'\\) itself is differentiable, we denote the derivative of \\(f'\\) by \\(f''\\), and call \\(f''\\) the __second derivative__ of \\(f\\).  
Continuing in this manner, we obtain functions
\\[f,f',f'',f^\{(3)\},...,f^\{(n)\}\\]
each of which is the deriv of the preceding one.  
\\(\quad\\) In order for \\(f^\{(n)\}\\) to exists at a point \\(x\\), \\(f^\{(n-1)\}\\) must exists at the neighbor of \\(x\\), so that we can evaluate
\\[\phi(t)=\frac\{f^\{(n-1)\}(t)-f^\{(n-1)\}(x)\}\{t-x\}\\]
near \\(x\\). (\\(f\\) must be differentiable \\(n-1\\) times near \\(x\\))


### Taylor's Theorem
> __Theorem__ 5.15 (PMA)\\(\quad\\) __Taylor's Theorem__  
Suppose 
* \\(f\\) is a real function on \\([a,b]\\)
* \\(n\\) is a positive integer
* \\(f^\{(n-1)\}\\) is continuous on \\([a,b]\\) (considering the boundary, this condition is not a 100% duplicated with preceding one)
* \\(f^\{(n)\}(t)\\) exists for every \\(t\in (a,b)\\).  \\[\\]
Let \\(\alpha,\beta\\) be distinct points of \\([a,b]\\), and define
\\[ P(t):=\sum\_\{k=0\}^\{n-1\} \frac\{f^\{(k)\}(\alpha)\}\{k!\}(t-\alpha)^k \tag\{23\}\\]
\\[=f(\alpha) + f^\{(1)\}(t-\alpha) + \frac\{f^\{(2)\}(\alpha)\}\{2!\}(t-\alpha)^2+\cdots + \frac\{f^\{(n-1)\}(\alpha)\}\{(n-1)!\}(t-\alpha)^\{n-1\}\\] (approximation of \\(f(t)\\) at \\(\alpha\\))  
Then there exists a point \\(x\in (\alpha, \beta)\\) such that (the approximation is somewhat exact)
\\[f(\beta)=P(\beta)+ \frac\{f^\{(n)\}(x)\}\{n!\}(\beta-\alpha)^n \tag\{24\}\\]

1. For \\(n=1\\), this is the mean value theorem.
2. In general, the theorem shows that \\(f(\beta)\\) can be approximated by a polynomial of deg \\(n-1\\) at \\(\alpha\\), and that (24) allows us to estimate the error, if we know bounds on \\(\| f^\{(n)\}(x)\| \\).

__proof__: Let \\(M\\) be the number defined by
\\[f(\beta)=P(\beta) + M(\beta-\alpha)^n \tag\{25\}\\]
1. We have to show that \\(n!M=f^\{(n)\}(x)\\) for some \\(x\\) between \\(\alpha,\beta\\), so that (25) becomes (24).  
2. Put \\[g(t)=f(t)-P(t)-M(t-\alpha)^n.\\]By (23), \\[g^\{(n)\}(t)=f^\{(n)\}(t)-n!M\quad(a<t<b)\\] (If we differentiate \\(P(t)\\) n times, it dissapears)  
Hence the proofwill be complete if we can show that \\(g^\{(n)\}(x)=0\\) for some \\(x\\) between \\(\alpha,\beta\\). 
3. At \\(\alpha\\), since \\(P^\{(k)\}(\alpha)=f^\{(k)\}(\alpha)\\) for \\(k=0,1,...,n-1\\), we have
\\[ g(\alpha)=g'(\alpha)=\cdot=g^\{(n-1)\}(\alpha)=0 \tag\{28\}\\]
4. Our choice of \\(M\\) shows that \\(g(\beta)=0\\), so that \\(g'(x\_1)=0\\) for some \\(x\_1\\) between \\(\alpha,\beta\\), by the mean value theorem. 
5. Since \\(g'(\alpha)=0\\), we conclude similarly that \\(g''(x\_2)=0\\) for some \\(x\_2\\) between \\(\alpha,x\_1\\). 
6. After \\(n\\) steps, we arrive at the conclusion that \\(g^\{(n)\}(x\_n)=0\\) for some \\(x\_n\\) between \\(\alpha,x\_\{n-1\}\\), that is, between \\(\alpha,\beta\\).


### Differentiation of Vector-valued function
Here we consider a family of functions in a form \\[f:\Re \mapsto \Re^k\\]
The resulting function can be decomposed into n components, \\(f\_i,\\ i=1,...,k\\), and with the metrics defined in \\(R^n\\) and <a href="{{site.url}}/analysis/2019/03/30/continuity.html#vector_valued" target="_blank">`Thm 4.10`</a>, some theorems stated here (`Thm 5.2, 5.3 (a),(b)`) can be directly applied (5.3 requires to replace the multiplication with `inner product`).

Namely, now \\(f'(x)\\) is __a point in__ \\(R^k\\) (if exists) which satisfies
\\[\lim\_\{t\rightarrow x\} \left\| \frac\{f(t)-f(x)\}\{t-x\}-f'(x) \right\|=0\\]
and again \\(f':R \mapsto R^k\\).

If \\(f\_1,...,f\_1\\) are compopnents of \\(f\\), as in <a href="{{site.url}}/analysis/2019/03/30/continuity.html#vector_valued" target="_blank">`Thm 4.10`</a>, then 
\\[ f'=(f'\_1,...,f'\_k) \\]
and \\(f\\) is differentiable at a point \\(x\\) i.i.f all of the functions \\(f\_1,...,f\_k\\) are differentaible at \\(x\\).

__Mean value theorem does not hold__, but we have another (as much as) useful theorem.
> __Theorem__ 5.19 (PMA)\\(\quad\\) (Lipschitz continuity of vector-valued continuous mapping?)  
Suppose \\(f\\) is a continuous mapping of \\([a,b]\mapsto R^k\\) and \\(f\\) is differentiable in \\((a,b)\\). Then there exists \\(x\in (a,b)\\) such that
\\[\|f(b)-f(a)\| \leq (b-a)\|f'(x)\|\\]

__proof__: Put \\(z=f(b)-f(a)\\), and define
\\[\phi(t)=z\cdot f(t)\quad (a\leq t \leq b).\\]
Then \\(\phi\\) is a real-valued continuous function on \\([a,b]\\) which is differentiable in \\((a,b)\\), The mean value theorem shows therefore that
\\[\phi(b)-\phi(a)=(b-a)\phi'(x)=(b-a)z\cdot f'(x)\\]
for some \\(x\in (a,b)\\). On the other hand,
\\[\phi(b)-\phi(a)=z\cdot f(b) - z\cdot f(a)=z\cdot z=\|z\|^2\\]
The Schwarz inequality now gives
\\[\|z\|^2 = (b-a)\|z\cdot f'(x)\|\leq (b-a)\|z\|\|f'(x)\|\\]
Hence \\(\|z\|\leq (b-a)\|f'(x)\|\\), which is the desired conclusion.


References
* (DA): 맛있는 해석학 4판, 김백진
* (PMA): Walter Rudin, Principle of Mathmatical Analysis

Next:  

