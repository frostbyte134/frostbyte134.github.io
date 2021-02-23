---
layout: post
title:  "BOJ 2261: 가장 가까운 두 점"
date:   2018-03-30 22:14:00
categories: problem_solving
use_math: true
tags: problem_solving geometry line_sweep parametric_search reference_problem
problem: 2261
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/><br/>
  
기초적인 line sweep 문제.


\\(N\leq 100,000\\) 개의 점이 있을 시, 가장 가까운 두 점의 거리는? pairwise & exhaustive \\(O(N^2)\\)는 TLE.


x좌표로 정렬하고, 검사할 점들의 집합 \\(\mathcal{S}\\)를 유지하며 진행. 이 집합은 binary tree로 구현 (C++: set)하며, \\(\mathcal{S}\\)의 내부정렬은 y좌표 기준.



(1) 정렬된 x좌표를 도는 iteration마다,  
지금까지 찾은 답이 ans라 했을 시, 현재 점과 x좌표 차이가 ans이상 나는 점은 검사할 필요가 없을 것임.  
\\(\mathcal{S}\\)의 시작번호를 \\(index\\) 변수에 저장해 두었다가, 매 iteration마다 S에 대한 검사를 수행. x좌표 차이가 ans이상 나는 경우 \\(index\\)번호의 점을 \\(\mathcal{S}\\)에서 삭제하고 1 증가시킴 (while문). 차이가 나지 않는 경우 해당 iteration에서의 \\(\mathcal{S}\\) 검사는 종료.


(2) y좌표 차이가 ans이상 나는 점 또한 검사할 필요가 없을 것임. \\(\mathcal{S}\\)를 y좌표 기준으로 정렬해놓았으므로 parametric search 수행가능. 구현에서는 간단하게 `set`의 lower_bound 및 upper_bound 함수를 사용.


결국..x좌표에 대한 가지치기는 `line sweep`으로, y좌표에 대한 가지치기는 `parametric search`로 수행했다는 것이 중요. 한번 \\(\mathcal{S}\\)에 넣은 점은 다시 넣지 않고, 각 삽입삭제마다 \\(\log N\\)이 걸리므로 결국 \\(O(N\log N)\\).



1. 3차원은 어쩌려나?..

2. 통나무 쪼개기 식으로 Divide and conquer로 풀 수 있는듯한데..
<hr>
<br/><br/>
Next:  
<a href="https://code.google.com/codejam/contest/dashboard?c=311101#s=p1" target="_blank">https://code.google.com/codejam/contest/dashboard?c=311101#s=p1</a>  
<a href="https://www.acmicpc.net/problem/7574" target="_blank">https://www.acmicpc.net/problem/7574</a>
<br/><br/>
References:  
<a href="https://www.acmicpc.net/blog/view/25" target="_blank">https://www.acmicpc.net/blog/view/25</a>