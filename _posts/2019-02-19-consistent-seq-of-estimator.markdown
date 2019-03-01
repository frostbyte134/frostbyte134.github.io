---
layout: post
title:  "Consistent Sequence of Estimators"
date:   2019-02-19 08:00:05 +0800
categories: probability
use_math: true
tags: probability point_estimation inequality
---

### Definitions
1. The __sequence of estimators__ \\(\hat\{R\}\_\{1\},\\ \hat\{R\}\_\{2\},...\\) of a parameter \\(r\\) is `consistent` if
\\[\lim\_\{n\rightarrow\infty\}P[\| \hat\{R\}\_\{n\} -r\| \geq \epsilon] = 0\\]
(We want to bound the realized values of a RV(estimator) with expectation)
2. __An estimator__ \\(\hat\{R\}\\) of a param \\(r\\) is `unbiased` if
\\[E[\hat\{R\}]=r\\]
otherwise, \\(\hat\{R\}\\) is biased.
3. The __sequence of estimators__ \\(\hat\{R\}\_\{n\}\\) of parameter \\(r\\) is `asymptotically unbiased` if
\\[\lim\_\{n\rightarrow\infty\}E[\hat\{R\}\_\{n\}]=r\\]
4. The mean square error (`MSE`) of an estimator \\(\hat\{R\}\\) of parameter \\(r\\) is
\\[e=E[(\hat\{R\}-r)^2]\\]

### Theorem
> If a sequence of `unbiased` estimators \\(\hat\{R\}\_\{1\},\\ \hat\{R\}\_\{2\},...\\) of parameter r has `MSE` \\(e\_n=V[\hat\{R\}\_\{n\}]\\) safisfying
\\[\lim\_\{n\rightarrow\infty\}e\_n=0\\]
then the sequence \\(\hat\{R\}\_\{n\}\\) is `consistent`.

__Proof__:  
Since \\(E[\hat\{R\}\_\{n\}]=r\\), we can restate MSE of \\(\hat\{R\}\_\{n\}\\) as \\(V[\hat\{R\}\_\{n\}]\\) (as stated in the theorem), and by applying `Chevyshev`'s inequality to \\(\hat\{R\}\_\{n\}\\),
\\[P[\| \hat\{R\}\_\{n\}-r\| \geq \epsilon]\leq \frac\{V[\hat\{R\}\_\{n\}]\}\{\epsilon^2\}\\]
Taking \\(n\rightarrow\infty\\) gives
\\[\lim\_\{n\rightarrow\infty\}P[\| \hat\{R\}\_\{n\}-r\| \geq \epsilon]\leq \lim\_\{n\rightarrow\infty\}\frac\{V[\hat\{R\}\_\{n\}]\}\{\epsilon^2\} = 0\\]

Next:  

