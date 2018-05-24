---
layout: post
title:  "BOJ 2143: 두 배열의 합"
date:   2018-05-23 09:49:00 +0900
categories: problem_solving
use_math: true
tags: problem_solving segment_tree dnq stack reference_problem
problem: 2143
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/><br/>

부분 배열의 개수가 그렇게 크지 않아 \\(\left(\frac\{n(n-1)\}\{2\}+n\right)\\), 부분배열 합을 정렬하고 parametric search로 합해서 T가 되는 처음과 끝을 찾음.

복습은 필요 없을듯