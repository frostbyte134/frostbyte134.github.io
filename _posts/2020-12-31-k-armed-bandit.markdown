---
layout: post
title:  "K-armed Stochastic (Stationary) Bandit"
date:   2020-12-31 08:00:05 +0800
categories: probability
use_math: true
tags: math probability bandit basic_regret_decomposition_identity
---

> <a href="https://banditalgs.com/2016/09/04/stochastic-bandits-warm-up/" target="_blank">https://banditalgs.com/2016/09/04/stochastic-bandits-warm-up/</a>


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
   \\[R\_n=n\mu^* -E[\sum\_{t=1}^NX\_t]\\]
  - "the difference between the rewards you would expect to obtain if you choose the optimal action in every round, and the rewards you actually expect to see by using your policy"

### Basic Regret Decomposition Identity Lemma

Define
\\[T\_k(n) = \sum\_{t=1}^n 1\\{A\_t=k\\}\\]
- for \\(n\\) trial, counting the event \\(A\_t=k\\)
- is a random variable

> Now we can have the __basic regret decomposition identity lemma__
\\[R\_n = \sum\_{k=1}^K\vec{\Delta}\_kE[T\_k(n)]\\]
\\[ = \sum\_{k=1}^K\left((\mu^* -\mu\_k)\mathbb{E}\left[\sum\_{t=1}^n 1\\{A\_t=k\\}\right] \right)\\]

- regret = loop for all distribution \\(k\\), calculate the expected number of event that the event \\(k\\) is selected for the time-duration \\(n\\), multiply them with \\(\mu^* - \mu\_k\\) and sum them all up.

__Proof__  
For any fixed \\(t\\), we have \\[\sum\_{k=1}^{K} 1\\{A\_t=k\\} = 1\\]
Hence \\[S\_n := \sum\_{t=1}^nX\_t = \sum\_{t=1}^n\sum\_{k=1}^K X\_t1\\{ A\_t=k \\}\\]
\\[n\mu^* = \sum\_{t=1}^n \mu^*  = \sum\_{t=1}^n\sum\_{k=1}^K \mu^* \\]
which gives
\\[ R\_n=n\mu^*  - E[S\_n] = \sum\_{k=1}^K\sum\_{t=1}^n E[(\mu^* -X\_t) 1\\{ A\_t=k \\} ] \tag{1}\\]
Now consider the inner term
\\[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} ]\\]
now using <a href="{{site.url}}/probability/2020/11/30/sum-of-ind-normals.html" target="_blank">iterated expectation,</a>
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


