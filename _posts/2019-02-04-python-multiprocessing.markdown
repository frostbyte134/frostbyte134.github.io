---
layout: post
title:  "Python multiprocessing (threading) examples"
date:   2019-02-04 08:59:00
categories: python
use_math: true
tags: multiprocessing multithreading cotyledon futures
---

Summary
* multithreading: useful with io bottleneck, low context switch overhead
* multiprocessing.pool: most convenient
* `futurist`: `wait_for_all` seems familier (java on android)
* `cotyledon`: management for the worker lifecycle (producer / consumer), can send signal and change behavior (example in the book)

```python
import random
import threading
import time

to = 1000000
end = time.time()
```


### Multithreading
```python
results = []
def compute():
    results.append(sum([random.randint(1, 100) for i in range(to)]))

workers = [threading.Thread(target=compute) for x in range(8)]
for worker in workers:
    worker.start()
for worker in workers:
    worker.join()

print("Resluts :", results)
print('time = {}'.format(time.time() - end))
```

### Multiprocessing
```python
import multiprocessing

def compute(results):
    results.append(sum([random.randint(1, 100) for _ in range(to)]))

with multiprocessing.Manager() as manager:
    results = manager.list()
    workers = [multiprocessing.Process(target=compute, args=(results,)) for _ in range(8)]

    for worker in workers:
        worker.start()
    for worker in workers:
        worker.join()
    

    print("Resluts :", results)
    print('time = {}'.format(time.time() - end))
```


### mp pool
```python
import multiprocessing
def compute(n):
    return sum([random.randint(1, 100) for _ in range(to)])

pool = multiprocessing.Pool(processes=8)
rlt = pool.map(compute, range(8))
print(type(rlt))
print("rlt = ", rlt)
print('time = {}'.format(time.time() - end))
```

### future
```python
futures
from concurrent import futures
import random

def compute():
    return sum([
        random.randint(1, 100) for i in range(to)
    ])

with futures.ProcessPoolExecutor(max_workers=8) as executor: #ThreadPoolExecutor
    futures = [executor.submit(compute) for _ in range(8)]

import multiprocessing
print("cpus = ", multiprocessing.cpu_count())
results = [f.result() for f in futures]
print("rlt = ", results)
print('time = {}'.format(time.time() - end))
```

### futurist
```python
import futurist
from futurist import waiters
import random

def compute():
    return sum([
        random.randint(1, 100) for i in range(to)
    ])


with futurist.ThreadPoolExecutor(max_workers=8) as executor:
    futures = [executor.submit(compute) for _ in range(8)]
    print(executor.statistics)

results = waiters.wait_for_all(futures)
print(executor.statistics)

print("results : ", [r.result() for r in results.done])
```


### cotyledon
send SIGHUP (signal hang up) like
> `kill -HUP pid`

```python
import cotyledon
import multiprocessing
class Manager(cotyledon.ServiceManager):
    def __init__(self):
        super(Manager, self).__init__()
        queue = multiprocessing.Manager().Queue()
        self.add(ProducerService, args=(queue,))
        #self.add(PrinterService, args=(queue,), workers=2)
        self.printer = self.add(PrinterService, args=(queue,), workers=2)
        self.register_hooks(on_reload=self.reload)
	
	def reload(self):
        print("reloading")
        self.reconfigure(self.printer, 5) # ??

class ProducerService(cotyledon.Service):
    def __init__(self, worker_id, queue):
        super(ProducerService, self).__init__(worker_id)
        self.queue = queue
    
    def run(self):
        i = 0
        while True:
            self.queue.put(i)
            i += 1
            time.sleep(1)

class PrinterService(cotyledon.Service):
    name = "printer"
    def __init__(self, worker_id, queue):
        super(PrinterService, self).__init__(worker_id)
        self.queue = queue
    
    def run(self):
        while True:
            job = self.queue.get(block=True)
            print("I am worker #{}, PID:{} and I hereby print {}".format(self.worker_id, self.pid, job))

Manager().run()
```

reference: The Hacker's guide to scaling python programming