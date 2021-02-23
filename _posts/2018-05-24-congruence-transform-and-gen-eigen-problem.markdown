---
layout: post
title:  "Congruence transformation and generalized eigenvalue problem"
date:   2018-05-24 14:09:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
<h3 id="congruence_transform">Congruence transformation</h3>
Two major transformations we've learned with __symmetric matrix__ \\(A\\)
1. Elimination \\(A=LDL^T\\)
2. Similarity transformation \\(Q\Lambda Q^T\\)

Note the similarity, which multiplies transpose for the __nonsingular__ \\(C\\) in the other side.  
Now we can ask that, for nonsingular \\(C\\), what is invariant for \\[A\quad\rightarrow\quad C^TAC?\\]
Trivially __symmetry is preserved__. Additionally,
> `The Law of inertia`: __Congruence transformation__ applied on a symmetric matrix \\(A\\), \\(C^TAC\\) for nonsingular \\(C\\), preserves the sign of the eigenvalues.

(Spectral transform with \\(C=Q\\) is one specific example)  
`Proof`. Assume nonsingular \\(A\\) (o.w., we can work with the nonsingular A+ϵI and A-ϵI, and at the end let ϵ→0. ???). Suppose \\(C\\) is linked to an orthogonal matrix \\(Q\\), by a continuous chain of nonsingular matrices \\(C(t)\\)

>\\(C(t)\quad\rightarrow\quad Q\\) as \\(t\\) goes  \\(0→1,\\>C(0)=C,\\>C(1)=Q\\).  
One good choice for C(t): Apply Gramm-Schmidt to C. Then
\\[C=QR  →  C(t)=tQ+(1-t)QR\\]
\\(C(t)\\) is invertible, since \\(Q\\) is invertible and \\(tI+(1-t)R\\) has positive diagonal (??)

Then the eigenvalues of \\((C(t))^T AC(t)\\) will gradually go toward the eigenvalues of \\(Q^T AQ\\), which we know that are equivalent to the eigenvalues of \\(A\\).
During the process, we note that \\((C(t))^T AC(t)\\) is never singular, thus none of the eigenvalues touch 0. Their sign remains the same throughout the whole process, especially at \\(C^T AC\\), the starting point.
(Think I need to prove the continuity…)  
  
__Important application__: For any symmetric A, the signs of diagonals \\(A=LDL^T\\) agree with the signs of the eigenvalues. Here the elimination meets eigenvalue.

<h3 id="gen_eigen_problem">Generalized Eigenvalue problem</h3>
We will replace \\(Ax=\lambda x\\) by \\(Ax=\lambda Mx\\) for positive definite \\(M=R^TR\\) with invertible \\(R\\). The purpose of such formulation can be explained by the congruence transform.

By letting \\(y=Rx\\), \\(x=R^\{-1\} y\\) so that \\[Ax=λMx\quad\rightarrow\quad AR^\{-1\} y=\lambda R^T y\quad\rightarrow\quad (R^\{-1\} )^T AR^\{-1\} y=λy.\\]
with substitution \\(R^\{-1\}=C\\), we see the congruence transform, equivalent to the original \\(Ax=\lambda Mx\\).
\\[C^TACy=\lambda y.\\]
The property of above problem is,
1. The eigenvalues of \\(Ax=\lambda Mx\\) are real, since \\(C^TAC\\) is symmetric. 
2. The sign of eigenvalues are equivalent to \\(A\\), by the `law of Inertia`.
3. \\(C^TACy=\lambda y\\) has orthogonal eigenvectors, which implies that the eigenvectors of \\(Ax=\lambda Mx\\) has \\[M-\textrm\{orthogonality\}\\>\\>\\>x_j^T Mx_i=(Rx_j)^T (Rx_i)=y_j^T y_i=0\\]
The main point is, as long as \\(M\\) is positive definite, the generalized eigenvalue problem \\(Ax=\lambda Mx\\) behaves exactly like \\(Ax=\lambda x\\). 