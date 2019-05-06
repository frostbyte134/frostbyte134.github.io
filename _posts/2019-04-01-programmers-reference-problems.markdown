---
layout: post
title:  "Programmers - reference problems"
date:   2019-04-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review reference_problem
---

### 전화번호 목록
<a href="https://programmers.co.kr/learn/courses/30/lessons/42577" target="_blank">https://programmers.co.kr/learn/courses/30/lessons/42577</a>

1. i번째와 i+1번째를 비교하면서 먼가 하고 싶을 시, zip(ary, ary[1:])
2. 문자형의 배열이 있을 시, 특정 문자가 다른문자의 접두어가 되는지 여부만 찾는 문제였음.  
난 그냥 길이가 짧길래
	1. string 길이로 정렬 후
	2. 긴 것부터 탐색하며 ary[:i] 길이별로 해쉬 만들어서 비교했는데  

결국 정렬을 할 거면, 그냥 string으로 정렬하면 되는 거였음. 

