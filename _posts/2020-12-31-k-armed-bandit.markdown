---
layout: post
title:  "K-armed Stochastic (Stationary) Bandit"
date:   2020-12-31 08:00:05 +0800
categories: probability
use_math: true
tags: math probability bandit basic_regret_decomposition_identity
---

> <a href="https://banditalgs.com/2016/09/04/stochastic-bandits-warm-up/" target="_blank">https://banditalgs.com/2016/09/04/stochastic-bandits-warm-up/</a>  
  <a href="https://banditalgs.com/2016/09/14/first-steps-explore-then-commit/#thm_subgaussian" target="_blank">https://banditalgs.com/2016/09/14/first-steps-explore-then-commit</a>


TODO
- review measure theory part of <a href="https://banditalgs.com/2016/09/04/stochastic-bandits-warm-up/" target="_blank">this page</a> after the RUDIN review


### (somewhat informal?) Problem Formulation
1. `Environment` = \\(K\\) distribution over the reals \\[P\_1,...,P\_K\\]  
   Note that these distributions are stationary, fixed over all the time steps
2. For each rounds \\(t = 1, 2, ...\\)
   - based on the past observations, the `learner` chooses an `action` \\(A\_t\\) \\[A\_t \in [K] := {1,...,K}\\]  
   - given \\(A\_t\\), the environment generates a __random__ `reward` \\[X\_t \sim P\_{A\_t}\\]
     when \\(A\_t = k\\), \\(X\_t\sim P\_k\\)
3. The Learner's goal is to maximize the random variable \\[S\_n := \sum\_{t=1}^nX\_t\\]  
   - many criterias for maximization. Ex) maximize \\(E[S\_n]\\)
   - didn't specified \\(n\\) yet - many choices (fixed, \\(\infty, \forall n\\))
4. Let
   \\[\mu_k = \int\_{-\infty}^{\infty}xP\_k(x)dx\\]
   \\[\mu^* =\max\_k\mu\_k\\]
   based on it, we can define
   \\[\vec{\Delta}\_k= \mu^* -\mu\_k\\]
   - expected amount of lost value when choosing action \\(k\\)
   - referred as `action gap`, `sub-optimality gap` at action \\(k\\)
6. Now we can define the `total regret` as
   \\[R\_n=n\mu^* -E[{\textstyle\sum}\_{t=1}^NX\_t]\\]
  - "the difference between the rewards you would expect to obtain if you choose the optimal action in every round, and the rewards you actually expect to see by using your policy"

### Basic Regret Decomposition Identity Lemma

Define
\\[T\_k(n) = \sum\_{t=1}^n 1\\{A\_t=k\\}\\]
- for \\(n\\) trial, counting the event \\(A\_t=k\\)
- is a random variable

> Now we can have the __basic regret decomposition identity lemma__
\\[R\_n = \sum\_{k=1}^K\vec{\Delta}\_kE[T\_k(n)]\\]
\\[ = \sum\_{k=1}^K\left((\mu^* -\mu\_k)\mathbb{E}\left[\sum\_{t=1}^n 1\\{A\_t=k\\}\right] \right)\\]

- regret in time duration \\(n\\) = loop for all distribution \\(k\\), calculate the expected number of event that the event \\(k\\) is selected for the time-duration \\(n\\), multiply them with \\(\mu^* - \mu\_k\\) and sum them all up.

__Proof__  
For any fixed \\(t\\), we have \\[\sum\_{k=1}^{K} 1\\{A\_t=k\\} = 1\\]
Hence \\[S\_n := \sum\_{t=1}^nX\_t = \sum\_{t=1}^n\sum\_{k=1}^K X\_t1\\{ A\_t=k \\}\\]
\\[n\mu^* = \sum\_{t=1}^n \mu^*  = \sum\_{t=1}^n\sum\_{k=1}^K \mu^* \\]
which gives
\\[ R\_n=n\mu^*  - E[S\_n] = \sum\_{k=1}^K\sum\_{t=1}^n E[(\mu^* -X\_t) 1\\{ A\_t=k \\} ] \tag{1}\\]
Now consider the inner term
\\[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} ]\\]
now using <a href="{{site.url}}/probability/2020/11/30/sum-of-ind-normals.html" target="_blank">iterated expectation,</a> (actually \\(A\_t\\) is __not random__ here, so the below proof can be shorten significantly, but anyway for more generality)
\\[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} ] = E\left[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} \|A\_t]\right]\\]
since it holds that
\\[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} \| A\_t=j] =  1\\{ A\_t=k \\}E[(\mu^* -X\_t) \| A\_t=j]\\]
\\[
\begin\{align\*\}  
E[(\mu^* -X\_t) 1\\{ A\_t=k \\} \| A\_t] &= 1\\{ A\_t=k \\}E[(\mu^* -X\_t) \| A\_t] \cr
                                        &= 1\\{ A\_t=k \\}(\mu^* -E[X\_t\| A\_t])  \cr
                                        &= 1\\{ A\_t=k \\}(\mu^* -\mu\_{A\_t})  \cr
                                        &= 1\\{ A\_t=k \\}(\mu^* -\mu\_k)  
\end\{align\*\}  
\\]
the iterated expectation becomes
\\[E\left[ 1\\{ A\_t=k \\}E[(\mu^\* -X\_t) \| A\_t] ] = E[1\\{ A\_t=k \\}(\mu^\* -\mu\_k) \right]\\]
\\[ = E\left[ 1\\{ A\_t=k \\} \right] ( \mu^{\*} - \mu\_k ) \\]

