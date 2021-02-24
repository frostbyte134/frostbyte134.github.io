---
layout: post
title:  "Sequence and Series of Functions"
date:   2021-02-23 08:00:05 +0800
categories: analysis
use_math: true
tags: analysis differentiation limit derivative
---

- <a href="https://drive.google.com/file/d/1J2bh2PE_0Kd_aWN5tqgHdeJzrE6IU_Dg/view?usp=sharing" target="_blank">rudin Chap7 Sequences and Series of Functions</a>

### Interchangiblity (?) of limits

1. Consider \\(\\{f\_n\\}\\), a sequence of functions defined on \\(E\\).
2. Suppose that the sequence of numbers \\(\\{f\_n(x)\\}\\) converges \\(\forall x\in E\\) (`pointwise convergence`!)  

We can then __define a function__ \\(f\\) by
\\[f(x) = \lim\_{n\rightarrow\infty}f\_n(x)\quad (x\in E) \tag{1}\\] 

When \\(f\_n\\) are (continuous, differentiable, or integrable), what can we say about \\(f\\)? __will it be continuous?__

Continuity of \\(f\\) is equivalent to
\\[\lim\_{t\rightarrow x}f(t) = f(x) \\]
\\[\lim\_{t\rightarrow x}\lim\_{n\rightarrow\infty}f\_n(t) = \lim\_{n\rightarrow\infty}f\_n(x) \tag{by the def of f} \\]
\\[\lim\_{t\rightarrow x}\lim\_{n\rightarrow\infty}f\_n(t) = \lim\_{n\rightarrow\infty}\lim\_{t\rightarrow x}f\_n(t)\tag{by the continuity of f\_n }\\]

so that, it is __equlvalent to asking that the limits can be interchanged.__
- in general this is not true
- it holds when \\(f\_n\rightarrow f\\) `uniformly` (we can remove \\(x\\) from the definition. one \\(N\in \mathbb{N}\\) will do for a \\(\epsilon > 0\\)) 
- converse (when the limits can be interchanged, \\(f\_n\rightarrow f\\) uniformly?) holds when \\(E\\) is compact
- __basically__, we first does not use the continuity. Instead we only use limits. The proof goes as
  - let \\(x\\) be a limit point of \\(E\\)
  - define \\(A_n = \lim\_{t\rightarrow x}f\_n(t)\\  )
  - If \\(f\_n\rightarrow f\\) uniformly, then we can prove that 
    \\[\lim\_{t\rightarrow x}f(t) = \lim\_{n\rightarrow\infty}A\_n\\]
    which is equivalent to
    \\[\lim\_{t\rightarrow x}\lim\_{n\rightarrow\infty}f\_n(t) = \lim\_{n\rightarrow \infty}\lim\_{t\rightarrow x} f\_n(t)\\]
    If we add the continuity here \\(\left(\lim\_{t\rightarrow x}f\_n(t) = f\_n(x),\quad \lim\_{t\rightarrow x}f(t) = f(x) \right)\\), we obtain the first theorem


