---
layout: post
title:  "Sigmoid output unit and Logit"
date:   2018-03-31 15:18:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---
We want to solve a binary classification problem.

Starting from MLE, consider a Bernoulli distribution. \\(p(y=1\|x)\in [0, 1]\\) must hold (and vice versa), and satisfying this constraint requires careful design efforts.



### (1) Sigmoid unit with clipping
Suppose we use a linear unit with 2 thresholds \\[p(y=1\|x) = \max\\{0, \min\\{1, W^Tx+b\\}\\}\\] Anytime the input \\(W^Tx+b\\) strayed from \\([0,1]\\), the gradient of the output wrt its parameters becomes 0.

\\(\Longrightarrow\\) The learning algorithm no longer has a guide to improve corresponding parameter (dead unit!)



<h3 id="sigmoid_with_logit">(2) Sigmoid unit with logit</h3>
Now, let \\(z=W^Tx+b\\) and begin with the assumption that the unnormalized log-probability is linear in \\(y\in\\{0,1\\}\\) and \\(z=W^Tx+b\\). Then, \\[\log\hat{P}(y)=yz.\\] (Observe that \\(z=\log\hat{P}(y=1\|x)\\). We are predicting a number \\(z=\log\hat{P}(y=1\|x)\\), instead of directly predicting \\(P(y=1\|x)\\) as in (1). Consequently, the linear unit \\(z=W^Tx+b\\) predicts an unnormalized log-probability.)

We first exponentiate to obtain the unnormalized log probabiltiy \\[\hat{P}(y)=\exp(yz).\\] We then normalize to see that this indeed yields a Bernoulli distribution, controled by a sogmoidal transformation of \\(z\\), over \\(y\in\\{0,1\\}\\): \\[P(y)=\frac{\exp(yz)}{\sum_{y'=0}^{1}y'z} = \frac{\exp(yz)}{1+\exp(z)}\\] \\[ =\sigma((2y-1)z)\\] where \\(\sigma\\) is a  sigmoid function \\[\sigma(x)=\frac{1}{1+\exp(-x)}=\frac{\exp(x)}{\exp(x)+1}.\\] The \\(z\\) variable defining such a distribution over binary variables is called a logit.



If we use MLE, then treating the probabilites in log space undoes the exp of the sigmoid, which prevents the saturation of sigmoid.



The loss function for MLE learning of a Bernoulli parameterized by a sigmoid is, \\[\mathcal{J}(\boldsymbol{\theta}) = -\log P(y\|x)\\] \\[=-\log \sigma((2y-1)z)\\] \\[=\zeta((1-2y)z)\\] By rewriting in terms of the softplus function, we see that it saturates only when \\((1-2y)z\\) is very negative - when it has right answer - when \\(y=1\\) and \\(z\\) is very positive, or \\(y=0\\) and \\(z\\) is very negative (Think about the plot of \\(sigma(z)\\)).



When we use other loss functions, such as MSE, the loss can saturate anytime \\(\sigma(z)\\) saturates.
<hr>
<br/><br/>
Next:<a href="https://nailbrainz.blogspot.kr/2018/03/softmax-unit.html" target="_blank">https://nailbrainz.blogspot.kr/2018/03/softmax-unit.html</a>  
<br/><br/>
References:  
<a href="http://cs231n.stanford.edu/handouts/derivatives.pdf" target="_blank">http://cs231n.stanford.edu/handouts/derivatives.pdf</a>  
<a href = "http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>  