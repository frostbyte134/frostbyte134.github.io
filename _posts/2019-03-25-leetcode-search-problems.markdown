---
layout: post
title:  "Leetcode - Search problems"
date:   2019-03-25 1:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review search
---

### Generate Parentheses

<a href="https://leetcode.com/problems/search-a-2d-matrix-ii" target="_blank">https://leetcode.com/problems/search-a-2d-matrix-ii</a>

\\(m\times n\\) 행렬이, 행 / 열 별로 독립적으로 정렬되어 있을 시,

1. 난 그냥 m*logn으로 풀음
2. 행렬은 각 element 별로 4개로 쪼갤 수 있다. 왼위가 자기보다 무조건 작은 곳, 오른아래가 무조건 자기보다 큰 곳.  
   왼쪽 위부터 시작하지 말고, 오른쪽 위부터 시작해서
   1. ary[i][j] < target: 더 큰 수 를 찾아야 하므로, 오른 아래는 무조건 없다. 왼쪽으로 빠꾸. 위는 예전에 갔으므로 갈 필요가 없음.
   2. ary[i][j] > target: 더 작은 수를 찾아야 하므로, 왼위는 무조건 없다. 아래로 ㄱ. 오른쪽은 오른쪽부터 시작했으므로 갈 필요가 없음.  
   의 방식으로 \\(\mathop\{O\}(m+n\\) 탐색 가능.

이런 문제를 바로바로 풀어야 할 텐데...
