---
layout: post
title:  "Limit superior and inferior"
date:   2018-12-29 09:00:05 +0800
categories: analysis
use_math: true
tags: analysis limit_superior supremum limit_inferior infimum
---

For a sequence \\(\\{a\_n\\}\\), let \\(C\\) be the set of all cluster points of it. (Cluster point of a sequence : there exist a subsequence converging to it).  
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
	(Any subsequence cannot converge to a limit larger than \\(\Lambda\\).)  
	(\\(\exists N\in\mathbb\{N\},\\ \forall n\\): for showing that __there could be no sequence__ converging to value larger than \\(\Lambda\\).)
2. \\(\forall \epsilon > 0,\forall N\in\mathbb\{N\},\\ \exists n\\ :\\ n>N\quad\land\quad a\_n>\Lambda-\epsilon\\)  
	(There is subsequence converging to \\(\Lambda\\) or larger)  
	(with \\(\forall N\in\mathbb\{N\},\\ \exists n\\) statement, we can easily generate a subseq for each \\(N\\))

__proof__: \\(\rightarrow\\). Let \\(\text\{limsup\}\\ a\_n=\Lambda\\).  
1. Negating 1. gives, 
\\[\exists \epsilon > 0,\\ \forall N\in\mathbb\{N\},\\ \exists n\\ :\\ n>N\quad\land\quad a\_n\geq\Lambda+\epsilon\\]
Thus for some \\(\epsilon\\), we can construct a sequence converging to limit larger than \\(\Lambda+\epsilon\\) - contradiction that \\(\sup C=\Lambda\\).
2. Negating 2. gives,
\\[\exists \epsilon > 0,\exists N\in\mathbb\{N\},\\ \forall n\\ :\\ n>N\quad\rightarrow\quad a\_n\leq\Lambda-\epsilon\\]
Thus for some \\(\epsilon>0\\), every subsequence converges to a limit less than or equal to \\(\Lambda\\) - contradiction that \\(\sup C=\Lambda\\).

\\(\leftarrow\\): Let \\(\text\{limsup\}\\ a\_n=\Lambda'\\). We'll show that \\(\Lambda'\\) will 

<br/>
* (DA): 맛있는 해석학 4판, 김백진

Next:  

