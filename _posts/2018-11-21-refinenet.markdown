---
layout: post
title:  "RefineNet: Multi-Path Refinement Networks for High-Resolution Semantic Segmentation"
date:   2018-11-14 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning cam basenet localization 
---

<a href="https://arxiv.org/abs/1611.06612" target="_blank">https://arxiv.org/abs/1611.06612</a>

* PASCAL VOC 2012 test 83.4
* Complicated (in upsampling) U-Net.
	1. Apply conv to all (multi-path) inputs, so that every feature map resolutions are fit to the smallest one (meh)  
	2. all feature maps are upsampled(bilinear) to the largest resolution of the inputs  

### Abstract
* `RefineNet`, a generic multi-path refinement network that explicitly exploits all the information available along the down-sampling process to enable high-resolution prediction using long-range residual connections.
* The individual components of RefineNet employ residual connections following the identity mapping mindset, which allows for effective end-to-end training.
* ... we introduce `chanied residual pooling`, which captures rich background context in an efficient manner.

### Introduction

Multiple striding/pooling reduces final image prediction typically by a factor of 32, losing much of the finer structure.
* learn `deconv filters` as an up-sampling operation.  
	The deconv operation are not able to recover the low-lvl visual features, which are lost after the downsampling operation in the convolution forward stage.
* atrous, replace striding with dilation (`DeepLab-v2`)  
	* perform convs on a large number of detailed (high-res) fet maps that usually have high dimensional features, which are computationally expensive.  
	* __atrous conv introduce a coarse sub-sampling of features__, which potentially leads to a loss of important details.
* exploit features from intermediate layers  
	\\(\rightarrow\\) use long-range resnet conn.
	* high-lvl semantic features help the category recognition of image regions
	* low-lvl visual features help to generate sharp, detailed bndries for high-res prediction.
	* mid-lvl - open question.

Out __main contributions__ are as follows:
1. Propose a muilti-path refinement network (`RefineNet`) -recursive, cascaded, flexible.
2. `RefineNet` can be effectively trained  
	... all components employ residual connections with identity mappings, such that gradients can be directly propagated through short-range and long-range residual connections along for both effective and efficient end-to-end training (link for wide-resnet)

3 (chained residual pooling), 4 (test on datasets) skipped
	
### Related works
* `Deeplab-CRF (v2)`: directly output a middle-res score map and then applies a dense CRF to refine bndries by leveraging color contrast information.
* `CRF-RNN` extends this by implementing RNN layers for end-to-end learning of the denseCRF and FCNN.

There exist several methods which exploit middle layer fetures for segmentation.
* FCN method of Long et al [36]  
	* adds prediction layers to middle layers to generate prediction scores at multiple res.
	* averageed the multi-res scores to generate the final pred
	* trained in a stage-wise manner, rather than end-to-end
* The `Hypercolumn` approach merges features from middle layers and learns dense classification layers.
* Both `SegNet` and `U-Net`(link) apply skip-connections in the deconv architecture to exploit the features from middle layers.

`RefineNet` employs short-range and long-range residual connections with identity mappings which enable effective end-to-end training of the shole system. (link wideresnet)

### Background
* The sequential subsampling (of `ResNet`) has two effect:
	1. it increases the receptive field of convolutions at deeper lvls, enabling the filters to capture more global and contextual info which is essential for high quality classification.
	2. for efficient training

typically, os=32 for classification (with thousands channels). This low-res feature map loses important visual details captured by early low-lvl filters, resulting in a rather coarse segmentation map.

... explaination of Deeplab-v2 methods (atrous-striding)...

### RefineNet

- explain omitted. Complicated (in upsampling) U-Net.
> 1. Apply conv to all (multi-path) inputs, so that every feature map resolutions are fit to the smallest one (meh)
2. all feature maps are upsampled to the largest resolution of the inputs  

[36]
Next:  


