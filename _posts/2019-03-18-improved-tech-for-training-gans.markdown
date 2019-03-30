---
layout: post
title:  "Improved Techniques for Training GANs"
date:   2019-03-18 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning gan
---

<a href="https://arxiv.org/pdf/1606.03498.pdf" target="_blank">https://arxiv.org/pdf/1606.03498.pdf</a>



### Abstract, Intro

### Minibatch Features



> <a href="{{site.url}}/deep_learning/2019/03/09/nips2016-gan-tutorial/" target="_blank">(2016 NIPS Tutorial)</a> One attempt is minibatch features (Salimans et al., 2016). The basic idea of minibatch features is to allow the discriminator to compare an example to a minibatch of generated samples and a minibatch of real samples.  
By measuring distances to these other samples in latent spaces, the discriminator can detect if a sample is unusually similar to other generated samples. Minibatch features work well. 

> <a href="{{site.url}}/deep_learning/2019/03/18/pg-gan/" target="_blank">`PG-GAN`</a> (To solve the mode collapse, a tendency to capture only a subset of the variation found in training data), compute feature statistics (of latent vectors) not only from individual imgs but also across the minibatch, thus encourging the minibatches of generated and training iamges to show similar statistics. This is implemented by adding a minibatch layer towards the end of the D, where the layer learns a large tensor that projects the input activation towards to an array of statistics. 