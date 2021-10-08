---
layout: post
title:  "Linear Algebra, Gilbert Strang, 4th"
date:   2020-11-04 09:00:05 +0800
categories: linear_algebra
use_math: true
tags: linear_algebra math need_review
---

복습할 시간 내기 쉽지 않네...

<img src="{{site.url}}/images/math/linear_alg/strang/chap1/mapping.jpg">  


### Chap 1
- \\(M \times N\\) matrix = M equations, N unknowns
- Geometry of Linear Equation \\(Ax=b\\)
  - linear combination of vectors (columns) \\(\sum a\_ix\_i=b\\), in column sense
  - intersection of hyperplanes, in row sense
    - ex) in \\(R^3\\), each row represents plane (freedom in \\(R^2\\), given linear (orthogonal) constraint), and their intersection is line (freedom in \\(R^2\\))
  - singular case - trivial (just a reminder)
- Any equality in \\(R^3\\) represents a plane (\\(3x+2y+5z=2, y=3, ...\\))
  - intersection of 2 planes = a line
  - intersection of 3 planes = a point
- different pictures of \\(Ax=b\\)
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
- \\(L\\) = lower triangle matrix (row operations) \\( L=L\_1L\_2L\_3...\\)
- \\(U\\) = resulting upper triangle mat
- time complexity \\(O(n^3)\\)

`1J`
- In the nonsingular case, there is a permutation matrix \\(P\\) that reorders the rows of \\(A\\) to avoid zeros in the pivot positions. Then \\(Ax=b\\) has a unique solution:  
With the rows reordered in advance, \\(PA\\) can be factored into \\(LU\\).
- In the singular case, no \\(P\\) can produce full set of pivots : elimination fails

학교에서 배운 Gaussin elimination
\\[L=L\_1L\_2L\_3\quad\quad, LPA=U\\]
1. row permutation을 먼저 하든 나중에 하든 노상관이므로, 먼저 해버리기
2. 항상 낮은 row에 높은 row를 더하거나 빼기 때문에, low triangle mat만 생김 (\\(L\_iA\\)의 곱 형태에서, \\(j\\) 번째 결과 row에 A의 row \\(k)에 )
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

`2C` If \\(Ax=0\\) has more unknowns than equations \\(\left(n>m\right)\\), then it has at least one special solution: There are more solutions than the trivial \\(x=0\\).
- = Its nullspace cannot be trivial
  - 왜나하면, column들이 dependent하기 떄문에 (column들의 linear combination에서 dependent한 칼럼이 있다 - 특정 special solution을 dependent한 칼럼들을 이용해 무한하게 만들 수 있으므로, nullspace가 nontrivial함)
    - 예를 들어 \\([a, b, c] \in N(A)\\)이고, \\(A\\)의 2, 3번째 column 이 dependent하다면, \\([a, b+c, b-c] \in N(A)\\)이고 둘은 row입장에서는 linearly dependent하지 않으므로..
    - 위의 소리는, dependent한 column이 있을 시 __단사가 될 수 없다는__ 것과 동일  
  - The columns of \\(A\\) are independent exactly when \\(N(A)\\) is trivial

`2H` If a vector space \\(V\\) consists of all linear combinations of \\(w\_1,...,w\_n\\), then these vectors span the space. Every vector \\(v\in V\\) is some combination of the \\(w\\)'s.

`2I` A basis for a vector space \\(V\\) is a sequence of vectors having two properties at once:
1. The vectors are linearly independent (not too many vectors)
2. They span the space \\(V\\) (not too few vectors)

`2J` Any two bases for a vector space \\(V\\) contain the same # of vectors. This number, which is shared by all bases and expresses the number of __degrees of freedom__ of the space, is the `dimension of `\\(V\\)

#### The Four Fundamental Subspaces

> When the rank is as large as possible, \\(r=n\\) or \\(r=m\\) or \\(r=m=n\\), then the matrix has a left-inverse \\(B\\) or a right-inverse \\(C\\) or a two-sided \\(A^\{-1\}\\).

- \\(r=n\\)인 경우 (column들이 independent), \\(A^TA\\)와 \\(A\\)는 둘다 trivial한 nullspace를 가지고 있음.
- \\(N(A) = N(A^TA)\\).
  - \\(\rightarrow\\) : trivial
  - \\(\leftarrow\\) : \\(AT^Ax=0 \quad\rightarrow\quad x^TA^TAx=0 \quad\rightarrow\quad \|\|Ax\|\|=0 \quad\rightarrow\quad Ax=0\\)
- \\(A^TA\\)는 \\(n\times n\\) 행렬에 N(A)가 trivial하므로 non-singular함
- 결국 A는, \\((A^TA)^\{-1\}A\\)의 left-inverse를 가짐!
- \\(r=m\\)인 경우 - transpose해서 보이면 됨

