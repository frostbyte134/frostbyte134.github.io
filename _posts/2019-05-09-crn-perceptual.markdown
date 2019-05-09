---
layout: post
title:  "Photographic Image Synthesis with Cascaded Refinement Networks"
date:   2019-05-08 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning generative style_transfer perceptual crn
---

<a href="https://arxiv.org/abs/1707.09405" target="_blank">https://arxiv.org/abs/1707.09405</a>

* perceptual loss + single pass DNN (segmap -> img), no GAN
* many baselines
* Cascaded Refinement Module - feeds segmap multiple times to the module (enforce conformity of output img to seg img)
* solves __inverse segmentation__, which is an underconstrained ont-to-many inverse problem.
* Given the underconstrained nature, good loss func is required - `perceptual loss`! (=`content loss`, Gayts et al [11], =`feature matching`)  
> The basic idea is to match activations in a visual perception network that is applied to the synthesized image and separately to the reference imag.

### Abstarct
* Given a semantic label map, our approach produces an image with __photographic appearance that conforms to the input layout__ (seg map) - what makes them to say like this in the intro?
* The approach thus function as a __rendering engine__ that takes a 2dim semantic spcification of the scene and produces a corresponding photographic image.
* does not rely on adversarial training


### Intro
> A direct synthesis approach could not immediately replace modern rending engines, but would indicate that an alternative route to photorealism may be viable and could some day complement existing computer graphics tecnhiques

(What about complement, helps each other? - this was the main approach though. The author states as above for novelty)

* our model is a __convnet__, trained in a __supervised fashion__ on pairs of photographs and corresponding semantic layouts.
* In this sense, our problem is the __inverse of semantic semgentation__.
* ...scale seamlessly to high image res (1024 x 2048)

careful perceptual experiment (Amazon Mech Turk)

### Related works

Many refs saying how hard the GAN training is

`Composite loss`: regression + adversarial loss
* ex: pix2pix


### Notations
> goal: train a __parametric mapping__ \(g\\) s.t. given a __semantic layout__ \\(L\\), produces a color img \\(I\in \Re^\{m\times n\times 3\}\\) that __conforms to __ \\(L\\)

* \\(L\\): one-hot semantic layout, \\(\sum\_\{c\}L(i,j,c)=1\\)

### 3 characteristics important for synthesizing photorealistic imgs
1. Global coordination: must capture long-range dependencies (ex - left red right is on - right must also be on)  
    \\(\rightarrow\\) resolve with `multi-res refinement` (what is __refinement__?)
2. High res  
\\(\rightarrow\\) resolve with (cascade) `progressive refinement` (???)
3. Memory  
   * We conjecture that high model capacity is essential for synthesizing high-res photorealistic imgs
   * Our design is modular and the capacity of the model can be expanded as allowed by hardward (....), 105M params
   * We have consistently found that increasing model capacity increases img quality

### Architecture
`CRN`: Cascaded Refinement Network, cascade of __refinement modules__ \\(M^i\\)
* \\(M^0\\): \\(4\times 8\\) (resolution)
* Resolution is doubled between conseq modules

1. \\(M^0\\) receives segmap \\(L\\) (downsampled to \\(w\_0\times h\_0))
2. All other modules are structurally identical
3. \\(M^i\\) receives concat \\(w\_i\times h\_i\times (d\_\{i-1\}\times c)) of the __segmap__ \\(L\\) (downsampled to \\(w\_i\times h\_i\\)) and output of \\(M^\{i-1\}\\)
4. bilinear upsampe (no upconv, after reading distill(google brain))
5. Each layer is followed by 3by3 conv, layer normalization (??), `LReLU` (why LReLU?)
6. The final output is not followed by normalization or nonlinearity. Instead, a linear proj (1by1 conv) is applied to map \\(F^i\\) (\w\_i\times h\_i\times d\_i\\) to output color img \\(w\_i\times h\_i\times 3\\).
7. The num of modules: 9 (4x8 to 1024x2048)

### Training
* solves __inverse segmentation__, which is an underconstrained ont-to-many inverse problem.
* Given the underconstrained nature, good loss func is required  
ex) synthesizing black car instead of a white car, will be severly penalized
* `perceptual loss`! (=`content loss`, Gayts et al [11], =`feature matching`)
> The basic idea is to match activations in a visual perception network that is applied to the synthesized image and separately to the reference imag.
* used `VGG19` conv1_2, conv2_2, conv3_2, conv4_2, conv5_2

### Baselines, Experiments
* \\(L1\\) with same architecture (thus only the perceptual loss is replaced) was the worst
* naive GAN+Seg (penalizes the segmentation) was also not good
* pix2pix (patch gan loss + l1) was also not good
* unet was slightly better
* [50] (not tuned CRN) + perceptual loss. The only dif=architecture


Next
* 