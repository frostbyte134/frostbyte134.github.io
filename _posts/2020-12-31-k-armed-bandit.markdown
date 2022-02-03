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
- TODO : add mean zero to the def of subgaussian  <a href="https://web.stanford.edu/class/stats311/Lectures/lec-14.pdf" target="_blank">https://web.stanford.edu/class/stats311/Lectures/lec-14.pdf</a>

<h3 id="def"> (somewhat informal?) Problem Formulation</h3>
1. `Environment` = \\(K\\) distribution over the reals \\[P\_1,...,P\_K\\]  
   Note that __these distributions are stationary,__ fixed over all the time steps
2. For each rounds \\(t = 1, 2, ...\\)
   - based on the __past observations,__ the `learner` chooses an `action` \\(A\_t\\) \\[A\_t \in [K] := {1,...,K}\\]  
   - given \\(A\_t\\), the environment generates a __random__ `reward` \\[X\_t \sim P\_{A\_t}\\]
     when \\(A\_t = k\\), \\(X\_t\sim P\_k\\) (\\(t\\) is not random, but \\(X\_t\\) is random)
3. The Learner's goal is to maximize the `total reward`, which is an random variable \\[S\_n := \sum\_{t=1}^nX\_t\\]  
   - many criterias for maximization. Ex) maximize \\(E[S\_n]\\)
   - didn't specified \\(n\\) yet - many choices (fixed, \\(\infty, \forall n\\))
4. For an action \\(k\\), let us define "expected reward gained when action \\(k\\) is chosen",
   \\[\mu_k = \int\_{-\infty}^{\infty}xP\_k(x)dx\\]
   \\[\mu^* =\max\_k\mu\_k\\]
   where the range of \\(k\\) is \\(\\{1,...,k\\}\\). Based on this, we can define
   \\[\vec{\Delta}\_k= \mu^* -\mu\_k\\]
   - expected amount of lost value when choosing action \\(k\\)
   - referred as `immediate regret`, `action gap`, `suboptimality gap` of action \\(k\\)


<h3 id="basic_regret_decomp">Basic Regret Decomposition Identity Lemma</h3>

For the rounds untill \\(n\\), define
\\[T\_k(n) = \sum\_{t=1}^n 1\\{A\_t=k\\}\\]
- for trials 1 to \\(n\\), counting the event \\(A\_t=k\\)
- is a random variable on some strategy (which is dependent on previous random rewards)

Now we can define the `total regret` as \\[R\_n=n\mu^* -E[{\textstyle\sum}\_{t=1}^NX\_t]\\]
- "the difference between the rewards you would expect to obtain if you choose the optimal action in every round, and the rewards you actually expect to see by using your policy"
- \\(n\mu\\) is the optimal total expected reward in \\(n\\) rounds. No learner can do better than this.
- The learner makes choices based on the random previous rewards \\(X\_i, i < t \\) to choose \\(A\_t\\) inside \\(X\_t\\), so \\(X\_t\\) is also random.
   - Even when using deterministic strategy, previous rewards \\(X\_j,j<t\\) is random so \\(A\_t\\) which depends on them is also random

> __Basic regret decomposition identity lemma__
\\[R\_n = \sum\_{k=1}^K\vec{\Delta}\_kE[T\_k(n)]\\]
\\[ = \sum\_{k=1}^K\left((\mu^* -\mu\_k)\mathbb{E}\left[\sum\_{t=1}^n 1\\{A\_t=k\\}\right] \right)\\]

- regret untill time \\(n\\) = loop for all distribution \\(k\\), calculate the expected number of event that the event \\(A\_t=k\\) is selected for the time-duration \\(t=1,...,n\\), multiply them with \\(\mu^* - \mu\_k\\) and sum them all up.
- The lemma simply decomposes the regret in terms of the loss due to using each of the arms.
- The technique of using indicators for switching from sums over one variable to another will be used quite a few times, so it is worth remembering

