---
layout: post
title:  "BOJ 1038: 감소하는 수"
date:   2018-02-25 20:20:05 
categories: problem_solving
use_math: true
tags: problem_solving need_review
---

<a target="_blank" href="https://www.acmicpc.net/problem/1038">https://www.acmicpc.net/problem/1038</a><br/>
  
문제를 두 단계로 접근   
  
1. N번째 감소하는 숫자의 '첫 자릿수 찾기'  
몇 자리까지 있는지 모르므로, dp[num][digit]이 N보다 커질 때 까지 N에서 빼감.  
N<dp[num][digit]이 되면, num이 digit자리에 오는 감소하는 수의 범위 안에 N이 들어간 것.
2. d자릿수가 있을 때, N번째 감소하는 숫자를 생성하는 함수로 나머지 답 완성  
-1.N=0이 될 수가 없음. N=1이 최소.  
-2. 이 때, d자리에서 높은 num부터 체크해가면 쉽게 풀 수 있을 것 같지만 안됨. dp[num][digit]으로 구하는건 num으로 시작하는 감소하는 수이지, num보다 작은 감소하는 수가 아니기 때문. 

miscs:
C[0][0]은 1이 맞는 것 같음. 