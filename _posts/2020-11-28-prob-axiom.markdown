---
layout: post
title:  "Probability models and axioms"
date:   2020-11-28 08:00:05 +0800
categories: probability
use_math: true
tags: math probability 
---

긴 복습의 시작....? 필요할 지는 뭐 모르는 거니까..

- <a href="https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-i-the-fundamentals/MITRES_6_012S18_L01.pdf" target="blank">https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-i-the-fundamentals/MITRES_6_012S18_L01.pdf</a>
- <a href="https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf" target="_blank">https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf</a>

TODO: 책 읽고 내용 추가


### Probability models

<img src="{{site.url}}/images/math/prob_model.png" width="1000">

- `sample space` \\(\Omega\\) : set of all possible, fine graned outcomes of an experiment  
    The sample space must be,
    - Mutually exclusive
    - Collectively Exhaustive
    - At the __right__ granularity (TODO: add link)
- the `probability law` assigns a non-negative number \\(\text\{P(A)\}\\) to a set \\(A\\) of possible outcomes (\\(A\\)=`event`)
- The probability laws must satisfy following `probability axiom`
  - Non-negativity \\(P(A)\geq =0\\)
  - Normalization \\(P(\Omega) = 1\\) 
  - Countable additivity : If \\(A\_1,A\_2,...\\) is an infinite sequence of disjoint events, \\[P(A\_1 \cup A\_2 \cup ... ) = P(A\_1) + P(A\_2) + ...\\]
    - additivity holds on countable sets. we cannot assign probability to some strange "area"s