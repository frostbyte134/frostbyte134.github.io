---
layout: post
title:  "Stacked Deconvolution Network for Semantic Segmentation"
date:   2018-11-03 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning segmentation deconvolution
---

<a href="https://arxiv.org/pdf/1708.04943.pdf" target="_blank">https://arxiv.org/pdf/1708.04943.pdf</a>

PASCAL VOC 2012 test mIOU 86.6


### Abstract
* Recent progress in semantic segmentation has been driven by improving the spatial resolution under FCNs.
* TO address this, we propose a __stacked deconv network__ (`SDN`) for semantic segmentation.
	* __multiple shallow deconv nets (SDN units) are stakced__ to integrate contextual info and grarantee the fine recovery of localization information.
	* __inter/intra unit connections__ are designed to asssist net training and enhance feature fusion, since the connections improve the flow of info and gradient propagation.
	* __hierachical supervision__ is appiled during the upsampling proc of each SDN unit, which guarantees the discrimination of feature reprewssentations and benefits the network optimziation.

### Introduction
> However, the classification network with downsampling sacrifices the spatial resolution of featuire maps to obtain the invariance to image transformations (isn't this property comes from the conv operation)  
The resolution reduction results in poor object delineation and small spurious regions in segmentation outputs.

Many approaches have been proposed to solve the above problems.
1. apply dilated conv:  
	pros: larger contextual info is caputred without losing the spatial resolution.  
	cons: output a coarse subsampling feature maps



[22]
Next:  


