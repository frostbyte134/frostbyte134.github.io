---
layout: post
title:  "BOJ 3974: Time To Live"
date:   2018-03-13 10:29:00 +0900
categories: problem_solving
use_math: true
tags: problem_solving simulation graph
problem: 3974
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/><br/>
  
(__트리의 최장거리 구하기__)  

트리에서,

1. 각 노드별로, 다른 노드에 도달할 수 있는 최대거리를 구함.
2. 그 거리 중 가장 작은 거리가 답.


이건 결국, 트리에서의 최장거리를 구한 후, (최장거리+1)/2로 구할 수 있음.   
  
__트리의 최장거리 구하기__ (edge weight = 1): 아무노드에서나 BFS를 돌리면, 가장 나중에 bfs가 끝나는 곳이 최장거리의 한쪽 끝임.  
  
`proof by contradiction`: 만약 아니라면,  
![hey]({{ site.url }}/images/ps/time_to_live.png)  
ex)최장거리: m-n. 만약 h부터 시작한 bfs에서 d가 가장 나중에 끝났다면, d-f경로를 m-f대신 갖다붙여 최장거리인 m-n보다 더 긴 거리를 만들 수 있을 것.
따라서
1. bfs 한번 돌려서 가장 늦게 끝나는 노드에서
2. 다시 한번 bfs를 돌려서 (길이+1)/2가 답임.