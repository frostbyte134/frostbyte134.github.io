---
layout: post
title:  "Orthogonality and subspaces"
date:   2018-05-10 08:59:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---

### Definition
Two vectors \\(x, y\\) are orthogonal i.i.f \\[x^Ty=\left<x,y\right>=0\\]
Since \\(a^Tb=\cos{\theta\} \\| a\\| \\| b\\| \\) <a href="{{site.url}}/analysis/2018/04/03/vector-projection.html" target="_blank">(link)</a>
\\[x^Ty>0:\textrm\{ angle is less than 90\}°\\]
\\[x^Ty<0:\textrm\{ angle is greater than 90\}°\\]

* If set of vectors are __mutually orthogonal__, then they are __mutually independent.__  
Proof: Suppose \\(v_1,...,v_r\\) are mutually orthogonal. Then if
\\[c_1v_1+...+c_rv_r=0\\]
by multiplying \\(v_i\\), we see that
\\[c_1{v_i}^Tv_1+...+c_r{v_i}^Tv_r=0\quad\rightarrow\quad c_i{v_i}^Tv_i=0\\]
\\[\rightarrow c_i=0.\\]
This holds for all \\(i\in [1,r]\\), so \\(v_1,...,v_r\\) are independent.