---
layout: post
title:  "Learning from Synthetic Data: Addressing Domain Shift for Semantic Segmentation"
date:   2019-05-11 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning generative domain_adaptation gan
---

<a href="https://arxiv.org/abs/1711.06969" target="_blank">https://arxiv.org/abs/1711.06969</a>

### Abstract
* Visual Domain ADaptation
* ... we focus on adapting the (feature) representations learned by segmentation networks across synthetic and real domains.
* ... achieve SOTA results on two challenging scenarios of synthetic to real domain adaptation (?)
 
proposing approach approach
1. Generalizes to unseen domains
2. results in improved aligment of source and target distributions

### Intro

DCNN shows good performance thanks to the abundant data \\(\rightarrow\\) some fields annotation is expensive (Cityscapes paper - 1hour/img) \\(\rightarrow\\) synthetic data

`Domain adaptation` encompasses the class of techniques that address this domain shift problems.
> Specifically, we focus on the hard case of the problem where no labels from the target domain are available. This cls of techniques is commonly referred to as `Unsupervised Domain Adaptation`

* The method we present here falls in the category of __aligning domains using an adversarial framework__.
* Unlike [14] (FCNs in the wild) where \\(D\\) operates directly n the feature space, we _project the features to the image space using a \\(G\\) and the \\(D\\) operates onthis projected image space._, which gives substantial MIOU improvement (Table 4)

> We propose a technique that employs generative models to align the source and target distributions in the feature space.

1. We first project the intermediate feature representations obtained using a DCNN to the image space by training a reconstruction module(=\\(G\\)) using a combination of \\(L\_1\\) and adversarial loss
2. We then impose the domain alignment constraint by forcing the network to learn features such that the source features produce target-like imgs when passed to the reconstruction module, and vice versa

### Related Works
`Domain Adatpation`
1. Early
   * Feature reweighting [5], constructing intermediate reprs using manifolds
   * measure domain discrepancy using `MMD` (Maximum Mean Discrepancy), minimize it [21, 22]
2. Adversarial (classification)
   * [7] <a href="{{site.url}}/deep_learning/2019/01/18/gdl.html" target="_blank">Gradient Reversial Layer</a> - feature space alignment
   * `PixelDA` [2], `CoGAN` [19] - operate in the pixel space
3. FCNs in the wild
   * domain adaptation, segmentation, adversarial
   * 2-stages
4. Curriculum domain adaptation
   * curriculum-style learning approach
     * easy task of estimating blobal label distributions over imgs and local distribution over landmark superpixel is learnt first
     * the segnet is then trained so that the target label distribution follow these inferred label properties

> One possible direction to address the domain adaptation problem is to __employ style transfer__ or __dross-domain mapping network__ to stylize the source domain images as target and __train the segmentation models in this stylized space__.

### Method

* \\(X : M\times N\times C\\) - arbitrary input image
* \\(Y : M\times N\\) - label map
* \\(\hat\{Y\} : M\times N\times N\_c\\) - output of a CNN  
\\(\hat\{Y\}[i,j] : \\) class prob. distribution
* \\(X^S,\\ X^T\\) - source, target data generating distribution (hidden)

#### Networks
<img src="{{site.url}}/images/deeplearning/gan/synth_1.png" width="700">
* Basenet \\(F,C\\): similar structure to `VGG16`, split into 2 parts
	1. the embedding, denoted by \\(F\\)
	2. pixel-wise classifier \\(C\\), which produces the label map same size as the input of \\(F\\)
* \\(G\\): takes as input the learned embedding (output of \\(F\\)) and reconstruct RGB img
* \\(D\\): performs two different tasks (!?!)
   1. classfies the input as real or fake in a domain consistent manner (?)
   2. pixel-wise label task, similar to the \\(C\\) network (what is the adv of this duplicated operations?)  


#### Procedures  
<img src="{{site.url}}/images/deeplearning/gan/synth_2.png" width="1200">
1. Given a {source img, source label} pair \\(\\{X^s,Y^s\\}\\)  
   1. extract a feature repr using \\(F\\) network
   2. classifier \\(C\\) takes the embedding \\(F(X^s)\\) as input, produces an img-sized label map \\(\hat\{Y\}^S\\)
   3. The generator \\(G\\) reconstructs the source input \\(X^s\\) conditioned on the embedding \\(F(X^s)\\) (?)  
   > Following recent successful works on img generation, we do not explicitly concatenate the generator input with a random noise vector but instead __use dropout__ layers throughout the \\(G\\) network
   4. \\(D\\) performs 2 tasks
      1. Distinguishing the real source input / generated source img as source-real/source-fake
      2. produce a pixel-wise label map of the generated source img
