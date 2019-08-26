---
layout: post
title:  "BOJ 11985: 오렌지 출하"
date:   2018-06-08 16:45:05 +0800
categories: problem_solving
use_math: true
tags: problem_solving dp need_review
problem: 11985
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>


동적계획법 문제. 점화식은 쉽게 유도가 됬는데, 구간의 최대/최소를 빠르게 찾아야 해서 구간트리도 들어가있나 했음. 결국 i번째에 대해 박스를 확장시키면서 최대/최소를 계속 갱신해 나갈 수 있어서 구간트리도 필요없었음.

값이 좀 커서 세심한 최대값 처리가 필요했던 문제. 987654321 적당히 좀 쓰자 ㅡㅡㅋ 귀찮긴 한데..

근데 입력 데이터가 좀 약한 것 같기도 함. 맥시멈으로 하면 타임아웃 날만도 한데..