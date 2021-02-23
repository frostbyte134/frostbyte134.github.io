---
layout: post
title:  "Ellipsoids and Positive Definite Matrices"
date:   2018-05-24 14:09:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
\\(x^TAx=1\\) with __positive definite__ \\(A\\) has a bijection mapping with the ellipsoid.  
The center is in origin, since \\(x\\) which satisfies \\(x^T Ax=1\\) must be symmetric around the origin.
{:.deccounter}
1. \\(A=I\\). Unit circle (length 1) \\[x^TIx=x^Tx=1.\\]
2. \\(A=D\\). Ellipsoid with __unit bases__ (not tilted) \\[x^TDx=\sum_\{i=1\}^nd_ix_i^2.\\]
By letting \\(x=\frac\{1\}\{\sqrt d_i\}e_i\\), the radius of ellipsoid toward axis \\(e_i\\) is \\(\frac\{1\}\{\sqrt d_i\}\\).
3. \\(A=\\)positive definite.  
We apply the Spectral decomposition \\(A=Q\Lambda Q^T\\). \\[x^TQ\Lambda Q^Tx=(Q^Tx)^T\Lambda Q^Tx=1\\]
For an \\(i\\)th eigenpair \\((q_i,\lambda_i)\\), letting \\(x=\frac\{1\}\{\sqrt \lambda_i\}q_i\\) gives one of the `maximum stretch` of ellipsoid, with __length__ \\(\frac\{1\}\{\sqrt \lambda_i\}\\) and __direction__ \\(q_i\\).  
In coordinate change perspective,
	> Suppose \\(A=QΛQ^T\\) with \\(\lambda_i>0\\).  Rotating  \\(y=Q^T x\\)  simplifies  \\(x^T Ax=1\\):
	\\[x^T Q\Lambda Q^T x=y^T \Lambda y=\lambda_1 y_1^2+\cdots+\lambda_n y_n^2=1\\]
	
	The maximum stretch direction of such ellipsoid \\(\frac\{1\}\{\sqrt \lambda_i\}x_i\\) is rotated into standard basis \\(e_i\\) after the transformation \\(y=Q^Tx\\).
{:.deccounter}