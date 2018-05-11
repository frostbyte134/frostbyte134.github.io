---
layout: post
title:  "BOJ 2213: 트리의 독립집합"
date:   2018-05-11 16:03:00 +0900
categories: problem_solving
use_math: true
tags: problem_solving dp simulation
problem: 2213
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  
정답률이 높아서 방심했는데 역시 뭔가가 있었음..  

원래 트리의 지배집합은 본인을 포함하지 않으면 자식들을 포함하는 것이 이득이나, 노드에 weight가 매겨저 있으므로 본인을 포함하지 않더라도 자식또한 포함하지 않는 것이 좋을 수도 있음.

1. 본인을 포함하는 경우 - 자식들은 전부 포함하지 않는다.
2. 본인을 포함하지 않는 경우 -  
각 자식마다,  \\(\textrm\{max\}\\)(해당 자식을 포함하지 않는 경우, 포함하는 경우)를 다 구해서 더한 뒤

a, b 두 값을 비교해서 큰게 dp[본인]이 됨. 트리이므로 부분문제 구조가 성립.