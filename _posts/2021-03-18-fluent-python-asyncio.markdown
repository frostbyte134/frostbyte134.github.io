---
layout: post
title:  "Fluent python asyncio - Chap 16,17,18"
date:   2021-03-16 08:00:05 +0800
categories: coding
use_math: true
tags: python asyncio
---

### Chap 16

> We find two main senses for the verb “to yield” in dictionaries: to produce or to give way. Both senses apply in Python when we use the yield keyword in a generator.

- A line such as `yield item` produces a value that is received by the caller of next(…), and
- it also gives way, suspending the execution of the generator so that the caller may proceed until it’s ready to consume another value by invoking `next()` again. The caller pulls values from the generator.


A coroutine is syntactically like a generator: just a function with the yield keyword in its body. 
- However, in a coroutine, yield usually appears on the right side of an expression (e.g., `datum = yield`), and 
- it may or may not produce a value — if there is no expression after the yield keyword, the generator yields None. 
- The coroutine may receive data from the caller, which uses .send( datum) instead of next(…) to feed the coroutine. Usually, the caller pushes values into the coroutine.


`coroutine`: a procedure that collaborates with the caller, yielding and receiving values from the caller. (by the `send()`, `yield`)