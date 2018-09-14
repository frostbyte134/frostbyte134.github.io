---
layout: post
title:  "Proposition and Condition"
date:   2018-09-12 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis proposition
---


### Proposition and Propositional Function
A `proposition` is a mathematical statement that __can only be true or false.__  
It is generally represented with lowercase letter alphabet, such as \\(p, q, r,...\\).

- \\(\sim\\): negation
- \\(\lor\\): logical OR, \\(\land\\): logical AND

Some statement turns out to be true or false when values are assigned to its variables.  
We call such statement as a `Propositional function`, or a `condition`.

They are represented with \\(p(x), q(x), r(x)\\) when we want to highlight its variables. Otherwise they are represented with lowercase alphabet \\(p,q,r,...\\), like propositions.

- `Domain` \\(U\\): set of all elements \\(x\\) which can be assigned to \\(p(x)\\)
- `Truth set` \\(\\{x\in U \| p(x)\\}\\): set of all elements \\(x\\) which makes \\(p(x)\\) true

### Special propositions

1. `Universial proposition`: for all element \\(x\\) in \\(U\\), such that \\(p(x)\\) holds
\\[\forall x\in U : p(x)\\]
where \\(\forall\\) is referred as the `universial quantifier`
2. `Existence proposition`: there exists an elements \\(x\\) in \\(U\\), such that \\(q(x)\\) holds
\\[\exists x\in U :q(x)\\]
where \\(\exists\\) is referred as the `existence quantifier`
3. `Conditional proposition`: for every element such that \\(p(x)\\) holds, \\(q(x)\\) also holds.
\\[p(x)\rightarrow q(x)\\]
	When \\(p(x)\rightarrow q(x)\\) holds, we call
	- \\(p(x)\\): `sufficient condition` (\\(p(x)\\) is sufficient enough to guarantee \\(q(x)\\))
	- \\(q(x)\\): `necessary condition` (it is necessary for \\(q(x)\\) to be true when \\(p(x)\\) is true)

	__For two propositional functions__ \\(p(x), q(x)\\) __which shares a domain, their conditional proposition__\\(p(x)\rightarrow q(x)\\) __also becomes a propositional function__
	
	\\[p \rightarrow q \text\{ is a proposition, and\}\\]
	\\[p(x)\rightarrow q(x) \text\{ is a propositional function\}\\]

### Miscs

1. symbol \\(\equiv\\)
\\[f(x)\equiv g(x)\\]
means that \\[\forall x\in U, f(x)=g(x) \text\{ holds\}\\]
2. symbol \\(:=\\) : defined as
3. `inverse` of a proposition \\(p\rightarrow q \\): \\(\quad q\rightarrow p\\)
3. `converse` of a proposition \\(p\rightarrow q \\): \\(\quad\sim p\rightarrow \sim q\\)
3. `contrapositive` of a proposition \\(p\rightarrow q \\): \\(\quad\sim q\rightarrow \sim p\\)
4. For propositions, `transitive` / `De Morgan's rule` holds.  
Based on the De Morgan's rule, we can derive the `negation rule of the quantifiers`
\\[\sim(p(x_1)\lor p(x_2)\lor p(x_3)\lor \cdots \lor p(x_n))\quad\Longleftrightarrow\quad\sim p(x_1) \land \sim p(x_2) \land \sim p(x_3) \land \cdots \land \sim p(x_n)\\]
is equivalent to
\\[\sim(\forall x \in \\{x_1,...,x_n\\}, p(x))\quad\Longleftrightarrow\quad \exists x\in\\{x_1,...,x_n\\}:\sim p(x)\\]

Next:  

