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

> (Ian Goodfellow) Batch norm is similar to dropout in the sense that it multiplies each hidden unit by a random value at each step of training. In this case, the random value is the standard deviation of all the hidden units in the minibatch. Because different examples are randomly chosen for inclusion in the minibatch at each step, the standard deviation randomly fluctuates.  
Batch norm also subtracts a random value (the mean of the minibatch) from each hidden unit at each step.  
Both of these sources of noise mean that every layer has to learn to be robust to a lot of variation in its input, just like with dropout.

(<a href="https://www.quora.com/Is-there-a-theory-for-why-batch-normalization-has-a-regularizing-effect" target="_blank">https://www.quora.com/Is-there-a-theory-for-why-batch-normalization-has-a-regularizing-effect</a>)

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
* \\(u_i\\) : input to an arbitrary layer, wrt \\(i\\)th training example
* \\(b\\) : bias term
* \\(x_i:=u_i+b\\) : output of the layer, wrt \\(i\\)th training example
* \\(\hat\{x_i\}:=x_i-\textrm\{E\}\[X\]\\) : normalized output, where
	* \\(\textrm\{E\}\[X\]:=\frac\{1\}\{N\}\sum_\{i=1\}^\{n\}x_i,\quad\\) for \\(\mathbb\{X\}:=\\{x_1,...,x_n\\}\\), the set of outputs of the layer, over the training set.

Note the dependencies of \\(E[X]\\) over the entire training set(or minibatch). If the gradient descent step ignores the dependencies of \\(E[X]\\) on \\(b\\) (before BN, this was the convention. To consider such dependencies, we need to take entire minibatch in the consideration). Then
\\[b\leftarrow b-\nabla b \quad\textrm\{where\}\quad \nabla b=\frac\{\partial l\}\{\partial \hat\{x\}\}\frac\{\partial\hat\{x\}\}\{\partial b\}=\frac\{\partial l\}\{\partial \hat\{x\}\}.\\]  
In the next step of GD, \\(x+E[x]\\) becomes
\\[u+(b+\nabla b)-E[u+(b+\nabla b)]=u+b-E[u+b]=x-E[x].\\]
Thus, in summary we
1. Updated \\(b\\) 
2. updating \\(b\\) induces change in \\(E[X]\\)

and such update over \\(b\\) leads to no change in output, nor the loss \\(l\\).  
\\(\longrightarrow\\) high probability that \\(b\\) will explode/shrink toward \\(\frac\{\partial l\}\{\partial \hat\{x\}\}\\) direction. 

### Joint Whitening

Batch normalization avoids such problems by __back-propagating through the normalization operation__ (By incorporating Batch normalization layer into the BP process).  
Specifically, let 
* \\(X\\) be a random vector over the uniform RV of training data, and  
* \\(x\\) be a layer input vector, realized value of \\(X\\).

Define the normalization as a transformation
\\[\hat\{x\}=N(x,X)\\]
which depends on the output of the layer over entire minibatch \\(X\\). 
For backpropagation we need to compute the Jacobians
\\[\frac\{\partial N(x,X)\}\{\partial X\}\\]
Note that in `(b)`, we only calculated \\[\frac\{\partial N(x,X)\}\{\partial x\}\in\frac\{\partial N(x,X)\}\{\partial X\}.\\]  
In previous example, suppose we want to calculate \\(\frac\{\partial l\}\{\partial b\}\\). Then 
\\[\frac\{\partial l\}\{\partial b}=\frac\{\partial l\}\{\partial N(x,X)\}\frac\{\partial N(x,X)\}\{\partial X\}\frac\{\partial X\}\{\partial b\}.\\]
where \\(\frac\{\partial l\}\{\partial b}\\) is given in the BP process.  
(Remember that, in calculating \\(E[X]\\), \\(b\\) is used for each \\(i\\), so that we require such Jacobian in BP process)

Within this framework, (joint) whitening need to calculate \\(\{\textrm\{Cov\}[X]\}\\) and its inverse sqrt, as it requires computing
\\[\{\textrm\{Cov\}[X]\}^\{-1\}(x-\textrm\{E\}[X\])\\]
and as well as the derivs of these transformation for BP. This motivates (much simpler) BN.

### Batch Normalizing Transform
Few things to notes are,
1. Instead of joint (over the random vector \\(x=(x_1,...,x_n)\\)) whitening, BN applies __independent normalization__ on \\(x_i\\) over the minibatch.
2. Normalization can change the representation of the layer  
\\(\quad\Longrightarrow\quad \\) __add learnable linear transform__, which can recover the original representation
3. Insert BN layer into backpropagation

> (???)  
Note that, the use of mini-batch is "enabled" by computation of per-dimension variance (var of \\(x_i\\), instead of \\(x\\))) rather than joint COV mat;  
In the joint case, regularization would be required(?), since  
mini-batch size < # of activation being whitened \\(\Longrightarrow\\) resulting in singular COV mat (this part is clear, since COV = \\(E[(X-E[X])(X-E[X])^T]\\). 

Let
* \\(\mathbb\{B\}\\): minibatch of size \\(m\\) 
* \\(x\\): particular activation of \\(x^\{(k)\}\\) (now \\(x\\) is scalar) (normalization is applied to each activation index \\(\rightarrow\\) omit \\((k)\\))
* \\(m\\): # of values of activation of \\(x\\), with respect to \\(\mathbb\{B\}\\).
\\[\textrm\{activation of x\}:\\>\\{x_1,...,x_m\\}\\]
* \\(\\{\hat\{x\}_1,...,\hat\{x\}_m\\}\\): normalized \\(\\{x_1,..,x_n\\}\\).
* \\(\\{\hat\{y\}_1,...,\hat\{y\}_m\\}\\): linear transformation of \\(\\{x_1,..,x_n\\}\\).

We refer to the transform \\[\textrm\{BN\}\_\{\gamma,\beta\}:\\{x_1,..,x_n\\}\mapsto\\{\hat\{y\}_1,...,\hat\{y\}_m\\}\\] as the __Batch Normalization Transform__.
(For the exact process and derivatives, refer to the <a href="https://arxiv.org/abs/1502.03167" target="_blank">original paper</a>)

> although the joint distribution of these normalized \\(\hat\{x\}^\{(k)\}\\) can change over the course of training, we expect that the introduction of normalized inputs accelerates the training of the sub-network and, consequently, the network as a whole.

>Thus, BN transform is a differentiable transformation that introduces normalized activations into the network. This ensures that as the model is training, layers can continue learning on input distributions that exhibit less internal covariate shift (by clipping 1st and 2nd order statistic independently, over the minibatch), thus __accelerating the training__. Furthermore, the learned affine transform applied to these normalized activations allows the BN transform to represent the identity transformation and preserves the network capacity.

(Need revision from here)


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