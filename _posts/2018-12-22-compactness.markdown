---
layout: post
title:  "Compact Sets"
date:   2018-12-22 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis compact open_cover
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

`proof:`
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


### Basic Theorems

> __Theorem__ 2.34 (PMA):  
Compact subsets of metric spaces are closed.

<img src="{{ site.url }}/images/analysis/2018-12-22/img2.png" class="center" style="width:400px"/>

`proof:`
Let \\(K\\) be a compact subset of a metric space \\(X\\). We shall prove that the complement of \\(K\\) is an open subset of \\(K\\).  
Suppose \\(p\in X,\\ p\notin K,\\ q\in K\\), and let \\(V\_q\\) and \\(W\_q\\) be neighborhoods of \\(p\\) and \\(q\\), respectively, of radii less than \\(\frac\{1\}\{2\}d(p,q)\\) [see Definition 2.18(a)?]. Since \\(K\\) is compact, there are finitely many points \\(q\_1,...,q\_n\in K\\) s.t.
\\[K\subset\left(W\_\{q\_1\}\cup ... \cup W\_\{q\_n\}\right)=W\\]
If \\(V:=V\_\{q\_1\}\cap\cdots\cap V\_\{q\_n\}\\), then \\(V\neq\emptyset\\) since \\(n\\) is finite, and is a neighborhood of \\(p\\) that does not intersect with \\(W\\). Hence \\(V\subset K^C\\) so that \\(p\\) is an interior point of \\(K^C\\). The theorem follows.


> __Theorem__ 2.35 (PMA):  
Closed subsets of compact sets are compact.

`proof:`
Suppose \\(F\subset K\subset X\\), \\(F\\) is closed, and \\(K\\) is compact. Let \\(\\{V\_\alpha\\}\\) be an open cover of \\(F\\). By adjoining \\(F^C\\) (which is open in \\(X\\)) to \\(\\{V\_\alpha\\}\\), we obtain an open cover \\(\Omega\\) of \\(K\\). Since \\(K\\) is compact, there is a finite subcollection \\(\Phi\\) of \\(\Omega\\) which covers \\(K\\), and hence \\(F\\). If \\(F^C\\) is still a member of \\(\Phi\\), se may remove it and still retain an open cover of \\(F\\). We have thus shown that a finite subcollection of \\(\\{V\_\alpha\\}\\) covers \\(F\\).



> __Corollary__: If \\(F\\) is closed and \\(K\\) is compact, then \\(F\cap K\\) is compact.

1. compact set \\(K\\) is closed, by Thm 2.34
2. Intersection of closed sets are closed
3. By 2.35, the intersection is also compact.


### Heine-Borel Theorem

> __Theorem__ 2.36 (PMA) :  
If \\(\\{K\_\{\alpha\}\\}\\) is a collection of compact subsets of a metrix space \\(X\\) such that the intersection of every finite subcollection of \\(\\{K\_\{\alpha\}\\}\\) is nonempty, then \\(\mathop\{\bigcap\}\_\{\alpha\}K\_\alpha\\) is nonempty.

