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
	x_1(t)  \\\
	\vdots  \\\
	x_n(t)  \\\
\end{bmatrix}
=
\begin{bmatrix}{}
	& & \\\
	& A & \\\
	& & \\\
\end{bmatrix}
\begin{bmatrix}{}
	x_1(t-1)  \\\
	\vdots  \\\
	x_n(t-1)  \\\
\end{bmatrix}
\\]

### (2) Single variable, multiple time step
\\[
\begin{bmatrix}{}
	x(t)  \\\
	\vdots  \\\
	x(t-r)  \\\
\end{bmatrix}
=
\begin{bmatrix}{}
	a & b & c \\\
	1 & 0 & 0 \\\
	0 & 1 & 0 \\\
\end{bmatrix}
\begin{bmatrix}{}
	x(t-1)  \\\
	\vdots  \\\
	x(t-r-1)  \\\
\end{bmatrix}
\\]

### (3) Multiple variable, multiple time step
\\(x(t):=(x_1(t),..., x_n(t)),\\>x(t)=A_1x(t-1)+...+A_tx(t-t),\\>A_i\in R^\{n\times n\}\\)
\\[
\begin{bmatrix}{}
	x(t)  \\\
	\vdots  \\\
	\vdots  \\\
	x(t-r)  \\\
\end{bmatrix}
=
\left[
	\begin{array}{c|c|c|c}
	A_1 & A_2 & ... & A_r \\\
	\hline
	I & ... & ... & 0 \\\
	\hline
	& & & \\\
	\hline
	0 & ... & I & 0 \\\
	\end{array}
\right]
\begin{bmatrix}{}
	x(t-1)  \\\
	\vdots  \\\
	\vdots  \\\
	x(t-1-r)  \\\
\end{bmatrix}
\\]
