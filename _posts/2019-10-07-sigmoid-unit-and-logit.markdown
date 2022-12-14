---
layout: post
title:  "Sigmoid output unit and Logit"
date:   2019-10-01 15:18:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---

> The softmax function, also known as softargmax or normalized exponential function, is a generalization of the logistic function to multiple dimensions [(wiki)](https://en.wikipedia.org/wiki/Softmax_function){:target="_blank"}


* revision history
* Written in 2018-03
* added easy Bayesian intro in 2019.10.1

### Easy Introduction (Added in 2019.10.1)
Consider a binary classification problem
* \\(classes Y\in \\{y\_1, y\_2\\}\\)
* data \\(X=x\\)
  
In Bayesian, \\[posterior \propto prior \times likelihood\\]
so prior \\(\times\\) likelihood is important. Thefore we apply log on it, and define
\\[a\_1 := \ln \left( P(Y=y\_1)P(X=x\|Y=y\_1) \right)\\]
\\[a\_2 := \ln \left( P(Y=y\_2)P(X=x\|Y=y\_2) \right)\\]
\\[\rightarrow a\_1 = \exp\\{ P(Y=y\_1)P(X=x\|Y=y\_1) \\}\\]

Now, the posterior can be expressed as
\\[ P(Y=y\_1 \| X=x ) = \frac\{ P(Y=y\_1,\\ X=x) \}\{ P(X=x\_1) \}\\]
\\[= \frac\{e^\{a\_1\}\}\{e^\{a\_1\}+e^\{a\_2\}\}\\]

which is, sigmoid / softmax (generalized case)

### logit <-> sigmoid
Logit function
\\[\text\{logit\}(y)=\frac\{y\}\{1-y\}=t\\]
and the sigmoid function
\\[\text\{sigmoid\}(t)=\frac\{1\}\{1+e^\{-t\}\}\\]
are in the inverse relation


### Written in 2018-03

We want to solve a binary classification problem.

Starting from MLE, consider a Bernoulli distribution. \\(p(y=1\|x)\in [0, 1]\\) must hold (and vice versa), and satisfying this constraint requires careful design efforts.



### (1) Sigmoid unit with clipping
Suppose we use a linear unit with 2 thresholds \\[p(y=1\|x) = \max\\{0, \min\\{1, W^Tx+b\\}\\}\\] Anytime the input \\(W^Tx+b\\) strayed from \\([0,1]\\), the gradient of the output wrt its parameters becomes 0.

\\(\Longrightarrow\\) The learning algorithm no longer has a guide to improve corresponding parameter (dead unit!)



<h3 id="sigmoid_with_logit">(2) Sigmoid unit with logit</h3>
Now, let \\(z=W^Tx+b\\) and begin with the assumption that the unnormalized log-probability is linear in \\(y\in\\{0,1\\}\\) and \\(z\\).  Then \\[\log\hat{P}(y)=yz.\\] Observe that \\(z=\log\hat{P}(y=1\|x)\\). We are predicting a number \\(z=\log\hat{P}(y=1\|x)\\), instead of directly predicting \\(P(y=1\|x)\\) as in (1). Consequently __the linear unit__ \\(z=W^Tx+b\\) __predicts an unnormalized log-probability.__

We first exponentiate \\(z\\) to obtain the unnormalized log probabiltiy \\[\hat{P}(y)=\exp(yz).\\] We then normalize to see that this indeed yields a Bernoulli distribution, controled by a sogmoidal transformation of \\(z\\), over \\(y\in\\{0,1\\}\\): \\[P(y)=\frac{\exp(yz)}{\sum_{y'=0}^{1}y'z} = \frac{\exp(yz)}{1+\exp(z)}\\] \\[ =\sigma((2y-1)z)\\] where \\(\sigma\\) is a  sigmoid function \\[\sigma(x)=\frac{1}{1+\exp(-x)}=\frac{\exp(x)}{\exp(x)+1}.\\] The \\(z\\) variable defining such a distribution over binary variables is called a `logit`.



In MLE, treating the probabilites in log space undoes the exp of the sigmoid, which __prevents the saturation of sigmoid.__

### (3) Loss function

The loss function for MLE learning of a Bernoulli parameterized by a sigmoid is, \\[\mathcal{J}(\boldsymbol{\theta}) = -\log P(y\|x)\\] \\[=-\log \sigma((2y-1)z)\\] \\[=\zeta((1-2y)z)\\] By rewriting in terms of the softplus function (or \\(P(y)=\sigma((2y-1)z)\\)), we see that it saturates only when \\((1-2y)z\\) is very negative (when it has right answer, \\(y=1\\) and \\(z\\) is very positive), or \\(y=0\\) and \\(z\\) is very negative.


When we use other loss functions, such as MSE, the loss can saturate anytime \\(\sigma(z)\\) saturates.
<hr>
<br/><br/>
Next:<a href="{{site.url}}/deep_learning/2018/04/01/softmax-unit.html" target="_blank">{{site.url}}/deep_learning/2018/04/01/softmax-unit.html</a>  
<br/><br/>
References:  
<a href="http://cs231n.stanford.edu/handouts/derivatives.pdf" target="_blank">http://cs231n.stanford.edu/handouts/derivatives.pdf</a>  
<a href = "http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>  