---
layout: post
title:  "Directional Derivative and steepest descent direction"
date:   2018-06-01 21:25:00 +0900
categories: optimization
use_math: true
tags: optimization analysis need_revise
---

need revision in differentiability -> continuity
add links to chain rule (analysis), differentiability, continuity

### Definition
`Directional derivative` in a unit vector \\(u\\) 
* is the __slope__ of a function \\(f\\) in \\(u\\)
* in other words, is a derivative of a function \\(f(x+\alpha u)\\) w.r.t. \\(\alpha\\), evaluated at \\(\alpha=0\\).  
By the chain rule (link from analysis!!) \\[F(\alpha):=\frac\{\partial\}\{\partial \alpha\}f(x+\alpha u)
=\frac\{\partial f(x+\alpha u)\}\{\partial (x+\alpha u)\}\cdot\frac\{\partial (x+\alpha u)}\{\partial \alpha \}
=\frac\{\partial f(x+\alpha u)\}\{\partial (x+\alpha u)\}\cdot u
\\]
and we see that, \\(F(0)=\frac\{\partial f(x)\}\{\partial (x)\}\cdot u=\nabla_xf(x)\cdot u.\\)  

<h3 id="steepest_desc">Negative direction of gradient is the steepest descent direction</h3>
To minimize \\(f\\), we would like to find a direction (in unit length) \\(u\\) where \\(f\\) decreases the most.
\\[\min_\{u,u^Tu=1\}u^T\nabla_xf(x)\\]
\\[=\min\_\{u,u^Tu=1\}\\|u\\|\_2\\|\nabla_xf(x)\\|\_2\cos\{\theta\}\\]
(Remember the <a href="{{site.url}}/analysis/2018/04/02/vector-projection.html" target="_blank">relationship between cosine and inner product</a>)  
Where \\(\theta\\) is the angle between gradient and \\(u\\). \\(\\|u\\|=1\\) is a constant, and removing irrelevant components with \\(u\\) gives
\\[=\min_\{u,u^Tu=1\}\cos\{\theta\}\\]
\\(\theta\\) is minimized when \\(u\\) points opposite direction with \\(\nabla_xf(x)\\). QED.  
The theorem assumes differentiability (heard that the theorem is more general, by just assuming continuity).

 
links:<a href="https://math.stackexchange.com/questions/223252/why-is-gradient-the-direction-of-steepest-ascent" target="_blank">https://math.stackexchange.com/questions/223252/why-is-gradient-the-direction-of-steepest-ascent</a>
