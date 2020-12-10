---
layout: post
title:  "Conditioning + Sums of Independent Random Variables"
date:   2020-11-30 08:00:05 +0800
categories: probability
use_math: true
tags: math probability 
---

- <a href="https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-i-the-fundamentals/MITRES_6_012S18_L12AS.pdf" target="_blank">lecture 12 Sums of independent random variables; Covariance and correlation</a>
- <a href="https://ocw.mit.edu/resources/res-6-012-introduction-to-probability-spring-2018/part-i-the-fundamentals/MITRES_6_012S18_L13AS.pdf" target="_blank">lecture 13 Conditional expectation and variance revisited; Application: Sum of a random number of independent r.v.'s</a>
- <a href="https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf" target="_blank">https://vfu.bg/en/e-Learning/Math--Bertsekas_Tsitsiklis_Introduction_to_probability.pdf</a>


Conditioning  
<img src="{{site.url}}/images/math/prob/cond.jpg" width="700">  
- condition is similar to the process of re-normalizing. We collect all samplespace components which is relevant with \\(A\\), add them up and renormalize to construct the conditional pdf/pmf.

### Discrete case : X + Y (independent)
- Let \\(Z:=X+Y\\), where \\(X,Y\\) are independent, discrete RVs with known PDFs
- __calculation of PDF reduced to__ `discrete convolution`
- \\(p\_Z(z) = \sum\_xP(X=x,Y=z-x) = \sum\_xP(X=x)P(Y=z-x) = \sum\_xp\_X(x)p\_Y(z-x)\\)
- To calculate \\(p\_Z(3)\\),
  1. filp \\(p\_Y\\)
  2. put it under the PMF of \\(X\\) (mathcing value)
  3. right-shift the flipped \\(p\_Y\\) by z
  4. cross-multiply and add


<img src="{{site.url}}/images/math/prob/discrete_conf.jpg" width="700">

- continuous case : same mechanics (flip, shift, etc). summation changed to integral


### The Sum of Independent Normals
- \\(X\sim N(\mu\_x,\sigma\_x^2), \\ Y\sim N(\mu\_y,\sigma\_y^2)\\), independent
- let \\(Z=X+Y\\). Using continuous convolution,
  \\[f\_Z(z) = \int\_\{-\infty\}^\{\infty\}f\_X(x)f\_Y(z-x)dx\\]
  \\[= \frac\{1\}\{ \sigma\_x\sqrt\{2\pi\}\} \exp\left( \frac\{-(x-\mu\_x)^2\}\{2\sigma\_x^2\} \right) \frac\{1\}\{\sigma\_y\sqrt\{2\pi\}\} \exp\left( \frac\{-(z-x-\mu\_y)^2\}\{2\sigma\_y^2\} \right)\\]
  \\[\text\{(algebra...)\} = \frac\{1\}\{ (\sigma\_x+\sigma\_y)\sqrt\{2\pi\}\} exp\left( \frac\{-(z-\mu\_y^2-\mu\_x)^2\}\{2(\sigma\_x^2+\sigma\_y^2)\} \right)\\]
  \\[\sim N(\mu\_x+\mu\_y,\sigma\_x^2+\sigma\_y^2)\\]
- which implies that, `the sum of finitely many independent normals is normal`
- TODO: fix (algebra..) part
  - maybe with MGF? we dont need to waste time

### Covariance
\\[\text\{cov\}(X, Y) := E\left[ (X-E[X])(Y-E[Y]) \right]\\]
if \\(X, Y\\) are independent,
\\[\text\{cov\}(X, Y) = E[ (X-E[X]) ]\cdot E[(Y-E[Y])] = 0\cdot 0 = 0\\]
__note__ that the converse \\(\text\{cov\}(X, Y) = 0 \quad\rightarrow\quad X,Y \text\{ are independent \}\\) is not true

Covariance properties
- \\(\text\{cov\}(X, X) = V[X]\\)
- \\(\text\{cov\}(X, Y) = E[XY] - E[X]E[Y]\\)
  - \\(\text\{cov\}(X, Y) = E[(X-\mu\_X)(Y-\mu\_Y)] = E[XY] - 2E[X]E[Y] +E[X][Y] = E[XY]-E[X]E[Y]\\)
