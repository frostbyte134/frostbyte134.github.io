---
layout: post
title:  "Similarity Transformation"
date:   2018-05-14 15:56:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
For non-singular \\(M\\), \\(B=M^\{-1\}AM\\) is the `similarity tansform` of \\(A\\).  

Two important questions for Similarity transform are
1. What do the similar matrices \\(M^\{-1\}AM\\) have in common?
\\[\rightarrow\textrm\{Eigenvalues\}\\]
2. With a special choice of \\(M\\), what special form can be obtained by \\(M^\{-1\}AM\\)?
\\[\rightarrow\textrm\{Jordan form\}\\]

### Similar matrices share eigenvalues and determinants
Suppose that \\(B=M^\{-1\}AM\\) for invertible \\(M\\). Then \\(A\\) and \\(B\\) have the same eigenvalues, and every eigenvector \\(x\\) of \\(A\\) corresponds to an eigenvector \\(M^\{-1\}x\\) of \\(B\\).  
`proof`: Suppose \\(Ax=\lambda x\\). Then \\[MBM^\{-1\}=\lambda x\\]
\\[ BM^\{-1\}x=\lambda M^\{-1\}x\\]
\\[\Rightarrow By=\lambda y\quad \textrm\{for\}\quad y=M^\{-1\}x.\\]
As for the determinants,
\\[\textrm\{det\}(A-\lambda I)=\textrm\{det\}(MBM^\{-1\}\lambda I)=\textrm\{det\}M\textrm\{det\}(A-\lambda I)\textrm\{det\}M^\{-1\}\\]
\\[=\textrm\{det\}(A-\lambda I)\\]

Additionally note that, similarity transform preserve independency.

### Similarity transform = change of basis
We can perform a `diagonalization = similarity transform = change of basis` to represent \\(A\\) in a different form, especially diagonal \\([\Lambda]\\) with spectral decomposition (__link!!__).
\\[AQ=Q\Lambda\quad\rightarrow\quad A=Q\Lambda Q^\{-1\}\\]
We can view \\(A=Q\Lambda Q^\{-1\}\\) as a set of linear transformation, with respect to __some basis matrix__ \\(Z\\) (Not guaranteed to be an orthonormal eigenvector matrix).
\\[A\_\{\textrm\{X to X\}\}=I\_\{\textrm\{Z to X\}\}A\_\{\textrm\{Z to Z\}\}I\_\{\textrm\{X to Z\}\}\\]
Here \\(Q^\{-1\}\\) becomes a matrix corresponding to identity transformation \\(I\\) from the basis \\(X\\) to \\(Z\\), which gives \\(Z\\) by
\\[Q^\{-1\}=Z^\{-1\}I(X)\quad\rightarrow\quad Q^\{-1\}=Z^\{-1\}X\quad\rightarrow\quad Z=QX\\] <a href="{{site.url}}/linear_algebra/2018/04/21/mat-and-linear-transform.html#change_of_basis_mat" target="_blank">(refer to (3) here)</a>.  
The linear system \\(y=Ax\\) becomes
\\[y=Q\Lambda Q^\{-1\}x \quad\rightarrow\quad Q^\{-1\}y=\Lambda Q^\{-1\}x\\]
\\[z=\Lambda q\\]
with the new coordinates \\(z=Q^\{-1\}y\\) and \\(q=Q^\{-1\}x\\), where \\(Q^\{-1\}\\) a matrix corresponds to a linear transformation \\(I\\) from the basis \\(X\\) to \\(Z\\), as stated above.