__Proof__  
For any fixed \\(t\\), we have \\[\sum\_{k=1}^{K} 1\\{A\_t=k\\} = 1\\]
Hence \\[S\_n := \sum\_{t=1}^nX\_t = \sum\_{t=1}^n\sum\_{k=1}^K X\_t1\\{ A\_t=k \\}\\]
\\[n\mu^\* = \sum\_{t=1}^n \mu^\*  = \sum\_{t=1}^n\sum\_{k=1}^K \mu^* 1\\{ A\_t=k \\} \\]
which gives
\\[ R\_n=n\mu^\*  - E[S\_n] = \sum\_{k=1}^K\sum\_{t=1}^n E[(\mu^\* - X\_t) 1\\{ A\_t=k \\} ] \tag{1}\\]
Now consider the inner term
\\[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} ]\\]

Consider the <a href="{{site.url}}/probability/2020/11/30/sum-of-ind-normals.html" target="_blank">iterated expectation,</a>
\\[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} ] = E\left[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} \|A\_t]\right]\\]

using <a href="{{site.url}}/probability/2020/11/30/sum-of-ind-normals.html" target="_blank"> the definition of conditioned RV</a>, since it holds that
\\[E[(\mu^* -X\_t) 1\\{ A\_t=k \\} \| A\_t=j] = E[(\mu^* -X\_t) \| A\_t=j] \\] \text\{  if \} j=k \text\{, otherwise \} \\] 
\\[ = 1\\{ A\_t=k \\}E[(\mu^* -X\_t) \| A\_t=j]\\]
(here \\(k\\) is a fixed constant. we loop with \\(k\\) in the outer sigma) for all \\(j \in \\(\\[K\\]\\)), we have
\\[
\begin\{align\*\}  
E[(\mu^* -X\_t) 1\\{ A\_t=k \\} \| A\_t] &= 1\\{ A\_t=k \\}E[(\mu^* -X\_t) \| A\_t] \cr
                                        &= 1\\{ A\_t=k \\}(\mu^* -E[X\_t\| A\_t])  \cr
                                        &= 1\\{ A\_t=k \\}(\mu^* -\mu\_{A\_t})  \cr
                                        &= 1\\{ A\_t=k \\}(\mu^* -\mu\_k)  
\end\{align\*\}  
\\]
(마지막 부분은 결국 \\(E[X\_t \| A\_t] = \mu\_\{A\_t\} = \int\_x P\_\{A\_t\}(x)\\)이냐는 질문과 동일. \\(E[ X\_t \| A\_t]\\)는 발생한 이벤트에 따라 \\(A\_t\\)의 값이 결정되어 함수 \\(E[X\_t \| A\_t = j] = \int\_x P\_\{j\}(x)\\)의 값을 가지게 되는 RV이므로, 마지막 equality도 성립)  
(almost surely?) and the iterated expectation becomes
\\[E\left[ 1\\{ A\_t=k \\}E[(\mu^\* -X\_t) \| A\_t] ] = E[1\\{ A\_t=k \\}(\mu^\* -\mu\_k) \right]\\]
\\[ = E\left[ 1\\{ A\_t=k \\} \right] ( \mu^{\*} - \mu\_k ) \\]

the equation (1) becomes, using the linearity of expectation
\\[\sum\_{k=1}^K\sum\_{t=1}^n E[1\\{ A\_t=k \\}] (\mu^{\*} -\mu\_k)\\]
\\[= \sum\_{k=1}^K E\left[\sum\_{t=1}^n 1\\{ A\_t=k \\}\right] (\mu^{\*} -\mu\_k)\\]
\\[= \sum\_{k=1}^K E[T\_k(n)] (\mu^{\*} -\mu\_k)\\]
QED

Note that,
- instead of using iterated expectation, we can factor the joint pdf of random variables \\(X\_t\\) and \\(A\_t\\) into \\(P(X\_t\|A\_t)P(A\_t)\\) (more algebraic)
- In \\(T\_k(n)\\), we could possibly have __information related to time__. i.e., it is possible that
  \\[1\\{ A\_1=k \\} \neq 1\\{ A\_2=k \\}\\]

### Concentration of Measure and Concentration Inequality
<a href="https://banditalgs.com/2016/09/14/first-steps-explore-then-commit/#thm_subgaussian" target="_blank">https://banditalgs.com/2016/09/14/first-steps-explore-then-commit</a>

