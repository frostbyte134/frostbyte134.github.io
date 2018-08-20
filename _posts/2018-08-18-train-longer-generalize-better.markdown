---
layout: post
title:  "Train longer, generalize better: closing the generalization gap in large batch training of neural networks"
date:   2018-08-18 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning SGD large_batch generalization_gap
---

<a href="https://arxiv.org/pdf/1705.08741.pdf" target="_blank">https://arxiv.org/pdf/1705.08741.pdf</a>  


### Abstraction
It has been observed that when using large batch sizes there is a persistent degradation in generalization performance - known as the `generalization gap` phenomenon.  

We find that the weight distance from its initialization grows logarithmically with the number of weight upadtes   \\(\rightarrow\\) therefore propose a "random walk on a random landspace" statistical model, which is known to exhibit similar "ultra-slow" diffusion behavior.  
\\(\rightarrow\\) 


Links:  
<a href="https://arxiv.org/abs/1710.10710" target="_blank">[11] (Freezing Weights) On pre-trained image features and synthetic images for deep learning</a>  
<a href="http://vladlen.info/papers/playing-for-data.pdf" target="_blank">[26] (GTA5) Playing for data: Ground truth from computer games, in ECCV, 2016</a>  
<a href="https://arxiv.org/abs/1605.06457" target="_blank">[7] (VKITTI) Virtual Worlds as Proxy for Multi-Object Tracking Analysis, In CVPR, 2016</a>  