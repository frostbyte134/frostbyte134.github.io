---
layout: post
title:  "Positive Definite Matrices"
date:   2018-05-24 09:58:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
### Definition
A \\(n\times n\\) matrix \\(A\\) is positive definite if and only if \\[x^TAx>0\\]for all \\(x>0\in R^n\\).  

<h3 id="test_for_pd_mat">Test for positive definiteness</h3>

{:.acounter}
{:.theorem}
> Following tests are sufficient and necessary condition for the __real symmetric__ \\(A\\) to be positive definite.
1. \\(x^TAx>0\\>\forall \textrm\{ nonzero \} x\in R^n\\) 
2. All eigenvalues are positive
3. All the left upper submatrices \\(A_k\\) have positive determinants
4. All the pivots after the Gaussian elimination (LDU decomposition) are positive
{:.theorem}
{:.acounter}
`proof`.  
`(A)`\\(\rightarrow\\)`(B)`: If \\(x^TAx>0\\), then for an eigenpair \\(\lambda, x\\), \\[Ax=\lambda x\\]\\[x^T Ax=λx^T x>0\\]\\[\quad\rightarrow\quad \lambda>0.\\]
`(B)`\\(\rightarrow\\)`(A)`:  
For eigenvector \\(x\\), \\[x^TAx=\lambda x^Tx>0.\\]  
For non-eigenvector \\(x\\), using Spectral decomposition (\\(A\\) is real symmetric) \\(A=Q\Lambda Q^T\\) where \\(Q\\) is an orthonormal eigenvector matrix of \\(A\\). We can represent \\(x\\) with \\(Q\\) by \\(x=Qc\\), so that\\[x^TAx=c^TQ^TQ\Lambda Q^TQc=\Lambda c^T c>0.\\]
`(A)`\\(\rightarrow\\)`(C)`:  If all \\(λ_i\\)s are positive,  
firstly, since determinant is the product of eigenvalues, \\(\textrm\{det\}⁡A>0\\).  
Since \\(x^T Ax=x_k^T Ax_k>0\\) for lower-zero padded \\(x_k\\), we see \\(A_k\\) is positive definite, which implies positive determinant.  
`(C)`\\(\rightarrow\\)`(D)`: If all \\(\textrm\{det\}A_k\\) are positive, 
according to the <a href="{{site.url}}/linear_algebra/2018/05/15/cofactor.html#pivots_with_det" target="_blank">one application of determinant</a>, \\(d_k=\textrm\{det\}A_k/\textrm\{det\}A_\{k-1\}\\) so \\(d_k\\) must be positive for all \\(k\\).  
`(D)`\\(\rightarrow\\)`(A)`: \\(A=LDU=LDL^T\\) (\\(A\\) is symmetric!) so that,
\\[x^TAx=x^TLDL^Tx=D(L^Tx)^TL^Tx>0.\\]

<h3 id="pd_and_least_sq">Least square and positive definite matrices (+Another definition of PD mat)</h3>
Rememter the <a href="{{site.url}}/linear_algebra/2018/05/16/projection.html" target="_blank">`least square`</a> setting \\[Rx=b,\quad\quad R\in R^\{m\times n\},m\leq n\\]
where the columns of \\(R\\) are independent. The system \\(Rx=b\\) might not solvable.  
Instead, we solved the `normal equation` \\(R^TR\hat\{x\}=R^T\hat\{x\}\\). The <a href="{{site.url}}/linear_algebra/2018/05/10/cross-prod-mat.html" target="_blank">`normal matrix`</a> \\(R^TR\\) is symmetric (indeed) and positive definite (which we will show now), provided that the __columns__ of \\(R\\) are __independent.__

{:.theorem}
> The symmetric matrix \\(A\in R^\{n\times n\}\\) is __positive definite__ i.i.f there exists \\( m\times n\\) matrix \\(R\\) with __independent columns__ such that \\[A=R^TR.\\]
{:.theorem}

`Proof.`  
\\(\leftarrow\\>\\>\\) If \\(A=R^T R\\) for \\(R\\) with independent columns, \\[x^T Ax=(Rx)^T Rx=\\|Rx\\|^2\\]
Since the columns of \\(R\\) are independent, we see that \\(x^TAx>0\\) for nontrivial \\(x\\).  
\\(\rightarrow\\>\\>\\) Since \\(A\\) is symmetric, \\(A=LDL^T\\). Easy choice is \\(R=L\sqrt\{D\}\\).
Note that for any \\(Q,\\>(QR)^T (QR)=R^T R=A\\), so the choice above is not unique.  
The `Choleskey decomposition` is done in similar way, wrt eigenvector basis S. \\[A=SΛS^T=(\sqrt Λ S^T )^T \sqrtΛ S^T.\\]
For positive __semidefinite__ matrices, we replace \\(>\\) into \\(\geq \\), and independent into dependent.