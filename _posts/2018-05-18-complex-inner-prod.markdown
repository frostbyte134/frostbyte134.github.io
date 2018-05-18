---
layout: post
title:  "Complex inner product and Euclidean space"
date:   2018-05-18 15:02:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra analysis need_revise
---

<h3 id="hermit_inner_prod">Definition: Complex (Hermitian) inner product</h3>
On a complex vector space \\(V\\), to each pair of vectors \\(\textbf\{u, v, w\}\\) and \\(c\in \mathbb\{P\}\\), let \\(\langle u,v\rangle\\) be a function that satisfies the following axioms.
{:.deccounter}
1. \\(\langle \textbf\{u,v\}\rangle=\overline\{\langle \textbf\{v,u\}\rangle\}\\).
2. `Bilinearity`: \\(\langle \textbf\{u+v,w\}\rangle=\langle \textbf\{u,w\}\rangle+\langle \textbf\{v,w\}\rangle\\) and \\(\langle \textbf\{u,v+w\}\rangle=\langle \textbf\{u,v\}\rangle+\langle \textbf\{u,w\}\rangle\\).
3. \\(\langle c\textbf\{u,v\}\rangle=\bar\{c\}\langle \textbf\{u,v\}\rangle=\\) and \\(\langle \textbf\{u\},c\textbf\{v\}\rangle=c\langle \textbf\{u,v\}\rangle=\\).
4. \\(\langle \textbf\{u,u\}\rangle\\) is a nonnegative real number, and \\(\langle \textbf\{u,u\}\rangle = 0\\) iif \\(\textbf\{u\}=0\\).
{:.deccounter}

__Side note__:  
Hermitian inner product is not symmetric, namely
\\[\langle \textbf\{u,v\}\rangle=\overline\{\langle \textbf\{v,u\}\rangle\}\\]
However the defintion of `norm` remains clear, since \\(\\|u\\|:=\sqrt\{\langle \textbf\{u,u\}\rangle\}\\) 

### Euclidean space
definition, Cauchy-Somewhaltz, etc...asdmasdk 


Link:
<a href="http://www.math.umd.edu/~hking/Hermitian.pdf" target="_blank">http://www.math.umd.edu/~hking/Hermitian.pdf</a>  
