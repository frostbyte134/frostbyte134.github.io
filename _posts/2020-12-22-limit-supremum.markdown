---
layout: post
title:  "Limit supremum and infimum"
date:   2020-12-22 09:00:05 +0800
categories: analysis
use_math: true
tags: analysis limit_supremum supremum limit_infimum infimum
---
References
* (DA): 맛있는 해석학 4판, 김백진
* Rudin : Principles Of Mathematical Analysis - W.Rudin

revision history
* written in 2018.12.29
* 1st revision in 2020.12.22
	* TODO: add post and link of the monotonic convergence theorem

### Definitions

For a sequence \\(\\{a\_n\\}\\), let \\(C\\) be the set of all cluster points of it.  
(`Cluster point` of a sequence : there exist a subsequence converging to it).  
1. If \\(\\{a\_n\\}\\) is __upper bounded__ and \\(C\neq\emptyset\\), let \\(\sup C\\)  be the `limit superior` of \\(\\{a\_n\\}\\), and denote by \\[\text\{limsup\}\_\{n\rightarrow\infty\}a\_n=\Lambda\\]
2. If \\(\\{a\_n\\}\\) is __lower bounded__ and \\(C\neq\emptyset\\), let \\(\inf C\\)  be the `limit inferior` of \\(\\{a\_n\\}\\), and denote by \\[\text\{liminf\}\_\{n\rightarrow\infty\}a\_n=\lambda\\]

If \\(\\{a\_n\\}\\) is not bounded, or when \\(C=\emptyset\\), 
1. If \\(\\{a\_n\\}\\) is not upper bounded, then define \\(\text\{limsup\}\\ a\_n=+\infty\\)
2. If \\(\\{a\_n\\}\\) is not lower bounded, then define \\(\text\{liminf\}\\ a\_n=-\infty\\)
3. If \\(\\{a\_n\\}\\) is upper bounded and \\(C=\emptyset\\), then define \\(\text\{limsup\}\\ a\_n=-\infty\\)
4. If \\(\\{a\_n\\}\\) is lower bounded and \\(C=\emptyset\\), then define \\(\text\{limsup\}\\ a\_n=+\infty\\)


For converging sequences,
1. is bounded
2. \\(C\\) is singleton  
Thus __for converging sequences__, \\(\text\{limsup=liminf\}\\).


### 3.7.5 Definition of limit superior using \\(\epsilon-N\\) statement
> __Theorem__ 3.7.5 (DA): Definition of limit superior using \\(\epsilon-N\\)  
Let \\(\\{a\_n\\}\\) is bounded, and \\(\Lambda\in\Re\\).  
Then \\(\Lambda=\text\{limsup\}\\ a\_n\\) i.i.f,
1. \\(\forall \epsilon > 0,\\ \exists N\in\mathbb\{N\},\\ \forall n\\ :\\ n>N\quad\rightarrow\quad a\_n<\Lambda+\epsilon\\)  
	* Any subsequence cannot converge to a limit larger than \\(\Lambda\\).
	* We have to show that no such subseq exists for some \\(\epsilon\\), thus \\(\exists N\in\mathbb\{N\},\\ \forall n>N\\).
2. \\(\forall \epsilon > 0,\forall N\in\mathbb\{N\},\\ \exists n\\ :\\ n>N\quad\land\quad a\_n>\Lambda-\epsilon\\)  
	* There is subsequence converging to \\(\Lambda\\) or larger
	* We have to construct a subseq, thus \\(\forall N\in\mathbb\{N\}\\)
	
__proof__: \\(\rightarrow\\). Let \\(\text\{limsup\}\\ a\_n=\Lambda\\).  
1. Negating 1. gives, 
\\[\exists \epsilon > 0,\\ \forall N\in\mathbb\{N\},\\ \exists n\\ :\\ n>N\quad\land\quad a\_n\geq\Lambda+\epsilon\\]
Thus for some \\(\epsilon\\), \\(a\_n\geq\Lambda+\epsilon\\) infinitely many times - contradicting that \\(\sup C=\Lambda\\).
2. Negating 2. gives,
\\[\exists \epsilon > 0,\exists N\in\mathbb\{N\},\\ \forall n\\ :\\ n>N\quad\rightarrow\quad a\_n\leq\Lambda-\epsilon\\]
Thus for some \\(\epsilon>0\\), every subsequence converges to a limit converges to a number less than or equal to \\(\Lambda-\epsilon\\) contradicting that \\(\sup C=\Lambda\\).

