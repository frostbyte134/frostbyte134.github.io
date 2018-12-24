---
layout: post
title:  "Proof of convergent sequences"
date:   2018-12-24 07:00:05 +0800
categories: analysis
use_math: true
tags: analysis limit sequence bounded subsequence
---

> When \\(0<r<1\\), show that \\(\lim\_\{n\rightarrow\infty\}r^n=0\\)

By defining \\(h:=\frac\{1\}\{r\}-1\\), \\(h>0\\) and \\(r=\frac\{1\}\{1+h\}\\) holds.  
By the `Bernoulli's inequality` (link),l for \\(n\in\mathbb\{N\}\\), 
\\[0<r^n=\frac\{1\}\{(1+h)^n\}\leq \frac\{1\}\{1+nh\}< \frac\{1\}\{nh\}\\]

Using the Sandwich theorem(link!), and the fact that 
\\[\lim\_\{n\rightarrow\infty\}0=0,\quad \lim\_\{n\rightarrow\infty\}\frac\{1\}\{nh\}=0\\]
we see that \\(\\{r^n\\}\\) converges to 0.

<br/>
* (DA): 맛있는 해석학 4판, 김백진

Next:  

