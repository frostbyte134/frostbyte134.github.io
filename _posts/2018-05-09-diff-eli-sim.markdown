---
layout: post
title:  "Difference between Elimination and Similarity transform"
date:   2018-05-09 19:49:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
For matrix \\(A\\) which represnets a linear system, both elimination and diagonalization converts \\(A\\) into a diagonal matrix. However there is a major difference.

### Elimination
Elimination multiplies `non-singular` (row / column) operation matrix \\(\left(P\\>/\\>Q\right)\\) so that 
\\[A=PDQ\\]
Where \\(D\\) is a diagonal matrix. The linear system becomes
\\[x_1=Ax_0\quad\rightarrow\quad x_1=PDQx_0\quad\rightarrow\quad (P^\{-1\}x_1)=D(Qx_0)\\]
\\[x_2=Ax_1\quad\rightarrow\quad x_2=PDQx_1\quad\rightarrow\quad (P^\{-1\}x_2)=D(Qx_1)\\]
\\[\vdots\\]
You can see that \\((P^\{-1\}x_1)\\) and \\((Qx_1)\\) does not match. Thus the __elimination cannot reformulate the linear system.__

### Similarity transform
(By finding \\(n\\) set of `eigenpairs`) We perform diagonalization by \\[AQ=Q\Lambda\rightarrow A=Q^\{-1\}\Lambda Q.\\]
Where \\(\Lambda\\) is a eigenvalue diagonal matrix. The linear system becomes
\\[x_1=Ax_0\quad\rightarrow\quad x_1=Q^\{-1\}\Lambda Qx_0\quad\rightarrow\quad (Qx_1)=\Lambda(Qx_0)\\]
\\[x_2=Ax_1\quad\rightarrow\quad x_2=Q^\{-1\}\Lambda Qx_1\quad\rightarrow\quad (Qx_2)=\Lambda (Qx_1)\\]
\\[\vdots\\]
\\((Qx_1)\\) now matchs, and the __linear system is reformulated in convenient form with similarity transformation.__