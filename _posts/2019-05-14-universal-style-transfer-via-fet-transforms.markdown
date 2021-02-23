---
layout: post
title:  "Universal Style Transfer via Feature Transforms"
date:   2019-05-14 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning generative unsupervised_style_transfer style_transfer perceptual wct
---

<a href="https://arxiv.org/abs/1705.08086" target="_blank">https://arxiv.org/abs/1705.08086</a>

* The `WCT` reflects a __direct matching of feature cov__ of the content img to a given style img.
* style characteristics = feature correlations

### Abstarct
* Existing feed-forward (style transfer) methods, while enjoying the inference efficiency, are mainly limited by inability og generatlizing to unseen styles or compromised visual quality.
* ... we ... tackles these limitations __without training on any pre-defined styles__
> The key ingredient of our method is a pair of feature transforms, whitening and coloring, that are embedded to an image reconstruction network (fet - wct - fet - wct ...)
* The `WCT` reflects a __direct matchingof feature cov__ of the content img to a given style img.

### Intro
* Style transfer ... enables the creation of new artistic works (...)
* The __key challenge__ is how to extract effective reprs of the style and then match it in the content img.
* Minimize Gram/cov matrices based loss functions through trained feed-forward nets [2, 6, 16, 20, 27] or iterative proc [9]
* `Universal style transfer`: the main issue is how to properly and effectively apply the extracted __style characteristics (feature correlations)__ to content imgs in a style-agnostic manner.
* `Transfer task`: wct in the middle of (multilayer) feedforwad nets
* `VGG-19` as the feature extractor (encoder), __trained__ (only training) a symmetric decoder to invert the `VGG-19` features to the original img
  * only requires learning the img reconstruction decoder with no style img involved 
* __Multi-level stylization pipeline__
* control-parameter (scalar \\(\alpha\\))

The main contributions are
* propose to use feature transforms (first?)
* couple the feature transforms with a pre-trained encoder + trained decoder

### Proposed
1. Encoder - pretrained `VGG-19`
2. Decoder - symmetric with Encoder. Trained with the `pixel reconstruction loss` () and `feature loss` () as
\\[L=\|\| I\_0 - I\_i \|\|\_2^2 + \lambda \|\| \Phi(I\_0 ) - \Phi(I\_i) \|\|\_2^2 \\]
where \\(\Phi\\) is the some layer features (Relu_X_1) of pretrained VGG encoder.


WCT: you know the thing

After the WCT, mix the feature linearly with prev(b4 WCT) features using \\(\alpha\in (0, 1)\\)

multilvl coarse-to-fine stylization
<img src="{{site.url}}/images/deeplearning/gan/ust.png" width="1200">

Next
* [3] Fast Patch-based style transfer of arbitrary style - replaces the content feature with more similar style feature based on patch similarity and hence limited capability, i.e., the content is strictly preserved while style is not well reflected with only lw-lvl info (e.g., colors) transferred
* [15] AdaIN - the content feature is simply adusted to have the same mean and var with the style feature, which is not eefective in capturing high-lvl repr of the style. Even learned with a set of training styles, it does not generalize well on unseen styles.