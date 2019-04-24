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
2. derivative of a function \\(f\\) is defined as a limit of the function\\(\phi\\). 
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
\\[f(t)-f(x)=[f'(x)-u(t)](t-x)\tag\{4\}\\]
\\[g(s)-g(y)=[g'(y)-v(s)](s-y)\tag\{5\}\\]
where \\(t\in [a,b],\\ s\in I\\), and \\(\lim\_\{t\rightarrow x\}u(t)=0,\\ \lim\_\{s\rightarrow y\}v(s)=0\\).  
Let \\(s=f(t)\\). Using first (5) and then (4) we obtain
\\[h(t)-h(x)=g(f(t))-g(f(x))\\]
\\[=[f(t)-f(x)][g'(y)+v(s)]\\]
\\[=(t-x)[f'(x)-u(t)][g'(y)+v(s)]\\]
or, if \\(t\neq x\\),
\\[\frac\{h(t)-h(x)\}\{t-x\}=[g'(y)+v(s)][f'(x)-u(t)]\\]

Note that, by the continuity (and continuity of the composed functions), \\[\lim\_\{t\rightarrow x\}v(f(t))=0.\\]so that the rhs of (6) tends to \\(g'(y)f'(x)\\).

### Mean value theorems


References
* (DA): 맛있는 해석학 4판, 김백진
* (PMA): Walter Rudin, Principle of Mathmatical Analysis

Next:  

