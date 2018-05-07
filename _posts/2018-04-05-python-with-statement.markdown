---
layout: post
title:  "Python - with statement and Context manager"
date:   2018-04-05 12:04:00
categories: python
use_math: true
tags: python
---


__Context manager__ is a class with two abstract functions:
* `__enter__`: for initializing (file open, for example)
* `__exit__`: for destructing (file close)

```python
with (context manager) as alias:
```
Before the start of following block `__enter__` is called for proper openning of the context,  
and at the end of the block `__exit__` is called for proper closing of the context.
  
Example:
```python
with open("foo.txt", "w") as f:
    f.write("Life is too short, you need python")
```