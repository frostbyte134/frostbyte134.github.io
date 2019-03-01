---
layout: post
title:  "leetcode - Next permutation"
date:   2019-03-01 1:59:00
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review
---

<a href="https://leetcode.com/problems/next-permutation/" target="_blank">https://leetcode.com/problems/next-permutation/</a>

Permutation의 다음번째는 무엇인가? (lexicographical order)

1. Permutation이므로 swap
2. lexi-order이므로, 자릿수가 작은 숫자를
	1. 자기보다 자릿수가 더 낮으면서
	2. 값은 더 큰 숫자
	3. 중 최소의 숫자와 바꿔야 함.
	
	이렇게 i번째 숫자를 j(<i) 번째 숫자와 바꾸었으면, i-1번째부터는 작은 순으로 정렬해주어야 함. 그래야 바로 다음번이 되니까.
3. 위에 해당하는 경우가 없을 시, 모든 숫자는 자기보다 자릿수가 낮은 숫자보다 큼. (ex - 4321) 문제에서 이러면 낮은순정렬하랬으므로 1d transpose해줌