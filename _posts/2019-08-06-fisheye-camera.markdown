---
layout: post
title:  "Fisheye Camera Model"
date:   2019-08-06 10:04:00 +0900
categories: coding
use_math: true
tags: geometry
---

TODO:
-  K_1 and K_2 (radial lense disortion) 정리 https://darkpgmr.tistory.com/31
- Pinhole camera model과의 alignemnt. 이책임님 말씀으론 Zoom 머시기를 쓰면 된다고 하는데 안나오네. 안되진 않을듯


* <a href="https://www.isprs.org/proceedings/XXXVI/5-W8/Paper/PanoWS_Berlin2005_Schwalbe.pdf" target="_blank">[1] https://www.isprs.org/proceedings/XXXVI/5-W8/Paper/PanoWS_Berlin2005_Schwalbe.pdf</a>

### Central projection model (Pinhole camera)


<img src="{{site.url}}/images/math/geometry/central_proj.png" width="400">  
(img from [1])

* `angle of incidence`: 만나서 이루는 각
* angle of incidence of the ray from an object point, is equal to the angle between the ray and the optical axis within the image space
* At an opening angle of 180 degrees (red line), an object point’s ray with an incidence angle of 90 degree would be projected onto the image plane at infinite distance to the principle point


### Fisheye projection

<img src="{{site.url}}/images/math/geometry/fish_proj.png" width="400">  
(img from [1])


* in the ideal case the distance between an image point and the principle point is __linearly dependent__ (ratio matches) on the angle of incidence of the ray from the corresponding object point

Suppose we have 
* \\(x\_c, y\_c, z\_c\\), object point coordinates in camera origin which are obtained by rotation and translation in (perspective coordinates)

For a 180 degree fisheye lens, and obj point's ray with an angle of icidence of 90 degree is projected onto the outer border of the circular fisheye image, which gives us following ratio
\\[\frac\{\alpha\}\{r\}=\frac\{90\deg\}\{R\}=\frac\{\pi / 2\}\{R\},\quad r=\sqrt\{x\_\{\text\{img\}\}^2 + y\_\{\text\{img\}\}^2\}\quad\rightarrow\quad y\_\{\text\{img\}\}=r^2-x\_\{\text\{img\}\}^2\\]
where
* \\(\alpha\\): angle of incidence
* \\(r\\): dist between img point and optical axis (principal point)
* \\(R\\): img radius (of fisheye camera)
* \\(x\_\{\text\{img\}\}, y\_\{\text\{img\}\}\\): img coordinates (from the principal point)

As in pinhole model, the ratio between \\(x\_\{\text\{img\}\}\, y\_\{\text\{img\}\}\\) follows the ratio between \\(x\_\{\text\{c\}\}, y\_\{\text\{c\}\}\\), as the following figure


<img src="{{site.url}}/images/math/geometry/geo_rel.png" width="500">  
(img from [1])

\\[\rightarrow\quad \frac\{x\_\{\text\{img\}\}\}\{y\_\{\text\{img\}\}\}=\frac\{x\_\{\text\{c\}\}\}\{y\_\{\text\{c\}\}\}\\]
Now,
\\[x\_\{\text\{img\}\}=\frac\{x\_\{\text\{c\}\}\}\{y\_\{\text\{c\}\}\}y\_\{\text\{img\}\},\quad r=\frac\{\alpha\}\{\pi / 2\}R\\]
\\[x\_\{\text\{img\}\}=\frac\{x\_\{\text\{c\}\}\}\{y\_\{\text\{c\}\}\}\sqrt\{r^2-x\_\{\text\{img\}\}^2\} \\]
\\[x\_\{\text\{img\}\}^2= \left(\frac\{x\_\{\text\{c\}\}\}\{y\_\{\text\{c\}\}\}\right)^2(r^2-x\_\{\text\{img\}\}^2)\\]
\\[x\_\{\text\{img\}\} = \frac\{r\}\{\frac\{y\_\{\text\{img\}\}\}\{x\_\{\text\{img\}\}\} \sqrt\{ \left(\frac\{x\_\{\text\{c\}\}\}\{y\_\{\text\{c\}\}\}\right)^2 + 1 \} \}\\]
\\[=\frac\{R \frac\{  \text\{atan\} \left( \sqrt\{ \frac\{x\_\text\{c\}^2 +  y\_\text\{c\}^2\}\{z\_\{\text\{c\}\} \}\}\right)
     \}\{\pi / 2\} \}\{\frac\{y\_\{\text\{img\}\}\}\{x\_\{\text\{img\}\}\} \sqrt\{ \left(\frac\{x\_\{\text\{c\}\}\}\{y\_\{\text\{c\}\}\}\right)^2 + 1 \}\}\\]
where
\\[\alpha = \text\{atan\} \left( \sqrt\{ \frac\{x\_\text\{c\}^2 +  y\_\text\{c\}^2\}\{z\_\{\text\{c\}\} \}\}\right)\\]

miscs
* https://kr.mathworks.com/help/vision/ug/fisheye-calibration-basics.html
* https://kr.mathworks.com/help/vision/ref/estimatefisheyeparameters.html
