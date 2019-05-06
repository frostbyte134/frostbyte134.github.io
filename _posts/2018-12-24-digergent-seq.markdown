---
layout: post
title:  "Divergent sequences"
date:   2018-12-24 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis limit sequence divergent
---

We say that a sequence \\(\\{a\_n\\}\\) converges to a `limit` \\(L\in\Re\\) when
\\[\forall \epsilon > 0,\\ \exists n\in \mathbb\{N\},\\ \forall n\\ : \\ n > N\quad\rightarrow\quad \| a\_n - L \| < \epsilon\\]

Obviously, its negation is
\\[\exists \epsilon > 0, \forall n\in \mathbb\{N\},\\ \exists n\\ : \\ n > N\quad\rightarrow\\ \land\\ \| a\_n - L \| \geq \epsilon\\]

`Divergent` sequences are in the category of nonconvergent sequences, but we need bit more conditions to define them.

### Definition
For a sequence \\(\\{a\_n\\}\\),
(i) diverges to \\(+\infty\\) when
\\[\forall Y\in\mathbb\{R\},\\ \exists N\in\mathbb\{N\},\\ \forall n\\ :\\ n>N\quad\rightarrow\quad a\_n>Y\\]
(ii) diverging to \\(-\infty\\) is defined similarly.

### Theorems
> __Theorem 3.4.6(DA):__ Sandwich theorem for the divergent sequences  
For two sequences \\(\\{a\_n\\},\\ \\{b\_n\\}\\), assume that \\(a\_n>b\_n\\) for finitely many \\(n\\). Then,
1. \\(\\{a\_n\\}\text\{ diverges to \}+\infty\quad\rightarrow\quad\\{b\_n\\}\text\{ diverges to \}-\infty\\) 
2. \\(\\{b\_n\\}\text\{ diverges to \}-\infty\quad\rightarrow\quad\\{a\_n\\}\text\{ diverges to \}-\infty\\)

__proof__: for 1, since \\(\\{a\_n\\}\\) diverges,
\\[\forall Y\in\mathbb\{R\},\\ \exists N\in\mathbb\{N\},\\ \forall n\\ :\\ n>N\quad\rightarrow\quad a\_n>Y\\]
and by the assumption it holds that,
\\[n>N\quad\rightarrow\quad b\_n\geq a\_n>Y\\]
Thus by the definition \\(\\{b\_n\\}\\) diverges. 2 is proved similarly.

<br/>
* (DA): 맛있는 해석학 4판, 김백진

Next:  

