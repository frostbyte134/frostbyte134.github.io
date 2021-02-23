---
layout: post
title:  "Stacked What-Where Autoencoders"
date:   2019-02-02 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning autoencoder
---

<a href="https://arxiv.org/abs/1506.02351" target="_blank">https://arxiv.org/abs/1506.02351</a>

"The idea behind using reconstruction as a regularizer"

### Abstract

(Proposing method) uses a convnet to encode the input, and employs a deconvnet (Zeiler et al, 2010) to produce the reconstruction. The obj func includes reconstruction terms that induce the hidden states in the Deconvnet to be similar to those of the Convnet.

Each pooling layer produces two sets of variables; the "what" which are fed to the next layer, and its complementary variable "where" that are fed to the corresponding (same lvl in generator) layer in the generative decoder.

### Intro

* Each layer in a `DBM` (Deep Blotzmann Machine) is an restricted boltzmann machne (`RBM`), which can be seen as a type of `autoencoder`.
* pros of Deep RBMs
	* can be trained in supervised, unsupervised, or semi-supervised
	* exploit the advantageous discriminative and generative models
* cons of Deep RBMs
	* poor convergence and mixing properties (?? undesired artifacts for example in image reconstruction?), ultimately due to the __reliance on sampling during training__

The main issue with stacked auto-encoders is __asymmetry__
1. The mapping implemented by the feed-forward pathway is often many-to-one (ex - convnet), for example mapping __images to invariant features__ or to class labels
2. Conversely, the mapping implemented by the feed-back (generative) pathway is one-to-many (e.g. mappng cls labels to image reconstruction). 

The common way to deal with this (in RBM, DBM) is to view the reconstruction mapping as probabilistic. _The missing info that is required to generate an image from a category label is dreamed up by sampling_ (!!).  
\\(\rightarrow\\) interesting visualization, but is impractical for training large nets since it tends to produce highly noisy gradients.

If the internal reprs are to possess good invariance properties, it is desirable that the mapping from one layer to the next be many-to-one (ex - convnets with striding)

Our model attempts to satisfy two objs
1. to learn a factorized repr that encodes invariance and equivariance (???)
2. leverage both labeled and unlabeled data to learn this repr in a unified framework

The main idea is, whenrever a layer implements a many-to-one mapping, we compute (or, store) a set of complementary variables that enable reconstruction.   
In max-pool, we view the position of the maxpool "switches" as the complementary info necessary for reconstruction. 

Feed forward Convnet -> feed-back Deconvnet  
* Each stage in this architecture is what we call a `what-where auto encoder`. 

The encoder is a conv layer with conv-ReLU-mp.
* The output of mp is the `what` variable
* The complementary vars are the max-pooling "switch" positions, which can be seen as the `where` variables.

The generative feed-back decoder reconstructs the input by "unpooling" the `what` using `where`, and running the result through a reconstructing conv layers. The reconstruction penalty at each layer constrains the hidden states of the feed-back pathway to be close to the hidden states of the feed-forward pathway.

Training
1. The system can be trained in __supervised__ manner: the bottom input of the feed-forward pathway is given the input, the top layer of the feed-back pathway is the desired output, and the weights of the decoders are updated to minimize the sum of the reconsturction cost. _If the hidden layer reconstruction costs are used, the model can be seen as supervised with a reconstuction regularization_.
2. In unsupervised mode, the top-layer label output is left unconstrained, and simply copied from the output of the feed-forward pathway.  

Our model is particularly suitable when one is faced with a large amount of unlabeled data and a relatively small amount of labeled data. (???)

Link:  
[6] <a href="https://arxiv.org/pdf/1502.02791" target="_blank">Learning transferable features with deep adaptation networks</a>  
[13] <a href="https://arxiv.org/abs/1606.07536" target="_blank">Coupled Generative Adversarial Networks</a>  

Next:  
[6] - Learning transferable features with deep adaptation networks   
[13] - Coupled Generative Adversarial Networks


