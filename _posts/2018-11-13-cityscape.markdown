---
layout: post
title:  "Cityscape"
date:   2018-11-12 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning 
---

<a href="https://www.cityscapes-dataset.com" target="_blank">https://www.cityscapes-dataset.com</a>

<a href="https://arxiv.org/pdf/1604.01685.pdf" target="_blank">https://arxiv.org/pdf/1604.01685.pdf</a>

### Data Specification
* Several hundreds of thousands of frames were acquired from a __moving vehicle__ during the span of __several months, covering spring, summer, and fall__ in __50 cities__, primarily in Germany but also in neighboring countries. 
* We deliberately __did not record in adverse weather conditions, such as heavy rain or snow__, as we believe such conditions to require specialized techniques and datasets
* Each 16 bit stereo image pair was subsequently __debayered and rectified__
* For comparability and compatibility with existing datasets we also provide low dynamic-range (LDR) 8 bit RGB images that are obtained by applying a logarithmic compression curve.  
  Such tone mappings are common in automotive vision, since they can be computed efficiently and independently for each pixel. To facilitate highest annotation quality, we applied a separate tone mapping to each image.  
  The resulting images are less realistic, but __visually more pleasing and proved easier to annotate__.
* The annotations (see Sec. 2.2) were done on the __20th frame of a 30-frame video snippet__, which we provide in full to supply context information. 
* For the remaining 23 cities, a single image every __20s or 20 m driving distance (whatever comes first)__ was selected for `coarse annotation`, yielding 20 000 images in total.

### Annotation Methods
*  Our 5000 fine pixel-level annotations consist of layered polygons (using LabelME program) and were realized in-house to guarantee highest quality levels
*  Annotators were asked to label the image from back to front such that no object boundary was marked more than once.   
 \\(\rightarrow\\) Each annotation thus __implicitly provides a depth ordering of the objects__ in the scene.

(Skipped the dataset splitting, quaility assurance, ...)


* The annotators were instructed to make use of the `depth ordering` and occlusions of the scene to accelerate labeling, analogously to LabelMe [60]; see Fig. 6 for an example. 
* In doing so, __distant objects are annotated first__, while occluded parts are annotated with a coarser, conservative boundary (possibly larger than the actual object). 
* Subsequently, the occluder is annotated with a polygon that lies in front of the occluded part. Thus, the boundary between these objects is shared and consistent.


* `Holes` in an object through which a background region can be seen are considered to be part of the object. 
* This allows keeping the labeling effort within reasonable bounds such that objects can be described via simple polygons forming simply-connected sets.

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


