---
layout: post
title:  "Designing Models to Aid Optimization"
date:   2018-06-09 08:34:00 +0900
categories: deep_learning
use_math: true
tags: optimization deep_learning need_revise
---

> To imporve optimization, the best strategy is not always to improve the optimization algorithm. Instead, many improvements in the optimizatio of deel models have come from designing the models to be easier to optimize.

In priciple, we could use activation functions that increase and decrease in jagged nonmonotonic patterns, but this would make optimization extremely difficult. In practive, _it is more important to choose a model family that is easy to optimize, than to use a powerful optimization algorithm_. 
* Most of the advances in neural entwork learning over the past 30years have been obtained by changing the model family rather than changing the optimization procedure. 
* Stochastic gradient descent with momentum, which was used to train neural networks in the 1980s, remains in use in motdern state-of-the-art neural network applications.

### Design choice of modern neural networks
* linear transformations between layers
* activation functions that are differentiable almost everywhere, with significant slope in large portions of their domain
In particular, LSTM, ReLU and maxout units have all moved towrd __using more linear functions than previous models__. These models have nice properties that make optimization easier.

In other words,
> modern neural nets have been designed so that their _local_ gradient information corresponds reasonably well to moving toward a distant solution.

Other model design strategies, such as skip connections, linear paths, or residuals mitigate the vanishing gradient problems.


Example
* <a href="{{site.url}}/deep_learning/2018/06/08/batch-normalization.html" target="_blank">Batch normalization</a>
* Residuals (link!)


<hr>
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>