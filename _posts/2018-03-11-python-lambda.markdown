---
layout: post
title:  "Python - lambda, expressions, statemets"
date:   2018-03-11 13:59:00
categories: python
use_math: true
tags: python
---

```python
lambda arguments: expression
```
is equivalent to
```python
def name(arguments):
    return expression
```

```Expression``` in python includes
- arithmetic
- unary, binary, boolean, comparison operations
- List comprehensions and generator operations

```Statements``` in python is composed of simple statement, which is a superset of expression, and compound statements.  
Simple statements include
- assignment
- call to functions
- pass, del, print, return, yield, raise, break, continue, import, global, and exec
Compound statements includes
- if, while, for, try, with def, and class.

A lambda expression may have a ```conditional expression``` (ternary operation in C++) in it,
```python
is_pos = lambda x: 'pos' if x>=0 else 'neg'
```
but it ```cannot have a if``` statement
```python
is_pos2 = lambda x: if x>=0: 'pos'
```
above statement will not be compiled, with SyntaxError