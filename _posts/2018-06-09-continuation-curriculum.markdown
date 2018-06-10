---
layout: post
title:  "Continuation Methods and Curriculum Learning"
date:   2018-06-09 10:34:00 +0900
categories: deep_learning
use_math: true
tags: optimization deep_learning need_revise
---

### Continuation Method
> `Continuation methods` are a family of strategies that can make optimization easier by choosing initial points to ensure that _local optimization spends most of its time in well-behaved resion of space__. 

The idea behind is constructing a series of objective functions over the __same parameters__.  

To optimize a cost function \\(J(\theta)\\), we construct new cost functions \\(\\{J^\{(0)\},...,J^\{(n)\}\\}\\), where \\(J^\{(n)\}=J(\theta)\\) being the most difficult.  
When we say that \\(J^\{(i)\}\\) is more `easier` than \\(J^\{(i+1)\}\\), we mean that it is well behaved (convex) over more of \\(\theta\\) space. The series of cost functions are designed so that a solution to one is a good initial point of the next. We thus begin by solving an easy problem, then refine the solution to solve incrementally harder problems until we arrive at a solution to the true underlying problem.

Survey papers: Mobahi and Fisher (2015)

### Local minima and Continuation methods
Tradionally, continuation methods were used to tackle local minima problem. Specifically, they were designed to reach a golbal minimum despite the presence of many local minima. An example of such construction is 'blurring'
\\[J^\{(i)\}(\theta)=\mathbb\{E\}_\{\theta `;\theta,\sigma^\{(i)\}\}J(\theta `)\\]
(\\(J^\{(i)\}(\theta)\\) is obtained by sampling from gaussian centered at \\(\theta\\), and taking expectaion over \\(J\\) with samples)  
The intuition for this is that some nonconvex functions become approximately convex when blurred.

However, local minima is no longer believed to be the primary problem for neural entwork optimization. But still, continuation methods can be help. The easier objective functions introduced by the continuation method can eliminate flat regions, decrease variancce in gradient estimates, improve conditioning of the Hessian matrix, or do anything else that will either make local updates easier to compute or improve the correspondance betyween local update directions and progress toward a global solution.

### Curriculum learning (shaping)
Bengio et al (2009), Zaremba and sutskever(2014)



<hr>
<br/><br/>
Next:  
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>