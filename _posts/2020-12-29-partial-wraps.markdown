---
layout: post
title:  "Python - partial, wraps, update_wrapper"
date:   2020-12-29 08:00:05 +0800
categories: python
use_math: true
tags: python coding
---

### functools.update_wrapper

<a href="https://www.geeksforgeeks.org/python-functools-update_wrapper/" target="_blank">https://www.geeksforgeeks.org/python-functools-update_wrapper/</a>

> Syntax:@functools.update_wrapper(wrapper, wrapped, assigned = WRAPPER_ASSIGNMENTS, updated = WRAPPER_UPDATES)  
Parameters:  
- wrapper: A wrapper function.
- wrapped: The function being wrapped over or the wrapped function.
- assigned: Attributes of the wrapped function which are assigned to the matching attributes of wrapper function as a tuple(optional argument).
- updated: Attributes of the wrapper function that are updated with respect to original function attributes as a tuple(optional argument).


- 

```python
import functools as ft 
  
  
# Defining the decorator 
def hi(func): 
      
    def wrapper(): 
        "Hi has taken over Hello Documentation"
        print("Hi geeks") 
        func() 
          
    # Note The following Steps Clearly 
    print("UPDATED WRAPPER DATA") 
    print(f'WRAPPER ASSIGNMENTS : {ft.WRAPPER_ASSIGNMENTS}') 
    print(f'UPDATES : {ft.WRAPPER_UPDATES}') 
      
    # Updating Metadata of wrapper  
    # using update_wrapper 
    ft.update_wrapper(wrapper, func) 
    return wrapper 
      
@hi
def hello(): 
    "this is the documentation of Hello Function"
    print("Hey Geeks") 
  
print(hello.__name__) # hello
print(hello.__doc__) # "this is the documentation of Hello Function"
help(hello) 
```

- __wrapped 함수의 metadata를 wrapper 함수에 덮어씌워 줌__



### functools.wrap and functools.partial
- <a href="https://www.geeksforgeeks.org/python-functools-wraps-function/" target="_blank">https://www.geeksforgeeks.org/python-functools-wraps-function/</a>
- we could use functools.wraps() as decorator __to wrapper function__.
- it is the nested decorator
- __returns partial function object of update_wrapper__

```python
def a_decorator(func): 

    @wraps(func) 
    def wrapper(*args, **kwargs): 
        """A wrapper function"""
  
        # Extend some capabilities of func 
        func() 
    
    #no need to call ft.update_wrapper(wrapper, func)
    return wrapper 
```

<a href="https://github.com/python/cpython/blob/master/Lib/functools.py#L65" target="_blank">implementation</a>

```python
def wraps(wrapped,
          assigned = WRAPPER_ASSIGNMENTS,
          updated = WRAPPER_UPDATES):
    """Decorator factory to apply update_wrapper() to a wrapper function
       Returns a decorator that invokes update_wrapper() with the decorated
       function as the wrapper argument and the arguments to wraps() as the
       remaining arguments. Default arguments are as for update_wrapper().
       This is a convenience function to simplify applying partial() to
       update_wrapper().
    """
    return partial(update_wrapper, wrapped=wrapped,
                   assigned=assigned, updated=updated)
```
- `WRAPPER_ASSIGNMENTS` default value : wrapper function’s __module__, __name__, __qualname__, __annotations__ and __doc__, the documentation string
- `WRAPPER_UPDATES` default value : wrapper function’s __dict__, i.e. the instance dictionary

you can see that, we have to use it in two steps.
  1. `wraps(wrapped)` returns a `partial` function object of `update_wrapper(wrapper=?, wrapped=wrapped)`
  2. we have to pass it the wrapped function, and rement arguments *args, **kwargs, __which gives below form of the convenient, function metadata preserving partial__


- <a href="https://github.com/tensorflow/tensor2tensor/blob/master/tensor2tensor/layers/common_attention.py" target="_blank">https://github.com/tensorflow/tensor2tensor/blob/master/tensor2tensor/layers/common_attention.py</a>

```python
def partial(fct, *args, **kwargs):
  """Same as functools.partial but with functools.wraps."""
  return functools.wraps(fct)(functools.partial(fct, *args, **kwargs))
```