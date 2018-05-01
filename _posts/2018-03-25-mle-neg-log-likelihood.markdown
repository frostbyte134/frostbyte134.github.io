---
layout: post
title:  "MLE and Negative log-likelihood, in Deep Learning Context"
date:   2018-03-25 21:49:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio) optimization probability
---
- Stochastic gradient descent applied to nonconvex loss functions has no convergence guarantee, and is sensitive to the initialization.
- For feedforward networks, it is important to initialize all weights to 0, or to small positive values.
<h3 id="learning_cd_mle">Learning Conditional Distribution with MLE</h3>
#### Training using MLE  
\\( \rightarrow \\) Cost function is the negative log-likelihood, described as the cross-entropy between the data and the model distribution.

{% raw %}
\\[ J(\theta) = -E_{X,Y\sim \hat{p}_{data}}\log\left({p_{model}(y|x)}\right) \\]
{% endraw %}

If \\(p_{model}(y|x)=\mathcal{N}(y;f(x;\theta,I)) \\), then we recover the mean squared error cost. \\[ J(\theta)=-E_{X,Y\sim \hat{p}_{data}}\log\left(\frac{1}{\sqrt{2\pi|I|}}exp\{ (y-f(x;\theta,I) )^T I^{-1} (y-f(x;\theta,I)) \}\right) \\]\\[=\ln\left(\frac{1}{\sqrt{2\pi}}\right)+{\|y-f(x;\theta,I) \|}^2 \\]
One recurring theme throughout neural network design is that the gradient of the cost function must be large and predictable enough to serve as a good guide for the learning algorithm. Functions that saturate (become very flat) undermine this objective because they make the gradient become very small. In many cases this happens because the activation functions used to produce the output of the hidden units or the output units saturate.

The negative log-likelihood (used in MLE) helps to avoid this problem for many models. Exp function saturates when its argument is very negative (converges to 0). The log function in the negative log-likelihood cost function undoes the exp of some output units.



#### Cross-entropy cost function usually doesn't have minimum  
Since by making \\(p(y_i|f(x_i;\theta))\approx0\\), \\(-\ln p(y_i|f(x_i;\theta))\rightarrow-\infty\\).
{% raw %}
If the model has freedom to control its variance, then it is possible to obtain \\(\mathcal(J)\rightarrow\infty\\), by assigning \\( p(y_i|f(x_i;\theta)) \approx 1 \\) (with extreme high density) and 0 for other \\(y\\) such that \\(y\neq y_i\\), for each training data \\((y_i,x_i)\\).
{% endraw %}
Regularization techniques described in chapter 7 provide several different ways of modifying the learning problem so that the model cannot reap unlimited reward in this way.



References:

<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>