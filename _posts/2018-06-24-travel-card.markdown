---
layout: post
title:  "BOJ 10456: Travel Card"
date:   2018-06-24 10:45:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving dp
problem: 10456
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

대전리저널 본선문제. 본선땐 많이 풀었다던데 데이터가 좀 약했다고 함.

많이 보던 dp문제긴 한데, 교통카드를 겹쳐서 쓸 수 있는 점이 특이함.

기차만 되는 교통카드가 없으므로, 버스만 되는 교통카드를 쓸 땐 기차를 어떻게 최소한의 비용으로 커버할지 알아야 함. 이 부분을 나이브하게 접근했다가 많이 틀렸다. 이것도 결국 dp로 계산.