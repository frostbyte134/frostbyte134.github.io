---
layout: post
title:  "Bayesian Model Comparison and Preference to Flat Minima"
date:   2018-08-20 08:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning SGD bayesian laplace_approximation
---

<a href="https://authors.library.caltech.edu/13793/" target="_blank">https://authors.library.caltech.edu/13793/</a>  


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

Right term is a __Gaussian prior__ in \\(R^p\\), where \\(\lambda\in\Re\\) is a precision matrix (=inverse of variance)
\\[P(w;M)\sim N(0,diag(\lambda))=\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}e^\{-\lambda\frac\{w^Tw\}\{2\}\}\\]

Then the __posterior__ is proportional to
\\[P(w|y,x;M)\propto\{e^\{-H(w;M)\}\times \}\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}e^\{-\lambda\frac\{w^Tw\}\{2\}\}\\]
\\[=\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}e^\{-(H(w;M)+\lambda\frac\{w^Tw\}\{2\})\}\\]
By defining \\(C(w;M):=H(w;M)+\lambda\frac\{w^2\}\{2\}\\) (__L2 regularized cross entropy__ (cost function)), we obtain
\\[P(w|y,x;M)=\frac\{\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}\\]

We also define 
* \\(w_0 :=\\) __optimal weight__ which maximizes the cost function (equivalent to maximizing the posterior)

To predict an unknown label \\(y_t\\) given \\(x_t\\) and training data / model, we marginalize over all possible weights
\\[P(y_t|x_t,y,x;M)=\int\{P(y_t,w|x_t,y,x;M)dw\}\\]
Note that, with the (somewhat) strong independent assumption between \\(w, (x,y), (x_t,y_t)\\), the inner term becomes
\\[P(y_t,w|x_t,y,x;M)=\frac\{P(y_t,x_t,w,y,x;M)\}\{P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(y,x;M)\}\{P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(y,x;M)P(w,x_t;M)\}\{P(w,x_t;M)P(x_t,y,x;M)\}\\]
\\[=\frac\{P(y_t,w,x_t;M)P(w,y,x;M)\}\{P(w,x_t;M)P(y,x;M)\}\\]
\\[=P(y_t|w,x_t;M)P(w|y,x;M)\\]


