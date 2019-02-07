---
layout: post
title:  "Python - Caching"
date:   2019-02-06 10:59:00
categories: python
use_math: true
tags: multiprocessing python caching
---

Reference: The Hacker's Guide to Scaling Python

### cachetools  library
- provides LRU, LFU, TTL caching

### Memoization
- only applicable to pure functions (no side effect)  
- `functools` provides LRU cache decorator

```python
import functiols
import math

@functools.lru_cache(maxsize=2)
def memoized_sin(x):
	return math.sin(x)
```

