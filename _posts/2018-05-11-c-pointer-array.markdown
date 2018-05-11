---
layout: post
title:  "C Pointer and Array"
date:   2018-05-11 10:13:00 +0900
categories: coding
use_math: true
tags: coding c++
---

### Dimension of a variable in C
Every variable in C has a concept of `dimension`.
```c++
int p; //dimension 0
int *p; //dimension 1
int **p; //dimension 2
...
```
Dimension must match to perform an assign operation.

### array name = pointer?
Although they have same dimension and same value (address), they are treated differently by the compiler.  
Automatic conversion from __pointer to array__ can be done, but not for vice versa (__array to pointer__).  
Thus we can think that, \\[\textrm\{array\} \subset \textrm\{pointer\}\\]
```c++
int a[5];
int *ptr = a; //dimension matches. no compile error (conversion from pointer to array)
a = ptr // compile error (conversion from array to pointer is prohibited)
printf("%p %d\n", a, sizeof(a)); //003AF708, 20
printf("%p %d\n", ptr, sizeof(ptr)); //003AF708, 4
```
Also note that, array handle is treeted as a constant
```c++
a = a+4; //compile error
```
VS2010 yields following compile error statement:  
__참조 또는 배열에 대한 포인터로의 변환은 있지만 배열 형식으로의 변환은 없습니다.__  

More complicated example is
```c++
int (*p3)[5];
int ary[4][5];
p3 = ary;
cout<<sizeof(ary)<<endl; //4*5*4
cout<<sizeof(ary[0])<<endl; //5*4
cout<<sizeof(p3)<<endl; //4
cout<<sizeof(*p3)<<endl;  //20
cout<<sizeof(*(p3+1))<<endl; //20
cout<<sizeof((*p3)+1)<<endl; //4
```

### [] has higher priority than *
```c++
int **p1;
```
 p1 is a `pointer`, which points 1-dimensional int pointer
<br/><br/>
```c++
int *p1[5];
```
 p1 is an `array` of size 5, where members are int pointer  
=`pointer array`
<br/><br/>
```c++
int (*p1)[5];
```
 p1 is a `pointer`, which points an array with 5 int elements  
=`array pointer`  
We can intepret above array pointer as a handle for [arbitrary size of row][5]

### Type of an array handle
Type of an array handle is __an pointer__ of the maximum item (array pointer)
```c++
int ary[3][4] = {0, };
```
Then, type of `ary` is `int (*)[4]` - a pointer which points int[4] (consecutive 4*4 bytes of memory area) 
```c++
int **p1 = ary; //dimension matches, but (int**) and int(*)[5] does not match (compile err)
int (*p1)[5] = ary; //no err
```


### Addition/subtraction operation on pointer
```c++
ary[1][2] = 7
```
Is converted into following expression
```c++
*(*(ary+1)+2) = 7
```
In address term, `ary+1` is run as, ary + 1 * (size of data which ary points)  
ary is an `array pointer` of int(*)[4], so above expression becomes (ary + 1 * sizeof(int[4]))