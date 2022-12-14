---
layout: post
title:  "Matrix Factorization Techniques, for Recommender Systems"
date:   2020-09-21 09:10:05 +0800
categories: coding
use_math: true
tags: coding
---

<a href="https://datajobs.com/data-science-repo/Recommender-Systems-[Netflix].pdf" target="_blank">https://datajobs.com/data-science-repo/Recommender-Systems-[Netflix].pdf</a>


### Glossary
Recommender systems are based on one of two stragegies
* `content filtering` - creates __profile__ for each item/user
* `collaborative filtering` is based on past user behavior (explicit/implicit user scores on item)
  * domain free (only require user interactions, no domain-specific profiles)
  * suffer from `cold start` problem (requires user interaction data)
  * two major categories : neighborhood methods / latent factor models

#### Neighborhood models (collab. filtering)
- <a href="https://datajobs.com/data-science-repo/Recommender-Systems-[Netflix].pdf" target="_blank">figure 1 on the link</a>
- centered on computing the relationship between items or, alternatively, between users.
- a product's neighbors are other products that tend to get similar ratings when rated by the same user.

#### Latent factor models (collab. filtering)
- tries to explain the ratings by the latent factors, inferred from the rating patterns
- such factors comprise a computerized alternative to the aforementhioned human-created song genres (contents)
- often, rating is calculated as a inner prod between user vecror \\(R^f\\) and item vector \\(R^f\\), where \\(f\\) refers to the # of factors.
- 추가적인 정보 (implicit ratings)를 활용하기 쉬움
- 보통 explicit ratings - sparse mat, implicit ratings - dense mat이라 함

### Problem formulation
1. \\(f\\) : # of latent factors
2. for each item \\(i \in I\\), \\(q\_i \in \Re^\{f\}\\) : 아이템 i가 각 factor를 얼마나 보유하였는지
3. for each user \\(u\in U\\), \\(p\_u\in \Re^\{f\}\\) refers to the user's preference to each factor
4. rating \\(r\_\{ui\}\\) is caclculated as a __dot product__ \\(p\_u^Tq\_i\\), and a `rating matrix` (`utility matrix`?) is  
   <img src="{{site.url}}/images/math/linear_alg/strang/chap1/rating_mat.jpg" width="800">  

### SVD
* <a href="https://linear_algebra/2018/05/26/svd.html" target="_blank">SVD</a> decomposes rating matrix \\(R\in \|U\|\times \|I\|\\) into \\(U\in \|U\|\times \|U\|, \Sigma \in \|U\|\times \|I\|, V^T \in \|I\| \times \|I\|\\) 
* excluding rows/cols with 0 (or very small) singular values (\\(\Sigma \in f\times f\\)), we obtain \\(\text\{rank\} f\\) approximation!
* <a href="https://stats.stackexchange.com/questions/211686/why-does-the-reconstruction-error-of-truncated-svd-equal-the-sum-of-squared-sing" target="_blank">SVD로 구한 factorization이 rank k constraint하에서, 원래 행렬과의 MSE (Frobenious norm)가 가장 작은 행렬</a>이며, error는 singular value들의 제곱의 합 (frob norm은 sqrt를 안하니..)  
  <img src="{{site.url}}/images/math/linear_alg/strang/chap1/frob.jpg" width="700">  
  증명은 윗 페이지에. 어렵지 않음 (remember that, "Frobenius norm obviously is invariant under left- and right-multiplication by orthogonal matrices")
* 그러나 결국 SVD를 쓰려면, rating matrix가 완전해야 함. 결측값이 있을 때 좋지 않음 (일부만 사용 - overfitting의 우려, 잘못 사용)



### (Non-convex) optimization

- rating matrix가 완전하지 않아도 적용 가능 (+regularization)
- SGD / alternating least square
- problem formulation \\[ \text\{min\}\_\{q^\*,p^\*\} \frac\{1\}\{2\} \left[ \Sigma\_\{(u,i)\in K\} \left(r\_\{ui\}-q\_i^Tp\_u\right)^2 + \lambda (\|\|q\_i\|\|^2 + \|\|p\_u\|\|^2) \right] \\]
__is a nonconvex function__ (\\((q\_i^Tp\_u)^2\\) term이 nonconvex함. hessian이 positive definite해질 수 없는 form)


#### SGD
- 각 data point \\(r\_\{ui\}\\) 에 대해 에러 \\(e\_\{ui\} := r\_\{ui\} - q\_i^Tp\_u\\) 를 정의하면, 
  - \\(p\_u\\) 에 대한 target function의 derivative = \\(-e\_\{ui\}q\_i + \lambda p\_u\\)
  - \\(q\_i\\) 에 대한 targ func의 deriv = \\(-e\_\{ui\}p\_u + \lambda q\_i\\)
- 각각 negative gradient 방향으로 최적화 가능

#### Alternating Least Squares
- term 1개를 고정시키면 least square problem (quadratic programming)
- \\(p\_u, q\_i\\) 에 대해 각각 병렬화 가능
- 데이터가 많을 때 이를 효과적으로 handling할 수 있다고 함 (?) - Collaborative Filtering for Implicit Feedback Datasets

### Adding bias
- 사람마다, 아이템마다 bias가 있음 - 이를 반영
- \\(\hat\{r\}\_\{ui\} := \mu + b\_i + b\_u + q\_i^Tp\_u\\)
  - mu = 전체 평균
  - \\(b\_i\\) : 아이템의 평균, \\(b\_u\\) : 유저의 평균
