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
provided that the limit exists in accordance with <a href="https://nailbrainz.github.io/analysis/2018/12/19/limit.html" target="_blank">its definition</a>.

Note that,
1. We thus associate with the function \\(f\\) a function \\(f'\\) whose domain is the set of points \\(x\\) at which the limit 2 exists. We call \\(f'\\) as the derivative of \\(f\\).
2. derivative of a function \\(f\\) is defined as a limit of the function\\(\phi\\). 
3. `gradient` = transpose of the derivative
4. If \\(f'\\) is defined at a point \\(x\\), we say that \\(f\\) is `differentiable` at \\(x\\) (pointwise property). 
5. It is possible to consider right(left)-hand derivatives, using the definition of right(left) limits.

> __Theorem__ 5.2 (PMA):  
Let \\(f\\) be defined on \\([a,b]\\). If \\(f\\) is differentiable at a point \\(x\in [a,b]\\), then \\(f\\) is continuous at \\([a,b]\\).

__proof__:  
If \\(f\\) is differentiable at \\([a,b]\\), then \\(\forall x\in [a,b],\\ \epsilon > 0, \exists \delta > 0 :\\)
Note that 
\\[f(t)-f(x)=\frac\{f(t)-f(x)\}\{t-x\}(t-x)=\phi(t)(t-x).\\]
As \\(t\rightarrow x,\\ f(t)-f(x)=\phi(t)(t-x)\rightarrow f'(x)\cdot (0)=0\\).  
__The converse is not true__.

References
* (DA): 맛있는 해석학 4판, 김백진
* (PMA): Walter Rudin, Principle of Mathmatical Analysis

Next:  

