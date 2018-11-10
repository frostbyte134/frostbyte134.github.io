---
layout: post
title:  "RefineNet: Multi-Path Refinement Networks for High-Resolution Semantic Segmentation"
date:   2018-11-9 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning segmentation multipath residual
---

<a href="https://arxiv.org/abs/1706.05587" target="_blank">https://arxiv.org/abs/1706.05587</a>

PASCAL VOC 2012 test mIOU 83.4 

- multi-way, residual (identity mapping, short(inside block), long (U-net like residual).
- mIOU less than Deeplabv3+. Why?
	1. Didnt utilized the global context?. Used several max pooling, which is said to be bad for the localization (CAM paper!)
	2. Problem in optimization - maybe too complex structure. No batchnorm in some convs. 


[22]
Next:  


