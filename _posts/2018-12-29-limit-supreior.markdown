---
layout: post
title:  "Limit superior and inferior"
date:   2018-12-29 09:00:05 +0800
categories: analysis
use_math: true
tags: analysis limit_superior supremum limit_inferior infimum
---

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


### Definition of limit superior using \\(\epsilon-N\\) statement
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
Thus for some \\(\epsilon\\), we can construct a sequence converging to limit larger than \\(\Lambda+\epsilon\\) (There are infinitely many \\(N\\): a cluster point (of sequence) exists) - contradiction that \\(\sup C=\Lambda\\).
2. Negating 2. gives,
\\[\exists \epsilon > 0,\exists N\in\mathbb\{N\},\\ \forall n\\ :\\ n>N\quad\rightarrow\quad a\_n\leq\Lambda-\epsilon\\]
Thus for some \\(\epsilon>0\\), every subsequence converges to a limit less than or equal to \\(\Lambda\\) (or \\(\Lambda - \epsilon \\) is the new supremum)- contradiction that \\(\sup C=\Lambda\\).

\\(\leftarrow\\): Let \\(\text\{limsup\}\\ a\_n=\Lambda'\\). We'll show that \\(\sup C=\Lambda'=\Lambda\\), where \\(\Lambda\\) is the number satisfying 1. and 2.  

1. \\(\Lambda'\leq\Lambda\\): we'll use 1. to show that no subsequence of \\(\\{a\_n\\}\\) converges to a cluster point larger than \\(\Lambda\\).  
If not, then \\(\Lambda'>\Lambda\\). Let \\(\epsilon=(\Lambda'-\Lambda)/2\\), and using 1 gives
\\[a\_n<\Lambda+\epsilon=\Lambda+\frac\{\Lambda'-\Lambda\}\{2\}=\Lambda'-\epsilon,\quad \forall n > N\\]
Thus \\(\Lambda'\\) cannot be \\(\sup C\\)=supremum of all cluster points, a contradiction.
2. \\(\Lambda'\geq\Lambda\\): We'll use 1, 2 to construct a subseq converging to \\(\Lambda'\\), and use that \\(\Lambda'=\sup C\\).  
Using 1. and 2., for each \\(\epsilon=1/k,\\ \exists N\in\mathbb\{N\}\\ :\\ 1\Lambda-\frac\{1\}\{k\}<a\_n<\Lambda+\frac\{1\}\{k\}\\)  
Using the sandwich theorem (link), we see that there is a subsequence converging to \\(\Lambda\\), and since \\(\Lambda'\\) is the supremum over the cluster points, the theorem follows. __Q.E.D.__


### Partial additivity of the limit supremum/infimum
> __Theorem__ 3.7.9 (DA): For bounded sequences \\(\\{a\_n\\},\\{b\_n\\}\\),  
1. \\(\\text\{limsup\}\\{a\_n+b\_n\\}\leq\text\{limsup\}\\ \\{a\_n\\}+\text\{limsup\}\\ \\{b\_n\\}\\) 
2. \\(\\text\{liminf\}\\{a\_n+b\_n\\}\geq\text\{liminf\}\\ \\{a\_n\\}+\text\{liminf\}\\ \\{b\_n\\}\\)

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
1. \\(\text\{limsup\}\\ \\{a\_n\\}=\inf\_\{N\in\mathbb\{N\}\}\sup\_\{k\geq n\}a\_k=\lim\_\{n\rightarrow\infty\}\sup\_\{k\geq n\}a\_k\\)
2. \\(\text\{liminf\}\\ \\{a\_n\\}=\sup\_\{N\in\mathbb\{N\}\}\inf\_\{k\geq n\}a\_k=\lim\_\{n\rightarrow\infty\}\inf\_\{k\geq n\}a\_k\\)

__proof__: Let
\\[x\_n=\sup\\{a\_k\\ \|\\ k\leq n\\}\\]
It is trivial that \\(x\_n\\) is monotonocally decreasing seq (think about the support of \\(\sup\\)), and is bounded by its definition. Thus \\(x\_n\\) converges by the monotonic convergence theorem (link), and let \\(\Lambda\\) be the limit of it.  
1. Then \\(\forall \epsilon>0,\\ \exists N\\) such that
\\[x\_N-L<\epsilon\quad\rightarrow\quad x\_N<L+\epsilon\\]
Since for \\(n\geq N\\), \\(a\_n\leq x\_n\\) holds,
\\[\forall \epsilon>0,\\ \exists N,\\ \forall n\\ :\\ n>N\quad\rightarrow\quad a\_n\leq x\_n<L+\epsilon\\]
which is exactly 1. of 3.7.5 (DA) (link)
2. For some \\(N\\) of 1., \\(\forall K\geq N\\),
\\[-\epsilon<x\_K-L\quad\rightarrow\quad L-\epsilon < x\_K\\]
holds. Since \\(x\_K\\) is a _supremum_ over \\(a\_k,\\ k\geq K\\), for such \\(\epsilon\\),  
\\[\exists k\geq K\\ :\\ L-\epsilon < a\_k\leq x\_K\\]
In summary, by exchanging \\(\forall K \geq N,\\ \exists k > K\\) to \\(\quad \forall K\in\mathbb\{N\},\exists k > K\\),
\\[\forall \epsilon > 0,\\ \forall k\in N,\\ \exists k\\ :\\ k\geq K \quad\land\quad L-\epsilon <a\_k\\]
which is exactly 3.7.5-2. 


Next:  

<br/>
* (DA): 맛있는 해석학 4판, 김백진