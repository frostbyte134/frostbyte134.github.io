---
layout: post
title:  "K-armed Stochastic (Stationary) Bandit 3 - Optimality 1"
date:   2021-01-25 09:00:05 +0800
categories: probability
use_math: true
tags: math probability bandit information_theory
---


- <a href="https://banditalgs.com/2016/09/22/optimality-concepts-and-information-theory/" target="_blank">https://banditalgs.com/2016/09/22/optimality-concepts-and-information-theory/</a>  
- <a href="https://www.stat.berkeley.edu/~bartlett/courses/2014fall-cs294stat260/lectures/bandit-lower-bound-notes.pdf" target="_blank">https://www.stat.berkeley.edu/~bartlett/courses/2014fall-cs294stat260/lectures/bandit-lower-bound-notes.pdf</a>

### Restatement of UCB Upper bound

Let \\(\mathcal{E}\_K\\) stand for the \\(K\\)-action stochastic env, where
1. the reward for action \\(i\in[K]\\) are generated from
2. a distribution \\(P\_i\\) with mean \\(\mu\_i\in[0, 1]\\)
3. If \\(X\sim P\_i\\) then \\(X-\mu\_i\\) is 1-subgaussian

(such environment will be called `1-subgaussian` for short)


<a href="{{site.url}}/probability/2021/01/07/k-armed-bandit-ucb.html" target="_blank">Previosuly</a> we showed that

> __Theorem (Worst case regret-bound for UCB)__ There exists a constant \\(C>0\\) such that the following hold:  
\\(\forall\\ K>0\\), \\(E\in \mathcal{E}\_K, n>1\\),
\\[\begin{align} 
\label{eq:UCBbound} 
R_n \le C \sqrt{K n \log(n)}\,. 
\end{align}\\]  
If \\(R\_n\\) is the expected regret of UCB when interacting with \\(E\\).

- \\(C\\) : a `universal constant`, in the sense that its value does not depend on \\(K, n, E\\) as long as they satisfies the constraints
- it is called the `worst-case bound`
  - it holds, even when the env is the worst for the UCB (somewhat positive thing)
  - points out certain weakness of the algorithm


### Minimax regret (lower bound of UCB)

One may wish to minimize such worst-case bound, by improving UCB or selecing other algorithms.  
However, above bound of UCB cannot be improved much, which means that  
no matter the policy, there will be an __env__ \\(E\\) on which all the policy achieves almost the same regret as the `worst-case bound`

