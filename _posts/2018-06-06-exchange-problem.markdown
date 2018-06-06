---
layout: post
title:  "BOJ 13137: Exchange Problem"
date:   2018-06-06 09:20:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving dp greedy need_review
problem: 13137
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  

동전교환 냅색dp에서, 언제 그리디한 해법과 차이가 날까를 생각해야 하는 문제.

뭣도 모르고 대충 가장 큰 동전값의 2배만 검사하면 되겠지 하고 풀어서 맞았음.

왜 맞았는지 정리가 안되서 찾아본 풀이(https://gooddaytocode.blogspot.com/2016/08/blog-post_6.html)를 참고해 보면, 동전값이 오름차순으로 정렬되있다고 했을 시 ary[N] + ary[N-1]만 검사해보면 됨.

Proof by contradiction. 만약 K>ary[N]+ary[N-1]이며 K가 그리디한 해법으로는 답을 못 구하는 값 중 최소라 한다면,
1. K의 냅색 답 중 ary[N]이 포함되지 않은 경우  
그렇다면 K-ary[i]>0 for some i!=N, N-1이 성립할 것임. K-ary[i] < K이므로 그리디한 해법으로 답을 구할 수 있음 (냅색 답 = 그리디 답). 하지만 K-ary[i] > ary[N]이므로 ary[N]을 빼도 답이 나올 것이므로 모순
2. K의 냅색 답 중 ary[N]이 포함된 경우  
그렇다면 냅색 답과 그리디 답 전부 ary[N]을 포함하고 있을 것이므로, K-ary[N] 또한 K와 같은 성질 (그리디로는 못풀고 냅색으로는 푸는 경우)을 보유하고 있음. K > K-ary[N]이므로 모순
