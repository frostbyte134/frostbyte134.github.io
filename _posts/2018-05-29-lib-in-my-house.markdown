---
layout: post
title:  "BOJ 2872: 우리집엔 도서관이 있어"
date:   2018-05-29 16:20:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving greedy
problem: 2872
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  

1. 최대 이동횟수는 N-1
2. 가장 큰 책보다 오른쪽에 있는 애들은 어차피 옮겨야 함
3. 가장 큰 책보다 왼쪽에서는, 가장 큰 책을 기준으로 (좀 떨어져 있어도) 1씩 차이나는 내림차순으로 있는 책들은 옮길 필요가 없음. 나머지는 옮겨야 됨. 왜냐하면
	1. 순서가 반전된 책 2개는 뒤의 책을 빼야 하고
	2. 순서가 1이상 차이나는 책들은, 중간에 책을 낄 수 없기 때문에 중간 책들을 앞으로 끌어오고 다음 작은 책을 앞으로 옮겨야 됨.
	
따라서 N을 기준으로 올바른 내림차순인 책들만 뺴놓고 다 옮겨야 함.
	