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

### Chap 1
- Any equality in \\(R^3\\) represents a plane (\\(3x+2y+5z=2,\\ y=3, ...))
  - intersection of 2 planes = a line
  - intersection of 1 planes = a point

#### Gaussian Elimination
\\[PA=LU\\]
- \\(P\\) = permutation matrix (non-singular)
- \\(L\\) = lower triangle matrix (row operations) \\(L=L\_1^\{-1\}L\_2^\{-1\}L\_3^\{-1\}...\\)
- \\(U\\) = resulting 

학교에서 배운 Gaussin elimination
\\[L=L\_1^\{-1\}L\_2^\{-1\}L\_3^\{-1\}PA=U\\]
1. row permutation을 먼저 하든 나중에 하든 노상관
2. 항상 낮은 row에 높은 row를 더하거나 빼기 때문에, low triangle mat만 생김
3. low triangle mat끼리 곱하면 low triangle mat이 나옴 (위 엔트리에 아이템이 생길 수가 없음. dot prod 하나만 해봐도 보임)
4. row operation을 나타내는 low triangle mat의 역행렬은, row에 곱하는 숫자에 -를 해 준 것만 다른 low triangle matrix
5. \\(O(N^3)\\). tight하게 하려면 1/3정도 곱해도 된다고 함
6. row끼리 더하고 빼고 permutation 하기 때문에, 원래의 rank나 해가 변할 일은 없음
7. row operation / permutation matrix들은 당연히 전부 non-singular


`Gauss-jordan` for calculating inverse
- U를 D로 만드는 연산으 역을 원래 행렬에 곱하면 됨
- \\(O(N^3)\\). O(N^2 * 2)번의 row operation / permutation을 할 것이고, 각 연산은 O(N)

