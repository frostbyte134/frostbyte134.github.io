---
layout: post
title:  "Continuity"
date:   2019-3-30 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis continuity limit function compact
---



### Limit of Functions
> __Definition__ 4.1 (PMA):  
Let \\(X\\) and \\(Y\\) be metric spaces; suppose \\(E\subset X\\), \\(f\\) maps \\(E\\) into \\(Y\\), and \\(p\\) is the limit point of \\(E\\). We write \\(f(x)\rightarrow q\\) as \\(x\rightarrow p\\), or
\\[\lim\_\{x\rightarrow p\}f(x)\\]
if there is a point \\(q\in Y\\) with the following property: For every \\(\epsilon>0\\) there exists a \\(\delta\\) such that
\\[d\_Y(f(x),q)< \epsilon\\]
for all points \\(x\in X\\) which
\\[0<d\_X(x,p)<\delta\\]

### Continuity
> __Definition__ 4.6 (PMA):  
Let \\(X\\) and \\(Y\\) be metric spaces; suppose \\(E\subset X\\), \\(f\\) maps \\(E\\) into \\(Y\\). Then \\(f\\) is said to be continuous at \\(p\\) if
\\[\forall\\ \epsilon > 0\\ \exists \\ \delta > 0 \\ : \\ d\_X(x,p)<\delta\quad\rightarrow\quad d\_Y(f(x),f(p)) < \epsilon\\]

`note`
* unlike 4.1, \\(f\\) should be defined at \\(p\\).
* If \\(E\\) is a set of isolated points, then \\(f\\) is always continuous
* If \\(p\\) is the limit point of \\(E\\), then \\(f\\) is continuous at \\(p\\) i.i.f \\[\lim\_\{x\rightarrow p\}f(x)=f(p)\\]
which is clear when we compare the definitions.

> __Theorem__ 4.8 (PMA):  
Let \\(X,Y\\) are metric spaces. Then a mapping \\(f:X\mapsto Y\\) is continuous on \\(X\\) _i.i.f_  \\(f^\{-1\}(V)\\) is open in \\(X\\) for every open set \\(V\subset Y\\), where \\(f^\{-1\}\\) is the inverse mapping of \\(f\\).

`proof`:  
\\(\rightarrow\\): list definitions and connect them  
1. \\(f\\) is continuous at \\(p\\)
\\[ \forall \epsilon > 0\\ \exists \delta > 0 \\ : \\ d\_X(p,x)<\delta \quad\rightarrow\quad d\_Y(f(p),f(x))<\epsilon \\]
2. From that, we have to show that if \\(V\subset Y\\) is open
\\[\exists \epsilon > 0 \\ : \\ d\_Y(f(p), y)<\epsilon \quad\rightarrow\quad y\in V\\]
then \\(f^\{-1\}(V)\\) is open in \\(X\\)
\\[\exists \delta > 0 \\ : \\ d\_X(p, x)<\epsilon,\\ x\in X \quad\rightarrow\quad x\in f^\{-1}(V)\\]
1. For all \\(f(p)\in V\\), there exists \\(\epsilon\\) of 2, and for such \\(\epsilon\\) there always \\(\exists \delta > 0\\) such that 1 holds.  
Therefore, for such \\(x\in N\_\delta(p)\\), 1 holds and this in turn imples that such \\(f(x)\in V\quad\rightarrow\quad x\in f^\{-1\}(V)\\).

\\(\leftarrow\\): somewhat trivial from the definitions  
In above proof, we have to show that 2 implies 1.  
For all \\(\epsilon\\) of 1 and \\(f(p)\in Y\\), \\[N\_\epsilon(f(p)):= \\{ y\in Y\\ \| \\ d\_Y(f(p),y)<\epsilon\\} \\] is an open set in \\(Y\\), 
therefore \\(f^\{-1\}(N\_\epsilon(f(p)))\\) is open in \\(X\\), and there exists \\(\delta\\)-neighbor of \\(p\\) in \\(X\\) which is a subset of \\(f^\{-1\}(N\_\epsilon(f(p))\\).  
To conclude, we see that for such  \\(\delta\\)-neighbor\\),
\\[x\in N\_\delta(p)\quad\rightarrow\quad x\in f^\{-1\}(N\_\epsilon(f(p))) \quad\rightarrow\quad f(x)\in N\_\epsilon(f(p))\\]
which is exactly 1.

