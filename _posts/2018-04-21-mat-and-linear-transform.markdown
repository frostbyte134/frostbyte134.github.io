---
layout: post
title:  "Matrix and linear transformation"
date:   2018-04-21 17:26:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---

<h3 id="linear_transform_to_mat">(1) Linear transformation to matrix</h3>
Suppose that,  
\\(  \\{ x_{1}, \ldots ,x_{n} \\}  \\) is a basis of  \\(n\\)-dimensional vector space \\(X\\), and  
\\(  \\{ y_{1}, \ldots ,y_{m} \\}  \\) is a basis of \\(m\\)-dimensional vector space \\(Y\\).

Then, every `linear transformation` \\(A\in L(R^n,R^m)\\) induces a set of \\(m\times n\\) numbers \\(a_{ij}\\) which compose a `matrix` \\([A]\in R^{m\times n}\\) by  
\\[A\left( \begin{bmatrix}
x_{1}  &   \ldots   &  x_{n} \cr
\end{bmatrix}
 \right) = [ \begin{matrix}
y_{1}  &   \ldots   &  y_{m} \cr
\end{matrix}
 ] [ A ].\\]
By applying linear transformation \\(A\\) to \\(x\_j\\) we see that in columnwise,  
\\[ A(x\_{j})= \sum\_{i=1}^{m}a\_{ij}y\_{i}
= \begin{bmatrix}
\sum\_{i=1}^{m}a\_{ij}(y\_{i})\_1 + ... + \sum\_{i=1}^{m}a\_{ij}(y\_{i})\_1 \cr
\cdots \cr
\sum\_{i=1}^{m}a\_{ij}(y\_{i})\_n + ... + \sum\_{i=1}^{m}a\_{ij}(y\_{i})\_n
\end{bmatrix}
\\]
We see that \\([A]\_{pq}=\sum\_{i=1}^{m}a\_{iq}(y\_{i})\_p + ... + \sum\_{i=1}^{m}a_{iq}(y_{i})\_p \\).

It is trivial (in theory) to determine \\(a\_{ij}\\), by \\[ A(x\_j)=Y \begin{bmatrix} a\_{1j} \cr \vdots \cr a\_{mj} \end{bmatrix} \rightarrow Y^{-1}A(x\_j)= \begin{bmatrix} a\_{1j} \cr \vdots \cr a\_{mj} \end{bmatrix}\\] ( \\(Y\\) is a non-singular matrix, by its construction) so that, `consequently`,
\\[ [A]=Y^{-1}[A(x\_1),...,A(x\_n)]\\]
  
  
For arbitrary  \\( \vec\{x\} \in R^{n} \\) ,  \\( \textbf{x}= \sum\_{j=1}^{m}c\_{j}x\_{j} \\) and (not particularly unique)  \\( \vec\{y\}=A\textbf{x} \\),

 \\[ A\textbf{x}= [ A ]  \begin{bmatrix}
x\_{1}  &   \ldots   &  x\_{n} \cr
\end{bmatrix}
  \begin{bmatrix}
c\_{1} \cr
 \ldots \cr
c\_{n} \cr
\end{bmatrix}
  = [ \begin{matrix}
y\_{1}  &   \ldots   &  y\_{m} \cr
\end{matrix}
 ]  [ A ]  \begin{bmatrix}
c\_{1} \cr
 \ldots \cr
c\_{n} \cr
\end{bmatrix}
 = [ \begin{matrix}
y\_{1}  &   \ldots   &  y\_{m} \cr
\end{matrix}
 ]   \begin{bmatrix}
 \sum\_{j=1}^{n}a\_{1j}c\_{j}\cr
 \ldots \cr
 \sum\_{j=1}^{n}a\_{mj}c\_{j}\cr
\end{bmatrix}
   \\]  \\[ = \sum\_{i=1}^{m} \(  \sum\_{j=1}^{n}a\_{ij}c\_{j} \) y\_{i} \\] 
The coordinate (remember that  \\( y\_{i} \\) s are bases) of  \\( Ax \\)  in terms of  \\( y\_{i} \\)  is  \\(  \sum\_{j=1}^{n}a\_{ij}c\_{j} \\).
  
  
#### Therefore, when we state \\(y=Ax\\) indeed we are transforming coordinates \\(y, x\\) with respect to a basis \\(X\\) hidden in \\(A\\).


### (2) Matrix to linear transformation
Conversely, a matrix  \\(  [ A ]  \in R^{m \times n} \\)  induces a linear transformation  \\( A \in L \( R^{n},R^{m} \)  \\) by,

for arbitrary \\(\vec\{x\}\in R^n\\), \\[  A(\textbf{x})=[A]\textbf{x}= \sum\_{i=1}^{m} \(  \sum\_{j=1}^{n}a\_{ij}c\_{j} \) y\_{i}\\] (Above relation)

<h3 id="change_of_basis_mat">(3) Change of basis as a matrix</h3>
In \\(R^n\\), we want to change the basis from \\(X\\) to \\(Q\\). With the conclusion in `(1)`, the corresponding matrix is
\\[ [A]=Q^{-1}[A(x\_1),...,A(x\_n)]\\]

### (4) A Bound to the matrix norm
Additionally, suppose  \\(  \\{ x\_{1}, \ldots ,x\_{n} \\}  \\)  and  \\(  \\{ y\_{1}, \ldots ,y\_{m} \\}  \\)  are standard basis of  \\( X \\)  and  \\( Y \\).

Remember that  \\( A \\)  is given by,

 \\[ Ax= \sum\_{i=1}^{m} \(  \sum\_{j=1}^{n}a_{ij}c\_{j} \) y\_{i} \\] then
 \\[  \vert Ax \vert = \(  \langle Ax,Ax \rangle  \) ^{1/2}=\sqrt[]{ \sum\_{i=1}^{m} \(  \sum\_{j=1}^{n}a\_{ij}c\_{j} \) ^{2}y\_{i}^{T}y\_{i}}=\sqrt[]{ \sum\_{i=1}^{m} \(  \sum\_{j=1}^{n}a\_{ij}c\_{j} \) ^{2}} \\] so that, by the term-by-term Cauchy-Schwarz,
 \\[  \vert Ax \vert ^{2}= \sum\_{i=1}^{m} \(  \sum\_{j=1}^{n}a\_{ij}c\_{j} \) ^{2} \leq  \sum\_{i=1}^{m} \(  \sum\_{j=1}^{n}a\_{ij}^{2} \)  \(  \sum\_{j=1}^{n}c\_{j}^{2} \) = \sum\_{i=1}^{m} \(  \sum\_{j=1}^{n}a\_{ij}^{2} \)  \vert x \vert = \sum\_{i,j}^{}a\_{ij}^{2} \vert x \vert ^{2} \\] and maximizing both sides under  \\(  \vert x \vert  \leq 1 \\),
 \\[  \Vert A \Vert  \leq  \(  \sum\_{i,j}^{}a\_{ij}^{2} \) ^{1/2} \\]