---
layout: post
title:  "BOJ 2316: 도시 왕복하기"
date:   2018-02-23 22:14:05 
categories: problem_solving
use_math: true
tags: problem_solving graph need_review need_revise
---

<a target="_blank" href="https://www.acmicpc.net/problem/2316">https://www.acmicpc.net/problem/2316</a><br/>
  
소스-싱크가 있는 네트워크에서, 소스로부터 싱크까지 동시에 유지할 수 있는 가장 많은 path수를 찾는 문제. 
동시에 유지해야 하므로, 방문을 1번으로 제한하는 네트워크 플로우로 풀 수 있음. 노드 내부에 capacity가 1인 엣지를 만들면 됨.  
  
나는 각 u, v페어에 대해  
```c
if (u != src && u != dst){
   cap[u + GAP][v] = INF;
} else cap[u][v] = INF;

if (v != src && v != dst){
   cap[v + GAP][u] = INF;
} else cap[v][u] = INF;
```
로 네트워크 모델링을 했는데..더 좋은 방법이 있을 것 같긴 한데 졸려서 모르겠다.   
복습할땐 디닉으로 풀어야지 ㅎㅎ  