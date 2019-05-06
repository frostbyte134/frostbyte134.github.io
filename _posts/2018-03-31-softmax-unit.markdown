---
layout: post
title:  "Softmax Unit"
date:   2018-03-31 16:34:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---
>Anytime we wish to represent a probability distribution over a discrete variable with \\(n\\) possible values, we may use the softmax function.

The softmax function is usually used as output units, and for internal units rarely if we wish the model to choose between one of \\(n\\) different options for some internal variable.


<h3 id="deriv_of_softmax">Derivation of softmax</h3>
>In the case of <a href="{{site.url}}/deep_learning/2018/04/01/sigmoid-unit-and-logit.html#sigmoid_with_logit">binary variables</a>, we wished to produce a single number \\[\hat{y}=P(y=1\|x).\\]Since this number needed to lie in \\([0,1]\\), and since we wanted the log of this number to behave well for gradient optimization, we chose to instead predict a number \\[z=\log\hat{P}(y=1\|x).\\]Exponentiating and normalizing gave us a Bernoulli distribution, controlled by the sigmoid function.

To generalize the above, we now need to produce a vector \\(\hat{\mathbf{y}}\\), with components \\(\hat{y}_i=P(y=i\|x)\\).  We require

1. \\(\hat{y}_i\in[0,1]\\)

2. \\(\sum_j\hat{y}_j=1\\)

Similarly to above, a linear layer predicts unnormalized log-probailities: \\[\mathbf{z}=W^T h+b\in R^n,\\] where \\(z_i=\log\tilde{P}(y=i\|x)\\). Then again we exponentiate and normalize to obtain the desired \\(\hat{\textbf{y}}\\). Formally, the softmax function \\(\Re^N\to\Re^N\\) is defined by \\[\textrm{softmax}(z_i)=\frac{\exp(z_i)}{\sum_j\exp(z_j)}.\\]

### MLE over softmax

During MLE optimization, the log undoes the \\(\exp\\) of softmax. \\[\log\textrm{softmax}(z)_i=z_i-\log\sum_j{\exp(z_j)}.\\]

We can see that,

1. \\(\log\textrm{softmax}(z)_i\\) is linear in \\(z_i\\) - it never saturates in terms of \\(z_i\\).

2. We can approximate 2nd term by \\(\max_jz_j\\). The MLE (negative log-likelihood) strongly penalizes the most active incorrect prediction.  
  
Few things to note are,
* Since the maximum likelihood is a consistent estimator, unregularized MLE will drive the model to learn parameters that, drive the softmax to predict the fraction of counts of each outcome in the trainng set.
* Many object functions, other than log-likelihood, do not work well with softmax.


### Saturation of softmax
 Like sigmoid, the softmax activation saturate when the differences between input values become extreme (indeed it is similar to the sigmoid case) 

1. To see that the softmax function responds to the difference between its inputs, observe that it is invariant to scalar scaling \\[\textrm{softmax}(z+c)=\frac{\exp(z)\exp(c)}{(\sum_j\exp(z))\exp(c)}=\textrm{softmax}(z).\\]Using this, we can derive numerically stable softmax \\[\textrm{softmax}(z)=\textrm{softmax}(z-\max_j{z_j}).\\]



(maybe i need to take the sum over all partial derivs)

2. \\(\textrm{softmax}(z)_i:==\frac{\exp(z_i)}{\sum_j\exp(z_j)}\\) saturates to 1 when \\(z_i=\max_j z_j\\), and \\(z_i\\) is much greater than all other inputs (Then we can state that \\(\log\sum_j{\exp(z_j)}\approx\max_j z_j\\).

3. It also saturates to 0, when \\(z_j\\) is not maximal and the maximum \\(z_i\\) is much greater. 

  
  
<hr>
<br/><br/>
Next:  
<br/><br/>
References:  
<a href = "http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>  