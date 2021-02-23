---
layout: post
title:  "Inception-v4, Inception-ResNet and the Impact of Residual Connections on Learning"
date:   2018-06-23 16:34:00 +0900
categories: deep_learning
use_math: true
tags: optimization deep_learning resnet residual inception need_revise
---
AAAI 2017, <a href="https://arxiv.org/abs/1602.07261" target="_blank">https://arxiv.org/abs/1602.07261</a>


### Summary
* Residual connection do help at least in training speed (fewer iterations)
* __Scalar scaling of residual__ (0.2~0.3) helps in stabilizing the network (Unstablility was also reported in the <a href="{{site.url}}/deep_learning/2018/06/19/residual-network.html" target="_blank">Residaul paper</a>)
* Excessive filters (over 1000) \\(\Longrightarrow\\) network "died" early in the training  
\\(\Longrightarrow\\) meaning that the last layer before the avg pooling started to produce only zeros after a few tens of thousands of iterations.

> Also our latest models (with and without residual connections) outperform all our previous networks, just by the virtue of the increased model size.


### 1. Abstract
> ...empirical evidence that training with residual connections accelerates the training of inception networks significntly.

> ...some evidence of residual Inception networks outperforming similarly expensive Inception networks without residual connections by a thin margin.

In this work we study the __combination of the two most recent ideas:__ <a href="{{site.url}}/deep_learning/2018/06/19/residual-network.html" target="_blank">`Residual connections` [1]</a> and the latest revised version of the <a href="{{site.url}}/deep_learning/2018/06/23/rethinking-the-inception-architecture.html" target="_blank">`Inception-v3` architecture [2]</a>.

1. In [5], it is argued that residual connections are of inherent importance for training very deep archi.  
\\(\Longrightarrow\\) it is natural to add residual connection in the filter concat stage of the Inception acrhi.  
_This would allow Inception to reap all the benefits of the residual approach while retaining its computational efficiency_.
2. Introduce `Inception-v4`, which has more simplified archi. and more inception modules.


### Related work
... The authors (of [1]) argued that _residual connections are inherently necessary for training very deep convolutional model._ In the experimental section we demonstrate (in a bit ad-hoc manner) that it is not very difficult to train competitive very deep networks without utilizing residual connections. __However the use of residual connections seems to imporve the training speed greatly, which is alone a great argument for their use__.
  
History of Inception nets are,
1. Inception-v1: GoogLeNet [3]
2. Inception-v2: added <a href="{{site.url}}/deep_learning/2018/06/13/batch-normalization.html" target="_blank">batch normalization</a>
3. Inception-v3: added asym factorization and regularization [1]
4. Inception-v4: Introduced in this paper. has more inception module.
5. Inception-ResNet
 

### Architectural Choices

#### Pure Inception Blocks
1. Previously, each inception block was pretrained independently due to the memory constraints.  
Now thanks to the Tensorflow(JIT backproP?) they didn't have to.
2. Made uniform choices for the Inception blocks for each grid size.

#### Residual Inception blocks
1. To compensate the dimensionality reduction induced by the induction block, \\(1\times1\\) filter-expansion is done b4 the residual conn.
2. Used BN onlky on top of the traditional layers(???), but not on top of the summations (residual conn???).

#### Scalaing of the Residuals
Excessive filters (over 1000) \\(\Longrightarrow\\) network "died" early in the training  
\\(\Longrightarrow\\) __last layer before the avg pooling started to produce only zeros after a few tens of thousands of iterations.__
 
 
### Network architecture
Refer to the <a href="https://arxiv.org/abs/1602.07261" target="_blank">paper</a>.

<br/><br/>
Next:  
<br/><br/>
References:  
<a href="https://arxiv.org/abs/1602.07261" target="_blank">https://arxiv.org/abs/1602.07261</a>