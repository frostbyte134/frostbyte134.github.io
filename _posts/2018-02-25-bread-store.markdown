---
layout: post
title:  "BOJ 3109: 빵집"
date:   2018-02-25 21:32:05 
categories: problem_solving
use_math: true
tags: problem_solving reference_problem searching
problem: 3109
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  
1. 윗쪽부터 시작한다면 윗쪽으로 가는게 제일 좋다.

2. dfs로 가 봐서 길이 없던 곳이면, 밑에서도 갈 필요가 없음. 따라서 vis를 dfs 종료 시 다시 false로 바꿔 줄 필요가 없다는 점이 포인트.