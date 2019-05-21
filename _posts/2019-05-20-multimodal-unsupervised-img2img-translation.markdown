---
layout: post
title:  "Multimodal Unsupervised Image-to-Image Translation"
date:   2019-05-20 09:12:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning generative img2img style_transfer
---

<a href="https://arxiv.org/abs/1804.04732" target="_blank">https://arxiv.org/abs/1804.04732</a>

* assumes that `latent space` of imgs can be decomposed into a `content space` and a `style space`
  * `content code`: underlying spatial structure, domain-invariant, encodes the information that should be preserved during tranlation
  * `style code`: rendering of the structure, captures domain-specific properties, represent remaining variations that are not contained in the input iamge

* used `GAN`s to __align the distribution of translated images with real images__
* we assume that the `latent space` of imgs can be decomposed into a `content space` and a `style space`
* we futher assume that _the imgs in different domains share a common content space but not the style space_

* style transfer - `example-guided style transfer` / `collection based style transfer`. img2img methods performs latter better (CycleGAN), but the proposing method performs both well

* `latent reconstruction loss` during domain translation

We note that, although the prior distribution is unimodal, the output image distribution can be multimodal thanks to the nonlinearity of the decoder. \\(G\\)  
\\(\rightarrow\\) : Multimodality depends on \\(G\\), which already shows severe mode collapse

Cycle-consistency
* img recon loss only at in-domain
* says that cross-domain reconstruction loss is __too strong__.   Instead `style-augmented cycle consistency`,  weaker form of cycle consistency is applied
    * From the img \\(x\_i\\), the encoder extracts style \\(s\_i\\) and the content \\(c\_i\\). The reconstruction is done only with content, while fixing the style.
    \\[L\_\{cc\}^\{x\_1\}=E\_\{x\_1\sim p(x\_1), s\_2\sim q(s\_2)\} \|\| G\_1(E\_2^c(G\_2(E\_1^c(x\_1),s\_2)),E\_1^s(x\_1))-x\_1 \|\|\_1\\] (Notice that \\(s\_2)\\) is fixed

`domain-invariant VGG loss`
* unsupervised - no pair - no conventional VGG loss!  
\\(\rightarrow\\) `domain-invariant VGG loss`, by performing instance normalzation on VGG features, and used it as the reference (...).
* it is said that (in appendix C), this accelerates the training in img larger than 512x512

`conditional inception score`
### Abstract

Unsupervised img2img translation
* have to learn conditional distribution (givn some image)
    > while this conditional distribution is inherently multimodal (one-to-many), existing approaches make an overly simplified assumption, modeling it as a deterministric 1to1 mapping.  

    \\(\rightarrow\\) fail to generate diverse output img

... we propose Multimodal Unsupervised Image-to-image Translation (MUNIT) framework

We assume that the image representation can be decomposed into a
* `content code` that is domain-invariant, and a 
* `style code` that captures domain-specific properties

... allows users to control the style of translation outputs by providing an example style image

### Intro

* (unsupervised img2img = one2many problem, so deterministic / unimodal [15] approach fails)
* Even if the model is made stochastic by injecting noise, the network usually learns to ignre it (pix2pix)

Multimodeal UNsupervised Img2img Translation (`MUNIT`) framework/problem  
<img src="{{site.url}}/images/deeplearning/gan/munit.png" width="1400">  
* we assume that the `latent space` of imgs can be decomposed into a `content space` and a `style space`
  * `content code` encodes the information that should be preserved during tranlation
  * `style code` represent remaining variations that are not contained in the input iamge

* we futher assume that _the imgs in different domains share a common content space but not the style space_
* to translate an img to the target domain, we recombine its content code with a random style code in the target style space (fig1(b))
* `content code` + sampled `style code` - various output imgs
* __user_control__ : instead of sampling `style code`, user may select target img - extract `style code` from it - add with `content code` 

### Related works
* In this works, we employ `GAN`s to __align the distribution of translated images with real images__ in the target domain.
* __This problem (Unsupervised img2img translation) is inherently ill-posed and requires additional constraints__
    * Some works enforce the translation to preserve certain properties of the source domain data, such as pixel values[21], pixel gradients [22], semantic feature [10], class labels [22], or pairwise sample distance [16]
    * cycle consistencies [7, 8, 9]

