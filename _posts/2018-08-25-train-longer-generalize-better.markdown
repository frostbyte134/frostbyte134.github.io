---
layout: post
title:  "Train longer, generalize better"
date:   2018-08-25 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning SGD large_batch generalization_gap
---

<a href="https://arxiv.org/abs/1705.08741" target="_blank">https://arxiv.org/abs/1705.08741</a>  

### Abstract
* It has been observed that when using large batch sizes there is a persistent degradation in generalzation performance - known as the `generalization gap`.
* we find that the weight distance from its initiliztion grows logarithmically with the number of weight updates. We there propose a "random walk on a random landscape" statistical model, which is known to exhibit similar "ultra-slow" diffusion behavior.
* ... show empirically that the `generalization gap` stems from the __relatively small number of updates rather than the batch size__.
* `Ghost Batch norm` which enables significant decrease in the generalization gap...


### Introduction
Since `SGD`, at best, finds a local minimum of the non-convex objective function, substantial research efforts are invested to explain DNNs ground breaking results.  
It has been argued that
1. saddle points can be avoided <a href="https://arxiv.org/abs/1503.02101" target="_blank">(Ge et al, 2015)</a>
2. "bad" local minima in the training error vanish exponentially <a href="https://arxiv.org/abs/1406.2572" target="_blank">(Dauphin et al, 2014)</a>, <a href="https://arxiv.org/abs/1412.0233.pdf" target="_blank">(Choromanska et al, 2015)</a>, <a href="https://arxiv.org/pdf/1702.05777.pdf" target="_blank">(Soudry & Hoffer, 2017)</a>.

However, it is still unclear why __these complex models tend to generalize well to unseen data, despite being hevily over-parametrized__ <a href="https://arxiv.org/abs/1611.03530" target="_blank">(Zhang et al., 2017)</a> 

With larger batch size, the trained model appear to generalize less well. This remained true even when the models were __trained without any budget or limits, until the loss function ceased to improve__ (Keskar et al, 2017). This has been named the `generalization gap`

In this study,
* First we propose that the initial learning phase can be described using a high-dimensional `random walk on a random potential` process, with an "ultra-slow" logarithmic increase in the distance of the weights from their initilaization, as we observe empirically.




Links:  
<a href="https://arxiv.org/abs/1503.02101" target="_blank">saddle points can be avoided (Ge et al, 2015)</a>  
<a href="https://arxiv.org/abs/1406.2572" target="_blank">"bad" local minima in the training error vanish exponentially (Dauphin et al)</a>  
Next - <a href="https://arxiv.org/abs/1412.0233" target="_blank">"bad" local minima in the training error vanish exponentially (Choromanska et al, 2015)</a>  
<a href="https://arxiv.org/pdf/1702.05777.pdf" target="_blank">"bad" local minima in the training error vanish exponentially (Soudry & Hoffer, 2017)</a>  
Next - <a href="https://arxiv.org/abs/1611.03530" target="_blank">DNNs are overparemeterized, but generalize well (Zhang et al., 2017)</a>  

