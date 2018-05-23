---
layout: post
title:  "BOJ 1989: 부분배열 고르기 2"
date:   2018-05-20 09:26:00 +0900
categories: problem_solving
use_math: true
tags: problem_solving segment_tree dnq reference_problem
problem: 1989
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/><br/>
  
  
08:45~09:30  

{:.nestedcounter}
1. 구간트리  
<a href="{{site.url}}/problem_solving/2018/03/11/select-partial-set.html" target="_blank">link</a>
2. 스택  
이 `통나무 쪼개기`류의 문제에서 결국 구해야 하는 건,  각 A[i]당 왼쪽, 오른쪽으로 A[i]보다 큰 숫자들로 이루어진 배열 A[l]~A[r]과의 연산 \\[\textrm\{func\}(A[i],\\>psum(A[l],\\>A[r]])\\]임. 스택에는 증가하는 숫자들만 들어있다고 가정. 이러면 스택에 아이템이 1개만 있다는 소리는 이 아이템이 지금까지 나온 아이템 중 가장 작다는 이야기임.
	1. st.top > A[i]일 시,  
		2. `st.pop()`수행.  
		3. st.top을 기반으로 하는 배열은 오른쪽으론 \\(r=i-1\\)에서 끝. 왼쪽에선 스택에 increasing num까지만 있으므로, st.top의 인덱스+1까지가 끝임. \\(l=\textrm\{st.top.index+1\}\\).  
		스택이 비었을 시는, 지금 pop된 아이템이 지금까지 중 제일 작으므로 \\(l = 0\\)임.  
		마지막 배열에 최솟값을 삽입해주면 남은 스택 처리도 됨.
	2. st.top <= A[i]일 시,  
	더 긴 배열을 만들 수 있으므로 계속함.
{:.nestedcounter}
