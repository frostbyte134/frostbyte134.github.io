---
layout: post
title:  "Inner product and Outer product"
date:   2018-04-02 22:29:00
categories: analysis
use_math: true
tags: analysis geometry linear_algebra need_revise
---

### Definition of Cos/Sin on a unit circle

| ![angle]({{ site.url }}/images/math/analysis/cosonangle.png){: .center-image }| 
|:--:| 
| defining \\(\cos\theta, \sin\theta\\) on a circle |

Let \\((x,y)\\) be a point on the unit circle, and \\(\theta\\) be the angle which the line between 0 and the point makes with \\((1, 0)\\). Then  \\[\cos\theta=x,\\>\sin\theta=y.\\]  
<a href="http://www.afralisp.net/archive/lisp/bulge.htm" target="_blank">http://www.afralisp.net/archive/lisp/bulge.htm</a> - def of tan/sec/etc..


<h3 id="proj_on_line">Projection onto a line (cosine and inner product)</h3>
What we want to show is:\\[\cos{\theta}=\frac{a^Tb}{\|a\|\|b\|}.\\]
![vproj]({{ site.url }}/images/math/analysis/vector_proj.png){: .center-image }

To begin with,
\\[p = ca\quad\textrm{for}\quad c\in\Re, a\in \Re^N\\] \\[a^T(b-p)=a^T(b-ca)=0\\] \\[\longrightarrow c=\frac{a^Tb}{a^Ta}, \\]so that \\[p=ca=\frac{a^Tb}{a^Ta}a, \quad \|p\|=\sqrt{\frac{(a^Tb)^2}{(a^Ta)^2}a^Ta}=\frac{a^Tb}{\|a\|}\\] now, \\[\cos{\theta}=\frac{\|p\|}{\|b\|}=\frac{a^Tb}{\|a\|\|b\|}\\]

