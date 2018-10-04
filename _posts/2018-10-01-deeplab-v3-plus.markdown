---
layout: post
title:  "(DeeplabV3Plus)Encoder-Decode rwith Atrous Separable Conv"
date:   2018-10-01 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning xception jft 
---

<a href="https://arxiv.org/abs/1610.02357" target="_blank">https://arxiv.org/abs/1610.02357</a> 

### (Atrous) Spatial Pyramid Pooling
* `(A)SPP`
* encode multi-scale contextual infroamtion, by probing the incoming features with filters(Atrous Conv) or pooling operations at multiple rates and multiple effective fields-of-view
* atrous conv allows one to control the density of the encoder features (appeared 3 times in the paper)

### Encoder
* `DeeplabV3` as the __Encoder__
* Deeplabv3 is used to encode the rich contextual info. 
* rich semantic info comes from last fet. map
* This paper enhances `encoder-decoder` (fast, good for sharp boundaries) with `ASPP`(augmented with the image-lvl feature in `deeplabv3`) to add contextual info  
(image here)

### Decoder (sim)
* a simple yet effective (this appeared 4 times in the paper) decoder __to recover the object boundary gradually(?)__, 


### Modified Xception



Next:  