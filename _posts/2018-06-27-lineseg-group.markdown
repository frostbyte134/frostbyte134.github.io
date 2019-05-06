---
layout: post
title:  "BOJ 2162: 선분 그룹"
date:   2018-06-27 20:45:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving geometry djset
problem: 2162
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

1. 선분이 l>r일시 스왑해주기.
2. ccw(cross prod)를 이용한 교차여부 판별. cprod(r2-r1,l1-r1)\*cprod(r2-r1,l2-r1)과 cprod(l1-l2,r1-l2)\*cprod(l1-l2,r2-l2)의 부호가 다르면 교차함
3. 둘 다 0일시는 일직선에 놓인 경우. 이 떈 교차하지 않는 경우의 역이 더 찾기 명확함.
4. disjoint set