\\(\leftarrow\\): Let \\(\text\{limsup\}\\ a\_n=\Lambda'\\). We'll show that \\(\sup C=\Lambda'=\Lambda\\), where \\(\Lambda\\) is the number satisfying 1. and 2.  

1. \\(\Lambda'\leq\Lambda\\): we'll use 1. to show that no subsequence of \\(\\{a\_n\\}\\) converges to a cluster point larger than \\(\Lambda\\).  
If not, then \\(\Lambda'>\Lambda\\). Let \\(\epsilon=(\Lambda'-\Lambda)/2\\), and using 1 gives
\\[a\_n<\Lambda+\epsilon=\Lambda+\frac\{\Lambda'-\Lambda\}\{2\}=\Lambda'-\epsilon,\quad \forall n > N\\]
Thus \\(\Lambda'\\) cannot be \\(\sup C\\)=supremum of all cluster points, a contradiction.
2. \\(\Lambda'\geq\Lambda\\): We'll use 1, 2 to construct a subseq converging to \\(\Lambda'\\), and use that \\(\Lambda'=\sup C\\).  
Using 1. and 2., for each \\(\epsilon=1/k,\\ \exists N\in\mathbb\{N\}\\ :\\ \Lambda-\frac\{1\}\{k\}<a\_n<\Lambda+\frac\{1\}\{k\}\\)  
Using the sandwich theorem (link), we see that there is a subsequence converging to \\(\Lambda\\), and since \\(\Lambda'\\) is the supremum over the cluster points, the theorem follows. __Q.E.D.__


### Partial additivity of the limit supremum/infimum
> __Theorem__ 3.7.9 (DA): For bounded sequences \\(\\{a\_n\\},\\{b\_n\\}\\),  
\\[1.\\ \\text\{limsup\}\\{a\_n+b\_n\\}\leq\mathop\{\text{limsup}\}\\ \\{a\_n\\}+\mathop\{\text{limsup}\}\\ \\{b\_n\\}\\]
\\[2.\\ \\text\{liminf\}\\{a\_n+b\_n\\}\geq\mathop\{\text{liminf}\}\\ \\{a\_n\\}+\mathop\{\text{liminf}\}\\ \\{b\_n\\}\\]

__proof__: For 1, Let \\(\text\{limsup\}\\ \\{a\_n\\}=A,\\ \text\{limsup\}\\ \\{b\_n\\}=B\\) and suppose the theorem does not hold. Then there must be a subsequence of \\(\\{a\_n+b\_n\\}\\) such that converges to a cluster point larger thatn \\(A+B\\). In equation,
\\[\exists \epsilon,\\ \forall N\in\mathbb\{N\},\\ \exists n\\ :\\ n>N\quad\rightarrow\quad a\_n+b\_n>A+B+\epsilon\\]
(Using \\(n\_k\\) subseq notation is much simpler, but anyway)  
This in turn implies
\\[a\_n>A+\frac\{\epsilon\}\{2\}\quad \lor\quad b\_n>B+\frac\{\epsilon\}\{2\}\\]
for infinitely many \\(n\\). Consequently,
\\[\text\{limsup\}\\ \\{a\_n\\} > A+\frac\{\epsilon\}\{2\}\quad\lor\quad\text\{limsup\}\\ \\{b\_n\\} > B+\frac\{\epsilon\}\{2\}\\]
(think about the Bolzano-Weierstrass Theorem(link)) for some \\(\epsilon\\), which is a contradiction.



### Definition of limit superior/inferior using supremum/infimum
__(important!)Theorem 3.7.10 (DA)__ For a bounded sequence \\(\\{a\_n\\}\\), 
\\[\mathop\{\text{lim sup}\}\\{a\_n\\}=\lim\_\{n\rightarrow\infty\}\sup\_\{k\geq n\}a\_k=\inf\_\{N\in\mathbb\{N\}\}\sup\_\{k\geq n\}a\_k\\]
\\[\mathop\{\text{lim inf}\}\\{a\_n\\}=\lim\_\{n\rightarrow\infty\}\inf\_\{k\geq n\}a\_k=\sup\_\{N\in\mathbb\{N\}\}\inf\_\{k\geq n\}a\_k=\\]

(we first show that \\(\mathop\{\text{limsup}\}\\ \\{a\_n\\}=\inf\_\{N\in\mathbb\{N\}\}\sup\_\{k\geq n\}a\_k\\), and then \\(\inf\_\{N\in\mathbb\{N\}\}\sup\_\{k\geq n\}a\_k = \lim\_\{n\rightarrow\infty\}\sup\_\{k\geq n\}a\_k\\))

__proof__: Let
\\[x\_n=\sup\\{a\_k\\ \|\\ k\leq n\\}\\]
It is trivial that \\(x\_n\\) is monotonocally decreasing seq (think about the support of \\(\sup\\)), and is bounded by its definition. Thus \\(x\_n\\) converges by the __monotonic convergence theorem (link),__ and let \\(L\\) __be the limit of it.__  
1. Then \\(\forall \epsilon>0,\\ \exists N\\) such that
\\[\| x\_N-L\| <\epsilon\quad \text{and} \quad \|x\_N\| - \|L\| < \| x\_N-L\| < \epsilon \quad\quad ... \text{triangular inequality}\\]
\\[\rightarrow x\_N<L+\epsilon\\]
Note that for \\(n\geq N\\), \\(a\_n\leq x\_n\\) holds so that
\\[\forall \epsilon>0,\\ \exists N,\\ \forall n\\ :\\ n>N\quad\rightarrow\quad a\_n\leq x\_n<L+\epsilon\\]
which is exactly 1. of 3.7.5 (DA)
1. Now, suppose that arbitrary \\(K\in \mathbb\{N\}\\) is given. By letting \\(m>\max(N, K)\\) for the given \\(\epsilon\\) (which was arbitrary) and \\(N\\) (which was dependent on \\(\epsilon\\), but it does not matter since we want existence of natural numbers \\(k>m>K\\)) of 1., 
\\[\|L-\frac{\epsilon}{2}\|<x\_m \quad\rightarrow\quad L-\frac{\epsilon}{2} < x\_m\\]
holds. Furthermore, since \\(x\_m\\) is a _supremum_ over \\(\\{a\_k | k \geq m\\}\\), by using the property of supremum \\(\exists k \geq m\\) such that, 
\\[x\_m - \frac{\epsilon}{2} < a\_k \leq x\_m\\]
so that, 
\\[L - \frac{\epsilon}{2} < x\_m < a\_k + \frac{\epsilon}{2}\\]
\\[L - \epsilon < a\_k\\]
in conclusion,
\\[\forall K\in \mathbb\{N\},\\ \exists k, :\quad k\geq K \quad \land \quad L-\epsilon < a\_k\\]
which is exactly 3.7.5-2. 

Using above Theorem, we can show some useful examples for the optimization

**************************************

> Example (DA) 3.7.11. for a bounded sequence \\(\\{a\_n\\}\\), show that 
\\[\mathop\{\text{lim sup}\}(-a\_n) = \mathop\{\text{lim inf}\}(a\_n)\\]

by the Theorem 3.7.10 (DA), 
\\[\mathop\{\text{lim sup}\}(-a\_n) = \lim\_{n\rightarrow\infty}(\sup\\{-a\_k \| k \geq n\\}) = \lim\_{n\rightarrow\infty}(-\inf\\{a\_k \| k \geq n\\})\\]
\\[ = -\mathop\{\text{lim inf}\}(a\_n)\\]

**************************************

> Example (DA) 3.7.12. for a bounded sequence \\(\\{a\_n\\},\\ \\{b\_n\\}\\), if \\(a\_n\leq b\_n\\ \forall n\in \mathbb{N}\\) then
\\[\mathop\{\text{lim sup}\}(a\_n) \leq \mathop\{\text{lim sup}\}(a\_n)\\]

__Proof.__  
1. Suppose 
\\[\sup\\{a\_k \| k \geq n\\} > \sup\\{b\_k \| k \geq n\\}\\]
Let \\(\sup\\{a\_k \| k \geq n\\} = A,\\ \sup\\{b\_k \| k \geq n\\} = B\\). Then by letting \\(\epsilon = (A-B)/2\\) and using the definition of supremum,
\\[A-\epsilon < a\_k \leq A\\]
\\[B-\epsilon < b\_k \leq B\\]
\\[A-\epsilon < a\_k < b\_k \leq B\\]
which is a contradiction. Therefore \\(\sup\\{a\_k \| k \geq n\\} \leq \sup\\{b\_k \| k \geq n\\}\\).
2. Then we have
\\[\mathop\{\text{lim sup}\}(a\_n) =  \lim\_{n\rightarrow\infty}(\sup\\{a\_k \| k \geq n\\}) \leq \lim\_{n\rightarrow\infty}(\sup\\{b\_k \| k \geq n\\}) = \mathop\{\text{lim sup}\}(a\_n)\\]
by the property of limit.

**************************

### (Rudin) Theorem 2.37
> If \\(E\\) is 
1. a set with infinite cardinality 
2. a subset of a compact set \\(K\\)  
then \\(E\\) has a limit point in \\(K\\)

__proof__: 
1. If not, then \\(E\\) does not have an limit point in \\(K\\)  
\\(\rightarrow\\) for every \\(k\in K\\), there exists \\(\epsilon\_k\\) such that the neighbor \\(N\_\{\epsilon\_k\}(k)\\) contains at most one point of \\(E\\) (namely, when \\(k\in E\\)).
2. \\(E\\) can be covered by the open cover \\(\\{N\_\{\epsilon\_k\}(k)\\}\\), but by 1 there exists no finite subcover which can cover \\(E\\), which also cannot cover \\(K\\), a contradiction.

### (Rudin) Theorem 3.6
> (a) If \\(\\{p\_n\\}\\) is a sequence in a compact metric space \\(X\\), then some subsequence of \\(\\{p\_n\\}\\) converges to a point in \\(X\\). 

Notice that the `set` is replaced with `sequence`, in compact metric space.

__proof__: Let \\(E\\) be the range of \\(\\{p\_n\\}\\).
1. When \\(E\\) is finite, \\(\exists\\) a point \\(x\in X\\) with infinitely many occurence in \\(\\{p\_n\\}\\).
2. When \\(E\\) has infinite cardinality, then by the `Thm 2.37` \\(E\\) has a limit point \\(x\in X\\).  
By the definition of the limit point (cluster point), every neighborhood of \\(x\\) contains infinitely many points of \\(E\\).  
For each \\(n\in \mathbb\{N\}\\), choose \\(p\_\{n\_i\}\in E\\) in \\(N\_\{1/n\}(x)\\).  
We now have a subsequence converging to \\(x\in X\\).

> (b) Every bounded sequence in R^k contains a convergent subsequence  

__proof__: This follows from (a), since `Thm 2.41` implies that every bounded subset of \\(R^k\\) lies in a compact subset of \\(R^k\\).

### (Rudin) Theorem 3.7
> The subsequential limits of a sequence \\(\\{p\_n\\}\\) in a metric space \\(X\\) form a closed subset of \\(X\\)

(We'll gonna show that, for a limit point \\(q\\) of \\(E^\*\\), the set of all subsequential limit points of \\({p\_n\}\\), there eixsts a subsequence of \\(\\{p\_n\\}\\) converging to \\(q\\). 

__proof__: with \\(E^\*\\) and \\(q\\) as above, 
1. choose \\(n\_1\\) s.t. \\(p\_\{n\_1\}\in E\\ \land\\ p\_\{n\_1\}\neq q\\). If there is no such \\(n\_1\\), then \\(E^\*\\) is an singleton and we have nothing to prove. Let \\(\delta=\|p\_\{n\_1\}-q\|\\).
2. Using induction, let \\(n\_\{i-1\}\\) be choosed.  
	-1. Since \\(q\\) is the limit point of \\(E\\), \\[\forall i\in\mathbb\{N\},\\ \exists q\_i\in E\\ : \\ \|q-q\_i\| < \delta 2^\{-i\}\\]  
	-2. Since \\(q\_i\in E^\*\\), there exists a subsequence \\(\\{p\_\{n\_i\}\\}\\) converging to \\(q\_i\\), and
	\\[\exists j \in\mathbb\{N\} ,\\ \forall k \in\mathbb\{N\} : k>j\quad\rightarrow\quad  \|p\_\{n\_k\}-q\_i\| <\delta 2^\{-i\}\\]
	-3. Using aboves,
	\\[\forall i\in \mathbb\{N\},\\ \exists j\in\mathbb\{N\},\\ \forall k\in\mathbb\{N\}\\ :\\  k>j\quad\rightarrow\quad\|q-p\_\{n\_k\}\| \leq \|q-q\_i\| + \|p\_\{n\_k\}-q\_i\| < 2\delta 2^\{-i\} = \delta 2^\{1-i\}\\]
	which shows that \\(\\{p\_\{n\_i\}\\}\\) converges to \\(q\\).
	
> If \\(x> q\\), then there is an integer \\(N\\) such that \\(p\_n<x\\)

__proof__: Suppose not. Then \\(p\_n\geq x\\) for infinitely many times, and we see that there is an subsequence converging to the limit value large or equal than \\(x\\), which is a contradiction.

> Limit supremum is unique

__proof__: Let \\(p,q\\) be two distinct limit supremum. Then there exists \\(x\\ :\\ p<x<q\\). Since \\(p\\) satisfies (b), we see that \\(\exists N\in\mathbb\{N\}\\) such that, \\(n>N\quad\rightarrow\quad p\_n<x\\) but then \\(q\\) cannot satisfy (a). 
 
With this theorem, we see that __there always exists a subsequence converges to limsup (or liminf)__ of a sequence
	



