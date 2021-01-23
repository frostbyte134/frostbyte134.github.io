---
layout: post
title:  "Open / Closed Sets in Metric Spaces"
date:   2021-01-23 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis metric_space open_set closed_set limit_point neightborhood interior cell closure
---

* Written in 2018-10-04
* Revision in 2020-01-23. 해석학 복습 고고. 이번에는 역함수 정리 꼭 가자

Note that, subset (not subseteq) is used in the def. of interior.

With the concept of `distance` defined in a <a href="{{site.url}}/analysis/2018/10/03/metric-space.html" target="_blank">__metric space__</a>, we can talk about the limit, and openness/closedness of a set.


### Definitions

* `segment` \\(a,b\\) in \\(\mathbb\{R\}\\): \\(\\{x\in\mathbb\{R\} \\ \| \\ a < x < b\\}\\)
* `k-cell` : segments in \\(\mathbb\{R\}^k\\)

Let \\(X\\) be a metric space. All points and set mentioned below are understood to be the elements / subsets of \\(X\\)
* `neightborhood` of \\(p\\) with radius \\(r:= N\_r(p)\\)  
   is a set \\(\\{x\in X \\ \| \\ d(x, p) < r\\}\\), and is denoted as a `open circle` in Euclidean space.
* `limit point` \\(p\\) of a set \\(E\\):  
  - Every neightborhood of \\(p\\) constains a point \\(q\neq p\\) such that \\(q\in E\\)  
  - __negation__ \\(\rightarrow \exists\\) a neighborhood \\(N\\) of \\(p\\) such that \\(N \bigcap E = \emptyset\\)  
* `isolated point` \\(p\\) of a set \\(E\\): \\(p\in E\\) but \\(p\\) is not an limit point
* \\(E\\) is `closed` if every limit point of \\(E\\) is a point of \\(E\\)
* \\(p\in E\\) is an `interior point` if \\(\exists\\ N\_r(p) \subset E \text\{ for some \} \\ r>0\\)
* \\(E\\) is `open` if every point of \\(E\\) is an interior point
* \\(E\\) is perfect, if \\(E\\) is closed and if every point of \\(E\\) is a limit point of \\(E\\) (no isolated points)
  * compare this def with the def of closed sets
* \\(E\\) is bounded if \\(\exists\\ q\in X,\\ M\in\mathbb\{R\} \\ : \\ d(p,q)<M,\quad \forall \\ p\in E\\) 
* \\(E\\) is dense in \\(E\\) if every point of \\(X\\) is a limit point of \\(E\\), or a point of \\(E\\)\\[\mathbb\{Q\} \text\{ is dense in \}\mathbb\{R\}\\]