Let \\(X\_i\\) be a iid RV with mean \\(\mu\\) and var \\(\sigma^2\\).
The <a href="{{site.url}}/probability/2020/12/10/rv-convergence.html#sample_mean" target="_blank">Sample mean</a>
\\[\text{Sample mean  } M\_n:=\frac{X\_1+...+X\_n}{n}\\]
has __mean__ \\(\mu\\), __variance__ \\(\sigma^2/n\\).

and using the <a href="{{site.url}}/probability/2020/12/10/rv-convergence.html#chevyshev" target="_blank">Chevyshev inequality,</a>  <a href="{{site.url}}/probability/2019/02/18/estimating-rv-with-expectations.html" target="_blank">(proof of Markov, Chevyshev)</a>

(ch)
\\[P[ \|M\_n-\mu\|\geq \epsilon ] \leq \frac{\text{var}}{\epsilon^2} = \frac{\sigma^2}{n\epsilon^2}\\]
converges to 0 in probability as \\(n\rightarrow \infty\\)

However, what can we say about the `tail probability`? (=distribution of the error, amount of probability that our estimation is far away from the true mean)
\\[P(\|M\_n - \mu \| \geq \epsilon)\\]


<h4 id="gauss_bound"> Why we need subguassianity and concentration inequality?</h4>
1. using the <a href="{{site.url}}/probability/2020/12/10/rv-convergence.html#chevyshev" target="_blank">Chevyshev inequality</a>  directly gives \\[P(\|M\_n-\mu\| \geq \epsilon) \leq \frac{\sigma^2}{n\epsilon^2}\\]  
   This is easily drawn, but since we only used the mean and var as the input information, it is often too loose.
2. using the <a href="{{site.url}}/probability/2020/12/11/clt.html#clt" target="_blank">central limit theorem</a> says that \\(M\_n/\sqrt{n\} \sim N(0, \sigma)\\). This would suggest (as in the <a href="https://banditalgs.com/2016/09/14/first-steps-explore-then-commit/#thm_subgaussian" target="_blank">link</a>)
   \\[P(\mu\_n \geq \mu + \epsilon) = P(\frac{S\_n}{\sqrt{n}} \geq \epsilon\sqrt{n})\\]
   \\[\approx \int^\infty_{\epsilon \sqrt{n}} \frac{1}{\sqrt{2\pi \sigma^2}} \exp\left(-\frac{x^2}{2\sigma^2}\right) dx\\]
   which can be easily bound by using
   \\[\int^\infty_{\epsilon \sqrt{n}} \frac{1}{\sqrt{2\pi \sigma^2}} \exp\left(-\frac{x^2}{2\sigma^2}\right) dx\\]
   \\[\leq \frac{1}{\epsilon \sqrt{2n\pi \sigma^2}} \int^\infty_{\epsilon \sqrt{n}} x \exp\left(-\frac{x^2}{2\sigma^2}\right) dx \\] 
   \\[= \sqrt{\frac{\sigma^2}{2\pi n \epsilon^2}} \exp\left(-\frac{n\epsilon^2}{2\sigma^2}\right)\\]
   (last equality follows from the integral by parts)  
   most of time this bound is stronger than 1, but this is __asymtotic__ : not easy to apply when \\(n\\) is fixed
   - "hence it is vital to take a closer look at measure concentration and prove a “version” of the CLT that is true even for small values of \\(n\\)"


<h4 id="Subgaussianity"> Subgaussianity</h4>

> __Definition__ : A random variable \\(X\\) is \\(\sigma^2\\)-subgaussian if \\(\forall\\ \lambda \in \mathbb{R}\\) it holds that
   \\[E[\exp(\lambda X)]\leq \exp(\frac{\lambda^2\sigma^2}{2})\\]

- The function \\(M\_X(\lambda):=E[\exp(\lambda X)]\\) is called the <a href="{{site.url}}/probability/2020/12/02/mgf.html" target="_blank">moment generating function</a>

__Lemma__ : If \\(X\\) is \\(\sigma^2-\\)subgaussian, and \\(X\_1,X\_2\\) are independent and \\(\sigma\_1^2,\sigma\_2^2-\\)subgaussian respectively then  
1. \\(V[X] \leq \sigma^2\\)
   - use taylor expansion on both side, compare \\(\sigma^2\\) term
