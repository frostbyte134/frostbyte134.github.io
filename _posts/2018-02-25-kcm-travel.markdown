---
layout: post
title:  "BOJ 10217: KCM Travel"
date:   2018-02-25 22:33:05 
categories: problem_solving
use_math: true
tags: problem_solving reference_problem graph shortest_path
problem: 10217
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

개인적으로 이런 dp를 reachability dp라고 부르는 중.  
  
  
```풀이 1.```  
최단거리는 결국 길이 N밖에 안되므로, N번 돌면서
각 노드(N개) 에서 코스트 M이내에 도달가능한 곳의 최소값을 갱신해주면 됨.  

\\[ O(N * N * M) \\]

(시간내에 되나? 벨만포드 쓴거랑 마찬가지인거같은데 될듯?)

```풀이 2.```  
각 코스트 M부터 0까지,  
각 노드별로,  
현재노드에 도달한 적이 있을 시, 주변노드의 최소값을 갱신해 주면 됨.  
왜 바깥for문이 M부터인가?  
ex) 노드가 n이라고 가정. n에 대해 M을 0부터 전부 체크해버리므로, n번 노드는 다시는 체크하는 일이 없음. 그러나 번호가 n이상인 노드를 포함하는 경로에서 더 좋게 n번째 노드로 도달하는 일이 있을 수도 있다.  
\\[O(N*M)\\]