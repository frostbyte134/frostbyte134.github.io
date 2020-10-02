---
layout: post
title:  "Python - GIL"
date:   2020-09-30 05:04:00 +0900
categories: coding
use_math: true
tags: coding python
---

### 정리 (2020.10.01)
* `GIL` : Global interpreter lock. parallel환경에서 인터프리터가 python byte code를 동시에 실행하는 것을 막음. 
* why GIL? : python은 garbage collection에서, reference count (인터프리터 내부 변수)를 이용하기 때문. 인터프리터에 락이 걸리기 때문에 내부 변수도 thread-safe해짐
* why GIL is a problem?
  1. mulththreading이 의미가 별로 없음
  2. python은 따로 쓰레드 스케쥴링이 없음 - 특정 쓰레드가 GIL을 잡아야 할 시 (ex - main thread만이 signal handling 가능) 이를 보장해 줄 방법이 없음
  3. GIL에 의한 context switch는 signaling을 수반 - context switch가 자주 되는 상황에서는 performance bottleneck이 됨
* why thread safe, with the presence of GIL?
  * 대부분의 파이썬 함수들은 thread safe하지 않음
  * ex) list - `append()`는 thread safe하고, `+=`은 thread safe하지 않음
  * `+=`는 read && write를 함. 각 연산은 atomic하지만 &&이 문제 (중간에 `tick`을 세는 듯. 이 때 GIL relase가 가능)
* how to solve(avoid) GIL problem?
  - `asyncio`, partially
  - `multiprocessing` is another way


### Preliminaries, Glossary
- <a href="https://jins-dev.tistory.com/entry/Compiler-%EC%99%80-Interpreter-%EC%9D%98-%EA%B0%9C%EB%85%90%EA%B3%BC-%EC%B0%A8%EC%9D%B4%EC%A0%90" target="_blank">인터프리터 vs 컴파일러</a>
  - <a href="https://stackoverflow.com/questions/39313677/how-does-python-interpreter-run-the-code-line-by-line-in-the-following-code" target="_blank">링크</a>파이썬 컴파일러는 1줄씩 주면 1줄씩 해석, 전체 코드를 주면 한번에 바이트코드로 바꾼다 함

<a href="https://wiki.python.org/moin/GlobalInterpreterLock" target="_blank">https://wiki.python.org/moin/GlobalInterpreterLock</a>
* In CPython, the global interpreter lock, or `GIL`, is a __mutex__ that protects access to Python objects, __preventing multiple threads from executing Python bytecodes at once.__ This lock is necessary mainly because CPython's memory management is not thread-safe. (However, since the GIL exists, other features have grown to depend on the guarantees that it enforces.)  
  > Only one Python thread can execute in the interpreter at once
* CPython extensions must be GIL-aware in order to avoid defeating threads. For an explanation, see <a href="https://docs.python.org/3/c-api/init.html#thread-state-and-the-global-interpreter-lock" target="_blank">Global interpreter lock.</a>
* GC를 ref count 방식으로 함 - 각 객체의 ref count가 critical section이 됨. 각자에 mutex변수를 두는 것 보단 interpreter를 잠그는 것을 선택. 인터프리터가 잠기므로, 인터프리터 내부 변수 (reference count) 도 잠기는 효과가 있음. <a href="https://dgkim5360.tistory.com/entry/understanding-the-global-interpreter-lock-of-cpython" target="_blank">https://dgkim5360.tistory.com/entry/understanding-the-global-interpreter-lock-of-cpython</a>
* <a href="https://stackoverflow.com/questions/6319207/are-lists-thread-safe" target="_blank">그렇다면, 왜 list중 thread-safe한 연산이 따로 있는 것인가? (append() is thread safe, while += is not)</a> : append는 write(atomic)만 함. +=는 read(atomic) && write(atomic) 연산 도중(&&)에 GIL을 놓을 수 있기 때문. 
* Non-CPython implementations
  * Jython and IronPython have no GIL and can fully exploit multiprocessor systems
  * PyPy currently has a GIL like CPython
  * in Cython the GIL exists, but can be released temporarily using a "with" statement


<a href="http://www.dabeaz.com/python/GIL.pdf" target="_blank">http://www.dabeaz.com/python/GIL.pdf</a>
* during each tick (periodic check)
  * GIL release/acquire may happen
  * __handle signal (main thread)__
  * 이 tick을 기반으로 cpu-bound operation의 time slice가 이루어짐
  * tick loosely mapped to an interpreter instruction
    * long instruction can block everything
    * ticks are uninterruptible!
  * main thread만 signal을 처리할 수 있지만, python은 따로 쓰레드 스케쥴러가 없음 - main thread가 걸리리라는 희망을 갖고, 매 tick마다 GIL을 잠시 놓음
  * main thread가 block되었을 시 - ctrl+c 안먹힘
