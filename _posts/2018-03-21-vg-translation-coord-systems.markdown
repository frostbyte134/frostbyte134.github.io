---
layout: post
title:  "Vision geometry - translation between different coordinate sysems"
date:   2019-07-27 10:58:00  +0800
categories: geometry
use_math: true
tags: geometry cv
---

- concatenated several posts, in 19.07.28

### 1. World coordinate system
Relative coordinate based on an arbitrary fixed point.

### 2. Camera coordinate system
* camera's focus point = origin  
* same unit (meter / cm / ...) as the world coordinate system
* <a href="{{site.url}}/geometry/2018/10/23/rot-trans-coord.html" target="_blank">translation between world coordinate system <-> object coordinate system </a>


### 3. Image coordinate system (pixel coordinate)
unit = pixel   
![이미지좌표계]({{ site.url }}/images/math/geometry/image_coord_sys.png)  

### 4. Normalized image coordinate system
- virtual plane for convenience (projection of all 3d points to a plane where `focal length` = 1)

* removed the effects of (camera) intrinsic parameters (<a href = "http://darkpgmr.tistory.com/77" target="_blank">__link__</a>) from Image coordinate system  
* unit 1 (1 pixel) away fromt he camera focus point.  
* `Origin` (=`principal point`): intersection with z-axis of camera coordinate system and the plane  
        = projection of the focus point into the normalized image plane

| ![핀홀투영]({{ site.url }}/images/math/geometry/pinhole_projection.png)| 
|:--:| 
| Image from [1] |

  

### Camera projection 
\\[ z_c 
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

### 1. World coordinate to camera coordinate
- using `extrinsic matrix` \\( \begin{bmatrix} R & T \end{bmatrix} \\) (Rotation and Translation)

\\[ \begin{bmatrix}   &   &  &  \\\ & R \in {\Re}^{3 \times 3} & & T \in {\Re}^{3 \times 1} \\\   & & & \\\ 0 & 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} x_w \\\ y_w \\\ z_w \\\ 1 \end{bmatrix} = \begin{bmatrix} x_c \\\ y_c \\\ z_c \\\ 1 \end{bmatrix} \\]

* Firstly we rotate \\( x_w, y_w, z_w \\) with \\( R \\), 
* then translate the whole plane with \\(T\\). __We cannot translate the points directly before we align the coordinates__.
* <a href = "{{site.url}}//geometry/2018/10/23/rot-trans-coord.html" target="_blank"> __ Rotation in 3D - link! __</a>

Note that, \\( T \\) __is the position of the origin of the world coordinate in camera-coordinate.__

![3]({{ site.url }}/images/math/geometry/rel_coord.png){: .center-image } 

If order to represent (x, y) with the camera plane, we need to add T (vector addition!).

### 2. camera coordinate to normalized img plane
- perspective transform (projection)

\\[\begin{bmatrix} x_c \\\ y_c \\\ z_c \end{bmatrix}\quad\rightarrow\quad z_c\begin{bmatrix} x_c/z_c \\\ y_c/z_c \\\ 1 \end{bmatrix} \\]

The coefficient \\(z_c\\) in the RHS of the main equation came from here

### 3. normalized img plane to img plane
- using `intrinsic matrix` 
  \\[K = \begin{bmatrix}   f\_x &  skew_cf\_x & c\_x \\\  & f\_y  & c\_y \\\   & & 1 \\\ \end{bmatrix},\\] \\[ z_c 
\begin{bmatrix}
u\\\ v \\\ 1 
\end{bmatrix} 
= \begin{bmatrix}   f\_x &  skew_cf\_x & c\_x \\\  & f\_y  & c\_y \\\   & & 1 \\\ \end{bmatrix} \begin{bmatrix} x_c/z_c \\\ y_c/z_c \\\ 1 \end{bmatrix}
\\]

`Intrinsic parameters`
1. focal length (in pixels, normally) \\(f\_x, f\_y\\)  
   * Since 1 pixel in img __corresponds exactly to a__ 1 img sensor (CCD), 
\\[f\_x \text\{(pixels)\} = \frac\{\text\{distance between lense center and principal point (in cm / mm) \}\}\{\text\{length of an image sensor in img x direction (in cm / mm)\}\}\\]
    * __if we halve the resolution with the same camera, then the focal length is also halved__  
      \\(\rightarrow\\) since the length and height of the img sensor size, which is mapped to 1 pixel, gets twice bigger
    * By the multiplication \\[f\_x \times \frac\{x_c\}\{z_c\}\\] we see obtain the __image of the (projection of all 3d points to normalized img plane)__ in the image plane (where the camera sensors are located)
2. coordinates of principal point \\(c\_x, c\_y\\)
    * why we add them - (0, 0) must go to (\\(c\_x, c\_y\\)), (\\(-c\_x, -c\_y\\)) must go to \\(0, 0).

References:  
[1] <a href="https://kr.mathworks.com/help/vision/ug/camera-calibration.html?s_tid=gn_loc_drop" target="_blank">https://kr.mathworks.com/help/vision/ug/camera-calibration.html?s_tid=gn_loc_drop</a>




[2] <a href = "http://darkpgmr.tistory.com/77" target="_blank">http://darkpgmr.tistory.com/77</a>