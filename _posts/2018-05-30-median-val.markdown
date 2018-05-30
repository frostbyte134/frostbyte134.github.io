---
layout: post
title:  "BOJ 9426: 중앙값 측정"
date:   2018-05-30 16:20:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving segment_tree reference_problem
problem: 9426
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  

크기 K인 배열에 숫자가 맘대로 들어가고 동시에 나감. 이 때 median을 O(K)보다는 빠르게 구하는 문제.
  
숫자의 범위가 작으므로, 숫자를 count하는 구간트리를 만듬. median번째 ((K+1)/2) 나타난 숫자가 뭔지 반환하는 쿼리는 기억해 두자.  

  