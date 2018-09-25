---
layout: post
title:  "Ordered set, Isomorphism and Supremum"
date:   2018-09-25 09:00:05 +0800
categories: analysis
use_math: true
tags: analysis chain totally_ordered_set well_ordered_set maximum maximal supremum least_upper_bound
---

### (totally) Ordered set

An `ordered set` \\(A,\gt\\) is a pair with a set and a <a href="{{site.url}}/analysis/2018/09/24/relation.html#order" target="_blank">order relation</a>. 

If the order relation can be applied to two elements of the set, we say that the elemtns are `comparable`. If two arbitrary elements of a set are comparable, we say that the set is a `totally ordered set` (or `linearly ordered set`).

EX) Let \\(m \| n\\) denote "\\(m\\) is divisible by \\(n\\)". Then \\(\|\\) is an order relation over \\(\mathbb\{N\}\\), since
* reflexive: \\(m\|m\\) holds for arbitrary \\(m\in \mathbb\{N\}\\)
* transitive: \\(m\|n \quad\land\quad n\|k\quad\rightarrow\quad m\|k\\) holds 
* anti-symmetric: \\(m\|n \quad\land\quad m\|n \quad\rightarrow\quad m=n\\) holds

However \\((\mathbb\{N\}, \|)\\) is not a totally ordered set. (ex - 3, 4)

A totally ordered subset of a ordered set is called as `chain`.


### Isomorphism of Sets

For two ordered sets \\((A, \leq),\\ (B, \leqslant)\\), if a function \\(f:A\mapsto B\\) such that
\\[\forall x,y\in A, x\leq y\quad\rightarrow\quad f(x)\leqslant f(y)\\]
exists, then we say that \\(f\\) is an `order-preserving function` (or increasing function).  
If a is one-to-one correspondence and \\(f, f^\{-1\}\\) are both order-preserving, we say that \\(f\\) is an `order-isomorphism`, and \\(A, B\\) are `isomorphic`. Isomorphism is denoted by
\\[A\cong B\\]


### Maximum, Maximal of a Set
Consider a ordered set \\((\\{1,2,3,4,5,6\\}, \rightarrow)\\)  
<img src="{{ site.url }}/images/math/iso.png" class="center" style="width:500px"/>  

1. `Maximum` element \\(x\\) of a set \\(A\\): for all elements, \\(x\\) is always larger
\\[\forall y\in A,\\ y\leq x \text\{ holds.\}\\]  
In \\(B\\), 6 is the maximum.  
`Minimum` of a set is defined in the same way, and 1 is the minimum of \\(B\\).
2. `Maximal` element \\(x\\) of a set \\(A\\): for every comparable elements, there is no larger element than \\(x\\).
\\[\forall y\in A, x\leq y \quad\rightarrow\quad y=x\\]
In \\(C\\), both 6 and 4 are maximal. `Minimal` is defined in the same way.

__Note__: If __every subset__ of a set (except \\(\emptyset\\)) has only one minimal element, then the set is called a `well-ordered set`.
1. \\(\mathbb\{N\}\\) is a well-ordered set, but \\(\mathbb\{Z\}\\) is not.
2. well-ordered set \\(\quad\rightarrow\quad\\) totally ordered set.  
Suppose not. Then there must be two elements \\(x,y\\) not comparable in the well-ordered set, and the set \\(\\{x,y\\}\\) does not have a minimal, so contradiction. The converse does not hold (ex - \\(\mathbb\{Z\}\\))


### Upper bound / Supremum of a Set

For an ordered set S, consider an arbitrary subset \\(E\\) of \\(S\\).
If \\(\exists\\>\beta\in S\\) such that \\(x\leq\beta\\>\forall x\in E\\), then we say that \\(\beta\\) is an `upper bound` of \\(E\\).  
Note that 
1. the upper bound \\(\beta\\) can be chosen outside of the set \\(E\\). 
2. Therefore __the existence of upper bounds may vary based on the universe of a set__.


Additionally, suppose there exists an \\(\alpha\in S\\) with:  
1. \\(\alpha\\) is an upper bound of \\(E\\).
2. If \\(\gamma<\alpha\\) then \\(\gamma\\) is not an upper bound of \\(E\\).  

Then \\(\alpha\\) is called the `least upper bound` of \\(E\\) [that there is at most one such α is clear from 2] or the `supremum` of \\(E\\), and we write
\\[\alpha=\sup E.\\]
The `greatest lower bound`, or `infimum`, of a set \\(E\\) which is bounded below is defined in the same manner.

An ordered set \\(S\\) is said to have the __least-upper-bound property__ if the following is true:
* If \\(E⊂S\\), \\(E≠\emptyset\\), and \\(E\\) is bounded above, then \\(\sup ⁡E\\) exists in \\(S\\).  
(If any set is not empty and bounded above, it must have upper bound in the universe)  


### Least Upper bound property implies Greatest Lower Bound property
__Rudin Theorem 1.11__: If \\(S\\) has least upper bound property and is bounded below, collect all the lower bounds in the universe in a set. The supremum (which is guaranteed to exists) of such set must be the infimum of \\(S\\).



Next:  

