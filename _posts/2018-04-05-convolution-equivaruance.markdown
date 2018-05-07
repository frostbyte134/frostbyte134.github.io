---
layout: post
title:  "Convolution is equivariance to translation"
date:   2018-04-05 20:11:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---
>A function \\(f\\) is `equivariance` to an another function \\(g\\) if \\(f(g(x))=g(f(x))\\) holds.

In the case of convolution, particular form of parameter sharing causes the layers to have equivariance to translation.

Ex) Let \\(I\\) be a function that giving integer brightness at integer coordinates, 
\\(g\\) be a function that shifts x-coordinates of an image to right

i.e., \\(g(I)(x,y)=I(x-1,y).\\)

Then, \\(\textrm{conv}(g(I)) = g(\textrm{conv}(I)).\\)

When processing time-series data, or images in 2-dimensional, equivariance to translation means convolution produces a sort of "timeline" (or a "feature map", indeed), that shows when different features appears in the input.

Convolution is not naturally invariant to other transformation, such as changing in the scale or rotation. Other mechanisms are needed to handed such transformation.
<hr>
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>