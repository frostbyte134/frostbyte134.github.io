---
layout: post
title:  "프로그래머를 위한 선형대수 복습노트"
date:   2020-07-31 09:00:05 +0800
categories: linear_algrbra
use_math: true
tags: linear_algrbra math need_review
---

TODO
- 차원정리 증명

### Chap 1
- 선형대수 : 공간, 근사에 대한 학문
- 좌표에 의존한다 = 기저 선택에 의존적이다
- \\(v\\) : 좌표, \\(\overrightarrow\{v\}\\) : 벡터. \\(\overrightarrow\{v\} = e\_1+v\_1 + e\_2+v\_2, v=[v\_1,v\_2]^T\\)
- 고유값은 어떻게 기저 선택에 의존적이지 않은가 - 닯음변환으로 고유벡터만 변하고 고유값은 그대로 있는 것을 확인가능
- 행렬은 사상이다
  - 대각행렬은 기저에 의존적 (닮은변환으로 대각으로 만들 수 있으니)
  - 단위행렬/영행렬은 기저에 의존적이 아님 \\(\left(x=f(x), 0=f(x) \quad\forall\quad x\in R^n\right)\\) 인 사상에 대응하는 행렬이므로)
- 사상으로서의 행렬에서 `전치`의 의미는 무엇인가
  - 선형공간에 내적을 도입해야 기저에 의존적이지 않은 전치 설명가능
  - __def__ : 선형사상 A와 내적 \\(\cdot\\)에 대해, \\[\overrightarrow\{x\}\cdot A(\overrightarrow\{y\}) = A^\{+\}(\overrightarrow\{x\})\cdot \overrightarrow\{y\}\\] 가 성립하는 사상 \\(A^+\\). 
  - 정규직교기저로 \\(A\\)를 표현하면, \\(A^+=A^T\\)가 됨.
- `det` : 부피 확대율. I행렬이 얼마나 커지는지로 생각하면 쉬움
  - \\(\text\{det\}A=\text\{det\}A^T\\). 
    - 잘 알다시피 `회전행렬`은 전치가 역행렬이 됨
      - 위의 전치의 정의로 생각해봐도 x를 아래로 30도 내리고 내적하나, y를 위로 30도 올리고 내적하나 각도는 같을 것
      - 회전행렬을 보면 skew-symmetric하고, nondiagonal entry는 sin뿐임. -각도를 넣으면 반대 부호가 나옴. -> 반대각으로의 회전 = transpose
    - 대각행렬의 det는 대각의 곱인 것도 부피로 그려보면 쉽게 이해가 감
      - 1st column = 1번째 좌표축 성분만 있음
      - 2nd column = a_12는 1번째 좌표축 성분이고, 무시해도 됨. 2번째 좌표축 성분만 넓이에 기여
      - ...


### Chap 2
<img src="{{ site.url }}/images/math/linear_alg/mapping.jpg" width="1000" class="center"/>  

- 전사 (`surjective`) = imA의 모든 y에 대한 상응하는 x가 존재
- 단사 (`injective`)= imA의 모든 y에 상응하는 x는 유일

Let \\(x\in R^n, y\in R^m, A\in R^\{n\times m\}\\)
- 결국 중요한 것은
  - \\(\text{dim ker}A\\) = 커널 (널스페이스)의 차원. 일단 원래 공간 \\(R^n\\)에서의 값임 \\(\text{dim ker}A \leq n\\)
  - \\(\text{dim im}A\\) = 사상의 이미지의 차원. 일단 목적공간 \\(R^m\\)에서의 값임 \\(\text{dim im}A \leq m\\) 
- \\(\text{rank}A\\) = \\(\text{dim im}A\\) 가 원래 공간의 차원 수 n와 같으면 단사, 목적 공간의 차원 수 m과 같으면 전사
- 차원정리 \\(\text{dim ker}A+\text{dim im}A=n\\). 증명 책에 있는데 귀찮아서 아직 안봄...

1. 단서가 부족한 경우 = 가로가 긴 경우 = \\(m<n\\)
   - surjective는 가능. injective는 안됨
   - injective하려면 \\(\text{dim ker }A=0\\)이어야 함. \\(\text{dim im}A \leq m < n\\)이므로, 차원정리에 따라 \\(\text{dim ker }A>0\\)
2. 단서가 너무 많은 경우 = 세로가 긴 경우 = \\(n<m\\)
   - injective는 가능.  surjective는안됨
   - surjective하려면 \\(\text{dim im}A=m\\)이어야 함. 차원정리에 따라  \\(\text{dim ker}A+\text{dim im}A=n<m\\)이므로 불가