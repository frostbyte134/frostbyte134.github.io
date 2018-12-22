---
layout: post
title:  "Compact Sets"
date:   2018-12-19 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis compact
---


### Open conver of a set
By an `open cover` of a set \\(E\\) in a metric space \\(X\\), we mean a collection \\(\\{G\_\{\alpha\}\\}\\) of subsets of \\(X\\) such that
\\[E\subset \bigcup\_\{\alpha\}G\_\{\alpha\}\\]

### Compactness
By an open cover of a set \\(E\\) in a metric space \\(X\\) is `compact` when __every__ open cover \\(K\\) of \\(E\\) has a __finite__ subcover containing \\(K\\).


### Compactness is independent of the universe
> __Theorem__ 2.33 (PMA):  
Suppose \\(K\subset Y\subset X\\). Then \\(K\\) is compact wrt \\(X\\) i.i.f \\(K\\) is compact wrt \\(Y\\).

<img src="{{ site.url }}/images/analysis/2018-12-22/img1.png" class="center" style="width:400px"/>

__proof__  
\\(\rightarrow\\): Consider an open cover of \\(K\\) in \\(Y\\), \\(\bigcup\_\{\alpha\}G\_\{\alpha\}\\). We have show that this open cover has a finite subcover, using the compactness of \\(K\\) in \\(X\\). 

Since \\(G\_\{\alpha\}\\) is open in \\(Y\subset X\\), \\(\exists\\) a set \\(F\_\{\alpha\}\\) open in \\(X\\), such that \\(G\_\alpha=Y\bigcap K\_\alpha\\). 

Since
\\[K\subset Y \quad\land\quad K\subset \bigcup\_\{\alpha\}G\_\{\alpha\},\\]
\\(\bigcup\_\{\alpha\}F\_\{\alpha\}\\) is an open cover of \\(K\\), and since \\(K\\) is compact in \\(X\\) it contains a finite subcover, denoted by the subindex \\(\alpha\_k\\). 

Now considering its intersection with \\(Y\\),
\\[\left(\bigcup\_\{\alpha_k\}K\_\{\alpha_k\}\right) \cap Y\\]
it contains \\(K\\) since the both terms contains \\(K\\), and finally
\\[=\bigcup\_\{\alpha\}K\_\{\alpha_k\}\cap Y=\bigcup\_\{\alpha\}G\_\{\alpha\_k\}\\]
Thus the finite subcover of \\(G\_\alpha\\) exists for arbitrary open cover \\(G\_\alpha\\) in \\(Y\\).

\\(\leftarrow\\) : Consider \\(\\{G\_\alpha\\}\\), an open subcover of \\(K\\) in \\(X\\). Taking intersection with \\(Y\\) as \\(\bigcup\_\alpha G\_\alpha \cap Y\\) it still contains \\(K\\), and since \\(K\\) is compact in \\(Y\\) it contains a finite subcover \\(\\{G\_\{\alpha\_k\}\\}\\). Now we have
\\[K\subset \bigcup\_\{\alpha\_k\} G\_\{\alpha\_k\} \cap Y \subset \bigcup\_\{\alpha\_k\} G\_\{\alpha\_k\}\\]
Thus we obtained finite subcover for an arbitary open cover in \\(X\\). __Q.E.D.__

> (PMA) By virtue of this theorem we are able, in many situations, to regard compact sets as metric spaces in their own right, without paying any attention to any embedding space. In particular, although it makes little sense to talk of open spaces, or of closed spaces (every metric space \\(X\\) is an open subset of itself, and is a closed subset of itself), it does make sense to talk of compact metric spaces.


### Theorems

> __Theorem__ 2.34 (PMA):  
Compact subsets of metric spaces are closed.

<img src="{{ site.url }}/images/analysis/2018-12-22/img2.png" class="center" style="width:400px"/>

__proof__: Let \\(K\\) be a compact subset of a metric space \\(X\\). We shall prove that the complement of \\(K\\) is an open subset of \\(K\\). 

Suppose \\(p\in X,\\ p\notin K,\\ q\in K\\), and let \\(V\_q\\) and \\(W\_q\\) be neighborhoods of \\(p\\) and \\(q\\), respectively, of radii less than \\(\frac\{1\}\{2\}d(p,q)\\) [see Definition 2.18(a)?]. Since \\(K\\) is compact, there are finitely many points \\(q\_1,...,q\_n\in K\\) s.t.
\\[K\subset\left(W\_\{q\_1\}\cup ... \cup W\_\{q\_n\}\right)=W\\]
If \\(V:=V\_\{q\_1\}\cap\cdots\cap V\_\{q\_n\}\\), then \\(V\neq\emptyset\\) since \\(n\\) is finite, and is a neighborhood of \\(p\\) that does not intersect with \\(W\\). Hence \\(V\subset K^C\\) so that \\(p\\) is an interior point of \\(K^C\\). The theorem follows.

> __Theorem__ 2.35 (PMA):  
Closed subsets of compact sets are compact.

__proof__: Suppose \\(F\subset K\subset X\\), \\(F\\) is closed, and \\(K\\) is compact. Let \\(\\{V\_\alpha\\}\\) be an open cover of \\(F\\). By adjoining \\(F^C\\) (which is open in \\(X\\)) to \\(\\{V\_\alpha\\}\\), we obtain an open cover \\(\Omega\\) of \\(K\\). Since \\(K\\) is compact, there is a finite subcollection \\(\Phi\\) of \\(\Omega\\) which covers \\(K\\), and hence \\(F\\). If \\(F^C\\) is still a member of \\(\Phi\\), se may remove it and still retain an open cover of \\(F\\). We have thus shown that a finite subcollection of \\(\\{V\_\alpha\\}\\) covers \\(F\\).

> __Corollary__: If \\(F\\) is closed and \\(K\\) is compact, then \\(F\cap K\\) is compact.

1. compact set \\(K\\) is closed, by Thm 2.34
2. Intersection of closed sets are closed
3. By 2.35, the intersection is also compact.


* (DA): 맛있는 해석학 4판, 김백진
* (PMA): Walter Rudin, Principle of Mathmatical Analysis
Next:  

