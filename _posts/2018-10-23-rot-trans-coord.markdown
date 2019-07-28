---
layout: post
title:  "Linear Transformation Between Coordiante Systems (3D)"
date:   2018-10-23 5:00:05 +0800
categories: geometry
use_math: true
tags: geometry rotatation
---

<img src="{{ site.url }}/images/math/rot.png" class="center" style="width:500px"/>  

### Rotation in 2D
Suppose that we want to perform \\(\text\{ccw\}(\theta)\\): counter-clock direction rotation, in the amount of theta.
\\[
\begin{bmatrix}\{\}
1 \\\
0 \\\
\end\{bmatrix\}
\quad\rightarrow\quad
\begin{bmatrix}\{\}
\cos\theta \\\
\sin\theta \\\
\end\{bmatrix\}
\\]
\\[
\begin{bmatrix}\{\}
0 \\\
1 \\\
\end\{bmatrix\}
\quad\rightarrow\quad
\begin{bmatrix}\{\}
-\sin\theta \\\
\cos\theta \\\
\end\{bmatrix\}
\\]
\\[\rightarrow
\begin{bmatrix}\{\}
\cos\theta && -\sin\theta \\\
\sin\theta && \cos\theta \\\
\end\{bmatrix\}
\\]

### Rotation in 3D
A __rotation of 3D body from (certain) standard__ can be described as a series (which is strict in order) of 2d transformations, in 3 axis
1. Yawing: movement along \\(z\\)-axis  
\\(\rightarrow\\) rotation in \\(x, y\\) plane, ignoring \\(z\\) coordinate.  
The matrix representing such rotation is, \\[R_x:=
\begin{bmatrix}\{\}
\cos\theta && -\sin\theta && 0\\\
\sin\theta && \cos\theta && 0\\\
0 && 0 && 1 \\\
\end\{bmatrix\}
\\]
(See how the transformation affects points)

\\[\text\{Rotation mat in 3D = \} R\_\{yaw\}R\_\{pitch\}R\_\{roll\}(\text\{standard\})\\]

### Coordinate Rotation (회전 - Rigid 좌표 변환)

Suppose that we are given a rotation matrix of of an object (That is, we have a world coordinate system and an object coordinate system, and have the rotation matrix of the object). Generally the direction is counter-clock wise (in each yaw, pitch and roll).  
To simplify the problem, we consider a rotation of coordinate system in 2D (__yawing__ \\(\text\{ccw\}(\theta)\\), for instance).  
<img src="{{ site.url }}/images/math/rot.png" class="center" style="width:500px"/>  
Note that, \\[\text\{Rotating the axis(object) ccw\}(\theta)\\]is equivalent to\\[\text\{Rotating the whole points cw\}(\theta)\\]
Yawing is given as the rotation of the object.  
Thus, to represent (a point \\(p\\) in the world coordinate) with the target(camera) coordinate , which rotated in the amount of \\(\text\{ccw\}(\theta)\\) in yawing,  
we have to rotate all points toward \\(\text\{cw\}(\theta)\\).

Notice that, if \\(R_\{yaw\}\\) is a rotation matrix representing \\(\text\{ccw\}(\theta)\\), then its inverse transformation is its transpose \\(R_\{yaw\}^T\\), representing \\(\text\{cw\}(\theta)\\).  
\\[\text\{ccw\}(\theta)=R_\{yaw\},\quad\quad \text\{cw\}(\theta)=R_\{yaw\}^T\\]
Then above statement can be represented as,
\\[[\text\{target coord\}]=R_\{yaw\}^T[\text\{world coord\}]\\]
and in reverse,
\\[[\text\{world coord\}]=R_\{yaw\}[\text\{target coord\}]\\]

__BUT__ note that this only holds in 2D case. (In 3d, the inverse of rotation matrix is not its transpose)

Next:  

<a href="http://planning.cs.uiuc.edu/node102.html" target="_blank">http://planning.cs.uiuc.edu/node102.html</a>