For a matrix \\(A\in R^\{m\times n\}\\), 
- subspaces of \\(R^n\\)
  - \\(N(A)\\) : nullspace of \\(A\\). Its dimension is the \\(n-r\\).
  - \\(C(A)\\) : column space of \\(A\\). Its dimension is rank \\(r\\).
- subspaces of \\(R^m\\)
  - the __row space__ of \\(A\\) is the column space of \\(A^T\\). It is \\(C(A^T)\\) and it is spanned by the rows of \\(A\\). Its dimension is also \\(r\\).
  - The left nullspace of \\(A\\) is the nullspace of \\(A^T\\) - \\(N(A^T)\\). Its dimension is \\(m-r\\).

`2M, 2N` : The (row / null) space of \\(A\\) has the same dimension \\(r\\) as the (row / null) space of \\(U\\) and they have same basis, because the row spaces of \\(A\\) and \\(U\\) are the same.
- The column space of \\(A\\) and \\(U\\) are different, but their dimensions are the same.

`2O` : The dimension of the \\(C(A)\\) equals the rank \\(r\\), which also equals the dimension of the row space : The number of independent columns equals the number of independent rows. A basis for \\(C(A)\\) is formed by the \\(r\\) columns of \\(A\\) that correspond, in \\(U\\), to the columns containing pivots.
- `row rank = column rank`
- For a square matrix, it it has full row rank than it also has full column rank


#### Existence of Inverses

`2Q`
1. __EXISTENCE__ : Full row rank \\(r=m\\). \\(Ax=b\\) has at least one solution \\(x\\) for every \\(b\\) i.i.f the columns span \\(R^m\\). Then \\(A\\) has a `right-inverse` \\(C\\) s.t. \\(AC=I,\\ \\ C\in R^\{n\times m\}\\). This is pissible only when \\(m\leq n\\).
  - 항상 전사인가? yes. column space (\\(R^m\\))가 full rank이므로, 어떤 b든 column들의 선형조합으로 생성 가능. 차원정리로도 보일 수 있음.
  - 항상 단사인가? no. \\(n-r\neq 0\\)인 경우 nullspace가 nontrivial함. 오히려 항상 단사가 아님.
  - 항상 right-inverse가 있을 것인가? yes. \\(C=A^T(AA^T)^\{-1\}\\). 증명 - `The Four Fundamental Subspaces` 부분 한글
2. __UNIQUENESS__ : Full column rank \\(r=n\\). \\(Ax=b\\) has at most one solution \\(x\\) for every \\(b\\) i.i.f the columns are linealy independent. Then \\(A\\) has an \\(n\times m\\) left-inverse \\(B\\) s.t. \\(BA=, C\in \{n\times m\}\\). This is possible only if \\(m\geq n\\).
  - 항상 전사인가? no. 이미지의 rank가 모자라므로 항상 전사가 아니라는 것은 자명함
  - 항상 단사인가? yes. nullspace가 trivial하므로
  - 항상 left-inverse가 있을 것인가? yes. 증명 - `The Four Fundamental Subspaces` 부분 한글

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

<img src="{{site.url}}/images/math/linear_alg/strang/chap1/rank1.jpg" width="800">  


`2V` Supposer \\(A\\) and \\(B\\) are linear transformations from \\(V\\) to \\(W\\) and from \\(U\\) to \\(V\\). Their product \\(AB\\) start with a vector \\(u\in U\\), goes to \\(Bu\\) in \\(V\\), and finishes with \\(ABu\\) in \\(W\\). This `composition` \\(AB\\) is again a linear transformation from \\(U\\) to \\(V\\).

(<a href="https://nailbrainz.github.io/analysis/2018/04/02/vector-projection.html" target="_blank">remember</a> that, \\(\text\{cos\}\theta = \|a^Tb\|/(\|a\|\|b\|)\\))

### Chap 3 Orthogonality
> A basis is a set of independent vectors that span a space. Geometrically, it is a set of coordinate axes.

- The fundamental subspaces meet at right angles : those four subspaces are perpendicular in pairs, two in \\(R^m\\) and two in \\(R^n\\).

`3A` The inner prod \\(x^Ty\\) is zero iif \\(x\\) and \\(y\\) are orthogonal vectors. If \\(x^Ty>0\\), their angle is less than 90 deg. If \\(x^Ty<0\\), their angle is greater than 90 deg (코사인 그래프)

`Useful fact`: If nonzero vectors are mutually orthogonal, then those vectors are linealy independent

`3B` Two subspaces \\(V\\) and \\(W\\) of the same space \\(R^n\\) are _orthogonal_ if every \\(v\in V\\) is orthogonal to every \\(w\in W\\)


> __Definition.__ Given a subspace \\(V\subseteq R^n\\), the space of all vectors orthogonal to \\(V\\) is called the __orthogonal complement__ of \\(V\\). It is denoted by \\(V^\{\perp\}\\) = V perp.

