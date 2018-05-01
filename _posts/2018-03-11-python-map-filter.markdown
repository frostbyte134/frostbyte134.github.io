---
layout: post
title:  "Python - map, filter"
date:   2018-03-11 22:59:00
categories: python
use_math: true
tags: python
---

# 1. map
```python
map(f, iterableA, iterableB, ...)
```
returns an iterator over a sequence. Above is interpreted as,
```python
f(iterableA[0], iterableB[0], ...), f(iterableA[1], iterableB[1], ...), ...
```
→ The # of argmuents of f and the # of iterables must match.  
Since it returns an iterator, map can be applied to infinite sequences. This won't be possible if it returns a list.  
```python
print(type(map))    #<class 'type'>
print( map(int, '123') )    #<map object at 0x02154850>
print( list(map(int, '123')) )  #[1, 2, 3]
```
Above example shows that ```map is a class``` (from Python3), not a function.  
### Lazy aspect of map
Even when ∃ some runtime(?) error (ex - # of arguments of map and # of iterables does not match), map class will not throw an error until it is materalized.
