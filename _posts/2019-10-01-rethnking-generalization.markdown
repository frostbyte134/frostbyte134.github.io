---
layout: post
title:  "Understanding Deep Learning Requires Rethinking Generalization"
date:   2019-10-01 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning augmentation
---


* <a href="https://arxiv.org/abs/1611.03530" target="_blank">https://arxiv.org/abs/1611.03530</a>
* <a href="https://openreview.net/forum?id=Sy8gdB9xx" target="_blank">Must read - https://openreview.net/forum?id=Sy8gdB9xx</a>

`Conventional wisdom` said
1. when the expressivity of a model is excessive, overfitting will occur
2. when it is adequate (with the help of regularization), the model cannot memorize all the training data, and will learn some `rules` of generalization

However, in `ILSVRC`, DL models easily fit random (labeling / data). With random label, conventional concept of learning (the relationship between data and labels) is impossible, but training converges.


This means that the expressivity of general basenets on ILSVRC are above the data, so that the conventional concept of `overfitting` (high generalization error caused by perfect memorization) cannot be applied.  
(But on the other way, what if the hypothesis class is so good and data are too trivial? this gives the same results while not violating the conventional wisdom)



### Regularization
> The basic idea is that although the original hypothesis is too large to generalize well, regularizers help confine learning to a subset of the hypothesis space with manageable complexity.  
By adding explicit (ex - penalizing norm) regularizer, __the effective complexity of the possible solutions is dramatically reduced__.

complexities - Rademacher, VC, flat-shattering

However, though the random labeling and chaning noise power experiments, it seems like that in DL the power of  regularization does not seems so great


### Implicit Regularization of SGD
with few assumptions, the final sol of SGD is a linear combination of the candidates - 


