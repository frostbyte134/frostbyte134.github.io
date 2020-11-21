---
layout: post
title:  "Python - AsyncIO"
date:   2020-09-27 09:10:05 +0800
categories: python
use_math: true
tags: python coding
---

aio = blocking wait -> event+callback?

내용 정리가 필요한 듯...

- When the await keyword is used, your coroutine is supended and the event loops checks if another coroutine can be executed or resumed.

### why asyncio?


<a href="https://discuss.python.org/t/what-are-the-advantages-of-asyncio-over-threads/2112/5" target="_blank">in Python, the three fundamental advantages of async/await over threads are: (글 엄청 잘쓰네 다들)</a>  
- `Cooperative multi-tasking` (green-thread에 의해서도 달성될 수 있음) is much lighter-weight than OS threads, so you can reasonably have millions of concurrent tasks, versus maybe a dozen or two threads at best.
- Using await makes visible where the schedule points are. This has two advantages:
    - It makes it easier to reason about data races
    - A downside of cooperative multi-tasking is that if a task doesn’t yield then it can accidentally block all other tasks from running; if schedule points were invisible it would be more difficult to debug this issue.
- Tasks can support cancellation. (Which also benefits from making await visible, because it makes it possible to reason about which points are cancellation points.)
- There are exactly three syntactic forms that can do an `await`, and those are await, async for, and async with.
- I’m not saying you’re wrong and async/await is always 100% the best. I’m saying the tradeoffs are complicated, and a lot of people have good reasons for deciding that async/await is the best option for their particular situation. Even before asyncio and async/await, the twisted and tornado libraries were very popular, and their APIs were much more difficult to work with than modern asyncio, because they didn’t have any help from the language and had to do everything with callbacks. - 결국 async를 callback말고도 다른 방법으로 하기 위해 await/async를 추가해 줬다는 말인가?


`green threads`
- decoupling python threads from os-threads. There is no bijection between python green threads and os level threads.


`Threading, via concurrent.futures` vs `Asyncio`
- 결국 멀티쓰레딩도 io연산을 만나면 uninterruptible sleep에 빠지며 해당 쓰레드는 스케쥴링에서 제외될 것임. 개인적인 생각에는 carefully written multithreading code (or well written green thread libs?)과 async/await의 성능 차이는 크게 없어 보이나, race condition / scheduling에 대한 접근 방식 차이인 듯 (implicit vs explicit + visible)
- cancellation도 한 몫 하는 듯?...난 아직 별로 필요한 적은 없었지만.
- 검색하면 바로 나오는 글에는 event loop가 1개 쓰레드로만 동작한다고 하지만, 진짜 그런지는 의심스럽다. 예를 들어 큰 io연산을 만나 yield한 코루틴이 3개 있다고 할 시, 이 io연산들은 각자 다른 uninterruptible 쓰레드 위에서 돌고 있을 테니까 (green thread가 아닌 이상). 안그러면 너무 비효율적이므로...결국 위 python core devs들의 말처럼 (you can reasonably have millions of concurrent tasks, versus maybe a dozen or two threads at best), multithreading의 task_interruptible + tast_uninterruptible 쓰레드 개수를 much smaller interruptible threads + task_uninterruptible 로 만들어 주는 듯. cooperative를 통해서 스케쥴링에서 일어나는 경쟁을 줄일 수 있게..그리고 이걸 줄일 수 있도록 잘 짜는 건 개발자 몫이고. explicit하게 표현되게 해 줬는데 알아서 잘 짜야지...?

결국 정리하면,
- uninterruptible sleep하는 태스크는 multithreading으로, CPU를 점유하는 interruptible tasks들은 cooperative하게 처리하겠다는 의도. 이 과정에서 코드 표현을 좀 explicit하게 해 주고, 사용자에게 더 많은 자유(=책임)을 준다는 것이 취지인 듯

