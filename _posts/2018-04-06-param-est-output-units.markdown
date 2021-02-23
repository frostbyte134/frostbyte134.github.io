---
layout: post
title:  "Estimating parameters with output units"
date:   2018-04-06 20:17:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---
The principle of MLE provides a guide for designing a good cost function.

>In general, if we define a conditional distribution \\(p(y\|x;\theta)\\) the principle of maximum likelihood suggests we use \\(-\log{p(y\|x;\theta)}\\) as our cost function.

We can think of the neural network as representing a function \\(f(x;\theta)\\). The outputs of this function are not direct predictions of the value \\(y\\). Instead, \\(f(x;\theta)=\omega\\) provides the parameters for a distribution over \\(y\\). Our loss function can then be interpreted as \\(-\log{p(y;\omega(x))}\\).



### Example: Learning the variance of a conditional Gaussian for \\(y\\) given \\(x\\)

(1) Simple case: \\(\sigma^2=\frac{1}{n}(x_i-\hat{\mu})^2\\)  
Recap: <a href="{{site.url}}/probability/2018/04/05/mle-of-gaussian.html" target="_blank">ML estimator of variance of I.I.D Gaussians is the sample variance.</a>

(2) Let \\(p(y\|x)\sim\mathcal{N}(\mu,\omega)\\), where \\(\omega=f(x;\theta)\\), and solve \\(\min[-\log{p(y\|x)}]=\min[-\mathcal{N}(x;\mu,\omega)]\\).  
We often want to find `precision`, instead of  
-1. `variance` \\(\rightarrow\\) \\(-\log{p(y\|x)}\\) includes division by variance.  
-2. `stddev` \\(\rightarrow\\) not only division, but also squaring  
for numerical stability.



We have to ensure that covariance matrix (COV) is positive definite, which is equivalent to positivity of all eigenvalues.

Generally we assume diagonal COV mat, which gives simple scalar positivity constraints. Without diagonal assumption, we impose positive definiteness by \\[\Sigma=B(x)^TB(x)\\] where \\(B(x)\\) is square matrix which we parametrize.

One practical issue if \\(\Sigma\\) is full rank is that computing inverse and \\(\mathrm{det}\\) requires \\(O(n^3)\\) (link?) (or equivalently and more commonly, calculating its eigen-decomposition (spectral?)).
<hr>
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>