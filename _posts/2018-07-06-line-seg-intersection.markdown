---
layout: post
title:  "Intersection between two lines and segments (in 2D)"
date:   2018-07-06 18:23:00 +0900
categories: geometry
use_math: true
tags: geometry need_revise
---

Throughout this page, we assume that a line \\(l_i\\) is composed of two points \\(l_i.p_1,\\>l_i.p_2\\) such that \\[l\_i.p\_1 \leq l\_i.p\_2\\] holds. (Note that \\(\leq\\) is not an generalized inequality(link??). It is just an element(scalar)wise comparison.)


### (1) No need for intersecting point

![hmm]({{ site.url }}/images/math/geometry/Line+segment+intersection.jpg)  

(Note that, \\(\textrm\{ccw\}(a,b,c)=(b-a)\times(c-a)\\))

Plus, we need to handle exception case, where \\(l_1\\) and \\(l_2\\) are in a same line. If they are in a same line, no matter they intersect or not they pass above test with value 0.

If \\(l\_1\\) and \\(l\_2\\) are in a same line, then \\[\textrm{ccw}(l\_1.p\_1,\\>l\_1.p\_2,\\> l\_2.p\_1)=0\quad  \textrm{and}\quad  \textrm{ccw}(l\_2.p\_1,\\>l\_2.p\_2,\\>l\_1.p\_1) = 0\\] holds. (<a href="{{site.url}}/geometry/2018/04/20/ccw.html" target="_blank">Recap - ccw function</a>)  
If they are parallel, we need to test 2 conditions.

1. \\(l1.p2 \leq l2.p1\quad\rightarrow\quad l\_1.p_1\\) - \\(l\_2.p_1\\) - \\(l\_1.p_2\\) - \\(l\_2.p_2\\)
2. \\(l2.p2 \leq l1.p1\quad\rightarrow\quad l\_2.p_1\\) - \\(l\_1.p_1\\) - \\(l\_2.p_2\\) - \\(l\_1.p_2\\)

if any of above holds, then the two segment intersects. Notice that if any of terms are 0 and the other is negative, then the segments meet at a point.
```java
typedef pair<double, double> vec2;
bool isIntersect(vec2 l1, vec2 l2, vec2 r1, vec2 r2){ //assumption of the top of the page applied 
	double f = cprod({ r2.first - r1.first, r2.second - r1.second }, { l1.first - r1.first, l1.second - r1.second }) *
		cprod({ r2.first - r1.first, r2.second - r1.second }, { l2.first - r1.first, l2.second - r1.second });
	double s = cprod({ l1.first - l2.first, l1.second - l2.second }, { r1.first - l2.first, r1.second - l2.second }) *
		cprod({ l1.first - l2.first, l1.second - l2.second }, { r2.first - l2.first, r2.second - l2.second });
	if (f > 0 || s > 0)return false;
	if (f == 0 && s == 0){
		if (l2 < r1 || r2 < l1)return false;
		else return true;
	}
	return true;
}
```

Note that above test can be applied between (point, line). B/C of this, to find out whether two objects (line, line) or (point, line) are above is better than determinant=0. 

