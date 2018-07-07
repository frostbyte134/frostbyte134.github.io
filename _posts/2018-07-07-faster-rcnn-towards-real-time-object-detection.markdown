---
layout: post
title:  "Faster R-CNN: Towards Real-Time Object Detection with Region Proposal Networks"
date:   2018-07-07 16:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning rcnn detection need_revise
---

NIPS 2015, <a href="https://papers.nips.cc/paper/5638-faster-r-cnn-towards-real-time-object-detection-with-region-proposal-networks" target="_blank">https://papers.nips.cc/paper/5638-faster-r-cnn-towards-real-time-object-detection-with-region-proposal-networks</a>  

### Abstract, introduction

* Suggested _Region Proposal Network_ __(RPN)__, that shares full-image convolutional features with the detection network.
* RPN and Fast-RCNN are merged into a single network by __sharing their convolutional features__ (NN with `attention` mechanism - RPN tells the unified network where to look) 
* PASCAL VOC 2007, 2012, MS COCO, and ILSVRC, 300 proposals/image
* ... observation is that the convoilutional feature maps used by region-based detectors, like Fast R-CNN, can also be used for generating region proposals.
* ... we introduce novel 'anchor' boxes that serve as __references at multiple scales and aspect ratios__.
* ... propose training scheme that alternates between fine-tuining for the regoin proposal task and then fine-tuning for object detection, while keeping the proposals fixed.


### Related work
1. `R_CNN`
	* Region proposals done by conventional (Non DL) methods
	* No object bounds
2. `OverFeat` methods
	-1. Fully connected layer is trained to predicts box coordinates for the localization task, assuming single object  
	-2. Then FCN is turned into(???) convolutional layer for detecting multiple class-specific objects.  
	* colvonutional features are computed from an image pyramid for classification, localization, and detection.
3. `Multibox` methods
	* Like Faster-RCNN, also generates region proposals from the network
	* at the same time, the network predicts multiple class-agnostic boxes, generalizing the "single box" fashion of `OverFeat`.
	* Such class-agnostic boxes are used as proposals for R-CNN.
	* However, `Multibox` does not share features between the proposal and detection network.

Links:  
<a href="https://arxiv.org/abs/1611.10012" target="_blank">https://arxiv.org/abs/1611.10012</a>  