#### 예제 1
```python
import asyncio
import time

async def func(ind):
    t = time.time()
    print("func {} called at".format(ind), t)
    await asyncio.sleep(ind) # simluate I/O operation (from different sources for each function)
    print("func {} term at".format(ind), time.time())


loop = asyncio.get_event_loop()
cur_t = time.time()
loop.run_until_complete(
    asyncio.gather(
        func(1),
        func(2),
        func(3)
    )
)
print("total loop elapsed ", time.time() - cur_t)

loop.close()
```
- 다른 source의 IO연산 3개가 있다고 할 시, 기본적인 multithreading은 OS level thread 3개를 동시에 실행시켜야 했고, 연산이 끝난 뒤에 4개가 동시에 priority에 따라 time slice를 가져갔음.  
- 그러나 asyncIO는 CPU를 점유할 쓰레드 1개 + 각자 IO연산별로 IO연산만 하고 종료하는 1개의 쓰레드 (제약사항이 있는 범용적인 쓰레드가 아니니 좀 더 간단하게 만들 수 있을 듯)가 있어서, 코딩이 간편하고 성능 개선의 여지가 좀 더 있을 듯. await으로 쓰레드 생성 지점이 Explicit하게 표현이 되는 것도 장점인 듯
  - `await (IO 연산)`이 쓰레드를 새로 만드는지는 (이벤트 루프에서?) 찾아보진 않았는데 맞을 듯. IO연산은 uninterruptible sleep이니까.
- await간의 우선 순위 (현재 task에서 await시 loop가 대기중인, await을 호출했다가 처리가 다 끝난 task 중 하나 선택) 가 어떻게 되지?
- 사용자가 잘못 짜면 (await을 하지 않고 자기 혼자 돌아가는 task 등) 망하는 듯. 쓰레딩은 time slice를 알아서 나눠 줬으나..

#### 예제 2 - producer / consumer
<a href="https://asyncio.readthedocs.io/en/latest/producer_consumer.html" target="_blank">https://asyncio.readthedocs.io/en/latest/producer_consumer.html</a>
- 사용되는 `asyncio.Queue`가 thread safe 할 필요 없음 <a href="https://docs.python.org/3/library/asyncio-queue.html" target="_blank">(실제로도 그러함)</a>
- `queue.put` / `queue.get`이 동시에 실행될 일이 __절대__ 없으므로, thread-safe할 필요가 없음

#### 예제 3 - crawler with asyncio
- <a href="https://aosabook.org/en/500L/a-web-crawler-with-asyncio-coroutines.html" target="_blank">https://aosabook.org/en/500L/a-web-crawler-with-asyncio-coroutines.html</a>
- 나중에...보자

### Reference pages
- <a href="https://blog.humminglab.io/python-coroutine-programming-2/" target="_blank">https://blog.humminglab.io/python-coroutine-programming-2/</a> [1]
- <a href="https://docs.python.org/3/library/asyncio-dev.html#asyncio-multithreading" target="_blank">https://docs.python.org/3/library/asyncio-dev.html#asyncio-multithreading</a>
- <a href="https://asyncio.readthedocs.io/en/latest/" target="_blank">https://asyncio.readthedocs.io/en/latest/</a> 
    > In short, asyncio adopted a radically different solution for race conditions.
  - 자신의 실행권한을 yield하는 것이 race condition에 대한 새로운 해결책이 되는 이유 = cpu1개를 time slice해서 나눠가져서, 실행 중 제어권이 의도하지 않게 넘어가는 상황을 원천적으로 막기 때문. 개발자가 critical section을 다 처리하고 yield를 하면, 해당 section은 cpu 연산에서는 보호받게 됨.
- <a href="https://docs.python.org/dev/library/asyncio.html" target="_blank">https://docs.python.org/dev/library/asyncio.html</a>
  - <a href="https://docs.python.org/dev/library/asyncio-dev.html#concurrency-and-multithreading" target="_blank">concurrency and multithreading</a>

> https://asyncio.readthedocs.io/en/latest/ 의 내용을 주로 가져옴

### Glossary
`coroutine` : A coroutine is a piece of code that can be paused and resumed. In contrast to threads which are preemptively multitasked by the operating system, __coroutines multitask cooperatively__. I.e. they choose when to pause (or to use terminology for coroutines before 3.4 - `yield`) execution. They can also execute other coroutines.
- `event loop` : The event loop is the central execution device to launch execution of coroutines and handle I/O (Network, sub-processes…)
  - 프로세스당 1개 / 쓰레드당 1개 같은 개념이 아니고 그냥 계속 만들 수 있는 듯
- `future` : It’s like a mailbox where you can subscribe to receive a result when it will be done. More details in official future documentation
- `task` : It represents the execution of a coroutine and take care the result in a future. More details in official task documentation


### 루프의 실행
`loop = asyncio.get_event_loop()`

1. 무한루프
```python
loop.run_forever()
loop.close()
```
2. gather 이용 (future 반환하는 함수)
```python
loop.run_until_complete(
    asyncio.gather(coroutines...)
)
loop.close()
```

