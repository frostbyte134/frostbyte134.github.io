---
layout: post
title:  "Hessian and matrix"
date:   2018-05-13 11:34:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra need_revise
---
links, convexity
    
__Hessian__ of a function \\(f: R^n \mapsto R \\) fits into a __square matrix__ \\(R^\{n\times n\}\\) by \\[
\begin{bmatrix}{}
	dx\_1 && ... && dx\_n
\end{bmatrix}
=
\begin{bmatrix}{}
	\frac\{df\}\{dx\_1 dx\_1\} && \frac\{df\}\{dx\_1 dx\_2\} && ... \\\
	\frac\{df\}\{dx\_2 dx\_1\} && ... && ... \\\
	... && ... && ... \\\
\end{bmatrix}
\begin{bmatrix}{}
	dx\_1 \\\ \vdots \\\ dx\_n
\end{bmatrix}
= \sum\_\{i=1\}^\{n\}\sum\_\{j=1\}^\{n\}dx\_i\frac\{df\}\{dx\_idx\_j\}dx\_j
\\]

### Continuous function
If \\(f\\) is continuous, then\\[dx\_i\frac\{df\}\{dx\_idx\_j\}dx\_j=dx\_j\frac\{df\}\{dx\_jdx\_i\}dx\_i,\\]
(link??) so the Hessian is symmetric (with real eigenvalues) (link)

### Minimum point and Hessian
At a stationary point \\(x\in R^n,\\>f'(x)=0\\) by the definition. To test whether \\(x\\) is the minimum, we use the Taylor expansion\\[f(y)=f(x)+(f'(x))^T(y-x)+\frac\{\(y-x)^Tf'' (x)(y-x)}\{2!\}+o(y-x),\\>\forall x\in R^n\\]
where \\(o(y-x)\\) is negligible (link to taylor expansion). Positive definiteness of hessian gives \\[f`` (x)>0\\]so that
\\[f(y)-f(x)>0\\>\forall x\in R^n\\]

### convexity
...

