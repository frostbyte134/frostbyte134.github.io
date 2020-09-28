---
layout: post
title:  "추천시스템....?"
date:   2020-09-21 09:10:05 +0800
categories: coding
use_math: true
tags: coding docker
---



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