`Lack of diversity`
* `BycicleGAN` model continuous and multimodal distributions, but requries pair supervision.

`Style transfer`
* `example-guided style transfer`: the target style comes from a single example, classifical style transver
* `collection style transfer`: in which the target style is defined by a collection of imgs, img2img translation methods have been demonstrated to perform well in the latter (CycleGAN)

`Disentangled representations learning`
* This work is inspired by `InfoGAN` which works on `disentangled representation learning without supervision.
* although it is vague, we refer to
    * `content` : underlying spatial structure
    * `style` : rendering of the structure

    In this work, we have 2 domains that share the same content distribution but have different style distribution.


### MUINIT

#### Assumptions
Let
* \\(x\_1\in X\_1,\\ x\_2\in X\_2\\) be two images drawn from image domains \\(X\_1,X\_2\\).
* __goal__ is to estimate \\(P\_\{X\_2\|X\_1\},\\ P\_\{X\_1\|X\_2\}\\) with _learned img2img translation model_ \\(P\_\{X\_\{1\rightarrow 2\}\|X\_1\},\\ P\_\{X\_\{2\rightarrow 1\}\|X\_2\}\\)   \\(P\_\{X\_2\|X\_1\},\\ P\_\{X\_1\|X\_2\}\\) are complex, multimodal distributions which a deterministic tranlation model does not work well.
* To tackle above, we make a `partially shared latent space` assumption
    * assume that each img \\(x\_i\in X\_i\\) is generated from a
        * `content latent code` \\(c\in C\\) that is __shared__ by both domains, and a 
        * `style latent code` \\(s\_i \in S\_i\\) that is specific to the individual domain

In this model, a pair of images \\((x\_1,x\_2)\\) which shared contents but diffferent in style, from the joint distribution (in theory), is __generated separately__ by  
\\[ x\_1=G\_1^\*(c,s\_1) \\]
\\[ x\_2=G\_2^\*(c,s\_2) \\]
where \\(c, s\_1, s\_2\\) (content, style1, style2) is generated from some prior distribution, and \\(G\_1^\*, G\_2^\*\\) is the \\(G\\) (__decoder__) we have to train.

We further that each \\(G\_i^\*\\)s are deterministic, and have their inverse __encoder__ \\(E\_i^\*=(G\_i^\*)^\{-1\}\\)
\\[(c,s\_i) = E\_i^\*(x\_i)\\]
(__we can disentangle content / style from this encoder__)

Note that even though the encoders and decoders are deterministic, \\(P\_\{X\_\{i\rightarrow j\} \| X\_i\}\\) is a continuous distribution, due to the dependency of \\(s\_2\\).

#### Model
<img src="{{site.url}}/images/deeplearning/gan/munit2.png" width="1200">
1. Within-domain training
    * trains encoder (which extracts `content code` and `style code`), and the decoder \\(G\\)
2. Cross-domain translation
    EX) \\(x\_1\in X\_1 \mapsto X\_2\\)
    1. Extract content code \\(c\_1\\) from \\(E\_1^*(x\_1)\\)
    2. Randomly draw a style code \\(s\\) from the __style prior distribution__ \\(\mathcal\{N\}(0, I)\\)
    3. Use \\(G\_2^\*\\) to produce the final output img \\(x\_\{1\mapsto 2\}=G\_2^\*(c\_1,s)\\).

    > We note that, although the prior distribution is unimodal, the output image distribution can be multimodal thanks to the nonlinearity of the decoder. \\(G\\)


__loss function__
* `bidirectional reconstruction loss`: ensures the encoders and decoders are inverses
    * `Image recon loss`: image-latent-image  
    active during within-domain reconstrution
    \\[L\_\{recon\}^\{x\_1\}=E\_\{x\_1\sim p(x\_1)\}\|\| G\_1(E^c(x\_1), E\_1^s(x\_1)) - x\_1 \|\|\\] \\(L\_\{recon\}^\{x\_1\}\\) is defined similarly
    * `Latent reconstruction loss`: latent-image-latent
    active during cross-domain translation
    \\[L\_\{recon\}^\{c\_1\}=E\_\{c\_1\sim p(c\_1),\\ s\_2\sim q(s\_2) \}\|\| E\_2^c(G\_2(c\_1,s\_2))) - c\_1 \|\|\\] 
    \\[L\_\{recon\}^\{s\_2\}=E\_\{c\_1\sim p(c\_1),\\ s\_2\sim q(s\_2) \}\|\| E\_2^s(G\_2(c\_1,s\_2))) - s\_1 \|\|\\]
    \\(L\_\{recon\}^\{c\_2\}, L\_\{recon\}^\{s\_1\}\\) is defined similarly

    The style reconstruction loss \\(L\_\{recon\}^\{s\_i\}\\) is _reminiscent_ of the `latent reconstruction loss` used in `InfoGAN`, `BicycleGAN`
    
* `adversarial loss`: matches the distribution of translated images to the image distribution in the target domain

### Theoretical(optimality) Analysis 

1. Latent distribution matching  
Notice that,  
    * the distribution of styles obtained by the disentangling encoder \\(s\_i=E\_i^s(x\_i)\\) and 
    * the distribution of style \\(s\_i\\) used in translation period \\(\mathcal\{N\}\\) 
    
    __can be different.__  
    proposing method does not have explicit constraint enforcing such property. (15, 40 used KDL loss, 17, 42 used adversarial loss) They only shows that at optimality, this property holds (proposition 2)
2. Joint-distribution matching  
    The model learns two conditional distribution
    \\[P(X\_\{1\rightarrow 2\} \| X\_1), P(X\_\{2\rightarrow 1\} \| X\_2)\\]
    which implicitly gives two approximation of \\(P(X\_1, X\_2)\\) as
    \\[P(X\_\{1\rightarrow 2\}, X\_1), P(X\_\{2\rightarrow 1\}, X\_2)\\]
    which are matched at optimizality (proposition 3)
3. Style-augmented cycle consistency  
    Notice that in the figure 2, we __do not have cycle consistency between different domains.__ The paper says __this is too strong__ (for a unsupervised img2img problem), which degenerates the entire model to a deterministic function (Appendix A). Instead, weaker `style-augmented cycle consistency` holds at optimality
    * It implies that, if we translate an img to the target domain and translate it back using the original style, 
    * From the img \\(x\_i\\), the encoder extracts style \\(s\_i\\) and the content \\(c\_i\\). The reconstruction is done only with content, while fixing the style.
    \\[L\_\{cc\}^\{x\_1\}=E\_\{x\_1\sim p(x\_1), s\_2\sim q(s\_2)\} \|\| G\_1(E\_2^c(G\_2(E\_1^c(x\_1),s\_2)),E\_1^s(x\_1))-x\_1 \|\|\_1\\] (Notice that \\(s\_2)\\) is fixed
    * It is enforced implicitly by the proposing `bidirectional reconstruction loss`
    
### Experiment
1. Content encoder
    * used strided conv, residual blocks, `Instance normalization`
2.  Style encoder
    * used strided conv, gap, fc. no Instance normalziation
3. Decoder
    * resid blocks, upsampling, convs
    * `AdaIN`, while the affine params are produced by the learned network, as in [54]
4. perceptual loss
    * unsupervised - no conventional perceptual loss!
    * instead, performed instance normalization on VGG features (no affine transforms), which make the VGG features more domain invariant - use them as the reference!
    This `domain-invariant VGG loss` accelerate the training on high-res (512x512) - used in such datasets  (experiments in the paper)  

### Conclusion
* surpass the unsupervised ones (`CycleGAN` series), and match the supervised ones (`BicycleGAN`)

<br/><br/>
Next
* [10] : Unsupervised cross-domain image generation, ICLR, 2017
* [15] : Unsupervised image-to-image translation networks, NIPS, 2017
* [16] : One-sided unsupervised domain mapping, NIPS, 2017
* [21] : Learning from simulated and unsupervised images through adversarial training, CVPR, 2017
* [22] : Unsupervised pixel-level domain adaption with generative adversarial networks, CVPR, 2017
