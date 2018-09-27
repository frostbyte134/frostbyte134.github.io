---
layout: post
title:  "Open / Closed set (in R)"
date:   2018-09-27 6:00:05 +0800
categories: analysis
use_math: true
tags: analysis real_number open_set close_set
---


### Open / Closet Set in R

Definition: Inner point, open set  

Let \\(G\subseteq \mathbb\{R\}\\) and \\(x\in G\\). If \\(\exists\\) open interval \\((a, b)\\) such that \\(x\in(a,b)\subseteq G\\),  
then we call \\(x\\) as the `inner point` of \\(G\\). Set of all inner point of \\(G\\) is an `interior` of \\(G\\).
  
When every element of \\(G\\) is an inner point, then we call \\(G\\) is an `open set`.

`Closed set`: a set is closed, if its complement is an open set.

### Boundary point, exterior

Define \\(B_r(x):=\\{y\in \mathbb\{R\} \\ \| \\ \|x-y\|<r\\}\\),  
\\(\quad\bar\{B\}_r(x):=\\{y\in \mathbb\{R\} \\ \| \\ \|x-y\|\leq r\\}\\).

Let \\(E\subseteq \mathbb\{R\},\\ x\in \mathbb\{R\}\\).
1. If \\(\forall \epsilon>0, B_\epsilon(x)\bigcap E\neq \emptyset \land B_\epsilon(x)\bigcap E^C\neq \emptyset\\),  
then we call \\(x\\) as a `boundary point` of \\(E\\). Set of all boundary points of \\(E\\) is called a `boundary`.
2. If \\(x\\) is neither an inner point nor a boundary point, we call \\(x\\) a `exterior` point.

Few notable things about the open/closed set in \\(\mathbb\{R\}\\) are
* for \\(x\in\mathbb\{R\},\\ \\{x\\}\\) is a closed set, with boundary \\(\\{x\\}\\) and interior \\(\emptyset\\).
* \\(\emptyset\\) is either closed or open, with empty boundary and interior.
* \\(\mathbb\{R\}\\) is either open or closed (take complement of \\(\emptyset\\)?). The interior of \\(\mathbb\{R\}\\) is itself, with empty boundary.
* \\((0,1]\\) is neither open nor closed, with interior \\((0,1)\\) and boundary \\(\\{0,1\\}\\).
* In \\(mathbb\{R\}\\), \\(\mathbb\{Z\}\\) is closed. \\(\mathbb\{Q\}\\) is neither close nor open.

### Relatively open set

The concept of openness/closedness changes wrt the universe.
(After the rudin)