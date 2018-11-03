---
layout: post
title:  "B-spline regression (P2CP)"
date:   2018-11-03 09:00:05 +0800
categories: deep_learning
use_math: true
tags: geometry vision
---

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

