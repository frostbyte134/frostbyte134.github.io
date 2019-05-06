---
layout: post
title:  "Adversarial Discriminative Domain Adaptation"
date:   2019-01-19 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning gan domain_adaptation gradient_reversal
---

<a href="https://arxiv.org/pdf/1702.05464.pdf" target="_blank">https://arxiv.org/pdf/1702.05464.pdf</a>


### Abstract
* Prior generative approaches show compelling visualiations, but are not optimal on discriminative tasks and can be limited to smaller shifts.
* Prior discriminative approaches could handle larger domain shifts, but imposed tied weights on the model and did not exploit a GAN-based loss.

We propose ... general framework which combine `discriminative modeling`, `untied weight sharing`, and a `GAN loss`, which we call Adversarial Discriminative Domain Adaptation (`ADDA`).

demonstrate ... by exceeding SOTA unsupervcised adaptation results on standard cross-domain digit classification tasks and a new more difficult cross-modality object classfication task.


### Intro

* ... due to a phenomenon known as `dataset bias` or `domain shift`, recognition models trained along with these reprs (basenet, for example) on one large dataset do not generalize to novel datasets and tasks.
> The typical solution is to further fine-tune these nets on task-specific datasets - often too expensive to obtain enough data to finetune the large # of params.

`measure of domain shift`
1. maximum mean discrepancy [5, 6], 
2. correlation distances [7, 8]
3. reconstruct the target from the source repr loss [9]

`Adversarial adaptation methods`
* seeks to minimize an approximate domain discrepancy through an adversarial objective wrt a domain discriminator.
* closely related to `GAN`
* make sure that discriminator cannot distinguish bet the distribution of its training and test domain examples [11, 12, 13]
	* [11, 12] share weights and learn a symmetric mapping of both source and target images to the shared feature space (11 - link. review paper.)
	* [13] decouple some layers thus learning a partially asym mapping (?)

... we propose a novel unified framework for adversarial domain adaptation, allowing us to __effectively examine the different factors of variation between the existing approaches__. Factors - weight sharing, base models, and adversarial losses
* we observe that generative modeling of input image distribution is not necessary, as the ultimate task is to learn a discriminative repr.
* On the other hand, asym mapping can better model the difference in low lvl features than sym ones.

<img src="{{ site.url }}/images/deeplearning/adda.png" class="center" style="width:600px"/>   
`ADDA` 
1. first learns a discriminative repr using the labels in the source domain and 
2. then learns a separate encoding that maps the target data to the same space using an asym mapping learned through a domain-adversarial loss.

### Related work

`MMD`: maximum mean discrepancy loss. Norm of the difference between two domain means.
* The `DDC` method[5] used MMD in addition to the regular classification loss on the source, to lean a repr that is both discriminative and domain invariant.
* [6] - The deep adaptation network (`DAN`) applied MMD to layers embedded in a reproducing kernel Hilbert space, effectively matching higher order statistics of the two distribution (feature alignment in higher space using kernel?)
* In contrast, [8] the deep Correlation Alighment (CORAL)- proposed to match the mean and cov of the two distributions.

... chosen an adversarial loss to minimize domain shift, learning a repr that is simultaneously discriminative of souce labels while not being able to distinguish between domains.
* [11] - ReverseGrad (link, reviewed)

`GAN` related
* pros: no need for complex sampling or inference
* BiGAN, Conditioanl GAN
* GoGAN: domain transfer. traning two GANs to generate the source and target images respectively. 

### Generalized Adversarial Adaptation


Link:  
[6] <a href="https://arxiv.org/pdf/1502.02791" target="_blank">Learning transferable features with deep adaptation networks</a>  
[13] <a href="https://arxiv.org/abs/1606.07536" target="_blank">Coupled Generative Adversarial Networks</a>  

Next:  
[6] - Learning transferable features with deep adaptation networks   
[13] - Coupled Generative Adversarial Networks


