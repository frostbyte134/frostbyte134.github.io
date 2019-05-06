---
layout: post
title:  "(Deeplab V3) Rethinking Atrous Convolution for Semantic Image Segmentation"
date:   2018-11-10 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning segmentation deconvolution belief_map
---

<a href="https://arxiv.org/abs/1706.05587" target="_blank">https://arxiv.org/abs/1706.05587</a>

PASCAL VOC 2012 test mIOU 85.7 (86.9 with JFT)


### Abstract
* ... we revisit atrous conv, a powerful tool to explicitly adjust filter's FOV (field of view) as well as control the resolution of feature responses computed by DCNN.
* To handle the __problem of segmentating objects at multiple scales__, we design modules which employ atrous conv in cascade of in parallel to cpature multi-scale context by adopting multiple atrous rates.
* no DenseCRF post-processing

### Introduction
Two main challenges in applying DCNN to segmentation
1. reduced feature resolution, caused by consecutive pooling/striding.  
It gives invariance to translation (abstraction), which is harmful to segmentation by worsening localization power.  
	\\(\rightarrow\\) advocate the use of atrous conv  
	... removing the downsampling operations from the last few layers and upsamplking the corresponding filter kernels, equivalent to inserting holds between filter weights.
2. existence of objects at multiple scales.
	Prev approaches - 
	1. image pyramid (multiscale, parallel)
	2. encoder-decoder structure
	3. extra modules (DenseCRF)
	4. spatial pyramid pooling (multiple rates at last feature map)
	
	... we revisit applying atrous conv to spp.  
	> In particular, our proposed module consists of atrous conv with various rates and __batch norm layers, which we found important to be trained as well.__
	
We discuss an important practical issue when applying a 3by3 atrous conv with an extrememly large rate, which fails to capture long-range inf due to image boundary, effectively simply degenerating to 1by1 conv, and propose to incorporate image-level features into the ASPP module.

(If one can find a way to limit the fields of atrous conv not to overrun the feature map size, )

### Related work

... we discuss 4 types of FCN that exploit context information for semantic segmentation.

1. __Image pyramid__: The same model, typically with shared weights, is applied to multi-scale inputs, Feature responses from the small scale inputs encode the long-range context, while the large-scale inputs preserve the small object details.
	* The main drawback: it does not scale well for larger/ddeper DCNNs due to limited GPU memory.
2. __encoder-decoder__: this model consists of two parts.
	1. __the encoder__ where spatial dimension of feature maps is guadually reduced, and thus loger range info is easily capured
	2. __the decoder__ where object details and spatial dimension are gradually recovered.
	
	* `segnet`: reuses the pooling indicees from the encoder and learn extra conv layers to densify the feature responses
	* <a href="{{site.url}}/deep_learning/2018/10/18/unet.html" target="_blank">`U-Net`</a>: adds skip connections from the encoder features to the corresponding decoder activations
	* `Refinenet` (next paper to review, add link): have demonstrated the effectiveneww of models based on encoder-decoder structure on several semantic segmentation benchmarks.
	* `Context module`: DenseCRF. Joint training of CRF and DCNN [96, 55, 73], while [59, 90] employ several extra conv layers on top of the `belief maps` of DCNN (belief maps: final DCNN feature maps that contain output channels equal to the number of predicted classes)  to cappture context info. Recently, [41] proposes to learn a general and sparse high-dimensional conv (`bilateral convolution`) and [82, 8] combine Gaussian CRF and DCNN for semantic segmentation.
3. __spatial pyramid pooling__: 
	* `Deeplab`: multi-scale parallel atrous conv at the final feature map
	* <a href="{{site.url}}/deep_learning/2018/11/01/pspnset.html" target="_blank">`PSPnet`</a>: spatial pooling at several grid scales
	* ... `LSTM` to aggregate global context [53, 6, 88]
4. __atrous conv__: deformable conv net (link later)


### Methods
__Atrous convolution__:  

Instead of deconv layers to recover the decimated feature maps, we advocate the use of atrous conv to maintain the feature map size, while also preserving the FOV (compared to the FOV on strided feature map)

... Atrous conv also allos us to explicitly control how densely to compute feature response in fully conv nets.

... we denote `output_stride` the __ration of input image spatial resolution to final output resolution__.

If one would like to double the staptial density of computed feature responses in the DCNN, the stride of last pooling or conv layer is set to 1 (instead of 2) to avoid signal decimation. Then, __all subsequent conv layers are replaed with atrouc conv with double rate__.  
(Note that, doubling rate may act like halving the fature map in 1 step, but as the network stacked it is just adding constant 2 to the FOV of filters. Thus we need to double it every time.) 


__Going Deeper with Atrous Conv__:  
\\(\rightarrow\\) conclusion: parallel atrous conv (`ASPP`) is better than consecutive striding/atrous conv  
1. Consecutive striding:  
In the last Resnet block (block 4), added 3 replicas (same structure) with striding, which has `output_stride=256`.  
2. Consecutive atrous conv (`Multi-grid method`: employ a hierarchy of grids of different sizes):  
OS=16 - 2 * [1, 2, 4] rates  
<img src="{{ site.url }}/images/deeplearning/consec.png" class="center" style="width:800px"/>  
3. ASPP: Compared to Deeplab v2, added image-level by GAVP (atrous conv with too large rate degenerated to 1by1 conv, since the filter weights of edges are applied to zero-padding region, so the middle filter weight is only effective)  
\\(\rightarrow\\) one 1by1, three 3bye with rates (6, 12, 18), and image-lvl GAVP, when `os=16`. The rates doubled when `OS=8`.


### Experiments

* Train OS=16, val os=8, crop_size=513, poly-policy with power 0.9
* phase 1 (with pretrained basenet): lr 0.0007, batch_norm_decay=0.0003, `trainaug` set, 30K iters
* phase 2 : lr 0.0001, freeze batch norm params, 30K iters
* Upsampling logits: Instead of downsampling images as in prev deeplabs, upsampled logits. Note that, __size of the input image matters__ for the large rate of atrous conv to be effective.
* augmentation: random scaling of input image (0.5 to 2.0), random left-right flipping (horizontal).
* duplicated the images that contain hard class (bycicle, chair, table, potted-plant, sofa)
* JFT (meh)
* 

Details of ablation study is in the appendix.

Async training?

__Cityscape__: 
1. more iterations (30K), larger crop size (769)
2. multi-scale {0.75, 1, 1.25, 1.5, 1.75, 2} with os=4 on CPU (wtf), 81.3% on test set.

[22]
Next:  


