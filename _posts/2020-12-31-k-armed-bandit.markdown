---
layout: post
title:  "K-armed Stochastic (Stationary) Bandit 1 - basics and ETC"
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
   - referred as `action gap`, `suboptimality gap` at action \\(k\\)
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

- regret in time duration \\(n\\) = loop for all distribution \\(k\\), calculate the expected number of event that the event \\(A\_t=k\\) is selected for the time-duration \\(t=1,...,n\\), multiply them with \\(\mu^* - \mu\_k\\) and sum them all up.

__Proof__  
For any fixed \\(t\\), we have \\[\sum\_{k=1}^{K} 1\\{A\_t=k\\} = 1\\]
Hence \\[S\_n := \sum\_{t=1}^nX\_t = \sum\_{t=1}^n\sum\_{k=1}^K X\_t1\\{ A\_t=k \\}\\]
\\[n\mu^\* = \sum\_{t=1}^n \mu^\*  = \sum\_{t=1}^n\sum\_{k=1}^K \mu^* 1\\{ A\_t=k \\} \\]
which gives
\\[ R\_n=n\mu^\*  - E[S\_n] = \sum\_{k=1}^K\sum\_{t=1}^n E[(\mu^\* - X\_t) 1\\{ A\_t=k \\} ] \tag{1}\\]
Now consider the inner term
\\[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} ]\\]
now using <a href="{{site.url}}/probability/2020/11/30/sum-of-ind-normals.html" target="_blank">iterated expectation,</a>
   - Even when using deterministic strategy, previous rewards \\(X\_j,j<t\\) is random so \\(A\_t\\) which depends on them is also random
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
- instead of using iterated expectation, we can factor the joint pdf of random variables \\(X\_t\\) and \\(A\_t\\) into \\(P(X\_t\|A\_t)P(A\_t)\\) (more algebraic)


### Concentration of Measure and Concentration Inequality
<a href="https://banditalgs.com/2016/09/14/first-steps-explore-then-commit/#thm_subgaussian" target="_blank">https://banditalgs.com/2016/09/14/first-steps-explore-then-commit</a>

Let \\(X\_i\\) be a iid RV with mean \\(\mu\\) and var \\(\sigma^2\\).
The <a href="{{site.url}}/probability/2020/12/10/rv-convergence.html#sample_mean" target="_blank">Sample mean</a>
\\[\text{Sample mean  } M\_n:=\frac{X\_1+...+X\_n}{n}\\]
has __mean__ \\(\mu\\), __variance__ \\(\sigma^2/n\\).

and using the <a href="{{site.url}}/probability/2020/12/10/rv-convergence.html#chevyshev" target="_blank">Chevyshev inequality,</a>  <a href="{{site.url}}/probability/2019/02/18/estimating-rv-with-expectations.html" target="_blank">(proof of markov, Chevyshev)</a>

(ch)
\\[P[ \|M\_n-\mu\|\geq \epsilon ] \leq \frac{\text{var}}{\epsilon^2} = \frac{\sigma^2}{n\epsilon^2}\\]
converges to 0 in probability as \\(n\rightarrow \infty\\)

However, what can we say about the `tail probability`? (=distribution of the error, amount of probability that our estimation is far away from the true mean)
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


#### Subgaussianity

> __Definition__ : A random variable \\(X\\) is \\(\sigma^2\\)-subgaussian if \\(\forall\\ \lambda \in \mathbb{R}\\) it holds that
   \\[E[\exp(\lambda X)]\leq \exp(\frac{\lambda^2\sigma^2}{2})\\]

- The function \\(M\_X(\lambda):=E[\exp(\lambda X)]\\) is called the <a href="{{site.url}}/probability/2020/12/02/mgf.html" target="_blank">moment generating function</a>

__Lemma__ : If \\(X\\) is \\(\sigma^2-\\)subgaussian, and \\(X\_1,X\_2\\) are independent and \\(\sigma\_1^2,\sigma\_2^2-\\)subgaussian respectively then  
1. \\(V[X] \leq \sigma^2\\)
   - use taylor expansion on both side, compare \\(\sigma^2\\) term
2. \\(cX\\) is \\(c^2\sigma^2-\\)subgaussian \\(\forall\\ c\in\mathbb{R]}\\)
   - directly use MGF
3. \\(X\_1+X\_2\\) is \\((\sigma\_1^2+\sigma\_2^2)-\\)subgaussian
   - in independent case, easily proved using \\(E[XY] = E[X]E[Y]\\)
   - if not independent, \\(X\_1+X\_2\\) is \\((\sigma\_1+\sigma\_2)^2\\). __TODO: add proofs?__

#### Concentration inequality

> __Theorem__ : If \\(X\\) is \\(\sigma^2-\\)subgaussian, then \\(P(X\geq \epsilon) \leq \exp(-\frac{\epsilon^2}{2\sigma^2})\\)

__proof__ - use a generic approach called `Chernoff's method` (TODO: add link, post?).  
Let \\(\lambda>0\\) be some constant, which will be fixed later. Then
\\[
\begin{align\*} 
P(X \geq \epsilon)
&= P(\exp\left(\lambda X\right)) \geq \exp\left(\lambda \epsilon\right) \cr
& \leq E[\exp\left(\lambda X\right)] \exp\left(-\lambda \epsilon\right) \tag{Markov’s inequality} \cr 
& \leq \exp\left(\frac{\lambda^2 \sigma^2}{2} – \lambda \epsilon\right) \tag{Def. of subgaussianity} 
\end{align\*}   
\\]