2. Given a target input \\(X^t\\),
   1. \\(G\\) takes the target embedding from \\(F\\) as input, reconstruct the targe timg
   2. \\(D\\) performs 1 task : distinguish target-real/target-fake
   3. \\(C\\) is not active, since there is no target label \\(Y^t\\)
3. In the test time, \\(F\\) and \\(C\\) is only used  
(How to validate the Usage of \\(C\\), which is never trained to segment target img?)

#### Iterative Optimization
In addition to the losses in `Table 1`, following losses are used
1. \\(L\_\{seg\}, L\_\{aux\}\\) : pixelwise cross-entropy loss, used in standard seg
2. \\(L\_\{rec\}\\) : \\(L1\\) img reconstruction loss

Each iter works on a randomly sampled triplet \\(X^s,Y^s,X^t\\) (refer to the `fig2`)
1. \\(D\\)-update  
   1. For source inputs, \\(D\\) is updated using a combination of within-domain adversarial loss \\(L\_\{adv,D\}^s\\) and auxiliary classificaiton loss \\(L\_\{aux\}^s\\)
   2. For target inputs, \\(D\\) is updated only on adversarial loss \\(L\_\{adv,D\}^t\\)
   \\[L\_D=L\_\{adv,D\}^s+L\_\{adv,D\}^t+L\_\{aux\}^s\\]
2. \\(G\\)-update  
   \\(G\\) need to fool \\(D\\) (\\(L\_\{adv,G\}^s + L\_\{adv,G\}^t\\)) while reconstructing realstic image ("ensure image fidelity") (\\(L\_\{rec\}^s + L\_\{rec\}^t\\))
3. \\(F\\)-update  
      > __The update to the \\(F\\) network is the critical aspect of our framework where the notation of domain shift is captured__

      \\[L\_F=L\_\{seg\}^s+\alpha L\_\{aux\}^s+\beta(L\_\{adv,F\}^s+L\_\{adv,F\}^t)\\]
      * \\(L\_\{seg\}^s+\alpha L\_\{aux\}^s\\) : \\(F\\) must extract features helpful in solving segmentation of source, with \\(C,D\\)
      * \\(F\\) is never updated with within-domain loss (real-fake loss of src/target)
      * \\(L\_\{adv,F\}^s+L\_\{adv,F\}^t\\) : core part (cross gradient???)  
            1. For source embedding \\(F(X^s)\\), we use gradient from \\(D\\) corresponding to classifying those embeddings as from target domain  
            (We insert \\(F(X^s)\\) into \\(D\\), setting their label as the target image) (remember that the \\(D\\) has 4 labels)  
            2. For target embedding, we to the convserse  
            > The iterative updates here can be considered as a minmax game between the \\(F\\) and \\(G,D\\) (similar to the minmax of \\(G-D\\), except in this case, the competition is between classifying the generated image as from source/target domains instead of them being real/fake)
  

#### Motivating design choice of D
* we extend `patch D` (of pix2pix), where __each pixel in the output map indicates real/fake__ prob across source and target domains hence resulting in 4 classes per pixel: _src-real, src-fake, tgt-real, tgt-fake_
* Following the Aux classifier of Onena et al, we employed an aux-pixel wise labeling loss to \\(D\\)


### Experiments
* used `SYNTHIA-RAND-CITYSCAPES` (9400 imgs), `GTA-5` (24966) to `CITYSCAPES`
* comparison with FCNs in the wild (`FCN`) and Curriculum Domain Adaptation (`CDA`). Following their approace, designated 500 CITYSCAPES val set as the test set.

#### Details
* 10,000 iterations
* imgs resized to 1025 x 512 -> upsample 2 for calculating MIOU
* ADAM (bs=1, LR=10^-5 for \\(F,C\\) and 2*10-4 for \\(G,D\\)).
* publicly available codes


### Left things
- Ablation study, comparison, feature space k-NN study (domain discrepancy in feature space, using cosine distance)


<br/><br/>
Next
* Odena et al : aux classifier on \\(D\\) 