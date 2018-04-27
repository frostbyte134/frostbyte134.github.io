---
layout: post
title:  "BOJ 2295: 세 수의 합"
date:   2018-03-01 22:02:05 
categories: problem_solving
use_math: true
tags: problem_solving need_review reference_problem
problem: 2295
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

집합에 있는 3개 수의 합이 집합 내에 있는 경우 중, 최대 케이스를 구하는 문제. 
N이 작으므로 각 항의 합 N2개를 정렬했다가, 합이 될 원소와 1개 원소의 차이를 이진탐색으로 찾음. 
\\[O(N^2\log{N^2})\\]

\\(O(N^2)\\)의 풀이도 있다는데 상상도 안가네..복습할 때 볼까