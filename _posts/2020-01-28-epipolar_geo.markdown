---
layout: post
title:  "Epipolar Geometry"
date:   2020-01-28 09:00:05 +0800
categories: math
use_math: true
tags: geometry camera epipolar math projection
---

<a href="https://web.stanford.edu/class/cs231a/course_notes/03-epipolar-geometry.pdf" target="_blank">https://web.stanford.edu/class/cs231a/course_notes/03-epipolar-geometry.pdf</a>

Preliminaries
* <a href="{{site.url}}/geometry/2018/10/23/rot-trans-coord.html" target="_blank">Linear transformation between cooridnate systems</a>
* <a href="{{site.url}}/geometry/2019/07/27/pinhole-camera-model.html" target="_blank">Pinhole camera model</a>
* <a href="{{site.url}}/coding/2019/08/06/fisheye-camera.html" target="_blank">Fisheye camera model</a>

<img src="{{site.url}}/images/math/geometry/epipolar_intro.png" width="800">


TODO:
* degree of freedom - singularity of matrix?

Let
1. \\(P\\) : a point in real world
2. \\(O\_1, O\_2\\) : origin of each camera. World coordinate \\(\equiv\\) CAM1 for convenience, and we have \\(R, T\\).
   1. Supposing that \\(K\_1, K\_2\\) are the `intrinsic` matrices, the `camera projection matrix` will be
   2. \\[M\_1=K\_1[I\\ 0]\quad\quad M\_2=K\_2[R\ T]\tag\{1\}\\]
   3. Above means that \\([R\ T][\text{world point\}] = [\text{cam2 point\}]\\). Since we perform the rotation first, \\(T\\) must be the location of CAM1 in the CAM2 coordinate, and \\(R\\) is the rotation which transforms CAM2 axis to CAM1 axis.
3. \\(p\_1, p\_2\\) : 3d points in each `image plane`, in CAM1, CAM2 coordinate (\\(z\_i\\) will be the `focal length`)
4. `epipolar plane` : plane defined by \\(P, O\_1, O\_2\\).
5. `baseline` : line connecting \\(O\_1, O\_2\\)
6. `epipole` : intersection between `baseline` and `image plane`
    * Given the \\(P, O\_i, K\\), we can specify the epipole 
7. `epipolar line` : a line from \\(p\_i\\) to respective epipole.


### Essential matrix
- linear constraint between \\(p\_1, p\_2\\) which containst the \\(R, T\\).

#### Canonical camera
- Let \\(K\_1=K\_2=I\\) (canonical camera setting). Then now we have camera matrix (1) as \\[M\_1=[I\ 0]\quad\quad M\_2=[R\ T]\\]
1. The location of \\(p\_2\\) in the CAM1 coordinates will be
\\[p\_2=Rx+T\\]
\\[R^Tp\_2-R^TT=x\\]
2. The location of \\(2T\\) (remember that \\(T\\) is the location of CAM1 in CAM2 coordinate. Thus \\(2T\\) is also in the epipolar plane) in the CAM1 coordinate will be
\\[2T=Rx+T\\]
\\[R^TT=x\\]
3. Both points lie in the epipolar plane. To get the normal of the epipolar plane, we perform <a href="{{site.url}}/analysis/2018/04/03/vector-projection.html" target="_blank">outer product</a>
\\[R^TT\times (R^Tp\_1-R^TT)\\]
\\[R^TT\times R^Tp\_1\\]
\\[R^T(T\times p\_1)\tag\{2\}\\]
4. From the linear algebra, we can represen cross prod between two vector as matrix-vector multiplication
\\[a\times b=
\begin\{bmatrix\}\{\}
0 & -a\_x & a\_y\\\
a\_z& 0 & -a\_x\\\
-a\_y& a\_x & 0\\\
\end\{bmatrix\}
=[a\_x]b\\]
5. Using this notation, and the fact that (2) is the unit vector of epipolar plane, we obtain linear equality
\\[R^T([T\_x]p\_2)^Tp\\]
\\[([T\_x]p\_2)^TRp\\]
\\[p\_2^{T}([T\_x])^TRp\tag\{3\}\\]
The matrix
\\[E=[T\_x]R\\]
is known as the __Essential matrix__, creating a compact expression for the epipolar constraint:
\\[p\_2^TEp\_1=0\\]

#### The Fundamental matrix
If the camera is not canonical, then 
\\[p=Kp\_c\\]
\\[K^\{-1\}p=p\_c\\]
holds, so that the equation (3) becomes
\\[p\_2^{T}K\_2^\{-T\}([T\_x])^TRK\_1^\{-1\}p\tag\{3\}\\]
and we call the matrix \\(K\_2^\{-T\}([T\_x])^TRK\_1^\{-1\}\\) as the __Fundamental matrix__.

Finding fundamental matrix - SVD or QR-decomposition  
Notice that, the linear constraints is free to scale, so we can fix F(2, 2)=1 and we have 8 degrees of freedom - need 8 points (essential matix = 5 degrees and singular)