---
layout: post
title:  "Measure Theory 1 - Basics"
date:   2021-01-05 08:00:05 +0800
categories: math
use_math: true
tags: math analysis probability
---

<a href="https://drive.google.com/open?id=1f5A7HRC-3hrEAjQ_vP_lJlsi5UhiM8Db" target="_blank"> Rudin Chap 11</a>


> Chap 11, Principles of Mathematical Analysis, by Walter Rudin



<img src="{{site.url}}/images/math/analysis/measure/measure.jpg" width="800">

- <a href="https://freshrimpsushi.tistory.com/category/%ED%95%B4%EC%84%9D%ED%95%99/%EC%B8%A1%EB%8F%84%EB%A1%A0?page=2" target="_blank">생새우초밥집/해석학/측도론</a>
- <a href="https://freshrimpsushi.tistory.com/480?category=747528" target="_blank">왜 이런 해골복잡한 거리의 확장이 필요한가?</a>

*************************

1. define a `ring` \\(\mathfrak{M} \\) \\[A\bigcup B \in \mathfrak{M} ,\quad\quad A-B \in \mathfrak{M} \\]
   1. a ring \\(\mathfrak{M} \\) is called a \\(\sigma\\)-ring if \\[\mathop{\bigcup}_{n=1}^{\infty}A\_n \in \mathfrak{M} \\]  
      whenever \\(A\_n \in \mathfrak{M} ,\quad n=1,2,3,...\\)
2. set function
   1. define additivity, countable additivity
      - `rearrange theorem`
   2. for the countably additive, nonnegative set function over a ring \\(\varepsilon\\), we can easily define the notion of convergence \\[\phi(A\_n)\rightarrow\phi(A)\\] if \\(A=\bigcup\_{i=1}^\infty A\_n\\) (reduced to the convergence of series)

#### Construction of the Lebesgue Measure
1. interval \\(I\\) in \\(R^p\\) : \\[a\_i \leq b\_i,\\ i=1,...,p,\\ \\ a\_i,b\_i\in R\\]
2. `elementary set` - union of a finite # of intervals
3. \\(\varepsilon\\) : family of all elementary subsets of \\(R^p\\)  
    \\(\varepsilon\\) is a ring, but not a \\(\sigma\\)-ring \\[\bigcup\_{i=1}^\infty [i, i+1] \notin \varepsilon\\]
4. define \\[m(I) = \prod\_{i=1}^{p}(b\_i-a\_i)\\]
    1. \\(m\\) is additive on \\(\varepsilon\\)
5. define `regular` set function - assumption : nonnegative, additive.

now we have,  
> Every regular set function on \\(\varepsilon\\) can be extended to a countably additive set function on a \\(\sigma\\)-ring which contains \\(\varepsilon\\)

1. defining \\(\mu^\* \\) :
   Consider countable covering of any set \\(E\subset R^p\\) by open elementary set \\(A\_n\\)  
   \\[E \subset \bigcup\_{i=1}^\infty A\_n\\]
   define
   \\[\mu^* (E) = \inf\sum\_{n=1}^\infty \mu(A\_n)\\]
   where the inf was taken over the covers composed of open elementary set.
2. Thm 11.8
   - if \\(A\in\varepsilon\\), then \\(\mu^*=\mu\\)
   - \\(\mu^* \\) is `subadditive`
3. for \\(A,B \subset R^p\\) define  
   \\[S(A,B) = (A-B)\bigcup(B-A)\\]
   \\[d(A,B) = \mu^* (S(A,B))\\]
   then we write \\(A\_n\rightarrow A\\) if
   \\[\lim\_{n\rightarrow\infty} d(A,A\_n) = 0\\]
   (we can write the limit of sets(interval) using the limit of real number)
4. Using the distance (indeed) function \\(d(A, B)\\), we can partition the \\(R^p\\) into equivalent classes.  
   In such classes, for every countable set \\(C,D\\) are in the same class as \\(\emptyset\\) and \\(d(C, D)=0\\).


#### Measure
If there is a sequence \\(\\{A_n\\}\\) of elementary sets s.t. \\(A\_n\rightarrow A\\), we say that  
\\(A\\) is __finitely__ \\(\mu-\\)__measurable__ and write \\(A\in\mathfrak{M} \_F(\mu)\\)

If \\(A\\) _is the union of a countable collection of finitely_ \\(\mu-\\)__measurable sets__,  
we say that \\(A\\) is \\(\mu-\\)__measureable__ and write \\(A\in\mathfrak{M} (\mu)\\)

> Thm (Rudin) 11.10 : \\(\mathfrak{M} (\mu)\\) is a \\(\sigma\\)-ring, and \\(\mu^* \\) is countably additive on \\(\mathfrak{M} (\mu)\\).

- thus, \\(\mu\\) which originally only define on \\(\varepsilon\\), is extended to a countably additive set function on a \\(\sigma-\\)ring \\(\mathfrak{M} (\mu)\\).
- This extened set function is called a __measure__.
- The special case \\(\mu=m\\) is called the `Lebesgue measure` on \\(R^p\\)
- We say that \\(E\\) is a `Borel set` if \\(E\\) can be obtained by a _countable # of operations__, starting from open set
  - the __operations__ includes union, intersections, or complements.
  - The collection \\(\mathfrak{B} \\) of all Borel sets in \\(R^p\\) is a \\(\sigma-\\)ring (?)
  - in fact it is the smallest \\(\sigma-\\)ring which contains all open sets (?)


### Measure Spaces
Let \\(X\\) is a set, not necessarily a subset of a euclidean space or indeed of any metric space
1. \\(X\\) is said to be a `measure space` if there exist
    - `measurable sets` : \\(\sigma-\\)ring \\(\mathfrak{M}\\) of subsets of \\(X\\)
    - `measure` : non-negative countably additive set function \\(\mu\\) define on \\(\mathfrak{M}\\)
2. If, in addition, \\(X \in \mathfrak{M}\\) (why not a subset? ) then \\(X\\) is said to be a `measurable space`
3. EX)\\[X=R^p,\quad \mathfrak{M} = \text{ the collection of all Lebesgue-measurable subset of }R^p\quad, \mu = \text{Lebesgue measure}\\]

> The essential feature of the theory (Lebesgue measure) ... everything depends only on the countable additivity of a \\(\mu\\) on a \\(\sigma-\\)ring

### Measurable function

Let \\(f : X \mapsto \overline{ \mathbb{R} }\\), \\(X\\) is a measurable space.

The function \\(f\\) is said to be `measurable` if the set 
\\[\\{x \| f(x) > a\\}\\]
is measurable for every real \\(a\\).

일단은 여기까지...복습 좀 하고 오자. 필요하면 ㅡㅡㅋ 킹님갓고