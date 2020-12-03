---
layout: post
title:  "(Linear) Least Square Estimation (and Bivariate Normal)"
date:   2020-12-03 08:00:05 +0800
categories: probability
use_math: true
tags: math probability 
---
{:.acounter}


> <a href="https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf" target="_blank">chap 4</a>


let \\(X\\) be a random variable we want to estimate.

### Visible X case

For any estimate \\(c\\), let \\(E[X] = m\\). then
\\[
\begin\{align\*\}  
E[(X-c)^2] &= E[(X-m+m-c)^2] \cr
           &= E[(X-m)^2] + 2E[(X-m)(m-c)] + E[(m-c)^2]  \cr
           &= E[(X-m)^2] + 2(E[X]-m)(m-c)] + (m-c)^2  \cr
           &= E[(X-m)^2] + (m-c)^2
\end\{align\*\}    
\\]
\\[E[(X-m)^2\leq E[(X-c)^2]]\\]

We see that \\(E[(X-c)^2]\\) is a __quadratic function__, which is minimized with the value \\(E[(X-m)^2]=V[X]\\).


<img src="{{site.url}}/images/math/prob/ls1.jpg" width="300">

> Best least square estimate of \\(X\\) is \\(E[X]\\)

read example 4.27 in the link pdf

### latent, hidden X case

Now suppose that we cannot observe \\(X\\) directly, but instead we have observable \\(Y\\) (=`measurement`)

Given the observation \\(Y=y\\), what is the best estimate?
   1. Once we told that \\(Y\\) takes the value \\(y\\), the situation is identical to above, except that we are now in a __NEW UNIVERSE__ that everything is conditioned on \\(Y=y\\))
   2. Using same steps (now the variable \\(c\\) is \\(g(y)\\), any estimator using \\(y\\)), we see that \\[E[(X-E[X\|Y=y])^2 \| Y=y] \leq E[(X-g(y))^2\|Y=y]\\]
   3. This inequality is indeed true for every possible (meaningful) value of \\(Y\\), thus  \\[E[(X-E[X\|Y])^2 \| Y] \leq E[(X-g(Y))^2\|Y]\\]
   4. Above is an inequality between random variables (functions of \\(Y\\)!). Using iterated expectation,  
      \\[E[E[(X-E[X\|Y])^2 \| Y]] \leq E[E[(X-g(Y))^2\|Y]]\\]
      \\[E[(X-E[X\|Y])^2]  \leq E[(X-g(Y))^2\]\\]  
      for all functions \\(g(Y)\\).



> Best least square estimate of \\(X\\) given(using) \\(Y\\) is \\(E[X\|Y]\\)

read "some property of the estimation error" part


### Linear Least Square Estimation


Now suppose that we have many measurements \\(Y\_1,...,Y\_n\\).
- Using the same argument, we easily see that \\[E[(X-E[X\|Y\_1,...,Y\_n])^2]  \leq E[(X-g(Y\_1,...,Y\_n))^2\]\\]  
- __However__, the to calculate above we need joint PDF/PMF over \\(P(X, Y\_1,...,Y\_n)\\), which is often untractable.
- The most common approach involves `linear estimator`s, \\[a\_1Y\_1+,...+a\_nY\_n+b\\], which gives following mean squared error \\[(X-a\_1Y\_1-...-a\_nY\_n-b)^2\\]
  - __this problem only requires the mean, var, covar of the RVs__


#### LLS with single estimation
We are interested in finding \\(a,b\\) that minimizes the mean squared estimation \\(E[(E-aY-b)^2]\\).

1. Suppose that \\(a\\) has already chosen (or, let it be chosen arbitrarily). 
2. The problem is now reduced to estimate RV \\(aX-Y\\), and by the above contents, the __best choice__ is \\[b=E[X-aY]=E[X] - aE[Y]\\]
3. Now the problem is reduced to \\[\min\_aE[(X-aY-E[X]+aE[Y])^2]\\]
   which is
   \\[
    E[\left( (X-E[X]) -a(Y-E[Y]) \right)^2] 
    \begin\{align\*\}  
        &= E[(X-E[X])^2]+a^2E[(Y-E[Y])^2]-2aE[(X-E[X])(Y-E[Y])]
        &= \sigma\_X^2 + a^2\sigma\_Y^2 -22a\cdot \text{cov}(X, Y)
    \end\{align\*\}  
    \\]
    This is quadratic (thus convex) function. Optimality condition gives
    \\[a=\frac{\text{cov}(X, Y)}{\sigma\_Y^2}=\frac{\rho \sigma\_X\sigma\_Y}{\sigma\_Y^2}=\rho\frac{\sigma\_X}{\sigma\_Y}\\]
    where \\(\rho:=\frac{\text{cov}(X, Y)}{\sigma\_X\sigma\_Y}\\) is the correlation coefficient.
4. With the such choice of \\(a\\), the linear mean squared estimation error is given by
   \\[\sigma\_X^2+a^2\sigma\_Y^2-2a\text{cov}(X, Y) = \sigma\_X^2+\rho^2\frac{\sigma\_X^2}{\sigma\_Y^2}\sigma\_Y^2-2\rho\frac{\sigma\_X}{\sigma\_Y}\rho\sigma\_X\sigma\_Y\\]
   \\[ = (1-\rho^2)\sigma^2\_X\\]

In summary,

<img src="{{site.url}}/images/math/prob/llms.jpg" width="300">



### The bivariate normal

체력이 후달리네..내일 ㅡㅡㅋ
