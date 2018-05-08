---
layout: post
title:  "BOJ 3430: 용이 산다"
date:   2018-02-25 21:20:05 
categories: problem_solving
use_math: true
tags: problem_solving greedy
problem: 3430
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

2개가 쌓이면 끝나고, 호수는 꽉 찬 채로 시작함.
0을 만났을 시,
1. 같은 호수끼리는 당연히 먼저 오는 호수를 먼저 먹어야 함.
2. 다른 호수끼리도, 나중에 오는 호수를 먼저 먹어서 보는 이득이 없음.
