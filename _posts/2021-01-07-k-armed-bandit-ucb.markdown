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


- <a href="https://web.stanford.edu/class/stats311/Lectures/lec-14.pdf" target="_blank">https://web.stanford.edu/class/stats311/Lectures/lec-14.pdf</a>

### Upper Confidence Bound

Recall that
1. if \\(X\_1,...,X\_n\\) are independent, and 1-subgaussian and
2. let \\(\hat{\mu}=\sum\_{t=1}^n X\_t/n\\). Then with the <a href="{{site.url}}/probability/2020/12/31/k-armed-bandit.html#hoefding" target="_blank">Hoeffding's bound</a>, 
\\[P(\hat{\mu} \geq \epsilon) \leq \exp\left( -\frac{n\epsilon^2}{2} \right)\\]
Equating the rhs with \\(\delta\\) and solve for \\(\epsilon\\) leads to
\\[\delta = \exp\left( -\frac{n\epsilon^2}{2} \right)\\]
\\[\sqrt{ -\frac{2}{n}\ln\delta } = \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) } = \epsilon\\]
so that
\\[P\left(\hat{\mu} \geq \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) } \right) \leq \delta\\]

#### "As large as plausibly possible"
- The learner decides the \\(A\_t\\) by looking at \\(T\_i(t-1)\\) samples from each arm \\(i\\), so that the `empirical mean of rewards` \\(\hat{\mu}_i(t-1)\\) at \\(t-1\\) is defined as (which is the unbiased(possibly) estimation of the true mean \\(\mu\_i\\))
  \\[\hat{\mu}\_i(t-1)  := \frac{1}{T\_i(t-1)}\sum\_{s=1}^{t-1}1\\{A\_s=i\\} X\_s\\]
- Then a good candidate for the __largest plausible estimate of the mean for arm__ \\(i\\) is
  \\[\hat{\mu}\_i(t-1) + \sqrt{ \frac{2}{n}\ln  \left(\frac{1}{\delta}\right) }\\]
  the algorithm chooses the action \\(i\\) which maximizes the above quantity
- small \\(\delta\\) : optimistic algorithm  
  large \\(\delta\\) : the optimism is less certain
- \\(1-\delta\\) := `confidence level`. different choices \\(\rightarrow\\) different algs with different analysis
- For now, we choose \\[\frac{1}{\delta} = f(t) := 1+t\log^2(t),\\ \\ t=1,2,...\\]  
  - \\(1/\delta\\) is time dependent, decreases faster than \\(1/t\\).
  - __Note__ that we used \\(\epsilon\\) to derive the \\(\delta\\), but in the course of algorithm they have no dependencies (\\(\epsilon\\) remain constaint, \\(\delta\\) is time-dependent)

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
  - it will only happen when \\(\hat \mu_i(t-1) \ll \mu\_i\\) and \\(0 \ll T\_i(t-1)\\) 

If (sadly) the arm \\(1\\) was not an optimal arm, i.e. \\(1 \neq \mathop{\text{argmax}}\mu\_i\\), and wlog let arm \\(i\\) was optimal.  
__Then the algorithm has made a wrong decision,__ and for the (hidden) true arm \\(i\\) we have
\\[\hat \mu_i(t-1) + \sqrt{\frac{2}{T_i(t-1)} \log\left(\frac{1}{\delta}\right)} \leq \mu_1 < \mu\_i \\]

That is, for the `UCB` to make a wrong decision,    
  - in the case of optimal arm, its upper bound of confidence interval should be even lower than its true mean
  - Right above, we pointed out that in order for `UCB` to make a decision, \\[\hat \mu_i(t-1) \ll \mu\_i \quad \text{  and  } \quad 0 \ll T\_i(t-1)\\]
    must hold. __Note that both conditions are mutually exclusive__,(when \\(n\\) grows so that \\(T\_i(t-1)\\) grows, sample mean converges to true mean)    
    which makes the prob of `UCB` to make wrong decision very low.
   