2. \\(cX\\) is \\(c^2\sigma^2-\\)subgaussian \\(\forall\\ c\in\mathbb{R}\\)
   - directly use MGF
3. \\(X\_1+X\_2\\) is \\((\sigma\_1^2+\sigma\_2^2)-\\)subgaussian
   - in independent case, easily proved using \\(E[XY] = E[X]E[Y]\\)
   - if not independent, \\(X\_1+X\_2\\) is \\((\sigma\_1+\sigma\_2)^**2**\\). __TODO: add proofs?__

<h4 id="concen"> Concentration inequality </h4>

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

Using this inequality, we can bound the tail (error) probability

<h4 id="hoefding"> Hoeffding's bound</h4>

Let
1. \\(X\_i-\mu\\) are \\(\sigma^2-\\)gaussian, and \\(X\_i\\)s are independent
   - \\(M\_n - \mu = \sum\_{i=1}^{n}(X\_i-m\_n)/n\\) is \\(\sigma^2/n-\\)subgaussian.
2. Then by the concentration inequality, we can bound the tail probability of \\(M\_n\\)

> __Corollary (Hoeffding's bound)__ : Assume that \\(X\_i-\mu\\) are independent, \\(\sigma^2-\\)subgaussian RVs. Then their sample mean \\(M\_n\\) satisfies
\\[P( \| M\_n - \mu \| \geq \epsilon) \leq \exp\left( -\frac{n\epsilon^2}{2\sigma^2} \right)\\]


By the inequality \\[\exp(-x) \leq \frac{1}{ex}\\] which holds when \\(x\geq 0\\), we see that
\\[P( \| M\_n - \mu \| \geq \epsilon) \leq \exp\left( -\frac{n\epsilon^2}{2\sigma^2} \right) \leq \frac{2\sigma^2}{en\epsilon^2}\\]
- for very small \\(\epsilon\\), the above inequality is much stronger than the one obtained by Chevyshev \\(\sigma^2/(n\epsilon^2)\\)
- and is exponentially smaller if \\(n\epsilon^2\\) is large, relative to \\(\sigma^2\\)

#### Example of Subgaussian RVs
- \\(X\sim N(0, \sigma^2)\\) then \\(X\\) is \\(\sigma^2-\\)subgaussian
- If \\(E[X] = 0,\\ \|X\|\leq B\\) almost surely for some \\(B\geq 0\\), then \\(X\\) is \\(B^2-\\)subgaussian
  - ex) X is a shifted bernoulli with \\(P[X=1-p]=p,\quad P[X=-p]=1-p\\) - \\(X\\) is \\(1/4-\\)subgaussian


### Explore-Then-Commit (ETC) strategy

