---
layout: post
title:  "Python - Functions"
date:   2018-03-15 16:04:00
categories: python
use_math: true
tags: python
---

## Variable Parameters * (keyword variable parameters **)  
Variable parameters allow a function to take an arbitrary number of position based arguments. It needn't be named as `*args`. Inside the function, the variable args (without an *) will be a tuple containing all the arguments.

`*` is also used for flattening (splatting). Example is as follows.  
```python
def demo_args(*args):
    print(str(type(args)) + str(args))

vars = ['john', 'foo']
demo_args(vars[0], vars[1]) #('john', 'foo')
demo_args(vars)             #(['john', 'foo'],)
demo_args(*vars)            #('john', 'foo')
```

If a function has normal, keyword, and variable parameters, the sequence will populate the 
1. normal parameters,
2. keyword parameters, and 
3. left over variables will be pass to the variable argument.  

```python
def func(a, b='b', *args):
    print([x for x in [a, b, args]])

func(*(3, 4, 5, 6, 7, 8))   #[3, 4, (5, 6, 7, 8)]
```
<br/>
## Higher-Order function
refers to a function which takes functions as argmuents, or returns functions.
Remember that the functions are first-class citizen in Python.
<br/><br/>
## Mutable type as default parameter is not good
Default parameters are initialized during function definition (global function - module load time, inner function - runtime). After initialization, they are stored in the `__defaults__` attributes.
If we modify the value of such mutable default parameters, the values remains changed from values we set in the definition.