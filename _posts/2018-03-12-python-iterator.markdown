---
layout: post
title:  "Python - Iteration (iterator, next)"
date:   2018-03-12 12:04:00
categories: python
use_math: true
tags: python
---
```python
seq = ['foo', 'bar']
for x in seq:
    print(x)
```
Above code is translated into (similar) code by Python interpreter
```python
iterator = iter(seq)
while True:
    try:
        x = iterator.__next__()
        print (x)
    except StopIteration as e:
        break
```
<br/>
Below is an example of self-iterable class.
```python
class Range(object):
    def __init__(self, low, high):
        self.current = low
        self.high = high

    def __iter__(self):
        'Returns itself as an iterator object'
        return self

    def __next__(self):
        'Returns the next value till current is lower than high'
        if self.current >= self.high:
            raise StopIteration
        else:
            self.current += 1
            return self.current - 1

for i in Range(0, 2):
    print(i, end=' ')   # 0 1
```
Note that the `__iter__()` function must raise StopIteration exception to stop.  

iterator can be ```materialized``` by using the ```list()``` or ```tuple()``` constructor functions.  
Note that you can only go forward in an iterator; there is no going back or reset.  
```max()```, ```min()``` functions and in, not in operators take iterator as an argument. In that case, if the stream returned by the iterator is infinite, the program will never end.  
Note also: ``Generator``, `Iterator vs Iterable`
