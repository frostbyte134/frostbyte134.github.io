---
layout: post
title:  "Python - closures"
date:   2019-07-29 16:04:00 +0900
categories: coding
use_math: true
tags: coding python
---

* originally written in 2018-03-15 16:04:00

>Wikipedia: Closure is a __function__, together with a referencing environment for the non-local variables of that function.

A closure in Python is simply a function returned by another function.
In Python, a function can return new functions (first class citizen). The inner function is a closure, and any variable it accesses that are defined outside of that function are free variables.

The criteria that must be met to create closure in Python are summarized in the following points.
* We must have a nested function (function inside a function).
* The nested function must refer to a value defined in the enclosing function.
* The enclosing function must return the nested function.

### Closure in Python
<a href="https://stackoverflow.com/questions/14413946/what-exactly-is-contained-within-a-obj-closure" target="_blank">https://stackoverflow.com/questions/14413946/what-exactly-is-contained-within-a-obj-closure</a>

In short, closure is implemented as a instance, which holds reference to the local and global variables it uses.
```python
def foo():
    bar = []
    for spam in ('ham', 'eggs', 'salad'):
        bar.append(lambda: spam)
    return bar

for bar in foo():
    print bar()
```

the result is 3 _salads_, since the _lambda_ functions (inside the list which the closure returns) points to the local variable _spam_.

Obviously, the local object is persistent until the lifecycle of the closure (function instance).

