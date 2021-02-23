---
layout: post
title:  "Python - Event Loop (=event driven=Message dispatching)"
date:   2019-02-04 10:59:00
categories: python
use_math: true
tags: multiprocessing multithreading python event_loop message_dispatching event_driven asyncio 
---

Reference: The Hacker's Guide to Scaling Python coroutine

Event loop (message dispatching):
* works with queue (possibly multiprocessing)
* when a msg is inquened, dequeue the msg and convery to the appropriate processing module (function)
* a program (processing module) must be able to handle diverse kinds of messages (event sources).

event source = message

### socket and select
* refer to the book

* example - blocking socket (with socket.recv function) gives 5sec delay.
* setting `socket.setblocking(False)` and immediatly calling recv gives exception. (it gives exception till the socket is unreadable). We can use `while True` as the control statement. 
* `select.select(rlist, wlkst, xlist)` returns (readable, writable, error occured) socker lists.
* We can use `select loop` as a main control statement. Such method (Event loop) is used in fast HTTP server such as `NGINX` or `Node.js`.
* `select` is relatively old and slow. Each OS provides alternatives  
 - `epoll` of Linux, `kqueue` of FreeBSD. Python3 provides `asyncio`, which is a high-lvl abstraction layer for event loop.

### asyncio (of Python3)
* based on event loop concept. Works similarly to the `select` (or, python generator).
* `asyncio` generates event loop, while the application registers callback functions for specific events.
	* such callback functions are called `coroutine`. 

### coroutine simple example
* coroutine is defined with `async def` keyword
* You can see the resamblance to the generator. coroutine will not run until it is registered to the event loop.

```python
import asyncio

async def hello_world():
    print("Hello world!")
    return 42

hello_world_coroutine = hello_world()
print(hello_world_coroutine)
# <coroutine object hello_world at 0x0000000002F8D200>

event_loop = asyncio.get_event_loop()
try:
    print("Entering event loop")
    result = event_loop.run_until_complete(hello_world_coroutine)
    #Hello world!
    print(result)
    #42
finally:
    event_loop.close()
```


### coroutine, await keyword
* `await` keyword works similarly to the `yield` of generator
> await (coroutine)

```python
import asyncio

async def add_42(num):
    print("adding 42")
    return 42 + num

async def hello_world():
    print("Hello 1")
    result = await add_42(23)
    print("Hello 2")
    return 42

event_loop = asyncio.get_event_loop()
try:
    print("Entering event loop")
    result = event_loop.run_until_complete(hello_world())
    #Hello world!
    print(result)
    #42
finally:
    event_loop.close()
```

1. hello_world coroutine gets control
2. With `await` keyword, __register add_42 keyword to the event loop and return the control__ (from hello_world coroutine to event loop)
3. event loop runs add_42 coroutine
4. event loop runs remnant of hello_world coroutine


### asyncio.gather, ayncio.sleep
* `asyncio.gather`: parallel run, wait until every function finishes
* `ayncio.sleep`: is also a coroutine. Returns the control to the loop, and sleeps (blocking only in called coroutine)

```python
import asyncio

async def hello_world():
    print("Hello world")


async def hello_python():
    print("Hello python")
    await asyncio.sleep(0.1)
    print("end")

event_loop = asyncio.get_event_loop()
try:
    print("Entering event loop")
    result = event_loop.run_until_complete(
        asyncio.gather(hello_world(), hello_python())
    )
    print(result)
finally:
    event_loop.close()
```

### aiohttp, async with (= await)

```python
import asyncio
import aiohttp

async def get(url):
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as response:
            return response

event_loop = asyncio.get_event_loop()
coroutines = [get("http://example.com") for _ in range(8)]
results = event_loop.run_until_complete(asyncio.gather(*coroutines))

print("results = ", results)
```
* `async with` = `await` (as a context manager, used `await` in __enter__ and __exit__ functions)
* every time opening client session or waiting for the get response, returns control to the main loop (so that the first ready coroutine could run first)

other useful funcs: `loop.call_later(sec, coroutine)`

### Go vs Python
* Go: static, Python: Dynamic
* Go supports parallelism:
	* one process can utilize many cores (ex - better caching)
	* easy to maintain parallel programs than Python
	* unlike python which has to use `async model` and `thread model` at the same time to handle blocking stuff, go provides single programming model `goroutine`.
	* profiling is better in multiprocessing, blocking stats (pprof)
	

### Multiprocessing with asyncio

* Note that, asyncio is useful for efficiently using single core with external (IO, for example) bottleneck, not the calculation bottleneck from the single core

```python
import asyncio
from concurrent.futures import ProcessPoolExecutor

async def sub_main():
    print('Hello from subprocess')

def sub_loop():
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(sub_main())

async def start(executor):
    await asyncio.get_event_loop().run_in_executor(executor, sub_loop)

if __name__ == '__main__':
    executor = ProcessPoolExecutor()
    asyncio.get_event_loop().run_until_complete(start(executor))
```
