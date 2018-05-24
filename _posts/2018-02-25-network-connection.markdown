---
layout: post
title:  "BOJ 3780: 네트워크 연결"
date:   2018-02-25 21:31:05 
categories: problem_solving
use_math: true
tags: problem_solving djset
problem: 3780
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>


약간 disjoint set의 응용 문제. 클러스터 l을 노드 r에 붙일 때, find(nd)는
1. 일단 현재 노드 nd의 부모를 tp에 저장해 놓고
2. gp = find(P[nd])를 호출하여 dist[tp]를 제대로 계산한다
3. dist[nd] += dists[tp]
4. return gp 
  
