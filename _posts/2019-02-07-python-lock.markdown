---
layout: post
title:  "Python - Lock"
date:   2019-02-06 10:59:00
categories: python
use_math: true
tags: multiprocessing python lock multithreading
---

Reference: The Hacker's Guide to Scaling Python

### Atomic operations of Python (in Threading level?)
* list
	* `append`, `extend`, `__getitem__`, `pop`, `__setitem__`, `sort`
* x=y 
* setattr
* dict
	* `__setitem__`, `update`, `keys`

### Treading.Lock
Example code
```python
import threading

stdout_lock = threading.Lock()


def print_sth(num):
    with stdout_lock:
        for i in range(10):
            print("{}_{}".format(num, i))

threads = [threading.Thread(target=print_sth, args=[i]) for i in range(5)]
for thread in threads:
    thread.daemon = True
    thread.start()
```
	
`Threading.Rlock`: allows re-locking per thread

### Multiprocessing.Lock
Works for within-python forked processes

```python
import multiprocessing
import time

stdout_lock = multiprocessing.Lock()

def print_num(ind):
    time.sleep(0.1)
    with stdout_lock:
        for i in range(10):
            print("{}_{}".format(ind, i))

if __name__ == "__main__":
    with multiprocessing.Pool(processes=3) as pool:
        jobs = [pool.apply_async(print_num, args=[i]) for i in range(3)]
        for job in jobs:
            job.wait()
```
* `apply_aync`: returns `ApplyResult` class. __Can specify callback which gets 1 argument (result)__
* `ApplyResult` class
	* `get([timeout])`: returns the result when it arrives (blocking). Timout
	* `wait([timeout])`: wait until the result arrives
	* `successful()`: returns whether the call is completed. Raise `AssertionError` if the result is not yet ready.
	
### Interprocess Lock
use `fastners` library (file-based) - supports decorator. etc.