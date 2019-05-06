---
layout: post
title:  "Python - Generator"
date:   2018-03-12 12:04:00
categories: python
use_math: true
tags: python
---

>A general theme of Python, as it progressed from version 2 to 3, is laziness.  

A way for functions to store state and generate the members of sequence on the fly  (instead of returning a list)

# generator
A function which returns an iterator. It looks like a normal function except that it contains yield statements for producing a series a values usable in a for-loop or that can be retrieved one at a time with the `next()` function. Each yield temporarily suspends processing, remembering the location execution state (including local variables and pending try-statements). When the generator resumes, it picks-up where it left-off (in contrast to functions which start fresh on every invocation).

Generator expressions / generator function with yield, return a generator object, which follows the iterator protocol (generator = self-iterator!)
An iterable object will have on `__iter__()` method.  
Every time it is iterated, `__iter__()` method will return an iterator object.  
An once iterable object will have an `__iter__()` method, and `next()` method.  
Below 2 functions are equivalent  
```python
def pos_gen1(seq):
    for x in seq:
        if x >= 0: yield x

def pos_gen2(seq):
    return (x for x in seq if x >= 0)
```
Generators are not executed when they are invoked, only when they are iterated over.   
And you can 
```python
def simple_generator():
    print("generate")
    yield 1
    yield 2

seq = iter(simple_generator())
print(seq.__next__())
print("-"*60)
print(seq.__next__())
print("-"*60)
print(seq.__next__())
```
Generator can be infinite. Return stops generation.