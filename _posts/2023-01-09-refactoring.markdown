---
layout: post
title:  "refactoring"
date:   2023-01-09 07:00:05 +0800
categories: coding
use_math: true
tags: coding
---

아..집에있던거 커밋을 안하고 왔네 ㅋㅋ

> Fowler, Martin. Refactoring (Addison-Wesley Signature Series (Fowler)) (p. 33). Pearson Education. Kindle Edition.


### Chap 1

When you have to add a feature to a program but the code is not structured in a convenient way, first refactor the program to make it easy to add the feature, then add the feature.
- 이번에 어드민 리팩토링 하는데 진짜 맞말 같음. 구조가 안좋으니까 한번에 바꿔야 하는 것의 범위가 너무 불확실하고 큼. 테스트 더하기도 어렵고...

ensure to a solid set of tests for the refactoring target code
- easier said...reality bites.
- refactoring changes the program in small steps (easier to find the cause of mistake)

파라미터가 없는 함수 극혐인데 (특히 오록스 보면서 좀 많았음), 중간 코드긴 하지만 자주 보인 듯

variable names are a key to clear code
- breaking a large function into smaller ones only adds value if the names are good (no need to peek into details if names are good)
- not easy to get good names right the first time -> need continous refactoring (least twice)

replaced few local variables to inline calls
- "it makes it much easier to do extractions, since there is less local scope to deal with"
- temp vars are only useful within their own routine, and therefore they encourge long, complex (own) routines - "i prefer to replace with a declared function"

JS - [object.assign](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Object/assign) = shallow copy over 1 level enumerable
