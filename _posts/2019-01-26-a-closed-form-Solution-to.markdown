---
layout: post
title:  "A Closed-form Solution to Photorealistic Image Stylization"
date:   2019-01-26 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning autoencoder domain_adaptation styilzation artistic_stylization photorealistic_stylization wct
---

<a href="https://arxiv.org/pdf/1702.05464.pdf" target="_blank">https://arxiv.org/pdf/1702.05464.pdf</a>


### Abstract
* `Image stylization`: transferring style of a ref photo to a content photo
* `Photorealistic` image stylization: add __photorealistic__ constraint

Conventional `IST`s
* tend to generate __spatially inconsitent stylizations__ with noticeable artifacts (=byproducts)

The proposed method consists of
* stylization step: transfers the style of the reference photo
	* is based on the `whitening` and `coloring transform` (`WCT`), which was designed for artistic stylization (suffers from structural artifacts when applied to Photorealistic image stylization)
* smoothing step: ensures spatially consistent stylization
	* based on `manifold ranking` algorithm
	* utilize a novel network design for feature transform?
	

Each of the steps has a __closed-form solution__ thus can be computed efficiently.


### Intro

Gatys et al
* 7: Texture synthesis using convolutional neural networks, NIPS, 2015
* 8: Image style transfer using convolutional neural networks, CVPR, 2016
* shows that the correlations between deep features encode the visual style of an image
* [7, 8] proposed optimization-based method, the nueral-style transfer algorithm, for image stylization.
	- matching the Gram matrices of deep features extracted from the content and style photos
* impressive performance in `artistic stylization` (converting )
* introduces structural artifacts and distortions, when applied to photorealistic image stylization

Luan et al
* 9: Deep photo style transfer
* on `neural transfer` alg of [7, 8], proposed adding a _regularization term_, for avoiding distortions
* often results in __inconsistent stylizations in semantically uniform regions__




Link:  
[6] <a href="https://arxiv.org/pdf/1502.02791" target="_blank">Learning transferable features with deep adaptation networks</a>  
[13] <a href="https://arxiv.org/abs/1606.07536" target="_blank">Coupled Generative Adversarial Networks</a>  

Next:  
[6] - Learning transferable features with deep adaptation networks   
[13] - Coupled Generative Adversarial Networks


