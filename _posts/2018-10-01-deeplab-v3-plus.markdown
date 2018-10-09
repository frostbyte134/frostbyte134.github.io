---
layout: post
title:  "(DeeplabV3+) Encoder-Decode rwith Atrous Separable Conv"
date:   2018-10-01 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning xception jft deeplab segmentation
---

<a href="https://arxiv.org/pdf/1802.02611.pdf" target="_blank">https://arxiv.org/pdf/1802.02611.pdf</a> 

__Read from training part after 2nd code review__

### Few peculiar conceps
* `resolution` could mean \\(W\times H\\) of a feature map, or a __resoultion of input image__ corresponding to a pixel in feature map.


### Questions
2. The role of `Image Pyramid`
1. multi_scale_logits = `MS` in eval?
3. Changing the OS during eval = change the atrous rate???  
Why does it work well?
1. poly learning policy???
2. fine-tune batch norm?
	> fine_tune_batch_norm=True, use at least batch size larger than 12 (batch size more than 16 is better). Otherwise, one could use smaller batch size and set fine_tune_batch_norm=False.  
	(fine_tune_batch_norm=)Set to True if one wants to fine-tune the batch norm parameters in DeepLabv3. Set to False and use small batch size to save GPU memory.

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
* Atrous conv controls density  
\\(\rightarrow\\) large rate = large FOW = more dense? (perhaps?)


### Output Stride
* `output stride` (OS): ratio of input image spatial resolution to the final output resolution (before global pooling / fc)
* > For the task of semantic segmentation, one can adopt OS = 16 or 8 (rather than 32 in classification) for __denser feature extraction__ by removing the striding in the last tone (or two) block(s) and applying the atrous conv correspondingly (for OS=8, rate = 2 or 4 for the last two blocks (8=2*4))
* `dense` feature map? more filters? more weights?
	* extracting densor feature maps during evaluation (i.e., eval output stride=8)
	* OS < 4 = more densor feature map = more GPU resource
* How to control OS? - How the atrous setting changed as the OS changes? 
	* One can extract features at an arbitrary resolution by applying the atrous conv, depending on the computation budget  
	* train output stride=32 (no atrous conv at all during training)
* Relation between `resolution` and `OS`  
Note that, in tensorflow `rate`>1 and `stride`>1 cannot happen at the same time (atleast in `SAME` conv)  
\\(\rightarrow\\) atrous conv does not change the \\(W\times H\\). Onny the "__resoultion of input image__ corresponding to a pixel in feature map"

With `Resnet101` as basenet,  
1. resnet_v1_101_beta.resnet_v1_101_beta (beta = change first 7by7 conv by two 3by3 conv)  
```python
blocks = [
      resnet_v1_beta_block(
          'block1', base_depth=64, num_units=3, stride=2),
      resnet_v1_beta_block(
          'block2', base_depth=128, num_units=4, stride=2),
      resnet_v1_beta_block(
          'block3', base_depth=256, num_units=23, stride=2),
      resnet_utils.Block('block4', bottleneck, [
          {'depth': 2048,
           'depth_bottleneck': 512,
           'stride': 1,
           'unit_rate': rate} for rate in multi_grid]),
  ]
return resnet_v1_beta(
      inputs,
      blocks=blocks,...)
```
Note that, resnet_v1_beta_block also returns resent_utils.block
2. resent_utils.block  
- inherits a `namedtuple('Block', ['scope', 'unit_fn', 'args'])`
3. resnet_v1_101_beta.resnet_v1_beta (at the last return)
```python
net = root_blocvk_fn # (maybe 7by7 \\(\rightarrow\\) 2 3by3 happens here)
net = slim.max_pool2d(net, stride=2, padding="SAME")
net = resnet_utils.stack_blocks_denset(net, blocks, output_stride)
```
4. resnet_utils.stack_blocks_dense(input. blocks, output_stride)
```python
for block in blocks: # we have 4 blocks (refer to 1)
	current_stride=1
	rate=1 # rate of atrous conv
	for unit in block.arg  # a block has 3, 4, 23, #multigrid units (refer to 1 and 2)
			if current_stride==output_stride:
				atrous conv(rate=stride, stride=1)
				current_stride *= stride
				# this does not change the W X H (output stride), but maintains the FOV of a unit
			else:
				conv(rate=1, stride=stride)
```
Compare two consecutive convs
\\[\text\{conv(rate=1, stride=2)\}\times 2 \quad VS \quad \text\{conv(rate=2, stride=1)\}\times 2\\]
Resulting feature maps have same FOV for a activation, but their spatial resolution differs (in latter, spatial resolution is maintained)  
* For a basenet to have dense features with normal convolution, while maintaining the FOV (less conv to make end denser = FOV decreased), it have to increase spatial resolution in the very begging conv blocks.  
* BUT if we use atrous conv, we can have dense feature maps at the end, maintaining FOV, while not increasing the spatial resolution of the begging of the network.

Note that, with __store_non_strided_activation__, the last block's stride changes from 2 to 1, we store that conv and do the max-pooling (don't know where they used it)



### Encoder
* No features dilated in the encoder-decoder  
\\(\rightarrow\\) faster computation
* includes Basenet, ASPP, and final 1-by-1 conv
* Output feature = deeplabV3 output b4 logits  
- 256 channels, rich semantic info.


### Decoder
refine_by_decoder function in model.py

* a simple yet effective (this appeared 4 times in the paper) decoder __to recover the object boundary gradually(?)__, 
* Prev(Naive decoders):  
In [24] with OS=16, features gradually, bilinearly upsampled 16times
* No reason stated why above decoder is not good (may not perform well?? wtf)
* Proposed decoder:  
	1. encoder features __bilinearly upsampled__ by a factor of 4 (`decoder_height`=4, 581, model.py)
	2.__1by1 conv__ applied on lowlvl fets to reduce channel (which was 256 or 512), since excessive input fet channels make training harder and encoder features trivial(574, model.py)
	3. encoder features __concatenated__ with the corresponding low-lvl features from basenet (Conv2 b4 striding in ResNet-101)  
	3. __few 3by3 convs__ to refine the fets,(589 or 605, model.py)  
	followied by another simple __bilinear upsample__ by a factor of 4. (288, model.py)
* OS=8 performs best, OS=16 is the most effective

### Options
in `train.py`, 
* FLAGS.train_crop_size = [513, 513]
* base_learning_rate
	1. 0.007 (training on PASCAL sugmented training set (what aug?)), 0
	2. 0.001 for fine-tuning on PASCAL trainval set
* learning_rate_decay_step = 2000, learning_power = 0.9 (hyperparam of poly-learning), momentum = 0.9
* weight_decay = resnet(0.0001), mobilenet/Xception (0.0004)
* upsample_logits = true 


### Modified Xception



Links:  
<a href="https://sthalles.github.io/deep_segmentation_network/" target="_blank"> Pascal MIOU 74% (simpler model)</a>

Next:  