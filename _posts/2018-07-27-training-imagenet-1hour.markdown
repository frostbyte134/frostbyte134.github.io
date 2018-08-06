---
layout: post
title:  "Accurate, Large Minibatch SGD: Training ImageNet in 1 Hour"
date:   2018-07-27 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning resnet optimization sgd
---

<a href="https://arxiv.org/abs/1706.02677" target="_blank">https://arxiv.org/abs/1706.02677</a>  

> Scale matters.

Terms
* sample: a data-label pair, \\((x,y)\\)
* worker: a GPU

### (1) Introduction

* ... we scale <a href="{{site.url}}/deep_learning/2018/06/19/residual-network.html" target="blank">`Resnet`-50</a> training, originally performed with a minibatch size of 256 images (using 8 Tesla P100 GPUs, 29 hours) to larger minibatch(=8192) with 1 hour, using 256 GPUs.
* Importantly, not only does our approach match the baseline validation error, but also yields training error curves that closely match the small minibatch baseline.
* ... comprehensive experiments in sec5 show that __optimization difficultiy is the main issue with large minibatches, rather than poor generalization__ (at least on ImageNet), in contrast to `[20]`
* ... in a research domain, we have found it to simplifyu migrating algorithms from a single-GPU to a multi-GPU implementation without requiring hyper-param search (e.g. in our experience migrating Fastr R-CNN and ResNets from 1 to 8 GPUs)


### (2) Large minibatch SGD

Consider a `supervised learning` problem by minimizing a loss \\(L(w)\\) of
\\[L(w):=\frac\{1\}\{|X|\}\sum\_\{x\in X\}l(x,w)\tag\{1\}\\] where
* \\(w\\): weights of a network
* \\(X\\): labeled training set, \\((x,y)\in X\\).
* \\(l\\): typically, sum of a `classification loss`(cross-entropy, need link) and `regularization loss`.

Minibatch stochastic Gradient Descent (`SGD`) performs the following update:
\\[w_\{t+1\}=w_t-\frac\{1\}\{n\}\sum\_\{x\in\beta\}\nabla l(x,w\_t)\\]where
* \\(\beta\\): minibatch sampled from \\(X\\)
* \\(n:=\|\beta\|\\): minibatch size
* \\(t\\): iteration index

Above framework works on the assumption that minibatch loss \\(\frac\{1\}\{\|\beta\|\}\sum\_\{x\in\beta\}l(x,w\_t)\\) can approximate \\(\frac\{1\}\{\|X\|\}\sum\_\{x\in X\} l(x,w)\\).

`momentum` is discussed later


### (2)-1. Learning Rates for Large Minibatches
We want to scale up the size of minibatch, while maintaining training and generalization accuracy. 

> __Linear Scaling Rule:__ When the minibatch size is multiplied by \\(k\\), multiply the learning rate by \\(k\\).

__Interpretation__: an informal discussion why above rule is efficient.

Consider 
* a network at iteration \\(t\\) (thus we start with \\(w_t\\)).
* a seq of \\(k\\) minibatches \\(\beta\_j,\\>0\leq j<k\\), each of size \\(n\\).
* a large minibatch \\(\bigcup\_\{j<k\}\\), with size \\(nk\\).

1. \\(k\\) `SGD` over small minibatches \\(\beta_j\\) with learning rate \\(\eta\\)
\\[w\_\{t+1\}=w\_t-\eta\frac\{1\}\{n\}\sum\_\{x\in\beta\_0\}\nabla l(x,w\_\{t\})\\]
\\[w\_\{t+2\}=w\_\{t+1\}-\eta\frac\{1\}\{n\}\sum\_\{x\in\beta\_1\}\nabla l(x,w\_\{t+1\})\\]
\\[+\\]
\\[\vdots\\]
\\[=w\_\{t+1\}=w\_t-\eta\frac\{1\}\{n\}\sum\_\{j<k\}\sum\_\{x\in\beta\_j\}\nabla l(x,w\_\{t+j\})\tag\{3\}\\]
2. single `SGD` over minibatch \\(\bigcup\_\{j<k\}\beta_j\\) with learning rate \\(\hat\{\eta\}\\)
\\[\hat\{w\}\_\{t+1\}=w\_t-\hat\{\eta\}\frac\{1\}\{nk\}\sum\_\{j<k\}\sum\_\{x\in\beta\_j\}\nabla x,w\_\{t+j\})\tag\{4\}\\]

If we could assume that
\\[\nabla l(x,w\_\{t+j\}\approx \nabla x,w\_\{t+j\})\quad\text\{ for \}j<k,\\]
then setting \\(\hat\{\eta\}=k\eta\\) would yields \\(w\_\{t+k\}\approx \hat\{w\}\_1\\).

However, above (rather strong) assumption could be violated in at least 2 situations
1. initial stage, where the learing is unstable  
\\(\leadsto\\) warmup in next secion
2. when \\(k\\) is too high  
\\(\leadsto\\) batch size restricted to 8192

