---
layout: post
title:  "Batch Normalization"
date:   2018-06-13 08:34:00 +0900
categories: deep_learning
use_math: true
tags: optimization deep_learning need_revise
---

> <a href="https://arxiv.org/abs/1502.03167" target="_blank">Batch normalization</a> is a method of adaptive reparametrization, motivated by the difficulty of training very deep models.

It provides __reasonable tradeoff__ between the representational power of the network and ease in optimization. 

### Inverse Covariance Shift (Motivations of BN)
<a href="https://arxiv.org/abs/1502.03167" target="_blank">`Inverse covariance shift`</a> :  A phenomenon s.t. the distribution of \[a layer's input over the entire traning set\] changes during the training, as the parmeters of the previous layers change.

The layers of deep networks are too much _tangled_(=__ICS__ exists) for effective optimization. Previous approaches of _untangling_ the network was 
{:.acounter}
1. Adding regularization penalty term  
	  \\(\Longrightarrow\\>\\) resulted in imperfect normalization
2. Manual intervene after each gradient step  
	  \\(\Longrightarrow\\>\\) waste of time (learning algorithm repeatedly proposed changing the mean and variance, while renormalzing them with intervention)  
{:.acounter}

### How the normalization untangles the network by reducing ICS?
Consider a extreme case, where 
* the training set is 1-d Normal
* each layer just multiplies scalar \\(w_i\\)
* GT is also a 1-d Gaussian.

Thus, we are trying to recover a 1-d Gaussian.  
Without the normalization, the last layer must recover a Gaussian from unknown distribution. However if we apply normalization, then the network reduces to 1 layer  which tries to recover a Gaussian from the standard Gaussian (remember that Gaussian is specified with 1st, 2nd order statistics (link???)).  

This is just an extreme case, and generally we want to find some reasonable tradeoff in the middle.


### Problem of manual intervention (b)
Specifically for `(b)`, let	
* \\(u_i\\) : input of an arbitrary layer, wrt \\(i\\)th training example
* \\(b\\) : bias term
* \\(x_i:=u_i+b\\) : output of the layer, wrt \\(i\\)th training example
* \\(\hat\{x_i\}:=x_i-\textrm\{E\}\[X\]\\) : normalized output, where
	* \\(\textrm\{E\}\[X\]:=\frac\{1\}\{N\}\sum_\{i=1\}^\{n\}x_i,\quad\\) for \\(\mathbb\{X\}:=\\{x_1,...,x_n\\}\\), the set of outputs of the layer, over the training set.

Note the dependencies of \\(E[X]\\) over the entire training set(or minibatch). If the gradient descent step ignores the dependencies of \\(E[X]\\) on \\(b\\) (before BN, this was the convention. To consider such dependencies, we need to take entire minibatch in the consideration). Then
\\[b\leftarrow b-\nabla b \quad\textrm\{where\}\quad \nabla b=\frac\{\partial l\}\{\partial \hat\{x\}\}\frac\{\partial\hat\{x\}\}\{\partial b\}=\frac\{\partial l\}\{\partial \hat\{x\}\}.\\]  
Consequently in the next step of GD, \\(x+E[x]\\) becomes
\\[u+(b+\nabla b)-E[u+(b+\nabla b)]=u+b-E[u+b]=x-E[x].\\]
Thus, in summary we
1. Updated \\(b\\) 
2. updating \\(b\\) induces change in \\(E[X]\\)

and such update over \\(b\\) leads to no change in output, nor the loss \\(l\\).  
\\(\longrightarrow\\) high probability that \\(b\\) will explode/shrink toward \\(\frac\{\partial l\}\{\partial \hat\{x\}\}\\) direction. 

Batch normalization avoids such problems by __back-propagating through the normalization operation__ (By incorporating Batch normalization layer into the BP process). Specifically, define the normalization as a transformation
\\[\hat\{x_i\}=N(x_i,\mathbb\{X\})\\]
which depends on the output of the layer over entire minibatch \\(\mathbb\{X\}\\).  
For backpropagation we need to compute the Jacobians
\\[\frac\{\partial N(x_i,\mathbb\{X\})\}\{\partial X\}\\]
Note that in `(b)`, we only calculated \\[\frac\{\partial N(x_i,\mathbb\{X\})\}\{\partial x_i\}\in\frac\{\partial N(x_i,\mathbb\{X\})\}\{\partial X\}\\].  
In previous example, suppose we want to calculate \\(\frac\{\partial l\}\{\partial b\}\\). Then 
\\[\frac\{\partial l\}\{\partial b}=\frac\{\partial l\}\{\partial N(x_i,\mathbb\{X\})\}\frac\{\partial N(x_i,\mathbb\{X\})\}\{\partial \mathbb\{X\}\}\frac\{\partial \mathbb\{X\}\}\{\partial b\}.\\]
where \\(\frac\{\partial l\}\{\partial b}\\) is given in the BP process.  
(Remember that, in calculating \\(E[X]\\), \\(b\\) is used for each \\(i\\), so that we require such Jacobian in BP process)

Need revision from here


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
Suppoase a layers with the form of \\(\phi(XW+b)\\), where \\(\phi\\) is some fixed nonlinear activiation (ReLU).  
Rather than applying BN to the input \\(X\\), it is general to __replace__ \\(XW+b\\) __by a normalized version of__ \\(XW\\). The bias term should be omitted, since it is redundant with the \\(\beta\\) of BN. The input \\(X\\) is usually the output of a nonlizer activation function, so that the statistics of it are thus more non-Gaussian and less amendable to standardization by linear operations(?).

<hr>
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>  
<a href="https://arxiv.org/abs/1502.03167" target="_blank">Batch Normalization: Accelerating Deep Network Training by Reducing Internal Covariate Shift</a>