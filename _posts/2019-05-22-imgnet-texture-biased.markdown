---
layout: post
title:  "ImageNet-Trained CNNs Are Biased Towards Texture"
date:   2019-05-22 09:10:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning style_transfer basenet
---

<a href="https://arxiv.org/abs/1811.12231" target="_blank">https://arxiv.org/abs/1811.12231</a>

<a href="https://drive.google.com/file/d/1JimNd1GQbxOuY5XFCNSUxWFAbnxhsveG/view?usp=sharing" target="_blank">read paper in ipad</a>

`cue-conflict` = evident conflict

### Abstract
* show that __ImageNet trained CNNs are strongly biased towards recognising textures rather than shapes__, which is in stark contrast to huamn behavioural evidence and reveals fundamentally different classification strategies.
* demonstrate that the `ResNet-50` that __learns texture-based representation__ on ImageNet, is able to __learn a shape-based representation__ instead when trained on `Stylized ImageNet`
* improved over detection performance (when replacing basenet), and previously unseen robusetness towards a wide range of image distortions, highlighting advantages of a shape-based representation.


`Stylized ImageNet`
* using `AdaIN`, selected style randomly from the  Kaggle's Painter by Numbers dataset
* object-related local texture info is replaced with random style of artistic paintings.

### Intro


1. Shape hypothesis
   > One widely accepted __intuition__ is that CNNs combine low-level features (e.g. edges) to increasingly complex shapes (such as wheels, car windows) until the object (e.g. car) can be readily classified
2. Texture hypothesis
   * CNNs can still classify texturised images perfectly well, even if the global shape structure is completely destroyed (Gatys et al, 2017)
   * Gatyes et al (2015) discovered that a linear classifier on top of a CNN's texture representation (Gram matrix) achieves hardly any classification performance loss compared to original network performance.
   * Brendel & Bethge 2019 deomnstrated that __CNNs with explicitly constrained receptive field sizes__ throughout all layers are able to reach surprisingly high accuracies on ImageNet, even though this effectively limits a model to recognising small local patches rather than integrating ojecct parts for shape recognition

`cue-conflict`
* Utilizing style transfer (Gatys et al., 2016), we created images with a texture-shape cue conflict such as the cat shape with elemehant texture depicted in Fig1c
* perform 9 experiments comparing human against CNNS on exactly the same images
* _These experiments provide behavioural evidence in favour of the texture hypothesis_
  * A cat with an elemhant texture is an elephant to CNNs, and still a cat to humans

__Changing biases (from texture to shape)__
* texture bias in CNNs can be overcome, if trained on a suitable dataset
* network with a higher shape bias are more robust to many image distortions (for some surpassing human performance, despite never being trained on them) and reach higher performance on classification and object recognition tasks.

### Methods

#### Experiments
... we only selected object and texture imgs that were correctly classified by all four networks. This was made to ensure that our resutls in the 6th experiment on `cue conflicts` (A cat with an elemhant texture), which is most decisive in terms fo the shape vs texture hypothesis, are fully interpretable.

Following Gatys et al. (2017), we define `texture` as an __image (regoin) with spatially stationary statistics.__

5 basic recognition experiments: Original, Greyscale, Silhouette, Edges, Texture
* Original, Texture : recovnised correctly by both CNNS and humans
* Greyscale : were recognised equally well
* Silhouette : CNN recognition accuraciees were much lower than human's
* Edge : more severe than Silhouete

One coufound in these experiments; CNNs tend not to cope well with domain shifts, i.e. the large change in img statistics from natural images (on which the networks have been trained) to sketches (which the networks have never seen before)

* Cue conflict: Human(texture, 95.9%) vs CNNS (texture, 17, 30, 40, 22)


#### Stylized Imagenet
* using `AdaIN`, selected style randomly from the  Kaggle's Painter by Numbers dataset
* object-related local texture info is replaced with random style of artistic paintings.

#### Overcoming the texture bias of CNNs

One reason (of the texture biases) might be the training task itself: From the `BagNet`, we know that ImageNet can be solved to high accuracy using only local info. In other words, _it might simply suffice to integrate evidence from many local texture features rather than going through the process of integrating and classifying global shapes_.  
\\(\rightarrow\\) to test this hypothesis, trained a ResNet-50 on Stylized-ImageNet (`SIN`) which the object-related local texture info is replaced with random style of artistic paintings.


1. Dataset comparison
   1. ResNet-50 trained and evaluated in `SIN`: top5 79%
   2. ResNet-50 trained and evaluaed in  `IN`: top5 92%
   
   \\(\rightarrow\\) `SIN` is a much harder task than `IN`, since textures are no longer predictive, but instead a nuisance factor (since the styles are selected randomly)
2. Cross-evaluation
   1. `IN` features generalize poorly on `SIN` (16.4% top5)
   2. `SIN` learned features generalze very well on `IN` (82.6 top5)
3. Testing whether local texture features are still sufficient to solfe `SIN`, used `BagNets` (restriced receptive field size)
    - high accuracy on `IN` (top5 70%, 9x9 `BagNet`), low in `IN` (10% top5, 9x9 `BagNet`)
4. `SIN`-trained Resnet-50 showed much stronger shape bias (81%) than `IN`-trained resnet (21%), which is almost strong as for humans

<br/><br/>
Next
`CBN`
* [9] : Modulating early visual processing by language
* [18] : multimodal unsupervised img2img translation, ICCV 2017
* [29] : Which training methods for gans do acually converge
* [31] : cGANs with projection discriminator, ICLR 2018
* [34] : Learning visual reasoning withou string priors
* [35] : Semi-parametric image synthesis, CVPR 2018

RandN input is a simple and natural way for multimodal synthesis
* [18] : Multimodal unsupervised image-to-image translation,k ECCV 2018, NVIDIA
* [50] : Toward multimodal img2img translation