- Now the problem becomes
\\[ \text\{min\}\_\{q^\*,p^\*\} \frac\{1\}\{2\} \left[ \Sigma\_\{(u,i)\in K\} \left(r\_\{ui\}-\mu -b\_u-b\_i-q\_i^Tp\_u\right)^2 + \lambda (\|\|q\_i\|\|^2 + \|\|p\_u\|\|^2 + b\_u^2+b\_i^2) \right] \\]
- notice that, we do not want basis to make rating deviate too far from \\(\mu\\)

### Cold start problem
use implicit feedbacks    
1. \\(N(u)\\) : a set of items for which user \\(u\\) expressed implicit preference  
  - new set of item factor \\(x\_i\in R^f\\)를 정의
  - 각 사용자 \\(u\\)마다, \\(\|N(u)\|^\{-0.5\}\sum\_\{i\in N(u)\}x\_i\\) 를 추가로 고려 (normalize해주는 것이 보통 좋다고 함. 크기가 다 다르니)
2. \\(\sum\_\{a\in A(u)\}y\_a\\) : user attribute도 추가로 고려 (이 경우, user attribute종류가 같다면 normalize필요는 없을 듯)

now the rating score becomes
\\(\hat\{r\}\_\{ui\} := \mu + b\_i + b\_u + q\_i^T\left[p\_u + \|N(u)\|^\{-0.5\}\sum\_\{i\in N(u)\}x\_i + \sum\_\{a\in A(u)\}y\_a \right]\\)

### Temporal dynamics
> Decomposing ratings into distinct terms allows the system to treat different temporal aspects seperately

- item biases \\(b\_i(t)\\) : item's (average) popularity may change over time
- user biases \\(b\_u(t)\\) : user change their baseline
- user preferences \\(p\_u(t)\\) : user's preferences, thinking, perception change over time

miscs : different confidence level \\(c\_\{ui\}\\) for each rating \\(r\_\{ui\}\\).

### 부록

> <a href="https://yamalab.tistory.com/67" target="_blank">https://yamalab.tistory.com/67</a> 의 내용을 정리함

`추천 시스템`
- 추천 시스템, 혹은 추천 모델링은 '특정 시점'에 '특정 고객'이 좋아할 만한 리스트를 찾아주는 것
- 서비스 관점에서 추천 시스템을 구축, 개발하는 입장에서 고려할 요소는 크게 4가지 정도이다. 추천 시스템은 거의 대부분의 경우 B2C 비즈니스 환경에서 적용된다. 그래서 당연하게도 고객, 아이템을 고려해야 하고 추가적으로 시스템의 업데이트와 추천 시스템의 알고리즘적 성능을 고려해야 한다.
- state of the art의 취급을 받고 있는 CF(Collaborative Filtering)이나 DL(Deep Learning) - 빅데이터가 필요
- 최신의 알고리즘보다는 훨씬 쉽고 간단하면서도 연산량이 작고, 그럼에도 불구하고 고급 알고리즘들과 비슷한 성능을 낼 수 있는 Association Rule
- 추천 시스템의 장애 요소
  - __Sparsity Problem__ (빈익빈 부익부 - 서비스가 커지면서 양적으로 성장하면 제곱으로 나타남)
  - __Information Utilization Problem__ - 클릭 등의 Implicit score 해석이 어려움 (간접적인 선호 / 사용기록)
    - Explicit Score가 좋지만 sparsity problem이 나타날 것
- 추천의 종류
  - 개인화 추천 (PR, Personalized Recommendation)
    - 대표 : CF, Collaborative Filtering- 
  - 비-개인화 추천 - rating기반, 현재 상품 기준. 
    - cold-start에 비교적 적응가능. 또는 PR이 적용 불가능한 곳
    - 대표 : Association Rule
  - Attribute-based
    - 아이템 자체의 content 활용. CF와 상호 보완적이라 함
    - 대표 : Content based approaches
- 추천 시스템의 평가
  - Accuracy, Precision, Recall, F1-score, ROCurve, RMSE, MAPE
- 추천 알고리즘
  - 통계 기반 모델링
    - 카이 스퀘어 제곱 (?), kl-divergence
  - CF 기반
    - neighborhood model (memory based)
      - user based
        - 유저(row) - 아이템(col)의 행렬을 만든 뒤, row vector가 유사한 사람들끼리 추천
        - 유사도 = euc, cos, jacard, pearson
      - item based
        - ?
      - 메모리 기반 알고리즘에서 rating의 빈공간을 추론하는 방법은, 아래에서 설명하게 될 MF와 문제가 동일하지만 해결 방식이 다르다. 메모리 기반 알고리즘에서는 빈공간을 유사 유저나 아이템의 유사도 계수를 이용하여 채워넣는 방법, 혹은 regression 문제로 만들어 해결하는 방법 등으로 채워나간다.
      - SVD를 비롯한 MF에서 목적함수는, Predicted rating을 구하는 Matrix Completion의 경우, 최적의 해(Rating – Predicted Rating의 최소)가 없이 근사값을 추론하는 문제이다. gradient descent 나 alternating ls 쓴다고 함
    - model based (matrix factorization)
      - 유저 = 행, 상품 = 열
        - latent vector
          - PCA의 eigen-vec+vals?
          - SVD의 diagonal이 latent vector인듯
          - 이를 Matrix Completion의 관점에서 보면, A 행렬에서 rating이 존재하는 데이터를 이용해 미지의 U, Σ, V를 학습하여 Completed 된 행렬 A`를 만들어내는 것이다. ?
            - https://yamalab.tistory.com/92?category=747907 gt matrix R을 어떻게 구해서 실제 문제에 어떻게 적용시킨다는건지 모르겠음



https://ratsgo.github.io/from%20frequency%20to%20semantics/2017/10/06/attention/