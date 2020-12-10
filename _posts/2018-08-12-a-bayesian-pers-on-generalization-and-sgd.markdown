---
layout: post
title:  "A Bayesian Perspective on Generalization and Stochastic Gradient Descent"
date:   2018-08-12 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning SGD bayesian laplace_approximation
---

<a href="https://arxiv.org/pdf/1804.06516.pdf" target="_blank">https://arxiv.org/pdf/1804.06516.pdf</a>  


### Bayesian Model Comparison
Let 
* \\(M\\): classification model
* \\(w\\): weight of \\(M\\)
* \\((x,y)\\): input / output

Then,
\\[\text\{Posterior over \}w\\>\propto\text\{ likelihood \}\times\text\{ prior\}\\]
\\[P(w|y,x;M)=\frac\{
P(y|w,x;M)\times P(w;M)
\}
\{
P(y|x;M)
\}
\\]

With the i.i.d assumption of inputs, the __likelihood__ becomes
\\[P(y|w,x;M)=\prod\_iP(y\_i|w,x\_i;M)\\]
\\[=\prod\_i\exp\\{\ln\{P(y\_i|w,x\_i;M)\}\\}\\]
\\[\exp\\{\sum\_i\{\ln\{P(y\_i|w,x\_i;M)\}\}\\}\\]
and we let
\\[P(y|w,x;M)=\text\{Likelihood of w\}=e^\{-H(w;M)\}, \text\{ where \}H(w;M):=-\sum\_i\{\ln\{P(y\_i|w,x\_i;M)\}\}\\]
Note that \\(H(w;M)\\) is the cross entropy term between one-hot categorical ground truth and our model.

Right term is a __Gaissian prior__ (\\(\lambda\\) is a precision (=inverse of variance))
\\[P(w;M)=\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-\lambda\frac\{w^2\}\{2\}\}\\]

Then the __posterior__ is proportional to
\\[P(w|y,x;M)\propto\{e^\{-H(w;M)\}\times \}\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-\lambda\frac\{w^2\}\{2\}\}\\]
\\[=\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-(H(w;M)+\lambda\frac\{w^2\}\{2\})\}\\]
By defining \\(C(w;M):=H(w;M)+\lambda\frac\{w^2\}\{2\}\\) (__L2 regularized cross entropy__ (cost function)), we obtain
\\[P(w|y,x;M)=\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}\\]

We also define 
* \\(w_0 :=\\) __optimal weight__ which maximizes the cost function (equivalent to maximizing the posterior)

To predict an unknown label \\(y_t\\) given \\(x_t\\) and training data / model,
\\[P(y_t|x_t,y,x;M)=\int\{P(y_t,w|x_t,y,x;M)dw\}\\]
Note that, with the (somewhat) strong independent assumption between \\(w, (x,y), (x_t,y_t)\\), the inner term becomes
\\[P(y_t,w|x_t,y,x;M)=\frac\{P(y_t,x_t,w,y,x;M)\}\{P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(y,x;M)\}\{P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(y,x;M)P(w,x_t;M)\}\{P(w,x_t;M)P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(w,y,x;M)\}\{P(w,x_t;M)P(y,x;M)\}\\]
\\[=P(y_t|w,x_t;M)P(w|y,x;M)\\]


