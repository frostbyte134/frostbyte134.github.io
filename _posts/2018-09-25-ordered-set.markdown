---
layout: post
title:  "Ordered set, Isomorphism and Supremum"
date:   2018-09-25 09:00:05 +0800
categories: analysis
use_math: true
tags: analysis chain totally_ordered_set well_ordered_set maximum maximal supremum least_upper_bound_property
---

### (Totally) Ordered set

An `ordered set` \\(\\{A,\gt\\}\\) is a pair with a set and a <a href="{{site.url}}/analysis/2018/09/24/relation.html#order" target="_blank">order relation</a>. 

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
If \\(f\\) is one-to-one correspondence and \\(f, f^\{-1\}\\) are both order-preserving, we say that \\(f\\) is an `order-isomorphism`, and \\(A, B\\) are `isomorphic`. Isomorphism is denoted by
\\[A\cong B\\]


<h3 id="maximum">Maximum, Maximal of a Set</h3>

Consider a ordered set \\((\\{1,2,3,4,5,6\\}, \rightarrow)\\)  
<img src="{{ site.url }}/nailbrainz.github.io/images/math/iso.png" class="center" style="width:500px"/>  

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

Note that,
* lower/upper bound of \\(\emptyset\\) can be any number.
* Thus, the supremum (least upper bound) of \\(\emptyset\\) is \\(-\infty\\)
* On the contrary, \\(\inf \emptyset=\infty\\)


### Definition of a supremum using epsilon
> Let \\(E\\) be a nonempty subset of \\(\mathbb\{R\}\\), bounded above.  
Then \\(\sup E=\alpha\\) exists i.i.f  
\\[\forall \epsilon>0,\\ \exists x\in E\\ :\\ \alpha-\epsilon<x\leq \alpha\\]

Proof
1. \\(\rightarrow\\).  
Suppose not. Then there exists no such \\(x\\), so \\(\alpha-\epsilon\\) can be a new supremum - contradiction.
2. \\(\leftarrow\\).  
Suppose not. Then there exists \\(\sup E=\alpha'\\). Considering \\(\alpha-\alpha'>0\\) into the equation as \\(\epsilon\\),
\\[\alpha-\alpha+\alpha'=\alpha'<x\leq \alpha\\]
which is a contradiciton.


<h3 id="lub_lbp"> Least Upper bound property implies Greatest Lower Bound property</h3>

__Rudin Theorem 1.11__: If \\(S\\) has least upper bound property and is bounded below, collect all the lower bounds in the universe in a set. The supremum (which is guaranteed to exists) of such set must be the infimum of \\(S\\).

Proof: Let 
* \\(U\\) be a universe with the Least upper bound property.
* \\(A\subseteq U\\) be a set, and
* \\(Q\\) be a __set of all lower bounds__ of \\(A\\). Then,\\[\forall q\in Q,\\ x\in A,\quad q\leq x\\]

Let \\(g:=\sup Q\\). We want to show that \\(g\\) is also \\(\inf A\\), using the fact that \\(g=\sup Q\\).  
Firstly since \\(g=\sup Q\\),
* \\(\forall q\in Q, g\geq q\\) (\\(g\\) is the greatest lower bound) 
* If \\(x\geq q\\ \forall q\in Q\\), then \\(x\geq g\\) 

We need to show that \\(g=\inf A\\), which is
1. \\(\forall x\in A,\\ x\geq g\\)  
Suppose not. Then \\(\exists x\in A\\ : \\ x<g\\). Consequently \\(x<g, q\leq g\\), and we want to draw \\(q\\) close enough to \\(g\\) to make \\(x < q \leq g\\), which is a contradiction of the definition of \\(Q\\). Let \\(\epsilon=g-x\\). Then since \\(g=\sup Q\\),
\\[\exists q\in Q : g-\epsilon < q \leq g\\]
\\[\exists q\in Q : g-g+x < q \leq g\\]
which is a contradiction.
2. If \\(k>g\\), then \\(k\\) is not an lower bound of \\(A\\)  
We assumed that \\(Q\\) is the set of all lower bounds of \\(A\\), and \\(k>g\geq q\\ \forall q\in Q \quad\rightarrow\quad k\notin Q\\).


### inf A = -sup -A

> Theorem: Let \\(A\in\mathbb\{R\}\\), and is lower boudned. Then
\\[\inf A = -\sup -A\\]

__Proof__: Since \\(A\\) is lower bounded and - reverses the order, \\(\beta:=\sup -A\\) exists. (Remember that \\(\mathbb\{R\}\\) has the least upper bound property)  
Then two property holds for \\(\beta\\)
1. \\(\forall -x\in -A,\\ \beta\leq -x\\)
2. If \\(\gamma < \beta\\), then \\(\exists -x\in -A \\ : \\ \gamma < x\\).

Using above 2 sequentially,
1. \\(\forall x\in A, -\beta \geq x\\) (Remember that - reverses the order, not negates)
2. If \\(-\gamma>-\beta\\), then \\(\exists x\in A \\ : \\ -\gamma > x\\).

Therefore \\(-\beta\\) is the infimum of \\(A\\).

Next:  

