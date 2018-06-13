---
layout: post
title:  "BOJ 2215: 원형 네트워크"
date:   2018-06-11 10:45:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving search reference_problem
problem: 2215
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

그리디문제라길래 계속 봤는데 그리디적인 속성은 별로 없었다. 부분문제 구조도 없는 것 같고..아무리 봐도 다 해야하는 것 같았는데 2^1000은 안될 거 같았음..

답은 이전에도 풀어 본 적 있는 패턴 (링크 못찾음). 선형 구간을 탐색할때의 마킹을 해줘야 함. 현재에서는 +1하고 연결된 곳에서는 -2를 해주는 테크닉도 깔끔한듯 (연결된 곳에서도 +1을 할 것이고, 연결된 곳의 연결된 곳인 현재에는 다시 방문하지 않을 것이므로 괜찮음).