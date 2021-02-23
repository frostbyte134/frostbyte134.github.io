---
layout: post
title:  "Fluent Python (Chap 1, 3, 4)"
date:   2020-12-20 08:00:05 +0800
categories: coding
use_math: true
tags: coding python
---

> Ramalho, Luciano. Fluent Python. O'Reilly Media. Kindle Edition. 



### Chap 1. The Python Data Model

<a href="https://docs.python.org/3/reference/datamodel.html" target="_blank">Python data models</a>
- if you learned another object-oriented language before Python, you may have found it strange to use `len(collection)` instead of `collection.len()`.
  - `Python data model` = key to everything we call `Pythonic`
- `dunder` methods = `__getitem__`
- implement `__getitem__`, `__len__` dunders and you will be able to perform
  - indexing `deck[0]`
  - random selection  
    ```python
    from random import choice
    choice( deck)
    ```
  - iteration  
    ```Python
    for card in deck:
      print( card)
    ```
  - inclusion test (if `__contains__` method is not implemented, then `in` __operator does a sequential scan__ )
    ```Python
    >>> Card(' Q', 'hearts') in deck
    True
    ```
  - how about __shuffling__ : currently the object is immutable (it is based on a list). There will be a one-liner `__setitem__` method in chap11.
- for built-in types like list, str, bytearray, and so on, __the interpreter takes a shortcut:__
  - the CPython implementation of len() actually returns the value of the ob_size field in the PyVarObject C struct that represents any variable-sized built-in object in memory. This is much faster than calling a method.
- If you need to invoke a special method, it is usually better to call the related built-in function
  - e.g., call len to implicitly call __len__
- CPython implementation detail: For CPython, id(x) is the memory address where x is stored.

#### String representation
```Python
def __repr__( self):
  return 'Vector(% r, %r)' % (self.x, self.y) 
```
- using `%r` is a good practice (because it shows the crucial difference between Vector( 1, 2) and Vector(' 1', '2'))
- On Wikipedia, the first definition of object model is “The properties of objects in general in a specific computer programming language.” This is what the “Python data model” is about.

### Chap 3
<img src="{{site.url}}/images/coding/python/hash.jpg" width="800">

<a href="https://docs.python.org/3/glossary.html#term-hashable" target="_blank">What is hashable?</a> An object is hashable if
- `__hash__()` : it has a hash value which never changes during its lifetime
- `__eq__()` : can be compared to other objects
- __User-defined types are hashable by default__ because their hash value is their id() and __they all compare not equal.__ If an object implements a custom __eq__ that takes into account its internal state, it may be hashable only if all its attributes are immutable.


#### Hash table in Dictionaries
1. A `hash table` is a sparse array
- item = `buckets`
  -  a bucket for each item contains 2 fields: __a reference to the key__ and __a reference to the value__ of the item. 
  -  all buckets have the same size \\(\rightarrow\\) access by offset.
  -  Python tries to keep at least 1/3 of the buckets empty; hash table too crowded \\(\rightarrow\\) copied to a new location with more buckets.
2. The `hash()` built-in function calls `__hash__` for user-defined types. 
  - If two objects compare equal, their hash values must also be equal, otherwise the hash table algorithm does not work
    - ex) because 1 == 1.0 is true, hash( 1) == hash( 1.0) must also be true, even though the internal repr of an int and a float are very different.
  - __to be effective as hash table indexes, hash values should scatter around the index space as much as possible__
    - ideally, objects that are similar but not equal should have hash values that differ widely.
    - Starting with Python 3.3, `a random salt value` is added to the hashes of str, bytes, and datetime objects. The salt value is constant within a Python process but varies between interpreter runs. The random salt is a security measure to prevent a DOS attack. Details are in a note in the documentation for the __hash__ special method.
3. Hash table algorithm
  - to get the value of my_dict[search_key]
      1. Python calls `hash(search_key)` to obtain the hash val of search_key
      2. and uses the __least significant bits__ of that hash val as an offset, to look up a bucket in the hash table (the number of bits varies)
      3. If the found bucket is empty, `KeyError` is raised
      4. Otherwise, the found bucket has an item — a found_key:found_value pair — and then Python checks whether search_key == found_key
         1. If they match, that was the item sought: found_value is returned.
         2. if search_key and found_key do not match, this is a __hash collision__
            - This happens because a hash function maps arbitrary objects to a small number of bits, and — in addition — the hash table is indexed with a subset of those bits
            - to resolve it, iterate through other `candidate key`. Generation of candidate key differs from the algorithm (like, adding some prime num)
              - if next candidate key is empty, then we again have `KeyError`
              - if we found the matching key, possibly with few hash collision, we return the value
  - insert = equivalent, except that we want to find empty bucket
  - refer to the `hasing (pseudo-random)` codes in <a href="{{site.url}}/problem_solving/2020/07/24/ps-codebase.html" target="_blank">this page</a>
4. For custom object to be hasable,
  - It supports the hash() function via a __hash__() method that always returns the same value over the lifetime of the object.
  - It supports equality via an __eq__() method. If a == b is True then hash(a) == hash(b) must also be True.
  - If a == b is True then hash(a) == hash(b) must also be True. (important!)
5. results
  - bucket array requires __sparsity__ : has (significant) memory overload
  - key search is fast
  - key ordering (low order = less collision) depends on the insertion order
  - adding item might occur reordering (copying to new, large bucket array for sparsity)
 

#### Chap 4. Text vs Bytes
 - string : sequence of characters
 - `unicode` : how to represent characters, as a number from 0 to 1,114,111
   - ex) A = U+0041
 - encoding (such as UTF8, UTF16) : how to encode the unicode into byte
   - `UTF-8` : for english + basic chars, compatible with `ASCII`
   - `UTF-16` : for eng+basic chars, uses additional dummy 1byte (0) to least significant bits

byte data
- `bytes` : immutable, `bytearray` : mutable
  - both uses new memory space when generating them from any file/string
- `memoryview` does not allocates new memory space