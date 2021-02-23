---
layout: post
title:  "Wide Residual Networks"
date:   2018-08-24 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning resnet residual
---

<a href="https://arxiv.org/abs/1605.07146" target="_blank">https://arxiv.org/pdf/1705.08741.pdf</a>  

- Empirical experiments on the architecture of Resnet, with cifar 10/100 and imagenet.

### Abstraction
* ... so training very deep residual networks has a problem of __diminishing feature reuse__, which makes these networks very slow to train.
* We decrease depth and increase width of residual networks.

Batch norm overfits???
> This is probably due to the fact that we don't do any data augmentation and __batch normalization overfits,__ so dropout adds a mregularization effect.

### Intro
* Recent follow-up work explored the __order of activations in residual networks__, presenting identity mappings in residual blocks `[13]` and improving training of very deep networks. (`conv`-`BN`-`ReLU` to `BN`-`ReLU`-`conv`?)
* As gradient flows through the network there is nothing to force it to go through residual block weights and it can avoid learning anything during training (????), so it is possible that there is either only a few blocks that learn useful representation, ... This problem was formulated as `diminishing feature reuse` in `[28]`. The author of `[14]` tried to address this problem with the idea of randomlyt disabling residual blocks during training.
* wider (more filters) resnet - training is more than 2X faster, while matching accuracy (higher, actually state of the art in CIFAR, and quite close in Imagenet compared to `[13]`, exceeding the original paper)
* Removed bottleneck design (for wider network), introduced dropout (between two 3X3 conv) to handle far more params.
* Dropout was also considered in `[13]`, in the identity layer, with negative effects. 


### Wide Residual networks
* \\(l\\): deepening factor. the number of convolutions in a block
* \\(k\\): multiplies the num of fets in convolutional layers.
* \\(d\\): number of blocks

The baseline basic block of orig paper corresponds to \\(l=2, k=1\\).  
The comparison has to be done among networks with the same num of params, so in this case we need to build networks with different \\(l, d\\), while ensuing that network complexity is kept roughly constant.

* The num of params increases linearly with \\(l\\) and \\(d\\).
* The num of params and comp complexity are quadratic in \\(k\\).  
However, wider networks (with more channel size) is more suitable for parallelization.
* One argument for wider residual network: almost all arthitectures b4 resnet, including Inception and VGG, were much wider compared to it.


### Experiments
- Cifar10/100
1. Type of convs in a block  
- Original resnet block (not bottlenecked one) \\(B(3,3)\\) were slightly better than \\(B(1,3), B(3,1,3), B(3,1),...\\)  
_Based on the above, blocks with comparable number of params turned tout to give more or less the same result._
2. Number of ocnvolutions per block  
\\(B(3)\\) was not so good, \\(B(3,3)\\) the best, and gets worsen as more convs are added \\(B(3,3,3), B(3,3,3,3)...\\).
3. Width of residual block  
refer to the paper

To __summarize__:
* widening coinsiustently improves performance across residual networks of different depth;
* increasing both depth and width helps until the num of params becomes too high and stronger regularization is needed;
* there doesn't seem to be a regularization effect from very high depth in residual networks as wide networks with the same number of params as thin ones can learn same or better reps. __Furthermore__, wide networks can successfully learn with a 2 or more times larger # of params than thin ones, which would require doubling the depth(!!) of thin networks, making them infeasibly expensive to train.

__Imagenet experiments__:  
With widening factor of 2.0 the resulting WRN-50-2-bottleneck outperforms ResNet-152 having 3 times less layers, and being significantly faster. (Seriously?) (Note that # of params are 1.5 larger than 101, time/batch is almost equivalent with 101, but better performance than 152, according to the author)

### Implementation details
LR 0.1, weight deacy 0.0005, momentum 0.9 (SGD), minibatch 128. No lr drop info for Imagenet.

Next:  
1. <a href="https://arxiv.org/pdf/1603.05027" target="_blank">[13] Identity Mappings in Deep residual Networks</a>  
2. <a href="https://arxiv.org/abs/1603.09382" target="_blank">[14] Deep networks with stochastic depth</a>  
3. <a href="https://arxiv.org/abs/1505.00387" target="_blank">[28] Highway Networks</a>  
4. <a href="http://proceedings.mlr.press/v9/glorot10a.html" target="_blank">[1] Understanding the difficulty of training deep feedforward neural networks</a>  
