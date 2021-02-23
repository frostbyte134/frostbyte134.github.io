---
layout: post
title:  "Perceptual Losses for Real-Time Style Transfer and Super Resolution"
date:   2019-05-08 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning generative style_transfer perceptual gram_matrix
---

<a href="https://arxiv.org/abs/1603.08155" target="_blank">https://arxiv.org/abs/1603.08155</a>

### Abstarct, Intro
We consider __image transformation problems__
* `denoising`, `super-resolution`, `colorization`, `semantic segmentation`, `depth estimation`

#### Losses in image transformation problems
1. `per-pixel loss`
    * low-level
    * small variation on objects (yellow -> blue car) penalized heavily
    * for two identical imgs offset from each other by one pixel, despite their __perceptual similarity__ they would be very different as measured by per-pixel loss
2. `perceptual loss`
    * uses pretrained DNN as the feature extractor
    * high-level (semantic)
    * __allows the transfer of semantic knowledge from the loss network to the transformation network__ (need not learn from the scratch)

#### Conventional approaches
* `per-pixel loss` (low-lvl, week in perturbation) + single-pass DNN
* `perceptual loss` + optimization (slow inference)

This work proposes, `perceptual loss` + single pass DNN


`style-transfer` problem is __ill-posed__ - there is no single correct output.


### Related work
Gatys et al [10] - __artistic style transfer__, combining the content of one image with the style of another by jointly minimizing the `feature reconstruction loss` of [6] and a `style reconstruction loss` also based on features extreacted from a pretrained CNN


### Method

<img src="{{site.url}}/images/deeplearning/gan/perceptual_model.png" width="1000">

1. Draw image from __Image transform net__ (downsample + resblk + upsample)
2. calculate `feature reconstruction loss`: normalized l2-dist of feature locations on `VGG-16`
3. calculate `style reconstruction loss`: Frobenious Norm of the two gram-matrices, constructed with VGG16 features from synthetic and real img

### Gram-matrix (Style recon loss)
`Gram-matrix` is a (uncentered - did not extract mean) covariance matrix  between (features of VGG16 from real img) and (features of VGG16 from synthetic img)


<img src="{{site.url}}/images/deeplearning/gan/gram_mat.png" width="800">

Therefore, \\(i, j\\) th component of the gram matric is the spatial-wise (1dim - cross product of spaces, 2dim - Hadammard product of imgs) linear relation between \\(i\\)th filter channel and \\(j\\)th filter channel.

> It captures information about which features tend to activate together.



Next
* 