It can be precisely represented as the `minimax regret`
- for a given horizon \\(n>0\\) (# of total trials)
- and a fixed number of actions \\(K>0\\) (# of arms)
- Let \\(\mathcal{A}_{n,K}\\) stand for the set of all possible policies on \\(n, [K]\\).

Then the __minimax regret__ for \\(n\\) and the `environment class` \\(\mathcal{E} \\) (=\\(\mathcal{E}\_k\\)) is defined as
\\[
\begin\{align\*\} 
R_n^\* (\mathcal{E})  = \inf_{A \in \mathcal{A}\_{n,k}} \sup_{E\in \mathcal{E}}  R_n(A,E)\,.
\end\{align\*\}
\\]

1. \\(R_n^* (\mathcal{E}) \\) is independent of policy, but only depends of \\(n, \mathcal{E}, K\\) (the dependent on \\(K\\) is hidden in \\(\mathcal{E}\\))
2. there exists no policies that performs better than the lower bound (obviously!).  
   It shows the fundamental hardness of the problem.


A `minimax optimal policy` is a policy \\(A\\) which achieves
\\[R_n^* (A,\mathcal{E}) = R_n^* (\mathcal{E})\\]
Finding such policy is exponentially hard, so we want to find the `near-minimax policy`, which can be stated as
\\[R\_n^* (A, \mathcal{E}) \leq CR\_n^* (\mathcal{E})\\]
or more `relaxed version`
\\[\frac{R\_n^* (A, \mathcal{E})}{R\_n^* (\mathcal{E})} \leq \log\left( \max(1, R\_n^* (\mathcal{E})) \right)\\]
- The idea is that \\(\log\left( R\_n^* (\mathcal{E}) \right)\\) is much smaller than \\(R\_n^* (\mathcal{E})\\), and we do not want our near-maximal policy \\(A\\) to produce regret wrt such value (proportional)

The value itself of \\(R\_n^* (\mathcal{E})\\) is of interest on its own
  - small \\(R\_n^* (\mathcal{E})\\) indicates that the problem is less-challenging in the worst-case sense
  - one of core researches of bandit (or learning) theory : to understand what makes \\(R\_n^* (\mathcal{E}))\\) large or small, often as a func of \\(n, K\\)


We now state the conclusion as the theorem

> __Theorem (Worst case regret lower)__ For any \\(K\geq 2,\\ n\geq 2\\), :  
\\[R_n^*(\mathcal{E}_K) \geq c\sqrt{Kn}\\]
for some universal constant \\(c>0\\).

> <a href="https://banditalgs.com/2016/09/22/optimality-concepts-and-information-theory/" target="_blank">In particular, we see that UCB is near-minimax optimal. But how to prove that the above result? The intuition is relatively simple and can be understood by just studying Gaussian tails.</a>


### Lower bounding ideas

Problem setting
1. Given \\(n\\) iid observation from normals with a __known variance__ of say 1 and __unknown mean__ \\(\mu\\), 
2. the `sample mean` of the observation is the `sufficient statistic` for the true mean \\(\mu\\)
   1. any observation can be replaced by the sample mean, without losing information
3. the distribution of sample mean also follows a gaussian, with mean (unknown) \\(\mu\\) and variance \\(1/n\\).
   
Now assume that \\(\mu\\) can take only two values, \\(\\{0, \Delta\\}\\)
- We assume wlog that \\(\Delta > 0\\). 
- as said, we can make decision solely based on the sample mean \\(\hat \mu\\), which is a sufficient statistic 
- If \\(n \gg \Delta \\), we (intuitively) seel that the decision is easy
  - If \\(\hat \mu\\) is closer to zero than to \\(\Delta\\), choose 0

__No matter then whether__ \\(\mu\\) __was indeed 0 or__ \\(\Delta\\), <a href="{{site.url}}/probability/2020/12/31/k-armed-bandit.html#gauss_bound" target="_blank">we can bound the error probability value itself </a>.
\\[
\begin{align\*} 
P\left( \hat \mu\_n \geq \mu + (\Delta /2) \right) \leq \frac{1}{\sqrt{2\pi n(\frac{\Delta}{2})^2}} \exp(-n (\Delta/2)^2/2) \le \exp(-\frac{n(\Delta/2)^2}{2})\,, 
\end{align\*}  
\\]  
- The only case we fail is when the deviation of sample mean exceeds \\(\delta/2\\)
- where the inequality in the middle assumed that \\(2\pi n (\Delta/2)^2\ge 1\\)
- we see that the error probability value decays exponentially with \\(n\\)
- if \\(\Delta\\) is too small compared to \\(n\\), the bound is useless (nearly 1)

However, above bound for the Gaussian tail is somewiat loose. With more <a href="https://mikespivey.wordpress.com/2011/10/21/normaltails/" target="_blank">calculation (using integral by parts)</a>, if \\(X\\) is normal,
\\[
\begin{align\*} 
P\left(X>\epsilon\right) \ge \left(\frac{1}{\epsilon}-\frac{1}{\epsilon^3}\right)\, \frac{\exp( – \frac{\epsilon^2}{2} )}{\sqrt{2\pi}} 
\end{align\*}  
\\]

and in our case \\(\epsilon = (\Delta /2)\\), if we let
\\[n(\Delta/2)^2/2 \leq c \quad\quad \left(  \Delta \le \sqrt{8c/n},\quad \text{ or equivalently }\quad n\le 8c/\Delta^2 \right)\\]
then the error low bound becomes
\\[C (\frac{1}{\sqrt{c}}-\frac{1}{c\sqrt{c}})\exp(-c)>0\\]

- The take home message is that if \\(n\\) is small compared to the differences in the means \\(\Delta\\) that we need to test, then we are facing an impossible mission (error prob will be close to 1)
- The ideas underlying this argument are core to any arguments that show an `impossibility` result in a statistical problem. 

__The next task is to reduce our bandit problem to a hypo testing problem as described above__

#### 'impossibility' bandits

Problem formulation
1. Two bandits instances \\(E, E'\\) where the `reward` distribution are Normal with \\(\sigma^2=1\\).
2. The vector of means are in \\([0,1]^K\\), thus the instances are in \\(\mathcal{E}\_K\\)
   - we assumes two different envs, with \\(K\\) arms
3. Let the mean vectors of two instances be \\(\mu, \mu'\\)
4. Our goal is tochoose \\(E,E'\\) (or equivalently, \\(\mu,\mu'\\)) in a way that
   1. `Competition`: Algorithms doing well on one instance, cannot do well on the other instance.
   2. `Similarity`: The instances are __close__ so that no matter what policy interacts with them, given the observations, the two instances are indistinguishable as in the hypo testing example above (error prob low bound is close to 1)

Our strategy is that
1. Choose \\(\mu\\) that one arm has a slightly higher mean (by a constant \\(\Delta\\)) than all the other arms, call this index \\(i_E\\).
2. Then we find the least favored arm in expectation \\(i\_{E'}\\) by the algorithm \\(A\\), which must not be \\(i\_E\\) in high prob
3. and to build \\(E'\\) we increase the mean of this arm by \\(2\Delta\\)
4. In particular, all the arms of \\(E\\) and \\(E'\\) has the same \\(\mu\\), except for  
   \\(i\_{E'}\\) which is optimal in \\(E'\\) (\\(E'\\) also has \\(i\_{E}\\), which is less optimal) and  
   \\(I\_E\\) which is optimal in \\(E\\) (\\(E\\) does not have \\(i\_{E'}\\))

여기서 하고 싶은 것은, "어떤 알고리즘이 아무리 노력해도" \\(c\sqrt{Kn}\\) regret bound 이하를 달성할 수 없는 환경이 있다는 것임
- 그 환경이 유일할 필요는 없음. 어떤 alg한테는 \\(E\\)가, 다른 alg한테는 \\(E'\\)이 저 바운드 이상만 되면 됨

Note that,
1. intuitively when the \\(A\\) run on \\(E'\\), it won't choose \\(i\_{E'}\\) more than \\(n/K\\) times (we have optimal arm \\(i\_E\\)) "in expectation"
   - 어떤 알고리즘이 최대한의 결과를 내려면, optimal하지 않은 arm \\((i\_{E'}\\)을 "평균적으로" \\(n/K\\) 이상 쓰지 않으리라고 기대됨
2. The two envs differ only in terms of the mean of \\(i\_{E'}\\)
3. To make two envs indifferentiable, set \\(\Delta=1/\sqrt{n/K}\\).
   - when \\(i\_{E'}\\) is chosn \\(n/K\\) times, the sample mean of this arm will have stddev \\(1/\sqrt{n/K}\\).
   - When the true mean is closer than the stddev, then they are indistinguisable (error probability will be high, as above!)
   - now when \\(A\\) is run on \\(E'\\), the interaction of \\(A-E'\\) will produce a near-identically distributed sequence of action-choices than the distribution when \\(A\\) was used on \\(E\\)
4. When \\(A\\) is run on \\(E\\) and \\(i\_E\\) is chosen fewer than \\(n(1-1/K)\\) times on expectation (다른 arm들을 시도라도 해 봐야 하니까), then it will have more than \\(\Delta(n- n(1-1/K)) \approx c\sqrt{Kn}\\) regret
   - here, \\(c\\) is a `universal constant` whose value can change line-by-line (by \\(n\\)>)
5. for the algorithm which choose \\(i\_E\\) more than \\(n(1-1/K)\\) times when interacting with \\(E\\)
   - by the indistinguisability between \\(E, E'\\), it will also choose \\(i\_E\\) same times on \\(E'\\), and it will have a regret (at least) greater than \\(c\sqrt{Kn}\\).