---
layout: post
title:  "Left inverse i.i.f Right inverse"
date:   2018-05-10 16:25:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
### Theorem
For \\(n\\)-dimensional sqaure matrix \\(A,\\>B\\), \\[AB=I\quad\rightarrow\quad BA=I\\]
`proof`:
\\[AB=I\\]
\\[(BA)B=B\\]
\\[(BA-I)B=0\\]

Note that from \\(AB=I\\), \\(\textrm\{det\}(AB)=\textrm\{det\}(A)\textrm\{det\}(B)=1\\), so that \\(\textrm\{det\}(B)\neq 0\\) and inverse of \\(B\\) exists.   
By multiplying \\(B^\{-1\}\\) on both sides \\(\cdots\\) `(1)`
\\[BA-I=0\\]
\\[BA=I\\]


(Another way to think about `(1)` is,  
by \\(\textrm\{det\}(B)\neq 0\\) we see that \\(B\\) is not a zero-matrix, so that considering \\((BA-I)B=0\\), \\(BA-I\\) must be a zero matrix)