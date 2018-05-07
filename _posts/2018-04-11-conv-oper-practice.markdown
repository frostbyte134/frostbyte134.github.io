---
layout: post
title:  "Convolution operation in practice"
date:   2018-04-11 20:23:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---
<a href="https://www.tensorflow.org/api_docs/python/tf/nn/conv2d" target="_blank">2d convolution in Tensorflow</a>

Recall that <a href="{{site.url}}/deep_learning/2018/03/29/cnn.html">convolution is a linear operation</a> and can thus be described as a matrix multiplication (if we first reshape the input tensor into a flat vector). The matrix involved is a function of the convolution kernel. The matrix is sparse, and each element of the kernel is copied to several elements of the matrix. This view helps us to derive some of the other operation needed to implement a convolutional network.

### (1) Convolution
To describe a convolution, we need 3 components

1. `filter` \\(K_{\textrm{[output channel][input channel][row][column]}}\\)
2. `input` \\(V_{\textrm{[input channel][row][column]}}\\)
3. `output` \\(Z_{\textrm{[output channel][row][column]}}\\)  
(output channel = type of filter. Note that each index can be a vector in \\(\Re^n\\))

Then, \\(Z_{i,j,k}\\) can be described by \\(V, K\\) as follows \\[Z_{i,j,k}=\sum_{l,m,n}{V_{l,m+(j-1),n+(k-1)}K_{i,l,m,n}}\\]


| ![angle]({{ site.url }}/images/deeplearning/6zX2c.png){: .center-image }| 
|:--:| 
| Image from <a href="http://jeanvitor.com/convolution-parallel-algorithm-python/" target="_blank">http://jeanvitor.com/convolution-parallel-algorithm-python/</a> |


And with the stride \\(s\\), \\[Z_{i,j,k}=c(K,V,s)=\sum_{l,m,n}{V_{l,m+s(j-1),n+s(k-1)}K_{i,l,m,n}}\tag{1}\\]



### (2) Zero padding
Without the zero padding, the width of the output shrinks by one pixel less (1st convolution) than the kernel width. 3 special cases of the zero-padding are worth mentioning.

1. No zero padding (`valid convolution` in MATLAB)  
Width of \\(V\\) is \\(m-k+1\\)
2. Zero padded to satisfy output width = input width (`same convolution` in MATLAB)  
Width of \\(V\\) is \\(m\\)
3. Zero padded to guaranteed that every pixel in image is included in the convolution \\(k\\) times in each direction Width of \\(V\\) is \\(m+2(k-1)\\) (`full convolution` in MATLAB)

In this case, the output pixels near the border are a function of fewer pixels than the output pixels near the center - This can make it difficult to learn a single kernel that performs well at all positions in the convolutional feature map.

Usually the __optimal amount of zero padding (in terms of test set classification accuracy) lies somewhere between__ `valid` __and__ `same` __convolution.__



### (3) Derivatives of convolution, in B-prop
Suppose we want to minimizer \\(J(V,K)\\). During the backpropagation, we'll receive a tensor \\(G\\) such that \\[G_{i,j,k}=\frac{\partial}{\partial{Z_{i,j,k}}}{J(V,K)} \\]

1. To compute the derivative w.r.t one component of kernel \\(K_{i,j,k,l}\\) (parameter of current layer), \\[\frac{\partial}{\partial{K_{i,j,k,l}}}{J(V,K)}=\sum_{m,n}{\frac{\partial}{\partial{Z_{i,m,n}}}{J(V,K)}}{\frac{\partial}{\partial K_{i,j,k,l}}Z_{i,m,n}}\\] (for fixed index of output channel \\(i\\), we have to iterate over image) \\[=\sum_{m,n}{\frac{\partial}{\partial{Z_{i,m,n}}{J(V,K)}}V_{j,(m-1)s+k,(n-1)s+l}}\\] (refer to (1) for the relations between indices)
2. To compute the derivative w.r.t input \\(V_{i,j,k}\\) (for further step of Bprop), \\[\frac{\partial}{\partial{V_{i,j,k}}}{J(V,K)}=\sum_{\substack{l,m \\ \textrm{s.t.} \\ (l-1)s+m=j}}\sum_{\substack{n,p \\ \textrm{s.t.} \\ (n-1)s+p=k}}\sum_{q}K_{q,i,m,p}{\frac{\partial}{\partial{Z_{q,l,n}}}{J(V,K)}}\\] (input \\(V_{i,j,k}\\) is multiplied by kernels satisfying above conditions, through all output channels (filters))



* We also generally add some bias term to each output before applying the nonlinearity.
* For locally connected layers, it is common to give each unit its own bias.
* For convolutional layers, it is typical to have one bias per channel of the output and share it across all locations within each convolutional map. (what bout its deriv?)


<hr>
<br/><br/>
Next:  
Training autoencoders (skipped, for now)
<br/><br/>
References:  
<a href="http://www.deeplearningbook.org/" target="_blank">http://www.deeplearningbook.org/</a>
<a href="http://jeanvitor.com/convolution-parallel-algorithm-python/" target="_blank">http://jeanvitor.com/convolution-parallel-algorithm-python/</a>