### PEP 3148 (concurrent의 futures 설명. asyncio의 coroutine은 아님)
```python
from concurrent import futures
import urllib.request

URLS = ['http://www.foxnews.com/',
        'http://www.cnn.com/',
        'http://some-made-up-domain.com/']

def load_url(url, timeout):
    return urllib.request.urlopen(url, timeout=timeout).read()

def main():
    with futures.ThreadPoolExecutor(max_workers=5) as executor:
        future_to_url = dict(
            (executor.submit(load_url, url, 60), url)
             for url in URLS)

        for future in futures.as_completed(future_to_url):
            url = future_to_url[future]
            try:
                print('%r page is %d bytes' % (
                          url, len(future.result())))
            except Exception as e:
                print('%r generated an exception: %s' % (
                          url, e))

if __name__ == '__main__':
    main()
```


### Python 3.8 asyncio document
<a href="https://docs.python.org/3/library/asyncio.html" target="_blank">https://docs.python.org/3/library/asyncio.html</a>

* asyncio is a library to write concurrent code using the `async/await` syntax.  
* asyncio is often a perfect fit for __IO-bound__(GIL!) and high-level structured network code.
* `asyncio.run(coroutine)`: 단일 진입점이 되는 메인 코루틴을 실행시키는 데 좋음
* await 만으론 concurrent execution이 안됨. `async def`로 선언된 coroutine을 `task = create_task(coro)`함수로 task로 만들어 줘야 concurrent execution이 됨
  * create_task로 만들어진 task객체는 concurrent 실행 (await) 될 수 있고, .cancel()로 취소할 수도 있음



__Important__ In this documentation the term “coroutine” can be used for two closely related concepts:
* a `coroutine function`: an async def function;
* a `coroutine object`: an object returned by calling a coroutine function.

three main types of awaitable objects: `coroutines`, `Tasks`, and `Futures`.
* Python coroutines are awaitables and therefore can be awaited from other coroutines
* Tasks are used to schedule coroutines concurrently.


A `Future` is a special low-level awaitable object that represents an eventual result of an asynchronous operation.
* A good example of a low-level function that returns a Future object is `loop.run_in_executor()`.


running an asyncio program: `asyncio.run(coro)`  
creating task: `asyncio.create_task(coro)`
Sleeping: `coroutine asyncio.sleep(coro)`  
Running Tasks Concurrently: `awaitable asyncio.gather(coro)`
* Run awaitable objects in the aws sequence __concurrently.__

### Coroutines and Tasks

> Subroutines are special cases of coroutines (Knuth)
  Any subroutine can be translated to a coroutine which does not call yield ("Epigrams on programming")

#### Coroutine vs thread
> <a href="https://en.wikipedia.org/wiki/Coroutine" target="_blank">Coroutines are very similar to threads.</a> However, coroutines are cooperatively multitasked, whereas threads are typically preemptively multitasked. This means that coroutines provide <a href="https://stackoverflow.com/questions/1050222/what-is-the-difference-between-concurrency-and-parallelism" target="_blank">concurrency but not parallelism.</a> The advantages of coroutines over threads are that they may be used in a hard-realtime context (switching between coroutines need not involve any system calls or any blocking calls whatsoever), there is no need for synchronisation primitives such as mutexes, semaphores, etc. in order to guard critical sections, and there is no need for support from the operating system.  
It is possible to implement coroutines using preemptively-scheduled threads, in a way that will be transparent to the calling code, but some of the advantages (particularly the suitability for hard-realtime operation and relative cheapness of switching between them) will be lost.


#### Coroutine vs generator
> <a href="https://en.wikipedia.org/wiki/Coroutine#Comparison_with_generators" target="_blank">Wikipedia</a> - Generators, also known as semicoroutines,[5] are a subset of coroutines. Specifically, while both can yield multiple times, suspending their execution and allowing re-entry at multiple entry points, they differ in coroutines' ability to control where execution continues immediately after they yield, while generators cannot, instead transferring control back to the generator's caller.

* `sub routine`: supports `main routine`. often implemented as functions without return value. 별도의 메모리공간에 sub-routine이 존재. return으로 종료. 종료 후 별도의 context (stack, register vals)를 저장하지 않음
* `coroutine`
  * 별도의 메모리공간에 았는 것은 동일 
  * `yield`를 통해 잠시 실행 권한을 반환했다가, 나중에 다시 그 위치에서 실행가능
  * 여러 진입점 보유가능 (?) - 메인루틴에 종속적이지 않음 

