---
layout: post
title:  "Bag of Tricks for Image Classification with Convolutional Nerual Networks"
date:   2019-06-01 09:10:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning classification segmentation detection
---

Revision history
1. 2019-06-01
2. 2019-08-17

<a href="https://arxiv.org/abs/1705.07904" target="_blank">https://arxiv.org/abs/1812.01187</a>

<a href="https://drive.google.com/file/d/1cX_HJdGHAq7JLoFvsjCr2ZHYv-LNFttf/view" target="_blank">Read paper from ipad</a>

### Abstract, Intro
* __training procedure refinement__, such as changes in data augmentations and optimization methods
* ... we will examine a collection of such refinements and empirically evaluate their impact on the final model accuracy through ablation study.
* many of them are minor __tricks__ like modifying the stride size of a particular convolution layer or adjusting learning rate schedule.
* `ResNet-50` top-1, 75.3 -> 79.29


### Mixup
refercence: https://github.com/facebookresearch/mixup-cifar10

```python
def mixup(input1, targ, criterion):
	# TODO: Speed up this process by constructing two matrices and lambda column
	lamb = beta_dist.sample().cuda()
	inds = np.random.permutation(input.size()[0])
	input2 = torch.stack([input[ind] for ind in inds], dim=0).cuda()
	label2 = torch.tensor([targ[i] for i in inds]).cuda()
	output = model(lamb * input1 + (1-lamb) * input2)
	return lamb * criterion(output, targ) + (1-lamb) * criterion(output, label2)
```
