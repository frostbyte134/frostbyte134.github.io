---
layout: post
title:  "Vector, Dimension and Coordinate" 
date:   2018-04-19 22:41:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---

### Theorem 9.1
- Definitions  
1.	A nonempty set \\(\textbf\{X\}\subset R^n\\) is a `vector space` if \\(\textbf{x\}+\textbf\{y\}\in \textbf\{X\}\\) and \\(c\textbf\{x\}\in \textbf\{X\}\\) for all \\(\textbf\{x,y\}\in \textbf\{X\}\\), and for all scalars \\(c\\).
2.	If \\(\textbf\{x\}_1,…,\textbf\{x\}_k\in R^n\\) and \\(c_1,…,c_n\\) are scalars, the vector
\\[c_1\textbf\{x\}_1+...+c_k\textbf\{x\}_k\\]
is called a linear combination of \\(\textbf\{x\}_1,…,\textbf\{x\}_1\\).  
If \\(S\subset R^n\\) and if \\(E\\) is the set of all linear combinations of elements of \\(S\\), we say that \\(S\\) `spans` \\(E\\).  
>Observe that every span is a vector space.
3. A set consisting of vectors \\(\textbf\{x\}_1,…,\textbf\{x\}_k\\) (we shall use the notation \\(\{\textbf\{x\}_1,…,\textbf\{x\}_k\}\\) for such a set) is said to be `independent` 
if the relation  \\(c_1\textbf\{x\}_1+...+c_k\textbf\{x\}_k=0\\) implies \\(c_1=...=c_k=0\\).  
Observe that no independent set contains the null vector (we can put any scalar \\(c_i\\) in front of that null vector)
4. If a vector space \\(X\\) contains an independent set of r vectors but contains no independent set of r+1 vectors,  
we say that \\(X\\) has `dimension` \\(r\\), and write \\(\textrm\{dim\}⁡X=r\\).  
>Dimension of a set = maximum number of independent vectors
>The set consisting of 0 alone is a vectors space; its dimension is 0.
5. An __independent subset__ of a vector space \\(X\\) which spans \\(X\\) is called a `basis` of \\(X\\).
Theorem: If a set is spanned by \\(r\\) vectors, then \\(\textrm\{dim\}X\leq r.\\)  
Observe that if \\(B=\\{x_1,…,x_k\\}\\) is a basis of \\(X\\), then every \\(\textbf\{x\}\in X\\) 
has a unique representation of the form \\(\textbf\{x\}=\sum c_j\textbf\{x\}_j\\).  
Such representation exists since \\(B\\) spans \\(X\\), 
and it is unique since B is independent (if not, subtracting each representation gives contradiction).
The numbers \\(c_1,…c_r\\) are called the `coordinates` of \\(\textbf\{x\}\\) with respect to the basis \\(B\\).  
Ex) the set \\(\\{e_1,…,e_n\\}\\), where \\(e_j\\) is the vector in \\(R^n\\) whose \\(j\\)th coordinate is 1 and whose other coordinates are all 0.
We shall call it the `standard basis` of \\(R^n\\).


<h3 id="coord">(2) Basis, and representation of a vector (coordinate system).</h3>

Generally we use n-dimensional tuple \\((a_1,...,a_n)\\) to represent a single vector in the space. This implicitly assumes the usage of standard basis \\((e_1 ,..., e_n)\\).

However, we can represent such vector with __any__ n-basis \\((b_1,...,b_n)\\). The new coordinate system satisfy above condition, thus forms a new vector space.

* There must be (indeed, since both basis matrices are nonsingular) bijective transformation between any two different coordinate systems. There is no preference (ranking?) among the coordinate systems. \\[\textrm{vector = [basis][coordinate]}\\]\\[\vec{v\}=Xc\\]

* During the course of linear algebra, we are mainly interested in the properties and concepts (<a href="{{site.url}}/linear_algebra/2018/05/14/similarity-transform.html" target="_blank">invertibility, eigenvalues,</a> rank, ...) which __does not rely on these coordinate systems__.

* __There is no concepts of "angle", "rotation", "length", etc. in a vector space.__ Such concepts are defined with `inner product` operation between vectors, and is called an Euclidean space (link).

* The <a href="{{site.url}}/linear_algebra/2018/04/21/mat-and-linear-transform.html" target="_blank">concept of diagonal matrix is dependent on the choice of coordinate system.</a>  
Namely, an linear mapping \\(\vec{y}=f(\vec{x})\\) is represented as \\(y=Dx\\) with a diagonal matrix \\(D\\), but is represented as \\(y'=Ax'\\) with an ordinary matrix \\(A\\) in another coordinate system. In the former system calculation gets prettier, and we need to figure out how we can find such a good basis.

* However, __the concept of Identity matrices / zero matrices are defined independently from the choice of coordinate system.__  
Indeed, identity matrix corresponds to a linear mapping \\(f\\) where \\(f(\vec{x})=x\\), and zero matrices corresponds to a linear mapping \\(f\\) where \\(f(\vec{x})=0\\).
