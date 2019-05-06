---
layout: post
title:  "Dilated Residual Networks"
date:   2019-01-19 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning gan domain_adaptation gradient_reversal
---

<a href="https://arxiv.org/pdf/1702.05464.pdf" target="_blank">https://arxiv.org/pdf/1702.05464.pdf</a>


### Abstract

Convnets for image classification progresively reduce resolution until the image is represented by tiny feature maps in which the spatial structure of the scene no longer `discenible`. (OS=32)

... we than study `gridding artifacts` introduced by dilation, develop an approach to removing these artifacts (`degridding`), and show that this further increases the performance of DRNs (even the classification!).

### Intro

... progressivelyh reduce resolution until the image is represented by tiny feature maps that retain little spatial info (7by7, or OS=32 is typical)

Furthermore, image classification is rarely a convolutional net's raison d'etre. (often a proxy task / pretrain)

We show that dilated residual networks (`DRN`s) yield improved image classification performance.

While it may not be clear a priori that avg pooling can properly handle such high-resolution output, we show that it can, yilding a notable accuracy gain.


### Dilated residual nets

What's worse, if the object's signal is lost due to down-sampling, there is little hope to recover it during training. However, if we retrain high spatial reosolution throughout the modle and provide output signals that densely cover the input field, bp can learn to preserve important info about smaller and less salient objects.

### Degridding
`Gridding`: As in fig4, single active cell overly propagate after the dilated conv. Unlike the non-dilated conv, filters are multiplied more on certain grid of the feature map.

Solutions
1. Removing max-pooling: We found that this max-pooling oper leads to high-amplitude high-freq activation. Such high-freq activations can be propagated to later layers and ultimately exacerbate gridding artifacts.
2. Adding layers: add (nin-dilated) conv layers in the top (akin to removing alisaing artifacts using filters with appropriate freq)
3. Removing residual conn (in line with 2.) in the top

Link:  
[6] <a href="https://arxiv.org/pdf/1502.02791" target="_blank">Learning transferable features with deep adaptation networks</a>  
[13] <a href="https://arxiv.org/abs/1606.07536" target="_blank">Coupled Generative Adversarial Networks</a>  

Next:  
[6] - Learning transferable features with deep adaptation networks   
[13] - Coupled Generative Adversarial Networks


