---
layout: post
title:  "Dimension of a set and span"
date:   2018-05-10 11:05:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra analysis
---

<h3 id="rudin92">Theorem: Rudin 9.2</h3>
Let \\(r\\) be a positive integer. If a vector space \\(X\\) is spanned by a set of \\(r\\) vectors (not yet independent), then \\[\textrm\{dim\}⁡X\leq r.\\]


Proof: If this is false, there is a vector space \\(X\\) which   
__contains__ an independent set \\(Q=\\{y_1,…,y_\{r+1\}\\}\\) (since its dimension must be larger than \\(r\\) and   
__spanned__ by a set \\(S_0=\\{x_1,…,x_r \\}\\) consisting of \\(r\\) vectors.  
Suppose \\(0\leq i\leq r\\) and suppose a set \\(S_i\\) has been constructed, which __spans__ \\(X\\) 
and which consists of all \\(y_j\\) with \\(1\leq j \leq i\\) plus a certain collection of \\(r-i\\) members of \\(S_0\\),
 say \\(x_1,…,x_\{r-i\}\\).
\\[S_i=\{y_1,…,y_i,x_1,…,x_\{r-i\} \},|S_i |=r\\>\\>∀i\\]
(In other words, \\(S_i\\) is obtained from \\(S_0\\) by replacing \\(i\\) of its elements by members of \\(Q\\), 
without altering the span – starting from \\(i=0\\) this is obvious).  
Since \\(S_i\\) spans \\(X,\\>y_\{i+1\}\\) is the span of \\(S_i\\); 
hence there are scalars \\(a_1,…,a_\{i+1\},\\>b_1,…,b_\{r-i\}\\) with \\(a_\{i+1\}=1\\), such that
\\[\sum\_\{j=1\}^\{i+1\}a\_j\textbf{y}\_j + \sum\_\{k=1\}^\{r-1\}b\_k\textbf\{x\}\_k=0.\\]
If all \\(b_k\\)s were 0, then the independence of \\(Q\\) (assumption) force all \\(a_j\\)s to be 0, a contradiction.
It follows that some \\(x_k\in S_i\\) is a linear combination of the other members of \\(T_i=S_i\cup y_\{i+1\}\\). 
Remove this \\(x_k\\) from \\(T_i\\) and call the remaining set \\(S\_\{i+1\}\\). Then \\(S\_\{i+1\}\\) spans the same set as \\(T_i\\), namely \\(X\\), so that \\(S\_\{i+1\}\\) has the properties postulated for \\(S\_i\\) with \\(i+1\\) in place of \\(i\\).  

Starting with \\(S_0\\), we thus construct sets \\(S_1,…,S_r\\). The last of these consists of \\(y_1,…,y_r\\), and our construction shows that it spans \\(X\\). But \\(Q\\) is independent; hence \\(y\_\{i+1\}\\) is not in the span of \\(S_r\\). This contradiction establishes the theorem.
  
___Corollary___
\\[\textrm\{dim⁡ \}R^n=n\\]
Proof	Since \\(\\{e_1,…,e_n \\}\\) spans \\(R^n\\), the theorem shows that \\(\textrm\{dim\}R^n \leq n\\). Since \\(\\{e_1,…,e_n \\}\\) is independent and \\(\\{e_1,…,e_n \\}\in R^n\\), \\(\textrm\{dim\}R^n\geq n\\).

### Theorem: Rudin 9.3
Suppose \\(X\\) is a vector space, and \\(\textrm\{dim⁡X\}=n\\)  
(a) A set \\(E\\) of n vectors in \\(X\\) spans \\(X\\) i.i.f \\(E\\) is independent.  
(b) \\(X\\) has a basis, and every basis consists of \\(n\\) vectors.  
(c) If \\(1\leq r\leq n\\) and \\(\\{y_1,..,y_r \\}\\) is an independent subset of \\(X\\), then \\(X\\) has a basis containing \\(\\{y_1,…,y_r \\}\\).  
  
Proof:  
1. Suppose \\(E=\\{x_1,…,x_n \\}\\). Since \\(\textrm\{dim⁡\}X=n\\), the set \\(\\{x_1,…,x_n,y\\}\\) is dependent for every \\(y\in X\\) (by the <a href="{{site.url}}/linear_algebra/2018/04/19/vector-space.html" target="_blank">definition of the dimension of set</a>). If \\(E\\) is independent, it follows that \\(y\\) is the span of \\(E\\); hence \\(E\\) spans \\(X\\).  
Conversely, if \\(E\\) is dependent, one of its members can be removed without changing the span of E (as in above theorem). Hence \\(E\\) cannot span \\(X\\), by Theorem 9.2. This proves (a).  
2. Since \\(\textrm\{dim⁡\}X=n,\\>X\\) contains an independent set of \\(n\\) vectors, and (a) shows that every such a set is a basis of X; (b) now follows from <a href="{{site.url}}/linear_algebra/2018/04/19/vector-space.html" target="_blank">9.1(d)</a> \\(\left(\textrm\{dim\}⁡X\geq n\right)\\) and 9.2 \\(\left(\textrm\{dim\}⁡X\leq n\right)\\).
3. To prove (c), let \\(\\{x_1,…,x_n \\}\\) be a basis of \\(X\\). The set
\\(S=\\{y_1,…,y_r,x_1,…,x_n \\}\\) spans \\(X\\) and is dependent, since it contains more than \\(n\\) vectors. The argument used in the proof of <a href="#rudin92">Theorem 9.2</a> shows that one of the \\(x_i\\) (we have full freedom to choose any vector in \\(S\\)) is a linear combination of the other members of \\(S\\), the remaining set still spans \\(X\\). This process can be repeated \\(r\\) times, and leads to a basis of X which contains \\(\\{y_1,…,y_r \\}\\), by (a).