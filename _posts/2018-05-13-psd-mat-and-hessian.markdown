---
layout: post
title:  "Jacobian and Hessian "
date:   2018-05-13 11:34:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra analysis optimization need_revise
---
links, convexity


<h3 id="jacobian">Jacobian</h3>
`Jacobian` of a function \\(f(x):R^n\mapsto R^m\\) is a \\(m\times n\\) matrix (<a href="{{site.url}}/linear_algebra/2018/04/21/mat-and-linear-transform.html" target="_blank">linear transformation</a>) such that \\(J_\{i,j\}=\frac\{\partial\}\{\partial x\_j\}(f(x)\_i)\\).

Using \\(J\\), we can calculate how \\(u=f(x)\in R^m\\) changes with respect to unit change in \\(x\in R^n\\).
\\[
\begin{bmatrix}\{\}
\frac\{\partial f(x)\_1\}\{\partial dx_1\} && ... && \frac\{\partial f(x)\_1\}\{\partial dx_n\} \cr
\vdots && \vdots && \vdots \cr
\frac\{\partial f(x)\_m\}\{\partial du_1\} && ... && \frac\{\partial f(x)\_m\}\{\partial dx_n\} \cr
\end\{bmatrix\}
\begin{bmatrix}\{\}
dx_1 \cr
\vdots  \cr
dx_n \cr
\end\{bmatrix\}
=
\begin{bmatrix}\{\}
\sum_\{i=1\}^n \frac\{\partial f(x)\_1\}\{\partial x_i\}dx_i \cr
\vdots  \cr
\sum_\{i=1\}^n \frac\{\partial f(x)\_m\}\{\partial x_i\}dx_i \cr
\end\{bmatrix\}
=
\begin{bmatrix}\{\}
\frac\{\partial f(x)\_1\}\{\partial x\} \cr
\vdots  \cr
\frac\{\partial f(x)\_1\}\{\partial x\}
\end\{bmatrix\}
\\]


<h3 id="jacobian">Jacobian and change of variable</h3>
Let \\(x=g(\textbf\{u\})\\) for \\(g:R^n\mapsto R^n\\). We want to change coordinates from \\(\textbf\{x\}\\) to \\(\textbf\{u\}\\) (note the order). Famous example in \\(n=2\\) is a change to polar coordinate.
\\[
\begin{bmatrix}\{\}
x \cr
y 
\end\{bmatrix\}
=
\begin{bmatrix}\{\}
r\cos\theta \cr
r\sin\theta 
\end\{bmatrix\}
\\]

In above example, suppose we want to perform integral over some region \\(R\\). After the coordinate change, \\(R\mapsto G\\) and
\\[\int\int_R g(\textbf\{x\})d\textbf\{x\} = \int\int_S f(g(\textbf\{u\}))\|J\|d\textbf\{u\}\\]
where \\(J=
\begin{bmatrix}\{\}
\frac\{\partial x\}\{\partial r\} && \frac\{\partial x\}\{\partial \theta\} \cr
\frac\{\partial y\}\{\partial r\} && \frac\{\partial y\}\{\partial \theta\}
\end\{bmatrix\}
=
\begin{bmatrix}\{\}
\cos\theta && -r\sin\theta \cr
\sin\theta && r\cos\theta
\end\{bmatrix\}
\\)

Reason why we multiply determinant:
1. determinant is a size of parallelogram with rows (or columns), or size of the unit cude after the transformation
2. Riemann integral is done wrt unit cube (__link, analysis!__)

If we want to recover a cube with specific size in the coordinate system of \\(x\\) using the rate of change in the coordinate system of \\(u\\), we have to multiply \\(\|J\|\\).

<h3 id="hessian">Hessian</h3>

__Hessian__ \\(H\\) of a function \\(f: R^n \mapsto R \\) fits into a __square matrix__ \\(R^\{n\times n\}\\) by \\[
\begin{bmatrix}{}
	dx\_1 && ... && dx\_n
\end{bmatrix}
=
\begin{bmatrix}{}
	\frac\{df\}\{dx\_1 dx\_1\} && \frac\{df\}\{dx\_1 dx\_2\} && ... \cr
	\frac\{df\}\{dx\_2 dx\_1\} && ... && ... \cr
	... && ... && ... \cr
\end{bmatrix}
\begin{bmatrix}{}
	dx\_1 \cr \vdots \cr dx\_n
\end{bmatrix}
= \sum\_\{i=1\}^\{n\}\sum\_\{j=1\}^\{n\}dx\_i\frac\{df\}\{dx\_idx\_j\}dx\_j
\\]
Equivalently, Hessian is the Jacobian of the gradient function (if exists).

Anywhere that the 2nd partial derivatives are continuous, the differential operators are commutative (link????). That is, \\[dx\_i\frac\{df\}\{dx\_idx\_j\}dx\_j=dx\_j\frac\{df\}\{dx\_jdx\_i\}dx\_i,\\]
(link??) so the Hessian is symmetric (with real eigenvalues, by the <a href="{{site.url}}/linear_algebra/2018/05/19/hermit-mat-and-spectral-theorem.html#spectral_theorem" target="_blank">spectral theorem</a>)

The 2nd derivative in a specific direction, represented by a unit vector \\(d\\) is given by \\(d^THd\\).
1. When \\(d\\) is an (orthonormal) eigenvector, the 2nd derivative toward that direction is the eigenvalue correspoding to \\(d\\).
2. When \\(d\\) is an arbitrary unit vector, then by the <a href="{{site.url}}/linear_algebra/2018/05/19/hermit-mat-and-spectral-theorem.html#spectral_theorem" target="_blank">spectral decomposition</a>, \\[d^THd=d^TQ\Lambda Q^Td^T=d^T(\sum_\{i=1\}^n\lambda_iq_iq_i^T)d=\sum_\{i=1\}^n\lambda_i(q_i^Td)^2\\]
You can see that, the `directional second derivative` \\(f\'\'(d)\\) is the weighted average of all the eigenvalues, with weights \\((q_i^Td)^2\\) between 0 and 1, and eigenvectors that have a smaller angle with \\(d\\) recieving more weight (thanks to <a href="{{site.url}}/analysis/2018/04/03/vector-projection.html" target="_blank">cos - cross product relation</a>)



### convexity of a functin and hessian
put contents in other posts. just post a link 
...