### (2)-2. Warmup.

__Constant warmup__  
is particularly helpful for prototyping obj detection / seg., that fine-tune pretrained layers together with newly initialized layers.  
For minibatch with size \\(kn\\),
1. low learning rate \\(\eta\\) for 5 epochs
2. return to \\(\hat\{\eta\}\\)

__Gradual warmup__  
1. Start with \\(\eta\\)
2. constantly increase till 5 epoch with \\(\hat\{\eta\}=k\eta\\).  
(Results are robust to the exact duration of warmup).


### (2)-3. Batch Norm(BN) with Large Minibatches
`BN` computes statistics (1st, 2nd moment) along the minibatch  
\\(\rightarrow\\) breaks independence of each sample's loss \\(l(x,w)\\).

> (?) [Shortcut], a practical consideration to avoid comm overhead, is acutally necessarey for preserving the loss fun when changing the minibatch size.

We write
* \\(l\_\beta(x,w)\\): loss of __a single sample__ \\(x\in\beta\\), which is _dependen on all samples in_ \\(\beta\\).
* \\(L(\beta,w)\\): loss over __a single sampled__ minibatch \\(\beta\\) of size \\(n\\)
\\[=\frac\{1\}\{n\}\sum\_\{x\in\beta\}l\_\{\beta\}(x,w)\\]

With `BN`, the training set can be thought of as containing [all distinct subsets of size \\(n\\) drawn from the original training set \\(X\\)]=\\(X^n\\).

\\(\rightarrow\\) Then, unlike above we wish \\(L(\beta,w)\quad\text\{for \}\beta\in X^n\\) to approximate [_training loss of minibatch in BN context_ \\(L(w)\\)]
\\[L(w)=\frac\{1\}\{\|X^n\|\}\sum\_\{\beta\in X^n\}L(\beta,w)\\]
where \\(X^n\\) denote a set of all distinct subssets of size \\(n\\) drawn from \\(X\\)

If we view \\(\beta\\) as __a single sample__ in \\(X^n\\), then the loss of each sample \\(\beta\\) can be computed independently with the assumption that
* batch size \\(n\\) is fixed  
\\(\rightarrow\\) if \\(n\\) is changed, it changes the underlying loss functional \\(l\\) that is optimized
* weight \\(w\\) is fixed

Then, in the case of distributed SGD training,
* if the per-worker size \\(n\\) is fixed
* while the total minibatch size is \\(kn\\)

It can be viewed as a [minibatch of \\(k\\) samples] __(Need to divide with \\(k\\)!)__ with each sample \\(\beta_j\\) is independently selected from \\(X^n\\)  
\\(\rightarrow\\) \\(L\\) is unchanged, ans is still defined in \\(X^n\\)  
(We need above to guarantee that \\(L\\) is unchanged in SGD with distrubuted batches)?

Under such point of view,
1. (3) becomes
\\[w\_\{t+1\}=w\_t-\eta\sum\_\{x\in\beta\_0\}\nabla L(\beta\_1,w\_\{t\})\\]
\\[w\_\{t+2\}=w\_\{t+1\}-\eta\sum\_\{x\in\beta\_0\}\nabla L(\beta\_2,w\_\{t+1\})\\]
\\[+\\]
\\[\vdots\\]
\\[=w\_\{t+1\}=w\_t-\eta\sum\_\{j<k\}\sum\_\{x\in\beta\_j\}\nabla L(\beta\_j,w\_\{t+j\})\\]
(Notice that \\(\beta_j\\) is summed up)
2. and (4) becomes
\\[\hat\{w\}\_\{t+1\}=w\_t-\hat\{\eta\}\frac\{1\}\{k\}\sum\_\{j<k\}\nabla L(\beta\_j,w\_\{t\})\\]

Following simliar logic as in sec.2.1, we set \\(\hat\{\eta\}=k\eta\\).
* If \\(n\\) is adjusted, it shloud be viewed as a hyperparam of `BN`, not dist-SGD (why?)
* `BN`-stats shouldn't be computed across all workers, for
	1. reduced communication cost
	2. to maintain the same underlying los function being optimized (computing bn stats over all workers changes func being optimized? why?)

Links:  
<a href="https://arxiv.org/pdf/1512.02325.pdf" target="_blank">SSD: Single Shot MultiBox Detector</a>  
<a href="https://arxiv.org/abs/1411.4038" target="_blank" id="7">[7] (Multibox) Scalable object detection using deep neural networks. In: CVPR. (2014)</a>  
<a href="https://arxiv.org/abs/1411.4038" target="_blank" id="10">[10] Fully Convolutional Networks for Semantic Segmentation</a>  
<a href="https://arxiv.org/abs/1411.5752" target="_blank" id="11">[11] Hypercolumns for object segmentation and fine-grained localization. In: CVPR. (2015)</a>  
<a href="https://arxiv.org/abs/1506.04579" target="_blank" id="12">[12] ParseNet: Looking wider to see better. In: ILCR. (2016)</a>  
