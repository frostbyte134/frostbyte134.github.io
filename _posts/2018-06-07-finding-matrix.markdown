---
layout: post
title:  "BOJ 1687: 행렬 찾기"
date:   2018-06-07 09:20:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving need_review
problem: 1687
---


<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  

2차원 dp 문제. 직사각형의 크기 세기.
1. 2차원 부분합으로 300X300X300X300. 예상한대로 TLE
2. <a href="{{site.url}}/problem_solving/2018/05/21/hist-maximum.html" target="_blank">히스토그램</a> 문제를 각 열에 대해 한다고 생각하면 될듯. 300X300은 검사해야 하는 게 당연하나, 현재 위치에서 <--쪽만 고려한다고 했을 시, 끊어진 부분부터는 생각할 필요가 없음. 그러므로 얼마나 끊어졌는지를 세어놨다가 히스토그램 문제처럼 위로 300을 더 가며 검사하면 됨.
3. 아예 히스토그램처럼 300X300도 될거 같은데?..