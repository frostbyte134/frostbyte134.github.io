---
layout: post
title:  "Linear Algebra, Gilbert Strang, 4th"
date:   2020-09-24 09:00:05 +0800
categories: linear_algebra
use_math: true
tags: linear_algebra math need_review
---

우째 볼때마다 새롭냐...앞챕터는 빨리 넘기고 뒤를 좀 다시 봅시다

왜 행렬이 github만 올리면 깨지는지 모르겠다. 레이텍 ㅡㅡ

<img src="{{site.url}}/images/math/linear_alg/strang/chap1/mapping.jpg">  


### Chap 1
- Any equality in \\(R^3\\) represents a plane (\\(3x+2y+5z=2, y=3, ...\\))
  - intersection of 2 planes = a line
  - intersection of 1 planes = a point
- different pictures of a matrix
  - `Row picture` : Intersection of planes
  - `Column picture` : combination of columns
  - If the \\(n\\) planes have no point in common, or infinitely many points (parallel planes - implies linear dependency), then the \\(n\\) columns lie in the same plane

`1A` \\(Ax\\) is a combination of the columns of \\(A\\). The coefficients are the components of \\(x\\).

`1D` 
1. Each entry of \\(AB\\) is the product of a row and a column
2. Each column of \\(AB\\) is the product of a matrix and a column
3. Each row of \\(AB\\) is the product of a row and a matrix


#### Gaussian Elimination
\\[PA=LU\\]
- \\(P\\) = permutation matrix (non-singular)
- \\(L\\) = lower triangle matrix (row operations) \\( L=L\_1^\{-1\}L\_2^\{-1\}L\_3^\{-1\}...\\)
- \\(U\\) = resulting upper triangle mat


`1J`
- In the nonsingular case, there is a permutation matrix \\(P\\) that reorders the rows of \\(A\\) to avoid zeros in the pivot positions. Then \\(Ax=b\\) has a unique solution:  
With the rows reordered in advance, \\(PA\\) can be factored into \\(LU\\).
- In the singular case, no \\(P\\) can produce full set of pivots : elimination fails

학교에서 배운 Gaussin elimination
\\[L=L\_1^\{-1\}L\_2^\{-1\}L\_3^\{-1\}PA=U\\]
1. row permutation을 먼저 하든 나중에 하든 노상관이므로, 먼저 해버리기
2. 항상 낮은 row에 높은 row를 더하거나 빼기 때문에, low triangle mat만 생김
3. low triangle mat끼리 곱하면 low triangle mat이 나옴 (대각 위쪽 엔트리에 아이템이 생길 수가 없음. dot prod 하나만 해봐도 보임)
4. row operation을 나타내는 low triangle mat의 역행렬은, 연산하는 (위쪽) row에 곱하는 숫자에 negate 해 준 low triangle matrix (더했던 걸 돌리려면 빼면 되니까)
5. \\(O(N^3)\\). tight하게 하려면 1/3정도 곱해도 된다고 함
6. row끼리 더하고 빼고 permutation 하기 때문에, 원래의 rank나 해가 변할 일은 없음
7. row operation / permutation matrix들은 당연히 전부 non-singular


#### `Gauss-jordan` for calculating inverse
- U를 D로 만드는 연산의 역행렬을 원래 행렬에 곱하면 됨
- \\(O(N^3)\\). O(N^2 * 2)번의 row operation / permutation을 할 것이고, 각 연산은 O(N)

`1K` The inverse of \\(A\\) is a matrix \\(B\\) such that \\(BA=I\\) and \\(AB=I\\). There is at most one such \\(B\\), and it is denote by \\(A^\{-1\}\\).

`1N` Suppose \\(A=A^T\\) can be factored int \\(A=LU=LDU\\) without row exchanges. Then \\(U\\) is the trnaspose of \\(L\\). The symmetric factorifzation becomes \\(A=LDL^T\\).


### Chap 2

> __Definition.__ A __subspace__ of a vector space is a nonempty subset that satisfies the requirements for a vector space: __Linear combinations stay in the subspace__.  
1. If we add any vector \\(x\\) and \\(y\\) in the subspace, \\(x+y\\) is in the subspace
2. If we multiply any vector \\(x\\) in the subspace by any scalar \\(c\\), \\(cx\\) is in the subspace.

A subspace is a subset that is __closed__ under addition and scalar multiplication

`2A` The system \\(Ax=b\\) is solvable i.i.f the vector \\(b\\) can be expressed as a combination of the columns of \\(A\\). Then \\(b\\) is in the column space.

The coluns of \\(AB\\) are combinations of the columns of \\(A\\) - the column space of \\(AB\\) is contained in (possibly equivalent) the column space of \\(A\\). Zero row will make a difference.

`2C` If \\(Ax=0\\) has more unknowns than equations \\(\left(n>m\right)\\), then it has at least one special solution: There are more solutions thatn the trivial \\(x=0\\).
- = Its nullspace cannot be trivial

The columns of \\(A\\) are indelendent exactly when \\(N(A)\\) is trivial

`2H` If a vector space \\(V\\) consists of all linear combinations of \\(w\_1,...,w\_n\\), then these vectors span the space. Every vector \\(v\in V\\) is some combination of the \\(w\\)'s.

`2I` A basis for a vector space \\(V\\) is a sequence of vectors having two properties at once:
1. The vectors are linearly independent (not too many vectors)
2. They span the space \\(V\\) (not too few vectors)

