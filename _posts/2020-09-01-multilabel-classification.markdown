---
layout: post
title:  "MLC"
date:   2020-09-01 09:10:05 +0800
categories: math
use_math: true
tags: math
---

<a href="https://careers.kakao.com/jobs/P-10200?skilset=Algorithm_Ranking" target="_blank">https://careers.kakao.com/jobs/P-10200?skilset=Algorithm_Ranking</a>

### 지원 동기
1. 현 회사
  - 부정적인 이야기는 최대한 안하는 것이 좋은 듯
  - 

### 지원 직무에 대한 나의 강점
- 

### 갈등, 해소법
- 

### 참고 자료
- <a href="http://economychosun.com/client/news/view.php?boardName=C00&t_num=13606175" target="_blank">http://economychosun.com/client/news/view.php?boardName=C00&t_num=13606175</a>
  -  `협업 필터링`과 `콘텐츠 기반 필터링`이 함께 사용된다. 협업 필터링은 이용자의 콘텐츠 사용 패턴을 분석해 추천하는 방식으로, 클릭이나 평점 등 기호 데이터를 활용한다. __콘텐츠 사용 패턴이 비슷한 사람들이 서로 비슷한 것을 선호한다고 가정하고 추천하기 때문에__ 사용자에게 친숙하고 반응이 좋은 콘텐츠들을 찾아준다. 그러나 협업 필터링은 __비슷한 취향에서 벗어난 새로운 콘텐츠를 추천해주기 어렵다는 한계가__ 있다. 이를 __보완하는__ 것이 콘텐츠 기반 필터링이다. 콘텐츠 자체의 내용을 분석해 유사한 콘텐츠를 찾는 기술이다. 특정 가수의 음악을 좋아하는 사람에게 그 가수와 비슷한 분위기를 가진 가수를 추천하거나 축구 뉴스를 좋아하는 사람에게 월드컵 소식을 추천해주는 식이다. 협업 필터링과 콘텐츠 기반 필터링은 각각 장점과 한계가 있다. 따라서 한쪽만 단독으로 사용하지 않고, 혼용하거나 다른 방식의 추천 기술과 함께 사용한다.”
  -  큐레이션의 효과를 높이는 데 중요한 것은.
     -  사용자 데이터 & 컨텍스트 수집 (데이터가 사용된)
  - 큐레이션 비중을 기계 대 사람이 80 대 20이 되는 수준으로 만드는 게 최적이라고 생각한다.
- <a href="https://brunch.co.kr/@kakao-it/333" target="_blank">https://brunch.co.kr/@kakao-it/333</a>
- <a href="https://brunch.co.kr/@kakao-it/72" target="_blank">https://brunch.co.kr/@kakao-it/72</a>
- <a href="https://brunch.co.kr/@goodvc78" target="_blank">https://brunch.co.kr/@goodvc78</a>
- <a href="https://github.com/kakao/buffalo" target="_blank">https://github.com/kakao/buffalo</a> matrix factorization library?
  - ALS, BPR (Bayesian Personalized Ranking Matrix Factorization?) 을 Python, C++로 구현

### Embedding
`Frequency based Embedding`
- Count Vector : construct a matrix (row = terms, col - documents)
- TF-IDF Vector
  - Ideally, what we would want is to down weight the common words occurring in almost all documents and give more importance to words that appear in a subset of documents.
  - TF = (Number of times term t appears in a document)/(Number of terms in the document)
    - eg: A document about Messi should contain the word ‘Messi’ in large number.
  - IDF = log(N/n), where, N is the number of documents and n is the number of documents a term t has appeared in.
    - so, the IDF of common words should be low
  - TF-IDF : TF X IDF
- Co-Occurrence Vector

- <a href="https://github.com/ratsgo/embedding" target="_blank">https://github.com/ratsgo/embedding</a>


- <a href="https://lovit.github.io/machine%20learning/2019/03/17/attention_in_nlp/" target="_blank">https://lovit.github.io/machine%20learning/2019/03/17/attention_in_nlp/</a>