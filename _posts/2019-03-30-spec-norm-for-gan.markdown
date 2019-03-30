---
layout: post
title:  "Spectral Normalization and GAN"
date:   2019-3-30 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning linear_algebra gan
---

<a href="https://arxiv.org/abs/1802.05957" target="_blank">https://arxiv.org/abs/1802.05957</a>


### Why Lipschitz Continuous Object Functions?

In the standard GAN formulation, the optimal \\(D\\) of GANs takes the form
\\[ D^\{\*\}\_G(x)=\frac\{q\_\{data\}\}\{q\_\{data\}(x)+p\_\{G\}(x)\} =\text\{sigmoid\}(f^\{\*\}(x))\\]
where
\\[ f^\*(x)=\ln q\_\{data\}(x) - \ln p\_\{G\}(x)\\]
and its derivative
\\[ \nabla\_xf^*(x)= \frac\{1\}\{q\_\{data\}(x)\}\nabla\_xq\_\{data\}(x) - \frac\{1\}\{p\_\{G\}(x)\}\nabla\_xp\_\{G\}(x)\\]
can be unbounded or even incomputable if any regularity is imposed to the deriv of \\(f(x)\\).

... we search for the \\(D\\) from the set of \\(K\\)-Lipschitz continuous functions, that is,
\\[\mathop\{\text\{arg max\}\}\_\{\|\| f\|\|\_\{\text\{Lip\}\} \leq K\} V(G,D)\\]

### Spectral Normalization

Proposing spectral normalization controls the Lipschitz constant of the discriminator function \\(f\\) by constraining the spectral norm of each layer \\(g\\ : \\ h\_\{in\}\mapsto h\_\{out\}\\). 

By definition, `Lipschitz norm` \\[\|\| g \|\|\_\{Lip\}:=\sup\_h\rho(\nabla g(h))\\]
where \\(\rho(A)\\) is the `spectral norm` of the matrox \\(A\\) (\\(L\_2\\) matrix norm)
\\[\rho(A) := \max\_\{h:h\neq 0\}\frac\{\|\| Ah\|\|\_2\}\{\|\|h \|\|\_2\}=\max\_\{\|\|h \|\|\_2\leq 1\}\|\| Ah\|\|\_2\tag\{6\}\\]

To see that (6) indeed holds,
1. \\(\leq\\): Let \\(h^\*\\) achieves the maximum in LHS. Then by
\\[\frac\{\|\| Ah^\* \|\|\_2\}\{\|\|h^\* \|\|\_2\}=\|\| A\frac\{h^\* \}\{\|\| h^* \|\|\_2\} \|\|\_2\\] we see that \\(\leq\\) holds
2. \\(\geq\\): Let \\(h^\*\\) achieves the maximum in RHS. Then by
\\[\|\| Ah^\* \|\|\_2 \leq \frac\{\|\| Ah^\* \|\|\_2\}\{\|\|h^\* \|\|\_2\}\\] 
since \\(\|\|h^\* \|\|\_2 \leq 1\\).

the objective value of (6) is equivalent to the largest singular value of \\(A\\). To see this indeed holds, let \\(A=SVD^T\\) using singular value decomposition.

### Intro
For example, (Nowozin et al., 2016; Uehara et al., 2016; Mohamed & Lakshminarayanan, 2017) revealed that the training of the discriminator amounts to the training of a good
estimator for the density ratio between the model distribution and the target. This is a perspective
that opens the door to the methods of implicit models (Mohamed & Lakshminarayanan, 2017; Tran
et al., 2017) that can be used to carry out variational optimization without the direct knowledge of
the density function

A persisting challenge in the training of GANs is the performance control of the discriminator. In
high dimensional spaces, the density ratio estimation by the discriminator is often inaccurate and
unstable during the training, and generator networks fail to learn the multimodal structure of the
target distribution. Even worse, when the support of the model distribution and the support of the
target distribution are disjoint, there exists a discriminator that can perfectly distinguish the model
distribution from the target (Arjovsky & Bottou, 2017). Once such discriminator is produced in
this situation, the training of the generator comes to complete stop, because the derivative of the
so-produced discriminator with respect to the input turns out to be 0. This motivates us to introduce
some form of restriction to the choice of the discriminator.

Next:  

