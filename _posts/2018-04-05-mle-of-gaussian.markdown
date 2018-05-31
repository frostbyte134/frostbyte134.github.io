---
layout: post
title:  "Maximum likelihood estimate of Gaussian"
date:   2018-04-05 17:44:00 +0900
categories: probability
use_math: true
tags: probability
---
Assumption: Draw a sequence \\(\\{x_1,...,x_n\\}\\) from  \\(n\\) i.i.d \\(X_n\sim\mathcal{N}(\mu_0,\sigma_0^2)\\)



The likelihood function is, \\[L(\mu,\sigma^2;x_1,...,x_n)=(2\pi\sigma^2)^{-n/2}\exp\left(-\frac{1}{2\sigma^2}\sum_{j=1}^n{(x_j-\mu})^2\right)\\]
and the log-likelihood becomes \\[l(\mu,\sigma^2;x_1,...,x_n)=-\frac{n}{2}\left(\ln2\pi+\ln\sigma^2\right)-\frac{1}{2\sigma^2}\sum_{j=1}^n(x_j-\mu)^2\\] The ML estimator of the mean and variance is \\[\hat{\mu}=\frac{1}{n}\sum_{j=1}^n{x_j},\quad\hat{\sigma}^2=\frac{1}{n}\sum_{j=1}^n{(x_j-\hat{\mu})^2}\\]

`Proof`. we need to solve \\[\min_{\mu,\sigma^2}-l(\mu,\sigma^2;x_1,...,x_n)\\] \\(-l\\) is convex, so we're going to check 1st-order optimality condition. \\[\frac{\partial}{\partial\mu}(-l)=-\frac{1}{\sigma^2}\sum_{j=1}^n{(x_j-\mu)}\\] \\[\quad=\frac{1}{\sigma^2}\left(-\sum_{j=1}^n{x_j}+n\mu\right)=0\\] \\[\quad\Longrightarrow\mu=\sum_{j=1}^n{x_j}.\\]

\\[\frac{\partial}{\partial\sigma^2}(-l)=\frac{n}{2\sigma^2}-\frac{1}{2(\sigma^2)^2}\sum_{j=1}^n(x_j-\mu)^2\\] \\[\quad=\frac{1}{2\sigma^2}\left(n-\frac{1}{\sigma^2}\sum_{j=1}^n(x_j-\mu)^2\right)=0\\] \\[ \Longrightarrow\sigma^2=\frac{1}{n}\sum_{j=1}^n(x_j-\mu)^2\\]


<hr>
<br/><br/>
Next:
asymptotic mean?  
generalization to n-dimensional (is trivial though)  
unbiased estimator?  
<br/><br/>
References:  