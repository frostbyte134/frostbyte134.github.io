---
layout: post
title:  "GAN Tutorial - NIPS 2016"
date:   2019-03-09 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning gan 
---

<a href="https://arxiv.org/abs/1701.00160" target="_blank">https://arxiv.org/abs/1701.00160</a>


{% include note.html content="Add your note here." %}

<div class="alert alert-danger" role="alert"><i class="fa fa-exclamation-circle"></i> <b>Warning: </b>This is a special warning message.</div>


TODO
1. MLE - add link


### 1. Intro

_Generative model_
> In this tutorial, this term refers  to any model that takes a training set, consisting of samples drawn from a distribution \\(p\_\{data\}\\), and learns to represent an estimate of that distribution __somehow__.

By __somehow__ we mean
1. explicit modeling of \\(p\_\{model\}\\)
2. implicit modeling, sample generation from \\(p\_\{model\}\\).  
`GAN`s focuses primarily on it, though it is possible for GANs to do both

Why genertative models? 
1. reinforcement learning
2. semi-supervised learning
3. superpixels / img2img

### 2. Gan in generative models

#### MLE and GAN
> Some generative models do not use MLE by default, but can be made to do so (_`GAN`s fall into this category)_

(Recap): MLE (TODO: add link)
\\[p\_\{model\} \propto p\_\{data \| model\}\times p\_\{data\}\\]
where \\[p\_\{data \| model\}\\ =\\ p\_\{model\}\left(x^\{(i)\};\theta\right)\\]
is the Likelihood of the data on the model, parameterized by \\(\theta\\).

The principle of MLE simply says to choose the params for the model that maximize the likelihood of the training data. This is easiest to do in log-space, where we have a sum rather than a product.
\\[\theta^\{*\}=\text\{argmax\}\_\{\theta\}\sum_\{i=1\}^m p\_\{model\}\left(x^\{(i)\};\theta\right)\\]

We can also think of `MLE` as __minimizing the KL divergence__ between \\(p\_\{data\}, p\_\{model\}\\)
\\[\theta^\{*\}=\text\{argmin\}\_\{\theta\}D\_\{KL\}(p\_\{data\}(x), p\_\{model\}(x;\theta))\\]
In practice, we don't have access to \\(p\_\{data\}\\), so we define `empirical distribution` \\(\hat\{p\}\_\{data\}\\) that places mass only on exactly those \\(m\\) points, approximating \\(p\_\{data\}\\).

> Minimizing \\(D\_\{KL\}(p\_\{data\}(x) \|\| p\_\{model\}(x;\theta))\\) is exactly equivalent to maximing the log-lkelihood of the training set.

### Taxonomy
<img src="{{ site.url }}/images/deeplearning/gan/taxonomy.png" class="center" style="width:700px"/> 

#### GANs vs other generative models
* The design of the generator has very few restrictions.
* No Markov chains, no variational bound needed
* Traing GAN requires finding Nash equalibrium of a game (difficult than simple minimizing)

### 3. How do GANs work?
`GAN` = structured probabilistic model containing latent variables \\(z\\) and observed variables \\(x\\)

__2 players__ in the game are represented by 2 differentiable (wrt its input and params) functions
1. `Discriminator` \\(D\\): takes \\(x\\) as an input and uses \\(\theta^\{(D)\}\\) as parameters
2. `Generator` \\(G\\): takes \\(z\\) as input and uses \\(\theta^\{(G)\}\\) as parameters

The __cost function__ of each players is defined in terms of both palyers' parameters
1. Cost func of \\(D:=J^\{(D)\}(\theta^\{(D)\},\theta^\{(G)\})\\)  
We wishes to minimize \\(J^\{(D)\}\\) while controlling only \\(\theta^\{(D)\}\\)
2. Cost func of \\(G:=J^\{(G)\}(\theta^\{(D)\},\theta^\{(G)\})\\)
We wishes to minimize \\(J^\{(G)\}\\) while controlling only \\(\theta^\{(G)\}\\)

The __solution__ to the above minimax optimization problem is a __(local) minimum (=saddle point)__, a point in parameter space where all neighboring points have greater or equal cost.

We use the term (local differential) `Nash equialibrium` here, which is a tuple \\((\theta^\{(D)\},\theta^\{(G)\})\\) s.t.
1. a local minimum of \\(J^\{(D)\}\\) wrt \\(\theta^\{(D)\}\\), and a 
2. a local minimum of \\(J^\{(G)\}\\) wrt \\(\theta^\{(G)\}\\)


### The generator G

* When \\(z\\) is sampled from some simple prior dist., \\(G(z)\\) yields a sample of \\(x\\) drawn from model \\(p\_\{model\}\\).
* There is not much restriction on \\(G\\)

### Simultaneously SGD
The training process consists of `simultaneous SGD`.  

On each step,
1. two minibatches, of \\(z\\) from the model's prior over latent variables and \\(x\\) from the dataaset, are sampled
2. two gradient steps are made simultaneously:
	* One updating \\(\theta^\{(D)\}\\) to reduce \\(J^\{(D)\}\\)
	* One updating \\(\theta^\{(G)\}\\) to reduce \\(J^\{(G)\}\\)

