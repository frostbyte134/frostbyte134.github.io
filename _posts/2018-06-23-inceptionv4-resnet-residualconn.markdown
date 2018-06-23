---
layout: post
title:  "Inception-v4, Inception-ResNet and the Impact of Residual Connections on Learning"
date:   2018-06-23 16:34:00 +0900
categories: deep_learning
use_math: true
tags: optimization deep_learning resnet residual inception need_revise
---
AAAI 2017, <a href="https://arxiv.org/abs/1602.07261" target="_blank">https://arxiv.org/abs/1602.07261</a>


### 1. Abstract
> ...empirical evidence that training with residual connections accelerates the training of inception networks significntly.

> ...some evidence of residual Inception networks outperforming similarly expensive Inception networks without residual connections by a thin margin.

In this work we study the __combination of the two most recent ideas:__ <a href="{{site.url}}/deep_learning/2018/06/19/residual-network.html" target="_blank">`Residual connections` [1]</a> and the latest revised version of the <a href="{{site.url}}/deep_learning/2018/06/23/rethinking-the-inception-architecture.html" target="_blank">`Inception-v3` architecture [2]</a>.

1. In [5], it is argued that residual connections are of inherent importance for training very deep archi.  
\\(\Longrightarrow\\) it is natural to add residual connection in the filter concat stage of the Inception acrhi.  
_This would allow Inception to reap all the benefits of the residual approach while retaining its computational efficiency_.
2. Introduce `Inception-v4`, which has more simplified archi. and more inception modules.


### Related work
... The authors (of [1]) argued that _residual connections are inherently necessary for training very deep convolutional model._ In the experimental section we demonstrate (in a bit ad-hoc manner) that it is not very difficult to train competitive very deep networks without utilizing residual connections. __However the use of residual connections semms to imporve the training speed greatly, which is alone a great argument for their use__.
  
History of Inception nets are,
1. Inception-v1: GoogLeNet [3]
2. Inception-v2: added <a href="{{site.url}}/deep_learning/2018/06/13/batch-normalization.html" target="_blank">batch normalization</a>
3. Inception-v3: added asym factorization and regularization [1]
4. Inception-v4: Introduced in this paper.
 

 
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="https://arxiv.org/abs/1512.00567" target="_blank">https://arxiv.org/abs/1512.00567</a>