> __Corollary__ (PMA):  
Let \\(X,Y\\) are metric spaces. Then a mapping \\(f:X\mapsto Y\\) is continuous on \\(X\\) _i.i.f_  \\(f^\{-1\}(V)\\) is closed in \\(X\\) for every closed set \\(V\subset Y\\).

### Vector-valued functions
In euclidean norm, by the ineuality 
\\[\|\|f\_j(x) - f_j(y)\|\| \leq \|\|\textbf\{f\}(x) - \textbf\{f\}(y)\|\| = \left\\{ \sum\_\{i=1\}^k \|\|f\_i(x) - f_i(y)\|\|^2 \right\\}^\{\frac\{1\}\{2\}\}\\]
we se that
1. \\(\textbf\{f\}\\) is continuous \\(\quad\rightarrow\quad\\) all \\(f\_i\\)s are continuous
2. all \\(f\_i\\)s are continuous \\(\quad\rightarrow\quad\\) \\(\textbf\{f\}\\) is continuous

holds.

### Examples
1. The functions \\(\phi\_i:=x\_i\\) is continuous, since the inequality
\\[\| \phi\_i(\textbf\{x\}) - \phi\_i(\textbf\{y\})\| \leq \|\textbf\{x\}-\textbf\{y\}\|\\]
2. Using the properties of limits (link?), we easily see that every polynomial \\(P\\)
\\[P:=\sum C\_\{n\_1\cdot n\_m\}x\\]

### Continuity and Compactness
> __Definition__ 4.13 (PMA):  
A mapping \\(f:\\) of a set \\(E\\) into \\(R^k\\) is said to be bounded if there is a real number \\(M\\) such that \\(\|f(x)\|\leq M\\ \forall\\ x\in E\\).

> __Theorem__ 4.14 (PMA):  
Suppose \\(f\\) is a continuous mapping of a compact metric space \\(X\\) into a metric space \\(Y\\). Then \\(f(X)\\) is compact.

`proof`:  
1. Let \\(\\{V\_\alpha\\}\\) be an open cover of \\(f(X)\\). We have to show that there exists a finite subcover which still covers \\(f(X)\\).
2. Since \\(V\_\alpha\subset Y\\) is open and \\(f\\) is continuous, \\(f^\{-1\}(V\_\alpha)\\) is also open set (`Thm 4.8`). We easily see that the inverse mapping of \\(\\{V\_\alpha\\}\\) covers \\(X\\), and
\\[X\subseteq f^\{-1\}\left(\mathop\{\bigcup\}\_\{\alpha\}V\_\alpha\right)\\]
\\[f^\{-1\}\left(\mathop\{\bigcup\}\_\{\alpha\}V\_\alpha\right) = \mathop\{\bigcup\}\_\{\alpha\}f^\{-1\}\left(V\_\alpha\right)\\]
Since \\(X\\) is compace, there exists an finite indices \\(\alpha\_1,...,\alpha\_n\\) such that
\\[X\subset f^\{-1\}(V\_\{\alpha\_1\}\bigcup\cdots\bigcup V\_\{\alpha\_n\})\\]
3. Since \\(f(f^\{-1\}(E))\subseteq E\\), we see that
\\[f(X) \subset f(f^\{-1\}(V\_\{\alpha\_1\}\bigcup\cdots\bigcup V\_\{\alpha\_n\})) \subseteq V\_\{\alpha\_1\}\bigcup\cdots\bigcup V\_\{\alpha\_n\})\\]
which shows that \\(f(X)\\) is compact.

In the case of \\(f:X\mapsto R\\) with \\(X\\) a compact metric set, \\(f(X)\\) is closed and bounded (`Thm 2.41`, Heine-Borel Theorem)

> __Theorem__ 4.16 (PMA):  
Suppose \\(f\\) is a continuous mapping of a compact metric space \\(X\\) into \\(R\\) (continuous real function), and
\\[M=\sup\_\{p\in X\}f(p),\quad m=\inf\_\{p\in X\}f(p)\tag\{14\}\\]
Then there exists point \\(p, q\in X\\) such that \\(f(p)=M\\) and \\(f(q)=m\\).

__We can always find solutions in the optimization problem, with a continuous real function on a compact set__