- \\(\text\{cov\}(aX+b, Y) = a\cdot \text\{cov\}(X, Y)\\)
- \\(\text\{cov\}(X, Y+Z) = \text\{cov\}(X, Y) + \text\{cov\}(X, Z)\\)

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


### Conditional Expectation as a Random Variable
define \\(g(y) = E[X\|Y=y] = \sum\_xxP[X=x \| Y=y] \\) (integral in continuous case)
- then \\(g(Y)\\) is the RV that yields the value \\(E[X\|Y=y]\\), if \\(Y\\) happens to take the value \\(y\\).

> Definition \\(E[X\|Y] := g(Y)\\)

__Remarks__
- It is a function of \\(Y\\) (composition) (\\(Y\\) is also a function, from the sample space to real line)
- It is a random variable
  - __Thus it has a distribution, mean, var, etc.__

#### The mean of E[X|Y] : Law of iterated expectations
\\[E[E[X\|Y]] = E[X]\\]

__proof__ : 
\\[
\begin\{align\*\}  
E[E[X\|Y]] = E[g(Y)] &= \sum\_yE[X\|Y=y]P[Y=y] \cr
                     &= \sum\_y(\sum\_xxP[X=x\|Y=y])P[Y=y] \cr
                     &= \sum\_y(\sum\_xxP[X=x\|Y=y]P[Y=y]) \cr
                     &= \sum\_xx(\sum\_yxP[X=x,Y=y]) \cr
                     &= \sum\_xxP[X=x]
\end\{align\*\}                       
\\]


stick-breaking example
- \\(E[Y] = \int\_0^\infty yP[Y=y] = \int\_0^l y\frac\{1\}\{l\} = \frac\{1\}\{l\}[\frac\{1\}\{2\}y^2]\_0^l = l/2\\)

### Conditional Variance as a Random Variable
- \\(V[X] = E[(X-E[X])^2]\\)
- \\(V[X\|Y=y] = E[(X-E[X\|Y=y])^2 \| Y=y]\\)
  - \\(V[X\|Y]\\) is the random variable that yields the value \\(V[X\|Y=y]\\), when \\(Y=y\\)

ex) \\(X\\) uniform on \\([0, Y]\\)
- \\(E[X\|Y=y] = \int\_0^yx\cdot\frac\{1\}\{y\}dx = y/2\\)
- \\(V[X\|Y=y] = E[X^2\|Y=y] - (E[X\|Y=y])^2\\)
  - \\(E[X^2\|Y=y] = \int\_0^yx^2\cdot\frac\{1\}\{y\} = \frac\{1\}\{y\}[\frac\{x^3\}\{3\}]\_0^y = y^2/3\\)
  - thus, \\(V[X\|Y=y] = y^2/3-y^2/4 = y^2/12\\)
  - which gives, \\(V[X\|Y] = Y^2/12\\)

> Law of total variance \\(V[X] = E[V[X \| Y]] + V[E[X \| Y]]\\)

