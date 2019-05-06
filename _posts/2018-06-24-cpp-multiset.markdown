---
layout: post
title:  "C++ Set"
date:   2018-06-23 08:45:05 +0800
categories: coding
use_math: true
tags: problem_solving coding c++
problem: 1107
---

`set` vs `multiset`: multiset allows duplication

### Declaration and Usage
```c++
#include <set>
multiset<int> bags;
bags.insert(val);
S.erase(val);
```

### lower_bound
returns first element in [First,last), or `set.end()` (can be used in any STL with comparion method < is defined)
```c++
multiset<int>::iterator iter = bags.lower_bound(gems[i].second);
if(iter != bags.end()){
	//do something
}
```