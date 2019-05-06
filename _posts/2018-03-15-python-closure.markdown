---
layout: post
title:  "Python - closures"
date:   2018-03-15 16:04:00
categories: python
use_math: true
tags: python
---

>Wikipedia: Closure is a function, together with a referencing environment for the non-local variables of that function.

A closure in Python is simply a function returned by another function.
In Python, a function can return new functions. The inner function is a closure, and any variable it accesses that are defined outside of that function are free variables.

Closure quickly enable generation of functions and conforming to an interface (the adapter pattern)
```python
def name_filter(name):
    def inner(row):
        if row['name'].lower() == name.lower():
            return row
    return inner

paul_filter = name_filter('Paul')
john_filter = name_filter('John')

def or_op(filters):
    def inner(row):
        for f in filters:
            if f(row):
                return row #implementation of short circuit operation

    return inner

beatle = or_op([paul_filter, john_filter])
print(beatle({'name':'asd'}))
```