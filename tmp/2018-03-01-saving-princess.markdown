---
layout: post
title:  "BOJ 2507: 공주 구하기"
date:   2018-02-25 22:33:05 
categories: problem_solving
use_math: true
tags: problem_solving dp counting
problem: 2507
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>

음...

우선 \\([0...A...B...N−1]\\)의 1차원 그래프에서 ```dp[A][B]```를,
\\[0→A→[A,B]\textrm{ 사이의 지점을 쓰지 않고 }→(N−1)→B→[A,B]\textrm{ 사이의 지점을 쓰지 않고 }→0\\]
으로 정의함.
왜 이렇게 정의하냐면, \\(dp[0][0]\\) 을 계산할 때
\\[0\rightarrow A\rightarrow [A,B]사이의>지점>C를>밟고\rightarrow N−1\rightarrow B\rightarrow 0\\]

으로 가는 경로는
\\[0→C→(N−1)→B→0\\]
에서(도) 세어질 것이기 때문.

```dp[0][0]```을 계산할 때 ```dp[i][j]```들을 다 더할 텐데 (i==j인 경우 말고), 이 때 중복카운트가 되면 안됨.
JLIS 비슷한 느낌인가? JLIS기억이 안나네..다시풀어볼까 ㅡㅡㅋ