`proof`:  
By the assumption, \\(f(X)\\) is closed and bounded. By constructing a sequence \\(\\{x\_n\\}\\) converging to \\(M\\) (`Thm 2.28`), we see that the limit point of \\(\\{x\_n\\}\\) is in \\(X\\).

> __Theorem__ 4.17 (PMA):  
Suppose \\(f\\) is a continuous 1-1 mapping of a compact metric space \\(X\\) onto a metric space \\(Y\\
\\). Then the inverse mapping \\(f^\{-1\}\\) defined on \\(Y\\) by
\\[f^\{-1\}(f(x)) = x\\ (x\in X)\\]
is a continuous mapping of \\(Y\\) onto \\(X\\).

__In general, inverse mapping of a 1-1 continuous mapping is not continuous__  
`proof`:  
Analogous to the statement
\\[f \text\{ is continuous\}\quad\rightarrow\quad f^\{-1\} \text\{ is open in \} X\\ \forall \text\{ open \} V\subset Y\\]
we have to show that
\\[f^\{-1\} \text\{ is continuous\}\quad\rightarrow\quad f \text\{ is open in \} Y\\ \forall \text\{ open \} V\subset X\\]
1. \\(V\\) is open in \\(X\\) - \\(V^C\\) is closed, and is compact \\(V^C\subset X\\). Hence \\(f(V^C)\\) is compact, by the `Thm 4.14`
2. Since \\(f\\) is an 1-1 mapping, \\(f(V^C)=f(V)^C\\) is also closed, so that \\(f(V)\\) is open.

### Uniform Continuity and Compact Domain
> __Definition__ 4.18 (PMA):  
Let \\(f\\) be a mapping of a metric space \\(X\\) into a metric space \\(Y\\). We say that \\(f\\) is uniformly continuous on \\(X\\) if for every \\(\epsilon > 0 \\) there exists \\(\delta > 0\\) such that
\\[d\_Y(f(p), f(q)) < \epsilon\\]
for all \\(p,q\in X\\) for which \\(d\_X(p,q)<\delta\\).

* __Uniform continuity is a property of a function on a set__, whereas __continuity can be defined at a single point__.
* Uniformly continuous \\(\rightarrow\\) continuous. The converse holds in certain situations, which follows.

> __Theorem__ 4.19 (PMA):  
Let \\(f\\) be a continuous mapping of a compact metric space \\(X\\) into a metric space \\(Y\\). Then \\(f\\) is uniformly continuous on \\(X\\) 

`proof`:  
Let \\(\epsilon > 0\\) be given. Since \\(f\\) is continuous, we can associate to each point \\(p\in X\\) a positive number \\(\phi(p)\\) such that
\\[ q\in X,d\_X(p,q)<\phi(p) \quad\rightarrow\quad d\_Y(f(p),f(q))<\epsilon/2 \tag\{16\}\\]
And again for each point \\(p\in X\\), let
\\[J(p) = \\{q\in X\\ \| \\ d\_X(p,q) < \frac\{1\}\{2\}\phi(p)\\}\\]
Since \\(p\in J(p)\\), the collection of all sets \\(J(p)\\) over \\(p\in X\\) is an open cover of \\(X\\); and since \\(X\\) is compact, there exists a finite set of points \\(p\_1,...,p\_n\\) in \\(X\\) such that
\\[X\subset J(p\_1)\bigcup\cdots \bigcup J(p\_n)\\]
We put
\\[\delta:=\frac\{1\}\{2\}\min[\phi(p\_1),...,\phi(p\_n)]\\]
Then \\(\delta>0\\) (this is one point where the finiteness of the covering, inherent in the def of compactness is essential). Now let \\(p,q\in X\\) such that \\(d\_X(p,q) < \delta\\). By (18), there is an integer \\(m\\), \\(1\leq m\leq n\\) such tha \\(p\in J(p\_m)\\); hence
\\[d\_X(p\_m,p) < \frac\{1\}\{2\}\phi(p\_m)\\]
and we also have
\\[d\_X(p,q\_m) \leq d\_X(p,q) + d\_X(p,p\_m) \leq \delta + \frac\{1\}\{2\}d\_Y(f(q), f(p\_m)) < \epsilon\\]
which completes the proof.


References
* (DA): 맛있는 해석학 4판, 김백진
* (PMA): Walter Rudin, Principle of Mathmatical Analysis

Next:  

