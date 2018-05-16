---
layout: post
title:  "Orthonormal basis"
date:   2018-05-15 18:16:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra need_revise
---
A set of vectors \\(\{q_1,...,q_n\}\\) are orthonormal if
\\[q_i^Tq_j
\begin{cases}
    0 & \text\{if \} i \neq j \\\
    1 & \text\{if \} i = j
\end{cases}
\\]
A matrix composed of orthonormal basis is generally denoted \\(Q\\).  
Properties of \\(Q\\) are,
1. \\(Q^TQ=I\\).  
\\(\rightarrow\\) If \\(Q\in R^n\\) \\(Q^T\\) is a left inverse, and <a href = "{{site.url}}/linear_algebra/2018/05/10/left-inverse-is-the-right-inverse.html" target="_blank">thanks to the statements here</a>, \\(Q^T\\) is also a right inverse.
2. \\(\\| Qx\\| =\\| x\\| \\), since \\[{\\| Qx\\|}^2=x^TQ^TQx=x^Tx={\\| x\\|}^2\\]
Therefore, __multiplication by__ \\(Q\\) __preserves length.__

### Orthonormal Basis
Finding coefficients of orthonormal basis is extremely simple.  
Let  \\(\{q_1,...,q_n\}\\) be an orthonormal basis in \\(R^n\\).  
Consider an arbitrary vector in \\(R^n,\\>b=c_1q_1+\cdots+c_nq_n\quad\rightarrow\quad Qc=b.\\)  
By multiplying \\(q_i\\) on both sides, \\[b^Tq_i=c_iq_i^Tq_i\quad\rightarrow\quad c_i=\frac\{b^Tq_i\}\{q_i^Tq_i\}\\]
(__after projection review__) Remember that, \\(\frac\{a^Tb\}\{a^Ta\}\\) is the 1-dimensional projection of \\(b\\) onto the line spanned by \\(a\\). Thus we can interpret𝑐\\(c_i\\)𝑖as a projection of \\(b\\)𝑏onto the line spanned by \\(q_i\\)𝑖. 
If we have insufficient orthogonal vectors 𝑞1,…,𝑞𝑟,𝑟<𝑛, then 
𝑄𝑥=𝑏
might not have answer, and the problem indeed becomes projection.
AFTER PROJECTION!