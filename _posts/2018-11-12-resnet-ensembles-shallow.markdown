---
layout: post
title:  "Residual Networks Behave Like Ensembles of Relatively Shallow Networks"
date:   2018-11-12 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning basenet resnet
---

in stark

<a href="https://arxiv.org/abs/1605.06431" target="_blank">https://arxiv.org/abs/1605.06431</a>



### Abstract
* ... they (resnet) can be seen as a collection of many paths of differing length. (1. unraveling)
* ... (eash sub-networks) they do not strongly depend on each other, like ensembles. (2. lesion study)
* ... resnets seem to enable very deep networks by leveraging only the short paths during training  (3. short paths)
	\\(\rightarrow\\) for resent of 110 layers, most effective paths comes from 10~34.  
	> Residual networks avoid the vanishing gradient problem by introducing short paths which can carry gradient throuhout the extent of very deep network.


### Introduction

We observe that removing single layers from residual networks at test time does not noticeably affect their proformance.
* This is surprising because removing a layer from a traditional architecutre such as VGG leads to a dramatic loss in performance.

The results (of lesion study) show ensemble-like behavior in the sense that removing paths from residual networks by deleting layers or corrupting paths by reordering layers only has a modest and smooth impact on performance.

* ...paths through residual networks vary in length  
\\(\rightarrow\\) thanks to the skip connections, the network can choose which module to use.
* the distribution of path lengths follows a binomial dist. , meaning that majority of paths in a 110 resnet are only about 55 lengths.
* we show most gradient during training comes from paths that are even shorter (i.e., 10-34 deep) (by subsampling modules and measuring Euc norm of grads)

### Related Works

__Ensembling__:
* final output predictions are averaged
* generally, one key characteristic of ensembles is their smooth performance wrt the # of members.  
> In particular, the performance increase from additional ensemble members gets smaller with increasing ensemble size. Even though they are not strict ensembles, we show that residual networks behave similarly.

__Drouput__: 
* dropping out individual neurons during training leads to a network that is equivalent to averaging over an ensemble of exponentially many networks.
* Similar in spirit, stochastic depth [9] trains an ensemble of entworks (in depth) by dropping out entire layers during training. 
* In this work, we show that entire layers can be removed from plain residual networks without impacting performance, indicating that they do not strongly depend on each other.

### 1. The unraveled view of residual networks

__ there are many paths in resnet__

<img src="{{ site.url }}/nailbrainz.github.io/images/deeplearning/unravel1.png" class="center" style="width:800px"/>  
<img src="{{ site.url }}/nailbrainz.github.io/images/deeplearning/unravel2.png" class="center" style="width:800px"/> 
 
* The graph (fig1-(b)) makes clear that data flows along many paths from input to output (thanks to skip conn.)
* Each unique path can be indexed by a binary code \\(b\in\\{0,1\\}^\{n\}\\)
* It follows that resnet have \\(2^n\\) paths, with binomial dist. (centered at mean)

> In classical visual hierrachy, each layer of processing depends only on the ouptput of the previous layer. Resnet networks cannot strictly follow this pattern, b/c of their inherent structure. Each module in the resnet is fed data from the powerset of all previous layers. 

It is worthwhile to note that __ordinary feed-forward neural nets can also be "unraveled"__ using the above, at the lvl of individual neurons rather than layers (ex - Inception Resnet has 2 pathes). However, paths in resnet have varying length. Further, each path in a resnet goes through a different subset of layers. __(Traditional nets such as VGG only have one path)__

Based on the observations, 
* are the paths in resnet dependent on each other? or do they exhibit a degree of redundancy?
* If they are ind., do they behave like an ensemble?
* Do paths of varying lengths impace the net differently?


### 2. Lesion study

... we use 3 lesion studies to show that paths in residual networks do not strongly depend on each other and that they __behave like an ensemble__. pre-activation resnet. No perturbations such as stochastic depth, dropout

1. __Deleting individual layers during test time__
	removing single layers from residual networks at test time does not noticeably affect their proformance.
	* This is surprising because removing a layer from a traditional architecutre such as VGG leads to a dramatic loss in performance. (VGG has one path, so affected massively)
2. __Deleting individual layers during test time__
	performance degradation shows logarithmic+smooth increase, similar to the ensemble case
3. __Reordering modules at test time__: same as 2  
	> This result is surprising, since it suggests that residual nets dcan be reconfigured to some extent at runtime.

	
### 3. The importance of short paths in resent
<img src="{{ site.url }}/nailbrainz.github.io/images/deeplearning/unravel3.png" class="center" style="width:700px"/> 

1. __Distribution of path lengths (fig6-(a))__: binomial. many at center. For resnet-54, 95% of blocks resides in 19-35
2. __vanishing grads in resnet:__  
TO empirically investigate the effect of vanishing grads, sample subpath of length \\(k\\) by
	1. feed a batch forward through whole net
	2. During the backward pass, randomly sample \\(k\\) blocks.
	3. For \\(k\\) blocks, pass through residual block.
	4. For others (\\(n-k\\)), pass through skip conn. 
	> The result show that the grad magnitude of a path decrease exponentiallyu with the number of modules it went through in the backweard pass, Fig6-(b)
3. __effective paths are relatively shallow__: 
	1. fig6-(c): To find the total grad magnitude contributed by paths of each length, multiply the freq of each path (n binomial dist.) with the expected grad magnitude (avg?). __Surprisingly, almost all of the grad updates during training come from paths bet 5-17 modules long__. THese are the `effective paths`, even though they constitute only 0.45% of all paths through this network. Moreover, incomparison to the total length of the net, __the effective paths are relatively shallow__. 
	2. To validate this result, retrained resnet with length 23 (avg of effective paths=11.5).  
	5.96(resnet-23) vs 6.10 (resnet-54), not much diff. statistically.

### Discussion and onclusion

* It becomes apparent that the deletion of resnet modules mostly affects the long paths.
* (Perturbation methods) by selecting a diff. subset of short paths in each mini-batch, it (stochastic depth) encourages the paths to produce good results independently. (thus behaving similarly as the resnet)
* we know that plain resnets already dont' depend on individual layers.


Why resnet works well? He at al said, "We obtain these results via a simple but essential concept-going deeper". While it is true that they are ddeeper than rpevious approaches, we present a complementary explanation.
1. Our unraveled view reveals that resnets can be viewed as a collection of many paths, instead of a single ultra deep net.
2. We perform lesion studies to show that, although these paths are trained jiointly, theyh do not strongly depend on each other.
3. ... the paths through the net that contribute grad during training are shorter than expected.

> Thus, resnet do not resolve the vanishing grad problem by preserving grad flow throughout the entire depth of the net. This insight revels that depth is still an open research question. These promising observations provide a new lens through which to examine neural nets.
	





[22]
Next:  


