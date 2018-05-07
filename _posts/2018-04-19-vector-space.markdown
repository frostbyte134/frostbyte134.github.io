---
layout: post
title:  "Vector, Vector spaces"
date:   2018-04-19 22:41:00
categories: linear_algebra
use_math: true
tags: linear_algebra
---

### (1) Definition of a Vector space

\\(\forall x,y\in V, \alpha\in\Re\\), if \\[x+y\in V\\] \\[\alpha x\in V\\]holds, then \\(V\\) is a vector space (more thoroughly?)



### (2) Basis, and representation of a vector (coordinate system).

Every vector in a n-dimensional vector space can be represented with n basis and n corresponding coordinates. Such coordinates must satisfy above two conditions, since they are genuine representation of all of the vector in a vector space.

Generally we use n-dimensional tuple \\((a_1,...,a_n)\\) to represent a single vector in the space. This implicitly assumes the usage of standard basis \\((e_1 ,..., e_n)\\).

However, we can represent such vector with any n-basis \\((b_1,...,b_n)\\). The new coordinate system satisfy above condition, thus forms a new vector space.

* There must be (indeed, since both basis matrices are nonsingular) bijective transformation between any two different coordinate systems. There is no preference (ranking?) among the coordinate systems. \\[\textrm{vector = [basis][coordinate]}\\]

* During the course of linear algebra, we are mainly interested in the properties and concepts (invertibility, rank, eigenvalues, ...) (links) which does not rely on these coordinate systems.

* __There is no concepts of "angle", "rotation", "length", etc. in a vector space.__ Such space is defined with `inner product` operation between vectors, and is called an Euclidean space (link).