* Adam is usually a good choice
* running more steps of one player than the other, as of late 2016, seems like a not good protocol (by Goodfellow)

### Cost function - Discriminator
\\(J^\{(D)\}\\) is defined as
\\[J^\{(D)\}(\theta^\{(D)\}, \theta^\{(G)\}) = -\frac\{1\}\{2\}E\_\{x\sim p\_\{data\}\}\log D(x) 
-\frac\{1\}\{2\}E\_\{z\}\log (1-D(x)) \\]

which is the standrad cross-entropy loss (add link), trained on 2 minibatches
1. from the dataseet, where the label is 1 for all examples
2. from the generator, there the label is 0 for all examples

#### __The optimal discriminator__

Supposing that the discriminator can be optimized in function space (it can be an arbitrary mapping, unlike in the functional space), taking derivative gives
\\[\frac\{\partial J^\{(D)\}\}\{\partial D(x)\}=\frac\{D(x)\}\{p\_\{d\}(x)\}+\frac\{1-D(x)\}\{p\_\{m\}(x)\}\\]
\\[\rightarrow D(x)=\frac\{p\_\{d\}(x)\}\{p\_\{m\}(x)+p\_\{d\}(x)\}\\]

>(Goodfellow) Estimating this ratio enables us to compute a wide variaty of divergences and their gradients.

Unlike other deep generative models, which makes approximation based on lower bounds or Makrov chains, `GAN` makes approximation based on using supervised learning to estimate a ratio of two densities.

>(Goodfellow)  The GAN approximation is subject to the failures of supervised learning: __overfitting and underfitting__. In principle, with perfect optimization and enough data these can be overcomed. Other models makes other approximation that have other failures.

### Minimax (Theoritical formulation)

The simplest version of the game is a `zero-sum game`, in which the sum of all player's score is always zero. This formulation gives the generator's cost function (which wasn't discussed so far) as
\\[J^\{(G)\}:=-J^\{(D)\}=+\frac\{1\}\{2\}E\_\{x\sim p\_\{data\}\}\log D(x) 
+\frac\{1\}\{2\}E\_\{z\}\log (1-D(x))\\]
Since the 1st term has nothing to do with the generator,
\\[J^\{(G)\}=\frac\{1\}\{2\}E\_\{z\}\log (1-D(x))\\]


the zero-sum game(=`minimax` game) can be solved by following minimax optimization problem
\\[\mathop\{\text\{arg min\}\}\_\{\theta^\{(G)\}\}\mathop\{\text\{arg max\}\}\_\{\theta^\{(D)\}\}-J^\{(D)\}\left(\theta^\{(D)\}, \theta^\{(G)\}\right)\\]


<a href="{{site.url}}/deep_learning/2018/12/07/gan.html" target="_blank">Goodfellow</a> showed that under above formulation, learning resembles minimizing the Jenson-Shannon divergence between the data and the modle distribution, and the game converges to an equalibrium under the convexity assumption.

<h3 id="heuristic"> Heuristic, <b>non-saturating game</b></h3>

> Minimizing the cross-entropy between a target class and a classifier's predicted distribution is highly effective b/c the cost never saturates when the classifier has the wrong output. THe cost does eventually saturate, approaching 0, but only when the classifier has already chosen the correct class.

(\\(-\log p\\) is very negative when p is so low, 0 when \\(p\approx 1\\))

In the above minimax game, D minimizes the cross-entropy but G maximizes it. __When the D successfully rejects generator samples with high confidence, the generator's gradient vanishes.__

To solve this, one approach is _to continue to use cross-entropy minimization for the generator_. Instead of flipping sign the cost of D, we flip the target used to construct the cross-entropy cost.
\\[J^\{(G)\}=\frac\{1\}\{2\}E\_\{z\}\log (D(x))\\]

> (Goodfellow) This version of the game is heuristically motivated, rather than being motivated by a theoretical convern. The sole motivation for this version of the game is to ensure that _each player has a strong gradient when that player is "losing" the game_


### MLE game
It is possible to do (approximated) MLE learning with GANs, which would mean _minimizing the KL-divergence between the data and the model_. <a href="{{site.url}}/deep_learning/2018/03/26/mle-neg-log-likelihood.html" target="_blank">(link)</a>

But note that, the above heuristic game is never equivalent to maximizing MLE.

### Choice of divergence (Rather than KL)

We might wonder exactly what is that makes GANs work well for generating samples.
> (Goodfellow) Previously, many people (including the author) believed that GANs produced sharp, realistic samples b/c they minimize the Jenson-Shannon divergence while VAEs produce blurry sample b/c they minimize the KL-divergence between the3 data and model.




Link:  
[6] <a href="https://arxiv.org/pdf/1502.02791" target="_blank">Learning transferable features with deep adaptation networks</a>  
[13] <a href="https://arxiv.org/abs/1606.07536" target="_blank">Coupled Generative Adversarial Networks</a>  

Next:  
[6] - Learning transferable features with deep adaptation networks   

