---
layout: post
title:  "Vector projection and Cosine"
date:   2018-04-02 22:29:00
categories: analysis
use_math: true
tags: analysis geometry linear_algebra need_revise
---
<h3 id="proj_on_line">(1) Projection onto a line</h3>
What we want to show is:\\[\cos{\theta}=\frac{a^Tb}{\|a\|\|b\|}.\\]
![vproj]({{ site.url }}/images/math/analysis/vector_proj.png){: .center-image }

To begin with,
\\[p = ca\quad\textrm{for}\quad c\in\Re, a\in \Re^N\\] \\[a^T(b-p)=a^T(b-ca)=0\\] \\[\longrightarrow c=\frac{a^Tb}{a^Ta}, \\]so that \\[p=ca=\frac{a^Tb}{a^Ta}a, \quad \|p\|=\sqrt{\frac{(a^Tb)^2}{(a^Ta)^2}a^Ta}=\frac{a^Tb}{\|a\|}\\] now, \\[\cos{\theta}=\frac{\|p\|}{\|b\|}=\frac{a^Tb}{\|a\|\|b\|}\\]

Projection \\(p\\) of \\(b\\) onto \\(a\\) can be simplified as \\[ p=({a'}^Tb)a', \\]where \\(a'\\) is the normalized vector of \\(a\\).



<h3 id="angle_bet_two_vecs">(2) Angle between two vectors</h3>

| ![angle]({{ site.url }}/images/math/analysis/cosonangle.png){: .center-image }| 
|:--:| 
| defining \\(\cos\theta, \sin\theta\\) on a circle |




\\[\textrm{acos}(\cos(\theta))=\textrm{acos}\left(\frac{a^Tb}{\|a\|\|b\|}\right) \\]

Side note: Angle between two lines.

Let \\(\theta=\textrm{acos}\left(\frac{a^Tb}{\|a\|\|b\|}\right).\\) Then the answer is \\(\min(\theta, \pi - \theta)\\).


| ![angle]({{ site.url }}/images/math/analysis/line_theta.png){: .center-image }| 
|:--:| 
| <a href="http://darkpgmr.tistory.com/121" target="_blank">http://darkpgmr.tistory.com/121</a>  |




<h3 id="cp_bet_two_vecs">(3) Outer product between two vectors</h3>
An outer product \\(a\times b\\) is defined between two vectors \\(a\in\Re^3, b\in\Re^3\\). It returns a vector, perpendicular to \\(a\\) and \\(b\\), with length equal to the size of parallelogram made of \\(a\\) and \\(b\\) in the plane they compose. 



When we let \\(a\\) as x-axis, \\(b\\) as y-axis, then the cross-product will be pointing toward z-axis direction.



| ![cp]({{ site.url }}/images/math/analysis/cross_product.png){: .center-image }| 
|:--:| 
| <a href="http://darkpgmr.tistory.com/121" target="_blank">http://darkpgmr.tistory.com/121</a>  |



In two dimension, we set \\(z\\) coordinate to 0. The direction does not matter (will be pointing z-axis), but the size of parallelogram matters.

It can be calculated as \\[\|v_1\|\|v_2\|\sin\theta = v_{1x}v_{2y}-v_{1y}v_{2x}\\] Since the \\(\theta\\) tells us how much we move from \\(v_1\\) to \\(v_2\\) in radian, and \\(\sin{-\theta}=-\sin{\theta}\\), the sign of cross product tells about the relative angular position between two vectors.

If \\(\theta\\) is positive, we can find b within \\(\pi\\) radian, toward counter-clockwise direction.

If \\(\theta\\) is positive, we can find b within \\(\pi\\) radian, toward clockwise direction.
<hr>
<br/><br/>
Next:
<br/><br/>
References:  
[1] <a href="http://darkpgmr.tistory.com/121" target="_blank">http://darkpgmr.tistory.com/121</a>  