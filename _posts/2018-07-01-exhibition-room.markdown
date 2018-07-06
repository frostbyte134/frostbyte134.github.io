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

난 dp[i]보다 dp[i-j]가 클 수 있다고 생각해서 구간트리를 썼는데, dp[i]가 dp[i-1]보다 크게 비교만 해주면 이 속성을 강제할 수 있으니 구간트리가 필요없음.