### UCB Regret Bound

> __Theorem (UCB Regret)__ : The regret of UCB is bounded by 
  \\[R_n \leq \sum_{i:\Delta_i > 0} \inf_{\epsilon \in (0, \Delta_i)} \Delta_i\left(1 + \frac{5}{\epsilon^2} + \frac{2}{(\Delta_i – \epsilon)^2} \left( \log f(n) + \sqrt{\pi \log f(n)} + 1\right)\right)\\]   
  Furthermore,  
  \\[ \mathop{\text{limsup}}\_{n \rightarrow \infty }  \frac{ R\_n }{ \log(n) } \leq \sum_{i : \Delta_i > 0} \frac{2}{\Delta_i}\\]


1. Remember that \\(f(t) = 1+t\log^2(t)\\), so that \\[\log f(n) \approx \log(n) + 2\log\log(n)\\]  
  - In `ETC`, we obtained \\(\log n\\) bound when we set \\(K=2\\) and <a href="{{site.url}}/probability/2020/12/31/k-armed-bandit.html#k2" target="_blank">used unreachable knowledge</a> of \\(\Delta\_2\\). we dont need such infeasible knowledge in `UCB`
2. By choosing \\(\epsilon=\Delta\_i/2\\), for analysis purpose we see that
  > __Corollary (UCB Simplified Regret)__ : The regret of UCB is bounded by (somewhat loosely, since we fixed \\(\epsilon\\))  
    \\[R_n \leq \sum_{i:\Delta_i > 0} \left(\Delta_i + \frac{1}{\Delta_i}\left(8 \log f(n) + 8\sqrt{\pi \log f(n)} + 28\right)\right)\\]
    
  and in particular, there exists \\(C>0\\) s.t. \\(\forall\\ \\ n \geq 2\\),
  \\[R_n \leq \sum_{i:\Delta_i>0} \left(\Delta_i + \frac{C \log n}{\Delta_i}\right)\\]

Now we are going to prove this theorem

<h4 id=lemma> Useful lemma</h4>

Firstly we will show a useful lemma

> __Lemma__ Let \\(X_1,X\_2,...\\) be a seq of independent 1-subgaussian RVs, define \\(\hat{\mu}:=\sum\_{s=1}^t(X\_s-\mu\_s)/t\\), \\(\epsilon>0\\) and
  \\[\kappa = \sum\_{t=1}^n 1\left\\{ \hat{\mu}\_t + \sqrt{\frac{2a}{t}}\geq \epsilon \right\\}\\]
  \\[       = \sum\_{t=1}^n 1\left\\{\sum\_{s=1}^t\frac{X\_s-\mu\_s}{t} + \sqrt{\frac{2a}{t}}\geq \epsilon \right\\}\\]
  Then,
  \\[E[\kappa] \leq 1 + \frac{2}{\epsilon^2}(a+\sqrt{\pi a} + 1)\\]

