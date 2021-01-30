---
layout: post
title:  "Cauchy sequence and Contractive sequence"
date:   2021-01-27 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis limit sequence complete_space contractive_sequence
---

- <a href="https://drive.google.com/file/d/1j76UouKwCaY0OdWEkEYRIQrwFe9KXlRJ/view?usp=sharing" target="_blank">rudin Chap3 Numerical Sequences and Series</a>

revision history
- written in 2018.12.29
- revision in 2021.01.27

is useful for proving convergence, without knowing the exact limit.

### Definition
A sequence \\(\\{a\_n\\}\\) is called a `Cauchy sequence` if
\\[\forall \epsilon > 0,\\ \exists n\in\mathbb\{N\},\\ \forall n,m>N\quad \rightarrow \quad \|a\_n-a\_m\| < \epsilon \\]

- Notice that, contrary to the definition of the limit of a sequence, above definition does not require explict repr of limit point. 
- Definition of `diameter` is required to prove the main results (refer to the pdf)

### Cauchy Seuquences

> __Theorem 3.11 (PMA)__  
1. In any metric space \\(X\\), every convergent sequence is a Cauchy sequence
2. If \\(X\\) is a compact metric space and if \\(\\{p\_n\\}\\) is a Cauchy sequence in \\(X\\), then \\(\\{p\_n\\}\\) converges to some point of \\(X\\).
3. In \\(R^K\\), every Cauchy sequence converges

### Thm 3.6.2 Convergence of Cauchy sequuence
> A sequence \\(\\{a\_n\\}\in \Re \\) converges i.ii.f it is a Cauchy sequence

__proof__.  
\\(\rightarrow\\): Suppose \\(\\{a\_n\\}\\) converges to \\(L\\). Then
\\[\forall \epsilon > 0,\\ \exists N\in\mathbb\{N\},\\ \forall n,m\quad :\quad n,m>N\quad\rightarrow\quad \|a\_n-L\|<\epsilon/2, \|a\_m-L\|<\epsilon/2\\]
We can bound \\(\|a\_n-a\_m\|=\|a\_n-\epsilon-a\_m+\epsilon\|\\) by
\\[\|a\_n-a\_m\|=\|a\_n-\epsilon-a\_m+\epsilon\|\leq\|a\_n-\epsilon\|+\|-a\_m+\epsilon\|<\epsilon/2+\epsilon/2\\]
\\(\leftarrow\\): 
1. Cauchy sequence is bounded  
	For an arbitrary \\(\epsilon>0\\), by the def of Cauchy seq \\(\exists N\in\mathbb\{N\},\\ \forall n,m>N\\) such that 
	\\[\|a\_n\|-\|a\_m\|\leq \|a\_n-a\_m\| < \epsilon\\]
	\\[\rightarrow \|a\_n\|<\|a\_m\|-\epsilon\\]
	By fixing \\(m\\) we see that \\(\\{a\_n\\}\\) is bounded by, \\(\max\\{a\_1,...,a\_\{n-1\},\|a\_m\|-\epsilon \\}\\)
2. By the <a href="{{site.url}}/analysis/2021/01/25/limit.html" target="_blank">Bolzano-Wierstrass theorem</a>, \\(\\{a\_n\\}\\) has a cluster point. Let us denote it by \\(L\\).
3. Then by the def of cluster point \\(\exists\\) a subsequence \\(\\{a\_\{n\_k\}\\}\\) converging to \\(L\\). Now \\(\forall \epsilon>0\\),  
	-1. Since the subsequence converges to \\(L\\), \\(\exists N\_1\in\mathbb\{N\},\\ \forall n\\ :\\ n>N\_1\quad\rightarrow\quad \|a\_n-L\|<\epsilon/2\\)
	-2. Since \\(\\{a\_\{n\_k\}\\}\\) is a Cauchy sequence, \\(\exists N\_2\in\mathbb\{N\},\\ \forall n,m\\: \\ n,m>N\_2\quad\rightarrow\quad \|a\_n-a\_m\| < \epsilon/2\\)  
	Combining above, \\(\forall n,n\_k>\max\\{N\_1,N\_2\\}\\), 
	\\[\|a\_n-L\|=\|a\_n-a\_\{n\_k\}-L+a\_\{n\_k\}\|\leq \|a\_n-a\_\{n\_k\}\|+\|-L+a\_\{n\_k\}\|<\epsilon\\]
	__Q.E.D.__




	
### Complete metric space
A metric space \\((M,D)\\) is called `complete` if arbitrary Cauchy sequence converges.

Example: `contractive sequence`.  
> For a sequence \\(\\{a\_n\\}\\), if 
\\[\exists 0<q<1,\\ \forall n\in\mathbb\{N\}\\ :\\ \|a\_\{n+1\}-a\_\{n\}\|\leq q\|a\_\{n\}-a\_\{n-1\}\|\\]
then we call \\(\\{a\_\{n\}\\}\\) a `contractive sequence`.

For a contractive sequence, generally
\\[\|a\_\{n+1\}-a\_\{n\}\|\leq q^n\|a\_1-a\_n\|\\]
using above,
\\[\|a\_\{n+p\}-a\_\{n\}\|\leq \|a\_\{n+p\}-a\_\{n+p-1\}\|+\|a\_\{n+p-1\}-a\_\{n+p-2\}\|+...+\|a\_\{n+1\}-a\_\{n\}\|\\]
\\[\leq q^\{n+p-1\}\|a\_1-a\_n\|+...+q^\{n\}\|a\_1-a\_n\|\\]
\\[=\Sigma\_\{i=1\}^p q^\{n+i-1\}\|a\_\{n+i\}-a\_\{n+i-1\}\|\\]
\\[=q^n\frac\{1-q^p\}\{1-q\}\|a\_1-a\_0\|\leq \frac\{q^n\}\{1-q\}\|a\_1-a\_0\|\\]
Since \\(0<q<1\\), \\(\exists N\\ :\\ q^N\cdot\frac\{1\}\{1-q\}\|a\_1-a\_0\|<\epsilon\\).  
Now we see that \\(\forall\epsilon>0,\\ \exists N\in\mathbb\{N\},\\ \forall n,p\\ :\\ n>N,\\ p>0 \quad\rightarrow\quad \|a\_\{n+p\}-a\_n\|<\epsilon\\), \\(\\{a\_n\\}\\) is a Cauchy sequence. Thus in complete metric space, especially in \\(\Re\\), \\(\\{a\_n\\}\\) converges.
<br/>


* (DA): 맛있는 해석학 4판, 김백진
* (PMA): Principle of Mathematical Analysis, Walter Rudin
Next:  

