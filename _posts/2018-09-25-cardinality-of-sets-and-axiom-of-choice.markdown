---
layout: post
title:  "Cardinality of Sets and the Axiom of Choice"
date:   2018-09-26 5:00:05 +0800
categories: analysis
use_math: true
tags: analysis cardinality uncountable infinite_set axiom_of_choice cantor_theorem need_revise
---

Cantor-Bernstein theorem proof needed  
Proof of \\(\mathbb\{R\}\approx \mathcal\{P\}(\mathbb\{N\})\\)

### Finite/Intinite sets

For two sets \\(A, B\\), if an <a href="{{site.url}}//analysis/2018/09/25/function.html#oto_corr" target="_blank">one-to-one correspondence</a> \\(f:A\mapsto B\\) exists then we say \\(A\\) and \\(B\\) are `equinumerous`, denoted by \\(A\approx B\\). By the property of one-to-one correspondence, __equinumerous relation is a equivalent relation__ of arbitrary family of sets.

If there exists \\(n\in \mathbb\{Z\}\\) such that a set \\(E\\) is equinumerous to a set \\(\\{0,1,...,n\\}\\), or \\(E=\emptyset\\), we say that \\(E\\) is `finite`. Formally speaking, let \\(w:=\\{k\in \mathbb\{Z\} \\ \| \\ k\geq 0\\},\\  w\_k:=\\{k\in \mathbb\{Z\} \\ \| \\ 0\leq k \leq n\\}\\).  
Then \\(E\\) is a countable set when
\\[\exists n \in w \\ : \\ E\approx w\_n.\\]

* A set which is not finite is `infinite`.
* By enumerating its elements, we see that some subset of an arbitrary infinite set is equinumerious with the \\(\mathbb\{N\}\\).
* A set equinumerious with \\(\mathbb\{N\}\\) is called a `enumerable set`. __Enumerable set is the smallest infinite set.__ We call finite sets and enumerable sets as the `countable set.
\\[\text\{finite \}\lor\text\{ enumerable = countable\}\\]

Following are some properties of the finite/infinite sets.
* \\(E\\) is infinit i.i.f \\(E\\) has enumerable subset
* \\(E\\) is infinit, \\(F\\) is finite \\(\quad\rightarrow\quad\\) \\(E\approx E\backslash F\\)
* \\(E\\) is infinit, \\(E\subseteq F \quad\rightarrow\quad\\) \\(F\\) is infinite
* \\(A,B\\) is countable \\(A\times B\\) is countable
* Let \\(2^A\\) be a set of all discrete functions, where \\(A\\) is domain (all values must be considered), \\(\\{0,1\\}\\) is codomain. Then\\[2^A\approx \mathcal\{P\}(A)\\] (ex - For \\(A=\\{a,b\\},\\ \\{a\\}=\\{(a,1),(b,0)\\}\\)
* If all \\(A_i\\)s of \\(\\{A_i \\ \| \\ i\in \mathbb\{N\}\\}\\) are finite, then their union is also finite.

### Cantor-Bernstein Theorem
If a one-to-one function \\(f:A\mapsto B\\) exists, we say that "\\(B\\) is greater or equal to \\(A\\)", and denote
\\[A\preceq B\\]. Furthermore, we denote \\(A\preceq B\\) and \\(A\not\approx B\\) as \\(A\prec B\\).

We see that \\(A\preceq B \\ \land\\ B\preceq A \quad\rightarrow\quad A\approx B\\) (Cantor-Bernstein Theorem). By this we see that \\(\preceq\\) is an order-relation of arbitrary sets.

Proof:


### Cardinality of Numbers
1. \\(\mathbb\{N\}, \mathbb\{Z\}\\) are countable (enumerable)
2. \\(\mathbb\{Q\}\\) is countable (\\(\frac\{a\}\{b\}\mapsto a+b\\), and sort)
3. \\(\mathbb\{R\}\\) is uncountable (proof is too famous and long to write here)
4. \\((0,1)\approx \mathbb\{R\}^2\\)  
	> Proof - Map \\((x\_1.x\_2x\_3...,y\_1.y\_2y\_3...)\in \mathbb\{R\}^2\quad\\) to \\(\quad 0.x\_1y\_1x\_2y\_2...\in (0,1)\\).  
	We see that \\(R^2\subset (0,1)\\), and the converse is trivial.
5. By 4, we see that \\(\mathbb\{R\}\approx \mathbb\{C\}\\).

In conclusion,
\\[\mathbb\{N\}\approx \mathbb\{Z\}\approx\mathbb\{Q\}\prec\mathbb\{R\}\approx\mathbb\{C\}\\]
Two questions may rise
1. Is there any set \\(E\\) such that, \\(\mathbb\{R\}\prec E\\)?  
	\\(\rightarrow\\) `Cantor's Theorem`: For an arbitrary set \\(E,\\ E\prec\mathbb\{P\}(E)\\) holds  
	> Proof: If not, then construct a 1-to-1 __correspondence__ \\(\phi:E\mapsto \mathbb\{P\}(E)\\).  
	By defining \\(B:=\\{x\in E \\ \| \\ x\notin \phi(x)\\}\\), it holds that \\(B\subseteq E\\);  
	Therefore there exists \\(y\in E\\) such that \\(\phi(y)=B\\). There cound be 2 cases.  
	1) \\(y\in\phi(y)=B\\)  
		Then \\(y\notin \phi(y)=B\\) by the definition of \\(B\\), a contradiction.  
	2) \\(y\notin\phi(y)=B\\)   
		Then again \\(y\in\phi(y)=B\\) must be hold by the definition of \\(B\\), a contradiction.
2. Is there any set \\(E\\) such that \\(\mathbb\{N\}\prec E \prec \mathbb\{R\}\\)?  
	\\(\rightarrow\\) `Axiom of choice`  
	No contradiction rises whether we accept or deny it.
	
Note that \\(\mathbb\{R\}\approx \mathcal\{P\}(\mathbb\{N\})\\), by the property of the continuous function. (How?)

Next:  