1. wrt the linearity of expectation, we firstly consider single \\(t\\)
   \\[\begin{align\*} 
   E\left[1\left\\{ \hat{\mu}\_t + \sqrt{\frac{2a}{t}}\geq \epsilon \right\\} \right] 
   &= P\left( \hat{\mu}\_t + \sqrt{\frac{2a}{t}}\geq \epsilon \right) \cr
   &\leq \sqrt{\frac{2a}{t}}\epsilon^{-1} = \sqrt{\frac{2a\epsilon^{-2}}{t}} \tag{Markov's inequality} \cr
   \end{align\*}   
   \\]
2. Let \\(u = 2a\epsilon^{-2}\\). For \\(t=1,...,\left\lfloor u \right\rfloor\\), we have immediate inequality
   \\[\sqrt{\frac{2a\epsilon^{-2}}{t}} \leq 1\\] so that
   \\[E[\kappa] \leq  u  + \sum\_{t=\left\lceil u \right\rceil}^n P\left( \hat{\mu}\_t + \sqrt{\frac{2a}{t}}\geq \epsilon \right)\\]
3. Now using the <a href="{{site.url}}/probability/2020/12/31/k-armed-bandit.html#concen" target="_blank">concentration lemma,</a>   
   \\[\begin{align\*} 
   E[\kappa] &\leq 1 + u + \int^\infty_u \exp\left(-\frac{t\left(\epsilon – \sqrt{\frac{2a}{t}}\right)^2}{2}\right) dt \cr 
             &= 1 + \frac{2}{\epsilon^2}(a + \sqrt{\pi a} + 1)
   \end{align\*}   \\]
   (for the last inequality, perform the <a href="https://freshrimpsushi.tistory.com/219" target="_blank">Gauss integral</a> from 0)

#### new empirical mean after some observation

Previously we defined
  - \\(\hat{\mu}_i(t)\\) : empirical mean of the arm \\(i\\), after \\(t\\) round

Now for the analysis of `UCB`, we define
  - \\(\hat{\mu}_{i,s}\\) : empirical mean of the arm \\(i\\), after \\(s\\) observations (which occur randomly, maybe not at all around some times)

To define \\(\hat{\mu}_{i,s}\\) rigorously, define \\(Z\_{i,s} \sim P\_i\\) as
\\[X\_t = Z\_{A\_t,T\_{A\_t}(t)}\\]
That is, \\(X\_t\\) = the reward at time \\(t\\) comes from the sequence \\(Z\_{i,s},\\ s=1,...,n\\). If the arm \\(i\\) is never selected, then it is the sequence of zeros length \\(n\\).

Now we define \\(\hat{\mu}_{i,s}\\) rigorously
\\[\hat{\mu}\_{i,s} := \frac{1}{s}\sum\_{u=1}^s Z\_{i,u}\\]

#### Main proof of UCB bound

Recall that using the <a href="{{site.url}}/probability/2020/12/31/k-armed-bandit.html#basic_regret_decomp" target="_blank">basic regret decomposition lemma</a>,
\\[R\_n = \sum\_{k=1}^K\vec{\Delta}\_kE[T\_k(n)] = \sum\_{i : \Delta\_i > 0}\vec{\Delta}\_i E[T\_i(n)]\\]
Now we are going to bound \\(E[T\_i(n)]\\). 

Let \\(i\\) be some suboptimal arm (\\(\Delta\_i>0\\)). We are going to decompose \\(T\_i(n)\\) into two terms.

Note that, we can decompose \\(1\\{A_t = i\\}\\) into two terms
\\[
\begin{align} 
1\\{A_t = i\\} &= 1\left\\{ \hat \mu_i(t-1) + \sqrt{\frac{2 \log f(t)}{T_i(t-1)}} \geq \mu_1 - \epsilon  \text{ and }   A_t = i \right\\} \nonumber \cr
               &\\ + 1\left\\{\hat \mu_i(t-1) + \sqrt{\frac{2 \log f(t)}{T_i(t-1)}} < \mu_1 - \epsilon  \text{ and }  A_t = i  \right\\}  \nonumber \cr
\end{align}  
\\]
and if \\(A_t = i\\) then \\(\hat \mu_1(t-1) + \sqrt{\frac{2 \log f(t)}{T_1(t-1)}} < \hat \mu_i(t-1) + \sqrt{\frac{2 \log f(t)}{T_i(t-1)}} \tag{1}\\)

so that (we indeed see that the inequality \\(\leq\\) holds in (1)), since there are cases where (1) holds but \\(A_t \neq i\\)
\\[
\begin{align} 
T_i(n) 
&= \sum_{t=1}^n 1\\{A_t = i\\} \nonumber \cr  
&\leq \sum_{t=1}^n 1\left\\{\hat \mu_1(t-1) + \sqrt{\frac{2\log f(t)}{T_1(t-1)}} \leq \mu_1 – \epsilon\right\\}  \nonumber \cr  
&\qquad \sum_{t=1}^n 1\left\\{\hat \mu_i(t-1) + \sqrt{\frac{2 \log f(t)}{T_i(t-1)}} \geq \mu_1 – \epsilon \text{ and } A_t = i\right\\}\,. \label{eq:ucb1} \tag{7} \cr  
\end{align}  
\\]

We now bount the two terms in (7)

1. Starting with the first, we again use the <a href="{{site.url}}/probability/2020/12/31/k-armed-bandit.html#concen" target="_blank">concentration lemma,</a>
   \\[\begin{align\*} 
     E\left[\sum_{t=1}^n 1\left\\{\hat \mu_1(t-1) + \sqrt{\frac{2 \log f(t)}{T_1(t-1)}} \leq \mu_1 – \epsilon\right\\}\right] 
     &= \sum_{t=1}^n P\left(\hat \mu_1(t-1) + \sqrt{\frac{2 \log f(t)}{T_1(t-1)}} \leq \mu_1 – \epsilon\right) \cr  
     &\leq \sum_{t=1}^n \sum_{s=1}^n P\left(\hat \mu_{1,s} + \sqrt{\frac{2 \log f(t)}{s}} \leq \mu_1 – \epsilon\right) \cr   
     &\leq \sum_{t=1}^n \sum_{s=1}^n \exp\left(-\frac{s\left(\sqrt{\frac{2 \log f(t)}{s}} + \epsilon\right)^2}{2}\right) \cr   
     &\leq \sum_{t=1}^n \frac{1}{f(t)} \sum_{s=1}^n \exp\left(-\frac{s\epsilon^2}{2}\right) \cr   
     &\leq \frac{5}{\epsilon^2}\,. 
   \end{align\*}\\]
  1. The 1st inequality follows from the union bound. Since \\(T\_1(t-1)\\) is random, we cannot apply the concentration lemma, so we replaced it with fixed scalars (of all cases)
  2. the 2nd ienequality is the concentration lemma (make mean zero)
  3. for the 3rd, \\(s\left(\sqrt{\frac{2 \log f(t)}{s}} + \epsilon\right)^2 \geq \sqrt{\frac{2 \log f(t)}{s}}^2\\) (and \\(\epsilon^{-x})\\) is decreasing)
