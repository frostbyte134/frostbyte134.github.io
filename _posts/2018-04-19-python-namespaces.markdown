---
layout: post
title:  "Python namespaces"
date:   2018-04-19 20:04:00
categories: python
use_math: true
tags: python
---

```python
d = 50 # global variable
class Myclass(object):
    x = 10 # class variable
    def func(self):
        y = 20 # (function) local variable
        print(self.x) # self, but referencing class variable. is equiv to print(type(self).x)
        self.x = 24 # instance attribute  is defined. 
        print('self.x = ' + str(self.x)) #self first references instance attribute, then class attribute.
        self.z = 30 # instance attribute is defined


if __name__=='__main__':
    a = Myclass()
    # print(a.y) # just can't do it
    
    # print(a.z) instance varialbe z not yer defined
    a.func()
    print(a.z)
    
    # print(a.func.y) # just can't do it 2. namespace of a function get removed after execution.
    
    b = Myclass() 
    print('(a.x, b.x) = ({0}, {1})'.format(a.x, b.x)) # for b, instance attribute is not yet defined.
    Myclass.x = 128
    print('(a.x, b.x) = ({0}, {1})'.format(a.x, b.x))  
```

* referencing an attribute with <attrName> inside a class function only searches in local (of the function) and global namespaces.
* To reference a (instance, class) attributes inside a class function, you need identifier <instanceName \| className | self>.<attrName>
* <self>.<attrName> firsts finds instance attributes, then searches for class attributes.
* <className>.<attrName> only finds the class attrs.