<a href="https://blueshw.github.io/2016/01/25/python-co-routine-vs-sub-routine/" target="_blank">https://blueshw.github.io/2016/01/25/python-co-routine-vs-sub-routine/</a>
> `next(coroutine)`은 coroutine 함수의 첫번째 yield 까지 호출한다음 대기합니다 ... iteration 이 가능한곳까지 next 함수가 수행된 뒤에는 StopIteration 에러가 발생하게 됩니다.  
  만약 yield 문이 대입연산의 우변에 있다면 해당 코루틴 객체에 send(value)를 호출해 주어야 합니다. somevar = yield valA 에 멈춰있는 상태에서 valA에 값이 전달되어야 하는데 아무런 값도 들어오지 않는다면 에러가 발생하게 됩니다. (무슨 에러?) 즉, yield 를 통해서 메인루틴과 서브루틴간에 서로 값이 이동하면서 특정 로직을 수행하게 되는 것입니다.


<a href="https://docs.python.org/3/library/asyncio-task.html" target="_blank">python 3.8.3 documentation of coroutine</a>


* <a href="https://tech.ssut.me/python-3-play-with-asyncio/" target="_blank">https://tech.ssut.me/python-3-play-with-asyncio/</a> - old
* <a href="https://nachwon.github.io/asyncio-and-threading/" target="_blank">https://nachwon.github.io/asyncio-and-threading/</a>  
> 코루틴은 항상 반드시 하나의 코루틴만 실행되기 때문에 (이벤트 루프 하나에서), 여러 쓰레드들을 사용할 때처럼 락을 관리할 필요가 없다. 다른 코루틴으로 제어권을 넘겨주려면 await 문을 사용하여 언제든지 넘겨줄 수 있다. 그렇기 때문에 코루틴은 안전하게 취소할 수 있다. 코루틴이 멈춰있던 await 문에서 CancelledError 를 처리해서 마무리하면 된다.
* https://sjquant.tistory.com/14  
  1. 이벤트 루프(Event Loop)
이벤트 루프는 작업들을 루프(반복문)를 돌면서 하나씩 실행시키는 역할을 합니다. 이때, 만약 실행된 작업이 특정한 데이터를 요청하고 응답을 기다려야 한다면, 이 작업은 다시 이벤트 루프에 통제권을 넘겨줍니다. 통제권을 받은 이벤트 루프는 다음 작업을 실행하게 됩니다. 그리고 응답을 받은 순서대로 멈췄던 부분부터 다시 통제권을 가지고 작업을 마무리합니다.
  1. 코루틴(Coroutine)
이때, 이러한 작업은 파이썬에서 코루틴(Coroutine)으로 이루어져 있습니다. 코루틴은 응답이 지연되는 부분에서 이벤트 루프에 통제권을 줄 수 있으며, 응답이 완료되었을 때 멈추었던 부분부터 기존의 상태를 유지한 채 남은 작업을 완료할 수 있는 함수를 의미합니다. 파이썬에서 코루틴이 아닌 일반적인 함수는 서브루틴(Subroutine)이라고 합니다.
* https://hamait.tistory.com/833

실화인가 ㄷㄷ
e
`async def` 함수명

코루틴 실행: loop.run_until_complete(supervisor()), 


### Coroutines
* <a href="https://hamait.tistory.com/830" target="_blank">https://hamait.tistory.com/830</a>
* <a href="https://docs.python.org/ko/3/library/asyncio-task.html" target="_blank">https://docs.python.org/ko/3/library/asyncio-task.html</a>
* https://sjquant.tistory.com/14
    - 이벤트 루프


### AsyncIO


### How to benefit from asyncIO?
* IO bottleneck handling?


### 어웨이터블
우리는 객체가 await 표현식에서 사용될 수 있을 때 어웨이터블 객체라고 말합니다. 많은 asyncio API는 어웨이터블을 받아들이도록 설계되었습니다.

어웨이터블 객체에는 세 가지 주요 유형이 있습니다: 코루틴, 태스크 및 퓨처.


### Future
```
from concurrent.futures import ThreadPoolExecutor
from time import sleep
 
def return_after_5_secs(message):
    sleep(5)
    return message
 
pool = ThreadPoolExecutor(3)
 
future = pool.submit(return_after_5_secs, ("hello"))
print(future.done())
sleep(5)
print(future.done())
print(future.result())

```
출처: https://hamait.tistory.com/828 [HAMA 블로그]