the equation (1) becomes, using the linearity of expectation
\\[\sum\_{k=1}^K\sum\_{t=1}^n E[1\\{ A\_t=k \\}] (\mu^{\*} -\mu\_k)\\]
\\[= \sum\_{k=1}^K E\left[\sum\_{t=1}^n 1\\{ A\_t=k \\}\right] (\mu^{\*} -\mu\_k)\\]
\\[= \sum\_{k=1}^K E[T\_k(n)] (\mu^{\*} -\mu\_k)\\]
QED
- instead of using iterated expectation, we can factor the joint pdf of random variables \\(X\_t\\) and \\(A\_t\\) into \\(P(X\_t\|A\_t)P(A\_t)\\) (algebraic)


### concentration of measure and Concentration Inequality
<a href="https://banditalgs.com/2016/09/14/first-steps-explore-then-commit/#thm_subgaussian" target="_blank">https://banditalgs.com/2016/09/14/first-steps-explore-then-commit</a>

Let \\(X\_i\\) be a iid RV with mean \\(\mu\\) and var \\(\sigma^2\\).
The <a href="{{site.url}}/probability/2020/12/10/rv-convergence.html#sample_mean" target="_blank">Sample mean</a>
\\[\text{Sample mean  } M\_n:=\frac{X\_1+...+X\_n}{n}\\]
has __mean__ \\(\mu\\), __variance__ \\(\sigma^2/n\\).

and using the <a href="{{site.url}}/probability/2020/12/10/rv-convergence.html#chevyshev" target="_blank">Chevyshev inequality,</a> 
\\[P[ \|M\_n-\mu\|\geq \epsilon ] \leq \frac{\text{var}}{\epsilon^2} = \frac{\sigma^2}{n\epsilon^2}\\]
converges to 0 in probability as \\(n\rightarrow \infty\\)

However, what can we say about the `tail probability`? (=distribution of the error)
\\[P(\|M\_n - \mu \| \geq \epsilon)\\]


#### Why we need subguassianity and concentration inequality?
1. using the <a href="{{site.url}}/probability/2020/12/10/rv-convergence.html#chevyshev" target="_blank">Chevyshev inequality</a>  directly gives \\[P(\|M\_n-\mu\| \geq \epsilon) \leq \frac{\sigma^2}{n\epsilon^2}\\]  
   This is easily drawn, but since we only used the mean and var as the input information, it is often too loose.
2. using the <a href="{{site.url}}/probability/2020/12/11/clt.html#clt" target="_blank">central limit theorem</a> says that \\(M\_n/\sqrt{n\} \sim N(0, \sigma)\\). This would suggest (as in the <a href="https://banditalgs.com/2016/09/14/first-steps-explore-then-commit/#thm_subgaussian" target="_blank">link</a>)
   \\[P(\mu\_n \geq \mu + \epsilon) = P(\frac{S\_n}{\sqrt{n}} \geq \epsilon\sqrt{n})\\]
   \\[\approx \int^\infty_{\epsilon \sqrt{n}} \frac{1}{\sqrt{2\pi \sigma^2}} \exp\left(-\frac{x^2}{2\sigma^2}\right) dx\\]
   which can be easily bound by using
   \\[\int^\infty_{\epsilon \sqrt{n}} \frac{1}{\sqrt{2\pi \sigma^2}} \exp\left(-\frac{x^2}{2\sigma^2}\right) dx\\]
   \\[\leq \frac{1}{\epsilon \sqrt{2n\pi \sigma^2}} \int^\infty_{\epsilon \sqrt{n}} x \exp\left(-\frac{x^2}{2\sigma^2}\right) dx \\] 
   \\[\sqrt{\frac{\sigma^2}{2\pi n \epsilon^2}} \exp\left(-\frac{n\epsilon^2}{2\sigma^2}\right)\\]
   most of time this bound is stronger than 1, but this is __asymtotic__ : not easy to apply when \\(n\\) is fixed
   - "hence it is vital to take a closer look at measure concentration and prove a “version” of the CLT that is true even for small values of \\(n\\)"


