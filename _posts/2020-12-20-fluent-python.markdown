---
layout: post
title:  "Fluent Python"
date:   2020-12-20 08:00:05 +0800
categories: coding
use_math: true
tags: coding python
---

> Ramalho, Luciano. Fluent Python. O'Reilly Media. Kindle Edition. 


이거 정리할 필요가 있나...? 그냥 마크해놓고 책 한번 훑는 게 더 빠를지도?

### Chap 1. The Python Data Model

<a href="https://docs.python.org/3/reference/datamodel.html" target="_blank">Python data models</a>
- if you learned another object-oriented language before Python, you may have found it strange to use `len(collection)` instead of `collection.len()`.
  - `Python data model` = key to everything we call `Pythonic`
- `dunder` methods = `__getitem__`
- implement `__getitem__`, `__len__` dunders and you will be able to perform
  - indexing `deck[0]`
  - random selection  
    ```python
    from random import choice
    choice( deck)
    ```
  - iteration  
    ```Python
    for card in deck:
      print( card)
    ```
  - inclusion test (if `__contains__` method is not implemented, then `in` __operator does a sequential scan__ )
    ```Python
    >>> Card(' Q', 'hearts') in deck
    True
    ```
  - how about __shuffling__ : currently the object is immutable (it is based on a list). There will be a one-liner `__setitem__` method in chap11.
- for built-in types like list, str, bytearray, and so on, __the interpreter takes a shortcut:__
  - the CPython implementation of len() actually returns the value of the ob_size field in the PyVarObject C struct that represents any variable-sized built-in object in memory. This is much faster than calling a method.
- If you need to invoke a special method, it is usually better to call the related built-in function
  - e.g., call len to implicitly call __len__
- CPython implementation detail: For CPython, id(x) is the memory address where x is stored.

#### String representation
```Python
def __repr__( self):
  return 'Vector(% r, %r)' % (self.x, self.y) 
```
- using `%r` is a good practice (because it shows the crucial difference between Vector( 1, 2) and Vector(' 1', '2'))
- On Wikipedia, the first definition of object model is “The properties of objects in general in a specific computer programming language.” This is what the “Python data model” is about.
