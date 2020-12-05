---
layout: post
title:  "Inferences in Continuous Linear Models"
date:   2020-12-05 08:00:05 +0800
categories: probability
use_math: true
tags: math probability bayesian
---


> <a href="https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-ii-inference-limit-theorems/" target="_blank">part-ii-inference-limit-theorems</a>

### Recognizing Normal PDF

\\[f\_X(x) = \frac{1}{\sigma\sqrt{2\pi}}\exp\left\\{ -\frac{(x-\mu)^2}{2\sigma^2} \right\\}\\]

\\[c\cdot\exp\left[\alpha x^2+\beta x + \gamma \right] = c\cdot\exp\left[\alpha((x+\frac{\beta}{2\alpha})^2 - \frac{\beta^2}{4\alpha^2}+\frac{\gamma}{\alpha})\right]\\]

- `negative exponential of a quadratic function is always a normal`
- Note that normal PDF has its peak at `mean`. Thus by using the optimality condition (of a convex quadratic function), we easily see that
  \\[2\alpha x+\beta = 0 \quad\rightarrow\quad \mu = -\frac{\beta}{2\alpha}\\]
- Similarly, `variance` can be calculated by collecting all scalar coefs of the quadratic, summarize them, multiply by 2, and invert it

### Estimating Normal with Additive Normal Noise
let
\\[X=\Theta + W,\quad\quad\quad \Theta,W \sim N(0, 1) \text{ are independent }\\]

1. we see that \\(f\_{X\|\Theta}(x\|\theta) = X + \theta + W \sim (\theta, 1)\\) (note that capital theta stands for the realized scalar value)
2. Then, using the bayse rule, 
   \\[
   \begin\{align\*\}  
   f\_{\Theta\|X}(\theta\|x) &= \frac{ f\_\Theta(\theta)f\_{X\|\Theta}(x\|\theta) }{ f\_X(x) } \cr
                             &= \frac{1}{f\_X(x)}c\exp\left\\{ -\frac{1}{2}\theta^2 \right\\} c\exp\left\\{ -\frac{1}{2}(x-\theta)^2 \right\\}
                             &= c(x)\exp\\{\text{quadratic}(\theta)\\}
   \end\{align\*\}
   \\]
   __we see that the posterior is also an Normal__   
3. Note that, the pdf of normal has its peak in its mean, which makes \\(\hat{\theta}\_{MAP} = \hat{\theta}\_{LMS}\\).  
   And we can easily get the mean, as stated above by differentiation 
   \\[\frac{\partial}{\partial \theta}\left[ \frac{1}{2}\theta^2 + \frac{1}{2}(x-\theta)^2 \right] \quad\rightarrow\quad \theta=x/2\\]
4. Thus we conclude,  
   1. optimal estimation \\(\hat{\theta}\_{MAP} = \hat{\theta}\_{LMS} = x/2\\)  
   2. optimal estimator \\(\hat{\Theta}\_{MAP} = \hat{\Theta}\_{LMS} = X/2\\)
5. even with general Normal RVs, above holds (with slightly different scalars)


### The Case of Multiple Observation
Now we have __multiple observations__, and we want to combine them for better inference
\\[X\_1=\Theta+W\_1\\]
\\[\cdots\\]
\\[X\_n=\Theta+W\_n\\]

Let
\\[\Theta\sim N(x\_0,\sigma\_0^2),\quad\quad W\_i\sim N(0, \sigma\_i^2)\\]
\\[\Theta,W\_1,...,W\_n \text{ are independent }\\]

We again want to calculate the posterior using Bayes rule
\\[f\_{\Theta\|X}(\theta\|x) = \frac{ f\_\Theta(\theta)f\_{X\|\Theta}(x\|\theta) }{ f\_X(x) }\\]
Note that the \\(X\\) here is a __random vector.__


{:.acounter}
1. For each measurement \\(i\\), given \\(\Theta = \theta, \\ X\_i=\theta+W\_i, \\ X\sim N(\theta,\sigma\_i^2)\\)
2. Now consider the random vector \\(X\\).  
   We want to calculate \\(f\_{X\_1,...,X\_n\|\Theta}\\), but note that since \\(\Theta\\) and \\(X\_1,...,X\_n\\) are independent (each \\(X\_i\\)s are linear (additive) relation with \\(W\_i\\)),   
   \\(f\_{X\_1,...,X\_n\|\Theta} = f\_{X\_1,...,X\_n}\\) and it factors into the __product__ of \\(n\\) normal.
   \\[ f\_{X\_1,...,X\_n\|\Theta}(x\_1,...,x\_n\|\theta) = \prod\_{i=1}^nf\_{x\_i\|\Theta}(x\_i\|\theta)\\]
