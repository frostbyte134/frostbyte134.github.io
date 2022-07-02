---
layout: post
title:  "Projection between (vec, vec) and (vec, pnt)"
date:   2018-07-19 18:23:00 +0900
categories: geometry
use_math: true
tags: geometry
---

### (1)Projection between two vectors

<img src="{{ site.url }}/nailbrainz.github.io/images/math/geometry/proj-vec.png" class="center" style="width:500px"/>

As usual,
\\[(b-ca)^Ta=0\\]
\\[(c=\frac\{b^Ta\}\{a^Ta\}\\]

### (2)Projection between a point (=a vector) and a line (which is represented with two vectors on it)

<img src="{{ site.url }}/nailbrainz.github.io/images/math/geometry/proj-pnt.png" class="center" style="width:500px"/>

1. Find projection between two vectors \\(\text\{proj\}(b-a,\\>q-a)\\)  
2. We have to add \\(a\\) to the result, recovering original coordinate system.

* As a byproduct, we can use above to test whether a point is on a line.
* If we want to find whether a point is on a segment, we need to add boundingRectangle test.