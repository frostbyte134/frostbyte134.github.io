---
layout: post
title:  "BOJ 9376: 탈옥"
date:   2018-02-25 21:20:05 
categories: problem_solving
use_math: true
tags: problem_solving searching need_review
problem: 9376
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  
1. 문은 결국, 레벨별로 생각할 수 있음. 그리고 레벨만 구할라면 (내가 했던 방법인) 2중 큐보다는 vis를 dist로 대체하는 것이 간편해 보인다.  
2. 난 (두명에서 출발하는) 레벨을 전부 샌 후, 만나기 전까지와 만난 후를 따로 세려고 했었음. 여기서 생긴 문제는, 탈출했을 때 어느 문을 사용했는 지 모르므로 문이 겹칠 수도 아닐 수도 있다는 것.  
3. 바깥에 테두리로 두르고 탈출용 1인을 더 추가하기 (핵심)  
3명이서 만난 레벨 (벽이면 1명만 문을 열면 되므로 -2. 답이 벽이 아닌 곳에 있는 경우도 있다. 그냥 빠져나갈 수 있는 경우.) 중 최소가 답.   
  