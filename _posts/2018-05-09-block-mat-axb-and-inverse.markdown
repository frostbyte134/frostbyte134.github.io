---
layout: post
title:  "Block representation of Ax=b"
date:   2018-05-09 10:43:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra need_revise
---
In solving \\(Ax=b\\) with elimination, what we perform is converting
\\[Ax-b=0\quad\equiv\quad
\left[
	\begin{array}{c|c}
	A & y \cr	
	\end{array}
\right]
\left[
	\begin{array}{}
	x \cr
	\hline
	-1 \cr
	\end{array}
\right]
=0\\] into
\\[
\left[
	\begin{array}{c|c}
	I & s \cr	
	\end{array}
\right]
\left[
	\begin{array}{}
	x \cr
	\hline
	-1 \cr
	\end{array}
\right]
=0\\]