### (2) Need an intersection point
1. lines  
Let us temporarily define a line as \\(\textbf\{a\}+p\textbf\{b\}\\), where \\(\textbf\{a\}\\) is a point \\(\textbf\{b\}\\) is a and a direction vector. We want to find a intersection between two lines \\(\textbf\{a\}+p\textbf\{b\}\\), \\(\textbf\{c\}+q\textbf\{d\}\\).  
We have to solve linear equations
\\[a_x+pb_x=c_x+qd_x\\]
\\[a_y+pb_y=c_y+qd_y.\\]
1st equation gives
\\[q=\frac\{(a_x-c_x)+pb_x\}\{d_x\}\\]
so that
\\[a_y+pb_y=c_y+\frac\{(a_x-c_x)+pb_x\}\{d_x\}d_y\\]
\\[(b_y-\frac\{b_xd_y\}\{d_x\})p=(c_y-a_y)+\frac\{(a_x-c_x)d_y\}\{d_x\}\\]
\\[(b_yd_x-b_xd_y)p=(c_y-a_y)d_x+(a_x-c_x)d_y\\]
\\[p=\frac\{(c_y-a_y)d_x+(a_x-c_x)d_y\}\{(b_yd_x-b_xd_y)\}\\]
Therefore, if two lines are not parallel \\(\left(\textbf\{b\}\times \textbf\{d\}\right)\neq0\\), two lines intersects at
\\[\textbf\{a\}+p\textbf\{b\}=\textbf\{a\}+\frac\{(c_y-a_y)d_x+(a_x-c_x)d_y\}\{(b_yd_x-b_xd_y)\}\textbf\{b\}\\]
\\[=\textbf\{a\}+\frac\{(\textbf\{c\}-\textbf\{a\})\times \textbf\{d\}\}\{\textbf\{b\}\times\textbf\{d\}\}\textbf\{b\}\\]
In the original representation of a line with two points \\(a, b\\), we let
\\[\textbf\{a\}=a,\\>\textbf\{b\}=b-a\\]
\\[\textbf\{c\}=c,\\>\textbf\{d\}=d-c\\]
so if \\(\left(\textbf\{b\}\times \textbf\{d\}\right)=(b-a)\times(d-c)\neq0\\), then __the lines intersect at__
\\[=\textbf\{a\}+\frac\{(\textbf\{c\}-\textbf\{a\})\times \textbf\{d\}\}\{\textbf\{b\}\times\textbf\{d\}\times(b-a)\}=
a+\frac\{(c-a)\times (d-c)\}\{(b-a)\times(d-c)}\times(b-a)
\\] (Notice that \\((b-a)\times(d-c)\\) of the parallel test can be resued)
```java
typedef pair<double, double> vec2
bool lineIntersection(vec2 a, vec2 b, vec2 c, vec2 d, vec2& x){  
	double det = (b-a).cross(d-c);
	if(fabs(det) < 1e-6)return false;
	x = a + (b-a) * ((c-a).cross(d-c) / det);
	return true;
}
```
2. segments  
	1. If two segments are parallel, then we can easily find a intersection point.  
	We can use above code to test whether the two lines (which are extension of segments) are parallel, and compute their arbitrary intersection \\(p\\). If two lines are parallel, then we need to recalculate \\(p\\) if the two segments intersect. If not, then \\(p\\) is unique and genunine. We go to (2) with original \\(p\\).
	2. If are not parallel, then we need to test 2 conditions.
		1. for the first segment \\((a,b)\\), we know that \\(a, b, p\\) are in a line. If two lines are not parallel (thus the intersection point \\(p\\) is unique) and \\(a<=p<=b\\) holds, then \\(p\\) is included in the segment
		2. for the 2nd segment \\((c, d)\\), we need to apply the same test with \\(p\\).  
		If above two tests are passed, then the segments intersect.
```java
bool parallelSegments(vec2 a, vec2 b, vec2 c, vec2 d, vec2& p){ //tests whether two segments intersect
    if(a > b) swap(a, b);
    if(c > d) swap(c, d);
    if(ccw(a, b, c) != 0 || b < c || d < a) return false; //checks whether 1. not parallel, 2. not intersecting.
    if(a < c)p = c; else p = a;
    return true;
}
bool isBndingRect(vec2 p, vec2 a, vec2 b){
    if(b < a)swap(a, b);
    return p == a || p == b || (a < p && p < b);
}
bool segIntersec(vec2 a, vec2 b, vec2 c, vec2 d, vec2& p){
    if(!lineIntersection(a, b, c, d, p)){
	    //(a,b), (c,d) are parallel and p is not unique. need to recalulate p
	    return parallelSegments(a, b, c, d, p);
    }
	return isBndingRect(p, a, b) && isBndingRect(p, c, d);
}
```

