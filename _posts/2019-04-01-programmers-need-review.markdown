---
layout: post
title:  "Programmers - need reviews"
date:   2019-04-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review
---

### 저울
<a href="https://programmers.co.kr/learn/courses/30/lessons/42886" target="_blank">https://programmers.co.kr/learn/courses/30/lessons/42886</a>

첨에 엄청 고민했다. 동전조합 dp같이 생겨먹어서..  
결국 40분만에 풀긴 품. 좀 더 빨리 풀어여 할 것 같은데..
1. 동전을 크기순으로 정렬
2. 작은 동전들로 i까지 만들고, 현재 동전이 w라면, i+w까지도 만들 수 있다.

### 큰 수 만들기
<a href="https://programmers.co.kr/learn/courses/30/lessons/42883" target="_blank">https://programmers.co.kr/learn/courses/30/lessons/42883</a>

어떤 수에서 k개의 숫자를 제거했을 시, 만들 수 있는 가장 큰 숫자는?
1. 앞쪽 숫자부터, 내림차순이 되는 것이 가장 좋음
2. 숫자 1개씩 제거한다고 할 시, 뒤쪽의 숫자를 제거해서 얻는 이득이 전혀 없음 (앞쪽 작은수를 제거 안하면, 어차피 작음)
3. ind-1로 계속 비교 / stack 이용

### 구명보트
<a href="https://programmers.co.kr/learn/courses/30/lessons/42885" target="_blank">https://programmers.co.kr/learn/courses/30/lessons/42885</a>

`2명`이라는 제한이 있으므로,
1. 가장 가벼운 사람부터 (index - i)
2. 자기와 맞는 가장 무거운 사람을 찾음 (index - j)
3. 찾을 시, 보트 1개 할당 맟 j -= 1 (재사용. 첨에 재사용을 안해서 TLE 났다. 숫자 3개 합쳐서 0 만드는 문제를 생각하고 재사용함. 어차피 다음 번 i는 더 무거운 사람이 나올것이므로, 더 가벼운 사람만 고려하면 됨)
4. i==j일시 처리, 나머지 처리

### 조이스틱
<a href="https://programmers.co.kr/learn/courses/30/lessons/42860" target="_blank">https://programmers.co.kr/learn/courses/30/lessons/42860</a>

1. 각 노드를 방문시, 무조건 A를 해당 Char로 바꿔줘야 하므로, 재방문 필요 X. 결국 주어진 조건(0\\(\rightarrow\\)n-1 가능, n-1\\(\rightarrow\\)0 이동불가)에서 가장 효율적인 방문순서를 찾는 문제로 바뀜. 
2. A가 가장 길게 연속하는 것을 찾아, 해당 연속A를 잘 이용하게 짜면 됨. 케이스를 좀 더 철저하게 고려하자.
3. 문제를 제대로 읽지 않아서 엄청 해맴...ㅜㅜ
