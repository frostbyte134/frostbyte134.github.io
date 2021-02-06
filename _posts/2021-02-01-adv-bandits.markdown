---
layout: post
title:  "Adversarial Bandits"
date:   2021-02-01 09:00:05 +0800
categories: probability
use_math: true
tags: math probability bandit information_theory
---


- <a href="https://banditalgs.com/2016/10/01/adversarial-bandits/" target="_blank">https://banditalgs.com/2016/10/01/adversarial-bandits/</a>  
- <a href="https://www.stat.berkeley.edu/~bartlett/courses/2014fall-cs294stat260/lectures/bandit-adversarial-notes.pdf" target="_blank">https://www.stat.berkeley.edu/~bartlett/courses/2014fall-cs294stat260/lectures/bandit-adversarial-notes.pdf</a>

### Intro

In real world, it is often case that __we cannot expect the reward sequences to be iid.__ (rewards could be correlated over time)  
we take __pragmatic__ (authors says) approach, where 
  - almost nothing is assumed about the mechanism that generates the rewards
  - while still keeping the objective of competing with the __single__ best action, `in hindsight`

This leads to `adversarial bandit` model
- __single__ best action, `in hindsight` : still has the stationarity assumption!
  - thanks to this assumption, the reward still can be kept sublinear (as in stochastic bandits)
  - However the algorithm need to be radically different from the stochastic setting


### Adversarial Bandits Framework

1. An `adversarial bandit env` \\(\mu\\) is given by an __(nonrandom)__ arbitrary sequence of reward vectors \\(x_1,...,x\_n\in [0,1]^K\\)
2. Given the env \\(\mu \in [0,1]^{Kn}\\), our model (not the policy=algorithm) says that in `round` \\(t \leq n\\), the reward of action \\(i\in [K]\\) is just \\(x\_{ti}\\)
   - this is b/c, the reward table is __just a big table of numbers__
   - Since arbitrary sequences are allowed, random reward will not lose generality

The `policy` \\(\pi\\) chooses action \\(i\\) from \\(\nu\\) in a sequential fashion
1. for the 1st round, \\(\pi\\) chooses \\(A\_1\sim p\_1(\cdot)\\) in random
   - the reward \\(X\_1=x_{1,A\_1}\\) is sent back to \\(\pi\\)
   - \\(X\_1\\) is random, since \\(A\_1\\) is random
2. In round \\(t\in [n]\\), \\(A\_t\\) is chosen based on \\(\left(\\{A\_1,X\_1\\},...,\\{A\_{t-1},X\_{t-1}\\} \right)\\)
   - In other words, \\(A\_t\sim \pi\_t\left(\cdot \| A\_1,X\_1,...,A\_{t-1},X\_{t-1}\right)\\)
   - The reward is then \\(X\_t=x\_{t,A\_t}\\)
3. This repeats \\(n\\) times, without any assumption on \\(n\\) a priori.

#### Regret

`Regret`, as a function of \\(\pi,\nu\\) is defined as
\\[R_n(\pi,\nu) = E\left[\max_{i\in [K]} \sum_{t=1}^n x_{ti} – \sum_{t=1}^n x_{t,A_t}\right]\\]
performance is measured by the __expected revenue lost__ when compared with the __best action in hindsight__
- We have randomness in the \\(A\_t\\)

Now, the __quality of a policy__ is defined through its `worst-case regret`
\\[R_n^*(\pi) = \sup_{\nu\in [0,1]^{nK}} R_n(\pi,\nu) \\]

Similar to the stochastic case, the main question is the existence of \\(\pi\\) s.t. the growth of \\(R*\_n(\pi)\\) as a function of \\(n\\) is `sublinear`
\\[R\_n = o(n)\\]


#### Randomizing pi
When
1. \\(\pi\\) is not randomized
2. the opponent (who has freedom to select \\(\nu\\)) knows \\(\pi\\)

