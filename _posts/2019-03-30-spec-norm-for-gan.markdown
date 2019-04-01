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

### Lipschitz norm and Singular Value Decomposition

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

the objective value of (6) is equivalent to the largest singular value of \\(A\\). To see this indeed holds, let \\(A=SVD^T\\) using <a href="{{site.url}}/linear_algebra/2018/05/26/svd.html" target="_blank">singular value decomposition</a>. Then we see that
\\[\|\| Ah \|\|\_2 = \sqrt\{h^TDV^TVD^Th\}\\]
\\[= \sqrt\{\sigma\_i^2(d\_i^Th)^2\}\\]
\\(D\\) is the full-rank orthonormal eivenvector matrix, which could be the basis of the \\(h\\). With the constraint \\(\|\| h \|\|\_2\leq 1\\), we indeed see that \\(\sqrt\{\sigma\_i^2(d\_i^Th)^2\}\\) becomes the largest singular value, with \\(h\\) as the corresponding eigenvector.


### Approximating Lipschitz norm of the Neural Net
Assuming that the network (Discriminator) \\(f(x;\theta)\\) is composed of the activations \\(a\_L\\) and linear functions (Convs,...) \\(W^L:h\_l\mapsto h\_\{l+1\} \\)
\\[f(x;\theta):=W^\{L+1\}a\_L(W^\{L\}(a\_\{L-1\} ... a\_1(W^1 x)  ... )) \\]
Using the inequality
\\[ \|\|g\_1 \circ g\_2 \|\| \leq \|\| g\_1 \|\| \|\| g\_2\|\|\\]
(seperate supremum is greater than joint supremum)  
and assume that the Lipschitz norm of activations are 1 (this is indeed true for many ReLUs), we see that
\\[ \|\|f\|\|\_\{Lip\} \leq \mathop\{\prod\}\_\{l=1\}^\{L+1\}\sigma (W^l) \\]
`Spectral normalization` normalizes the spectral norm of the weight matrix \\(W\\) so that it satisfies \\(\sigma(W)=1\\).
\\[\bar\{W\}\_\{SN\}:=W/\sigma(W)\\]

Difference with L2 reg / Lasso / spectral norm "regularization"
- spectral normalization performs __data dependent regularization__
- l2reg, Lasso and spectral norm regularization performs __data independent regularization__ (in a sense that, it always tries to normalize the any weights toward 0 in some metric?)

### Fast Approximation of the Spectral Norm
- appeals to the `power method`
- <a href="https://pytorch.org/docs/stable/_modules/torch/nn/utils/spectral_norm.html" target="_blank">pytorch implementation</a>

For a weight matrix \\(W\\), power method performs following update
\\[x^\{k+1\}=W^TWx^\{k\}\\]
Decomposing \\(x^\{k\}=\Sigma c\_id\_i\\) gives,
\\[=\frac\{  DV^\{2k\}D^T\Sigma c\_id\_i \}\{ \|\| DV^\{2k\}D^T\Sigma c\_id\_i\|\| \} = \frac\{  \Sigma c\_i\sigma\_i^\{2k\}d\_i \}\{ \|\| \Sigma c\_i\sigma\_i^\{2k\}d\_i \} = \frac\{ \sigma\_1^\{2k\}\Sigma c\_i \frac\{\sigma\_i^\{2k\}\}\{\sigma\_1^\{2k\}\}d\_i \}\{ \|\| \sigma\_1^\{2k\}\Sigma c\_i \frac\{\sigma\_i^\{2k\}\}\{\sigma\_1^\{2k\}\}d\_i  \|\|\} \\]
where \\(\sigma\_1\\) is the largest eigenvalue. Since \\(\frac\{\sigma\_k\}\{\sigma\_1\}\\) converges to 0 for \\(k\neq 1\\), 
\\[\lim\_\{k\rightarrow\infty\}x^\{k\}= d\_1\\]
(\\(c\_1,\\ \sigma\_1\\) dissapears since we performed normalization. There is unique vector with unique direction with length 1)  
And we obtain the largest singular value by \\[\sigma\_1=\sqrt\{d\_1W^TWd\_1\}\\]

### Grad Analysis of the Spectrally Normalized Weights
THe gradients (when the spectrum(?) has multiplicities, we would be looking at subgradients here, which happens with probability 0 almost surely? - need check) of \\(\bar\{W\}\_\{SN\}(W)\\) wrt \\(W\_\{ij\}\\) is,
\\[\bar\{W\}\_\{SN\}:=W/\sigma(W)\\]
\\[\frac\{\partial \bar\{W\}\_\{SN\}(W) \}\{ \partial W\_\{ij\} \} = \frac\{\partial W \}\{ W\_\{ij\} \}\frac\{1\}\{\sigma(W)\} + \frac\{\partial \frac\{1\}\{\sigma (W)\} \}\{ \partial W\_\{ij\}\}W\\]
\\[= \frac\{1\}\{\sigma(W)\}E\_\{ij\} - \frac\{ 1 \}\{\sigma(W)^2\}\frac\{\partial\sigma (W)\}\{\partial W\_\{ij\}\} \\]
\\[=  \frac\{1\}\{\sigma(W)\}E\_\{ij\} - \frac\{[u\_1v\_1^T]\_\{ij\}\}\{\sigma(W)^2\}W \\]
(For the last term, remember that \\(\sigma(W)=\sigma\_1=u\_1Wv\_1^T\\)
\\[ = \frac\{1\}\{\sigma(W)\}(E\_\{ij\} - [u\_1v\_1^T]\_\{ij\} \bar\{W\}\_\{SN\})\\]
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


### References
* <a href="https://www.cs.cmu.edu/~venkatg/teaching/CStheory-infoage/book-chapter-4.pdf" target="_blank">https://www.cs.cmu.edu/~venkatg/teaching/CStheory-infoage/book-chapter-4.pdf</a>  
* <a href="https://christiancosgrove.com/blog/2018/01/04/spectral-normalization-explained.html" target="_blank">https://christiancosgrove.com/blog/2018/01/04/spectral-normalization-explained.html</a>