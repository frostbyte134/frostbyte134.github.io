---
layout: post
title:  "Speed/accuracy trade-offs for modern convolutional object detectors"
date:   2018-06-30 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning cnn resnet detection rcn ssd need_revise
---

CVPR 2017, <a href="https://arxiv.org/abs/1611.10012" target="_blank">https://arxiv.org/abs/1611.10012</a>  

### Abstract, introduction

> The goal of this paper is to serve as a guide for selecting a detection architecture that achieves the right speed/memory/accuracy balance for a given application and platform.

* ... Faster R-CNN, R-FCN and SSD systems, which we view as __meta-architectures__ and trace out the speed-accuracy trade-off curve created by using alternative feature extractors and varying other critical parameters such as image size ...
* ... they often rely on `model ensembling` and `multicrop methods`(??), which are too slow for practical usage.
* We primarily investigate single-model/single-pass detectors, by which we mean models that do not use ensembling, multi-crop methods, or other "tricks" such as `horizontal flipping`(??).
* ... show that using fewer proposals for `Faster R-CNN` can spped it up significantly without a big loss in accuracy, making it competitive with its faster cousins, SSD and RFCN.
* ... show that `SSDs` performance is _less sensitive to the quality of the feature extractor_ than Faster R-CNN and R-FCN.
* ... identify __sweet spots__ on the accuracy/speed trade-off curve where _gains in accuracy are only possible by sacrificing speed_.


### Meta-architectures
1. `R-CNN` method took the straight forward approach of cropping externally computed box proposals out of an input image and running a neural net classifier on these crops.  
\\(\leadsto\\) duplicate computation from overlapping crops
2. `Fast R-CNN` alleviated the problem by cropping from an intermediate (conv) layer.

Recent works have shown that it is possible to __generate box proposals using neural networks__ using the concept of `anchor`s.
* `anchors` \\(a\\): collection of boxes overlaid on the image at different loc, shape and ratios (= `default boxes` = `priors`)  
	A model is trained to make 2 prediction over each anchor
	1. discrete class prediction (__classification__)for each anchor
	2. contious prediction (__regression__) of an offset by which the anchor needs to be shifted to fit the groundtruth bounding box.

Specifically, for each anchor \\(a\\), we try to find the best matching GT box \\(b\\). 

1. If such a matching is found we call \\(a\\) as __positive anchor__, and assign it  
	1. class label \\(y_a\in\\{1,...,K\\}\\) for the anchor \\(a\\) and  
	2. a vector encoding of box \\(b\\) wrt anchor \\(a\\). (called the __box encoding__ \\(\phi(b_a;a)\\)).  
2. If not found, we call \\(a\\) as __negative anchor__, and
	\\[y_a=0\\]

Then _the loss_
\\[L(a;I;\theta)=\alpha1[a \textrm\{ is positive\}]l_\{loc\}(\phi(b_a;a)-f_\{loc\}(I;a;\theta))+\beta l_\{cls\}(y\_a,f_\{cls\}(I;a;\theta))\tag\{1\}\\]
_for anchor_ \\(a\\) is measured as the sum of
1. localization error (regression)
\\[\alpha1[a \textrm\{ is positive\}]l_\{loc\}(\phi(b_a;a)-f_\{loc\}(I;a;\theta))\\]
2. classification error
\\[\beta l_\{cls\}(y\_a,f_\{cls\}(I;a;\theta))\\]
where
* \\(f_\{loc\}(I;a;\theta))\\): prediction of box encoding of \\(a\\) wrt \\(I, \theta\\)
* \\(f_\{cls\}(I;a;\theta))\\): class prediction of \\(a\\) wrt \\(I, \theta\\)
Such measure is averaged over the all anchors \\(a\\), and minimized wrt \\(\theta\\).




### Meta-architecture - SSDs
<img src="{{ site.url }}/images/deeplearning/tradeoff/ssd.png" class="center" style="width:500px"/>

... we use the term `SSD` to refer broadly to architectures that __use a single feed-forward convolutional network to directly predict classes and anchor offsets without requiring a second stage per-proposal classification operation.

* Both Multibox and region proposal network (__RPN__) stage of Faster R-CNN use this approach to predict class-agnostic box proposals.


### Meta-architecture - Faster R-CNN
<img src="{{ site.url }}/images/deeplearning/tradeoff/faster.png" class="center" style="width:500px"/>

In the Faster R-CNN setting, detection happens in two stages.
1. in _region proposal network (__RPN__), images ar processed by a feature extractors (VGG, Resnet,...) and features are selected in some intermediate lvl, to predict a class-agnostic box proposals.  
	* The loss function for this stage takes the form of equ(1), using a grid of anchors tiled in space, scale and aspect ration. (How can we use (1) if the box-proposals are not aware of the classes?)
2. in the 2nd stage, these (typically 300) box proposals are used to crop features from the same intermediate feature map, which are subsequently fed to the remainder of the feature extractor, to predict a class and class-specific box-refinement for each proposal.  
	* The loss function again takes the form of equ(1) using the proposals generated from the RPN as anchors.


### Meta-architecture - R-FCN
<img src="{{ site.url }}/images/deeplearning/tradeoff/rfcn.png" class="center" style="width:500px"/>

... is like Faster R-NN, but instead of cropping features from the same layer where region proposals are predicted, crops to the last layer minimizes the amount of of features prior to prediction.
\\(\leadsto\\) minimize the pe-region computation that must be done


### Experimental setups
need_revise

Links:  
<a href="https://arxiv.org/abs/1611.10012" target="_blank">https://arxiv.org/abs/1611.10012</a>  