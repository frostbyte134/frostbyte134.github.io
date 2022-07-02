---
layout: post
title:  "Projection (Least square)"
date:   2018-05-16 09:36:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---


<h3 id="one-dim-proj">Projection (1-dimensional)</h3>
Preliminary: <a href="{{site.url}}/analysis/2018/04/03/vector-projection.html#proj_on_line" target="_blank">Projection onto a line</a>  
On above, projection of a vector \\(b\\) over \\(a\\) was \\(\frac\{a^Tb\}\{a^Ta\}a\\).
By rearranging,\\[\frac\{a^T b\}\{a^T a\}a=a\frac\{a^T b\}\{a^T a\}=\frac\{(aa^T)\}\{a^T a\}b=Pb,\quad \text\{where  \} P=\frac\{aa^T\}\{a^T a\}\\]
\\(P\\) is called a `Projection matrix`. It has two properties.
1. \\(P\\) is symmetric \\((aa^T)^T=(a^T)^Ta^T=aa^T\\).
2. \\(P^N=P\\) (Projection onto itself is itself)
3. P has <a href="{{site.url}}/linear_algebra/2018/05/09/rank.html#rank_bottleneck" target="_blank">rank 1</a>, and is __positive definite__.

<h3 id="least_square">General Projection (Least-square)</h3>
So called `least square` problem in \\(Ax=b,\\>A\in R^\{n\times n\}\\) is, finding the projection \\(A\hat\{x\}\\) of \\(b\\) over the space spanned by the columns of \\(A\\).

\\(Ax=b\\) may has solution(s) or not, and the failure is almost certain when \\(m\gg n\\). 
{:.acounter}
1. 1-dimensional case (Too many equations, too few variable)  
\\[ax=b\quad\rightarrow\quad
\begin\{bmatrix\}\{\}
2 \cr 3 \cr 4
\end\{bmatrix\}
[x\]=
\begin\{bmatrix\}\{\}
b_1 \cr b_2 \cr b_3
\end\{bmatrix\}\quad\rightarrow\quad
\textrm\{Too many equations, too few variables\}
\\]
One good way to get approximate solution is, minimizing the squared error.
\\[E^2:=\frac\{1\}\{2\}\{(2x+b_1)^2+(3x+b_2)^2+(4x+b_3)^2\}\\]
using plane calculus, from the 1st order optimality condition we obtain
\\[\frac\{dE^2\}\{d\}=2(2x+b)+3(3x+b_2)+4(4x+b_3)=0\\]
\\[\rightarrow x=\frac\{2b_1+3b_2+4b_3\}\{2^2+3^2+4^2\}=\frac\{a^Tb\}\{a^Ta\}\\]
So that, the least square to a one-variable problem \\(ax=b\\) is, \\(\hat\{x\}=\frac\{a^Tb\}\{a^Ta\}\\), which was a one-dimensional projection onto 1-column matrix \\(A\\).
2. General case  
We initially had \\(Ax=b\\) which might not be unsolvable. Instead we use the tool of linear algebra or calculus to obtain a reasonable \\(\hat\{x\}\\).  
In calculus case, the __scalar error__ is \\(E^2(x):=\frac\{1\}\{2\}\\|Axb\\|^2\\), a distance in \\(R^n\\).
Finding \\(\hat\{x\}\\) which minimizes \\(\frac\{1\}\{2\}\\|Ax-b\\|^2\\) is, equivalent to finding a point \\(A\hat\{x\}\\) in the column space closest to \\(b\\) (projection!) <br/>
<img src="{{ site.url }}/nailbrainz.github.io/images/math/linear_alg/general_proj.jpg" width="1000" class="center"/>  
In linear algebra case, using orthogonality
\\[\begin\{matrix\}\{\}
a_1^T(b-A\hat\{x\})=0 \cr \vdots \cr a_n^T(b-A\hat\{x\})=0 
\end\{matrix\}
\quad\rightarrow\quad A^T(b-A\hat\{x\})=0\quad\rightarrow\quad A^TA\hat\{x\}=A^Tb.
\\] \\(A^TA\hat\{x\}=A^Tb\\) is known as the `normal equation`, and \\(A^TA\\) is the `normal matrix` (__link???__)  
When \\((A^TA)^\{-1\}\\) exists, \\(\hat\{x\}=(A^TA)^\{-1\}A^Tb\\) and since the projection was \\(p=A\hat\{x\}=Pb\\),
\\[A(A^TA)^\{-1\}A^Tb=Pb\quad\rightarrow\quad P=A(A^TA)^\{-1\}A^T.\\]
{:.acounter}
  
Few remarks are,  
* \\(A^TA\\) is invertible only when columns of \\(A\\) are independent <a href="{{site.url}}/linear_algebra/2018/05/10/cross-prod-mat.html" target="_blank">(link)</a>.
* If \\(b\\) is in the columnspace of \\(A\\) \\((b=Ax')\\), then projection of \\(b\\) is \\(b\\) itself\\[p=Pb=A(A^TA)^\{-1\}A^TAx'=Ax'=b\\] When \\(A\\) is square and invertible, then every vector projects to itself.
* In `Least-square regression`, a row corresponds to a data point.
<h3 id="other_proj_mat">Two Projection matrices P and I-P</h3>
We saw that, \\(P=A(A^T A)^\{-1\} A^T\\) projects `any` b into the columnspace of \\(A\\), by \\(p=Pb\\).
What \\(P\\) does is decomposing b into
1. \\(Pb\\), which is the component Parallel to the column space of \\(A\\)
2. And \\((b-Pb)\\), which is the component orthogonal to the column space of \\(A\\).
Thus, from below equation
\\[b-Pb=(I-P)b\\]
we see that 
\\[I-P=I-A(A^T A)^\{-1\} A^T\\]
is an another projection matrix, which projects b into the left nullspace of \\(A\\).
