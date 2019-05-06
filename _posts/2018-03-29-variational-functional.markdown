---
layout: post
title:  "Variational optimization, Functional"
date:   2018-03-29 11:19:00
categories: deep_learning
use_math: true
tags: optimization
---
### (1) Functional

A `functional` is a function of another function.
a functional assigns a real number (not extended!) to each function
Example: \\[F(y(x)) = \int_a^bf(x,y(x),y'(x))dx \\]

where \\(y(x)\\) is a function. We cannot say that \\(f\\) is a functional, since it could diverge.

Another typical example of functional includes norms, with vectors as the inner function.





### (2) Calculus of Variations

Euler-Lagrangian equation (mechanical)

Ex) arc length of a curve (link!)

if we mechanically follow the Euler-lagrangian, then we obtain that y''=0 -> y' = c -> a line minimizes the arc length between two points.





### (3) Variational optimization



the solution is an infinite-dimensional vector (a function!)


Examples are,

- Active-contour model (snake algorithm?) : explicitly finds the curve

- Level set method : implicitly finds the curve, with level sets.

- Image denoising

