---
layout: post
title:  "Deep Feedfoward Network"
date:   2018-03-25 14:38:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio) cnn
---
= `Multilayer Percepron` (MLP)

>The goal of feedfoward network is to approximate a function \\(f^*\\)

It defines `a mapping` \\(y=f(x;\theta)\\), and learns the value of parameter \\(\theta\\) that results in the best approximation of \\(f^*\\).
- __No feedback connection__, hence the name.

<h3 id="linear_to_ffn">From linear model to feedfoward network</h3>
To extend linear models \\(\textbf{y}=\textbf{x}^Tw\\) to represent nonlinear function, we can apply the linear model not to \\(\textbf{x}\\), but its transformed input \\(\phi(\textbf{x})\\), where \\(\phi\\) is a nonliear transformation.

We can think of \\(\phi\\) as providing a set of __feature representation of__ \\(\textbf{x}\\).

The question is then, how to choose a mapping \\(\phi\\).

1. Very generic \\(\phi\\)  
- ex) `RBF`. If \\(\phi(\textbf{x})\\) is of high enough dimension, we can always fit the training set, but often generalization is poor.  
- Usually based only on the principle of local smoothness and do not encode enough prior information to solve advanced problems.

2. Manually engineering \\(\phi\\)  
was dominant before the advent of deep learning.

3. To learn \\(\phi\\)  
Now, we have a model \\[\textbf{y}=f(\textbf{x};\theta,w)={\phi(\textbf{x};\theta)}^Tw.\\]Then we now have  
-1. parameters \\(\theta\\) we use to learn \\(\phi\\) from a broad class of functions  
-2. parameters \\(w\\) that maps \\(\phi(\textbf{x}_i)\\) to \\(\textbf{y}_i\\) for each \\(\textbf{x}_i, \textbf{y}_i\\) in traning set.  

- Here, \\(\phi\\) defines the hidden layer. We can be highly generic as 1, by using very broad family of \\(\phi\\).  
- Like 2., we can encode priors in \\(\phi(\textbf{x};\theta)\\) to help generalization.
- The general principle of __improving models by learning features__ extends beyond the feedfoward networks described in this chapter. It is a recurring theme of deep learning that applies to all the kinds of models.


Next: <a href="{{site.url}}/deep_learning/2018/03/25/mle-neg-log-likelihood.html" target="_blank">MLE and Negative log-likelihood, in Deep Learning Context</a>  


References:
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>
