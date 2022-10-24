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

#### Foreign Key Mapping
Maps anassociation between objects to a foreign key reference between tables

1:N 일 경우 사용가능, N:M일떈 포린키 사용 자체가 불가능 (association table)
- 이 때 업데이트가 피곤함
  - 다 삭제 + 새로 생성 -> 다른 테이블에 의해 ref안될때만 가능
  - diff - 변경점만 디프 떠서 업데이트?

오브젝트 로딩 사이클에 빠질 수 있음 - 잘 해결 (empty object를 일단 놓기?)

#### Association Table Mapping
Saves an association as a table with foreign keys to the tables that are linked by the association

별도 테이블 두기 (p-key 필요없음. pair of foreign key자체가 pk)
- 조인으로 다수의 쿼리를 한방에 대체가능 - 더러워서 자주 쓰긴 뭐함 (효율적이여야 할 때만)
- 기존 객체끼리 연결하고 싶은데, 컬럼을 추가하고 싶지 않을 때

예제 - 그냥 N:N, 다수의 1:N 로딩 (where), 조인한 테이블에서 한방에 로딩 등에 대한 mapper 예제
### 느낀점
- 돌아다니다 몽고디비 락에 대한 설명을 봤는데, 이 책 pessimistic lock과 완전 동일해서 신기했음 http://mongodb.citsoft.net/?page_id=187
- 솔직히 compount key java example 부분은 안봤음. 나중에 이게 필요할 때 생각나면 보러 갈 듯 ㅋㅋ

