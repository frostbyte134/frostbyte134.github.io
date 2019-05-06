---
layout: post
title:  "Learning Deconvolution Network for Semantic Segmentation"
date:   2018-10-20 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning segmentation deconvolution unpooling
---

2015, ICCV
PASCAL VOC 2012 test 72.5

### Abstract, Introduction
* Limitation of conventional (pre-2015) seg nets: prone to considering multi-scale objects  
	1. receptive field size fixed - the object that is substantially larger or smaller than the receptive field may be fragmented or mislabeld. In other words, label prediction is doen with the only locla info. for large objs and the pixels that belong to the same object may be inconsistent labels as shown in below figure.  
	<img src="{{ site.url }}/images/deeplearning/seg-lim.png" class="center" style="width:500px"/>
	2. the detailed structures of an obj are often lost or smoothed b/c the label map, input to the deconv layer, is too coarse (dense, os=8 in deeplab!) and __deconv procedure is overly simple.__ Recent (2015) methods use CRF to mitigate this issue (ex - integrate multiple outputs with CRF)  
* The proposed algorithm mitigates the limitations of the existing methods based on fully convolutional networks by __integrating deep deconv net and proposal-wise prediction (by CRF);__


To overcome such issues, the proposing network 
1. try to learn complex deconv nets (composed of unpool, deconv, bn, ReLU).  
Says it is the first one to attempt it.
2. The trained network is __applied to individual obj proposals__ to objtain instance-wise segmentations, which are comnbined (by CRF) for the final semantic segmentation; __it is free from scale issue (lim 1)__ and identifies finer details of objects.

Related works
* In (Fully Convolutional Networks for Semantic Segmentation, CVPR 2015) paper, fc layers in the standard CNNs are interpreted as convolutions with large receptive fields, and seg is achieved using coarse class score maps obtained by feedforwarding an input image.

### Architecture
<img src="{{ site.url }}/images/deeplearning/conv-deconv.png" class="center" style="width:1000px"/>  
* Input image: object proposals from edge-box [28]
* Output image: prob map in the same size to input iamge
* contracting part: VGG (13 layers), 2 fc layers in the end
* expanding part: unpool+deconv+relu, Symmetric with contracting part
* Inference: gather all instance seg results (zero padded to match dimension), perform max or mean gathering for each spatial loc, and apply fc-CRF [16]

### Deconv Network
<img src="{{ site.url }}/images/deeplearning/deconv-unpool.png" class="center" style="width:500px"/>  
* `pooling`: filter noisy activations in a lower layer by abstracting activations in a receptive field with a single represnetative value.  
	* helps classification by retaining only robust activations in upper layers
	* spatial info with a receptive field is lost
* `unpooling`: record `switch variables` map during pooling, and perform reverse operation of pooling
	* useful to reconstruct the structure of input objs (?)
	* yields sparse activation map
* 'deconv`: associate a single input activation with multiple outputs  
	* in this paper, cropped the boundary of the output of deconv, to keep the size of the output map identical to the one from the preceding unpooling layer.
	* The learned filters in deconv layers = bases (in linear algebra sense?) to reconstruct shape of an input obj.  
	\\(\rightarrow\\) similar to the conv net, a hierarchical struct. of deconv layers are used to capture dif. lavel of shape details.

### Training
* lr 0.01., momentum 0.9, weight-decay 0.0005. VGG - imagenet pretrained, 
* Pascal VOC 2012 augmented, train+val as train set. Accuracy tested on val image
* rate decayed by 10 every time validation accuracy plateaus  


[16]   
[28]	
	
Next:  