---
layout: post
title:  "Normal matrix"
date:   2018-05-10 16:05:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---

### Definition
A matrix \\(N\\) is normal, if it commutes with \\(N^H\\): \\[NN^H=N^HN.\\]


<h3 id="normal_and_spectral">Normal matrices have full set of orthonormal eigenvectors</h3>
We prove the above by showing that we can apply the spectral theorem to the normal matrics, and obtaining full rank of unitary eigenvector matrix \\(U\\).
>Normal matrices are exactly those that the <a href="{{site.url}}/linear_algebra/2018/05/19/hermit-mat-and-spectral-theorem.html#spectral_theorem" target="_blank">`Spectral decomposition`</a> can be applied  


To apply the spectral decomposition using the Schur's theorem, its triangular form must be diagonal.  
`proofs`:  
1. If \\(N\\) is normal, then so as its triangle form \\(T=U^HTU\\) in <a href="{{site.url}}/linear_algebra/2018/05/19/hermit-mat-and-spectral-theorem.html#schur_lemma" target="_blank">`Schur's lemma`.</a>
\\[TT^H=U^HNN^HU=U^HN^HNU=T^HT.\\]
2. A triangular \\(T\\) which is normal, must be diagonal.
Proof by induction.    

__Base case__: Let \\(n=2\\). WLOG let \\[T=\begin\{bmatrix\} a && 0 \\\ b && c \end\{bmatrix\}.\\] Then \\(\\>T^HT-TT^H=0\\) gives 
\\[T=
\begin\{bmatrix\}
|b|^2 && \bar\{b\}c-a\bar\{b\} \\\ 
\bar\{c\}b-b\bar\{a\} && -|b|^2 
\end\{bmatrix\}=0
\\] so \\(b=0\\) and \\(T\in \mathbb\{R\}^\{2\times 2\}\\) must be diagonal.

__Inductive step__: For \\(n\leq 2\\), suppose that the theorem holds for \\(n\\). Let \\[T_\{n+1\}=\begin\{bmatrix\} T && 0 \\\ v && a \end\{bmatrix\}.\\] be an arbitrary triangular matrix in \\(\mathbb\{C\}^\{(n+1)\times(n+1)\}\\), where \\(T\\) is an (normal, by assumption) triangular matrix in \\(\mathbb\{C\}^\{n\times n\},\\>v\in \mathbb\{C\}^\{1\times n\},\\>a\in\mathbb\{C\}.\\) Then \\(T_\{n+1\}^HT_\{n+1\}-T_\{n+1\}T_\{n+1\}^H=0\\) gives
\\[
\begin\{bmatrix\} T^HT-TT^* + v^Hv && v^Ha-Tv^H \\\ \bar\{a\}v-vT^H && -|v|^2 \end\{bmatrix\}
=\begin\{bmatrix\} 0 + \\|v\\|^2 && v^Ha-Tv^H \\\ \bar\{a\}v-vT^H && -\\|v\\|^2 \end\{bmatrix\}
=0
\\]
Hence \\(v=0\\) and since \\(T\\) is diagonal, \\(T_\{n+1\}\\) is also diagonal.

<h3 id="share_null">Normal matrix and original matrix share nullspace</h3>
For any matrix \\(A\\), \\(AA^T\\) or \\(A^TA\\) is normal. Then \\(A^TA\\) has the same nullspace as \\(A\\). Indeed,
\\[Ax=0\rightarrow A^T Ax=0\\]
is obvious. To prove the converse,
\\[A^T Ax=0\quad\rightarrow\quad x^T A^T Ax=0\quad\rightarrow\quad (Ax)^T (Ax)=\||Ax\||^2=0\quad\rightarrow\quad Ax=0.\\]
* If the columns of A are independent \\(\left(\textrm\{rank\}A=n\right)\\)) then \\(N(A)=\\{0\\}\\), \\(N(A^TA)=\\{0\\}\\) holds so that \\(A^TA\\) is invertible.


### Normal matrix is positive definite
