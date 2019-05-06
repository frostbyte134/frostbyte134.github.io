---
layout: post
title:  "BOJ 2515: 전시장"
date:   2018-07-01 10:45:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving dp
problem: 2515
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

난 i<j일때 dp[j]보다 dp[i]가 클 수 있다고 생각해서 구간트리를 썼는데 (뒤에까지 찾아봐야 하므로 max쿼리용 구간트리), dp[i]가 dp[i-1]보다 크게 max연산만 해주면 이 속성을 강제할 수 있으니 구간트리가 필요없음.

dp[j]서 만들 수 있는 그림 시퀸스는 당근 dp[i]에서도 만들 수 있으므로 위의 속성강제가 됨.