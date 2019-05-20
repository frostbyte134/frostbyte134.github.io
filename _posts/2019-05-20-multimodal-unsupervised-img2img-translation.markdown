---
layout: post
title:  "Multimodal Unsupervised Image-to-Image Translation"
date:   2019-05-20 09:12:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning generative img2img style_transfer
---

<a href="https://arxiv.org/abs/1804.04732" target="_blank">https://arxiv.org/abs/1804.04732</a>

* assumes that `latent space` of imgs can be decomposed into a `content space` and a `style space`
  * `content code` domain-invariantm, encodes the information that should be preserved during tranlation
  * `style code` captures domain-specific properties, represent remaining variations that are not contained in the input iamge

* used `GAN`s to __align the distribution of translated images with real images__
* we assume that the `latent space` of imgs can be decomposed into a `content space` and a `style space`
* we futher assume that _the imgs in different domains share a common content space but not the style space_


### Abstract

Unsupervised img2img translation
* have to learn conditional distribution (givn some image)
    > while this conditional distribution is inherently multimodal (one-to-many), existing approaches make an overly simplified assumption, modeling it as a deterministric 1to1 mapping.  

    \\(\rightarrow\\) fail to generate diverse output img

... we propose Multimodal Unsupervised Image-to-image Translation (MUNIT) framework

We assume that the image representation can be decomposed into a
* `content code` that is domain-invariant, and a 
* `style code` that captures domain-specific properties

... allows users to control the style of translation outputs by providing an example style image

### Intro

* (unsupervised img2img = one2many problem, so deterministic / unimodal [15] approach fails)
* Even if the model is made stochastic by injecting noise, the network usually learns to ignre it (pix2pix)

Multimodeal UNsupervised Img2img Translation (`MUNIT`) framework/problem  
<img src="{{site.url}}/deeplearning/gan/munit.png" width="1400">  
* we assume that the `latent space` of imgs can be decomposed into a `content space` and a `style space`
  * `content code` encodes the information that should be preserved during tranlation
  * `style code` represent remaining variations that are not contained in the input iamge

* we futher assume that _the imgs in different domains share a common content space but not the style space_
* to translate an img to the target domain, we recombine its content code with a random style code in the target style space (fig1(b))
* `content code` + sampled `style code` - various output imgs
* __user_control__ : instead of sampling `style code`, user may select target img - extract `style code` from it - add with `content code` 

### Related works
* In this works, we employ `GAN`s to __align the distribution of translated images with real images__ in the target domain.
* __This problem is inherently ill-posed and requires additional constraints__
    * Some works enforce the translation to preserve certain properties of the source domain data, such as pixel values[21], pixel gradients [22], semantic feature [10], class labels [22], or pairwise sample distance [16]
    * cycle consistencies [7, 8, 9]



<br/><br/>
Next
* [10] : Unsupervised cross-domain image generation, ICLR, 2017
* [15] : Unsupervised image-to-image translation networks, NIPS, 2017
* [16] : One-sided unsupervised domain mapping, NIPS, 2017
* [21] : Learning from simulated and unsupervised images through adversarial training, CVPR, 2017
* [22] : Unsupervised pixel-level domain adaption with generative adversarial networks, CVPR, 2017
