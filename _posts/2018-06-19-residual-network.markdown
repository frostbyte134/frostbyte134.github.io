---
layout: post
title:  "Deep Residual Learning for Image Recognition"
date:   2018-06-19 08:34:00 +0900
categories: deep_learning
use_math: true
tags: optimization deep_learning need_revise
---

After the Faster-RCNN, add appendix part

### Motivations (degradation)

> Is learning better networks as easy as stacking more layers?

The `vanishing gradient` problem was a major obstacle to answer this question, as it hinders us from stacking many layers (by hampering convergence from the very beginning). Advent of <a href="{{site.url}}/deep_learning/2018/06/13/batch-normalization.html" target="_blank">`batch normalization`</a> / `normalized initialization`(link??) largely addressed this problem, and deeper networks began to converge (to somewhere).

However, as deeper networks are able to start converging, a `degradation` problem has been exposed:  
\\(\Longrightarrow\\) as the network get deepers, _training error gets saturated and then degrades rapidly_,  
and adding more layers (to a suitably deep model) leads to higher training error.

Such degradation is __not caused by overfitting__ (=failures in regularization, low training err and high validation err), but caused by the __failure in optimization__(high training err and high validation err). You can see it by observing the empirical results that, even though \\(\exists\\) a non-degenerating solution (by construction) which assigns identity mappings to addition layers, adding more layer resulted in higher training error.

> The degradation problem suggests that the solvers might have difficulties in approximating identity mappings by multiple nonlinear layers.

### Deep Residual Learning

Let us consider 
* \\(\mathcal\{H\}(\textrm\{x\})\\) as an underlying mapping we want to _approximate_ (not learn, importantly. Possibly we can approximate it indirectly by learning other functions) with few stacked layers, and
* \\(\textrm\{x\}\\) as an input to the layer.

Instead of learning \\(\mathcal\{H\}(\textrm\{x\})\\) directly, we would like to 
1. _learn_ \\(\mathcal\{F\}(\textrm\{x\}):=\mathcal\{H\}(\textrm\{x\})-\textrm\{x\}\\), and 
2. add \\(\textrm\{x\}\\) to \\(\mathcal\{F\}(\textrm\{x\})\\) to recover \\(\mathcal\{H\}(\textrm\{x\})\\).  

In words, we would like to approximate \\(\mathcal\{H\}(\textrm\{x\})\\) by learning `residual` \\(\mathcal\{F\}(\textrm\{x\})\\).

Then by setting \\(\mathcal\{F\}(\textrm\{x\})=0\\) (which is easy in normalied initialization and BN setting), the network can easily approximate identity mapping. 


### Appendix (Object detection model details)


<br/><br/>
Next:  
<br/><br/>
References:  
<a href="https://arxiv.org/pdf/1512.03385.pdf" target="_blank">https://arxiv.org/pdf/1512.03385.pdf</a>  
<a href="https://icml.cc/2016/tutorials/icml2016_tutorial_deep_residual_networks_kaiminghe.pdf" target="_blank">https://icml.cc/2016/tutorials/icml2016_tutorial_deep_residual_networks_kaiminghe.pdf</a>  
