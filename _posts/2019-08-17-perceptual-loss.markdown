---
layout: post
title:  "Reconstructing Bag of tricks + Stylized imagenet"
date:   2019-08-16 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning pytorch
---

The purpose of this document is, recording the reconstruction procedure of 

1. <a href="https://arxiv.org/abs/1812.01187" target="_blank">paper</a>, <a href="{{site.url}}/deep_learning/2019/06/01/bag-of-tricks-classification.html" target="_blank">review</a>,
2. <a href="https://arxiv.org/abs/1811.12231" target="_blank">paper</a>, <a href="https://nailbrainz.github.io/deep_learning/2019/05/22/imgnet-texture-biased.html" target="_blank">review</a>

to use the `SIN` (Stylized Imagnet Model) as a perceptual loss calculator in GAN training (pix2pix setup). 



> Git repo: <a href="https://github.com/nailbrainz/resnet50_stylized" target="_blank">https://github.com/nailbrainz/resnet50_stylized</a>

### Bag of Tricks

1. Baseline  
<img src="{{site.url}}/images/deeplearning/recon/tricks_baseline.png" width="500">
2. Model tweks + training heuristics  
<img src="{{site.url}}/images/deeplearning/recon/exp1.png" width="900">
3. distillation, mixup, label smoothing, cosine lr  
<img src="{{site.url}}/images/deeplearning/recon/exp2.png" width="500">

#### Done
1. <a href="{{site.url}}/deep_learning/2018/08/28/identity-mappings-in-resid-nets.html" target="_blank">pre-activation</a>  
__Note that, pre-activation was not mentioned in the paper__
2. mixup
3. LR warmup
4. zero \\(\gamma\\)
5. no-bias decay
6. FP16
7. Cosine LR

#### TODO
1. Implementing label smoothing  
- not well supported in Pytorch
2. distillation


#### Experiments

__Defaults__: FP16, LR warmup, Zero \\(\gamma\\), no bias decay

Num | Date | top1, top5 | commit | preact | mixup | lr | epochs | time
---- | -------- | ---- | ---- | ---- | ---- | ---- | ---- | ----
1 | 2019-08-16 | in progress | <a href="https://github.com/nailbrainz/resnet50_stylized/commit/f8ac759dbf01c489b3fb1a698f1f7838ca94b33d" target="_blank">link</a> | O | X | cosine | 120 | 3.5days

Will update exps done in other places soon

### Stylized Imagenet

1. Cross-training and inference with `SIN`, `IN`  
<img src="{{site.url}}/images/deeplearning/recon/style1.png" width="900">
2. Comparison  
<img src="{{site.url}}/images/deeplearning/recon/style2.png" width="900">
3. Model used `ResNet-50` of `torchvision.models.resnet50`
4. Training procedure
`SIN`  
* `SIN` for 60 epochs with `torch.optim.SGD` using a momentum term of 0.9, weight decay (1e-4) and a learning rate of 0.1 which was multiplied by a factor of 0.1 after 20 and 40 epochs of training, batch size of 256. 
* This SIN-trained model is the same model that is reported in Figures 5 and 6 as well as in Table 2. In the latter, this corresponds to the second row (training performed on SIN, no fine-tuning on ImageNet). 
`SIN+IN`  
* For the model reported in the third row (`SIN+IN`), training was jointly performed on SIN and on IN. This means that both training data sets were treated as one big data set (exactly twice the size of the IN training data set), on which training was performed for 45 epochs with identical hyperparameters as described above, except that the initial learning rate of 0.1 was multiplied by 0.1 after 15 and 30 epochs. The weights of this model were then used to initialise the model reported
in the fourth row of Table 2, which was fine-tuned for 60 epochs on ImageNet (identical hyperparameters except that the initial learning rate of 0.01 was multiplied by 0.1 after 30 epochs). 


#### Done
1. Generating `SIN` dataset
2. Few experiments on `IN` alone (TODO: will upload results)

#### TODO
1. Implementing dataloader which could perform joint `IN+SIN` training

#### Experiments
Will update exps done in other places soon
