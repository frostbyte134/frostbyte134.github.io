---
layout: post
title:  "4 Fundamental subspaces of a rank r,m X n matrix"
date:   2018-04-12 22:41:00
categories: linear_algebra
use_math: true
tags: linear_algebra
---

![4spaces]({{ site.url }}/images/math/linear_alg/4spaces.jpg)  

### (1) Row space (\\(R^n\\), with \\(n-r\\) basis)
* Space spanned by the rows
* Row operation does not change the rowspace (Basis remains the same)
* If a nonzero vector is in rowspace, \\(A\\) transforms it to a vector in nonzero columnspace.


### (2) Null space (\\(R^n\\), with \\(n-r\\) basis)
* For \\(x\in\textrm{null}(A),\>Ax=0\\) holds \\(\rightarrow\\) taking inner product with rows of \\(A\\) and \\(x\\) gives \\(0\in\Re\\).

* Orthogonal complement to the rowspace (Gathered all vectors orthogonal to rowspace – we need to find  basis all orthogonal to the basis of rowspace) (Orthogonal complement will be defined rigorously later)
* Row operation does not change the nullspace (since such operation does not change the rowspace)
* \\(A\\) transforms a vector from nullspace to the origin of the column space (\\(0\in\Re^n\\)).


### (3) Column space (\\(R^m\\), with \\(r\\) basis)
* Space spanned by the columns
* Row operation does not change the column space, since the nullspace remains same
Proof. After the row operation, the matrix (in row sense) will look like \\[\begin{bmatrix} \textrm{row a} \\\ \vdots \\\ \textrm{row a + row b} \end{bmatrix}\\] 1. Linear combinations of columns which produced 0 vector remains the same, since the \\(\textrm{row a}\\) is copied directly into another row.
2. Linear combinations of columns which did not produced 0 vector remains the same, for the same reason
Therefore, the basis of the column vector remains the same after the row operation.


### (4) Left-nullspace (\\(R^m\\), with \\(m-r\\) basis)
* Orthogonal complement of the column space
* Row operation does not change the left-nullspace, since it does not change the column space


### (5) \\(Ax=b\\) is solvable when
* \\(b\\) is in the columnspace, or equivalently,
* \\(b\\) is in \\(\left(\textrm{Left nullspace}\right)^\perp\\) (remember that orthogonal complement of left nullspace is the columnspace)
(\\(Ax=b\\) is valid only when \\(y^TA=0\\) implies \\(y^Tb=0\\))