We have calculated the right term \\(P(w|y,x;M)=\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}\\) above. To deal with the normalization term \\(P(y|x;M)\\), using the above results and marginalization,
\\[\int{P(w|y,x;M)}dw=1\\]
\\[\int{\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}}dw=1\\]
\\[\frac\{1\}\{P(y|x;M)\}\int{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}}dw=1\\]
\\[P(y|x;M)=\sqrt\{\frac\{\lambda\}\{2\pi\}\}\int{e^\{-C(w;M)\}}dw\\]
Therefore the prediction becomes
\\[P(y_t|w,x_t,y,x;M)=\int\{P(y_t|x_t;M)P(w|y,x;M)dw\}\\]
\\[=\int\{P(y_t|w,x_t;M)\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}dw\}\\]
\\[=\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}\}\{P(y|x;M)\}\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\\]
\\[=\frac\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}\}\{\sqrt\{\frac\{\lambda\}\{2\pi\}\}\int{e^\{-C(w;M)\}}dw\}\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\\]
\\[=\frac\{\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\}\{\int{e^\{-C(w;M)\}}dw\}\tag\{3\}\\]
However, 
* these integrals are dominated by the (maximum) regin near \\(w_0\\) (isn't it too rough?) (\\(w_0\\) is an argmax to the likelihood \\(P(y_t\|w,x_t;M)\\) and the term proportional to the posterior \\(e^\{-C(w;M)\}\\)), and since \\(P(y_t\|w,x_t;M)\\) is smooth (at least in deep learning, we never use models with discontinuity), we usually approximate \\[\frac\{\int\{P(y_t\|w,x_t;M)e^\{-C(w;M)\}dw\}\}\{\int{e^\{-C(w;M)\}}dw\}=\frac\{P(y_t\|w_0,x_t;M)e^\{-C(w_0;M)\}\}\{e^\{-C(w_0;M)\}}=P(y_t\|w_0,x_t;M)\\]

The probability ratio between two different model with different structure becomes
\\[\frac\{P(M_1\|y,x)\}\{P(M_2\|y,x)\}=\frac\{P(y\|x;M\_1)P(M_1)\}\{P(y\|x;M\_2)P(M_2)\}\\]
We usually set the __prior ratio__ \\(P(M=M_i)\\) as uniform, so what matters in determining good model is the __evidence ratio__, which controls how much the training data changes our prior belief.

We have derived the __evidence ratio__ above, that is,
\\[P(y|x;M)=\sqrt\{\frac\{\lambda\}\{2\pi\}\}\int{e^\{-C(w;M)\}}dw=\left(\frac\{\lambda\}\{2\pi\}\right)^\{p/2\}\int{e^\{-C(w;M)\}}dw\\]

__Assuming__ that the integral is dominated by the region near the minimum point \\(w_0\\), the multidimensional Taylor approximation at \\(w_0\\) of \\(C(w;M)\approx C(w_0)+0+\frac\{(w-w_0)^TC^\{(2)\}(w_0)(w-w_0)\}\{2\}\\) gives (remember that \\(C'(w_0)=0\\))  
(This approximation is dangerous, since it is very much likely that there exists many minimum points in deep learning models, thus the integral might not be dominated by a minimum point)
\\[P(y\|x;M)=\left(\frac\{\lambda\}\{2\pi\}\right)^\{p/2\}\exp\\{-C(w_0)\\}\int\exp\\{-\frac\{(w-w_0)^TC^\{(2)\}(w_0)(w-w_0)\}\{2\}\\}dw\\]

Remember that n-dimensional normal with __precision matrix__ \\(C^\{(2)\}(w_0)\in P\times P\\) integrates to (__assuming__, again, that the covariance matrix is not degenerate)
\\[1=\int\frac\{\sqrt\{\|C^\{(2)\}(w_0)\|\}\}\{(2\pi)^\{p/2\}\}\exp\{-\frac\{(w-w_0)^TC^\{(2)\}(w_0)(w-w_0)\}\{2\}\}\\]
Therefore, by modifying the equation,
\\[P(y\|x;M)\approx\left(\frac\{\lambda\}\{2\pi\}\right)^\{p/2\}\exp\\{-C(w_0)\\}\frac\{(2\pi)^\{p/2\}\}\{\sqrt\{\|C^\{(2)\}(w_0)\|\}\}\int\frac\{\sqrt\{\|C^\{(2)\}(w_0)\|\}\}\{(2\pi)^\{p/2\}\}\exp\\{-\frac\{(w-w_0)^TC^\{(2)\}(w_0)(w-w_0)\}\{2\}\\}\\]
\\[=\frac\{\lambda^\{p/2\}\exp\{-C(w_0)\}\}\{\sqrt\{\|C^\{(2)\}(w_0)\|\}\}\\]
(Above taylor approximation = `Laplace's approximation`.)

The determinant is the product of eigenvalues, and thus
\\[P(y\|x;M)\approx\exp\left{-\left(C(w_0)+\frac\{1\}\{2\}\sum\_\{i=1\}^\{p\}\ln(\lambda_i/\lambda)\right)\right}\\]
* The contribution \\(\sum\_\{i=1\}^\{p\}\ln(\lambda_i/\lambda)\\) is often called the `Occam factor`, since it enforces Ocam's razor; when two models describe the data equally well, the simpler model is usually better. 
* __Minima with low curvature are simple__, because the parameters do not have to be fine-tuned to fit the data.
\\[\text\{low curvature = low value of \sum\_\{i=1\}^\{p\}\ln(\lambda_i/\lambda)\}\\]

### Stochastic Differential Equations and the Scaling Rules (Need serious revision, scalar->vec)

We now identify the SGD "noise scale" (which is the key in the tradeoff between depth and bredth in the Bayesian evidence?), and use it to derive scaling rules which predict how the optimal batch size depends on the learning rate, training set size and momentum coef.

Consider a gradient update
\\[\nabla \omega=-\frac\{\epsilon\}\{N\}\left(
\frac\{dC\}\{d\omega\}+\left(\frac\{d\hat\{C\}\}\{d\omega\}-\frac\{dC\}\{d\omega\}\right)\right)
\\]
where
* \\[\frac\{dC\}\{d\omega\}\in\Re\\]: True gradient (scalar, not a RV, since we have a fixed set of training examples) of the cost function \\(C\\), which is defined by
\\[\frac\{dC\}\{d\omega\}:=\sum\_{i=1}^N\frac\{dC_i\}\{d\omega\}\\]
where
\\[C(x,w;M):=H(x,w;M)+\lambda\frac\{w^2\}\{2\}=-\sum\_i\{\ln\{P(y\_i|w,x\_i;M)\}\}+\lambda\frac\{w^2\}\{2\}\\]
Note that we have randomness in \\(x\\), and treat \\(C\\) as a function over the random variable (iid distributed) \\(X\\).
* \\[\frac\{d\hat\{C\}\}\{d\omega\}\in\Re\\]: gradient of a batch, which is a scalar random variable, since we have a randomness in selecting batch. It is defined by
\\[\frac\{d\hat\{C\}\}\{d\omega\}:=\frac\{N\}\{B\}\sum\_\{i=1\}^B\frac\{dC_i\}\{d\omega\}.\\]
Its expectation (as a RV) is,
\\[\text\{E\}\left[\frac\{d\hat\{C\}\}\{d\omega\}\right]=\frac\{N\}\{B\}\sum\_\{i=1\}^B\text\{E\}\left[\frac\{dC_i\}\{d\omega\}\right]=\frac\{N\}\{B\}\times B\times\frac\{1\}\{N\}\frac\{dC\}\{d\omega\}=\frac\{1\}\{N\}\frac\{dC\}\{d\omega\}\\]
We want \\(\frac\{d\hat\{C\}\}\{d\omega\}\approx \frac\{dC\}\{d\omega\}\\)
* \\(\epsilon\\): learning rate
* \\(N\\): training set size

Few things important are
1. \\[\text\{E\}\left[\frac\{dC_i\}\{d\omega\}\right]=\frac\{1\}\{N\}\frac\{dC\}\{d\omega\}\\]since from the definition of \\(\frac\{dC\}\{d\omega\}\\),
\\[\text\{E\}\left[\frac\{dC\}\{d\omega\}\right]=\frac\{1\}\{N\}\text\{E\}\left[\frac\{dC_i\}\{d\omega\}\right]\\]
Since \\(\frac\{dC_i\}\{d\omega\}\\) are iid, we obtain above result.
2. while,
\\[\text\{E\}\left[\frac\{dC_i\}\{d\omega\}\frac\{dC_j\}\{d\omega\}\right]=\left(\frac\{1\}\{N\}\frac\{dC\}\{d\omega\}\right)^2+F(\omega)\delta\_\{ij\}\\] since
\\[\text\{Cov\}\left[\frac\{dC_i\}\{d\omega\}\frac\{dC_j\}\{d\omega\}\right]=F(\omega)\delta\_\{ij\}\\]
\\[\quad\quad=\text\{E\}\left[\left(\frac\{dC_i\}\{d\omega\}-\frac\{1\}\{N\}\frac\{dC\}\{d\omega\}\right)^2\right]
=\text\{E\}\left[\frac\{dC_i\}\{d\omega\}\frac\{dC_j\}\{d\omega\}\right]
-\frac\{2\}\{N^2\}\left(\frac\{dC\}\{dw\}\right)^2+\frac\{1\}\{N^2\}\left(\frac\{dC\}\{dw\}\right)^2
\\]which gives the desired result. Note that \\(F(\omega)\\) is a __matrix__ describing the gradient covariances, which are a function of the current parameter values.


We adopt the `central limit theorem`(LINK!!!) and __model the gradient error__
\\[\alpha=\left(\frac\{d\hat\{C\}\}\{d\omega\}-\frac\{dC\}\{d\omega\}\right)\\]
with __Gaissan random noise__ (appendix C).

It is easy to show that
* \\[\text\{E\}\left[\alpha\right]=0 \\] (which is obvious with above equations), and
* \\[\text\{E\}\left[\alpha^2\right]=N(\frac\{N\}\{B\}-1)F(\omega)\\]
since
\\[\text\{E\}\left[\alpha^2\right]=\text\{E\}\left[\left(\frac\{d\hat\{C\}\}\{d\omega\}-\frac\{dC\}\{d\omega\}\right)^2\right]\\]
\\[=\text\{E\}\left[\left(\frac\{d\hat\{C\}\}\{d\omega\}\right)^2\right]-2\text\{E\}\left[\frac\{d\hat\{C\}\}\{d\omega\}\frac\{dC\}\{d\omega\}\right]+\text\{E\}\left[\left(\frac\{dC\}\{d\omega\}\right)^2\right]\\]
Each terms are
\\[\text\{E\}\left[\left(\frac\{dC\}\{d\omega\}\right)^2\right]=\left(\frac\{dC\}\{d\omega\}\right)^2\\]
\\[\text\{E\}\left[\left(\frac\{d\hat\{C\}\}\{d\omega\}\right)^2\right]=\text\{E\}\left[\left(\frac\{N\}\{B\}\sum\_\{i=1\}^B\frac\{dC_i\}\{d\omega\}\right)^2\right]=\frac\{N^2\}\{B^2\}\sum\_i^B\sum_j^B\left(\left(\frac\{1\}\{N\}\frac\{dC\}\{d\omega\}\right)^2+F(\omega)\delta\_\{ij\}\right)=\left(\frac\{dC\}\{d\omega\}\right)^2+\frac\{N^2\}\{B^2\}\sum\_i^B\sum_j^B\left(F(\omega)\delta\_\{ij\}\right)\\]
\\[-2\text\{E\}\left[\frac\{d\hat\{C\}\}\{d\omega\}\frac\{dC\}\{d\omega\}\right]=-2\frac\{dC\}\{d\omega\}\text\{E\}\left[\frac\{d\hat\{C\}\}\{d\omega\}\right]=-2\frac\{dC\}\{d\omega\}\frac\{1\}\{N\}\frac\{dC\}\{d\omega\}\\]


Links:  
<a href="https://arxiv.org/abs/1710.10710" target="_blank">[11] (Freezing Weights) On pre-trained image features and synthetic images for deep learning</a>  
<a href="http://vladlen.info/papers/playing-for-data.pdf" target="_blank">[26] (GTA5) Playing for data: Ground truth from computer games, in ECCV, 2016</a>  
<a href="https://arxiv.org/abs/1605.06457" target="_blank">[7] (VKITTI) Virtual Worlds as Proxy for Multi-Object Tracking Analysis, In CVPR, 2016</a>  