Then the opponent can easily make \\(\nu\\) s.t. 
\\[R_n(\pi,\nu)=n\\]
holds, which is the largest possible regret (remember that rewards \\(x\_{ti} \in [0, 1]\\) in the problem setting, by 
- assigning 0 to \\(x\_{ti}\\) which \\(\pi\\) will choose at time \\(t\\)
- and assign 1 for other \\(x\_{tj}, i\neq i\\) in time \\(t\\)

When \\(\pi\\) randomizes, 
1. above strategy does not work anymore
2. \\(\pi\\) will result in policies with good worst-case guarantees
   - How?  The key observation is that the goal of learning is modest:   
      - No environment can simultaneously generate large rewards for some actions and prevent a suitable learner to detect which action these large rewards are associated with.   
      - This is because the rewards are bounded and hence a large total reward means that the reward of the action has to be large often enough, which makes it relatively easy for a learner to identify the action with such large rewards.


### Stochastic and Adversarial Worst-case Regrets

#### Stochastic Worst-case Regret
Recall that <a href="{{site.url}}/probability/2020/12/31/k-armed-bandit.html#def" target="_blank">in stochastic setting,</a> the total expected reward is compared to the maximum expected reward \\(\max\_i \left\\{E[\sum\_{t=1}^n X\_{t, i} ]\right\\} \\) 
\\[R\_n = n\mu^* - E\left[ \sum\_{t=1}^NX\_{t,A\_t} \right] \\]
\\[X\_{t, A\_t}\sim P\_{A\_t},\quad\quad \mu^* = \max\_i E[X\_{t,i}]\\]
(Since we assumed stationarity, we dont need \\(t\\) but it is not omitted for the uniformity in repr)  
We see that,
\\[\begin{align\*} 
R\_n &= \sum\_{t=1}^n \max\_i E[X\_{t,i}] - E\left[ \sum\_{t=1}^n X\_{t,A\_t} \right] \cr
     &=  \max\_i \left\\{\sum\_{t=1}^n E[X\_{t,i}]\right\\} - E\left[ \sum\_{t=1}^n X\_{t,A\_t} \right] \cr
     &=  \max\_i \left\\{\sum\_{t=1}^n E[X\_{t,i}] - E\left[ \sum\_{t=1}^n X\_{t,A\_t} \right] \right\\} \cr
     &= \max_i E\left[ \sum_{t=1}^n X_{t,i} – X_{t,i} \right]
\end{align\*}\\]

#### Adversarial Worst-case Regret

whereas in adversarial case, it is compared to the maximum reward
\\[R_n(\pi,\nu) = E\left[\max_{i\in [K]} \sum_{t=1}^n x_{ti} – x_{t,A_t}\right]\\]


#### Comparison

Since \\[E\left\\{ \max_i \sum_{t=1}^n X_{t,i} \right\\} \ge \max_i E\left\\{ \sum_{t=1}^n X_{t,i}\right\\}\\] (in lhs, we have freedom to change arm through \\(i=1,...,n\\), but in rhs we must slect single arm through the process), we see that
\\[E\left\\{ \max_i \sum_{t=1}^n X_{t,i} – X_{t,A_t} \right\\} \ge \max_i E\left\\{ \sum_{t=1}^n X_{t,i} – X_{t,A_t} \right\\}\\]
where lhs is adversarial case, and rhs is stochasic case.
- remember that the adversarial regret is desinged to have much higher value (we select optimal single arm in hindsight), thus above inequality holds
- an algorithm achieving small adversarial regret will also achieve a small (worst-case) regret on stochastic case
- the lower bound of stochastic worst regret \\(c\sqrt{nK}\\) also becomes the lower bound of adversarial worst retret
   - 나중에 lower bound 읽은 후 ㄱㄱ
   - Gaussn reward를 사용한 증명을 Bernoulli reward로 바꿔야 한다고 함 (0.5 mean Bernoulli)

### EXP3
`EXP3` stands for __Exponential-weight algorithm for Exploration and Exploitation__

In every round, EXP3 does
1. Sample an action \\(A\_t\\) from a previously computed distributions \\(P\_{ti}, i=1,...,K\\)
2. Estimate rewards for all the actions(arms), based on the observed reward \\(X\_t\\)
3. use the estimated rewards to update \\(P\_{ti}\, i\in [K]\\)


<h4 id="sampling_action">Sampling an action </h4>

Sampling from \\(P\_{ti}, i=1,...,K\\) means to select \\(A\_t\\) randomly given the past \\(A\_1,X\_1,...,A\_{t-1}, X\_{t-1}\\).  
This can be implemented by,
1. assume normalized \\(\pi\_t\\) (which generates \\(P\_{ti}\\)), so that \\(\sum\_{j}P\_{tj}=1\\) and the uniform is over \\([0, 1]\\)
2. for each \\(t=1,...,n\\), we have uniform over \\([0, \sum\_{j}P\_{tj}] = [0, 1]\\)
3. choose \\(A\_t=i\\) if the output falls into \\(\left[\sum\_{j=1}^{i-1} P\_{tj},\\ \sum\_{j=i}^{i}P\_{tj}\right)\\)



#### Reward estimation

For some policy \\(\pi=(\pi\_1,...,\pi\_n)\\), let
\\[P\_{ti} = \pi\_t(i\|A\_1,X\_1,...,A\_{t-1}, X\_{t-1}) \\]
- \\(p\_{ti}\\) is random, since given actions and rewards are random.
- we assume that \\(P\_{ti}>0\\) almost surely (which is true in EXP3)

> Perhaps surprisingly, reward estimation also benefits from randomization!

After reward \\(X\_t\\) is observed, we can use the `vanilla importance sampling estinator`
\\[\hat X\_{ti} = \frac{1\\{A\_t=i\\}}{P\_{ti}}X\_t\\]
- \\(\hat X\_{ti} \in \mathbb{R}\\) is random
- is \\(\hat X\_{ti}\\) a good estimator of \\(x\_{ti}\\)?
  - we want it to be an  __unbiased estimator__ of \\(x\_{ti}\\)
  - we want __small variance__

Before showing it, let us introduce a conditional expectation operator \\(E\_t[\cdot]\\) : 
\\[E\_t[Z] := E[Z \|A\_1,X\_1,...,A\_{t-1}, X\_{t-1} ] \tag{3}\\]

1. __expectation__ (to show that it is unbiased)
   Note that, by writing \\(A\_{ti} := 1\\{A\_t = i\\}\\), we see that \\[X\_tA\_{ti} = x\_{t,i}A\+ti\\] (If \\(A\_t=i\\), we get reward \\(x\_{t,i}\\) from the model, which makes \\(X\_t=x\_{ti}\\) so that \\[\hat X\_{ti} =  \frac{A\_{ti}}{P\_{ti}}x\_{t,i}\\]
   Now, thanks to the <a href="#sampling_action" target="_blank">assumption</a> \\(E\_t[A\_{ti}]=P\_{ti}\\) (thus \\(A\_{ti}\\) is the __random__ \\(P\_{ti}\\)), and since \\(P\_{ti}\\) is a function of \\(A\_1,X\_1,...,A\_{t-1}, X\_{t-1}\\) (given those actions and rewards, it is just a scalar), we get
   \\[E_t\left[ \hat{X}_{ti} \right] = E_t\left[ \frac{A\_{ti}}{P\_{ti}} \,x\_{ti} \right] = \frac{x\_{ti}}{P\_{ti}}\,E\_t[A\_{ti}] = \frac{x\_{ti}}{P\_{ti}}\,P\_{ti} = x\_{ti} \\]  
   and also note that (3) shows that \\(E\left[\hat X\_{ti}\right]=x\_{ti}\\), by taking iterated expectation.
2. __variance__ (which we want to be small)  
   Similarly to mean we introduce \\(V\_t[\cdot]\\) and consider
   \\[V\_t[\hat X\_{ti}] = E\_t\left[\left( \hat X\_{ti} - E\_t[\hat X\_{ti}] \right)^2\right] = E\_t[\hat X\_{ti}^2] - E\_t[\hat X\_{ti}]^2\\]  
   which is the variance of \\(\hat X\_{ti}\\) given the pase,, i.e. the variance due to the __randomness of__ \\(A\_t\\) __alone, disregarding the randomness of the history__.  
   - The conditional variance is more meaningful than the full variance as the estimator itself has absolutely no effect on what happened in the past!
   - Why would we want then to account for the variations due to the randomness of the history when discussing the quality of the estimator?

   We already calculated \\(E\_t[\hat X\_{ti}]\\), and since 
   \\[\hat X\_{ti}^2 = \frac{A\_{ti}}{P\_{ti}^2}x\_{ti}^2 \quad\rightarrow\quad E\_t\left[ \hat X\_{ti}^2 \right] = \frac{x\_{ti}^2}{P\_{ti}}\\] so that
   \\[V\_t[\hat X\_{ti}] = x\_{ti}^2\frac{1-P\_{ti}}{P\_{ti}}\\]
   - we see that \\(V\_t[\hat X\_{ti}]\\) __can get large if__ \\(P\_{ti}\\) __is small__ (will be covered later)

skipped the `loss-based importance sampling estimator` (similar one with above)