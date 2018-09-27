---
layout: post
title:  "Mathematical Induction and Natural Number"
date:   2018-09-27 5:00:05 +0800
categories: analysis
use_math: true
tags: analysis induction natural_number
---

- Can prove statements with natural number domain

### Indudctive Set and Natural Numbers

`Inductive set` \\(I\\) is defined by
1. \\(1\in I\\)
2. \\(n\in I \quad\rightarrow\quad n+1\in I\\)

Above 2 conds holds for \\(\mathbb\{N\}\\), but are not enough to specify \\(\mathbb\{N\}\\). It is specified as the __smallest inductive set__.

(Easy workaround) Show that intersection of inductive set is inductive set. 

Other numbers are defined by
* \\(\mathbb\{Z\}:=(-\mathbb\{N\}\bigcup\{0\}\bigcup\mathbb\{N\}\\)
* \\(\mathbb\{Q\}:=\\{p/q \\ \| \\ p\in\mathbb\{Z\},\\ q\in\mathbb\{Z\}^*\\}\\)
* Irrational number: a number which is not in \\(\mathbb\{Q\}\\)

### Mathematical Induction
> Theorem 2.3.4. Mathematical Induction  
If a statement \\(p\\) which having \\(\mathbb\{N\}\\) as its domain satisfies
1. \\(p(1)\\) holds
2. if \\(p(k)\\) for \\(k\in\mathbb\{N\}\\) holods, then \\(p(k+1)\\) holds (`Inductive hypothesis`)  
Then \\(p(n)\\) holds for \\(n\in\mathbb\{N\}\\).

Proof (for fun):
1. Define truth set of \\(p\\) as \\(P\\).  
then, \\(P:=\{k\in\mathbb\{N\} \\ \| \\ p(k)\}\\), so \\(P\subseteq \mathbb\{N\}\\).
2. \\(P\\) is an inductive set by the condition, so \\(\mathbb\{N\}\subseteq P\\) holds (\\(\mathbb\{N\}\\) is the smallest inductive set)



Next:  

