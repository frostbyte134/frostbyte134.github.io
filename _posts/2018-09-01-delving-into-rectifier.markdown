---
layout: post
title:  "Delving Deep into Rectifiers"
date:   2018-09-01 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning initialization
---

<a href="https://arxiv.org/pdf/1603.05027.pdf" target="_blank">https://arxiv.org/pdf/1603.05027.pdf</a>  

- Robust initialization method that particularly considers the rectifier nonlinearities (<a href="https://pytorch.org/docs/stable/_modules/torch/nn/init.html" target="_blank">`Kaiming_initialization`</a> in pytorch)

- Remember that the paper is written in 2015

### Introduction
...we have witnessed tremendous improvements in recognition performance, mainly due to advances in __two technical directions__: building more powerful models, and designing effective strategies against overfitting.
1. neural networks are becoming more capable of fitting training data, b/c of 
	- increased comprexity (increased depth of `VGG`, `GoogleNet` )
	- enlarged width
	- use of smaller strides
	- new non-linear activations
	- sophisticated layer design (<a href="https://arxiv.org/abs/1406.4729" target="_blank">spacial pyramid pool [11]<a/>, going deeper with conv)
2. On the other hand, better generalization is achieved by
	- effective regularization techniques
	- aggressive data augmentation
	- and large-scale data.

(ref to each item is in the paper.)

### Definition and Derivative of PReLU
wasn't able to find PReLU in more recent papers. However calculating its deriv is somewhat worth remembering. The author says that one PReLU (with specific \\(a_i\\) is applied over a channel, element-wise to \\(W\times H\\) inputs


Formally, we consider an activation function defined as:
\\[
f(y\_i)=\begin\{cases\}
y_i,\quad\text\{if \}y\_i>0 \cr
a\_iy\_i,\quad\text\{if \}y\_i\leq 0 \cr
\end\{cases\}
\\]
where
- \\(y\_i\\) is the input of the nonlinear activation \\(f\\) on the \\(i\\)th channel, and 
- \\(a_i\\) is a coef controlling the slope of the negative part. (0 in ReLU)

Note that each PReLU is defined for each channel, like `BatchNorm`.

\\(a_i\\) is a trainable parameter. The update formula of \\(\\{a_i\\}\\) are simply derived from the chain rule. The gradient of \\(a_i\\) for one layer is:
\\[\sum\_\{y\_i\}\frac\{\partial E\}\{\partial f(y\_i)\}\frac\{\partial f(y\_i)\}\{\partial a\_i\}\tag\{2\}\\]
(think the summation is done over the \\(W\times H\\))


### Initiliazation of Filter Weights for Rectifiers

... in `VGG` they pre-train a model with 8 conv layers to initialize deeper models. But this strategy require more training time, and may also lead to a poorer local optimum. In `GoogleNet`, auxiliary classifiers are added to intermediate layers to help with convergence.

Glorot and Bengio [7] proposed to adopt a properly scaled uniform distribution for initialization. This is called
`Xavier initialization` in [14]. Its derivation is based on the assumption that the activations are linear, and is invalid for ReLU and PReLU. In the following, we derive a theoretically more sound initialization by taking ReLU/PReLU into account.

### 1. Foward Propagation Case
For a conv layer, a response is:
\\[\textbf\{y\}_l=W_l\textbf\{x\}_l+b_l\\]


__Notations__:
- \\(\{x\}\\) is a \\((k\times k\times c)\\) by \\(1\\) vector that represents \\(k\times k\times c\\) input feature map.
- let \\(n=k^2c\\), denoting the num of connections of a response
- \\(W\\) is a \\(d\times n\\) matrix, where \\(d\\) is the number of filters and each row of \\(w\\) represents the weights of single filter.
- \\(b\\) is a vector of biases, and \\(y\\) is the response at a pixel of the output map.
- We use \\(l\\) to index a layer. We have \\(\textbf\{x\}\_l=f(\textbf\{y\}\_\{l-1\})\\).
- We also let \\(c_l=d_\{l-1\}\\). That is,
input channel size of \\(l\\)th layer = output channel size (row of \\(W\\)) of \\(l-1\\)th layer

Therefore we have
\\[\textbf\{y\}_l=W_l\textbf\{x\}_l+b_l\\]
\\[\rightarrow d_l\times1=(d_l\times n_l)\times(n_l\times 1)+(d_l)\\]

__Assumptions__:
- We let the initialized elements in \\(W\_l\\) be i.i.d.
- As in `Xavier`, we assume that the elements in \\(x\_l\\) are also i.i.d, and \\(x_l\\) and \\(W_l\\) are ind of each other.

Let \\(y\_l, w_l, x_l\\) represents the RVs of __each element__ in \\(\textbf\{y\}_l,W_l,\textbf\{x\}_l\\). Then we have
\\[Var[y\_l]=n_lVar[w_lx_l]\\]
We let \\(x_l\\) have zero-mean. Then the variance of the product of ind RVs gives us:
\\[Var[y\_l]=n_lVar[w\_l]E[x\_l^2]\\]
For the previous layer \\(l-1\\), if we let \\(w\_\{l-1\}\\) have a symmetric distribution around zero and \\(b_\{l-1\}=0\\), then \\(y\_\{l-1\}\\) has zero mean and has a symmetrid distribution around the mean. Considering the recurrence relation 
\\[\textbf\{x\}\_\{l\}=\textbf\{y\}\_\{l-1\}=W\_\{l-1\}\textbf\{x\}\_\{l-1\}\\]
this leads to
\\[E[x^2\_l]=Var[y\_\{l-1\}]=Var[w\_\{l-1\}x\_\{l-1\}]=\\]

Next:  

