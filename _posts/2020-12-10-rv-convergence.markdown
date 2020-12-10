---
layout: post
title:  "Convergence and the Weak Law of Large Numbers"
date:   2020-12-07 08:00:05 +0800
categories: probability
use_math: true
tags: math probability bayesian
---

> <a href="https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-ii-inference-limit-theorems/" target="_blank">part-ii-inference-limit-theorems</a>

- <a href="{{site.url}}/probability/2019/02/19/estimating-rv-with-expectations.html" target="_blank">Preliminary - Markov inequality, Chevyshev inequality</a>

### Markov Inequality
use a bit of information about a distribution to learn something about probabilities of "extreme events" (tail probability)

`Markov Inequality` : If \\(X\geq 0\\) and \\(a>0\\), then \\[P(X\geq a) \leq \frac{E[X]}{a}\\]


1. Example: \\(X\sim \exp(1)\\) : \\(P[X\geq a] \leq 1/a\\).
   \\(P[X\geq a]=e^{-a}\\), so it is not a good bound (Chevyshev is better)


### Chevyshev Inequality
RV \\(X\\), with finite \\(\mu\\) and variance \\(\sigma^2\\)
- IF the variance is small, then \\(X\\) is unlikely to be too far from the mean
\\[P( \|X-\mu\|\geq c )\leq \frac{sigma^2}{c^2}\\]

1. Replace \\(c\\) with \\(\sigma^2k^2\\). Then \\[P(\|X-\mu\|\geq k\sigma)\leq \frac{1}{k^2}\\]
   __Probability that__ \\(X\\) __goes__ \\(k\\) __times standard deviation from the mean is bounded by__ \\(1/k^2\\).  
2. Example: \\(X\sim \exp(1)\\).  
   To compare with Markov inequality, we will calculate \\(P[X\geq a] \\) using CHevyshev inequality
   \\[P[X\geq a] = P[X-a\geq a-1] \leq P[\|X-1\|\geq a-1] \leq \frac{1}{(a-1)^2}\\]
   is bit stronger than the Markov inequality, since it __uses additional information (variance)__

### Weak Law of Large Numbers (WLLN)
Let \\(X\_1,X\_2,...\\) : i.i.d with finite mean \\(\mu\\) and variance \\(\sigma^2\\).

Define \\[\text{Sample mean : } M\_n:=\frac{X\_1+...+X\_n}{n}\\]
__which is a random variable__, is the most simplest and natural method to estimate true mean \\(\mu=E[X\_i]\\).

\\(E[M\_n]\\) : involves two averaging
1. averaging using \\(\frac{1}{n}\\)
2. averaging with \\(E\\), which involves all ocassions


Now
\\[E[M\_n] = \frac{E[X\_1+...+X\_n]}{n} = \frac{n\mu}{n} = \mu\\]
\\[\text{var}[M\_n] = \frac{\text{var}[X\_1+...+X\_n]}{n^2} = \frac{n\sigma}{n^2} = \frac{\sigma^2}{n}\\]
Using Chevyshev inequality

\\[P[ \|M\_n-\mu\|\geq \epsilon ] \leq \frac{\text{var}}{\epsilon^2} = \frac{\sigma^2}{n\epsilon^2}\\]
which converges to 0 as \\(n\rightarrow \infty\\)


Interpretation
- One experiment, Many measurements \\(X\_i=\mu+W\_i\\)
  - \\(W\_i\\) : iid measurement noise, \\(E[W\_i]=0\\)
- sample mean \\(M\_n\\) is unlikely to be far off from the true mean \\(\mu\\)



### The Pollstaer's Problem
- let \\(p\\) be the fraction of population that will vote "yes" in a referendum
  - we want to estimate \\(p\\)
- Choose \\(i\\) th person uniformly, independently, and define a RV \\(X\_i\\) by
  \\[ X\_i=
  \begin{cases}
    1 & \text\{if yes,\} \cr
    0 & \text\{if no.\}
  \end{cases}  
  \\]
- No way to exactly calculate \\(p\\)
  - Then, \\(M\_n = (X\_1+...+X\_n)/n\\) is the fraction of yes in our sample.
  - prefer small error, e.g. \\(\|M\_n-p\| < 0.001\\) - no way
  - But can gurantee the probability \\[P[\|M\_{10,000}-p] \leq \frac{signa^2}{n\epsilon^2} = \frac{p(1-p)}{10^4 10^{-4}} \leq \frqc{1}{4}\\]  
    (last inequality comes from the fact that \\(p(1-p)\\) is concave, maximum at \\(p=1/2\\))  
    "probability that the difference of estimation is larget than 0.01 is less than 25%"  
  - if we want 5% of such number, solve \\[\frac{1/4}{n10^{-4}}\leq \frac{5}{100} \quad\rightarrow\quad n>> \frac{10^6}{20} = 50,000\\]
  - we have two parameters here  
      1. `accuracy` 1%
      2. `confidence` 5%
  - accuracy of 0.01 is somewhat high. Many polls assumes 3%~5% accuracy
  - more better inequality (Cramer-rao?) gives much smaller \\(n\\) (rather than 50,000)
