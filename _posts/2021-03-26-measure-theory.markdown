---
layout: post
title:  "Lebesgue Integral, Convergence"
date:   2021-03-26 08:00:05 +0800
categories: math
use_math: true
tags: math analysis probability
---

<a href="https://drive.google.com/file/d/1UhtkZybCemTuTKHIJ4TTFPll92DEJ67L/view?usp=sharing" target="_blank"> Rudin Chap 11</a>


> Chap 11, Principles of Mathematical Analysis, by Walter Rudin

- <a href="https://freshrimpsushi.github.io/posts/probability-in-terms-of-measure-theory/" target="_blank">생새우초밥집, 측도론으로 정의한 확률</a>
  - 리뉴얼하면서 페이지가 많이 사라진듯. 다시 생기면 링크 ㄱㄱ

*************************

(개인적으로?) 르벡 적분의 가장 큰 의의는 __limit operation과 interchangible하다는__ 것에 있음
- Lebesgue's `Dominatec Convergence Theorem`. "지배"당하고 (\\( f\_n \leq g \\)) \\(f\\)로 수렴하는 함수의 수열 \\(\\{f\_n\\}\\)은,
  - \\(f\_n, f\\) 가 르벡 적분가능하며(!) \\(f\_n\\)의 르벡적분이 \\(f\\)의 르벡적분으로 수렴함. 굉장히 편리함

*************************


`Fatou's lemma`
\\[f(x)=\mathop{\text\{liminf\}}\_{n\rightarrow\infty} f\_n(x) \quad\rightarrow\quad \int\_E{f d\mu} \leq \mathop{\text\{liminf\}}\_{n\rightarrow\infty} f\_n d\mu \\]
- 이거하고 DCT보기전에 liminf의 일반적인 성질을 다시 보고 오면 좋음 <a href="https://analysis/2020/12/22/limit-supremum.html" target="_blank">링크</a>

chap 9, 10도 올려야 하는데..너무 귀찮다. 의욕이 없음. 뭔가 잘못 선택한 느낌..


*************************


<img src="{{site.url}}/images/math/analysis/measure/measure.jpg" width="800">

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