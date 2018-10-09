---
layout: post
title:  "Hyperparams of google networks"
date:   2018-10-10 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning basenet hyperparams
---



### Tensorflow-Slim

<a href="https://github.com/tensorflow/models/blob/master/research/slim/train_image_classifier.py" target="_blank">`slim`-general training</a> 
- learning rates, decay strategy for various optimizers (+poly)
- For each replica (note that sync=false), weight_decay 0.00004, batch_size 32, lr 0.01(?), 
- num_processing_threads=4


<a href="https://github.com/tensorflow/models/blob/master/research/slim/train_image_classifier.py" target="_blank">`slim`-Inception ResNet</a> 
- batch_norm_decay=0.9997, batch_norm_epsilon=0.001, dropout 0.8


### Xception
deeplab v3+ paper  
1. Nesterov momentum optimizer with momentum = 0.9, initial learning rate = 0.05, rate decay = 0.94 every 2 epochs, and weight decay 4e − 5. We use asynchronous training with 50 GPUs and each GPU has batch size 32 with image size 299×299
2. reproduced resnet-101 with the same training protocols?

<a href="https://github.com/keras-team/keras-applications/blob/master/keras_applications/xception.py" target="_blank">Official `keras` implmentation</a>
1. uses basic params of layers.BatchNormalization(momentum=0.99, epsilon=0.001)

Next:  