We have calculated the right term \\(P(w|y,x;M)=\frac\{\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}\\) above. To deal with the normalization term \\(P(y|x;M)\\), using the above results and marginalization,
\\[\int{P(w|y,x;M)}dw=1\\]
\\[\int{\frac\{\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}}dw=1\\]
\\[\frac\{1\}\{P(y|x;M)\}\int{\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}e^\{-C(w;M)\}}dw=1\\]
\\[P(y|x;M)=\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}\int{e^\{-C(w;M)\}}dw\\]
Therefore the prediction becomes
\\[P(y_t|w,x_t,y,x;M)=\int\{P(y_t|w,x_t;M)P(w|y,x;M)dw\}\\]
\\[=\int\{P(y_t|w,x_t;M)\frac\{\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}e^\{-C(w;M)\}\}\{P(y|x;M)\}dw\}\\]
\\[=\frac\{\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}\}\{P(y|x;M)\}\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\\]
\\[=\frac\{\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}\}\{\sqrt\{\frac\{\lambda^p\}\{(2\pi)^p\}\}\int{e^\{-C(w;M)\}}dw\}\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\\]
\\[=\frac\{\int\{P(y_t|w,x_t;M)e^\{-C(w;M)\}dw\}\}\{\int{e^\{-C(w;M)\}}dw\}\tag\{3\}\\]
However, 
* these integrals are dominated by the (maximum) regin near \\(w_0\\) (isn't it too rough?) (\\(w_0\\) is an argmax to the likelihood \\(P(y_t\|w,x_t;M)\\) and the term proportional to the posterior \\(e^\{-C(w;M)\}\\)), and since \\(P(y_t\|w,x_t;M)\\) is smooth, we usually approximate \\[\frac\{\int\{P(y_t\|w,x_t;M)e^\{-C(w;M)\}dw\}\}\{\int{e^\{-C(w;M)\}}dw\}=\frac\{P(y_t\|w_0,x_t;M)e^\{-C(w_0;M)\}\}\{e^\{-C(w_0;M)\}}=P(y_t\|w_0,x_t;M)\\]

The probability ratio between two different model with different structure becomes
\\[\frac\{P(M_1\|y,x)\}\{P(M_2\|y,x)\}=\frac\{P(y\|x;M\_1)P(M_1)\}\{P(y\|x;M\_2)P(M_2)\}\\]
We usually set the __prior ratio__ \\(P(M=M_i)\\) as uniform, so what matters in determining good model is the __evidence ratio__, which controls how much the training data changes our prior belief.

We have derived the __evidence ratio__ above, that is,
\\[P(y|x;M)=\left(\frac\{\lambda\}\{2\pi\}\right)^\{p/2\}\int{e^\{-C(w;M)\}}dw\\]

__Assuming__ that the integral is dominated by the region near the minimum point \\(w_0\\), the multidimensional Taylor approximation at \\(w_0\\) of \\(C(w;M)\approx C(w_0)+0+\frac\{(w-w_0)^TC^\{(2)\}(w_0)(w-w_0)\}\{2\}\\) gives (remember that \\(C'(w_0)=0\\))  
(This approximation is dangerous, since it is very much likely that there exists many minimum points in deep learning models, thus the integral might not be dominated by a minimum point)
\\[P(y\|x;M)=\left(\frac\{\lambda\}\{2\pi\}\right)^\{p/2\}\exp\\{-C(w_0)\\}\int\exp\\{-\frac\{(w-w_0)^TC^\{(2)\}(w_0)(w-w_0)\}\{2\}\\}dw\\]

Remember that n-dimensional normal with __precision matrix__ \\(C^\{(2)\}(w_0)\in P\times P\\) integrates to (__assuming__, again, that the covariance matrix is not degenerate)
\\[1=\int\frac\{\sqrt\{\|C^\{(2)\}(w_0)\|\}\}\{(2\pi)^\{p/2\}\}\exp\left\\{-\frac\{(w-w_0)^TC^\{(2)\}(w_0)(w-w_0)\}\{2\}\right\\}dw\\]
Therefore, by modifying the equation,
\\[P(y\|x;M)\approx\left(\frac\{\lambda\}\{2\pi\}\right)^\{p/2\}\exp\\{-C(w_0)\\}\frac\{(2\pi)^\{p/2\}\}\{\sqrt\{\|C^\{(2)\}(w_0)\|\}\}\int\frac\{\sqrt\{\|C^\{(2)\}(w_0)\|\}\}\{(2\pi)^\{p/2\}\}\exp\left\\{-\frac\{(w-w_0)^TC^\{(2)\}(w_0)(w-w_0)\}\{2\}\right\\}\\]
\\[=\frac\{\lambda^\{p/2\}\exp\{-C(w_0)\}\}\{\sqrt\{\|C^\{(2)\}(w_0)\|\}\}\\]
(Above taylor approximation = `Laplace's approximation`.)

The <a href="{{site.url}}/linear_algebra/2018/05/09/characteristic-equ.html#apps" target="blank">determinant is the product of eigenvalues</a>, and thus
\\[P(y\|x;M)\approx\ext\left{-\left(C(w_0)+\frac\{1\}\{2\}\sum\_\{i=1\}^\{p\}\ln(\lambda_i/\lambda)\right)\right}\\]
* The contribution \\(\sum\_\{i=1\}^\{p\}\ln(\lambda_i/\lambda)\\) is often called the `Occam factor`, since it enforces Ocam's razor; when two models describe the data equally well, the simpler model is usually better. 
* __Minima with low curvature are simple__, because the parameters do not have to be fine-tuned to fit the data.
\\[\text\{low curvature = low value of \sum\_\{i=1\}^\{p\}\ln(\lambda_i/\lambda)\}\\]