* All interpreter locking is based on signaling
  * To acquire the GIL, check if it's free. If not, go to sleep and wait for a signal
  * To release the GIL, free it and signal
  * 모든 GIL 관련 연산이 signaling을 포함하기 때문에, `tick이 자주 계산되는 특정 CPU 연산을 많이 할 경우` GIL 관련 부가 연산이 많아지면서, 멀티쓰레딩, 멀티프로세싱이 오히려 느려질 수 있음
    * 이 걸 해결하고자 `asyncio`를 그렇게 밀어 주는 건가...  
    ```python
    import time
    import threading

    def count(n):
        while n > 0:
            n -= 1

    trial = 100000000
    t = time.time()
    count(trial)
    count(trial)
    print("serial, elapsed = ", time.time() - t) # serial, elapsed =  8.761561632156372

    t1 = threading.Thread(target=count,args=(trial,))
    t2 = threading.Thread(target=count,args=(trial,))

    t = time.time()
    t1.start()
    t2.start()
    t1.join(); t2.join()
    print("two thread, elapsed = ", time.time() - t) # two thread, elapsed =  8.967807292938232
    ```

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



### Why care about thread-safe operations, with the presence of GIL?
There are operations (ex - += of list) that are not atomic. During the middle of the operation, GIL can be released when the tick depletes.


### Then why use GIL?
- 목적은 reference count에서 atomic operation을 하기 위함...? 
- single thread에서 성능에 우위가 있다고 함. 모든 ref count 변수를 atomic으로 두는 fine-graned lock과 비교하는 이야기인가...? <a href="https://www.slideshare.net/deview/2d4python" target="_blank">https://www.slideshare.net/deview/2d4python</a> 이거 읽어봐야 할 듯

<a href="https://docs.python.org/3/c-api/init.html#thread-state-and-the-global-interpreter-lock" target="_blank">https://docs.python.org/3/c-api/init.html#thread-state-and-the-global-interpreter-lock</a>
* The Python interpreter is not fully thread-safe. In order to support multi-threaded Python programs, there’s a global lock, called the global interpreter lock or GIL, that must be held by the current thread before it can safely access Python objects. Without the lock, even the simplest operations could cause problems in a multi-threaded program: for example, when two threads simultaneously increment the reference count of the same object, the reference count could end up being incremented only once instead of twice.  
* Therefore, __the rule exists that only the thread that has acquired the GIL may operate on Python objects or call Python/C API functions.__ In order to emulate concurrency of execution, the interpreter regularly tries to switch threads (see sys.setswitchinterval()). The lock is also released around potentially blocking I/O operations like reading or writing a file, so that other Python threads can run in the meantime.
* The Python interpreter keeps some thread-specific bookkeeping information inside a data structure called PyThreadState. There’s also one global variable pointing to the current PyThreadState: it can be retrieved using PyThreadState_Get().

결국, Python object에 접근할 떄는 atomic이 되는 것. 여러번 Python object에 접근하거나 C api를 호출하는 연산은 결국 thread-safe하지 않겠네.

reference counting 관련 C python code - <a href="https://dgkim5360.tistory.com/entry/understanding-the-global-interpreter-lock-of-cpython" target="_blank">link</a>

### Java - Mark and swap
이건 GC항목에 가야하는 거 아닌가?

<a href="https://velog.io/@litien/GIL-Java%EC%97%90%EB%8A%94-%EC%97%86%EB%8D%98%EB%8D%B0" target="_blank">출처 - https://velog.io/@litien/GIL-Java%EC%97%90%EB%8A%94-%EC%97%86%EB%8D%98%EB%8D%B0</a>
* Java는 Mark and Sweep(GC)으로 메모리를 관리한다. 객체 참조에 대한 수를 저장하지 않고, 루트부터 하나씩 참조를 따라가면서 찾은 객체가 살아있음을 Marking 한 후 전체 힙 객체들을 순회하면서 마킹되지 않은 객체들을 제거하는 방식이다.
* Mark and Sweep에서는 메모리가 일정수준 이상 찼을 때 위에서 언급한 컬렉팅 작업이 시작된다. 때문에 오브젝트의 참조가 변경 될 때마다 Atomic한 연산이 수행 될 필요가 없다. 이것이 Java에서 GIL라는 용어를 찾아보기 힘든 이유이다. 대신에 참조를 확인하는 mark 과정에서 모든 스레드가 일시적으로 중단시켜 gc의 atomic을 보장한다. 이 시기를 `stop the world`라 부르는데 이 stop the world를 줄이기 위해 여러 GC 알고리즘들이 발전하고 있다.