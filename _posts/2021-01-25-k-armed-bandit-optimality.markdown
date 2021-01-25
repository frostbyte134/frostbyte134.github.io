---
layout: post
title:  "K-armed Stochastic (Stationary) Bandit 3 - Optimality 1"
date:   2021-01-25 09:00:05 +0800
categories: probability
use_math: true
tags: math probability bandit information_theory
---


- <a href="https://banditalgs.com/2016/09/22/optimality-concepts-and-information-theory/" target="_blank">https://banditalgs.com/2016/09/22/optimality-concepts-and-information-theory/</a>  

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
\\[R\_n^* (A, \mathcal{E}) \leq R\_n^* (\mathcal{E})\\]
or more `relaxed version`
\\[\frac{R\_n^* (A, \mathcal{E})}{R\_n^* (\mathcal{E})} \leq \log\left( \max(1, R\_n^* (\mathcal{E})) \right)\\]
The idea is that \\(\log\left( R\_n^* (\mathcal{E}) \right)\\) is much smaller than \\(R\_n^* (\mathcal{E})\\), and we do not want our near-maximal policy \\(A\\) to produce regret wrt such value (proportional)

- The value itself of \\(R\_n^* (\mathcal{E})\\) is of interest on its own
  - small \\(R\_n^* (\mathcal{E})\\) indicates that the problem is less-challenging in the worst-case sense
- one of core researches of bandit (or learning) theory : to understand what makes \\(R\_n^* (\mathcal{E}))\\) large or small, often as a func of \\(n, K\\)


We now state the conclusion as the theorem

> __Theorem (Worst case regret lower)__ For any \\(K\geq 2,\\ n\geq 2\\), :  
\\[R_n^*(\mathcal{E}_K) \geq c\sqrt{Kn}\\]
for some universal constant \\(c>0\\).

> <a href="https://banditalgs.com/2016/09/22/optimality-concepts-and-information-theory/" target="_blank">In particular, we see that UCB is near-minimax optimal. But how to prove that the above result? The intuition is relatively simple and can be understood by just studying Gaussian tails.</a>