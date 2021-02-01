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
2. Given the env \\(\mu \in [0,1]^{Kn}\\), the `model` (policy \\(\pi\\)) says that in `round` \\(t \leq n\\), the reward of action \\(i\in [K]\\) is just \\(x\_{ti}\\)
   - this is b/c, the reward table is __just a big table of numbers__
   - Since arbitrary sequences are allowed, random reward will not lose generality

The policy \\(\pi\\) chooses action frol \\(\nu\\) in a sequential fashion
1. for the 1st round, \\(\pi\\) chooses \\(A\_1\sim p\_1(\cdot)\\) in random
   - the reward \\(X\_1=x_{1,A\_1}\\) is sent back to \\(\pi\\)
   - \\(X\_1\\) is random, since \\(A\_1\\) is random
2. In round \\(t\in [n]\\), \\(A\_t\\) is chosen based on \\(\left(\\{A\_1,X\_1\\},...,\\{A\_{t-1},X\_{t-1}\\} \right)\\)
   - In other words, \\(A\_t\sim \pi\_t\left(\cdot \| A\_1,X\_1,...,A\_{t-1},X\_{t-1}\right)\\)
   - The reward is then \\(X\_t=x\_{t,A\_t}\\)
3. This repeats \\(n\\) times, without any assumption on \\(n\\) a priori.

#### Regret

Regret, as a function of \\(\pi,\nu\\) is defined as
\\[R_n(\pi,\nu) = \EE{\max_{i\in [K]} \sum_{t=1}^n x_{ti} – \sum_{t=1}^n x_{t,A_t}}\\]
performance is measured by the __expected revenue lost__ when compared with the __best action in hindsight__


__Now__, the quality of a policy is defined through its `worst-case regret`
\\[R_n^*(\pi) = \sup_{\nu\in [0,1]^{nK}} R_n(\pi,\nu) \\]

Similar to the stochastic case, the main question is the existence of \\(\pi\\) s.t. the growth of \\(R*\_n(\pi)\\) as a function of \\(n\\) is `sublinear`
\\[R\_n = o(n)\\]


#### Randomizing pi
When
1. \\(\pi\\) is not randomized
2. the opponent (who has freedom to select \\(\nu\\)) knows \\(\pi\\)

Then the opponent can easily make \\(nu\\) s.t. 
\\[R_n(\pi,\nu)=n\\]
holds, which is the largest possible regret in the problem setting.

When \\(pi\\) randomizes, 
1. above strategy does not work anymore
2. \\(\pi\\) will result in policies with good worst-case guarantees
   - How?  The key observation is that the goal of learning is modest:   
      - No environment can simultaneously generate large rewards for some actions and prevent a suitable learner to detect which action these large rewards are associated with.   
      - This is because the rewards are bounded and hence a large total reward means that the reward of the action has to be large often enough, which makes it relatively easy for a learner to identify the action with such large rewards.


### Relation between Stochastic and Adversarial bandits (in Rewards)