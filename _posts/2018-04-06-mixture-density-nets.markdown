---
layout: post
title:  "Mixture density network"
date:   2018-04-06 20:49:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---
We often want to perform `multimodal regression`.

That is, to predict real values from conditional distribution \\(p(y\|x)\\) that can have several different peaks in \\(y\\) shape for the same value of \\(x\\). In that case, a Gaussian mixture is a natural representation for the output (Jacobs et al?)



A typical example of such is the `mixture density network`, which is the title of this post.

A Gaussian mixture output with \\(n\\) components is defined by the conditional probability distribution: \\[p(y\|x)=\sum_{i=1}^np(c_i\|x)\mathcal{N}(y;\mu^{(i)}(x),\Sigma^{(i)}(x))\\] The neural net must have 3 kinds of outputs.



1. Mixture components \\(p(c=i\|x)\\): a vector.
These form a multinoulli distribution over \\(n\\) different components, associated with latent random variable \\(c\\). (`latent`, since we don't observe it on the data)  
Softmax over \\(n\\)-dimensional vector is often used.
2. A matrix \\(\left[\mu^{(1)}(x),\ldots,\mu^{(n)}(x)\right]\\).  
If \\(y\in\Re^d\\), then the matrix must output an \\(n\times d\\) matrix, containing all \\(n\\) of these \\(d\\)-dimensional vectors of means.
3. A tensor \\(\left[\Sigma^{(1)}(x),\ldots,\Sigma^{(n)}(x)\right]\\), where \\(\Sigma^{(i)}(x)\in\Re^{d\times d}\\).  
We typically use a diagonal matrix to avoid computing determinant.



It has been reported that gradient-based optimization of conditional Gaussian mixtures (on the output of neural networks) can be numerically unreliable, in part b/c one gets divisions by the variance. One solution is to `clip gradient` (link??? section 10.11.1) while another is to scale the gradients heuristically (Murray and Larochelle, 2014).

Gaussian mixture output are particularly effective in generative models of speech and movements of physical objects.


<hr>
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>