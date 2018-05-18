---
layout: post
title:  "Hermitian matrices and Spectral theorem"
date:   2018-05-18 15:02:00 +0900
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
	> Schur's lemma tommorow!!!!
	
	`proof`: whatever
{:.deccounter}
### Complex inner product space
We see that \\[\textrm\{\}\\]

### Hermitian 



Next: Normal matrix

Link:
<a href="http://www.math.umd.edu/~hking/Hermitian.pdf" target="_blank">http://www.math.umd.edu/~hking/Hermitian.pdf</a>  

