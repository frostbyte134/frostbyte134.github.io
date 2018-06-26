---
layout: post
title:  "The Real Numbers and The Least Upper Bound Property"
date:   2018-06-25 22:34:00 +0900
categories: analysis
use_math: true
tags: analysis
---

> A set of all `rational numbers` \\(Q\\) is inadequate for many purposes.

For example, \\(Q\\)
* has certain gaps, that \\(\exists\\) no \\(x\in Q\\) s.t. \\(x^2=2\\).
* does not have the `least upper bound` property

### Order
An `order` on a set \\(S\\) is an _relation_, with following 2 properties
1. If \\(x\in S\\) and \\(y\in S\\), then one and the only one of the _statements_
\\[x<y,\quad x=y,\quad y<x\\]
holds.
2. If \\(x,y,z\in S\\), and \\(x<y,\\>y<z\\) holds, then \\(x<z\\) holds - `Transitivity`

Note: The notation \\(x\leq y\\) indicates that \\(x<y\\) or \\(x=y\\), without specifying which one of two holds. Therefore,
\\[!(x\leq y)\quad\textrm\{is\}\quad x>y.\\]

### Ordered Set
An ordered set is a set \\(S\\) in which an order is defined.

### (Least) Upper bound (property)
For an ordered set S, consider an arbitrary subset \\(E\\) of \\(S\\).
If \\(\exists\\>\beta\in S\\) such that \\(x\leq\beta\\>\forall x\in E\\), then we say that \\(\beta\\) is an `upper bound` of \\(E\\).

Additionally, suppose there exists an \\(\alpha\in S\\) with:  
1. \\(\alpha\\) is an upper bound of \\(E\\).
2. If \\(\gamma<\alpha\\) then \\(\gamma\\) is not an upper bound of \\(E\\).  

Then \\(\alpha\\)α is called the `least upper bound` of \\(E\\) [that there is at most one such α is clear from 2] or the `supremum` of \\(E\\), and we write
\\[\alpha=\sup E.\\]
The `greatest lower bound`, or `infimum`, of a set \\(E\\) which is bounded below is defined in the same manner.

An ordered set \\(S\\) is said to have the __least-upper-bound property__ if the following is true:
* If \\(E⊂S\\), \\(E≠\emptyset\\), and \\(E\\) is bounded above, then \\(\sup ⁡E\\) exists in \\(S\\).  
(If any set is not empty and bounded above, it must have upper bound in the universe)  


### Least Upper bound property implies Greatest Lower Bound property
__Rudin Theorem 1.11__: If \\(S\\) has least upper bound property and is bounded below, collect all the lower bounds in the universe in a set. The supremum (which is guaranteed to exists) of such set must be the infimum of \\(S\\).
