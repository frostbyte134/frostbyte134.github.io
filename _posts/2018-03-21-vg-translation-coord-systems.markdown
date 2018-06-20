---
layout: post
title:  "Vision geometry - translation between different coordinate sysems"
date:   2018-03-21 22:58:00
categories: geometry
use_math: true
tags: geometry cv
---
Translation from world coordinate to the pixel coordinate is, \\[ z_c 
\begin{bmatrix}
u\\\ v \\\ 1 
\end{bmatrix} 
= K 
\begin{bmatrix} R & T 
\end{bmatrix} 
\begin{bmatrix} 
x_w \\\ y_w \\\ z_w \\\ 1 
\end{bmatrix} \\]
![1]({{ site.url }}/images/math/geometry/vline.png){: .center-image }  
![2]({{ site.url }}/images/math/geometry/calibration_cameramodel_coords.png){: .center-image }  

### 1. World-coordinate to camera coordinate, 
using `extrinsic parameters` \\( \begin{bmatrix} R & T \end{bmatrix} \\) (Rotation and Translation)

\\[ \begin{bmatrix}   &   &  &  \\\ & R \in {\Re}^{3 \times 3} & & T \in {\Re}^{3 \times 1} \\\   & & & \\\ 0 & 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} x_w \\\ y_w \\\ z_w \\\ 1 \end{bmatrix} = \begin{bmatrix} x_c \\\ y_c \\\ z_c \\\ 1 \end{bmatrix} \\]

Firstly we rotate \\( x_w, y_w, z_w \\) with \\( R \\), then translate the whole plane with \\(T\\).

Note that, \\( T \\) __is the position of the origin of the world coordinate in camera-coordinate.__

![3]({{ site.url }}/images/math/geometry/rel_coord.png){: .center-image } 

If order to represent (x, y) with the camera plane, we need to add T (vector addition!).


References:  
[1] <a href="https://kr.mathworks.com/help/vision/ug/camera-calibration.html?s_tid=gn_loc_drop" target="_blank">https://kr.mathworks.com/help/vision/ug/camera-calibration.html?s_tid=gn_loc_drop</a>