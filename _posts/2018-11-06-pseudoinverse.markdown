---
layout: post
title:  "Pseudo Inverse"
date:   2018-11-06 13:13:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra need_revise
---
<img src="{{ site.url }}/images/math/linear_alg/pseudoinverse.png" class="center" style="width:800px"/>  


A \\(m\times n\\) matrix \\(A\\) maps a nonzero vector in its rowspace into a nonzero vector in its columnspace.  
Inverse, \\(A^\{-1\}\\) (if exists) maps a nonzero vector in \\(A\\)'s columnspace to a nonzero vector in \\(A\\)'s rowspace.  

When \\(A\\) is defective, there could be 2 cases.
1. \\(\textrm\{rank\}A \leq m\\)
2. \\(\textrm\{rank\}A \leq n\\)


whatever

### Least square and the Pseudoinverse

A rectangular system \\(Ax=b\\) shares least-square solution with the normal system \\(A^TA\hat\{x\}=A^Tb\\).  

\\(Ax=b\\) has two difficulties.
1. Independent columns, but dependent rows : \\(Ax=b\\) may have no solution. \\(b\\) is not in the columnspace of \\(A\\), so we solve \\(A^TAx=A^Tb\\). When \\(A\\) has independent columns, \\(A^Tb\\) must be in the columnspace of \\(A^TA\\).
2. Dependent columns : Then \\(A^TA\\) is not invertible and \\(\hat\{x\}\\) is not determined (any nullspace component can be added). We have to choose the __best__ (=shortest) \\(\hat\{x\}\\) for every \\(Ax=b\\).


`Theorem`: The optimal solution of \\(Ax=b\\) is the minimum length of the solutions of \\(A^TA\hat\{x\}=A^Tb\\). Pseudoinverse \\(A^+:=V\Sigma^+ U^T\\) of \\(A\\) (not \\(A^TA\\)) gives the solution by \\(x^+=A^+b\\).

__Proof__: For clarity, we first claim that \\(x^+\\) always lies in the rowspace of \\(A\\), since no nonzero nullspace component is added to it. 

Remember that every vector \\(\hat\{x\}\\) can be splitted into \\(\hat\{x\}=x\_r+x\_n\\). Assuming that \\(\hat\{x\}\\) is the solution, there are 3 main important points about the splitting.
1. The rowspace component \\(x\_r\\) also solves the normal system \\(A^TAx=A^Tb\\), since \\(Ax\_n=0\\).
2. The components are orthogonal, and they obey Pythagoras's law:
\\[\\| \hat\{x\} \\| (x\_r+x\_n)^T(x\_r+x\_n)=\\| x\_r \\|^2 + \\| x\_n \\|^2\\]
so that \\(\hat\{x\}\\) is the shortest when \\(x\_n=0\\).
3. All solutions of \\(A^TA\hat\{x\}=A^Tb\\) have the same \\(x\_r\\). That vector is \\(x^+\\).

Now we show that \\(x^+=A^+b=V\Sigma^+ U^Tb\\).  
1. Multiplciation by the orthognal matrix \\(U^T\\) leaves length unchanged
\\[\\| Ax-b\\| =\\| V\Sigma^+ U^Tx-b\\|=\\| \Sigma V^Tx-U^Tb\\|\\] 
2. Define \\(y=V^Tx=V^\{-1\}x\\), which has same length with \\(x\\). Then, minimizing \\(\\|Ax-b\\|\\) is equivalent to minimizing \\(\\|\Sigma y-U^Tb\\|\\). Now \\(\Sigma\\) is diagonal and we know the best \\(y^+\\). It is \\(y^+=\Sigma^+U^Tb\\), where \\(\Sigma^+\\) is taking reciprocal of each nonzero diagonal components of \\(\Sigma\\). For zero diagonal entries, the norm value does not change whatever we put on corresonding elements of \\(\Sigma^+\\), so 0 is the optimal (minimum norm answer).


