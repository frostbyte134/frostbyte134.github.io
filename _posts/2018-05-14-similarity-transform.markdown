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
1. What do the `similar matrices` \\(M^\{-1\}AM\\) have in common?
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

### Similarity transform = change of basis
To represent a vector, <a href = "{{site.url}}/linear_algebra/2018/04/19/vector-space.html#coord" target="_blank">we need a basis and coordinate</a>. 