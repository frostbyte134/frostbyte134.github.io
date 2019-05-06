---
layout: post
title:  "BOJ 2104: 부분배열 고르기"
date:   2018-03-11 13:59:00
categories: problem_solving
use_math: true
tags: problem_solving dnq segment_tree
problem: 2104
---
<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/><br/>

문제가 쉬워 복습에 넣지 않음.  

1. 핵심은 Divide and conquer 구조를 파악하는 것. A[i],A[j] 구간에서 A[k]가 최소값이라면, 최소값이 A[k]인 동안은 그냥 i,j 구간으로 잡는게 값이 제일 크다. 따라서 A[k]가 없는, A[i],A[k−1] 구간과 A[k+1],A[j] 구간의 값들만 고려하면 됨.

2. 구간트리. 근데 왜 난 구간트리에 인덱스도 반환하도록 짜놨지?...
복습할 땐 구간트리 없이 풀어보자. 종만북의 통나무 쪼개기처럼 될듯?

ios::sync_with_stdio(false);
cin.tie(0);