`proof`: Suppose that \\(\mathop\{\bigcap\}\_\{\alpha\}K\_\alpha\\) is empty. Fix a \\(\alpha'\\) and assume \\(\nexists\\ p\in K\_\{\alpha'\} \\ : \\ p\in K\_\alpha\\ \forall\\ \alpha \neq \alpha'\\) (assumption says the intersection is nonempty only for finite collections).  
Then \\(\bigcup\_\{\alpha\}K\_\{\alpha\}^C\\) is an open cover of \\(K\_\{\alpha'\}\\), and there exists a finite collections \\(K\_\{\alpha\_1\}^C,...,K\_\{\alpha\_n\}^C\\) that their union covers \\(K\_\{\alpha'\}\\). Now we have a contradiction, since by the statement so far,
\\[K\_\{\alpha'\}\cap\left( K\_\{\alpha\_1\}^C\cup \cdots \cup K\_\{\alpha\_n\}^C \right)^C=\emptyset\\]
\\[\rightarrow K\_\{\alpha'\}\cap\left( K\_\{\alpha\_1\}\cap \cdots \cap K\_\{\alpha\_n\} \right)=\emptyset\\]QED.


> __Corollary__: If \\(\\{K\_n\\}\\) is a sequence of nonempty compact sets such that \\(K\_n\supset K\_\{n+1\}\\), then \\[\mathop\{\bigcap\}\_\alpha K\_\alpha\neq\emptyset\\]

\\(\\ \\)

> __Theorem__ 2.37 (PMA) :  
If \\(E\\) is an subset (with infinite cardinality) of a compact set \\(K\\), then \\(E\\) has a limit point on \\(K\\).

`proof:`:
1. If no point of \\(K\\) were __a limit point of \\(E\\)__, then for all \\(q\in K\\) exists a neighborhood \\(V\_\{\epsilon\_q\}\\) which contains __at most one point of \\(E\\)__ (namely, \\(q\\) if \\(q\\in E\\)).
2. Now it is clear that no finite subcollection of \\(\mathop\{\bigcup\}\_q V\_\{\epsilon\_q\}\\) can cover \\(E\\), and the sma e is true of \\(K\\) since \\(E\subset K\\). This contradicts the compactness of \\(K\\).

> __Theorem__ 2.38 (PMA) :  
If \\(\\{I\_n\\}\\) is a sequence of intervals in \\(R^1\\), such that \\(I\_n\supset I\_\{n+1\}\\ (n=1,2,...)\\), then \\(\mathop\{\bigcap\}\_\{n\}^\infty I\_n\\) is not empty.

`proof`:
1. Let \\(E\\) be the set of all \\(x\_n\\). Since \\(x\_n\\)s are bounded by any \\(b\_k\\), by the least upper bound property of \\(R\\), the supremum exists, so denote \\(x=\sup E\\). We immediately see that \\(x\_n \leq C\\)
2.  Now we want to show that \\(x\leq b\_n\\). Suppose not. Then for some \\(n\\), \\(x > b\_n\\) and let \\(\epsilon'=x-b\_n\\).  
Since \\(x=\sup E,\\ \forall\\ \epsilon>0\\ \exists\\ n\in\mathbb\{N\}\\ :\\ x-\epsilon < x\_n \leq x\\). By letting \\(\epsilon=\epsilon'\\), we see that
\\[x-\epsilon' = b\_n < a\_n < x\\] which is a contradiction.
3. Combining all 2, we see that \\(a\_n\leq x \leq b_n \forall n\in \mathbb\{N\}\\), so that \\[x\in \mathop\{\cap\}\_\{i=1\}^\infty I\_n\neq\emptyset\\]. 

> __Theorem__ 2.39 (PMA) :  
Let \\(K\\) be a positive integer. If \\(\\{I\_n\\}\\) is a sequence of \\(k\\)-cells such that \\(I\_n\supset I\_\{n+1\}\\ (n=1,2,3,...)\\), then \\(\mathop\{\cap\}\_\{i=1\}^\infty I\_n\neq\emptyset\\).

__proof__: Apply 2.38 dimension-wise.

> __Theorem__ 2.40 (PMA) :  
Every \\(k\\)-cell in \\(\Re\\) is compact.

Without this theorem, we cannot say rigorously that every closed interval \\([a\_n, b\_n]\\) is compact (every open cover contains finite subcover).

`proof`:
1. Let \\(I\\) be a \\(k\\)-cell, consisting of all points \\(\textbf\{x\}=(x\_1,...,x\_k)\\ :\\ a\_j\leq x\_k \leq b\_j\\ (1\leq j\leq k)\\). Put
\\[\delta := \left\\{  \sum\_\{j=1\}^k (b\_j-a\_j)^2\right\\}^\{\frac\{1\}\{2\}\}.\\]
Then we easily see that \\(\forall \textbf\{p, q\}\in I,\\ \|\|\textbf\{p\}-\textbf\{q\}\|\| \leq \delta\\).  
2. Suppose, to get a contradiction, that \\(I\\) is not compact. Then there is an open cover \\(\\{G\_\alpha\\}\\) which contains no finite subcover. Put \\(c\_j=(a\_j+b\_j)/2\\). Now using \\(2\times k\\) intervals, we can construct \\(2^k\\) subintervals, and atleast one of such subintervals cannot be covered by finite open cover (If not, take union and it covers \\(I\\)). Call the interval \\(I\_n\\), anc continue the process for \\(n=1,2,...\\), we obtain a sequence \\(\\{I\_n\\}\\) with following properties.  
    1. \\(I\supset I\_1 \supset I\_2 ...\\)
    2. \\(\forall\\ n,\\ I\_n\\) cannot be covered by the open subcover.
    3. If \\( \textbf\{p, q\}\in I\_n\\), then \\(\|\|\textbf\{p\}-\textbf\{q\}\|\| \leq 2^\{-n\}\delta \\).
3. By (a) and `Theorem 2.39`, \\(\exists x^* \\) which lies in all \\(I\_n\\). Since the \\(\\{G\_\alpha\\}\\) covers \\(I\\), for some \\(\alpha\\ x^* \in G\_\alpha\\). Since \\(G\_\alpha\\) is open in \\(\Re\\), there exists \\(\lambda\\ :\\ \|\|x^* - q\|\| \leq \lambda \rightarrow q\in G\_\alpha\\). Now for some \\(n'\\ :\\ 2^\{-n'\}\delta \leq \lambda\\)\\), (c) implies that \\(I\_n\subset G\_\alpha\\), which contradicts (b). 



The equivalence of 1, 2 of following theorem is known as __Heine-Borel Theorem__.
> __Theorem__ 2.41 (PMA) :  
If a set \\(E\in R^k\\) has one of the following three properties, then it has the other two:
1. \\(E\\) is closed and bounded
2. \\(E\\) is compact
3. Every infinite subset of \\(E\\) has a limit point in \\(E\\)

`proof`:
* If 1. holds, then \\(E\\) is a subset of some \\(k\\)-cell, and 2. follows from the `Theorem 2.40` and `Theorem 2.35`. 
* Theorem 2.37 shows that 2. implies 3.
* It remains to show tha 3. implies 1.  
Proof by contraposition:  
-1. Suppose \\(E\\) is not bounded. Then \\(E\\) contains points \\(x\_n\\) with
\\[\|x\_n\| > n\\ (n=1,2,3,...)\\]
The set \\(S:=\\{x\_n \| n=1,2,3,...\\}\\) clearly has no limit point in \\(R^k\\), thus not in \\(E\\). This show that 3. implies that \\(E\\) is bounded.
-2. If \(E\\) is not closed, then there is a point \\(x\_0\in R^k\\) which is a limit point of \\(E\\) but not in \\(E\\). Define \\(S:=\\{x\_n\\ \| \\ \|x\_0-x\_n\|<1/n\\}\\). Then \\(S\\) is infinite (otherwise \\(x\_0\\) cannot be a limit point of \\(E\\)), \\(S\\) has \\(x\_0\\) as a limit point, and \\(S\\) has no other limit point in \\(R^K\\). To show that \\(S\\) has no other limit point in \\(R^k\\), suppose \\(y\in R^k\\) such that \\(x\_0\neq y\\). Then
\\[\|x\_n-y\| \geq \|x\_0 - y\| - \|x\_n - x\_0\| \\]
\\[\|x\_0 - y\| - \frac\{1\}\{2\} \geq \frac\{1\}\{2\}\|x\_0-y\|\\]  

(1st - traingular inequality, 2nd - above, 3rd - \\(\frac\{1\}\{2\} \leq \frac\{1\}\{2\}\|x\_0-y\| \\), which holds for large \\(n\\)) for all but finitely many \\(n\\); this whos that \\(y\\) is not a limit point of \\(S\\) (Theorem 2.20). Since there exists an infinite subset of \\(E\\) suth chat has no limit point in \\(E\\), \\(E\\) is closed.  


We should remark, at this point, that 2. and 3. are equivalent in any metric spaces (Exercise 26) but that 1. does not, int general, implyt 2. and 3. Examples are furnished by Exercise 16 adn by the space \\(\mathcal\{l\}^2\\), which is discussed in Chap 11.

### Weierstrass Theorem
> __Theorem__ 2.42 (PMA) : Weierstrass Theorem  
Every bounded infinite subset of \\(R^k\\) has a limit point in \\(R^k\\).

`proof`:  
Being bounded, the set \\(E\\) is a subset of some \\(k\\)-cell \\(\in R^k\\). By `Theorem 2.40`, the cell is compact, so \\(E\\) has a limit point in the cell, by `Theoren 2.37`.


References
* (DA): 맛있는 해석학 4판, 김백진
* (PMA): Walter Rudin, Principle of Mathmatical Analysis

Next:  

