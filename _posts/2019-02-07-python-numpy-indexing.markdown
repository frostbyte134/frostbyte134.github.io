---
layout: post
title:  "Python - Numpy Indexing"
date:   2019-02-06 11:00:00
categories: python
use_math: true
tags: python numpy indexing
---

Reference: 
1. <a href="https://docs.scipy.org/doc/numpy-1.15.0/user/basics.indexing.html#other-indexing-options" target="_blank">scipy - numpy indexing</a>
2. <a href="https://scipy-cookbook.readthedocs.io/items/Indexing.html" target="_blank">https://scipy-cookbook.readthedocs.io/items/Indexing.html</a>

> __Summary__: copying and referencing (returing a view of original array) behavior of numpy 
1. slicing and partial indexing (without index array, just scalars) __returns the view__ of the data array
2. `Fancy indexing`, including index array and boolean indexing (whether partial or non-partial) does not return the view, but the __copy__ of the original data.  
When used in a lhs of assignment though, those indexing can change the values of the data array, in a bit slow speed than 1. The reason for bit slow speed is due to its structure (refer to the last section)


### Index arrays
Numpy array may be indexed with other arrays (sequence-like objs, except `tuple`).
* Index arrays must be of integer type
* Each value in the array indicates which value in the array to use
* Negative indexing allowed

> Generally speaking, what is returned when index arrays are used,  
is an array with the same shape as the index array, but with the type & value of the array being indexed.
```python
x = np.arange(10,1,-1)
x[np.array([[1,1],[2,3]])] # array([[9, 9], [8, 7]])
```

In below example, since the indexing is specifed only in the first dimension (with length 2), below result occurs. Indexing in 1st dimension gives length 5 1-dim array, and notice that the shape is same as the indexing array.
```python
x = np.arange(10,0,-1).reshape(2, 5)
print( x[np.array([[1,1], [1,0]])] ) #

# result = [[[ 5  4  3  2  1]
#			 [ 5  4  3  2  1]],
# 			[[ 5  4  3  2  1]
#			 [10  9  8  7  6]]]
```

### Indexing multidimensional arrays

* Multidimensional array indexing tend to be more unusual uses (seriously?)

Starting with an example
```python
y = np.arange(35).reshape(5, 7)
```

Rule of the Thumb
> To designate a single item in `len(ary.shape) == k` array using indexing, we need __k__ 1-dim index arrays. For the absent arrays, no broadcasing supported.

Therefore we need 2 index arrays to index y without partial indexing.

1. index arrays have a matching shape, and there is an index array for each dimension of the orig array  
\\(\rightarrow\\) resultant array has the same shape as the index arrays
```python
y[np.array([0, 2, 4]), np.array([0, 1, 2])] #array([0, 15, 30])
```
2. If the index arrays do not have the same shape, broadcasting between index arrays performed
```python
y[np.array([0, 2, 4]), 1] #array([1, 15, 29])
```
3. partial indexing is also supported
```python
>>> y[np.array([0, 2, 4]), 1]
array([[ 0,  1,  2,  3,  4,  5,  6],
       [14, 15, 16, 17, 18, 19, 20],
       [28, 29, 30, 31, 32, 33, 34]])
```
In general,
> the shape of resultant array = indexing array (concat) unindexed part of orig array

For example, indexing (lookup, 3) __shaped__ color lookup table with (h, w) __shaped__ array with dype=uint8 (\\(\geq\\) lookup) gives (h, w, 3) array.  
The first (and the only) index array (h, w) designate where to look in the first channel (lookup) of the original array.

### Slicing 

Unlike the built-in `list`, sliced or partial indexing with scalars (not the numpy array or list) does not copy but __reproduces new view__ of the original data.
```python
ary = [1, 2, 3, 4]
what = ary[1:3]

what[0] = 25
print(ary) # [1, 2, 3, 4]

ary = np.array([1, 2, 3, 4])
what = ary[1:3]

what[0] = 25
print(ary) # [1, 25, 3, 4]
```
* `array.copy()` gives copy of the array in different memory location.
* Notice that, for the slicing (a:a+1) which results in single element, numpy array returns the copy (not the view).
* Above holds same for the partially indexed arrays

Numpy supports multidimensional indexings, such as `x[2, 5]` rather than `x[2][5]`.
```python
x = np.arange(10)
x.shape = (2, 5)
x[0] # array([0, 1, 2, 3, 4])
x[0][2] #2
```
Even among the indexings with scalars, `x[0][2]` is more inefficient than `x[0, 2]`, since intermediate `x[0]` subarray is created (it points the same memory direction, but still inefficient).

### Boolean or "mask" index arrays
> Boolean arrays used as indices are treated in a different manner entirely than index arrays.

Unlike the index arrays (refer to the `rule of the thumb`), boolean arrays must be (at least) of the __same shape__ as the initial dimensions of the original array  
1. The most straightforward case, the boolean array has same shape with data array
```python
b = y>20 # shape.b = (5, 7)
y[b] # returns 1-dim array of length 14  (21~34)
```
* Notice that the result is 1-dim numpy array
* `y[b]` is equivalent to `y[np.nonzero(b)]` (same in efficiency perspective? not sure.)

When the boolean array has few dimensions than the data array, multidimensional array returned.  
The shape of the returned array will be
> result.shape = ((# of nonzero element of boolean array), (residual dimensions of the data array))


### Structural indexing tools
* `np.newaxis`
* `...`: ellipsis maybe used to indicate selecting in full any remaning unspecified dimensions.
```python
z = np.arange(81).reshape(3, 3, 3, 3)
z[1,...,2]
z[1, :, :, 2]
```
above 2 are equivlanemt

### How assigning values to indexed arrays works
```python
x = np.arange(0, 50, 10)
array([ 0, 10, 20, 30, 40])
x[np.array([1, 1, 3, 1])] += 1
x # array([ 0, 11, 20, 31, 40])
```
One could expect x[1] to be 13, but it is not.
1. temp array, containing values of x at [1, 1, 3, 1] is created ([10, 10, 30, 10])
2. 1 is added to each
3. temp array is assigned back

## <a href="https://scipy-cookbook.readthedocs.io/items/Indexing.html#How-indexing-works-under-the-hood" target="_blank">How indexing works under the hood</a>

A numpy array is a block of memory, a data type for interpreting memory location, a list of sizes, and a list of strides.  
So for example, C[i,j,k] is the element starting at position i*strides[0] + j*strides[1] + k*strides[2]. This is why the transposing is fast (reverse the strides and sizes. Now we can insert reversed index and get the original data), but fancy indexing is rather slow.