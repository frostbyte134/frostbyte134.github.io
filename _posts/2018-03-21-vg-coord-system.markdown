---
layout: post
title:  "Vision geometry - Coordinate System"
date:   2018-03-21 08:36:00
categories: geometry
use_math: true
tags: geometry cv
---

### 1. World coordinate system
Relative coordinate based on an arbitrary fixed point.

### 2. Camera coordinate system
camera's focus point = origin  
same unit (meter / cm / ...) as the world coordinate system

### 3. Image coordinate system (pixel coordinate)
unit = pixel   
![이미지좌표계]({{ site.url }}/images/math/geometry/image_coord_sys.png)  

### 4. Normalized image coordinate system
virtual plane for convenience  
removed the effects of (camera) intrinsic parameters (<a href = "http://darkpgmr.tistory.com/77" target="_blank">__link__</a>) from Image coordinate system  
unit 1 (1 pixel) away fromt he camera focus point.  
`Origin`: intersection with z-axis of camera coordinate system and the plane  
        = projection of the focus point into the normalized image plane

| ![핀홀투영]({{ site.url }}/images/math/geometry/pinhole_projection.png)| 
|:--:| 
| Image from [1] |

Translation between world coordinate to image coordinate: (__link__)


References:  
[1] <a href = "http://darkpgmr.tistory.com/77" target="_blank">http://darkpgmr.tistory.com/77</a>