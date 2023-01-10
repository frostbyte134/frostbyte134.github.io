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



variable names are a key to clear code
- breaking a large function into smaller ones only adds value if the names are good (no need to peek into details if names are good)
- not easy to get good names right the first time -> need continous refactoring (least twice)

replaced few local variables to inline calls
- "it makes it much easier to do extractions, since there is less local scope to deal with"
- temp vars are only useful within their own routine, and therefore they encourge long, complex (own) routines - "i prefer to replace with a declared function"

JS - [object.assign](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Object/assign) = shallow copy over 1 level enumerable

conditional to polymorphic
- if-else문을 객체 생성 안으로 몰아넣는거 아닌가 싶긴 하지만.. -> 이 상속구조에 기대는 코드들이 더 생길수록 이득이라는 듯
- 일단 로직의 위치를 옮기고, 다음 상속구조에 따른 polymorphic change를 적용하는듯 (나였으면 상속구조부터 짰을 듯...)

> I believe, however, that we can go beyond taste and say that the true test of good code is how easy it is to change it

small steps are key
- in this case: decomposing into small, nested functions (with good names) -> use Split Phase (?) to seperate the calc/printing -> introduce polymorphism
- but what if a big bunch of codes depends on many external resources?zz

느낀점
- 리액트 공부중이라 자바스크립트인게 좋은 듯
- 파라미터가 없는 함수 좀 그런데 (특히 오록스 보면서 좀 많았음. 난 사이드 이펙트다 라는 느낌. 코드 보기도 어려움), 중간 코드긴 하지만 자주 보인 듯.
- 코드에도 줄넘어갈때마다 하이픈 붙는것때문에 좀 그럼...