Remarks
- we assume the __noise__ for all rewares \\(X\_i\\) is 1-subgaussian
  - __which is equivalent to saying that__ \\[X\_t - E[X\_t] \text{ is 1-subgaussian} \tag{2}\\]
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
2. \\(\hat{\mu}\_i(mK)\\) is the empirical mean of the reward of arm \\(i\\) up to round \\(t\\):
   \\[\hat{\mu}\_i(t):= \frac{1}{T\_i(t)}\sum\_{s=1}^t1\\{A\_s=i\\} X\_s\\]
   (remember that \\(T\_i(t)\\) is the # of times arm \\(i\\) was chosen till time \\(t\\))
3. in `ETC`, \\(T\_i(t)\\) is deterministic for \\(t\leq mK\\), and \\(\hat{\mu}\_i(mK)\\) is never used in \\(t>mK\\) (at \\(t=mK\\), our action is fixed)
   - Thus, easy to analysize the bound of \\(\hat{\mu}\_i(mK)\\) using the inequalities shown above. In equation,
      \\[\hat{\mu}\_i(mK) = \frac{1}{m}\sum\_{s=1}^tX\_s \tag{3} \\]
     - In other algorithms which also uses \\(\hat{\mu}\_i(mK)\\), \\(T\_i(t)\\) could be random
   - \\(\hat{\mu}\_i(mK)\\) is __NOT__ the sample mean of IID RVs. the distribution of \\(1\\{A\_s=i\\}\\)

#### Regret derivation of ETC
<a href="http://www.ds3-datascience-polytechnique.fr/wp-content/uploads/2017/08/2017_08_31-09_01_Csaba_Szepesvari_Bandits_part1.pdf" target="_blank">http://www.ds3-datascience-polytechnique.fr/wp-content/uploads/2017/08/2017_08_31-09_01_Csaba_Szepesvari_Bandits_part1.pdf</a>

recall the basic regret decomposition lemma, which calculates the regret wrt the distribution (arm) index \\(i\\)
\\[R\_n = \sum\_{i=1}^K\vec{\Delta}\_{A\_t}E[T\_i(n)]\\]
However, we can calculate it with repsect to \\(nK\\) rounds
1. For the first \\(mK\\) rounds, we will exploit \\(K\\) arms deterministically \\(m\\) times. No randomness here, and \\(E[T\_i(n)]=m\\)
   \\[R\_{mK}=m\sum\_{i=1}^{K}\vec{\Delta}\_i\\]
2. For the remaining \\(n-mK\\) times, \\(E[T\_i(n)]\\) is   
   =  \\(P(i=\mathop{\text{argmax}}\_j\hat{\mu}\_j(mK)) \times (n-mk)\\)  
   = (probability that arm \\(i\\) is selected) * (# of times the arm i will be used if selected)
   \\[R\_{n-mK} = (n-mK)\sum\_{i=1}^{K}\vec{\Delta}\_iP(i=\mathop{\text{argmax}}\_j\hat{\mu}\_j(mK))\\]
3. In conclusion,
\\[R\_n = R\_{mK} + R\_{n-mK} = m\sum\_{i=1}^{K}\vec{\Delta}\_i + (n-mK)\sum\_{i=1}^{K}\vec{\Delta}\_iP(i=\mathop{\text{argmax}}\_j\hat{\mu}\_j(mK))\\]

Now we have to bound the probability \\(P(i=\mathop{\text{argmax}}\_j\hat{\mu}\_j(mK))\\).
1. Assumw WLOG that the arm \\(i=1\\) is the optimal, so that \\(\mu\_1=\mu^\* = \max\_i\mu\_i\\).
2. Algebraicly, 
\\[\begin\{align\*\}  
P(i=\mathop{\text{argmax}}\_j\hat{\mu}\_j(mK)) &= P(\hat{\mu}\_i(mK) - \hat{\mu}\_1(mK) \geq 0) \cr
                                               &= P(\hat{\mu}\_i(mK) - \mu\_i - \hat{\mu}\_1(mK) + \mu\_1\geq 0)  
\end\{align\*\}\\]

Note that 
1. in (3), we were able to simplify \\(\hat{\mu}\_i(mK)=\frac{1}{m}\sum\_{s=1}^tX\_s\\) in ETC, so that
   \\[\hat{\mu}\_i(mK) - \mu\_i = \frac{1}{m}\sum\_{s=1}^t(X\_s - E[X\_s])\\]
2. in (2), we had 1-subgaussian assumption for the noise term, and based on the lemma in the <a href="#Subgaussianity">Subgaussianity</a> page,  
   \\[\frac{1}{m}\sum\_{s=1}^t(X\_s - E[X\_s]) \text{  is 1/m subgaussian}\\]
3. Adding two 1/m subgaussian (2/m subgaussian), and using the concententration inequality, we conclude
   \\[P(i=\mathop{\text{argmax}}\_j\hat{\mu}\_j(mK)) \leq \exp\left( -\frac{m\vec{\Delta}\_i^2}{4} \right)\\]
4. and by straightforward substitution we have
   \\[R\_n \leq R\_{mK} + R\_{n-mK} = m\sum\_{i=1}^{K}\vec{\Delta}\_i + (n-mK)\sum\_{i=1}^{K}\vec{\Delta}\_i\exp\left( -\frac{m\vec{\Delta}\_i^2}{4} \right)\\]

<h4 id="k2"> Regret Analysis of ETC </h4>
5. if \\(m\\) is small, then the error probability \\(\exp\left( -\frac{m\vec{\Delta}\_i^2}{4} \right)\\)will likely to grow
6. if \\(m\\) is too large, exploration is excessive and the first term will grow
7. When \\(K=2\\), assuming that \\(n\\) is sufficiently large (so that \\((n-2m\approx n),\\ \vec{\Delta}\_1=0, \vec{\Delta}\_2=\vec{\Delta}\\) so we have
   \\[R_n \leq m \Delta + (n – 2m) \Delta \exp\left(-\frac{m\Delta^2}{4}\right) \leq m\Delta + n \Delta \exp\left(-\frac{m\Delta^2}{4}\right)\\]
   it is the sum of two convex function, so by taking derivative (not so hard) we have minimum (up to rounding error) at
   \\[m = \lceil\frac{4}{\Delta^2} \log\left(\frac{n \Delta^2}{4}\right)\rceil\\]
   which bounds the regret by
   \\[R_n \leq \Delta + \frac{4}{\Delta} \left(1 + \log\left(\frac{n \Delta^2}{4}\right)\right) \tag{5}\\]
   1. Even with additional assumptions, the choice of \\(m\\) depends on \\(\vec{\Delta}\\) and \\(n\\).
   2. Sometimes it is reasonable to assume the fixed \\(n\\), but it is __never practical for the suboptimality gap to be known__.
   3. __However__, one can choose \\(m\\) that only depends on \\(n\\), which satisfies \\(R\_n=O(n^{2/3})\\).
      1. any details? proofs?
   4. There are __other algs__ which do not even need \\(n\\) but have much better rate \\(R\_n=O(n^{1/2})\\)
      - <a href="{{site.url}}/probability/2021/01/07/k-armed-bandit-ucb.html" target="_blank">UCB</a> 
8. When \\(K=2\\), we have another bound. Using the fact that \\(E[T\_i(n)]>0\\) and \\(\sum\_{i=1}^{K}E[T\_i(n)]=n\\) (use iterated expectation to see this holds) gives
   \\[R\_n=\sum\_{i=1}^2 \vec{\Delta}\_iE[T\_i(n)] = 0 * E[T\_1(n)] + \vec{\Delta}E[T\_2(n)] \leq n\vec{\Delta}\\]
   When \\(\vec{\Delta}\\) is extremely small, our intuition is that the regret must be small, since the wrong choice does not make too much difference.  
   However in equ(5) it is not the case - \\(\vec{\Delta}\\) is in the denominator.  
   Above bound prevents such catastrophy to be happen, and practically the bound becomes 
   \\[R_n \leq \min\left\\{ n\Delta,\, \Delta + \frac{4}{\Delta}\left(1 + \log\left(\frac{n\Delta^2}{4}\right)\right) \right\\}\\]
9. (exercise) assuming that \\(\vec{\Delta} \leq \sqrt{n}\\), 
   \\[\Delta + \frac{4}{\Delta}\left(1 + \log\left(\frac{n\Delta^2}{4}\right)\right) \leq \sqrt{n} + \frac{4}{\sqrt{n}}\left(1 + \log\left(\frac{n^2}{4}\right)\right)\\]
   We see that, by taking derivative, \\(\sqrt{n}\\) increase more rapidly than \\(\log(n^2)\\), and the latter term has decreasing number \\(4/\sqrt{n}\\) as the coefficient. We see that the convergence is dominated by the term \\(\sqrt{n}\\).  
   In conclusion, if we assume \\(\vec{\Delta} \leq \sqrt{n}\\) then \\(R\_n=O(\sqrt{n})\\)


### Additional notes

> Note 1: The __Berry-Esseen theorem__ quantifies the speed of convergence in the CLT. It essentially says that the distance between the Gaussian and the actual distribution decays at a rate of \\(1\sqrt{n}\\) under some mild assumptions. This is known to be tight for the class of probability distributions that appear in the Berry-Esseen result. However, this is a poor result when the tail probabilities themselves are much smaller than \\(1\sqrt{n}\\). Hence, the need for alternate results

Similar idea of ETC
1. The exporation is still forced, but spread around the round \\(n\\) - \\(\epsilon-\\)greedy strategy
   - no need of explicitly fixed \\(n\\)
   - \\(\epsilon\\) slowly decreases, as a function of time
   - even this \\(\epsilon-\\)greedy suffers the same difficulties (need to know the horizon \\(n\\) and sub-optimality gaps ?) that ETC faces

와따...해골복잡하게 사는구만 ㅡ,.ㅡ