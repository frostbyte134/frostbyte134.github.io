---
layout: post
title:  "Python - coroutine (native)"
date:   2020-09-10 09:10:05 +0800
categories: python
use_math: true
tags: python coding
---

### Reference pages
- <a href="https://blog.humminglab.io/python-coroutine-programming-2/" target="_blank">https://blog.humminglab.io/python-coroutine-programming-2/</a> [1]


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


<a href="https://nailbrainz.github.io/coding/2020/03/01/asyncio.html" target="_blank">이거랑 잘 합쳐봐야 할듯</a>