We can choose \\(\lambda\\) to minimize \\(\frac{\lambda^2 \sigma^2}{2} – \lambda \epsilon\\), which is convex quadratic. We choose \\(\lambda=\epsilon/\sigma^2\\) by the optimality condition.

Using this inequality, we can bound the error probability

#### Hoeffding's bound

Combining the lemma,
1. \\(X\_i-\mu\\) are \\(\sigma^2-\\)gaussian, and \\(X\_i\\)s are independent
   - \\(M\_n - \mu = \sum\_{i=1}^{n}(X\_i-m\_n)\\) is \\(\sigma^2/n-\\)subgaussian.
2. Then by the concentration inequality, we can bound the tail probability of \\(M\_n\\)

> Corollary (Hoeffding's bound) : Assume that \\(X\_i-\mu\\) are independent, \\(\sigma^2-\\)subgaussian RVs. Then their sample mean \\(M\_n\\) satisfies
\\[P( \| M\_n - \mu \| \geq \epsilon) \leq \exp\left( -\frac{n\epsilon^2}{2\sigma^2} \right)\\]


By the inequality \\[\exp(-x) \leq \frac{1}{ex}\\] which holds when \\(x\geq 0\\), we see that
\\[P( \| M\_n - \mu \| \geq \epsilon) \leq \exp\left( -\frac{n\epsilon^2}{2\sigma^2} \right) \leq \frac{2\sigma^2}{en\epsilon^2}\\]
- for very small \\(\epsilon\\), the above inequality is much stronger than the one obtained by Chevyshev
- and is exponentially smaller if \\(n\epsilon^2\\) is large, relative to \\(\sigma^2\\)

#### Example of Subgaussian RVs
- \\(X\sim N(0, \sigma^2\\) then \\(X\\) is \\(\sigma^2-\\)subgaussian
- If \\(E[X] = 0,\\ \|X\|\leq B\\) almost surely for some \\(B\geq 0\\), then \\(X\\) is \\(B^2-\\)subgaussian
  - ex) X is a shifted bernoulli with \\(P[X=1-p]=p,\quad P[X=-p]=1-p\\) - \\(X\\) is \\(1/4-\\)subgaussian


### Explore-Then-Commit strategy

Remarks
- we assume the __noise__ for all rewares \\(X\_i\\) is 1-subgaussian
  - just to avoid writing too many \\(\sigma^2\\)
  - all the other algorithms requires the knownledge of \\(\sigma^2\\), but this does not (need confirm)

The `ETC` algorithm
1. uses predefined parameter \\(m\\) : # of times each arm will be explored before commiting
2. Thus it will __explore__ \\(mK\\) rounds before choosing a single action for the remaining \\(n-mK\\) rounds. Formally,
\\[A\_t=
\begin{cases}
    i & \quad \text\{if \}  (t \text{mod} K) + 1 = i \text{ and } t\leq mK; \cr
    \mathop{\text{argmax}}\_i \hat{\mu}\_i(mK) & \quad \text\{if \} t > mk,
\end{cases}   
\\]

where
1. ties (even) in the argmax handled in a fixed arbitrary way
2. \\(\hat{\mu}\_i(mK)\\) is the empirical mean of arm \\(i\\) up to round \\(t\\):
   \\[\hat{\mu}\_i(mK):= \frac{1}{T\_i(t)}\sum\_{s=1}^t1\\{A\_s=i\\} X\_s\\]
   (remember that \\(T\_i(t)\\) is the # of times arm \\(i\\) was chosen till time \\(t\\))
3. in `ETC`, \\(T\_i(t)\\) is deterministic for \\(t\leq mK\\), and \\(\hat{\mu}\_i(mK)\\) is never used in \\(t>mK\\)
   - Thus, \\(\hat{\mu}\_i(mK)\\) has single source of randomness, easy to analysize the bound we showed above
     - In other algorithms which also uses \\(\hat{\mu}\_i(mK)\\), \\(T\_i(t)\\) could be random
   - \\(\hat{\mu}\_i(mK)\\) is the sample mean of IID RVs

#### Regret Analysis of ETC
<a href="http://www.ds3-datascience-polytechnique.fr/wp-content/uploads/2017/08/2017_08_31-09_01_Csaba_Szepesvari_Bandits_part1.pdf" target="_blank">http://www.ds3-datascience-polytechnique.fr/wp-content/uploads/2017/08/2017_08_31-09_01_Csaba_Szepesvari_Bandits_part1.pdf</a>

recall the basic regret decomposition lemma,
\\[R\_n = \sum\_{t=1}^K\vec{\Delta}\_{A\_t}E[T\_k(n)]\\]
However, we can calculate it with repsect to \\(n\\) rounds
1. For the first \\(mK\\) rounds, we will exploit \\(K\\) arms deterministically. No randomness here, and \\(E[T\_k(n)]=m\\)
   \\[R\_{mK}=m\sum\_{i=1}^{K}\vec{\Delta}\_i\\]
2. and then for the remaining \\(n-mK\\) times, \\(E[T\_k(n)]\\) = (probability that arm \\(k\\) is selected) * (# of times the arm will be used if selected, \\(n-mk\\)).
   \\[R\_{n-mK} = (n-mK)\sum\_{i=1}^{K}\vec{\Delta}\_iP(i=\mathop{\text{argmax}}\_j\hat{\mu}\_j(mK))\\]
3. Finally,
\\[R\_n = R\_{mK} + R\_{n-mK} = m\sum\_{i=1}^{K}\vec{\Delta}\_i + (n-mK)\sum\_{i=1}^{K}\vec{\Delta}\_iP(i=\mathop{\text{argmax}}\_j\hat{\mu}\_j(mK))\\]

와따...해골복잡하게 사는구만 ㅡ,.ㅡ