---
layout: post
title:  "Upsampling Images in Deep Learning"
date:   2019-04-07 09:00:05 +0800
categories: deep_learning
use_math: true
tags: deep_learning upsample transposed_convolution convolution bilinear_upsample align_corner
---

### Transposed Convolution
images from the <a href="https://github.com/vdumoulin/conv_arithmetic/blob/master/README.md" target="_blank">link</a>.
<tr>
    <td>
        <img src="{{site.url}}/images/deeplearning/gan/conv.png" width="400">
    </td>
    <td>
        <img src="{{site.url}}/images/deeplearning/gan/transposed_conv.png" width="400">
    </td>
</tr>

`Transposed convolution` (AKA `fractionally-strided convolution` or a `deconvolution`) 
- expand filter of convolution to matrix (to see it as a linear function), then transpose the obtained linear function it to get `transposed convolution`. <a href="https://towardsdatascience.com/up-sampling-with-transposed-convolution-9ae4f2df52d0" target="_blank">(refer to the excellent article here!)</a>

### Transposed convolution as the gradient of convolution operation
From the <a href="https://pytorch.org/docs/stable/nn.html#convtranspose2d" target="_blank">link</a>,
> ConvTranspose2d - This module can be seen as the __gradient of Conv2d with respect to its input__

To explain,
1. Remember that the gradient are transpose of derivative, and deriv of \\(R^M\mapsto R^N\\) is \\(M\times N\\) matrix (add inner from the blog?). 
2. By expanding the filers and inputs, we can view the __convoluton as the linear mapping__.  
EX) in the above image, convolution is an linear function that maps \\(R^\{16\}\\) to \\(R^4\\), which is practicatlly a \\(4\times 16\\) matrix.  
Its derivative is \\(4\times 16\\) matrix, thus its gradient is \\(16\times 4\\) matrix. This matrix can be thought as the transposed convolution.  
Therefore, with stride=1, there exists __1to1 mapping between transposed-convolution and convolution__

### Output_padding
However, __when the stride is not 1, convolution maps several input shape to same output__. For example, 
```python
nn.Conv2d(in_ch=32, out_ch=64, kernel_size=3, stride=2, padding=1)
```
maps `torch.randn(1, 32, 96, 96)` and `torch.randn(1, 32, 95, 95)` to the same output, namely `torch.Size([1, 64, 48, 48])`.  

To resolve such ambiguity, `output_padding` of `torch.nn.ConvTranspose2d` adds zero padding to the output.

1. when `tconv = nn.ConvTranspose2d(64, 32, kernel_size=3, stride=2, padding=1, output_padding=0,`
```python
inp = torch.randn(1, 64, 48, 48)
print(tconv(inp).size())
```
yields `torch.Size([1, 32, 95, 95])`
2. when `tconv = nn.ConvTranspose2d(64, 32, kernel_size=3, stride=2, padding=1, output_padding=1,`
```python
inp = torch.randn(1, 64, 48, 48)
print(tconv(inp).size())
```
yields `torch.Size([1, 32, 96, 96])`


### Checkerboard Artifact of Transposed Convolution
<a href="https://distill.pub/2016/deconv-checkerboard/" target="_blank">is well described here</a>.

In practice, for upsampling, it is recommended to use 
1. upsample-conv strategy, or 
2. kerner_size % stride == 0 strategy (4 and 2, for example)

Checkerboard effect of normal convolution
1. Gradient of convolution is the transposed convolution
2. transposed-convolution with stride, where kerner_size % stride == 0 doesnt hold, suffer from the checkerboard effect
3. then, the gradient of it's matching convolution also suffers from the checkerboard effect! (remember that the gradient is multiplied during backpropagation)
4. For example, "SAME" convolution with ksize=3, stride=2 could suffer from it. (utilizing the gradient of specific nodes too much) In the last part of <a href="https://distill.pub/2016/deconv-checkerboard/" target="_blank">the article linked above</a>, such problem indeed occurs with the \\(D\\) of GANs.  
> It’s unclear what the broader implications of these gradient artifacts are. One way to think about them is that some neurons will get many times the gradient of their neighbors, basically arbitrarily. Equivalently, the network will care much more about some pixels in the input than others, for no good reason. Neither of those sounds ideal.

### Bilinear Upsample and Align Corners
<a href="https://discuss.pytorch.org/t/what-we-should-use-align-corners-false/22663/6" target="_blanl">An image from the link</a>, 
<img src="{{site.url}}/images/deeplearning/align_corner.png" width="800">

From below example, we can wee that,
1. `align_corner=True` __for both TF and Pytorch work the same__, as the description in the <a href="https://en.wikipedia.org/wiki/Bilinear_interpolation" target="_blank">Wikipedia</a> or from the <a href="https://darkpgmr.tistory.com/117" target="_blank">Darkprogrammer</a>
2. __`align_corner=False` for Pytorch works same as the opencv.__ Not sure what tf tried to implement with align_corner=False. 

