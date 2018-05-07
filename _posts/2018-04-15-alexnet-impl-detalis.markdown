---
layout: post
title:  "Alexnet implementation details"
date:   2018-04-15 00:52:00
categories: deep_learning
use_math: true
tags: deep_learning 
---

Input: \\(224\times 224\times 3\rightarrow 227\times 227\times 3\\) (zero padded)

### Conv1
* input: \\(227\times 227\times 3\\)
* Kernel \\(11\times 11\times 3\\), stride \\(4\\), VALID, \\(48\times 2\\) filters
 \\(\rightarrow (227-11)/4+1=55\\)
* output: \\(\left(55\times 55\times 48\right)\times 2\\)

### MP1
* input: \\(55\times 55\times 48\times 2\\)
* patch \\(3\times 3\\), stride \\(2\\), VALID
\\(\rightarrow (55-3)/2+1=27\\)
* output: \\(\left(27\times 27\times 48\right)\times 2\\)

### Response_normalization1
* Equation is in the paper


### Conv2

* input: \\(\left(27\times 27\times 48\right)\times 2\\)
* Kernel \\(5\times 5\times 48\\), stride \\(1\\), SAME, \\(128\times 2\\) filters
\\(\rightarrow (27+4-5)+1=27\\)
* output: \\(\left(27\times 27\times 128\right)\times 2\\)

### MP2
* input: \\(\left(27\times 27\times 128\right)\times 2\\)
* patch \\(3\times 3\\), stride \\(2\\), VALID
\\(\rightarrow (27-3)/2+1=13\\)
* output: \\(\left(13\times 13\times 128\right)\times 2\\)

### Response_normalization2
* Equation is in the paper


### Conv3
* input: \\(\left(13\times 13\times 128\right)\times 2 \rightarrow  \left(13\times 13\times 256\right)\\)
* Kernel \\(3\times 3\times 256\\), stride \\(1\\), SAME, \\(192\times 2\\) filters
\\(\rightarrow (13+2-3)+1=13\\)
* output: \\(\left(13\times 13\times 192\right)\times 2\\)


### Conv4
* input: \\(\left(13\times 13\times 192\right)\times 2\\)
* Kernel \\(3\times 3\times 192\\), stride \\(1\\), SAME, \\(192\times 2\\) filters
\\(\rightarrow (13+2-3)+1=13\\)
* output: \\(\left(13\times 13\times 192\right)\times 2\\)


### Conv5
* input: \\(\left(13\times 13\times 192\right)\times 2\\)
* Kernel \\(3\times 3\times 192\\), stride \\(1\\), SAME, \\(128\times 2\\) filters
\\(\rightarrow (13+2-3)+1=13\\)
* output: \\(\left(13\times 13\times 128\right)\times 2\\)


### MP3

* input: \\(\left(13\times 13\times 128\right)\times 2\\)
* patch \\(3\times 3\\), stride \\(2\\), VALID
\\(\rightarrow (13-3)/2+1=6\\)
* output: \\(\left(6\times 6\times 128\right)\times 2\\)


### FC1

* input: \\(\left(6\times 6\times 128\right)\times 2=9216\\)
\\((9216)\times(9216\times 4096)+(4096)\\)
* output: \\(4096\\)


### FC2
* input: \\(4096\\)
\\((4096)\times(4096\times 4096)+(4096)\\)
* output: \\(4096\\)


### FC3

* input: \\(4096\\)
\\((4096)\times(4096\times 1000)+(1000)\\)
* output: \\(1000\\)

<br/><br/>
Next:  
<br/><br/>
References:  
<a href="https://papers.nips.cc/paper/4824-imagenet-classification-with-deep-convolutional-neural-networks.pdf/" target="_blank">https://papers.nips.cc/paper/4824-imagenet-classification-with-deep-convolutional-neural-networks.pdf</a>
<a href="https://github.com/nailbrainz/tensorflow/blob/master/alexnet_implementation.ipynb" target="_blank">https://github.com/nailbrainz/tensorflow/blob/master/alexnet_implementation.ipynb</a>

