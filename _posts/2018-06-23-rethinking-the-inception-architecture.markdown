---
layout: post
title:  "Rethinking the Inception Architecture for Computer Vision"
date:   2018-06-23 08:34:00 +0900
categories: deep_learning
use_math: true
tags: optimization deep_learning incepction_net 1by1_conv need_revise
---
CVPR 2016, <a href="https://arxiv.org/abs/1512.00567" target="_blank">https://arxiv.org/abs/1512.00567</a>

Need to add link in 7

### 1. Abstract

> ...explorer ways to scale up networks in ways that aim at utilizing the added computation as efficienlty as possible by `suitable factorized convolutions` and `aggressive regularization`.

* Suitable factorization: \\((5\times5)\\) conv \\(\quad\longrightarrow\quad\\) \\((3\times3)\\) conv \\(\times\\) \\((3\times3)\\) conv (or even, `asymmetric factorization`)
* aggressive regularization: Label smoothing regularization (LSR). regularizes logits, which has infinite domains (by assigning \\(z_i\rightarrow\infty\\), we obtain \\(\log z_i\approx1\\)) (__overconfidence__) with mixed distribution.  

### 2. General Design Principle
Few design principles based on large-scale experimentation (empirical). Principles below are speculative.

{:.acounter}
1. __Avoid representational bottlenects, especially early in the network.__ One should avoid bottlenecks with extreme compression. In general the representation size shloud gently decrease...
2. Higher dimensional representations are easier to process locally within a network. __Increasing the activation per tile in a convolutional network allows for more disentangled features.__ The resulting network will train faster.
3. Spatial aggregation (so called spread out conv, generally larger than \\(3\times3\\)) can be done over lower dimensional embeddings (\\(1\times1\\) conv) without much or any loss in representational power.  
...hypothesized that the reason is the strong correlation between adjacent unit results in much less loss of information during dimension reduction if the outputs are used in a spatial aggregation context. Given that these signals should be easily compressible, the dimension reduction (with \\(1\times1\\) conv) even promotes faster learning.
4. Balance the width (featur map size) and depth(filter size) of the network. Increasing both the width and the depth of the network can contribute to higher quality networks (what about opt difficulty?). However, __the optimal improvement for a constant amount of computation can be reached if both are increased in parallel.__
{:.acounter}


### 3. Factorizing Convolutions with Large Filter Size
> Much of the original gains of the <a href="https://www.cs.unc.edu/~wliu/papers/GoogLeNet.pdf" target="_blank">GoogLeNet</a> arises from a very generous use of dimension reduction. This can be viewed as a special case of factorizing convolutions in a computationally efficient manner.

In a vision network (where <a href="{{site.url}}/deep_learning/2018/03/29/cnn.html#equivariance" target="_blank">`translation invariance`</a> exists), it is expected that __outputs of nearby activations are highly correlated__.  
\\(\leadsto\\) the depth(filter size) of activation can be reduced before aggregation, and that this should result in similarly expressive local representation.

In fully conv nets, each weight (of conv filter) corresponds to one multiplication per activation. Therefore,  
reduced # of weights with suitable factorization  
\\(\leadsto\\) disentangled params  
\\(\leadsto\\) easy learning.
{:.deccounter}
1. Factorization into smaller convolutions  
...by exploiting <a href="{{site.url}}/deep_learning/2018/03/29/cnn.html#equivariance" target="_blank">`translation invariance`</a>, it seems natural to replace the fully connected component by a two layer conv architecture:
\\[(5\times5) \textrm\{ conv \} \quad\longrightarrow\quad(3\times3)\textrm\{ conv \} \times (3\times3)\textrm\{ conv \}\\]
Above example gives, for a single dimension, \\[\frac\{\textrm\{filter of (3by3)\}\times2\times\textrm\{#filters\}\}\{\textrm\{filter of (5by5)\}\times\textrm\{#filters\}\}=\frac\{9\times2\}\{25\}\quad\rightarrow\quad 28\% \textrm\{ saving\}\\]
It is reported in the paper that, using linear activation (between factorized conv?) was always inferior to using ReLUs in all stages (empirically).
2. Spatial factorization into Asymmetric Convolutions  
\\[(n\times n) \textrm\{ conv \} \quad\longrightarrow\quad(1\times n)\textrm\{ conv \} \times (n\times1)\\]
...we have found that employing this factorization does not work well on early layers, but it gives very good results on __medium grid-sizes__ (on \\(m\times m\\) feature maps, where \\(m\\) ranges __between 12 and 20__).
{:.deccounter}


### 4. Utility of Auxiliary Classifiers
\\(\rightarrow\\) aux heads of GoogLeNet. Skipped since it doesnt look like a standard nowadays.
> ...we argue that the auxiliary clasifiers act as regularizers.


### 5. Efficient Grid Size Reduction
> In order to avoid a representational bottleneck, before applying maximum or avg pooling, the activation dimension of the network filters is expanded

Example TODO:
\\[d\times d\textrm\{ grid with \}k\textrm\{ filters \}\quad\longrightarrow\quad \frac\{d\}\{2\}\times \frac\{d\}\{2\}\textrm\{ grid with \}2k\textrm\{ filters \}\\]

1. (left of fig9): conv with stride 2  
\\(\leadsto\\) creates a representational bottlenect, as the `overall dimensionality of the representation` drops to \\((\frac\{d\}\{2\})^2k\\)
2. (right of fig9): expand dimension with 1by1 conv, then apply conv with stride 2
\\(\leadsto\\) \\((d\times d \times k) \times 2k\\) computation bottlenect
3. (fig10): Parallel stride 2 block.

<img src="{{ site.url }}/nailbrainz.github.io/images/deeplearning/inception/expansion.jpg" class="center"/>  

__No explanation/intuition in the paper why (the bizarre asymmetric structure of) 3 works. No explanation either why they decided to use it.__ Maybe inspired by the asymmetry of 3-2.


### 6. Inception-V2
refer to the paper.  
Note that, in the lower part normal convs are used, and then inception modules are inserted in the middle. 


### 7. Model Reularization via Label Smoothing
1. For discrete RV, minimizing cross entropy with logits = Maximum likelyhood est of softmax (link!!!)
2. Maximum of MLE is achieved by \\(z_k\rightarrow\infty\\) with correct labels, and 0 otherwise.  
However it may result in overfitting, and encourges the differences between the largest logit and all others to become large (reduce the model's adaptability)  
\\(\Longrightarrow\\) by mixing with uniform distribution, encourge the model to __be less confident__.


### 9. Performance of Lower Resolution Input
In the contexts like detection problem, the network must process lower dimensional inputs (ex - 79\\(\times\\)79).
> The comon wisdom is that models employing higher resolution receptive fields  tend to result in significantly improved recognition performance. However it is important to __distinguish between the effect of the increased resolution of the  first layer receptive field and the effects of larger model capacitance and computations__. 

They conducted 3 experiments, varying only the input receptive size (and immediate pooling). The result was somewhat similar.

|Receptive Field Size |Top-1 Accuracy (single frame)|
|---------------------|-----------------------------|
|\\(79\times79\\)     |75.2%                        |
|\\(151\times151\\)   |75.2%                        |
|\\(299\times299\\)   |76.6%                        |


<br/><br/>
Next:  
<br/><br/>
References:  
<a href="https://arxiv.org/abs/1512.00567" target="_blank">https://arxiv.org/abs/1512.00567</a>