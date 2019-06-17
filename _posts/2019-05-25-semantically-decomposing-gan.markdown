---
layout: post
title:  "(SD-GAN) Semantically Decomposing the Latent Spaces of Generaqtive Adversarial Networks"
date:   2019-05-23 09:10:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning gan style content disentanglement 
---

<a href="https://arxiv.org/abs/1705.07904" target="_blank">https://arxiv.org/abs/1705.07904</a>


### Abstract
* We propose a new algorithm for training GANs that jointly learns latent codees for both `identities` (`things`, e.g. individual humans), and `observations` (`stuff` e.g. specific photographs, random variations)
* By fixing the identity portion of the latent codes (decomposing \\(z\\) into identity/observation parts), we can generate diverse images of the same subjects while maintaining contigent aspects asuch as lighting and pose.
* corresponding __samples from the real dataset consist of two distinct photographs of the same subject__ (severly supervised!)
* ... to fool \\(D\\), \\(G\\) must __produce pairs__ that are photorealistic, distinct, and appear to depict the same individual.


### Intro
> In many domains, a suitable generative process might consist of several stages (mulitstage)

Ex) To geenrate a photograph of a product,
1. sample from the space of products
2. sample from the space of phogographs of _that product_

While we may know the identity of the subject in each photograph (of the products in retail stores, like AMAZON / 11st), we may not know the `contigent aspects` of the observations

`contigent aspects of the observation`
* lighting, pose, backgrounds


Given a set of commonalities, we might want to incorporate this sturcture into our latent representations
* `GAN`s learn mappings from latent codes \\(z\\) in some low-dimentional space \\(Z\\) to points in the space of natural data \\(X\\).
* While GANs are popular, ... they do not, in their original form, explicitly disentangle the latent factors according to knwon commonalities

__In this paper__, we propose Semantically Decomposed GANs (`SD-GAN`s), which encourage a specified portion of the latent scpae to correspond to a known source of variation.
* the technique decomposes the latent code \\(Z\\) into 
  * \\(Z\_i\\) corresponding to identitiy (things)
  * and the remaining portion \\(Z\_O\\) to the other contigent aspects of observations


`SD-GAN`s learn through a __pairwise training scheme__
* a sample from real dataset - a pair of imgs with a common identity (and different variations)
* a sample from \\(G\\) - a pair of imgs with common \\(z\_i\in Z\_i\\) but different \\(z\_o\in Z\_O\\)
* To fool \\(D\\), \\(G\\) must not only produce diverse and photorealistic imgs, but also imgs that depict the same identity when \\(z\_I\\) is fixed.
* we modify the \\(D\\) so that it can determine whether a pair of samples consitutes a match.
* Through face generating experiments, confirmed that \\(G\\) learns certain properties that are free to vary across observations but not identity (pose, expression, hirsuteness, ...)
* the aspects that are more salient for facial verification remain consistent as we vary the observation code \\(z\_o\\)


Experiments
* `SD-GAN`s trained on face generating stylistically-constrasting, deentity-matched image paris that human annotators and a SOTA face verification algoritm recognize as depicting the same subject.
* On measures of identity coherence and image diversity, SD-GANs perform comparably to a recent conditional GAN method; SD-GANs can also imagine new identities, while conditional GANs are liited to generating existing identities from the training data (?)

### Methods
adapt both the `DCGAN` and `BEGAN`

#### SD-GAN Formulation
