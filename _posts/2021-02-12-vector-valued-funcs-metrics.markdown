---
layout: post
title:  "Vector Valued Functions, Metric Spaces"
date:   2021-02-12 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis
---

TODO: 관련 내용 볼때마다 보충하기

Theorem 4.15 
> If \\(f\\) is a continuous mapping of a compact metric space \\(X\\) into \\(R^k\\), then \\(f(X)\\) is closed and bounded. Thus \\(f\\) is bounded.

-> Theorem 2.41


Chap2의 Weierstrass정리는 애시당초 R^K에 대한 것임

Theorem 2.42
> Every bounded infinite subset of \\(R^k\\) has a limit point in \\(R^k\\)

Distances in \\(R^k\\) - defined by Theorem 1.37


The complex field : Theorem 1.24
- complex field가 field axiom 만족 (1.25)
- 거리를 complex conjugate를 이용해 \\(\|z\| = (z\bar z)^{1/2}\\)로 정의 - metric의 조건을 모두 만족 (1.33)


Theorem 1.35 슈왈츠 부등식
- for \\(a,b \in \mathbb{C}^n\\), \\(\| a^T\bar{b} \|  \leq \sum\_{j=1}^n \|a\_j\|^2 \sum\_{j=1}^n \|b\_j\|^2\\)
- 거리는 바로 위에 정의된 것 이용

Theorem 1.36 Euclidean space
- 일반적인 L2 norm 사용. 코시수열만 아니면 유클리디안 공간이나 그게 그거인 듯
- 이 책에선 L2 norm을 표시할 떄 \\(\|\|a\|\|\\) 쓰지 않음