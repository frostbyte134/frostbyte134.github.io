---
layout: post
title:  "Characteristic equation of a matrix"
date:   2018-05-09 20:25:00 +0900
categories: linear_algebra
use_math: true
tags: linear_algebra need_revise
---
### (1) Definition
To find the eigenvalues of square matrix \\(A\in R^\{n\times n\}\\), we have to solve\\[Ax=\lambda x\quad\rightarrow\quad(A-\lambda I)x=0.\\]
We have to find \\(\lambda\\)s such that makes the nullspace of \\(A-\lambda I\\) nontrivial, which is equivalent to solving
\\[\textrm\{det\}(A-\lambda I)=0.\\]
We define \\(\Phi_A(\lambda)=\textrm\{det\}(\lambda I-A)\\) as the __characteristic equation__ of \\(A\\).  
Thinking about the formula of determinant, it is clear that \\(\Phi_A(\lambda)\\) is a \\(n\\)th polynomial.  
### (2) Applications
* Similar matrices share characteristic equation (and thus, eigenvalues)  
\\[\textrm\{det\}(P^\{-1\}AP)=(\textrm\{det\}P^\{-1\})(\textrm\{det\}A)(\textrm\{det\}P)=\textrm\{det\}A\\]
* Determinant of \\(A\\) = product of eigenvalues.  
As a \\(n\\)th polynomial, \\[\Phi_A(0)=\textrm\{det\}(A)=\prod_\{i=1\}^\{n\}\lambda\_i\\]
* \\(\textrm\{Tr\}A=\sum\_\{i=1\}^\{n\}\lambda_i\\)