3. Now using the bayese rule, 
   \\[f\_{\Theta\|X}(\theta\|x)=\frac{1}{f\_X(x)}\cdot c\_0 \exp\left\\{ -(\theta-x\_0)^2/2\sigma\_0^2 \right\\} 
   \prod\_{i=1}^nc\_i\exp\left[ -(\theta-x\_0)^2/2\sigma\_0^2 \right] 
   \\]
   we again see that the posterior is normal (it is quadratic!)
4. In summary,
   \\[f\_{\Theta\|X}(\theta\|x)= = c\cdot \exp\left\\{ \sum\_{i=0}^n \frac{(\theta-x\_i)^2}{2\sigma\_i^2} \right\\}\\]
   To perform MAP/LMS, we find the peak of the distribution (=mean), wich is
   \\[\sum\_{i=0}^n \frac{(\theta\-x\_i)}{\sigma\_{i}^2}=0\\]
   so we conclude,
   \\[\hat{\theta}\_{MAP} = \hat{\theta}\_{LMS} = \frac{\sum\_{i=0}^n\frac{x\_i}{\sigma\_i^2}}{\sum\_{i=0}^n\frac{1}{\sigma\_i^2}}\\]
5. interpretation
    -1. posterior is normal, estimates are linear of the form \\(\hat{\theta} = a\_0+a\_1x\_1+...+a\_nx\_n\\)
    -2. estimate \\(\hat{\theta)}\\) : weighted average (inverted variance) (`convex combination`) of \\(x\_0\\) (`prior mean`) and \\(x\_i\\) (`observations`)
    -3. \\(\sigma\_i^2\\) large - \\(X\_i\\) is very noise - gets small weights
{:.acounter}


#### The Mean Squared Error
1. reasonable performance measure = \\(E[(\Theta-\hat{\Theta})^2 | X=x]\\)
  - But given \\(X=x\\), \\(\hat{\Theta}\\) is determined
   \\[E[(\Theta-\hat{\Theta})^2 | X=x] = E[(\Theta-\hat{\theta})^2 | X=x]\\]
  - and we calculated \\(\hat{\theta}\\) just above, as \\(\frac{\sum\_{i=0}^n\frac{x\_i}{\sigma\_i^2}}{\sum\_{i=0}^n\frac{1}{\sigma\_i^2}}\\)
  - And note that \\(\hat{\theta}\\) is the mean of the posterior, so that \\(\hat{\theta}=E[\Theta\|X=x]\\)
  - now the performance measure becomes \\(E[(\Theta -  E[\Theta\|X=x] )^2 || X=x]\\), which is the variance of \\(\Theta\\) in the \\(X=x\\) conditioned universe
   \\[E[(\Theta-\hat{\Theta})^2 \| X=x] = \text{var}(\Theta\|X=x)\\]
2. In "Recognizing Normal PDF" part, we had simple way to calculate the variance of a normal
   1. \\(\alpha = \sum\_{i=0}^n\frac{1}{2\sigma\_i^2}\\)
   2. multipling 2 and inverting gives \\(1/(\sum\_i=0^n\frac{1}{\sigma\_i^2})\\)
3. Now we have \\(E[(\Theta-\hat{\Theta})^2 \| X=x] = 1/(\sum\_i=0^n\frac{1}{\sigma\_i^2})\\). What about \\(E[(\Theta-\hat{\Theta})^2]\\) ?
4. using total expectation theorem, we again see that \\(E[(\Theta-\hat{\Theta})^2] = 1/(\sum\_i=0^n\frac{1}{\sigma\_i^2})\\)
   - This makes sense, since Given \\(X=x\\), the mean squared value was not a function of \\(x\\)
5. interpretation
   - some \\(\sigma\_i^2\\) small \\(\quad\rightarrow\quad\\) MSE small. Our uncertainty is small
   - Many \\(\sigma\_i^2\\) small \\(\quad\rightarrow\quad\\) MSE small. Our uncertainty is large
   - If \\(\sigma\_0=\sigma\_1=...\\), then the variance becomes \\(\sigma^2/(n+1)\\). __More observation -> more certain!__ (estimated variance goes down)
   - Conditional MSE was not a function of \\(X=x\\), all same! = no specific \\(X=x\\) is more desirable



For simple model \\(X, W\sim N(0, 1), X,W\\) are independent,  
<img src="{{site.url}}/images/math/prob/normal_1.jpg" width="700">  

1. red line : prior \\(f\_\Theta(\theta)\\)
2. blue line : posterior \\(f\_{\Theta\|}(\theta)\\) basesd on observation \\(x=0, \hat{\theta}=0/2\\)
3. green line : posterior \\(f\_{\Theta\|}(\theta)\\) basesd on observation \\(x, \hat{\theta}=x/2\\)

Note that the variance is fixed regardless of the observation, as we've seen above.