If \\(W=V^\{\perp\}\\) then \\(V=W^\{\perp\}\\), and \\(\text\{dim\}V + \text\{dim\}W = n\\). In other words, \\(V^\{\perp\perp\}=V\\).

__Dimension formula__ dim(row space) + dim(nullspace) = number of columns, \\(n\\).

`3D`, __Fundamental theorem of Linear Algebra__ The rowspace is orthogonal complement to the nullspace (in \\(R^n\\)). The column space is orthogonal complement to the left nullspace

<img src="{{site.url}}/images/math/linear_alg/strang/chap1/mapping.jpg">  

`3F` From the row space to the column space, \\(A\\) is actually invertible. Every vector \\(b\\) in the column space comes from exactly one vector \\(x\_r\\) in the row space.

> Every matrix transforms its row space onto its column space.

\\(A^T\\) goes in the opposite direction, from \\(R^m\\) to \\(R^m\\) and from \\(C(A)\\) to \\(C(A^T)\\). Of course the transpose is not inverse.

When \\(A^\{-1\}\\) fails to exist, the best substitute is the <a href="https://nailbrainz.github.io/linear_algebra/2018/11/06/pseudoinverse.html" target="_blank">`pseudoinverse`</a> \\(A^+\\). This inverts \\(A\\) where that is possible: \\(A^+Ax=x\\) for \\(x\\) in the row space. On the left nullspace, nothing can be done. \\(A^+y=0\\). Thus \\(A^+\\) inverts \\(A\\) where it is invertible, and has the same rank \\(r\\). One formula for \\(A^+\\) depends on the <a href="https://nailbrainz.github.io/linear_algebra/2018/05/26/svd.html" target="_blank">singula value decomposition.</a>


#### 3.2 Cosines and Projections onto lines
> We want to connect inner products to angles, and also to transposes.

<a href="https://nailbrainz.github.io/linear_algebra/2018/05/16/projection.html" target="_blank">Projection onto a line - least-squares solution to an overdetermined system</a>

projection onto a line and Schwartz inequality (The most important inequality in mathematics!)  
<img src="{{site.url}}/images/math/linear_alg/strang/chap1/schwartz.jpg" width="900">  

#### Transpose from Inner products
Up to now, \\(A^T\\) is simply the reflection of \\(A\\) across its main diagonal;  the rows of \\(A\\) become the columns of \\(A^T\\).  
Its close connection to inner products gives a new and much more _abstract_ definition of the transpose:

- __def__ : 선형사상 A와 내적 \\(\cdot\\)에 대해, \\[\overrightarrow\{x\}\cdot A(\overrightarrow\{y\}) = A^\{+\}(\overrightarrow\{x\})\cdot \overrightarrow\{y\}\\] 가 성립하는 사상 \\(A^+\\). 
- 정규직교기저로 \\(A\\)를 표현하면, \\(A^+=A^T\\)가 됨.


#### Least square
- <a href="https://nailbrainz.github.io/linear_algebra/2018/05/16/projection.html" target="_blank">LINK</a> 으로 대체
- Weighted least squares system \\(WAx=b\\) where \\(W\\) is a diagonal matrix with weights.
  - EX) 각 row (a data point)는 신뢰성, 표본 크기 등의 credibility degree를 가질 수 있음
- __The least square solution__ to above system is \\(\hat\{x\}_W\\), which can be found in 
  - `weighted normal equation` \\((A^TW^TWA)\hat\{x\}\_W=A^TW^TWb\\)


#### Gram-Schmidt and QR factorization
- every \\(m\times n\\) matrix with independent columns can be factorized to \\(QR\\), where \\(Q\\) is the orthonormal matrix and \\(R\\) is the upper triangle matrix (which is clear given the Gram-Schmidt process)

#### Function Spaces and Fourier Series
- 엄청 중요하니까 한번 읽어 보기
- `Hilbert space` : norm이 유한한 무한차원 벡터들로 이루어진 vector sapce



### Chap 5 Eigenvalues and Eigenvectors

- eigenvalues - solution of characterstic equation \\((A-\lambda I)x=0\\)
- eigenvectors - nontrivial nullspace component of the characteristic equation

__5C__ : The eigenvectors diagonalize a matrix:
- Suppose the \\(n\times n\\) matrix \\(A\\) has \\(n\\) linearly indpendent eigenvectors. If these eigenvectors are the columns of a matrix \\(S\\), then \\(S^\{-1\}AS\\) is a diagonal matrix \\(\Lambda\\). The eigenvalues of \\(A\\) are on the diagonal of \\(\Lambda\\).
- \\(S^\{-1\}AS=\Lambda\\)
- can be shown by \\(As=S\Lambda\\)
- Normal matrices have linearly independent e-vecs, hence diagonalizable