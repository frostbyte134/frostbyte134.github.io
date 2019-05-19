---
layout: post
title:  "(CBN) A Learned Representation for Artistic Style"
date:   2019-05-18 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning generative conditional_gan gan
---

<a href="https://arxiv.org/abs/1610.07629" target="_blank">https://arxiv.org/abs/1610.07629</a>

### Abstract

* parsimoniously: excessively unwilling to spend
* ... we investigate the construction of a single, scalable deep network that can parsimoniously capture the artistic style of a diversity of paintings.
* We demonstrate that such network __generalizes across a diversity of artistic styles byreducing a painting to a point in an embedding space__.
* this model permits a user to explore new painitng sytles by arbitrarily combining thestyles learned from individual paintings.

### Intro
* old style transfer literature (separation of `style` and `content` without DNN)


### Style transfer with Deep Networks

* Style transfer can be defined as finding a pastiche img \\(p\\) whose content is similar to that of a content img \\(c\\), but whose style is similar to that of a style img \\(s\\)
* This objective is by nature vaguely defined, b/c __similarity in content and style are themselves vaguely defined__


(Previous works of) The neural algorithm of artistic style proposes the following definitions:
* two imgs are __similar in content__ if their high-lvl features as extracted by a trained classifier are clsoed in Euclidean distance
* two imgs are __similar in style__ if their low-lvl features as extracted by a trained classifier share ths same statistics or, more concretely, if the difference between the features' `Gram matrices` has a small Frobenious norm

A style-transfer network is trained to minimize feature loss + gram matrces matching loss

### N-style feedforward style transfer networks
> Our work stems from the intuition that many styles probably share some degree of computation, and that this sharing is thrown away by training \\(N\\) network from scratch when building an \\(N\\) styles style transfer system.

(ex - many impressionist paintings share similar paint strokes but differ in the color pallete being used)

* We propose to train a single conditional style transfer network \\(T(c,s)\\) for \\(N\\) styles
* how the conditioning should be done?
* we found a suprising fact bout the __role of normalization in style transfer networks__: to model astyle, iti s sufficient to specialize scaling and shifting params after normalization toeach specific style.
* In other words, all conv weights of astyle transfer network can be shared across many styles, and itis sufficient totune params for anaffine transformation after normalization for each style
* We call this `conditional instance normalization`

For details (in case you forget it), refer to the BigGAN pytorch implementation

### Methodology
Same arch as Johnson (2016), except
* zero padding -> mirror padding 
* transposed conv -> NN upsample + same conv

which in checkboard distill, said to removes chekkerboard pattern

### Conclusion
> That said, in the case ofart stylization when posed asafeedforward network, itcould be that the specific network archi (especially without the CBN) is unable to take full advantage of its capacity

* ... we domonstrated that conditional instance normalization constitutes a simple, efficient and scalabel modification of style tansfer networks that allows them to model muptiple styles at the same time.

<br/><br/>
Next
