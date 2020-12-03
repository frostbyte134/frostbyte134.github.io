---
layout: post
title:  "Kantorovish-Rubinstein Duality"
date:   2019-03-21 09:00:05 +0800
categories: optimization
use_math: true
tags: deep_learning gan linear_programming duality optimization
---

is a duality of the EMD (Wasserstein-1).

TODO
* add link to the strong duality of the linear programming (either using linalg or from the convex)


### Discrete case

Given two discrete random variables \\(X\\) and \\(Y\\) which __shares \\(K\\) state__ \\(\\{x\_1,...,x\_K\\}\\), consider their distribution \\[p\_r(x\_i):=p(X=x\_i)\quad p\_\theta(x\_j):=p(Y=x\_j)\\]

`Wasserstein-1` distance, or `Earch Mover's distance` (EM-distance) is defined by
\\[\text\{EMD\}(p\_r,p\_\theta)=\inf\_\{\gamma\in\Pi\} \|\| x\_i - x\_j \|\| \gamma(x\_i,x\_j) = \text\{EMD\}(p\_r,p\_\theta)=\inf\_\{\gamma\in\Pi\} E\_\{(x\_i,x\_j)\sim\gamma\}\|\| x\_i - x\_j\|\| \\]
where \\(\Pi\\) represents all joint distribution over the \\(X, Y\\) such that the marginals are \\(p\_r\\) and \\(p\_\theta\\).


We can also set \\(\Gamma=\gamma(x\_i,x\_j)\in \Re^\{K\times K\}\\) and \\(D=\|\| x\_i - x\_j\|\|\in \Re^\{K\times K\}\\), so that
\\[\text\{EMD\}(p\_r,p\_\theta)=\inf\_\{\gamma\in\Pi\}\langle D,\Gamma \rangle\_F\\]
where \\(\langle , \rangle\_F\\) denotes the Frobenious inner product.

Above can be solved using __linear programming__. The problem becomes
\\[\text\{minimize\}\quad c^Tx\\]
\\[\text\{s.t.\}\quad Ax=b\\]
\\[\quad\quad -x\leq 0\\]
where
\\[x:=\text\{vec\}(\pi)\in \Re^\{K\times K\} \\]
\\[c:=\text\{vec\}(\|\| x\_i - x\_j \|\|)\in \Re^\{K\times K\} \\]
\\[A:=
\begin{bmatrix}{}
	1 & 1 & 1 & ... & 0 & 0 & 0 & ...\cr
	0 & 0 & 0 & ... & 1 & 1 & 1 & ...\cr
	\vdots \cr
    1 & 0 & 0 & ... & 1 & 0 & 0 & ... \cr
    0 & 1 & 0 & ... & 0 & 1 & 0 & ... \cr
    \vdots \cr
\end{bmatrix} \in R^\{2\times K\}
\\]
\\[b:=
\begin{bmatrix}{}
	p\_r \cr
	p\_\theta \cr
\end{bmatrix} \in R^\{2\times K\}
\\]

The Lagrangian becomes
\\[\mathcal{L}(\lambda, \nu) = \inf \left\\{ \_\{x\} c^Tx + (b-Ax)^T\lambda - x^T\nu \right\\}\\]
\\[ = \inf\_\{x\} \left\\{ x^T(c - A^T\lambda - \nu) + b^T\lambda \right\\} \\]
\\[ = 
\begin{cases}
b^T\lambda \quad \text\{if\}\quad c - A^T\lambda - \nu = 0 \cr
-\infty \quad \text\{o.w\} \cr
\end{cases}
\\]

The dual problem now becomes
\\[\text\{maximize\}\quad b^T\lambda\\]
\\[\text\{s.t.\}\quad c - A^T\lambda = \nu\\]
\\[\quad\quad \nu \geq 0\\]

The two constraint can be joind into one
\\[A^Ty \leq c\\]
so that the dual problem becomes
\\[\text\{maximize\}\quad b^T\lambda\\]
\\[\text\{s.t.\}\quad A^Ty \leq c\\]

Now, knowing that the strong duality holds (TODO: add link!), we can solve this dual.

Given the related variables, consider the dual variable \\(\lambda\\) as the realization of two discrete functions \\(f, g\\) over the states \\(\\{x\_1,...,x\_K\\}\\)
\\[
\begin{bmatrix}{}
	f(x\_1) \cr
	\vdots \cr
    f(x\_K) \cr
    g(x\_1) \cr
    \vdots \cr
    g(x\_K) \cr
\end{bmatrix} \in R^\{2\times K\}
\\]

Now for \\(i=j\\),
\\[f(x\_i\)+g(x\_i)\leq \|\|x\_i - x\_i\|\| = 0 \quad\land\quad g(x\_i\)+f(x\_i)\leq \|\|x\_i - x\_i\|\| = 0\\]
\\[\rightarrow 0 \leq f(x\_i\)+g(x\_i)\leq 0\\]
so that \\(f(x\_i)=-g(x\_i)\\) holds.

Now for \\(i\neq j\\),
\\[f(x\_i\)-f(x\_j)\leq \|\|x\_i - x\_j\|\| \quad\land\quad f(x\_j\)-f(x\_i) \leq \|\|x\_i - x\_j\|\| \\]
\\[\rightarrow -\|\|x\_i - x\_j\|\| \leq f(x\_i\)-f(x\_j)\leq \|\|x\_i - x\_j\|\|\\]

which holds for 1-Lipschitz functions
\\[\|\| f(x\_i)-f(x\_j) \|\| \leq \|\|x\_i - x\_j\|\| \\]

Thus the dual problem becomes
\\[\sup\_\{\|\| f\|\|\_\{L\leq 1\}\} \left\\{ E\_\{x\sim p\_r\}f(x) - E\_\{x\sim p\_\theta\}f(x) \right\\} \\]

reference: <a href="https://vincentherrmann.github.io/blog/wasserstein/" target="_blank">https://vincentherrmann.github.io/blog/wasserstein/</a>