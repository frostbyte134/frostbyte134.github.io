---
layout: post
title:  "Unsupervised/pre-training kernels of Convolutional layers"
date:   2018-04-11 20:46:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---

>Typically, the most expensive part of convolutioanl network training is learning the features. The output layer is usually relatively inexpensive because of the small number of features provided as input to this layer after passing through several poolings.
  
One way to reduce the cost of convolutioanl network training is to use features that are not trained in a supervised fashion.
EX) learn kernels with an unsupervised fashion. Coates et al (2011) applied k-means to small image patches, then use each learning centroid as a convolutional kernel.
  
An intermediate approach is to learn the features, but using methods that do not require full forward and B-prop at every gradient step
- Greedy layer-wise pretraining (`Convolutioanl deep belief network`)
  
Today, most convolutional networks are training in a purely supervised fashion, using full forward and b-prog through the entire network on each training iteration.  
As with other approaches to unsupervised pretraining, it remains difficult to tease apart the cause of some of the benefits seen with this approach. Unsupervised pretraining may offer some regularization relative to supervised training, or it may simply allow us to train much larger architectures b/c of the reduced computational cost of the learning rule.
  
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>
