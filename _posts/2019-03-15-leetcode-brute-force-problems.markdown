---
layout: post
title:  "Leetcode - Brute-Force Problems"
date:   2019-03-15 1:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode brute_force need_review
---

### N-Queens
<a href="https://leetcode.com/problems/n-queens/" target="_blank">https://leetcode.com/problems/n-queens/</a>

1. Naive - on the board
2. 보드보다 상태공간을 더 잘 표현할 수 있음
    1. queen의 위치는, 1-d array의 위치가 row, 값이 column
    2. position의 조건이, rowInd+colInd와 rowInd-colInd 가 같으면 같은 대각에 있는 것이므로, 위의 두 값을 queen의 위치와 같이 저장. 같은 row/col체크는 하지 않을 것 (위에서 이미 결정하고 오므로)
    3. naive board solution은 정말 보드를 다 찾아보지만 이 solution은 row별로 어디에 놓을지만 결정해도 되므로 시간절약도 많이 될듯
