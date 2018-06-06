---
layout: post
title:  "Challenges in Neural Network Optimization"
date:   2018-06-06 12:34:00 +0900
categories: deep_learning
use_math: true
tags: linear_algebra analysis optimization deep_learning
---



<h3 id="ill_cond_hess">Ill-conditioned Hessian</h3>
<a href="{{site.url}}/linear_algebra/2018/06/04/hessian-and-optimization.html" target="_blank">Recall that</a>, the 2nd Taylor expansion predicts that a gradient descent step of \\(-\epsilon g\\) will add
\\[-\epsilon g^Tg+\frac\{1\}\{2\}\epsilon^2g^THg\\]
to the cost. When the condition number of \\(H\\) is high, which is referred as `ill-conditioned Hessian`, minimization with gradient descent is in problem.  
>Ill-conditioned problem is generally believed to be present in neural network training problems. and techniques which tackles it such as Newton's method does not scale well to deep learning.

<h3 id="local_minima">Local Minima</h3>
Local minima caused by the symmetry of valiables / weight symmetry is generally not a big problem, as they all have same object function cost.  
>Local minima with high cost poses a serious problem, but today that does not appear to be the frequent case. The problem remains an active area of research, but experts now suspect that for sufficiently large neural networks, most local minima have a low cost functionv alue, and htat is not important to find a true global minimum rathar than to find a point in prarameter space that has low but not minimal cost. <a href="https://arxiv.org/abs/1412.6544" target="_blank">(Goodfellow et al(2015))</a>

<h3 id="plateaus">Saddle points and Plateaus</h3>
For a function with arbitrary form, number of saddle points grow exponentially. To understand roughly, in a critical point (with 0 deriv) all of the eigenvalues of Hessian must be positive, but saddle point can (and must) have both positive and negative eigenvalues.

>An amazing property of many random functions is that the eigenvalues of the Hessian become more liekly to be positive, as we reach regions of low cost.

\\(\Longrightarrow\\) Critical points with high function value are likely to become saddle points. Thus in optimization (includes deep learning), __saddle points pose more serious problem than local minima__. 

However, despite of the fact that gradient quickly vanishes 0 near the critical point (including saddle point), __gradient descent `empirically` seems able to escape the saddle points in many cases__.

Whereas, saddle points constitute serious problem for Newton's method.  
Gradient descent is designed to move __downhill` and not explicitly to find a critical point.  
Newton's method however, is designed to find a critical point. there exists a <a href="https://arxiv.org/abs/1406.2572" target="_blank">saddle-free Newton's method</a> which tackled this problem, and holds promises if it can be scaled.


### Nonconvexity
<a href="https://arxiv.org/abs/1412.6544" target="_blank">Goodfellow et al(2015)</a> stated that, the epigraph of obejctive function for deep learning usually do not have many conspicuous obstacles (which cause bad local minima).
> Prior to the success of stochastic gradient dsecent for training very large models beginning in roughly 2012, neural net cost function surfaces were generally believed to have much more nonconvex structure than is revealed by these projections (in the paper).