Projection \\(p\\) of \\(b\\) onto \\(a\\) can be simplified as \\[ p=({a'}^Tb)a', \\]where \\(a'\\) is the normalized vector of \\(a\\).


<h3 id="sin_formula">Sine and the outer product</h3>
(Although we derive \\(\|u\times v\|=\|u\|\|v\|\sin\theta\\) from the determinant(like something), the inverse derivation directly follows)  
Remember that the _outer product is defined in 3-Dimension_. Let \\(u=\left<u_1,u_2,u_3\right>,\\>v=\left<v_1,v_2,v_3\right>\\), and \\(\theta\\) be the angle between the two vectors. The __cross product__ of \\(u,v\\) is defined by
\\[u\times v:=
\begin\{vmatrix\}\{\}
	i && j && k \\\
	u_1 && u_2 && u_3 \\\
	v_1 && v_2 && v_3 \\\
\end\{vmatrix\}
=
\begin\{vmatrix\}\{\}
	u_2 && u_3 \\\
	v_2 && v_3 \\\
\end\{vmatrix\}i
-
\begin\{vmatrix\}\{\}
	u_1 && u_3 \\\
	v_1 && v_3 \\\
\end\{vmatrix\}j
+
\begin\{vmatrix\}\{\}
	u_1 && u_2 \\\
	v_1 && v_2 \\\
\end\{vmatrix\}k
\\]
\\[\left<u_2v_3-u_3v_2,u_3v_1-u_1v_3,u_1v_2-u_2v_1\right>.\\]
(Althought the leftmost equation factorizes similarly to the determinant, \\(i,j,k\\) are (orthonormal) vectors, so it is not exactly a determinant)
Therefore, squaring gives
\\[\|u\times v\|^2=(u\times v)\cdot(v\times u)\\]
\\[=u_2^2v_3^2-2u_2u_3v_2v_3+u_3^2v_1^2-2u_1u_3v_1v_3+u_1^2v_3^2+u_1^2v_2^2-2u_1u_2v_1v_2+u_2^2v_1^2\tag\{1\}\\]

Meanwhile,
\\[(\|u\|\|v\|)^2=\left(\sqrt\{u_1^2+u_2^2+u_3^2\}\sqrt\{v_1^2+v_2^2+v_3^2\}\right)^2\\]
\\[=u_1^2v_1^2+u_1^2v_2^2+u_1^2v_3^2+u_2^2v_1^2+u_2^2v_2^2+u_2^2v_3^2+u_3^2v_1^2+u_3^2v_2^2+u_3^2v_3^2\tag\{2\}\\]
Also, notice that
\\[(u\cdot v)^2=(u_1^2v_1^2+u_2^2v_2^2+u_3^2v_3^2+2u_1u_2v_1v_2+2u_1u_3v_1v_3+2u_2u_3v_2v_3\tag\{3\}\\] 
It holds that
\\[(2)-(1)=(3)\quad\quad\textrm\{(Lagrange's Identity)\}\\]

Thus, we have
\\[\|u\times v\|^2=(\|u\|\|v\|)^2-(u\cdot v)^2\\]
\\[=(\|u\|\|v\|)^2-(\|u\|\|v\|\cos\theta)^2\quad...\quad\textrm\{def of cos\}\\]
\\[=(\|u\|\|v\|)^2(1-\cos^2\theta)\\]
\\[=(\|u\|\|v\|)^2\sin^2\theta\\]
Taking sqrt gives
\\[|u\times v\|=\|u\|\|v\|\sin\theta\\]

In 2-dimension, letting \\(u_3,v_3=0\\) gives familiar formula
\\[(u_1,u_2)\times(v_1,v_2)=u_1v_2-v_1u_2=\|u\|\|v\|\sin\theta\\]




<h3 id="cp_bet_two_vecs">Outer product as 3rd perpendicular vector</h3>
An outer product \\(a\times b\\) is defined between two vectors \\(a\in\Re^3, b\in\Re^3\\). It returns a vector, perpendicular to \\(a\\) and \\(b\\), with length equal to the size of parallelogram made of \\(a\\) and \\(b\\) in the plane they compose. 


When we let \\(a\\) as x-axis, \\(b\\) as y-axis, then the cross-product will be pointing toward z-axis direction.


| ![cp]({{ site.url }}/images/math/analysis/cross_product.png){: .center-image }| 
|:--:| 
| <a href="http://darkpgmr.tistory.com/121" target="_blank">http://darkpgmr.tistory.com/121</a>  |


In two dimension, we set \\(z\\) coordinate to 0. The direction does not matter (will be pointing z-axis), but the size of parallelogram matters.

It can be calculated as \\[\|v_1\|\|v_2\|\sin\theta = v_{1x}v_{2y}-v_{1y}v_{2x}\\] Since the \\(\theta\\) __tells us how much we move (in radian) from__ \\(v_1\\) __to__ \\(v_2\\), and \\(\sin{-\theta}=-\sin{\theta}\\), the sign of cross product tells about the relative angular position between two vectors.

If \\(\theta\\) is positive, we can find b within \\(\pi\\) radian, toward counter-clockwise direction.

If \\(\theta\\) is positive, we can find b within \\(\pi\\) radian, toward clockwise direction.



<h3 id="angle_bet_two_vecs">Angle between two vectors</h3>


\\[\theta=\textrm{acos}(\cos(\theta))=\textrm{acos}\left(\frac{a^Tb}{\|a\|\|b\|}\right) \\]

__Side note__: Angle between two lines.

Let \\(\theta=\textrm{acos}\left(\frac{a^Tb}{\|a\|\|b\|}\right).\\) Then the answer is \\(\min(\theta, \pi - \theta)\\).

We let minimum \\(\theta\\) to be the angle between two __lines__, since we can always find two angles between two lines (or 0).


| ![angle]({{ site.url }}/images/math/analysis/line_theta.png){: .center-image }| 
|:--:| 
| <a href="http://darkpgmr.tistory.com/121" target="_blank">http://darkpgmr.tistory.com/121</a>  |





<hr>
<br/><br/>
Next:
<br/><br/>
References:  
[1] <a href="http://darkpgmr.tistory.com/121" target="_blank">http://darkpgmr.tistory.com/121</a>  
<a href="http://math.oregonstate.edu/bridge/papers/dot+cross.pdf" target="_blank">http://math.oregonstate.edu/bridge/papers/dot+cross.pdf</a>
<a href="https://math.la.asu.edu/~surgent/mat272/cross_mag_proof.pdf" target="_blank">https://math.la.asu.edu/~surgent/mat272/cross_mag_proof.pdf</a>