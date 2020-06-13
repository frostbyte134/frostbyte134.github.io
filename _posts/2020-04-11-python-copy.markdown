---
layout: post
title:  "Python - copy"
date:   2020-04-10 05:04:00 +0900
categories: coding
use_math: true
tags: coding python
---
<a href="https://blueshw.github.io/2016/01/20/shallow-copy-deep-copy/" target="_blank">https://blueshw.github.io/2016/01/20/shallow-copy-deep-copy/</a>
<a href="https://tech.ssut.me/new-interesting-data-structures-in-python-3/" target="_blank">https://tech.ssut.me/new-interesting-data-structures-in-python-3/</a>

맨날 해깔려서...

__대입 연산__시
1. immutable객체 - 얕은 복사가 진행됨. immutable 내부의 mutable객체는 복사가 진행되지 않고 reference가 만들어짐
2. mutable 객체 - reference가 만들어짐

immutable 객체 내에 mutable 객체가 있을 시 `([1, 2], [3, 4])`
1. 대입 연산을 하면 얕은 복사가 진행됨
2. copy.deepcopy를 한 뒤 이걸로 생긴 객체를 print해보니 그 때 `ideone`에서 런타임 에러 발생. 왜이러지?


<a href="https://zzsza.github.io/development/2018/08/25/python-object/" target="_blank">https://zzsza.github.io/development/2018/08/25/python-object/</a> 마지막 예제 좋네