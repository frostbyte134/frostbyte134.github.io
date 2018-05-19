---
layout: post
title:  "BOJ 13415: 정렬 게임"
date:   2018-05-19 09:49:00 +0900
categories: problem_solving
use_math: true
tags: problem_solving segment_tree
problem: 13415
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/><br/>
  
  
08:45~09:30  

{:.deccounter}
1. 구간트리. 근데 내가 구간트리를 써서 푸는 문제의 상당수는 stl set으로 쉽게쉽게 풀 수 있는 것 같은데..
2. 가장 최근 정렬된 구간이 우선순위를 지님. 가장 높게 지정된 index부터 정렬이 되었을 것이므로, 역순으로 가장 최근 정렬결과를 고려하며 구간트리를 갱신. 
{:.deccounter}
복습이 필요한 문제 같진 않음.