```python
import tensorflow as tf
import numpy as np
import cv2
from pprint import pprint
np.set_printoptions(precision=2)
resize_shape = (8, 8)

a = np.ones((1, 2, 2, 1), dtype=np.float32)
a[0, 0, 0, 0] = -1.0
a[0, 1, 1, 0] = 5.0
pprint(a.reshape(1, 1, 2, 2))
b = tf.constant(a, dtype=tf.float32)
c = tf.image.resize_bilinear(b, resize_shape, align_corners=False)
d = tf.image.resize_bilinear(b, resize_shape, align_corners=True)

with tf.Session() as sess:
    np_c = sess.run(c)
    print("from tensorflow, align_corner=False")
    pprint(np_c[0, :, :, 0], width=200)
    np_d = sess.run(d)
    print("from tensorflow, align_corner=True")
    pprint(np_d[0, :, :, 0], width=100)

print("from opencv")
pprint(cv2.resize(a[0], resize_shape, interpolation=cv2.INTER_LINEAR), width=100)
pprint(cv2.resize(a[0], resize_shape, interpolation=cv2.INTER_LINEAR).shape)
torch.set_printoptions(precision=2)
val = torch.zeros(1, 1, 2, 2).float()
val[0, 0, 0, 0] = -1.0
val[0, 0, 1, 1] = 5.0
pprint(val)
print("from torch, align_corner=False")
pprint(nn.functional.interpolate(val, size=(8, 8), mode='bilinear', align_corners=False).view(1, 8, 8, 1)[0, :, :, 0], width=100)
pprint(nn.functional.interpolate(val, size=(8, 8), mode='bilinear', align_corners=False).view(1, 8, 8, 1)[0, :, :, 0].size())
print("from torch, align_corner=True")
pprint(nn.functional.interpolate(val, size=(8, 8), mode='bilinear', align_corners=True).view(1, 8, 8, 1)[0, :, :, 0], width=100)
pprint(nn.functional.interpolate(val, size=(8, 8), mode='bilinear', align_corners=True).view(1, 8, 8, 1)[0, :, :, 0].size())
```

Result
```python
array([[[[-1.,  1.],
         [ 1.,  5.]]]], dtype=float32)

from tensorflow, align_corner=False
array([[-1.  , -0.5 ,  0.  ,  0.5 ,  1.  ,  1.  ,  1.  ,  1.  ],
       [-0.5 ,  0.12,  0.75,  1.38,  2.  ,  2.  ,  2.  ,  2.  ],
       [ 0.  ,  0.75,  1.5 ,  2.25,  3.  ,  3.  ,  3.  ,  3.  ],
       [ 0.5 ,  1.38,  2.25,  3.12,  4.  ,  4.  ,  4.  ,  4.  ],
       [ 1.  ,  2.  ,  3.  ,  4.  ,  5.  ,  5.  ,  5.  ,  5.  ],
       [ 1.  ,  2.  ,  3.  ,  4.  ,  5.  ,  5.  ,  5.  ,  5.  ],
       [ 1.  ,  2.  ,  3.  ,  4.  ,  5.  ,  5.  ,  5.  ,  5.  ],
       [ 1.  ,  2.  ,  3.  ,  4.  ,  5.  ,  5.  ,  5.  ,  5.  ]],
      dtype=float32)

from tensorflow, align_corner=True
array([[-1.  , -0.71, -0.43, -0.14,  0.14,  0.43,  0.71,  1.  ],
       [-0.71, -0.39, -0.06,  0.27,  0.59,  0.92,  1.24,  1.57],
       [-0.43, -0.06,  0.31,  0.67,  1.04,  1.41,  1.78,  2.14],
       [-0.14,  0.27,  0.67,  1.08,  1.49,  1.9 ,  2.31,  2.71],
       [ 0.14,  0.59,  1.04,  1.49,  1.94,  2.39,  2.84,  3.29],
       [ 0.43,  0.92,  1.41,  1.9 ,  2.39,  2.88,  3.37,  3.86],
       [ 0.71,  1.24,  1.78,  2.31,  2.84,  3.37,  3.9 ,  4.43],
       [ 1.  ,  1.57,  2.14,  2.71,  3.29,  3.86,  4.43,  5.  ]],
      dtype=float32)

from opencv
array([[-1.  , -1.  , -0.75, -0.25,  0.25,  0.75,  1.  ,  1.  ],
       [-1.  , -1.  , -0.75, -0.25,  0.25,  0.75,  1.  ,  1.  ],
       [-0.75, -0.75, -0.47,  0.09,  0.66,  1.22,  1.5 ,  1.5 ],
       [-0.25, -0.25,  0.09,  0.78,  1.47,  2.16,  2.5 ,  2.5 ],
       [ 0.25,  0.25,  0.66,  1.47,  2.28,  3.09,  3.5 ,  3.5 ],
       [ 0.75,  0.75,  1.22,  2.16,  3.09,  4.03,  4.5 ,  4.5 ],
       [ 1.  ,  1.  ,  1.5 ,  2.5 ,  3.5 ,  4.5 ,  5.  ,  5.  ],
       [ 1.  ,  1.  ,  1.5 ,  2.5 ,  3.5 ,  4.5 ,  5.  ,  5.  ]],
      dtype=float32)
(8, 8)

tensor([[[[-1.,  0.],
          [ 0.,  5.]]]])

from torch, align_corner=False
tensor([[-1.00, -1.00, -0.88, -0.62, -0.38, -0.12,  0.00,  0.00],
        [-1.00, -1.00, -0.88, -0.62, -0.38, -0.12,  0.00,  0.00],
        [-0.88, -0.88, -0.69, -0.31,  0.06,  0.44,  0.62,  0.62],
        [-0.62, -0.62, -0.31,  0.31,  0.94,  1.56,  1.88,  1.88],
        [-0.38, -0.38,  0.06,  0.94,  1.81,  2.69,  3.12,  3.12],
        [-0.12, -0.12,  0.44,  1.56,  2.69,  3.81,  4.38,  4.38],
        [ 0.00,  0.00,  0.62,  1.88,  3.12,  4.38,  5.00,  5.00],
        [ 0.00,  0.00,  0.62,  1.88,  3.12,  4.38,  5.00,  5.00]])
torch.Size([8, 8])

from torch, align_corner=True
tensor([[-1.00, -0.86, -0.71, -0.57, -0.43, -0.29, -0.14,  0.00],
        [-0.86, -0.63, -0.41, -0.18,  0.04,  0.27,  0.49,  0.71],
        [-0.71, -0.41, -0.10,  0.20,  0.51,  0.82,  1.12,  1.43],
        [-0.57, -0.18,  0.20,  0.59,  0.98,  1.37,  1.76,  2.14],
        [-0.43,  0.04,  0.51,  0.98,  1.45,  1.92,  2.39,  2.86],
        [-0.29,  0.27,  0.82,  1.37,  1.92,  2.47,  3.02,  3.57],
        [-0.14,  0.49,  1.12,  1.76,  2.39,  3.02,  3.65,  4.29],
        [ 0.00,  0.71,  1.43,  2.14,  2.86,  3.57,  4.29,  5.00]])
torch.Size([8, 8])
```

