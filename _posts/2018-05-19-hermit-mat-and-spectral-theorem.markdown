---
layout: post
title:  "Hermitian matrices and Spectral theorem"
date:   2018-05-19 15:02:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra need_revise
---

<h3 id="hermit_mat">Definition: Hermitian matrices</h3>
Based on the <a href="{{site.url}}/linear_algebra/2018/05/18/complex-inner-prod.html#hermit_inner_prod" target="_blank">definition of complex conjugate and Hermitian inner product,</a>  
We say that \\(A\in\mathbb\{C\}^\{n\times n\}\\) is Hermitian if
\\[A^*=\overline\{A\}^T=A.\\]
* Diaginal entries must be real
* above-diagonal entries are conjugate to corresponding below-diagonal entries
* \\(\textrm\{Symmetric matrices\}\subset\textrm\{Hermitian matrices\}\\)

### Preliminaries of Spectral theorem (Schur's Lemma)

{:.deccounter}
1. Theorem 1  
	> If \\(T:V\mapsto V\\) is a linear transformation(operator) of a nontrivial finite dimensional complex vectors space \\(V\in\mathbb\{C\}^n\\), then \\(T\\) has an eigenvector.  
	
	`proof`:
	Let \\(A\\) be a <a href="{{site.url}}/linear_algebra/2018/04/21/mat-and-linear-transform.html" target="_blank">matrix corresponding</a> to \\(T\\). Since \\(V\\) is nontrivial, \\(n>0\\). Then the characteristic equation of \\(A\\) has at least one root, so \\(A\\) has at least one eigenpair.
2. Definition of <a href="{{site.url}}/linear_algebra/2018/05/15/orthonormal-basis.html#unitray_mat">Unitary matrices</a>
3. Product of two unitary matrices is unitary
\\(\rightarrow\\) <a href="{{site.url}}/linear_algebra/2018/05/15/orthonormal-basis.html#properties_of_orthonormal">(5) here</a> + (Orthonormal matrices are subset of unitary).
4. Schur's Lemma
	> If \\(A\\) is __any__ square complex matrix,  then there is an upper triangular complex matrix \\(T\\) and a unitary \\(U\\) such that  
	\\[A=UTU^*=UTU^\{-1\}\\]
	
	`proof`: Let \\(q_1\\) be an eigenvector of \\(A\\), which is guaranteed to be exists by `(1)`. By the <a href="{{site.url}}/linear_algebra/2018/05/15/orthonormal-basis.html#gram_schmidt"  target="_blank">Gram-Schmidt process</a> we may choose any \\(q'_i\\) such that \\(\\{q_1,...,q'_n\\}\\) is an orthonormal basis.  
	Let \\(Q_0:=[q_1,..,q_n]\in\mathbb\{C\}^\{n\times n\}\\). Then \\(Q_0\\) is unitary, and \\(\{Q\_0\}^\* A Q\_0=\begin\{bmatrix\}\{\} \lambda_1 && * \\\ 0 && A\_2 \end\{bmatrix\}\\) for some \\((n-1)\times(n-1)\\) matrix \\(A_2\\).  
	Likewise, we may find a unitary \\((n-1)\times(n-1)\\) matrix \\(Q_1\\) so that \\(Q_1^\*A_1Q_1=\begin\{bmatrix\}\{\} \lambda_2 && * \\\ 0 && A_3 \end\{bmatrix\}\\) for \\((n-2)\times (n-2)\\) matrix \\(A_3\\). Then we see that \\[Q_0^\*AQ_0=\begin\{bmatrix\}\{\} \lambda_1 && * \\\ 0 && A_2 \end\{bmatrix\}\\] \\[Q_1^\*Q_0^\*AQ_0Q_1=\begin\{bmatrix\}\{\} \lambda_1 && * && * \\\ 0 && \lambda_2 && * \\\ 0 && 0 && A_3 \end\{bmatrix\}\\] for some \\((n-2)\times(n-2)\\) matrix \\(A_3\\). The process continues till \\[(Q_n^\*\cdots Q_0^\*) A (Q_0 \cdots Q_n)=T\\] where \\(T\\) is \\(n\times n\\) upper triangular matrix with eigenvalues of \\(A\\) in diagonal, and \\(U:=Q_n\cdots Q_0\\) is unitary thanks to `(3)`. Finally we see that \\[A=UTU^\*\\] holds.
{:.deccounter}

<h3 id="spectral_theorem">Spectral theorem</h3>



Next: Normal matrix

Link:
<a href="http://www.math.umd.edu/~hking/Hermitian.pdf" target="_blank">http://www.math.umd.edu/~hking/Hermitian.pdf</a>  

