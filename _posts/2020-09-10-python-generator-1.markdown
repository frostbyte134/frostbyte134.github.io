---
layout: post
title:  "Python - Generator, coroutine (Non-native)"
date:   2020-09-10 09:10:05 +0800
categories: python
use_math: true
tags: python coding
---


`non-native`
- generator : 결과를 반환하지 않고, iterator를 반환함. iterate될 때 마다 실행됨. (=caller에서 `__next__()`를 호출해 줄 때 마다)
  - coroutine도 caller가 `send()`를 호출해 줄 때 마다 실행되는데 : A generator is essentially a cut down (asymmetric) coroutine. The difference between a coroutine and generator is that a coroutine can accept arguments after it’s been initially called, whereas a generator can’t. (진입점 차이)
- `PEP380` generator에서 return 지원 : yield from으로 중간 제너레이터에서 하위 제너레이터 return 값을 받아서 활용하기 위함


### Reference pages
- <a href="https://blog.humminglab.io/python-coroutine-programming-1/" target="_blank">https://blog.humminglab.io/python-coroutine-programming-1/</a> [1]


### History
- 2018-03-12 작성
- 2020-09-10 revision 1 (예제 추가)


>A general theme of Python, as it progressed from version 2 to 3, is laziness.  

A way for functions to store state and generate the members of sequence on the fly  (instead of returning a list)

### generator
- `A function which returns an iterator`  
  - It looks like a normal function except that it contains yield statements for producing a series a values usable in a for-loop or that can be retrieved one at a time with the `next()` function. Each yield temporarily suspends processing, remembering the location execution state (including local variables and pending try-statements). When the generator resumes, it picks-up where it left-off (in contrast to functions which start fresh on every invocation).
- Generator expressions / generator function with yield, return a generator object, which follows the iterator protocol (generator = self-iterator!)
- An iterable object will have on `__iter__()` method.  
- Every time it is iterated, `__iter__()` method will return an iterator object.  
- An once iterable object will have an `__iter__()` method, and `next()` method.  

Below 2 functions are equivalent  
```python
def pos_gen1(seq):
    for x in seq:
        if x >= 0: yield x

def pos_gen2(seq):
    return (x for x in seq if x >= 0)
```

__Generators are not executed when they are invoked, only when they are iterated over.__ And you can 
```python
def simple_generator():
    print("generate")
    yield 1
    yield 2

seq = iter(simple_generator())
print(seq.__next__())
print("-"*60)
print(seq.__next__())
print("-"*60)
print(seq.__next__())
```
Generator can be infinite. Return stops generation.

### Example 1

```python
class Iterator(object):
    def __init__(self, num):
        print("__init__")
        self.index = 0
        self.until = num

    def __next__(self):
        print("__next__")
        if self.index > self.until:
            raise StopIteration
        n = self.index * 2
        self.index += 1
        return n

class Counter(object):
    def __init__(self, num):
        print("Counter __init__")
        self.num = num

    def __iter__(self):
        print("Counter __iter__")
        iter = Iterator(self.num)
        print("Counter __iter__ done")
        return iter

for i in Counter(5):
    print(i)
```

1. Initializer `__init__` of Counter is called in `for` loop
2. After the initialization is finished, `__iter__` of Counter is called
   1. Inside, `__init__` of Iterator is called and we now have Iterator obj in the loop
3. for each loop
   1. `__next__` of Iterator is called
   2. `start of a loop`
   3. blah blah

`__iter__` 함수를 Iterator 클래스에 통합할 수 없는 이유 : For문에서 Iterator 클래스가 2번 만들어지게 됨
 - `__iter__`를 호출하는 Iterator랑, `__next__`를 호출하는 Iterator 2개


### PEP 342 – Coroutines via Enhanced Generators
<a href="https://www.python.org/dev/peps/pep-0342/#new-generator-method-send-value" target="_blank">PEP 342 – Coroutines via Enhanced Generators</a> = yield basd coroutines


예전까진
1. 제너레이터 호출로 main에서 제어권 넘김
2. yield로 main에 값 및 제어권 넘김

