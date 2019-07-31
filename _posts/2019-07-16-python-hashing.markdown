---
layout: post
title:  "Python - hashing"
date:   2019-07-16 16:04:00 +0900
categories: coding
use_math: true
tags: coding python
---
<a href="https://stackoverflow.com/questions/49722196/how-does-python-compute-the-hash-of-a-tuple" target="_blank">https://stackoverflow.com/questions/49722196/how-does-python-compute-the-hash-of-a-tuple</a>

Hashing used in python depends on the `__hash__()` function
* for immutable object, the `__hash__()` function is not implemented (nonetype)
* for tuples (and immutable list-like objects),   
  >  it does a bunch of XOR hokus-pocus with the hashes of each of its elements.
* for some python implementation, `__hash__()` returns same value as the `id()` function. But this is not mandatory



```python
class A: pass
a0 = A()
ta = (1, a0)
hash(ta)  # -1122968024
a0.x = 20
hash(ta)  # -1122968024
```

Since we did not implemented `__hash__()` function, the Python interpreter does not consider the instance added, thus returning same hash value