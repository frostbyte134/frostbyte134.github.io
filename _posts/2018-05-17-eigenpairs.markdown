---
layout: post
title:  "Eigenpairs"
date:   2018-05-18 15:02:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra need_revise
---

### Few interesting theorems about the eigenpairs
> For invertible \\(A\\),  if \\(\lambda\\) is an eigenvalue of \\(A\\) with eigenvector \\(x\\) then \\(\frac\{1\}\{\lambda\}\\) is an eigenvalue of \\(A^\{-1\}\\) with eigenvector \\(x\\)


`proof`: 
\\[Ax=\lambda x\\]
\\[A^\{-1\}Ax=\lambda A^\{-1\}x\\]
\\[\therefore \frac\{1\}\{\lambda\}x=A^\{-1\}x.\\]
  
> Determinant of \\(A\\) = product of all eigenvalues of \\(A\\).

\\(\rightarrow\\) <a href="{{site.url}}/linear_algebra/2018/05/09/characteristic-equ.html#apps">link</a>



### Geometric multiplicity is bounded by the algebraic multiplicity
https://www.google.co.kr/search?q=geometric+multiplicity+is+less+than+algebraic+multiplicity&rlz=1C1QJDB_enKR796KR796&oq=geometric+mul&aqs=chrome.2.69i57j0l5.7111j0j4&sourceid=chrome&ie=UTF-8