---
layout: post
title:  "Python - GIL"
date:   2020-04-10 05:04:00 +0900
categories: coding
use_math: true
tags: coding python
---

<a href="https://wiki.python.org/moin/GlobalInterpreterLock" target="_blank">https://wiki.python.org/moin/GlobalInterpreterLock</a>
* In CPython, the global interpreter lock, or GIL, is a mutex that protects access to Python objects, preventing multiple threads from executing Python bytecodes at once. This lock is necessary mainly because CPython's memory management is not thread-safe. (However, since the GIL exists, other features have grown to depend on the guarantees that it enforces.)
* CPython extensions must be GIL-aware in order to avoid defeating threads. For an explanation, see <a href="https://docs.python.org/3/c-api/init.html#thread-state-and-the-global-interpreter-lock" target="_blank">Global interpreter lock.</a>


<a href="http://www.dabeaz.com/python/GIL.pdf" target="_blank">http://www.dabeaz.com/python/GIL.pdf</a>
* <a href="https://web.stanford.edu/~ouster/cgi-bin/cs140-winter13/lecture.php?topic=scheduling" target="_blank">IO bound jobs have higher priority, CPU bound jobs has lower priority - to keep IO busy</a>
* priority inversion in multicore - CPU-bound가 잡고 있을 때, release & signal을 하면 다른 코어에 있는 IO-bound가 시그날을 받고 GIL을 체크하지만, 이미 CPU-bound thread가 GIL을 얻은 상황.

### avoiding GIL
* `PyPy` currently has a GIL like CPython
* in `Cython` the GIL exists, but can be released temporarily using a "with" stateme


All of Python's blocking I/O primitives release the GIL while waiting for the I/O block to resolve - <a href="https://stackoverflow.com/questions/29270818/why-is-a-python-i-o-bound-task-not-blocked-by-the-gil" target="_blank">https://stackoverflow.com/questions/29270818/why-is-a-python-i-o-bound-task-not-blocked-by-the-gil</a>


C / C++ libs like Numpy, OpenCV  
> numpy code __often__ releases the GIL while it is calculating, so that simple parallelism can speed up the code.
- https://stackoverflow.com/questions/50014026/is-the-gil-released-while-using-multithreading-with-python-opencv
- GIL avoidance는 C/C++코드상에서 매크로로 됨
  - opencv - `ERRWRAP2`, 
  - C python API - `Py_BEGIN_ALLOW_THREADS` (=`{ PyThreadState *_save; _save = PyEval_SaveThread();`). How can i use it?
    1. read first <a href="https://docs.python.org/3/c-api/init.html" target="_blank">https://docs.python.org/3/c-api/init.html</a>
    2. example <a href="https://docs.python.org/2.0/api/threads.html" target="_blank">python c api ref manual</a>
    3. what is this <a href="https://thomasnyberg.com/releasing_the_gil.html" target="_blank">https://thomasnyberg.com/releasing_the_gil.html</a>


* <a href="https://stackoverflow.com/questions/36194285/is-the-thread-created-by-ctypes-also-under-gil-in-python" target="_blank">ctypes are not affected by GIL. It's not like threads are under the GIL, operations in the Python interpreter are</a>



### Why care about thread-safe operations (and some are not, such as +=) with GIL?



### GIL advantages
- single thread에서 성능에 우위가 있다고 함. GIL과 대비되는 방식은 fine-graned lock 인데, 이거는 single thread서 느리다고 함. <a href="https://www.slideshare.net/deview/2d4python" target="_blank">https://www.slideshare.net/deview/2d4python</a> 이거 읽어봐야 할 듯