* You can see in above that, as the <a href="https://github.com/tensorflow/tensorflow/issues/19627" target="_blank">claim here</a>, `align_corner=False` in tensorflow is __not that symmetric__.

* <a href="https://pytorch.org/docs/stable/nn.html#upsample" target="_blank">In the Pytorch document example here</a>, you can see that
  1. with the same scalaing factor, when the input size changed, `align_corner=false` __changes the non-zero values at the top left side__
  2. `align_corner=True` does not change the values with respect to the input size. Not sure this is desirable behavior.

* This article <a href="https://hackernoon.com/how-tensorflows-tf-image-resize-stole-60-days-of-my-life-aba5eb093f35" target="_blank">https://hackernoon.com/how-tensorflows-tf-image-resize-stole-60-days-of-my-life-aba5eb093f35</a>, the author complains that align_corner=false moves the image one pixel, by not aligning corner.

* from <a href="https://www.tensorflow.org/api_docs/python/tf/image/resize_bilinear" target="_blank">`tf.image.resize_bilinear`</a>, 
  * `align_corners`: An optional bool. Defaults to False. If true, the centers of the 4 corner pixels of the input and output tensors are aligned, preserving the values at the corner pixels. Defaults to false


* https://stackoverflow.com/questions/48628736/bilinear-interpolation-implentations-in-tensorflow-and-opencv  
> Commonly (in OpenCV, Matlab, scipy, etc.), pixels are assumed to cover unit areas and what is aligned are the very corners of the top-left and bottom-right pixels. Sampling interval changes to old_size / new_size.  
In Tensorflow, there are two brand new schemes, neither of which matches the one above.  
For align_corners=True, the corner pixel centers are aligned with new sampling interval of (old_size - 1) / (new_size - 1) in-between. For align_corners=False, only the top-left pixel centers are aligned and the rest is sampled with interval old_size / new_size.

<a href="https://github.com/tensorflow/tensorflow/issues/6720" target="_blank">"DeepLab's Four Alignment Rules":</a>
1. Use of odd-sized kernels in all convolution and pooling ops.
2. Use of SAME boundary conditions in all convolution and pooling ops.
3. Use align_corners=True when upsampling feature maps with bilinear interpolation.
4. Use of inputs with height/width equal to a multiple of the output_stride, plus one (for example, when the CNN output stride is 8, use height or width equal to 8 * n + 1, for some n, e.g., image HxW set to 321x513).

https://github.com/tensorflow/tensorflow/issues/19627