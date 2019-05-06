---
layout: post
title:  "Convolution operation in practice"
date:   2018-04-11 20:23:00
categories: deep_learning
use_math: true
tags: deep_learning deep_learning(bengio)
---
<a href="https://www.tensorflow.org/api_docs/python/tf/nn/conv2d" target="_blank">2d convolution in Tensorflow</a>

Recall that <a href="{{site.url}}/deep_learning/2018/03/29/cnn.html" target="_blank">convolution is a linear operation</a> and can thus be described as a matrix multiplication (if we first reshape the input tensor into a flat vector). The matrix involved is a function of the convolution kernel. The matrix is sparse, and each element of the kernel is copied to several elements of the matrix. This view helps us to derive some of the other operation needed to implement a convolutional network.

### (1) Convolution
To describe a convolution, we need 3 components

1. `filter` \\(K_{\textrm{[output channel][input channel][row][column]}}\\)
2. `input` \\(V_{\textrm{[input channel][row][column]}}\\)
3. `output` \\(Z_{\textrm{[output channel][row][column]}}\\)  
(output channel = type of filter. Note that each index can be a vector in \\(\Re^n\\))  
(Notice that, filter/input/output row/columns possibly have different sizes)

Then, \\(Z_{i,j,k}\\) can be described by \\(V, K\\) as follows \\[Z_{i,j,k}=\sum_{l,m,n}{V_{l,j+(m-1),k+(n-1)}K_{i,l,m,n}}\\]
where \\(m, n\\) are iterated over the size of filter, starting with 1.

| ![angle]({{ site.url }}/images/deeplearning/6zX2c.png){: .center-image }| 
|:--:| 
| Pic of a single channel. Image from <a href="http://jeanvitor.com/convolution-parallel-algorithm-python/" target="_blank">http://jeanvitor.com/convolution-parallel-algorithm-python/</a> |


And with the stride \\(s\\), \\[Z_{i,j,k}=c(K,V,s)=\sum_{l,m,n}{V_{l,m+s(j-1),n+s(k-1)}K_{i,l,m,n}}\tag{1}\\]



### (2) Zero padding
Without the zero padding, the width of the output shrinks by one pixel less (1st convolution) than the kernel width. 3 special cases of the zero-padding are worth mentioning. If \\(m\\) is the width of image and \\(k\\) is the width of the filter, than

1. No zero padding (`valid convolution` in MATLAB)  
Width of \\(V\\) is \\(m-k+1\\)
2. Zero padded to satisfy output width = input width (`same convolution` in MATLAB)  
Width of \\(V\\) is \\(m\\)
3. Zero padded to guaranteed that every pixel in image is included in the convolution \\(k\\) times in each direction Width of \\(V\\) is \\(m+2(k-1)\\) (`full convolution` in MATLAB)

In this case, the output pixels near the border are a function of fewer pixels than the output pixels near the center - This can make it difficult to learn a single kernel that performs well at all positions in the convolutional feature map.

Usually the __optimal amount of zero padding (in terms of test set classification accuracy) lies somewhere between__ `valid` __and__ `same` __convolution.__



### (3) Derivatives of convolution, in B-prop
Remember the above notation
1. `filter` \\(K_{\textrm{[output channel][input channel][row][column]}}\\)
2. `input` \\(V_{\textrm{[input channel][row][column]}}\\)
3. `output` \\(Z_{\textrm{[output channel][row][column]}}\\)   

(Notice that, filter/input/output row/columns possibly have different sizes)

Suppose we want to minimizer \\(J(V,K)\\). During the backpropagation, we'll receive a tensor \\(G\\) such that \\[G_{i,j,k}=\frac{\partial}{\partial{Z_{i,j,k}}}{J(V,K)} \\]

1. To compute the derivative w.r.t one component of kernel \\(K_{i,l,p,q}\\) (parameter of current layer), \\[\frac{\partial}{\partial{K_{i,l,p,q}}}{J(V,K)}=\sum_{m,n}{\frac{\partial}{\partial{Z_{i,m,n}}}}J(V,K){\frac{\partial}{\partial K_{i,l,p,q}}Z_{i,m,n}}\\] 
	1. An \\(i\\)th filter (kernel) generates \\(i\\)th output channel \\(Z\_\{i,\*,\*\}\\), and during the process a corresponding filter compoment \\(K_{i,l,p,q}\\) contributes to the entire output channel by multiplication (with an input component for each output channel).  
	Thus we have to iterate over the row \\(m\\)/col \\(n\\) __of the output__.
	2. In order to calculate \\(\frac{\partial}{\partial K_{i,l,p,q}}Z_{i,m,n}\\), we need to review (1) to figure out which component of input is multiplied with \\(K_{i,l,p,q}\\) while generating \\(Z\_\{i,m,n\}\\). Since
	\\[Z_{i,m,n}=\sum_{l,p,q}{V_{l,p+s(m-1),q+s(n-1)}K_{i,l,p,q}}\\]
	we see that by fixing \\(p,q\\),
	\\[=\sum_{m,n}{\frac{\partial}{\partial{Z_{i,m,n}}}{J(V,K)}V_{l,p+s(m-1),q+s(n-1)}}\\] 
2. To compute the derivative w.r.t input \\(V_{i,j,k}\\) (for further step of Bprop), \\[\frac{\partial}{\partial{V_{i,j,k}}}{J(V,K)}=\sum_{\substack{l,m \\ \textrm{s.t.} \\ (l-1)s+m=j}}\sum_{\substack\{k,p \\ \textrm{s.t.} \\ (n-1)s+p=k\}}\sum_{q}K_{q,i,m,p}{\frac{\partial}{\partial{Z_{q,l,n}}}{J(V,K)}}\\] (input \\(V_{i,j,k}\\) is multiplied by kernels \\(K_{q,i,m,p}\\) contributing to \\(Z_{q,l,n}\\) s.t. satisfying conditions \\(j=(l-1)s+m,\\>k=(n-1)s+p\\), through all output channels \\(q\\). We have to sum them up.



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
