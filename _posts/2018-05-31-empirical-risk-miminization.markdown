---
layout: post
title:  "Empirical Risk Minimziation"
date:   2018-05-31 19:48:00 +0900
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio) optimization
---
Given \\(m\\) training set \\((\textbf\{x}\_i, y_i)\\), `Training` in deep learning refers to finding a parameter \\(\theta\\) s.t. reduces a const function \\(J(\theta)\\). It generally includes a regularization term (L2) + performance measure (mAP).

### Risk minimization
Typically the cost function \\(J(\theta\)\\) is defined by
\\[J(\theta):=E_\{(\textbf\{x\},y)\sim p\_\{\textrm\{data\}\}\}L(f(\textbf\{x\};\theta),y)\\]
where
* \\(f(\textbf\{x\};\theta)\\) : prediction of model with input \\(\textbf\{x\}\\)
* \\(L\\) : per-example loss function
* \\(p\_\{\textrm\{data\}\}\\) : data generating distribution

Above is an `optimization problem`. Everything is almost nice and clear.  
However \\(p\_\{\textrm\{data\}\}\\) is generally not known, so we have to use __empirical distribution__ \\(\hat\{p\}\_\{\textrm\{data\}\}\\). Now the cost function changes to
\\[J^\*(\theta):=E\_\{(\textbf\{x\},y)\sim\hat\{p\}\_\{\textrm\{data\}\}\}L(f(\textbf\{x\};\theta),y)\equiv \frac\{1\}\{m\}\sum\_\{i=1\}^m L(f(\textbf\{x\};\theta),y)\\]
\\(J^\*(\theta)\\) is known as the `emipirical risk`, and the problem of minimizing it is called as the `empirical risk minimization` (ERM).

> Empirical risk minimization tries to __indirectly__ minimize \\(J(\theta)\\) by minimizing approximate objective \\(J^\*(\theta)\\). 


### ERM in deep learning

Nonetheless,
1. ERM is prone to overfitting. Models with high capacity (ex - deep learning) can simply memorize the training set.
2. ERM is not really feasible. We have to calculate the deriv wrt objective function, and deriv of many objective functions are not in a good shape.

> Instead, in deep learning we must use a slightly different approach, in which the quantity that we actually optimize is even more different from the quantity that we truly want to optimize.

<hr/>
<br/>
<br/>
Next:  


References:
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>