__proof__ : 
- \\(V[X\|Y=y] = E[X^2\|Y=y] - (E[X\|Y=y])^2\\)
- \\(V[X\|Y] = E[X^2\|Y] - (E[X\|Y])^2\\)
  - \\(E[V[X\|Y]] = E[X^2] - E[(E[X\|Y])^2]\\)
  - \\(V[E[X \| Y]] = E[(E[X\|Y])^2] - (E[(E[ X \|Y ] ])^2 = E[(E[X\|Y])^2] - (E[X])^2 \\)
  - adding above two terms gives us the desired equality


example  

<img src="{{site.url}}/images/math/prob/simple.jpg" width="400">
- assume \\(P[Y=1] = P[Y=2] = 1/2\\)
- \\(E[X] = \frac\{1\}\{2\}[x^2/2]\_0^1 + \frac\{1\}\{4\}[x^2/2]_1^3 = 5/4 \\)
- \\(E[E[X \| Y]] = p\_Y(1)E[X\|Y=1] + p\_Y(2)E[X\|Y=2]\\)
  - \\( E[X\|Y=1] \\) : \\(X\\) given \\(Y=1\\) has meaningful (uniform) pdf at \\([0, 1]\\), thus \\(\int\_0^1 x dx = 1/2\\)
  - \\( E[X\|Y=2] \\) : \\(X\\) given \\(Y=2\\) has meaningful (uniform) pdf \\([1, 3]\\), thus \\(\int\_2^3 x \cdot \frac\{1\}\{2\dx = 2\\)
  - \\(E[E[X \| Y]] = \frac\{1\}\{2\}E[X\|Y=1] + \frac{1}{2}E[X\|Y=2] = 5/4 = E[X]\\) !

- \\(E[V[X \| Y]] = p\_Y(1)V[X\|Y=1] + p\_Y(2)V[X\|Y=2]\\)
  - \\( E[X^2\|Y=1] \\) : \\(X\\) given \\(Y=1\\) has probability at \\([0, 1]\\), thus \\(\int\_0^1 1\cdot x^2dx = 1/3\\)
    - \\(V[X\|Y=1] = 1/3-(1/2)^2 = 1/12\\)
  - \\( E[X^2\|Y=2] \\) : \\(X\\) given \\(Y=2\\) has probability at \\([1, 3]\\), thus \\(\int\_2^3 1\cdot \frac\{1\}\{2\}x^2dx = 13/3\\)
    - \\(V[X\|Y=2] = 13/3-2^2 = 1/3\\)
  - \\(E[V[X \| Y]] = 1/2 * 1/12 + 1/2 * 1/3 = 5/24\\)
- \\(V[E[X\|Y]]\\) : we can calculate the expectation of \\((E[X\|Y] - E[E[X\|Y]])^2\\) for each \\(y\in \\{1,2\\}\\)
  1. \\(Y=1\\) : \\((E[X\|Y] - E[E[X\|Y]])^2 = (1/2 - 5/4)^2\\)
  2. \\(Y=2\\) : \\((E[X\|Y] - E[E[X\|Y]])^2 = (2 - 5/4)^2\\)
  3. calculating expectation \\(p\_Y(1)(E[X\|Y=1] - E[E[X\|Y=1]])^2 + p\_Y(2)(E[X\|Y=2] - E[E[X\|Y=2]])^2 = 9/16\\) !
- now we have, \\(V[X] = E[V[X\|Y]] + V[E[X\|Y]] = 37/48\\)
  - \\(E[V[X\|Y]]\\) : __average variability within sections__, and sections refers each \\(y \in \\{1,2\\}\\)
  - \\(V[E[X\|Y]]\\) : __variability between sections__ \\(y \in \\{1,2\\}\\)


### Sum of a Random Number of Independent RVs

Let
- \\(N\\) : number of stores visited (Non-negative integer R.V)
- \\(X\_i\\) : money spent in store \\(i\\)
  - \\(X\_i\\)s are independent, identically distributed (i.i.d)
  - independent of \\(N\\)
let \\(Y=X\_1+...+X\_N\\)


1. calculating \\(E[Y]\\)
  - \\(E[Y\|N=n] = E[X\_1+...+X\_n \| N=n] = E[X\_1+...+X\_n] = nE[X]\\)
  - thus, \\(E[Y\|N] = NE[X]\\)
  - Now we can calculate \\(E[Y]\\) in two ways,
    - total expectation theorem : \\(E[Y] = \sum\_np\_N(n)E[Y\|N=n] = \sum\_np\_N(n)nE[X] = E[X]\sum\_np\_N(n)n = E[X]E[N]\\)
    - Law of iterated expectation : \\(E[Y] = E[E[Y\|N]] = E[N]E[X]\\)
2. calculating \\(V[Y] = E[V[Y\|N]] + V[E[Y\|N]]\\)
  - \\(E[V[Y\|N]]\\)
    - \\(V[Y\|N=n] = V[X\_1+...+X\_N\|N=n] = V[X_1+...+X\_n] = nV[X]\\)
    - thus, \\(V[Y\|N] = NV[X]\\)
  - \\(V[E[Y\|N]]\\)
    - \\( = V[NE[X]] = E[X]^2V[N]\\)
   - now we have, \\(V[Y] = NV[X] + E[X]^2V[N] \\)


Random sum of geometric number of geometric/exponential is geometric/exponential - refer to the MGF page