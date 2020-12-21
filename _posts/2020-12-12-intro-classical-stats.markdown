---
layout: post
title:  "An Intro to Classical Statistics"
date:   2020-12-12 08:00:05 +0800
categories: probability
use_math: true
tags: math probability bayesian
---

`classical` = not Bayesian
- `Bayesian` : unknown params were __random__ with certain prior
- `classic` : __non-random__ that just happens to be unknown

estimating without prior
- sample mean gives point estimate
- `confidence interval` = accuracy of point estimate (high prob of containing true theta)
  - can easily calculate using `CLT`
- estimating correlation coefs using sample mean?

MLE
- uniform prior
- applicable on classical stats



### Classical Statistics
Bayesian
- Inference using Bayes rule (unknow \\(\Theta\\) and observation \\(X\\) are both RVs)

classical
- \\(\theta\\) is non-random, certain __fixed parameter__ of \\(P\_X(x;\theta)\\).
- We estimate \\(\theta\\) using the random observation \\(X\\), using `estimator` \\(\hat{\Theta}=g(X)\\)
  - often, both \\(g\\) and \\(\hat{\Theta}\\) are called `estimator`
  - \\(\hat{\Theta}\\) is a RV
  - \\(\hat{\theta}=g(x)\\) is called `estimate` (realized, sampled one)


<img src="{{site.url}}/images/math/prob/classic.jpg" width="700">  

- many models, one for each possible value of \\(\theta\\).

Problem types in classical statistics
- `Hypothesis testing` : \\(H\_0 : \theta=1/2\\) vs \\(H\_1 : \theta = 3/4\\)
- `Composite testing` : \\(H\_0 : \theta=1/2\\) vs \\(H\_1 : \theta \neq 1/2\\) (more complex)
- `Estimation` : design an __good estimator__ \\(\hat{\Theta}\\)
  - good : estimation error \\(\hat{\Theta}-\theta\\) small
  - small : many interpretation for the notion
- no single answer, not an closed problems
  - but __good properties__ exist



### Estimating a mean

The simplest `Estimation` problem

Let
- \\(X\_1,,,.X\_n\\) : i.i.d, mean \\(\theta\\), variance \\(\sigma^2\\)

Then we have `sample mean` \\(\hat{\Theta}\_n := M\_n=\frac{X\_1+...+X\_n}{n}\\)
- is an `unbiased` estimator \\[E[\hat{\Theta}] = \theta\\]
- by `WLLN`, \\(\hat{\Theta}\_n\rightarrow\theta,\\ \forall \theta\\) - is a `consistent` estimator
- `mean squared error` MSE \\(E[(\hat{\Theta}\_n-\theta)^2] = \text{var}(\hat{\Theta}\_n)=\sigma^2/n\\)
  - in sample mean problem it does not depend on \\(\theta\\), but in some other problems it may


#### On the MSE of an Estimator
For __any__ estimator, using \\(E[X^2]=\text{var}(X) + E[X]^2\\),
\\[E[(\hat{\Theta}-\theta)^2] = \text{var}(\hat{\Theta}-\theta) + E[\hat{\Theta}-\theta]^2 = \text{var}(\hat{\theta}) + (\text{bias})^2\\]

Suppose our estimator is sample mean, \\(\hat{\Theta}\_n=M\_n\\).  
- MSE is, \\(\sigma^2/n + 0\\)

OTOH, if the estimator is constant 0, \\(\hat{\Theta}\_n=0\\).
- MSE is, \\(0 + \theta^2 \\)

<img src="{{site.url}}/images/math/prob/mse.jpg" width="500">  

- red = sample mean esimator, blue = 0 estimator
  - when \\(\theta\\) is close to 0, 0 estimator is better
  - In Bayesian setting we fix prior to encode such belief/info, but in classical setting we cannot.
- we define \\(\sqrt{\text{var}\hat{\Theta}}\\), stddev of the estimator, as the `standard error`
  - high standard error = our problem/data has high randomness, and our estimate varies a lot (may not be so accurate)
  - small standard erorr = our estimates are concentrated
  - it is highly dependent on problem setting, models, ...


### Confidence Intervals
- the value of an estimator \\(\hat{\Theta}\\) may not be informative enough, does not tell everything
- An \\(1-\alpha\\) `confidence interval` is an interval \\([\hat{\Theta}^-,\hat{\Theta}^+]\\) (we have randomness in it) s.t. \\[P(\hat{\Theta}^- \leq \theta \leq \hat{\Theta}^+) \geq 1-\alpha\quad\quad \forall\\ \theta\\]
- often \\(\alpha=0.05, 0.025, 0.01\\)
- interpretation is subtle
  - __NOT__ a statement about the actual numbers that are reported. It is about the experiment.
  - having a 95% confidence interval = 95% of the estimation carried out will capture the true parameter
  - 특정 실험을 carry out해서 estimation이 \\(C\\)가 나왔다 \\(\quad\rightarrow\quad\\) \\([C-\alpha, C+\alpha]\\) 안에 true parameter가 있을 확률 95%, 90%,...
    - 다른 실험에 \\(C\_1\\)이 나왔다 치면, 그 실험도 동일

#### CI for the estimation of mean

