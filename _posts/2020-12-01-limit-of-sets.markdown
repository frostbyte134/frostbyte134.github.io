---
layout: post
title:  "Set and Probability"
date:   2020-12-01 08:00:05 +0800
categories: probability
use_math: true
tags: math probability 
---
{:.acounter}


TODO:
- rename title
- merge this page to somewhere?


> Preliminary (must!)  
  - <a href="https://nailbrainz.github.io/analysis/2018/09/14/set-basic.html" target="_blank">set-basic</a>
  - <a href="https://nailbrainz.github.io/analysis/2018/09/25/ordered-set.html" target="_blank">Ordered set, Isomorphism and Supremum</a>
  - <a href="https://nailbrainz.github.io/analysis/2018/09/25/cardinality-of-sets-and-axiom-of-choice.html" target="_blank">Cardinality of Sets and the Axiom of Choice</a>




### Sets
- \\(A^n\\) : Cartesian product of sets, defined as a set of \\(n\\)-tuples \\[A\_1\times ... \times A\_n := \\{ (a\_1,...,a\_n) \| a\_i\in A\_i \\ \forall i\\}\\]
  - Note that \\(\emptyset \subset \mathcal\{P\}(A\_i)\\), and also \\(\emptyset \subset \mathcal\{A^n\}\\). Cartesian product when \\(A\_i=\emptyset\\) is not defined <a href="https://www.quora.com/What-happens-if-you-take-a-cartesian-product-of-an-empty-set-and-a-non-empty-set" target="_blank">https://www.quora.com/What-happens-if-you-take-a-cartesian-product-of-an-empty-set-and-a-non-empty-set</a>
  - \\(A^\infty\\) is define in the same way (tuple of infinite length)
- \\(2^A = \mathcal\{A\}\\) : set of all subsets of \\(A\\)
- There is an 1-1 correspondence between \\[\\{0,1\\}^\infty,\quad \\{0,1\\}^\mathbb{N},\quad 2^\mathbb{N}\\] 이거 증명 어디 있었는데..다 까먹었네
  - such correspondence can be used in shoing that \\[\text\{If \} A \text\{ is infinite, then \} 2^A \text\{ is uncountable\}\\]
  - __proof__ : \\(\|2^\mathbb{N}\| \leq \|2^A\|\\) and  \\(\|2^\mathbb{N}\| \\) is uncoutable, which is a result with 1-1 correspondance with \\(\\{0,1\\}^\infty\\)

### Limit of sets
1. `Limit supremum` \\[\limsup\_\{n\rightarrow \infty \} A\_n = \mathop\{\bigcap\}\_\{k=1\}^\infty \left( \mathop\{\bigcup\}\_\{n=k\}^\infty \right) A\_n\\]
    for \\(w\in \limsup\_\{n\rightarrow \infty\}A_n\\) to be hold, \\(w\\) must be in \\(A\_n\\) infinitely many times, not necessarily successive.
2. `Limit infimum` \\[\liminf\_\{n\rightarrow \infty \} A\_n = \mathop\{\bigcup\}\_\{k=1\}^\infty \left( \mathop\{\bigcap\}\_\{n=k\}^\infty \right) A\_n\\]
    for \\(w\in \liminf\_\{n\rightarrow \infty\}A_n\\) to be hold, \\(w\\) must be in \\(A\_n\\) infinitely and successively, for some \\(n\geq N\\).


### Strange sets
- not every subset of \\((0,1]\\) is Lebesgue measurable ...