---
layout: post
title:  "B-spline regression (P2CP)"
date:   2018-11-03 09:00:05 +0800
categories: deep_learning
use_math: true
tags: geometry vision
---

<a href="https://cran.r-project.org/web/packages/crs/vignettes/spline_primer.pdf" target="_blank">https://cran.r-project.org/web/packages/crs/vignettes/spline_primer.pdf</a>

### B-spline
B-spline function \\(B(x)\\) is defined by
* `degree` \\(n\\) (of `spline order` \\(m=n+1\\))
* \\(N+2\\) nondecreasing `knots` vector
\\[t_0\leq ...\leq t_\{N+1\}\\]

### Augmented Knots
Define the \\(N+2+2(m-1)=N+2m=N+2n+2\\) `augmented knots` vector by adding \\(m-1\\) additional points on each side of the knots vector.
\\[t\_\{-(m-1)\}=...=t\_0\leq ... \leq t\_\{N+1\}=...=t\_\{N+m\}\\]
or, reindexing by
\\[t\_0=...=t\_\{m-1}\leq ... \leq t\_\{N+m\}=...=t\_\{N+2m-1\}\\]

### Basis function
For each augmented knots, define a set of real-valued `basis function` \\[B\_\{i,j\}(x)\quad =\quad B\_\{\text\{[knots index][recursive order <= degree]\}\}\\]
by
\\[
B\_\{i,0\}(x)=\begin\{cases\}
1 \quad\text\{if \} t\_i\leq x < t\_\{i+1\} \cr
0 \quad\text\{otherwise \} \cr
\end\{cases\}
\\]

\\[B\_\{i,j\}(x)=\alpha\_\{i,j\}B\_\{i,j-1\}(x)+[1-\alpha\_\{i+1,j\}(x)]B\_\{i+1,j-1\}(x)\\]
where
\\[
\alpha\_\{i,j\}(x)=\begin\{cases\}
\frac\{x-t\_i\}\{t\_\{i+j\}-t\_i\} \quad\text\{if \} t\_\{i\+j}\neq t\_\{i\} \cr
0 \quad\text\{otherwise \} \cr
\end\{cases\}
\\]

### B-spline function
A function which realizes the B-spline is defined by
\\[B(x)=\sum\_\{i=m-1\}^\{N+m-2\}(x),\quad x\in [t\_0,t\_\{N+1\}]\\]
__Notice that we have \\(N+2n+2\\) augmented knots, but use only the \\(N+n+1\\) control points.__

The \\(\beta = \{\beta\_0...,\beta\_\{N+n\}\}\\) is called `control points` or `de Boor points`.


### Linear regression of P2CP
1. Single point cases  
Given a point \\(x\\), we obtain a \\(N+n+1\\)-dimensional vector \\(a\\), which represents how the basis function evaluates \\(x\\).
\\[a=[B_\{m-1,n\}(x),...,B_\{N+m-2,n\}(x)\\]

Taking inner product of \\(a\\) with control points \\(\beta\\), \\[\beta = [\beta\_1,...,\beta\_\{N+n\}]\\] gives a function value how our B-splie evaluates \\(x\\).
2. Mulitiple points
Given \\(t\\) points, by elaborating 1 we obtain matrix-vector multiplication (and linear regression, or projection)
\\[
\begin\{bmatrix\}
\\ \-\\ a\_\{0\}^T \\ \-\\ \cr
\vdots \cr
\\ \-\\ a\_\{N+n\}^T \\ \- \cr
\end\{bmatrix\}
\begin\{bmatrix\}
\beta\_\{0\} \cr
\vdots \cr
\beta\_\{N+n\} \cr
\end\{bmatrix\}
\approx
\begin\{bmatrix\}
f(x\_0\) \cr
\vdots \cr
f(x\_\{N+n\}\) \cr
\end\{bmatrix\}
\\] 
\\[A\beta=x\\]
where 
* \\(A\in (t\times N+n),\\ \beta\in \Re^\{N+n\}\\), and \\(f\\) is a function we wish to approximate.

As in <a href="{{site.url}}/linear_algebra/2018/05/16/projection.html" target="_blank">(link)</a>, we want to project \\(x\\) by the subspace spanned by the columns of \\(A\\). Then the columns of \\(A\\) must be orthogonal to the error vector \\(e=x-A\beta\\), so that we obtain
\\[A^T(b-A\beta)=0\\]
\\[A^TA\beta=A^Tb\\]

Next: PseudoInverse!!! (when we have many knots, it is quite unlikely that \\(A^TA\\) is invertible)

### Python codes
```python
import matplotlib.pyplot as plt
import numpy as np
import math


# B_{i,deg}(x)
# Refer to https://cran.r-project.org/web/packages/crs/vignettes/spline_primer.pdf for the technical background
def basis(x, i, deg, knots):
    if deg == 0:
        return (1 if knots[i] <= x and x < knots[i+1] else 0)

    # compare knots_{i+deg} and knots_{i}
    def calcAlpha(i, deg, knots):
        if knots[i + deg] == knots[i]:
            return 0
        else:
            return (x - knots[i])/(knots[i + deg] - knots[i])
    
    alp1 = calcAlpha(i, deg, knots)
    alp2 = calcAlpha(i+1, deg, knots)
    return alp1*basis(x, i, deg-1, knots) + (1-alp2)*basis(x, i+1, deg-1, knots)


nKnots = 10
bDeg = 4

domain = np.linspace(0, 10, 100)


knots = np.linspace(0, 10, nKnots + 2)
func = list(map(np.cos, domain))


knots = np.concatenate((np.array([knots[0] for i in range(bDeg)]), knots), axis=0)
knots = np.concatenate((knots, np.array([knots[len(knots) - 1] for i in range(bDeg)])), axis=0)
print(len(knots))


mat = []
for input in domain:
    b = []
    for i in range(nKnots + bDeg + 1): #4 is the degree of B-spline
        b.append(basis(input, i, 4, knots))

    # print(i, ", ", basis(knots[i], i, 4, knots))
    mat.append(b)
matT = np.transpose(mat, (1, 0))

print(np.matmul(matT, mat))
b = np.matmul(np.linalg.inv(np.matmul(matT, mat)), matT)
b = np.matmul(b, func)
print(b)

ans = np.matmul(mat, b)
plt.plot(domain, ans, color='b')



x = np.linspace(3, 8, 20)
y = list(map(math.cos, x))
matt = []
for input in x:
    tb = []
    for i in range(nKnots + bDeg + 1): #4 is the degree of B-spline
        tb.append(basis(input, i, 4, knots))

    # print(i, ", ", basis(knots[i], i, 4, knots))
    matt.append(tb)

plt.plot(x, y, color='y')
plt.plot(x, np.matmul(matt, b), color='k')
plt.show()
```