### Examples
Let us consider the following subsets or \\(\mathbb\{R^2\}=\mathbb\{C\}\\).
* \\(\\{x\\},\\ x\in \Re\\) : closed (vacuously, or consider complement)
* \\(\emptyset\\) : open and closed, with empty interior/exterior
* \\(\\{z\in\mathbb\{C\}\quad\|\quad \|z\|<1\\}\\)  
\\(\rightarrow\\) not closed, open, not perfect, bounded
* \\(\\{z\in\mathbb\{C\}\quad\|\quad \|z\|\leq 1\\}\\)  
\\(\rightarrow\\) closed, not open, perfect, bounded
* A nonempty finite set  
\\(\rightarrow\\) closed (vacuously), not open, not perfect, bounded
* The set of all integers \\(\mathbb{Z}\\)  
\\(\rightarrow\\) closed(complement is open, or vacuously), not open, not perfect (\\(\mathbb\{Z\}\\) cannot have a limit point, so is not closed in \\(\mathbb\{R\}\\), bounded
* The set of all rational numbers \\(\mathbb{Q}\\)  
  \\(\rightarrow\\) Not open, nor closed.
* \\(\mathbb\{R\} \text{  and  }\mathbb\{R^2\}=\mathbb\{C\}\\)  
\\(\rightarrow\\) closed, open, perfect, not bounded
* The segment \\((a,b),\\ a,b\in\mathbb\{R\}\\)  
\\(\rightarrow\\) not closed, open (relatvie to \\(\mathbb\{R\}\\)) or not open (in \\(\mathbb\{C\}\\)), not perfect, bounded

### Theorems

Note that many of the theorems does not assume the Euclidean space, but works in general metric space with distance \\(d\\).

> __Theorem__(Rudin 2.19): __Every neightborhood is an open set__

__proof__: Consider a neightborhood \\(N\_r(p)\\) of \\(p\in\mathbb\{R\}\\), and let \\(q\\) be an arbitrary point of \\(N\_r(p)\\). We have to show that \\(N\_h(q)\subset N\_h(q)\\) for some \\(h\\).  Let \\(h=r-d(p,q)\\). Then for an arbitrary point \\(s\in N\_h(q)\\),
\\[d(p,s)\leq d(p,q)+d(q,s) < r-h + h =r\\]

> __Theorem__(Rudin 2.20): If \\(p\\) is an limit point of a set \\(E\\), then __every neightborhood__ of \\(p\\) __contains infinitely many points__ of \\(E\\).

__proof__: Suppose there exists \\(r>0\\) such that makes \\(N\_r(p)\bigcap E=\\{q_1,...,q_n,p\\}\\). Define \\[r'=\min\_i d(p,q_i).\\]The minimum of finite positive numbers are positive, so that \\(r'>0\\). The neightborhood \\(N\_\{r'\}(p)\\) contains no points of \\(E\\) except for \\(p\\), namely \\(N\_\{r'\}(p)\bigcap E=\\{p\\}\\), so that \\(p\\) is not a limit point of \\(E\\) and contradiction rises.  
__Corollary__: A finite point set has no limit points (and is closed vacuously).

__Theorem 2.22__ is about the De Morgan's for arbitrary (including uncountable) index set

> __Theorem__(Rudin 2.23): A set \\(E\\) is open iif its complement \\(E^C\\) is closed.

__proof__:  
1. \\(\rightarrow\\)  
Let \\(x\\) be a limit point of \\(E^C\\). Then every neighborhood of \\(x\\) has intersection with \\(E^C\\), so that by the definition of open set \\(x\notin E\\), then \\(x\in E\\). \\(E\\) is closed.
2. \\(\leftarrow\\)  
Let \\(x\notin E^C\\), so that \\(x\in E\\) by the def. of complement. Then since \\(E^C\\) is closed, \\(x\\) is not an limit point of \\(E^C\\), so some neighborhood of \\(x,\\ N_\epsilon(x)\\) has no intersection with \\(E^C\\), which implies that \\(N_\epsilon(x)\subset\\), and sicne this holds for arbitrary point of \\(E\\), \\(E\\) is open.

### Intersection / Union of open/closed sets

> __Theorem__(Rudin 2.24)  
(a) For any collection \\(\\{G\_\alpha\\}\\) of open sets, \\(\bigcup\_\alpha G\_\alpha\\) is open.  
(b) For any collection \\(\\{F\_\alpha\\}\\) of closed sets, \\(\bigcap\_\alpha F\_\alpha\\) is closed.  

__proof__: For (a), Let \\(G:=\bigcup\_\alpha G\_\alpha\\). If \\(x\in G\_\alpha\\), then for some \\(\epsilon>0,\\ N\_\epsilon(x)\subset G_\alpha\\), which imples that \\(N\_\epsilon(x)\subset G\\). Thus \\(G\\) is also open.  
Using De Morgan's Law on (a) gives (b).  

> __Theorem__ 2.24 Cont'ed:  
(c) For any finite collection \\(\\{G\_\alpha\\}\\) of open sets, \\(\bigcap\_\{i=1\}^N G\_\alpha\\) is open.  
(b) For any finite collection \\(\\{F\_\alpha\\}\\) of closed sets, \\(\bigcup\_\{i=1\}^N F\_\alpha\\) is closed.  

__proof__: In (a), taking minimum of radii \\(\epsilon\\) (which makes \\(N_\epsilon(x)\in G\_\alpha\\), gives a neighborhood of \\(x\\) in all of the finite sets, thus the intersection. (Note that when such sets are infinite, the infimum \\(\epsilon\\) could converge to 0).


__Side note:__ For an open set \\(G\\) and closed set \\(F\\),  
- \\(G\F = G\bigcap F^C \\) : open
- \\(F\G\\) : closed, vice versa.

### Supremum is in the closer of a set

__Definition__: `closure` of \\(E,\\)\\[\bar\{E\}:=E\bigcup \\{\text\{all limit points of \}E\\}\\] 

> __Theorem__(Rudin 2.28): Supremum is in the closer of the set. (__Supremum is a limit point, if it is not in the set__)  
Let \\(E\\) be a nonempty set of __real numbers__ which is bounded above. Let \\(y=\sup E\\). Then \\(y\in\bar\{E\}\\). Hence \\(y\in E\\) is \\(E\\) is closed.

__proof__:  
1. If \\(y\in E\\), then the theorem trivially holds.
2. If not, then by the definition of the supremum, for every \\(\epsilon>0\\) there must be \\(x\in E\\) such that 
\\[y-\epsilon < x \leq y\\]  for otherwise \\(y-\epsilon\\) can be a new supremum. Thus \\(y\\) is a limit point of \\(E\\), and \\(y\in \bar\{E\}\\).


### Open Relative To

__Remark__(Rudin 2.29): Suppose that \\(E\subset Y \subset X\\), where \\(X\\) is a metric space.  
To say that \\(E\\) is an open subset of \\(X\\), for every \\(p\in E\\) there is associated (pointwise property!) \\(\epsilon>0\\) such that \\(d(p,q)<\epsilon\\) imples that \\(q\in E\\).  
But we know that (Rudin 2.16) a subset of a metric space is also a metric space, so our def may equally well be made within \\(Y\\).  
To be explicit, let us say that \\(E\\) is `open relative to` \\(Y\\), when \\(\forall\\ p\in E\\) if \\(q\in Y\\) then there exists associated \\(\epsilon>0\\ : d(p,q)<\epsilon\\).  
A set could be open relative to \\(Y\\) (subset), while not open in \\(X\\) (universe). Think about a circle in 3D space. It is never open in 3D, but is open in 2D plane which is a proper subset of 3D space.

Following theorem show that there is certain relation between these concepts.

> __Theorem__(Rudin 2.30): Suppose \\(Y\subset X\\), and \\(Y, X\\) are metric spaces.  
A subset \\(E\\) of \\(Y\\) is open relative to \\(Y\\) iif \\(E=Y\bigcap G\\) for some open subset \\(G\\) of \\(X\\).

1. \\(\rightarrow\\):  
Since \\(E\\) is open relative to \\(Y\\), for each point \\(p\in E\subset Y\\) there must be \\(\epsilon\_p\\) such that \\(d(p,q\)<\epsilon\_p \quad\rightarrow\quad q\in E\\). Now consider \\(X\\) as an universe, and define \\(G:=\bigcup\_\{p\}N\_\{\epsilon_p\}(p)\\) where the neighbors are defined in \\(X\\). Then \\(G\\) is open by Theorem 2.19 and 2.24, and we have \\(E\subset G\cap Y\\). Conversely, if \\(p\in G\\) and \\(p\in Y \\), then \\(d(p,q\)<\epsilon\_p, p\in Y\\) holds so that \\(p\in E\\). Thus we have \\(E=G\cap Y\\).  
2. \\(\leftarrow\\):  
let \\(G\\) is open in \\(X\\) and let \\(E=G\bigcap Y\\). Then every \\(p\in E\\) has a neighbor (in \\(X\\)) \\(N\_\epsilon(p)\subset G\\). Now it holds that
\\[N\_\{\epsilon_p\}(p)\cap Y \subset G\cap Y = E\\] so that \\(E\\) is open relative to \\(Y\\).





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