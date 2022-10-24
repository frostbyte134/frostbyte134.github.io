---
layout: post
title:  "Patterns of Enterprise APP Architecture 4"
date:   2022-09-26 09:10:05 +0800
categories: coding
use_math: true
tags: coding
---

### Chap 12 - Object-Relational Structural Patterns


#### Identity field
> saves a db id field in an object to maintain identity between an in-memory obj and a a db row

what kind of key to use
1. meaningful vs meaningless
  - human makes mistakes. meaningful to human - someday one can make mistake. meaningless is better
2. simple key vs compount key
  - with simple key, you can reuse simple logics in many places
3. string vs int -> int is better for performance

when an object will not be saved to db, better put 'PLACEHOLDER_ID' (default dummy value) to identity field, if the programming language does not support empty field


### 느낀점
- 돌아다니다 몽고디비 락에 대한 설명을 봤는데, 이 책 pessimistic lock과 완전 동일해서 신기했음 http://mongodb.citsoft.net/?page_id=187
- 솔직히 compount key java example 부분은 안봤음. 나중에 이게 필요할 때 생각나면 보러 갈 듯 ㅋㅋ
