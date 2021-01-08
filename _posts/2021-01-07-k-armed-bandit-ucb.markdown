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
- Then a good candidate for the __largest plausible estimate of the mean for arm__ \\(i\\) is
  \\[\hat{\mu}\_i(t-1) + \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) }\\]
  the algorithm chooses the action \\(i\\) which maximizes the above quantity
- small \\(\delta\\) : optimistic algorithm  
  large \\(\delta\\) : the optimism is less certain
- \\(1-\delta\\) := `confidence level`. different choices -> different algs with different analysis
- For now, we choose \\[\frac{1}{\delta} = f(t) := 1+t\log^2(t),\\ \\ t=1,2,...\\]  
  - \\(1/\delta\\) is time dependent, decreases faster than \\(1/t\\).
  - __if__ \\(\delta\\) __is time dependent, then so as the__ \\(\epsilon\\)

In summary, with \\(\delta\\) and the `index` (=\\( \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) } \\)) defined above,
\\[A\_t=
\begin{cases}
    \mathop{\text{argmax}}\_i\left( \hat{\mu}\_i(t-1) + \sqrt{ \frac{2\log f(t)}{T\_i(t-1)} } \right) & \text{if  } t > K \cr
    t & \text\{o.w \},
\end{cases}   
\\]
- index : an `index algorithm` chooses the arm in each round that maximizes the `index`.
  - in the case of `UCB`, index = empirical mean + confidence width

#### Analysis

Suppose that wlog, the arm \\(1\\) is chosen much more frequently then others.  
Then we have \\(\hat{\mu}\_1(t-1)\rightarrow \mu\_1, \text{ and } \frac{2}{n}\rightarrow 0\\) so that
\\[\hat{\mu}\_1(t-1) + \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) } \approx \mu\_1\\]

In this case, the algorithm better be confident that the other arms are indeed worse.
  - This naturally leads to the confidence interval
    \\[\hat \mu_i(t-1) + \sqrt{\frac{2}{T_i(t-1)} \log\left(\frac{1}{\delta}\right)} \leq \mu_1\\]   
  - it will only happen when and \\(\hat \mu_i(t-1) \ll \mu\_i\\) and \\(0 \ll T\_i(t-1)\\) 

If (sadly) the arm \\(1\\) was not an optimal arm, i.e. \\(1 \neq \mathop{\text{argmax}}\mu\_i\\), and wlog let arm \\(i\\) was optimal.  
Then the algorithm was wrong, then for the arm \\(i\\) we have
\\[\hat \mu_i(t-1) + \sqrt{\frac{2}{T_i(t-1)} \log\left(\frac{1}{\delta}\right)} \leq \mu_1 \leq \mu\_i \\]
__For the optimal arm, its upper bound of confidence interval is even lower than its true mean__  

   

### UCB Regret Bound

> __Theorem (UCB Regret)__ : The regret of UCB is bounded by 
  \\[R_n \leq \sum_{i:\Delta_i > 0} \inf_{\epsilon \in (0, \Delta_i)} \Delta_i\left(1 + \frac{5}{\epsilon^2} + \frac{2}{(\Delta_i – \epsilon)^2} \left( \log f(n) + \sqrt{\pi \log f(n)} + 1\right)\right)\\]   
  Furthermore,  
  \\[ \mathop{\text{limsup}}\_{n \rightarrow \infty }  \frac{ R\_n }{ \log(n) } \leq \sum_{i : \Delta_i > 0} \frac{2}{\Delta_i}\\]


1. Remember that \\(f(t) = 1+t\log^2(t)\\), so that \\[\log f(n) \approx \log(n) + 2\log\log(n)\\]  
  - In `ETC`, we obtained \\(\log n\\) bound when we set \\(K=2\\) and __used unreachable knowledge__ of \\(\Delta\_2\\).  
  - In `UCB`, we dont need such infeasible knowledge
2. 
__Proof__
1. 

By choosing \\(\epsilon=\Delta\_i/2\\), for analysis purpose we see that

> __Corollary (UCB Simplified Regret)__ : The regret of UCB is bounded by (somewhat loosely, since we fixed \\(\epsilon\\))  
  \\[R_n \leq \sum_{i:\Delta_i > 0} \left(\Delta_i + \frac{1}{\Delta_i}\left(8 \log f(n) + 8\sqrt{\pi \log f(n)} + 28\right)\right)\\]
  and in particular, there exists \\(C>0\\) s.t. \\(\forall\\ \\ n \geq 2\\),
  \\[R_n \leq \sum_{i:\Delta_i>0} \left(\Delta_i + \frac{C \log n}{\Delta_i}\right)\\]
