---
layout: post
title:  "BOJ 1162: 도로포장"
date:   2018-02-23 22:14:05 
categories: problem_solving
use_math: true
tags: problem_solving graph need_review
---

<a target="_blank" href="https://www.acmicpc.net/problem/1162">https://www.acmicpc.net/problem/1162</a><br/>
우선..다익스트라 한번 돌리고 k번 점프류 dp로 풀랬는데 틀림.<br/>
<br/>
내 생각은 노드 n에서 k번째 포장을 사용해서 올 수 있는 최단거리 dp[k][n]은<br/>
dp[k-1][n]과 dp[k-1][주변노드]들의 최소값이라고 생각했는데, 이러면 멀리 있는 dp[k][엄청짧은노드]의 값이 propagation이 안됨.<br/>
<br/>
결국 해결책은 다익스트라를 2차원 그래프에 대해([n][k]) 돌리는거였음. 이 2차원 다익스트라는 좀 재밌는듯.<br/>
당연하지만 2번의 inqueue과정이 있다. 하나는 기존 다익스트라 (k변화 없음)고, 나머지 하나는 k가 1 상승하는 inqueue.<br/> 
<br/>
아그런데 생각해보니 k번 점프류 dp도 한번 bfs를 돌려주는데..그거 돌려줬으면 맞았을듯 ㅡㅡ;바보같이<br/>
어쨋건 이쪽이 구현이 훨 간편한 것 같다. 앞으로 k번 점프류 dp는 이 2차원 다익스트라로 풀어야지<br/>