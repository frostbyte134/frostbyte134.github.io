---
layout: post
title:  "Intersection between two lines and segments"
date:   2018-04-20 21:23:00 +0900
categories: geometry
use_math: true
tags: geometry need_revise
---
### (1) No need for intersecting point

![hmm]({{ site.url }}/images/math/geometry/Line+segment+intersection.jpg)  

Plus, we need to handle exception case, where l1 and l2 are parallel.

If l1 and l2 are parallel, then \\[\textrm{ccw}(l1.p1,\\>l1.p2,\\> l2.p1)=0\quad  \textrm{and}\quad  \textrm{ccw}(l2.p1,\\>l2.p2,\\>l1.p1) = 0\\] holds. (<a href="{{site.url}}/geometry/2018/04/20/ccw.html" target="_blank">Recap - ccw function</a>)

Assuming that \\(li.p1 \leq li.p2\\) for all lines, we need to test 2 conditions.

1. \\(l1.p2 \leq l2.p1\\)

2. \\(l2.p2 \leq l1.p1\\)

if any of above holds, then the two segment intersects.



### (2) Need an intersection point


