---
layout: post
title:  "Cityscape"
date:   2018-11-12 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning 
---

<a href="https://www.cityscapes-dataset.com" target="_blank">https://www.cityscapes-dataset.com</a>


### Deeplab v2

Cityspace test 70.4

2048X1024 image size is challending
1. downsample image by 2. Found this is not good.  
\\(\rightarrow\\) using orig resolution bring 1.9% improvement (mIOU)
2. During inferencing, to deal with the high resolution image,  
	split each images into overlapping regions, similar to [37]("The cityscapes dataset for semantic urban scene understanding, CVPR")
3. replaced VGG-16 with Resnet
4. No multi-scale input, due to limited GPU mem.
5. augmentation (randomly scaling, from 0.5 to 1.5)- 0.6, `ASPP` - 1.2, `LargeFOV` - 2.6%,  CRF - 0.4%.


### Deeplab v3
Cityscape VAL 79.30%
* Trained on train_fine set (2975 images), 90k iterations, 77.23%  
* OS=16/8 (0.6%), `MS` (multi-scale inputs, {0.75, 1, 1.25}, 0.5%), `Flip` (left-right flipped inputs, 0.5%)
* trained on trainval_coarse (3475+20000), `MS` {0.75, 1, 1.25, 1.5, 1.75, 2} - 0.8%, OS=4 - 0.1%


### Deeplab v3+
Cityscape VAL 79.55, test 82.1%
* Xception + DeeplabV3: 77.33% (minor improvement!)  
* + proposing encoder-decoder: +1.46%
* __removing img lvl feature__: +0.4% (!)
* Add entry flow, as `MSRA` did in COCO detection - X-71 net - best (79.55%)
* Then fine-tune the model on the coarse annotations to compete in TEST set - 


### PSPNet

test80.2 (without coarse, 78.4)

* Poly rate policy (90K)
* Notably, took large benefit (1.8%) from coarse set
* No pre-train on COCO (perhaps?)


### Xception?

### Wide resnet?

### Google NAS?



[22]
Next:  


