---
layout: post
title:  "Sum and series"
date:   2018-08-23 08:00:05 +0800
categories: deep_learning
use_math: true
tags: probability analysis
---

### Series (of a function)

\\[\sum_\{a\in A\}f(a)\tag\{1\}\\]
is a _formal symbol_, and one has to define its meaning carefully. This symbol is called a `series`.

If \\(A\\) is __a finite set__, then the natural definition of (1) would be
\\[\sum_\{a\in A\}f(a)=f(a\_1)+f(a\_2)+\cdots+f(a\_n)\tag\{2\}\\]
In this case, (1) is well defined by the __commutative and associative__ laws of addition (is independent of the ways we number and group the elements \\(a_1,...,a_n\\)); if it were not, (2) would not be a legitimate definition.

With the sets of infinite cardinality, the story gets complicated.  
If \\(f(a)\geq 0\\>\\>\forall a\in A\\), then we can safely define
\\[\sum_\{a\in A\}f(a)=\lim_\{n\rightarrow\infty\}\[f(a_1)+\cdots+f(a_n)\]\tag\{4\}\\] 
Clearly the inner term of rhs monotonically increases as \\(n\\) increases, so the limit exists (to \\(\infty\\) or to some number). Moreover, it turns out that the RHS is independent of the ways we number the elements of \\(A\\) (which we will prove now), so (4) is indeed a legitimate definiton with such strong assumption.  

> __proof__: for any arbitrary ordering \\(\\{a_1,...,a_n,a_\{n+1\},...\\}\\), for any \\(n\geq1\\) there exists some \\(m\geq1\\) such that (since \\(n\\) is finite, the sum till \\(n\\) is also finite)
\\[\\{a_1,...,a_n\\}\subset\\{b_1,...,b_m\\}\\]
so that, 
\\[f(a_1)+...+f(a_n)\leq f(b_1)+...+f(b_m)\leq \lim\_\{k\rightarrow\infty\}f(b_1)+...+f(b_k)\\]
if the 1st relation holds for all \\(n\\), then it also holds for \\(n\rightarrow\\infty\\)
\\[\lim\_\{n\rightarrow\infty\}f(a_1)+...+f(a_n)\leq \lim\_\{k\rightarrow\infty\}f(b_1)+...+f(b_k)\\]
Now, for reversing the roles of ordering, for any \\(m\geq 1\\) there exists \\(n\geq1\\) such that
\\[\\{a_1,...,a_n\\}\subset\\{b_1,...,b_m\\}\\]
and the proof is complete, by following the same line.

However, without such strong assumption we cannot use above proof, so we introduce new notation.  
For any real numbers \\(k\\), let
\\[k^+=\max\\{k,0\\},\quad k^-=\max\\{-k,0\\}.\\]
Notice that,
\\[k=k^++k^-,\quad\|k\|=k^++k^-.\\]

We extend this notation to functions. Since \\(f=f^+-f^-\\) holds,
\\[\sum\_\{a\in A\}f(a)=\sum\_\{a\in A\}f^+(a)-\sum\_\{a\in A\}f^-(a).\\]
Now suppose that \\(A\\) is `countably infinite` set: \\(A=\\{a_1,a_2,...\\}\\). For _general_ \\(f\\), (4) gives legitimate definitons of
\\[\sum\_\{a\in A\}f^+(a):=\lim\_\{n\rightarrow\infty\}f^+(a_1)+...+f^+(a_n)\\]
and
\\[\sum\_\{a\in A\}f^-(a):=\lim\_\{n\rightarrow\infty\}f^-(a_1)+...+f^-(a_n)\\]
by the above proof.  

__Defined / Undefined series__
1. We define (1) for a countably infinite set \\(A\\) by
\\[\sum\_\{a\in A\}f(a):=\sum\_\{a\in A\}f^+(a)-\sum\_\{a\in A\}f^-(a)\\]
__unless__(!!) both sums on the RHS equals to \\(\infty\\), in which case we say that (1) is `undefined`.
2. Whenever (1) is defined (whether finite, or \\(\pm\infty)), we can use the fact that _the limit of a difference equals the difference of the limits_ to obtain
\\[\sum\_\{a\in A\}f(a)=\lim\_\{n\rightarrow\infty\}[f^+(a_1)+...+f^+(a_n)]-\lim\_\{n\rightarrow\infty\}[f^-(a_1)+...+f^-(a_n)]\\]
\\[=\lim\_\{n\rightarrow\infty\}[(f^+(a_1)-f^-(a_1))+...+(f^+(a_n)-f^-(a_n))]\\]
\\[=\lim\_\{n\rightarrow\infty\}[f(a_1)+...+f(a_n)]\\]
(We can treat it without splitting \\(f=f^+-f^-\\))

Some cases we are interested are,
1. Absolutely convergent series  
Notive that \\(\sum\_\{a\in A\}\|f(a)\|\\) is always defined. In case
\\[\sum\_\{a\in A\}f^+(a)+\sum\_\{a\in A\}f^-(a)=\sum\_\{a\in A\}\|f(a)\|<\infty\\]
we say that the series (1) __converges absolutely__, and in this case we easily see that the terms
\\[\sum\_\{a\in A\}\|f(a)\|,\sum\_\{a\in A\}f^+(a),\sum\_\{a\in A\}f^-(a)\\]
are all finite. We are mainly interested in absolutely convergent series. From the above discussion, we see that __(1) is defined as a finite number i.i.f it is absolutely convergent__ (Link in the analysis someday??). Absolutely convergent series, even when they are infinite, __have many properties of finite series__, such as
\\[\sum\_\{a\in A\}kf(a)=k\sum\_\{a\in A\}f(a),\quad \sum\_\{a\in A\}(f(a)+g(a))=\sum\_\{a\in A\}f(a)+\sum\_\{a\in A\}g(a)\\]
2. Divergent series  
If (1) is undefined, or equal to \\(+\infty\\) or \\(-\infty\\), we say it `diverges`.
