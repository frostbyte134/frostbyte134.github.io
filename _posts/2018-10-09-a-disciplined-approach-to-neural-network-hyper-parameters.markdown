---
layout: post
title:  "A disciplined approach to neural network hyper-parameters"
date:   2018-10-10 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning basenet hyperparams
---

<a href="https://www.reddit.com/r/MachineLearning/comments/8e8f08/r_a_disciplined_approach_to_neural_network/" target="_blank">Reddit post</a> 

1. poly learning policy???
2. fine-tune batch norm?
	> fine_tune_batch_norm=True, use at least batch size larger than 12 (batch size more than 16 is better). Otherwise, one could use smaller batch size and set fine_tune_batch_norm=False.  
	(fine_tune_batch_norm=)Set to True if one wants to fine-tune the batch norm parameters in DeepLabv3. Set to False and use small batch size to save GPU memory.
3. 

### Options
in `train.py`, 
* FLAGS.train_crop_size = [513, 513]
* base_learning_rate
	1. 0.007 (training on PASCAL sugmented training set (what aug?)), 0
	2. 0.001 for fine-tuning on PASCAL trainval set
* learning_rate_decay_step = 2000, learning_power = 0.9 (hyperparam of poly-learning), momentum = 0.9
* weight_decay = resnet(0.0001), mobilenet/Xception (0.0004)
* upsample_logits = true 
	
	
Links:  
<a href="https://sthalles.github.io/deep_segmentation_network/" target="_blank"> Pascal MIOU 74% (simpler model)</a>

Next:  