---
layout: post
title:  "K-armed Stochastic (Stationary) Bandit 2 - UCB"
date:   2021-01-07 08:00:05 +0800
categories: probability
use_math: true
tags: math probability bandit basic_regret_decomposition_identity
---

`UCB` = __Upper Confidence Bound__ algorithm

- <a href="https://banditalgs.com/2016/09/18/the-upper-confidence-bound-algorithm/" target="_blank">https://banditalgs.com/2016/09/04/stochastic-bandits-warm-up/</a>  


> <a href="https://banditalgs.com/2016/09/18/the-upper-confidence-bound-algorithm/" target="_blank">"The algorithm is based on the principle of optimism in the face of uncertainty"</a>  


### Upper Confidence Bound

Recall that if \\(X\_1,...,X\_n\\) are independent, and 1-subgaussian and \\(\hat{\mu}=\sum\_{t=1}^n X\_t/n\\). Then with the <a href="{{site.url}}/probability/2020/12/31/k-armed-bandit.html#hoefding" target="_blank">Hoeffding's bound</a>, 
\\[P(\hat{\mu} \geq \epsilon) \leq \exp\left( -\frac{n\epsilon^2}{2} \right)\\]
Equating the rhs with \\(\delta\\) and solve for \\(\epsilon\\) leads to
\\[\delta = \exp\left( -\frac{n\epsilon^2}{2} \right)\\]
\\[\sqrt{ -\frac{2}{n}\ln\delta } = \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) } = \epsilon\\]
so that
\\[P\left(\hat{\mu} \geq \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) } \right) \leq \delta\\]

__as large as plausibly possible__
- The learner decides the \\(A\_t\\) by looking at \\(T\_i(t-1)\\) samples from each arm \\(i\\), and the `empirical mean of rewards` 
  \\[\hat{\mu}\_i(t-1)  := \frac{1}{T\_i(t-1)}\sum\_{s=1}^t1\\{A\_s=i\\} X\_s\\]
- Then a good candidate for the `largest plausible estimate` of the mean for arm \\(i\\) is
  \\[\hat{\mu}\_i(t-1) + \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) }\\]
  the algorithm chooses the action \\(i\\) which maximizes the above quantity
- small \\(\delta\\) : optimistic algorithm  
  large \\(\delta\\) : the optimism is less certain
- \\(1-\delta\\) := `confidence level`. different choices -> different algs with different analysis
- For now, we choose \\[\frac{1}{\delta} = f(t) := 1+t\log^2(t),\\ \\ t=1,2,...\\]  
  - \\(1/\delta\\) is time dependent, decreases faster than \\(1/t\\).

In summary, with \\(\delta\\) and the `index` (=\\( \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) } \\)) defined above,
\\[A\_t=
\begin{cases}
    \mathop{\text{argmax}}\_i\left( \hat{\mu}\_i(t-1) + \sqrt{ \frac{2\log f(t)}{T\_i(t-1)} } \right) & if t > K \cr
    t & \text\{o.w \},
\end{cases}   
\\]
- index : an `index algorithm` chooses the arm in each round that maximizes the `index`.
  - in the case of `UCB`, index = empirical mean + confidence width

### UCB regret