`2J` Any two bases for a vector space \\(V\\) contain the same # of vectors. This number, which is shared by all bases and expresses the number of __degrees of freedom__ of the space, is the `dimension of \\(V\\)`

#### The Four Fundamental Subspaces

> When the rank is as large as possible, \\(r=n\\) or \\(r=m\\) or \\(r=m=n\\), then the matrix has a left-inverse \\(B\\) or a right-inverse \\(C\\) or a two-sided \\(A^\{-1\}\\).

For a matrix \\(A\in R^\{m\times n\}\\), 
- subspaces of \\(R^n\\)
  - \\(N(A)\\) : nullspace of \\(A\\). Its dimension is the rank \\(r\\).
  - \\(C(A)\\) : column space of \\(A\\). Its dimension is \\(n-r\\).
- subspaces of \\(R^m\\)
  - the __row space__ of \\(A\\) is the column space of \\(A^T\\). It is \\(C(A^T)\\) and it is spanned by the rows of \\(A\\). Its dimension is also \(r\\).
  - The left nullspace of \\(A\\) is the nullspace of \\(A^T\\) - \\(N(A^T)\\). Its dimension is \\(m-r\\).

`2M, 2N` : The (row / null) space of \\(A\\) has the same dimension \\(r\\) as the (row / null) space of \\(U\\) and they have same basis, because the row spaces of \\(A\\) and \\(U\\) are the same.
- The column space of \\(A\\) and \\(U\\) are different, but their dimensions are the same.

`2O` : The dimension of the \\(C(A)\\) equals the rank \\(r\\), which also equals the dimension of the row space : The number of independent columns equals the number of independent rows. A basis for \\(C(A)\\) is formed by the \\(r\\) columns of \\(A\\) that correspond, in \\(U\\), to the columns containing pivots.
- `row rank = column rank`
- For a square matrix, it it has full row rank than it also has full column rank


#### Existence of Inverses

`2Q`
1. __EXISTENCE__ : Full row rank \\(r=m\\). \\(Ax=b\\) has at least one solution \\(x\\) for every \\(b\\) i.i.f the columns span \\(R^m\\). Then \\(A\\) has a `right-inverse` \\(C\\) s.t. \\(AC=I,\\ \\ C\in R^\{n\times m\}\\). This is pissible only when \\(m\leq n\\).
  - 항상 전사인가? yes. column space (\\(R^m\\))가 full rank이므로, 어떤 b든 column들의 선형조합으로 생성 가능
  - 항상 단사인가? no. \\(n-r\neq 0\\)인 경우 nullspace가 nontrivial함.
  - 항상 right-inverse가 있을 것인가? yes. \\(C=A^T(AA^T)^\{-1\}\\)
    - 여러 방법이 있을 텐데...일단 \\(AA^T\\)가 invertible하다는 것만 보여도 될 듯. Chap3에 나온다 하니 밑에서 정리 ㄱㄱ.
2. __UNIQUENESS__ : Full column rank \\(r=n\\). \\(Ax=b\\) has at most one solution \\(x\\) for every \\(b\\) i.i.f the columns are linealy independent. Then \\(A\\) has an \\(n\times m\\) left-inverse \\(B\\) s.t. \\(BA=, C\in \{n\times m\}\\). This is possible only if \\(m\geq n\\).
  - 항상 전사인가? no. 이미지의 rank가 모자라므로 항상 전사가 아니라는 것은 자명함
  - 항상 단사인가? yes. nullspace가 trivial하므로
  - 항상 left-inverse가 있을 것인가? yes. \\((A^TA)^TA^T\\). \\(A^TA\\)와 \\(A\\)는 nullspace를 공유하므로 (\\(\leftarrow\\)는 쉽고, \\(\rightarrow\\)는 \\(xA^TAx=\|\|Ax\|\|=0\\)으로), \\(A^TA\\)는 nullspace가 trivial한 정방행렬이 됨. 1번도 이거 + \\(A^T\\)로 증명하면 되지 않나?

For the square matrices, the condition for invertibility is __full rank__ : \\(r=m=n\\). Each of these conditions is a necessary and sufficient test (every cond is equivalent to each other, and ensures that \\(A\\) is invertible):
1. The columns span \\(R^n\\), so \\(Ax=b\\) has at least one solution for every \\(b\\)
2. The colums are independent, so \\(Ax=0\\) has only the solution \\(x=0\\).
3. The rows of \\(A\\) span \\(R^n\\)
4. The rows are linearly independent
5. Elimination can be completed : \\(PA=LDU\\)
6. The determinant of \\(A\\) is not zero
7. Zero is not an eigenvalue of \\(A\\)
8. \\(A^TA\\) is positive definite


> Rank 1 matrix : Every rank 1 matrix has the simple form \\(A=uv^T\\) = column times row

<img src="{{site.url}}/images/math/linear_alg/strang/chap1/rank1.jpg">  


`2V` Supposer \\(A\\) and \\(B\\) are linear transformations from \\(V\\) to \\(W\\) and from \\(U\\) to \\(V\\). Their product \\(AB\\) start with a vector \\(u\in U\\), goes to \\(Bu\\) in \\(V\\), and finishes with \\(ABu\\) in \\(W\\). This `composition` \\(AB\\) is again a linear transformation from \\(U\\) to \\(V\\).