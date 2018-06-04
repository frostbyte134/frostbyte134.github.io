---
layout: post
title:  "Hessian and optimization"
date:   2018-06-04 20:34:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra analysis optimization deep_learning need_revise
---

Continued from <a href="{{site.url}}/linear_algebra/2018/05/13/psd-mat-and-hessian.html" target="_blank">posts about hessian.</a>


<h3 id="gradient_step_and_hessian">Gradient step and Hessian</h3>
The directional second deritive \\(f\'\'(u)\\) with unit direction \\(u\\), which can be calculated with the Hessian \\(H\\) by \\(u^THu\\), __tells us how well we can expect a gradient step to perform__.

Considera 2nd order Taylor expansion (link!!!) of \\(f(x)\\) at \\(x^\{(0)\}\\)
\\[f(x)\approx f(x^\{(0)\})+(x-x^\{(0)\})^Tg+\frac\{1\}\{2\}(x-x^\{(0)\})^TH(x-x^\{(0)\}).\\]
<a href="{{site.utl}}/optimization/2018/06/01/gradient-steepest-descent.html#steepest_desc" target="_blank">The next step of gradient descent</a> goes to \\(x^\{(0)\}-\epsilon g\\). Substituting it into our approximation gives,
\\[f(x^\{(0)\}-\epsilon g)\approx f(x^\{(0)\})-\epsilon g^Tg+\frac\{1\}\{2\}\epsilon^2g^THg\\]
Interpretations of the 3 terms in LHS are
* \\(f(x^\{(0)\})\\) : original function value
* \\(-\epsilon g^Tg\\) : expected improvement thanks to the __slope__ of \\(f\\)
* \\(\frac\{1\}\{2\}\epsilon^2g^THg\\) : correction, considering the __curvature__ of \\(f\\)

When \\(\frac\{1\}\{2\}\epsilon^2g^THg\gg \epsilon g^Tg > 0\\), the gradient step will not perform well in minimizing \\(f\\).

<h3 id="hessian_and_perform_of_grad">Performance of the gradient method and Hessian</h3>

{:.acounter}
1. Step size and Hessian  
When \\(g^THg>0\\), 1st optimality condition of (above) approximation
\\[f(x^\{(0)\}-\epsilon g)\approx f(x^\{(0)\})-\epsilon g^Tg+\frac\{1\}\{2\}\epsilon^2g^THg\\]
with respect to \\(\epsilon\\) gives,
\\[\epsilon^\*g^THg-g^Tg=0\\]
Thus __the optimal step size which decreases the next step of gradient descent the most__ is 
\\[\epsilon^\*=\frac\{g^Tg\}\{g^THg\}.\\]
2. What happens when the condition number\\(\left(\frac\{\lambda_\{\textrm\{max\}\}}\{\lambda_\{\textrm\{min\}\}}\right) \gg 0\\)?  
{:.acounter}
1. Step size perspective: when \\(g\\) alligns with the eigenvector of \\(\lambda_\{\textrm\{max\}\}\\) and stepsize = \\(\frac\{1\}\{\lambda_\{\textrm\{max\}\}\}\\)  
\\(\rightarrow\\) __stepsize must be small__ to avoid overshotting. However the gradient descent is unware of this.
2. To the direction of eigenvector with smallest eigenvector, the derivative will increase slowly.  
Whereas to the direction of eigenvector with largest eigenvector, the derivative will increase rapidly.  
Again, gradient descent does not aware of this, so __it cannot move ahead to the direction where the gradient remains negative longer__.


### Minimum point and Hessian (second deriv test)
At a __stationary point__ \\(x\in R^n,\\>f'(x)=0\\) by the definition. To test whether \\(x\\) is the minimum, we use the Taylor expansion\\[f(y)=f(x)+(f'(x))^T(y-x)+\frac\{\(y-x)^Tf\'\'(x)(y-x)}\{2!\}+o(y-x),\\>\forall x\in R^n\\]
where \\(o(y-x)\\) is negligible (link to taylor expansion). <a href="{{site.url}}/linear_algebra/2018/05/24/positive-definite-mat.html" target="_blank">Positive definiteness</a> of hessian gives \\[f\'\'(x)>0\\]so that
\\[f(y)-f(x)>0\\>\forall x\in R^n\\]

In the stationary point \\(x\\), when \\(f\'\'(x)\\) has both positive and negative eigenvalues,  then \\(x\\) is a `saddle point`
* \\(f(x)\\) increases towards eigenvector directions of positive eigenvalues
* \\(f(x)\\) decreases towards eigenvector directions of negative eigenvalues  

which is obvious with <a href="{{site.url}}/linear_algebra/2018/05/19/hermit-mat-and-spectral-theorem.html" target="_blank">spectral decomposition</a>.
