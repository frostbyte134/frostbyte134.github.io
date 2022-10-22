---
layout: post
title:  "Identity Mappings in Deep Residual Networks"
date:   2018-08-28 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning resnet residual
---

<a href="https://arxiv.org/pdf/1603.05027.pdf" target="_blank">https://arxiv.org/pdf/1603.05027.pdf</a>  

- Good properties of simple, identity (=not including activations like ReLU) residual connection

### Introduction
ResNets can be expressed in a general form:
\\[y\_l=h(x\_l)+\mathcal\{F\}(x\_l,\mathcal\{W\}\_l)\\]
\\[x\_\{l+1\}=f(y_l)\\]
where
* \\(x\_l\\): input to the \\(l\\)th unit
* \\(x\_\{l+1\}\\): output of the \\(l\\)th unit
* \\(\mathcal\{W\}\_l:={W_\{l,k\}\|\_\{1\leq k\leq K\}}\\) denotes a set of weight of the \\(l\\)-th residual unit, where \\(K\\) is the num of layers in a Residual Unit (is 2 or 3 in the orig paper).
* \\(\mathcal\{F\}\\): residual function, e.g. a stack of 2 or 3 \\(3\times3\\) conv layers in the orig paper.

In __original resnet__ paper, \\(h(x\_l)=x_l\\) is identity mapping and \\(f(y\_l)\\) is a ReLU.

The central idea of resnet is to learn the additive residual function \\(\mathcal\{F\}\\) wrt \\(h(x\_l)\\), with a key choice of using \\(h\\) as an identity mapping. This is realized by attaching an identity skip connection (`shortcut`).

> In this paper, we analyze deep residul networks by __focusing on creating  a "direct" path for propagating information__, not only within a residual unit, but through the entire network. Our derivation reveals that _if both \\(h(x\_l)\\) and \\(f(y\_l)\\) are identity mappings_, the signal could be directly propagated from one unit to any other units, in both forward and backward pass.

### Analysis of Deep Residual Networks
\\(l\\)th Residual unit can be represented as
\\[y\_l=h(x\_l)+\mathcal\{F\}(x\_l,\mathcal\{W\}\_l)\\]
\\[x\_\{l+1\}=f(y_l)\\]
If \\(f\\) is also an identity mapping : \\(x\_\{l+1\}\equiv y\_l\\), we can put 2nd eqn to 1st and obtain
\\[x\_\{l+1\}=x\_\{l\}+\mathcal\{F\}(x\_l,\mathcal\{W\}\_l)\\]
Recursively, terms \\(x\_\{l+i\}\\) are canceled
\\[x\_\{l+1\}=x\_\{l\}+\mathcal\{F\}(x\_l,\mathcal\{W\}\_l)\\]
\\[x\_\{l+2\}=x\_\{l+1\}+\mathcal\{F\}(x\_\{l+1\},\mathcal\{W\}\_\{l+1\})\\]
\\[x\_\{l+3\}=x\_\{l+2\}+\mathcal\{F\}(x\_\{l+2\},\mathcal\{W\}\_\{l+2\})\\]
\\[\vdots\\]
and summing out gives
\\[x\_\{L\}=x\_\{l\}+\sum\_\{i=l\}^\{L-1\}\mathcal\{F\}(x\_l,\mathcal\{W\}\_l)\tag\{4\}\\]
for any _deeper unit_ \\(L\\) and _shallower unit_ \\(l\\). 

Eqn (4) exhibits `some nice properties`.
1. The feature \\(x\_L\\) of any deeper unit \\(L\\) can be represented as the feature of \\(x\_l\\) of any shallower unit __plus__ the summation \\(\sum\_\{i=l\}^\{L-1\}\mathcal\{F\}(x\_l,\mathcal\{W\}\_l)\\), indicating that the model is in a __residual fashion__ between any units \\(L\\) and \\(l\\).
2. The feature \\(x\_L\\) of any deeper unit \\(L\\) can be represented as a __summation of the residual functions__ \\(\mathcal\{F\}\\)
\\[x\_\{L\}=x\_\{0\}+\sum\_\{i=0\}^\{L-1\}\mathcal\{F\}(x\_l,\mathcal\{W\}\_l)\\]
In contrast, in a `plaine network` \\(x\_\{l+1\}\\) is a series of matrix-vector products, say,
\\[x\_\{L\}=x\_\{0\}\prod\_\{i=0\}^\{L-1\}\mathcal\{F\}(x\_l,\mathcal\{W\}\_l)\\]
3. Denoting the loss function as \\(\varepsilon\\). from the chain rule of Backprop we have
\\[\frac\{\partial\varepsilon\}\{\partial x\_l\}=\frac\{\partial\varepsilon\}\{\partial x\_L\}\frac\{\partial x\_L\}\{\partial x\_l\}=\frac\{\partial\varepsilon\}\{\partial x\_L\}\left(1+\frac\{\partial\}\{\partial x\_l\}\sum\_\{i=l\}^\{L-1\}\mathcal\{F\}(x_i,\mathcal\{W\}\_i\right)\\]
Generally it is very unlikely that \\(\mathcal\{F\}(x_i,\mathcal\{W\}\_i\)=-1\\) always holds, so the gradient does not vanish even when the weights are arbitrary small.

Note: when the skip connection is not identity mapping e.g. multiply some scalar on skip connection as in incepv4 paper (link), above nice property breaks (1 becomes prod of the scalars)


To this end, the author suggested modification of ResNets units as  

<img src="{{ site.url }}/images/deeplearning/resnet_identity.png" class="center" style="width:500px"/>

Next:  
2. <a href="https://arxiv.org/abs/1603.09382" target="_blank">[14] Deep networks with stochastic depth</a>  
4. <a href="http://proceedings.mlr.press/v9/glorot10a.html" target="_blank">[1] Understanding the difficulty of training deep feedforward neural networks</a>  
