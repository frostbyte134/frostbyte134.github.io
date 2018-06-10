---
layout: post
title:  "Batch Normalization"
date:   2018-06-08 08:34:00 +0900
categories: deep_learning
use_math: true
tags: optimization deep_learning need_revise
---

> <a href="https://arxiv.org/abs/1502.03167" target="_blank">Batch normalization</a> is a method of adaptive reparametrization, motivated by the difficulty of training very deep models.

### Motivations
Deep networks are too much tangled with itself for effective optimization. Previous approaches tried to 'untangle' network a bit by normalizing hidden layers. The method of normalization was 
1. Adding regularization penalty term  
\\(\Longrightarrow\\>\\) resulted in imperfect normalization
1. Manual intervene after each gradient step  
\\(\Longrightarrow\\>\\) waste of time (learning algorithm repeatedly proposed changing the mean and variance, while renormalzing them with intervention)

Batch normalization avoids such problems by __back-propagating through the normalization operation for computing the mean and the stddev__ (By inserting Batch normalization layer in the BP process).


### Advantages of normalization
Normalization 
\\[X'=\frac\{X-\textrm\{mean\}\}\{\textrm\{stddev\}\}\\]
rules out 1st and 2nd order statistics. Note that ruling out 1st order statistic is different from ruling out linear dependencies (Gram-Schmidt orthogonalization?).  
 
For example, if input is Normal RV and layers are simple scalar weight multiplication, then normalizing each layer is equivalent to ruling out all hidden layers except the last one, since only the 1st and 2nd order statistics are required to construct a Normal RV.


### Advantages of reparametrization
Since we lost some expressive power of the network by normalization, it is common to construct the batch of hidden unit activations \\(H\\) by
\\[H\quad\Longrightarrow\quad\gamma H'+\beta\\]
rather than simply the normalized \\(H'\\). The variables \\(\gamma,\\>\beta\\) are learned parameters that allows the nerwork to recover the old parametrization, but __the new parameterization has different__ `learning dynamics`. 
* Previously the mean of \\(H\\) was determined by the complex interactions of the layers below \\(H\\). 
* Whereas, the mean of \\(\gamma H'+\beta\\) is solemly determined by the \\(\beta\\), which is much easier to lean (how?) by the gradint descent.


### Where to apply BN?
Most neural network layers take the form of \\(\phi(XW+b)\\), where \\(\phi\\) is some fixed nonlinear activiation (ReLU).  
Rather than applying BN to the input \\(X\\), it is generally recomended to replace \\(XW+b\\) by a (normalized version of \\(XW\\)). The bias term should be omitted, since it is redundant with the \\(\beta\\) of BN. The input \\(X\\) is usually the output of a nonlizer activation function. The statistics it are thus more non-Gaussian and less amendable to standardization by linear operations(?).

<hr>
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>