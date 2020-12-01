---
layout: post
title:  "Sums of Independent Random Variables"
date:   2020-11-30 08:00:05 +0800
categories: probability
use_math: true
tags: math probability 
---

- <a href="https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-i-the-fundamentals/MITRES_6_012S18_L12AS.pdf" target="_blank">lecture 12 Sums of independent random variables; Covariance and correlation</a>
- <a href="https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-i-the-fundamentals/MITRES_6_012S18_L13AS.pdf" target="_blank">lecture 13 Conditional expectation and variance revisited; Application: Sum of a random number of independent r.v.'s</a>
- <a href="https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf" target="_blank">https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf</a>


### The PMF/PDF of X+Y (independent)

#### Discrete case : X + Y (independent)
- \\(Z=X+Y\\), \\(X,Y\\) are independent, discrete with known PDFs
- calculation of PDF reduced to `discrete convolution`
- \\(p\_Z(z) = \sum\_xP(X=x,Y=z-x) = \sum\_xP(X=x)P(Y=z-x) = \sum\_xp\_X(x)p\_Y(z-x)\\)
- To calculate \\(p\_Z(3)\\),
  1. filp \\(p\_Y\\)
  2. put it under the PMF of \\(X\\) (mathcing value)
  3. right-shift the flipped \\(p\_Y\\) by z
  4. cross-multiply and add


<img src="{{site.url}}/images/math/prob/discrete_conf.jpg" width="700">

- continuous case : same mechanics (flip, shift, etc). summation changed to integral


#### The Sum of Independent Normals
- \\(X\tilde N(\mu\_x,\sigma\_x^2), \\ Y\tilde N(\mu\_y,\sigma\_y^2)\\), independent
- let \\(Z=X+Y\\). Using continuous convolution,
  \\[f\_Z(z) = \int\_\{-\infty\}^\{\infty\}f\_X(x)f\_Y(z-x)dx\\]
  \\[= \frac\{1\}\{ \sigma\_x\sqrt\{2\pi\}\} \exp\left( \frac\{-(x-\mu\_x)^2\}\{2\sigma\_x^2\} \right) \frac\{1\}\{\sigma\_y\sqrt\{2\pi\}\} \exp\left( \frac\{-(z-x-\mu\_y)^2\}\{2\sigma\_y^2\} \right)\\]
  \\[\text\{(algebra...)\} = \frac\{1\}\{ (\sigma\_x+\sigma\_y)\sqrt\{2\pi\}\} exp\left( \frac\{-(z-\mu\_y^2-\mu\_x)^2\}\{2(\sigma\_x^2+\sigma\_y^2)\} \right)\\]
  \\[\tilde N(\mu\_x+\mu\_y,\sigma\_x^2+\sigma\_y^2\\]
- which implies that, `the sum of finitely many independent normals is normal`
- TODO: fix (algebra..) part

### Covariance
\\[\text\{cov\}(X, Y) := E\left[ (X-E[X])(Y-E[Y]) \right]\\]
if \\(X, Y\\) are independent,
\\[\text\{cov\}(X, Y) = E[ (X-E[X]) ]\cdot E[(Y-E[Y])] = 0\cdot 0 = 0\\]
__note__ that the converse \\(\text\{cov\}(X, Y) = 0 \quad\rightarrow\quad X,Y \text\{ are independent \}\\) is not true

Covariance properties
- \\(\text\{cov\}(X, X) = V[X]\\)
- \\(\text\{cov\}(X, Y) = E[XY] - E[X]E[Y]\\)
  - \\(\text\{cov\}(X, Y) = E[(X-\mu\_X)(Y-\mu\_Y)] = E[XY] - 2E[X]E[Y] +E[X][Y] = E[XY]-E[X]E[Y]\\)
- assuming zero means,
  - \\(\text\{cov\}(aX+b, Y) = E[aXY] - E[aX][Y] = aE[XY] = a\cdot \text\{cov\}(X, Y)\\)
  - \\(\text\{cov\}(X, Y+Z) = E[X(Y+Z)] = E[XY]+E[YZ] = \text\{cov\}(X, Y) + \text\{cov\}(Y, Z)\\)

#### The variance of a sum of random variables
1. two RVs case
  \\[V[X\_1+X\_2] = E[(X\_1+X\_2-E[X\_1+X\_2])^2]\\]
  \\[ = E[(X\_1-E[X\_1])^2 + 2(X\_1-E[X\_1])(X\_2-E[X\_2])+E[(X\_1-E[X\_1]^2)\\]
  \\[= V[X\_1] + 2\text\{cov\}(X\_1, X\_2) + V[X\_2]\\]
2. \\(n\\) (fixed constant) RVs case
  \\[V[X\_1+...X\_n] = \sum\_\{i=1\}^n + \sum\_\{\\{(i, j) : i\neq j\\}\}\text\{cov\}(X\_i,X\_j)\\]


#### Correlation coefs
\\[\rho(X,Y) = \frac\{\text\{cov\}(X,Y)\}\{\sigma\_X\sigma\_Y\}\\]
- normalized cov
- shows the level of linear relation
- if \\(\|\rho\|=1\\), then \\(X=Y\\) or \\(X=-Y\\).


TODO: read chap13