Again, \\(X\_i\\) iid and
\\(\hat{\Theta} = M\_n=\frac{X\_1+...+X\_n}{n}\\)
Then what is 95% confidence interval?
- We know that the distribution of \\(M\_n\\) can be approximated by normal, using `CLT`
- normal tables \\(\Phi(1.96) = 0.975 = 1-0.025\\)(due to symmetry)  
  <img src="{{site.url}}/images/math/prob/normal_table1.jpg" width="500">  
  (blue one = 90% confidence interval)    
  \\[P\left( \frac{\|\hat{\Theta}\_n-\theta\|}{\sigma\sqrt{n}} \leq 1.96 \right) \approx 0.95 (CLT)\\]
  \\[=P\left( \hat{\Theta}\_n - \frac{1.96\sigma}{\sqrt{n}} \leq \theta \leq \hat{\Theta}\_n + \frac{1.96\sigma}{\sqrt{n}} \right) \approx 0.95\\]
- For each estimation (with fixed \\(n\\)) from the estimator, 95% that the true mean \\(\\theta\\) falls into the interval \\((\hat{\Theta}\_n - \frac{1.96\sigma}{\sqrt{n}}, \hat{\Theta}\_n + \frac{1.96\sigma}{\sqrt{n}})\\)
- this is "approximated" (by CLT) confidence interval

#### CI for the mean when sigma is unknown
- option 1 : use upper bound on \\(\sigma\\)
  - If \\(X\_i\\)~Bern, \\(\sigma \leq 1/2\\)
- option 2 : use ad-hoc estimate of \\(\sigma\\)
  - If \\(X\_i\\)~Bern, \\(\sigma=\sqrt{\theta(1-\theta)}\\), so that \\(\hat{\sigma}=\sqrt{\hat{\theta}(1-\hat{\theta})}\\)
- option 3 : use sample mean estimate of the variance
  - it is a expectation \\(E[(X\_i-\theta)^2]\\), so we take several these samples and take average 
  \\[\frac{1}{n}\sum\_{i=1}^n(X\_i-\theta)^2\quad\rightarrow\quad \sigma^2 \text{  by WLLN}\\]  
  - unknown \\(\theta\\)? \\(\rightarrow\\) plug in estimate \\(\hat{\Theta}\_n\\), which gives
  \\[\frac{1}{n}\sum\_{i=1}^n(X\_i-\hat{\Theta})^2 \quad\rightarrow\quad \sigma^2 \\]  
  (composite of continuous functions is continuous, and use convergence of composite functions?)
  - involves two approximations
    - CLT : approximately normal
    - using estimate of \\(\sigma\\)
    - correction for second approximation (`t-tables` instead of normal table)  used when \\(n\\) is small (~30)?
    - sometimes \\(1/n \rightarrow 1/(n-1)\\)?


### Other natural estimators
sample mean estimator \\(\hat{\Theta}=\frac{1}{n}\sum\_{i=1}^nX\_i \\) converges to true mean \\(\theta\_X\\) as \\(n\rightarrow\infty\\), by WLLN.

Note that for any continuous(?) function \\(g\\), if \\(\theta=E[g(X)]\\) then \\(\hat{\Theta} = \frac{1}{n}\sum\_{i=1}^ng(X\_i)\\)

Examples
- \\(v\_X = \text{var}(X) = E[(X-\theta\_X)^2],\quad\quad \hat{v}\_X = \frac{1}{n}\sum\_{i=1}^n(X\_i-\hat{\Theta}\_X)^2\\)
- \\(\text{cov}(X, Y) = E[(X-\theta\_X)(Y-\theta\_Y)],\quad\quad \hat{\text{cov}}(X, Y) = \frac{1}{n}\sum\_{i=1}^n (X-\hat{\theta}\_X)(Y-\hat{\theta}\_Y\\)
- correlation coef also can be approximated
- next steps : find the distribution of \\(\hat{\Theta}\\), \hat{\text{cov}}(X, Y), MSE, 


### MLE

If an parameter is calculated by expectation \\(\theta=E[g(X)]\\), then the natural way of estimating it is taking average 
\\[\hat{\Theta} = \frac{1}{n}\sum\_{i=1}^ng(X\_i)]\\]
In other cases (\\(\theta\\) is not an expectation of something), we will pick \\(\theta\\) tkat __makes data most likely__
\\[\hat{\theta}\_{ML} = \mathop{\text{argmax}}\_\theta p\_X(x;\theta)\\]
In Bayesian (MAP), we wanted to find the peak of \\(p\_{\Theta\|X}(\theta\|x) = p\_{X\|\Theta}p\_{\Theta}(x\|\theta)(\theta)\\)
- technically, if we set the prior to uniform(constant), we are performing MLE
- but philosophically they are different
  - Bayesian : what is the most likely value of \\(\theta\\)
  - MLE : what is the value of \\(\theta\\) that makes my data most likely (least surprising)

Comments on MLE
- maximize \\(p\_X(x;\theta)\\)
  - closed form solution exists, but mostly done numerically
- sound theoritical facts
  - If have \\(n\\) iid data from model \\(p\_X(x;\theta)\\); then under mild assumptions `MLE estimator` is
    - consistent : \\(\hat{\Theta}\_n\rightarrow \theta\\)
    - asymptotically normal \\(\frac{\hat{\Theta}\_n}{\sigma(\hat{\Theta}\_n)}\rightarrow N(0, 1)\\) (CDF convergence) 


#### Examples
Let \\(K\\) be the # of heads of binomial with parameters \\(n\\) (known) and \\(\theta\\) (unknown).
\\[P\_K(k;\theta) = \binom{n}{k}\theta^k(1-\theta)^{n-k})\\]
take log, deriv wrt \\(\theta\\) (is it a convex func?) gives \\(k/\theta-(n-k)/(1-\theta)=0\\)  
Therefore, \\(\hat{\theta}\_{ML} = k/n\\)
- same as `MAP estimator` with uniform prior on \\(\theta\\)