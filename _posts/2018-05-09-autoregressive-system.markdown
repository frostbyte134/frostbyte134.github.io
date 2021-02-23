---
layout: post
title:  "Autoregressive systems"
date:   2018-05-09 19:19:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra
---
### (1) Multiple variable, single time step
\\[
\begin{bmatrix}{}
	x_1(t)  \cr
	\vdots  \cr
	x_n(t)  \cr
\end{bmatrix}
=
\begin{bmatrix}{}
	& & \cr
	& A & \cr
	& & \cr
\end{bmatrix}
\begin{bmatrix}{}
	x_1(t-1)  \cr
	\vdots  \cr
	x_n(t-1)  \cr
\end{bmatrix}
\\]

### (2) Single variable, multiple time step
\\[
\begin{bmatrix}{}
	x(t)  \cr
	\vdots  \cr
	x(t-r)  \cr
\end{bmatrix}
=
\begin{bmatrix}{}
	a & b & c \cr
	1 & 0 & 0 \cr
	0 & 1 & 0 \cr
\end{bmatrix}
\begin{bmatrix}{}
	x(t-1)  \cr
	\vdots  \cr
	x(t-r-1)  \cr
\end{bmatrix}
\\]

### (3) Multiple variable, multiple time step
\\(x(t):=(x_1(t),..., x_n(t)),\\>x(t)=A_1x(t-1)+...+A_tx(t-t),\\>A_i\in R^\{n\times n\}\\)
\\[
\begin{bmatrix}{}
	x(t)  \cr
	\vdots  \cr
	\vdots  \cr
	x(t-r)  \cr
\end{bmatrix}
=
\left[
	\begin{array}{c|c|c|c}
	A_1 & A_2 & ... & A_r \cr
	\hline
	I & ... & ... & 0 \cr
	\hline
	& & & \cr
	\hline
	0 & ... & I & 0 \cr
	\end{array}
\right]
\begin{bmatrix}{}
	x(t-1)  \cr
	\vdots  \cr
	\vdots  \cr
	x(t-1-r)  \cr
\end{bmatrix}
\\]
