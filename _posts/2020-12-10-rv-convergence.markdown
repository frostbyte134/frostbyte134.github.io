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

Define \\[\text{Sample mean  } M\_n:=\frac{X\_1+...+X\_n}{n}\\]
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

> __Definition__ : Weak Law of Large Numbers (WLLN). For \\(\epsilon > 0\\), 
  \\[P[\|M\_n-\mu\|\geq \epsilon ]\rightarrow 0, \quad\quad \text{as } n\rightarrow\infty\\]

\\[\text{Sample mean converges to true mean in probability}\\]

Interpretation
- One experiment, Many measurements \\(X\_i=\mu+W\_i\\)
  - \\(W\_i\\) : iid measurement noise, \\(E[W\_i]=0\\)
- sample mean \\(M\_n\\) is unlikely to be far off from the true mean \\(\mu\\)



### The Pollster's Problem
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
  - But can gurantee the probability \\[P[\|M\_{10,000}-p] \leq \frac{signa^2}{n\epsilon^2} = \frac{p(1-p)}{10^4 10^{-4}} \leq \frac{1}{4}\\]  
    (last inequality comes from the fact that \\(p(1-p)\\) is concave, maximum at \\(p=1/2\\))  
    "probability that the difference of estimation is larget than 0.01 is less than 25%"  
  - if we want 5% of such number, solve \\[\frac{1/4}{n10^{-4}}\leq \frac{5}{100} \quad\rightarrow\quad n>> \frac{10^6}{20} = 50,000\\]
  - we have two parameters here  
      1. `accuracy` 1%
      2. `confidence` 5%
  - accuracy of 0.01 is somewhat high. Many polls assumes 3%~5% accuracy
  - more better inequality (Cramer-rao?) gives much smaller \\(n\\) (rather than 50,000)


### Convergence in Probability
example : `WLLN`

> __Definition:__ A sequence \\(Y\_n\\) converges in probability to a number \\(a\\) if : 
  \\[\text{ for any } \epsilon > 0 , \lim\_{n\rightarrow\infty}P[\|Y\_n-a\| \geq \epsilon ]=0\\] 

- The distribution of \\(Y\_n\\) is concentrated near \\(a\\), for some \\(n\geq n\_0\\) and \\(\epsilon\\)
- no independence assumption

<img src="{{site.url}}/images/math/prob/conv_prob.jpg" width="1000">  


Properties
* Suppose \\(X\_n\rightarrow a, Y\_n\rightarrow b\\) in probability
  * If \\(g\\) is continuous, then \\(g(X\_n)\rightarrow g(a)\\)
  * \\(X\_n+Y\_n\rightarrow a+b\\)
  * __BUT__, \\(E[X\_n]\\) __need not converge to__ \\(a\\). Convergence in probability does not imply the convergence of expectations


#### Example 1.
\\[ P\_{Y\_n}(y)=
\begin{cases}
  1-(1/n) & y=0 \cr
  1/n & y=n^2
\end{cases}  
\\]

<img src="{{site.url}}/images/math/prob/conv_prob_example.jpg" width="500"> 

- We see that, \\(P[\|Y\_n-0\|\geq \epsilon] = 1/n\\), which converges to 0 as \\(n\rightarrow \infty\\).
- However, \\(E[Y\_n] = n^2\cdot(1/n) =n \\), which goes to \\(\infty\\) as \\(n\rightarrow \infty\\).
- Convergence in probability does not imply the convergence of expectations, since __expectation is very sensitive to the tail__


#### Example 2
- \\(X\_i\\) : i.i.d, uniform on [0, 1]
- \\(Y\_n=\min\\{X\_1,...,X\_n\\}\\)
  - gives the inequality \\(Y\_{n+1}\leq Y\_n\\), which implies convergence


We will show that, \\(Y\_n\rightarrow 0\\) in probability
1. Fistly, since \\(Y\_n>0 \forall n\\), \\(P[\|Y\_n-0\|\geq \epsilon] = P[Y\_n \geq \epsilon]\\) 
2. We see that, 
   \\[ 
   \begin\{align\*\}  
    P[Y\_N\geq \epsilon] &= P[X\_1\geq \epsilon \& ... \& X\_n \geq \epsilon] \cr
                         &= P[X\_1\geq \epsilon]\times \vdots \times P[X\_n \geq \epsilon] \cr
                         &= (1-\epsilon)^n
    \end\{align\*\}    
   \\]
   we indeed see that the \\(Y\_n\rightarrow 0\\) in probability holds.

__Related topics__
1. Better bounds/approximations on tail probabilities
   - Markov/Chevyshev
   - Chernoff bound \\(P[\|M\_n-\mu\| \geq a] \leq \exp(-nh(a))\\). Much stronger than Chevyshev, but need more assumptions
   - __Central limit theorem__ : \\(M\_n\\) behaves like a normal RV
