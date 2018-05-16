---
layout: post
title:  "Projection (Least square)"
date:   2018-05-16 09:36:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
<ol>
<li>1</li>
<li>2</li>\\(what the\\)
</ol>


### Projection (1-dimensional)
Preliminary: <a href="{{site.url}}/analysis/2018/04/03/vector-projection.html#proj_on_line" target="_blank">Projection onto a line</a>  
On above, projection of a vector \\(b\\) over \\(a\\) was \\(\frac\{a^Tb\}\{a^Ta\}a\\).
By rearranging,\\[\frac\{a^T b\}\{a^T a\}a=a\frac\{a^T b\}\{a^T a\}=\frac\{(aa^T)\}\{a^T a\}b=Pb,\quad \text\{where  \} P=\frac\{aa^T\}\{a^T a\}\\]
\\(P\\) is called a `Projection matrix`. It has two properties.
1. \\(P\\) is symmetric \\((aa^T)^T=(a^T)^Ta^T=aa^T\\).
2. \\(P^N=P\\) (Projection onto itself is itself)
3. P has __rank 1__ <a href="{{site.url}}/linear_algebra/2018/05/09/rank.html#rank_bottleneck" target="_blank">(link)</a>, and is __positive definite__.

<h3 id="least_square">Least square</h3>
So called `least square` problem in \\(Ax=b,\\>A\in R^\{n\times n\}\\) is, finding the projection \\(A\hat\{x\}\\) of \\(b\\) over the space spanned by the columns of \\(A\\).

\\(Ax=b\\) may has solution(s) or not, and the failure is almost certain when \\(m\gg n\\). 
{:.acounter}
1. 1-dimensional case (Too many equations, too few variable)  
\\[ax=b\quad\rightarrow\quad
\begin\{bmatrix\}\{\}
2 \\\ 3 \\\ 4
\end\{bmatrix\}
[x\]=
\begin\{bmatrix\}\{\}
b_1 \\\ b_2 \\\ b_3
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
Again, the __scalar error__ is \\(E^2(x):=\frac\{1\}\{2\}\\|Axb\\|^2\\), a distance in \\(R^n\\).
Finding \\(\hat\{x\}\\) which minimizes \\(\frac\{1\}\{2\}\\|Ax-b\\|^2\\) is, equivalent to finding a point \\(A\hat\{x\}\\) in the column space closest to \\(b\\) (projection!)   
![angle]({{ site.url }}/images/math/linear_alg/general_proj.jpg){: .center-image }  
\\[\begin\{matrix\}\{\}
a_1^T(b-A\hat\{x\}=0 \\\ \vdots \\\ a_n^T(b-A\hat\{x\}=0 
\end\{matrix\}
\quad\rightarrow\quad A^T(b-A\hat\{x\})=0\quad\rightarrow\quad A^TA\hat\{x\}=A^Tb.
\\] \\(A^TA\hat\{x\}=A^Tb\\) is known as the `normal equation`, and \\(A^TA\\) is the `normal matrix` (__link???__)
{:.acounter}

Few remarks are,  
* \\(A^TA\\) is invertible only when columns of \\(A\\) are independent.
* If \\(b\\) is in the columnspace of \\(A\\) \\((b=Ax')\\), then projection of \\(b\\) is \\(b\\) itself\\[p=Pb=A(A^TA)^-1A^TAx'=Ax'=b\\] When \\(A\\) is square and invertible, then every vector projects to itself.

<h3 id="other_proj_mat">Two Projection matrices P and I-P</h3>
We saw that, \\(P=A(A^T A)^\{-1\} A^T\\) projects `any` b into the columnspace of \\(A\\), by \\(p=Pb\\).
What \\(P\\) does is decomposing b into
1. \\(pb\\), which is the component Parallel to the column space of \\(A\\)
2. And \\((b-Pb)\\), which is the component orthogonal to the column space of \\(A\\).
Thus, from below equation
\\[b-Pb=(I-P)b\\]
we see that 
\\[I-P=I-A(A^T A)^\{-1\} A^T\\]
is an another projection matrix, which projects b into the left nullspace of \\(A\\).