의 반복 구조였고, main에서 generator로 값 넘기기가 불가능했음. 이제 `send()`를 이용해 가능. 이외에도 `throw()`, `close()`를 지윈  
레퍼런스 페이지의 예제
```python
def coroutine1():
    print('callee 1')
    x = yield 1
    print('callee 2: %d' % x)
    x = yield 2
    print('callee 3: %d' % x)
	
task = coroutine1()
i = next(task)    # callee 1 출력, i는 1이 됨. x = yield 1에서 멈춤 (이부분이 쓰레드와 다른 점!!!!!)
i = task.send(10) # x = yield 1 밑 부분부터 진행, "callee 2: 10" 출력, i는 2가 됨
task.send(20)     # callee 3: 20 출력 후 StopIteration exception 발생
```

> Coroutine은 generator와 yield 에서 값을 받을 수 있다는 것을 제외하고는 모든 것이 동일하다. [1]

<a href="https://stackoverflow.com/questions/715758/coroutine-vs-continuation-vs-generator" target="_blank">https://stackoverflow.com/questions/715758/coroutine-vs-continuation-vs-generator</a>
- A generator is essentially a cut down (asymmetric) coroutine. The difference between a coroutine and generator is that a coroutine can accept arguments after it's been initially called, whereas a generator can't.
- `continuation`은 또 뭐지....?




### yield from
- main - coroutine - subroutine (another coroutine) 의 구조일 시, coroutine에서 subroutine을 쉽게 쓸 수 있게 해 줌
- `yield`만 고려할 시엔 큰 문제가 없지만, `send`를 고려하게 되면 문제가 복잡해짐. 


[1] 의 예제
```python
def subcoroutine():
    print("Subcoroutine")
    x = yield 1
    print("Recv: " + str(x))
    x = yield 2
    print("Recv: " + str(x))

def coroutine():
    _i = subcoroutine()
    _x = next(_i)
    while True:
        _s = yield _x

        if _s is None: # 받아온 것이 없으므로 send가 아님
            _x = next(_i)
        else:          # 받아온 것이 있으므로 보내야 함
            _x = _i.send(_s)

x = coroutine()
next(x)
x.send(10)
x.send(20)
```

를
```python
def subcoroutine():
    print("Subcoroutine")
    x = yield 1
    print("Recv: " + str(x))
    x = yield 2
    print("Recv: " + str(x))

def coroutine():
    yield from subcoroutine()
```
로 바꿀 수 있다고 함 (?)


### PEP380 : generator에서 return 지원

```python
def test():
    yield 1
    return 10
```
는 실제로
```python
def test():
    yield 1
    e = StopIteration()
    e.value = 10
    raise e
```
와 같다고 함. 

- 추가이유 : sub-routine의 최종 결과물을 `yield from`에서 받아서 활용하기 위해
```python
def sum(max):
    tot = 0
    for i in range(max):
       tot += i
       yield tot
    return tot


def coroutine():
    x = yield from sum(10)
    print('Total: {}'.format(x))
```

- sub-routine인 `sum()`의 최종 결과물을 yield from에서 return 으로 받아 활용
- main에서는 중간결과들을 다 받을 수 있음
- > from [1] : 보통 coroutine 기반으로 lightweigth thread를 작성하는 경우 이와 같이 중간값 보다는 __다른 coroutine과 같이__ 돌다가 최종 결과를 받기를 원하는 경우이다. 이때 yield from의 return값을 사용하게 된다.
- > from [1] : 다음 장에서 나오게 될 asynio의 eventloop로 돌아가는 coroutine에서 yield from의 리턴값을 제대로 사용하게 된다. asyncio는 비동기로 모든 함수들이 실행된다. 특정 이벤트에 따라서 호출되는 것은 일반 callback 함수 일 수 있고, coroutine 일 수 있다. Coroutine은 위와 같이 yield from으로 다른 coroutine을 호출하여 결과를 비동기로 받을 수 있다 (하지만 코드를 보면 yield from 이라는 문장만 있지 생긴것은 sequential하게 되는 셈이고, 예외 처리도 sequential한 코드와 동일한 방식으로 처리가 가능하다).

