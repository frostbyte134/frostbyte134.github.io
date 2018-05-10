---
layout: post
title:  "Normal matrix"
date:   2018-05-10 16:05:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---

<h3>Normal matrix and original matrix share nullspace</h3>
\\(A^TA\\) has the same nullspace as \\(A\\). Indeed,
\\[Ax=0\rightarrow A^T Ax=0\\]
is obvious. To prove the converse,
\\[A^T Ax=0\quad\rightarrow\quad x^T A^T Ax=0\quad\rightarrow\quad (Ax)^T (Ax)=\||Ax\||^2=0\quad\rightarrow\quad Ax=0.\\]
* If the columns of A are independent \\(\left(\textrm\{rank\}A=n\right)\\)) then \\(N(A)=\\{0\\}\\), \\(N(A^TA)=\\{0\\}\\) holds so that \\(A^TA\\) is invertible.

### Normal matrix is positive definite
