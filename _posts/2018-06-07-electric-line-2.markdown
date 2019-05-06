---
layout: post
title:  "BOJ 2568: 전깃줄 - 2"
date:   2018-06-07 16:45:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving dp parametric_search need_review lis
problem: 2568
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  

Lis문제. 오랬만에 봐서 그런지 다 까먹음 ㅜㅜ
1. 이진탐색  
배열 ary에서 candidate solution 배열 seq를 유지하며, i번째 원소에 대해
	1. seq의 의 끝번보다 ary[i]가 큰 경우. ary[i]를 뒤에 붙인다.
	2. 아닌 경우, seq에서 ary[i]보다 같거나 큰 가장 작은 seq[j]를 ary[i]와 교환한다.  
	이 때 주의할 점은, 이름이야 candidate solution이라고 지었지만, 교환되었을 시의 seq배열은 진짜 candidate solution이 아니라는 것. 교환된 seq[j]는 seq[j]다음 배열들이 전부 교환되어 끝까지 갔을 때야 비로소 진짜 candidate solution이 됨.  
	교환이유: 당연하지만 ary[j]는 seq[j-1] 뒤에 붙이는 것이 가장 좋다. 그러나 ary[i]의 위치 상 seq[j-1]와 seq[j] 사이에 낄 수는 없으므로, seq[j]와 교환하는 것이 최선. 이렇게 점점 배열 컷이 낮아지다 보면, 나중에는 훨씬 작은 숫자를 뒤에 붙일 수 있기 때문.  
	이걸로 LIS를 찾을 수 있다는 걸 증명하려면 어떻게 해야 하나..귀류법인가?
2. 구간트리  
숫자를 우선 (값, 인덱스)의 페어로 정렬하고, 값이 작은 숫자부터 자기의 인덱스보다 보다 뒷구간에서 가장 큰 LIS값 (구간트리로 찾음)을 가져와 +1하면 됨.
