---
layout: post
title:  "Python - Comprehensions"
date:   2018-03-12 09:04:00
categories: python
use_math: true
tags: python
---
List comprehension supports the functionality of map and filter classes.
```python
[expr for val in iterable if condition]
```
Multiple list comprehension works like for loops in other languages
```python
print([x for y in range(3)
       for x in range(4)])  #[0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3]
```
<br/>
#### __Nested list comprehension__
```python
print([[x for x in range(4)] for y in range(3)])
#[[0, 1, 2, 3], [0, 1, 2, 3], [0, 1, 2, 3]]
print([[x + 1 for x in range(num*3, num*3+3)] 
       for num in range(0, 3)])
```
  
Opinions vary, but most agree that the imperative solution is more readable (for nested comprehensions?)
<br/><br/>
#### __Dictionary comprehension__
```python
print({i:i for i in range(5)}) #{0: 0, 1: 1, 2: 2, 3: 3, 4: 4}
```

Set comprehension
print({i for i in range(5)}) #{0, 1, 2, 3, 4}

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