2. Different types of convergence
   - convergence in probability
   - convergence with probability 1
     - in a single experiment, consider seq of RVs \\(Y\_n\\) and a RV \\(Y\_n\\).
     - for an trial \\(\omega\\), \\(P[\\{\omega : Y\_n(\omega) \rightarrow\_{n\rightarrow\infty} Y(\omega)\\}]=1\\)
     - stronger than "in probability"
     - __Strong law of large numbers:__  sample mean converges to true mean in probability 1
   - convergence of a sequence of distributions __(CDF!)__ to a limiting CDF
     - used in CLT (CLT talks about distribution)



### Convergence in Probability of the Sum of Two Random Variables
\\[\text{If }X\_n\rightarrow a \text{ and }Y\_n\rightarrow b\text{, then} X\_n+Y\_n\rightarrow a+b \text{ (in probability)}\\]
- Convergence in probability is quite similar to the convergence of sequences

Preliminary : prove above in sequences (use \\(\epsilon / 2\\) for each convergence)

1. For an arbitrary \\(\epsilon > 0\\), we want to show that \\[P[\|X\_n+Y\_n-a-b\| \geq \epsilon ] \rightarrow 0\\]
2. We see that \\[\\{\| (X_n - a) + (Y\_n - b) \| \geq \epsilon \\}\subset \\{\|X\_n-a\|\geq \epsilon/2 \text{ or } \| Y\_n-a \| \geq \epsilon/2\\}\\]  
   which implies \\[P[ \| (X_n - a) + (Y\_n - b) \| \geq \epsilon] \leq P[ \| X\_n-a \| \geq \epsilon/2 \text{ or } \| Y\_n-a \| \geq \epsilon/2] \leq P[ \| X\_n-a \| \geq \epsilon/2] + P[ \| Y\_n-a \| \geq \epsilon/2]\\]
3. Thanks to the assumption each \\(P[ \| X\_n-a \| \geq \epsilon/2]\\) converges to 0. This is the convergence of sequence, so we can apply the preliminary, so their sum converges to 0. 


### Jensen's Inequality
for a convex \\(g\\), 
\\[E[g(X)] \leq g(E[X])\\]
(remember that the expectation is a convex combination)


### Hoeffding's Inequality
\\[P(X\_1+...+X\_n\geq na) \leq \exp\\{-na^2/2\\}\quad\quad\quad X\_i : i.i.d\\]
 
and
\\[
X\_i=
\begin{cases}
  1 & \text\{ with probability \} 1/2 \cr
  -1 & \text\{ with probability \} 1/2 
\end{cases}  
\\]


 Note that the Chevyshev inequality (which equivalently tells us sth about the tail probability) states that \\(p(X\_1+...+X\_n\geq na) \leq 1/(na^2)\\), so Hoeffding's inequality is much stronger. Using the CLT+CDF of normal gives much weaker bound, even than  Chevyshev.

Assumptions
- \\(a>0\\)
- \\(s>0\\)

 Trick : Instead of looking at event \\(X\_1+...+X\_n\geq na\\), we take a look at equivalent event
 \\[P[e^{s(X\_1+...+X\_n)} \geq e^{sna}]\\]
 using Markov's inequality, we can bound above term by
 \\[\leq E[e^{s(X\_1+...+X\_n)}]/ e^{sna}\\]
 \\[\leq E[e^{s(X\_1)}]^n / e^{sna} = \left( \frac{E[sX\_1]}{e^{sa}} \right)^n = \rho^n\\]

 For any \\(s>0\\) above holds. We choose \\(s>0\\) which gives most useful bound \\(\rho<1\\).

Fistly
1. \\(E[e^{sX\_1}]^n = (\frac{\frac{1}{2}(e^s+e^{-s})}{e^{sa}})^n\\)
2. numerator \\(\frac{1}{2}(e^s+e^{-s})\\) has its minimum at 0 with value 1, symmetric.
3. denominator \\(e^{sa}\\) has value 1 at 0, and will be larger than numerator for small \\(s>0\\).

`Hoeffding's inquality`
\\[\left( \frac{\frac{1}{2}(e^s+e^{-s})}{e^{sa}} \right)^n \leq e^{-na^2/2}\\]
relies on the specific form of the distribuion of \\(X\\), but `Chernoff's bound` generalizes it (__TODO__: add link!)

__proof__ : remember the Taylor series \\(e^s=1+s+s^2/2! + s^3/3! = \sum\_{i=0}^\infty \frac{s^i}{i!}\\)  
so that
\\[\frac{1}{2}(e^s+e^{-s}) = \sum\_{i=0}^{\infty}\frac{s^{2i}}{(2i)!}\\]
Note that
\\[(2i)! = 1\cdot 2 ... \cdot i \cdot (i+1) ... (2i) \geq i! \cdot 2^i\\]
which gives
\\[\sum\_{i=0}^{\infty}\frac{s^{2i}}{(2i)!} \leq \sum\_{i=0}^{\infty}\frac{s^{2i}}{i!2^i} = \sum\_{i=0}^{\infty}\frac{(s^2/2)^{i}}{i!} = e^{s^2/2}\\]

Consequently,
\\[\left( \frac{\frac{1}{2}(e^s+e^{-s})}{e^{sa}} \right)^n \leq \frac{ e^{s^2/2}}{e^{sa}} \leq (e^{e^{s^2/2 - sa}})^n\\]
selecting \\(s=a\\) gives Hoeffding's inequality