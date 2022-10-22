---
layout: post
title:  "cGANs with Projection Discriminator"
date:   2019-04-15 10:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning batch_norm
---

<a href="https://arxiv.org/abs/1802.05637" target="_blank">https://arxiv.org/abs/1802.05637</a>

<img src="{{site.url}}/images/deeplearning/gan/proj_d.png" width="800"/>

### Derivation of equation (2) in the paper

Let
* \\(x\\) be an input vector, \\(y\\): conditional information.
* discriminator \\(D(x,y;\theta):= \mathcal\{A\}(f(x,y;\theta))\\), where \\(f\\) is the model (neural net) and \\(\mathcal\{A\}\\) is the last activation function. `sigmoid` __is used in the proof of paper__, so that \\(\mathcal\{A\}=\sigma\\)
  
The standard __adversarial loss__ for GAN is given by
\\[\mathcal\{L\}(D)=-E\_\{q(y)\}[E\_\{q(x\|y)\}\ln D(x,y)]- E\_\{p(y)\}[E\_\{p(x\|y)\}\ln[1-D(x,y)]]\\]
To find the optimal discriminator \\(f^\text\{\*\}\\)in the functional space as <a href="https://deep_learning/2019/03/09/nips2016-gan-tutorial.html" target="_blank">Goodfellow did</a>, we first fix \\(x,y\\) of \\(D\\) so that
\\[\mathcal\{L\}(D(x,y))=-q(y)q(x\|y)\ln \sigma(f^\*(x,y))-p(y)p(x\|y)\ln[1-\sigma(f^\*(x,y))]] \\]
take derivative of the above term wrt a scalar \\(f^\*(x,y)\\) and letting it be 0 
\\(\left( \frac\{\partial \mathcal\{L\}(\sigma(f^\*(x,y)))\}\{f^\*(x,y)\}=0 \right)\\)gives
\\[q(y)q(x\|y)\frac\{1\}\{\sigma(f^\*(x,y))\}\sigma(f^\*(x,y))(1-\sigma(f^\*(x,y))) - p(y)p(x\|y)\frac\{1\}\{1-\sigma(f^\*(x,y))\}\sigma(f^\*(x,y))(1-\sigma(f^\*(x,y)))\\]
Dividing by the common term \\(\sigma(f^\*(x,y))(1-\sigma(f^\*(x,y))\\) and clearing the equation gives
\\[\frac\{q(y)q(x\|y)\}\{p(y)p(x\|y)\} =\frac\{\sigma(f^\*(x,y))\}\{1-\sigma(f^\*(x,y))\}\\]
\\[\ln \frac\{q(y)q(x\|y)\}\{p(y)p(x\|y)\} =\ln \frac\{\sigma(f^\*(x,y))\}\{1-\sigma(f^\*(x,y))\}\\]
We immediately see that RHS is the `logit` function, inverse of the softmax \\(\sigma\\). Now we obtain the equation (2) of the paper
\\[f^\*(x,y)= \ln \frac\{q(y)q(x\|y)\}\{p(y)p(x\|y)\} =\ln\frac\{q(y\|x)\}\{p(y\|x)\}+ln \frac\{q(x)\}\{p(x)\} := r(y\|x) + r(x) \tag\{2\}\\]

### Derivation of the projection D

Assuming the log-linear model (which includes many parametric family) to model the conditional distribution \\(p(y=c \| x)\\) of \\(D\\) (indeed it is),
\\[\ln p(y=c\|x) = \{v\_c^\{p\}\}^T\phi(x)-\ln Z(\phi(x))\\]
where
* \\(Z(\phi(x))=\sum\_\{j=1\}^C \{v\_c^\{p\}\}^T\\) is the partition function
* \\(\phi : x\mapsto R^\{d^L\}\\) is the __input to the final layer (fc layer) (after avg pool)__ of the network. 

This way, the ratio of log-likelihood ratio term \\(\ln\frac\{q(y=c\|x)\}\{p(y=c\|x)\}\\) becomes
\\[\ln\frac\{q(y=c\|x)\}\{p(y=c\|x)\} = (\{v\_c^\{q\}\}^T-\{v\_c^\{p\}\}^T)^T\phi(x)-(\ln Z^q(\phi(x))-\ln Z^p(\phi(x)))\\]
By letting
* \\(v\_c:=\{v\_c^\{q\}\}-\{v\_c^\{p\}\}\\)
* \\(\psi(\phi(x)):= -(\ln Z^q(\phi(x))-\ln Z^p(\phi(x))) + r(x)\\)

We see that letting \\(y=c\\) in equation (2) becomes
\\[f(x,y=c) = v\_c^T \phi(x) + \psi(\phi(x))\\]

If we use \\(y\\) as one-hot vector for each class, and \\(V\\) be an embedding matrix (num_cls \\(\times\\) nfg) for the classes, where each row is \\(v\_c\\),  we can rewrite the above model by
\\[f(x,y) = y^T V\phi(x) + \psi(\phi(x))\\]

Note that, in practice, 
* \\(\phi \\) : input to the fc layer, after avg pool (batch_size \\(\times\\) ndf)
* \\(V \\) : embedding, where each row represent \\(v\_c\\)

#TODO: explain summation

> Most notably, this formulation introduces the label information via an inner product, as opposed to concatenation.

> As we have repeatedly explained, our D measures the divergence between the generator distribution \\(p\\) and the target distribution \\(q\\) on the assumption that label posterior \\(p(y\|x),\\ q(y\|x) \\) are relatively simple (in the family of log-linear model), __and it is highly possible that we3 are gaining stability in the training process by imposing a regularity condtion on the divergence measure__.