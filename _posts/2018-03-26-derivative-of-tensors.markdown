---
layout: post
title:  "Derivatives of Tensors (In Deep learning context)"
date:   2018-03-26 20:59:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---
>Derivatives are a way to measure rate of change.



### (1) Scalar in, Scalar out
For \\(f : \Re\mapsto\Re\\), the derivative of f at a point \\(x\in\Re\\) is a scalar \\(a\in \Re\\) which satisfies\\[ f'(x)=\lim_{h\to0}\frac{f(x+h)-f(x)-ah}{h}=0,  f'(x)\in\Re\\]
- For \\(y=f(x)\\), the `chain rule` tells us that \\[\frac{\partial z}{\partial x} =\frac{\partial z}{\partial y}\frac{\partial y}{\partial x}\\]with scalar product.

- `Linear approximation` gives \\[ f(x+h)\approx f(x)+f'(x)h \\] where f'(x)h is a scalar product.



### (2) Gradient: vector in, scalar out
 For \\(f : \Re^N\mapsto\Re\\), the derivative of f at a point \\(\textbf{x}\in\Re^N\\) is now a vector \\(A\in \Re^N\\) which satisfies \\[ \bigtriangledown_{x}f(x)=\lim_{\|h\|\to0}\frac{f(x+h)-f(x)-Ah}{\|h\|}, f'(x)\in\Re\\] (is it right to use \\(\|\|\\) here?)

- For \\(f:\Re^N\to\Re, g:\Re\to\Re, y=f(x),z=g(y)=g(f(x))\\) the `chain rule` extends as \\[\frac{\partial z}{\partial x} =\frac{\partial z}{\partial y}\frac{\partial y}{\partial x}\\] with scalar-vector multiplication.

- `Linear approximation` gives \\[ f(x+h)\approx f(x)+f'(x)\cdot h \\] (Remember that, dot product \\(\cdot\\) is elementary-wise multiplication, which makes sense as a rate of change for each elementary unit vector)



### (3) Jacobian: vector in, vector out
 For \\(f : \Re^N\mapsto\Re^M\\), the derivative of f at a point \\(\textbf{x}\in\Re^N\\) is now a matrix \\(A\in\Re^{M\times N}\\), which satisfies

\\[ \lim_{\|h\|\to0}\frac{\|f(x+h)-f(x)-Ah\|}{\|h\|}=0\\] Such matrix \\(A=\frac{\partial f(x)}{\partial y} \\) is called a Jacobian.

- For \\(f:\Re^N\to\Re^M, g:\Re^M\to\Re^K, y=f(x),z=g(y)=g(f(x))\\) the `chain rule` extends as \\[\frac{\partial z}{\partial x} =\frac{\partial z}{\partial y}\frac{\partial y}{\partial x}\\] with matrix multiplication \\((K\times N)=(K \times M)\times(M \times N)\\).

- `Linear approximation` now becomes \\[ f(x+h)\approx f(x)+\frac{\partial f(x)}{\partial y}h \\] where \\(h, \frac{\partial f(x)}{\partial y}\\) are matrices (matrix multiplication).



<h3 id="gen_jacob_deriv">(4) Generalized Jacobian: tensor in, tensor out!</h3>
A `tensor` is a D-dimensional grid of numbers.

Suppose now \\(f : \Re^{N_1\times\cdot\cdot\cdot\times N_{D_x}}\mapsto\Re^{M_1\times\cdot\cdot\cdot\times M_{D_y}} \\). If \\(y=f(x)\\) then \\(\frac{\partial y}{\partial x}\\) is a generalized Jacobian, which is a tensor with shape \\[(M_1\times\cdot\cdot\cdot\times M_{D_y})\times(N_1\times\cdot\cdot\cdot\times N_{D_x})\\] Note that we separated the variables in 2 groups. 1st group is for \\(y\\), and 2nd group is for \\(x\\).

Now if \\(i\in\mathbb{Z}^{D_y}, j\in\mathbb{Z}^{D_x}\\) be vectors of integer indices. Then \\[ \left(\frac{\partial y}{\partial x}\right)_{i,j}=\frac{\partial y_i}{\partial x_j} \in \Re \\] Note that \\(y_i,x_j\\), and \\(\left(\frac{\partial y}{\partial x}\right)\\) are all scalars, thanks to the vector indices.

Using this notation, we can perform multiplication between two tensors like multiplication of two matrices.

- For \\(g:\Re^{N_1\times\cdot\cdot\cdot\times N_{D_y}}\to\Re^{N_1\times\cdot\cdot\cdot\times N_{D_z}}, y=f(x),z=g(y)=g(f(x))\\) the `chain rule` extends as \\[\frac{\partial z}{\partial x} =\frac{\partial z}{\partial y}\frac{\partial y}{\partial x}\\] with generalized matrix-matrix muliply (dot product between tensors) \\[ ({N_1\times\cdot\cdot\cdot\times N_{D_z}}) \times({N_1\times\cdot\cdot\cdot\times N_{D_x}}) = \\]\\[ ({N_1\times\cdot\cdot\cdot\times N_{D_z}}) \times ({N_1\times\cdot\cdot\cdot\times N_{D_y}}) \times \\]\\[ ({N_1\times\cdot\cdot\cdot\times N_{D_y}}) \times ({N_1\times\cdot\cdot\cdot\times N_{D_x}}).\\] Indeed it __resembles the dot product:__ \\[ \left( \frac{\partial z}{\partial x} \right)\_{i,j} = \sum_k \left( \frac{\partial z}{\partial y} \right)\_{i,k} \left( \frac{\partial y}{\partial x} \right)\_{k,j} =  \left( \frac{\partial z}{\partial y} \right)\_{i,:}\cdot \left( \frac{\partial y}{\partial x} \right)\_{:,j}\\]

- `Linear approximation` now becomes \\[ f(x+h)\approx f(x)+\frac{\partial f(x)}{\partial y}h \\] where \\(\frac{\partial f(x)}{\partial y}h\\) is generalized matrix-vector multiply \\[ ({N_1\times\cdot\cdot\cdot\times N_{D_y}}) \times({N_1\times\cdot\cdot\cdot\times N_{D_x}}) = \\]\\[ ({N_1\times\cdot\cdot\cdot\times N_{D_y}}) \times ({N_1\times\cdot\cdot\cdot\times N_{D_x}}) \times \\]\\[ ({N_1\times\cdot\cdot\cdot\times N_{D_x}}).\\] Generally, the __generalized Jacobians are too big to be fit into memory.__ We explicitly calculate the closed form by hand.
<hr>
<br/><br/>
Next:
<br/><br/>
References:  
<a href="http://cs231n.stanford.edu/handouts/derivatives.pdf" target="_blank">http://cs231n.stanford.edu/handouts/derivatives.pdf</a>  
<a href = "http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>  