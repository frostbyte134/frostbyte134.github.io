---
layout: post
title:  "Python - Parameterized Decorator"
date:   2018-03-15 17:04:00
categories: python
use_math: true
tags: python
---

is a decorator customized on per function basis.

The method to generate a parameterized decorator, is to wrap the decorator with another function!
```python
def limit(length):
    def decorator(func):
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            #We have to sth with result and length here. Customization for func happens here.
            return result[:length]
    return wrapper
return decorator

#1st usage of parameterized decorator
@limit(5)
def data3(string):
    return string + " limit ro 3"
print(data3("ab"))

#2nd usage of parameterized decorator
def data8(string, sth = " hat"):
    return string + sth + "limit to 8"
dec = limit(8)(data8)
print(dec("he"))
```