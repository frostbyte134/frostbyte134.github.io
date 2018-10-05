---
layout: post
title:  "(DeeplabV3+) Encoder-Decode rwith Atrous Separable Conv"
date:   2018-10-01 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning xception jft 
---

<a href="https://arxiv.org/pdf/1802.02611.pdf" target="_blank">https://arxiv.org/pdf/1802.02611.pdf</a> 

__Read from training part after 2nd code review__

### Questions
1. `dense` feature map? more filters? more weights?
2. The conv was "SAME" in code, so can't figure out what they mean by "controlling density" using atrous conv
3. How to control OS with dilation(rate)? - How the atrous setting changed as the OS changes?  
> One can extract features at an arbitrary resolution by applying the atrous conv, depending on the computation budget
("resolution"? wasn't the code uses SAME conv in args?)

### (Atrous) Spatial Pyramid Pooling
* `(A)SPP`
* encodes multi-scale contextual infroamtion, by probing the incoming features with filters(Atrous Conv) or pooling operations at multiple rates (= multiple fields-of-view)
* rates = dilation = distance between filter elements  
rate2 3by3 conv has __same FOV__ with rate1 5by5?

### Atrous conv
* atrous-conv allows one to control the density of the encoder features (appeared 3 times in the paper) 
* last feat map is rich in semantic info., but lacks obj boundaries  
\\(\\rightarrow\\) apply the atrous conv to obtain denser feature maps
* V3+ added `Image-level pooling` - \\((W\times H\times C)\quad\rightarrow\quad(1\times 1\times C)\quad\rightarrow\quad(W\times H\times \text\{#Classes\})\\)
* > One can 

### Output Stride
* `output stride` (OS): ratio of input image spatial resolution to the final output resolution (before global pooling / fc)
* > For the task of semantic segmentation, one can adopt OS = 16 or 8 (rather than 32 in classification) for __denser feature extraction__ by removing the striding in the last tone (or two) block(s) and applying the atrous conv correspondingly (for OS=8, rate = 2 or 4 for the last two blocks)

### Encoder
* No features dilated in the encoder-decoder  
\\(\rightarrow\\) faster computation
* includes Basenet, ASPP, and final 1-by-1 conv
* Output feature = deeplabV3 output b4 logits  
- 256 channels, rich semantic info.


### Decoder
* a simple yet effective (this appeared 4 times in the paper) decoder __to recover the object boundary gradually(?)__, 
* Prev(Naive decoders):  
In [24] with OS=16, features gradually, bilinearly upsampled 16times
* No reason stated why above decoder is not good (may not perform well?? wtf)
* Proposed decoder:  
	1. encoder features __bilinearly upsampled__ by a factor of 4
	2. __concatenated__ with the corresponding low-lvl features from basenet (Conv2 b4 striding in ResNet-101)  
	b4 concat, __1by1 conv__ applied on lowlvl fets to reduce channel (which was 256 or 512), since excessive input fet channels make training harder and encoder features trivial
	3. __few 3by3 convs__ to refine the fets, followied by another simple __bilinear upsample__ by a factor of 4.
* OS=8 performs best, OS=16 is the most effective

### Modified Xception



Links:  
<a href="https://sthalles.github.io/deep_segmentation_network/" target="_blank"> Pascal MIOU 74% (simpler model)</a>

Next:  