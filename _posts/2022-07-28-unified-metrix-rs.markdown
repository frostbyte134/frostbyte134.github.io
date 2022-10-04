---
layout: post
title:  "MULTI-VAE"
date:   2020-09-01 09:10:05 +0800
categories: math
use_math: true
tags: image_processing ML 
---

### Abstract, topical diversity
- for __offline eval__ of Recommder Systems (RSs), accuracy was de facto
  - recommendation diversity and novelty have become recognised to be critical to user's perceived utility
  - `accuracy-diversity dilemma` shows up
- propose new metric, derived from search system eval
  - combines topical diversity and accuracy
  - satisfies a set of desired properties (forumlated axiomatically)
- presented experimental eval

### Intro
a seq of decisions must be taken to determine the metrics
1. online vs offline
  - many select offline due to limited resources / chances
2. when using offline, 2nd decision arise
  - eval with error metric for the rating prediction task / eval with ranking metrics for top-n recommendations
  - many refs says ranking metrics lead to more user satisfaction
3. when eval with top-n on offline colab filtering, is to choose to what to measure
  - most common objective: accuracy of the recommendations
  - serendipity, novelty, diversity


Proposed unified metric for evaluationg top-n recommendations
- considers topical (aspect) redundancy and both personalized item and topical relevance
- focused on topical or aspect based diversity

### Axioms
1. aspect가 1개만 있고, 이걸 공유하는 아이템 i_p, i_p+k 에서 i_p+k의 relevance 가 더 높으면, 이 둘을 ranking에서 스왑했을 때 점수가 높아짐
2. 랭킹 차이가 동일해도, 초반 2개를 스왑하는게 후반 2개를 스왑하는 것 보다 점수 증가가 높음
3. aspect a_n'이 saturated 됐을 때 (s가 높음), a_n'을 갖고 있는 i_p+k의 relevance가 더 높아도 saturated되지 않은 a_n을 갖고 있는 i_p를 스왑하면, relevance가 높은 게 앞에 왔어도 랭킹의 점수가 낮아짐
4. 동일한 레이팅을 가진 아이템들이어도, 처음 하나만 온 게 훨씬 뒤에 온 N개보다 총 점수에 더 기여하는 large enough N이 있다 (upper bound)
5. 4의 반대 (레이팅이 충분이 높으면 맨 앞에 있는 것 보단, 쪼금 뒤에 N개가 있는 게 더 좋다), (lower bound)
6. 아이템의 레이팅이 같으면 더 선호하는 aspect가 있는 쪽을 선택
7. 