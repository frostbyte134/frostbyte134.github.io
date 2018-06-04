---
layout: post
title:  "BOJ 10891: Cactus? Not Cactus?"
date:   2018-06-04 14:20:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving dfs graph reference_problem need_review
problem: 10891
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  

방향그래프에서 각 노드의 사이클 개수를 세는 문제.

우선 난
1. dfs의 방문상태는 0 (not visited), 1(visiting), 2(visited)이며, 부모를 빼고 visiting중인 노드를 만나면 사이클이 있다고 판별
2. 사이클 판별시 사이클이 감지된 노드를 기록했다가, function stack에서 해당 노드가 나오기 전까지 마킹함

으로 풀었는데, 사실 저 마킹은 완벽한 방법이 아닌듯. 예를 들면 큰 그래프 안에 작은 그래프가 있는 경우, 작은 그래프 마킹때문에 큰 그래프 일부에서 제대로 기록이 안될 수 있을듯.

여러 답을 봤는데, 요약해보면
1. visiting중인 노드라는 조건은 dfs 방문순서가 자기보다 빠른으로 바꿀 수 있음
2. Koosaga님 답이 가장 깔끔해 보임. 부모노드를 기록해 놨다가 사이클 판별 시 부모노드를 돌며 사이클 갯수+1해줌.
  