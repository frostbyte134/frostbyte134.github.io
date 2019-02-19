---
layout: post
title:  "Estimating Randon Variables with Expectations (Markov, Chevyshev)"
date:   2019-02-19 07:00:05 +0800
categories: probability
use_math: true
tags: probability point_estimation inequality
---

### Markov's Inequality

For a RV \\(X\\) s.t. \\(P[X<0]=0\\), \\(c\in\Re,\\ c>0\\), 
\\[P[X\geq c^2]\leq \frac\{E[X]\}\{c^2\}\\] 

* The theorem implies that, _the distribution function (`CDF`, for some RVs) can be expressed in terms of the expectation_.
\\[F\_X(c^2)\geq 1-\frac\{E[X]\}\{c^2\}\\]
* Why \\(c^2\\), rather than \\(c\\)? \\(\quad\rightarrow\quad\\) for the relevance with the Chevyshev's inequality

__Proof__  
Since \\(X>0\\) almost surely, \\(f\_X(x)=0\\) for \\(x<0\\) and
\\[E[X]=\int\_\{0\}^\{c^2\} xf\_X(x)dx + \int\_\{c^2\}^\{\infty\} xf\_X(x)dx\\]
\\[\geq \int\_\{c^2\}^\{\infty\} xf\_X(x)dx\\]
\\[\geq c^2\int\_\{c^2\}^\{\infty\} f\_X(x)dx\\]
where the last inequality holds by the fact that \\(x>c^2\\) in the integral area 

### Chevyshev Inequality
For a RV \\(Y\\) and \\(c\in\Re,\\ c>0\\), 
\\[P[\| Y-\mu\_\{Y\}\| \geq c] \leq \frac\{V[Y\]\}\{c^2\}\\]

* If \\(V[Y]=0\\), then \\(P[Y=0]\\) with probability 1.
* Convergence of the sample mean, to the \\(E[X]\\) (?)

__Proof__  
In Markov's inequality, let
\\[X=(Y-\mu\_\{Y\})^2\\]
be a derived RV. Then,
\\[P[(Y-\mu\_\{Y\})^2\geq c^2] \leq \frac\{E[(Y-\mu\_\{Y\})^2]\}\{c^2\}\\]
\\[\rightarrow\\ P[\| Y-\mu\_\{Y\}\| ] \leq \frac\{V[X]\}\{c^2\}\\]

* For some nonnegative RVs, Chevyshev's inequality sometimes provides better bound than Markov's.  
Compare
\\[P[X\geq c^2]\leq \frac\{E[X]\}\{c^2\}\\] 
with
\\[P[\| X-\mu\_\{X\}\| \geq d] \leq \frac\{V[X\]\}\{d^2\}\\]
\\[\rightarrow\\ P[X \geq d+\mu\_\{X\}] \leq \frac\{V[X\]\}\{d^2\}\\]
Letting \\(d=c^2-\mu\_\{X\}\\), above holds for RVs with
\\[\frac\{E[X]\}\{c^2\} > \frac\{V[X\]\}\{(c^2-\mu\_\{X\})^2\}\\]


Next:  