2. For the second term, we can use the above <a href="#lemma">lemma</a>
   \\[\begin{align\*} 
    &E\left[\sum_{t=1}^n 1\\{\hat \mu_i(t-1) + \sqrt{\frac{2 \log f(t)}{T_i(t-1)}} \geq \mu_1 – \epsilon \text{ and } A_t = i\\}\right] \cr   
    &\qquad\leq E\left[\sum_{t=1}^n 1\\{\hat \mu_i(t-1) + \sqrt{\frac{2 \log f(n)}{T_i(t-1)}} \geq \mu_1 – \epsilon \text{ and } A_t = i\\}\right] \cr   
    &\qquad\leq E\left[\sum_{s=1}^n 1\\{\hat \mu_{i,s} + \sqrt{\frac{2 \log f(n)}{s}} \geq \mu_1 – \epsilon\\}\right] \cr   
    &\qquad= E\left[\sum_{s=1}^n 1\\{\hat \mu_{i,s} – \mu_i + \sqrt{\frac{2 \log f(n)}{s}} \geq \Delta_i – \epsilon\\}\right] \cr 
    &\qquad\leq 1 + \frac{2}{(\Delta_i – \epsilon)^2} \left(\log f(n) + \sqrt{\pi \log f(n)} + 1\right)\,. 
   \end{align*}\\]

3. The first part of the theorem follows by substituting the results of the previous two displays into   
   The second part follows by choosing \\(\epsilon = \log^{-1/4}(n)\\) (wtf) and letting \\(n\rightarrow \infty\\)