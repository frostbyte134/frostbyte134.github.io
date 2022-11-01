---
layout: post
title:  "Patterns of Enterprise Application Architecture 4"
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


#### dependent mapping
has one class perform the database mapping for a child class
- 일부 object는 자연스럽게 특정 다른 오브젝트와 의존관계를 맺음 (앨범 - 트랙). 이 객체들이 다른 것들과 연관이 없을 시, album mapper가 track mapper도 포함하게 해서 동작 단순화 (...)

The basic idea behind it is that, one class (the dependent) relies upon some other class (the owner) for its database persistence. Each dependent can, and must have one owner
- This (must have  one dependent) manifests
  - for active recore/row data gataway, dependent class wont have any db code (its in the owner)
  - with data mapper, mapping code is in the owner   

UML - composition!

#### Serialized LOB
save a graph of objects by serializing them into a single large object (LOB), which it stores in a db field

#### Single Table Inheritance
Represnets an inheritance hierarchy of classes as a single table that has columns for all the fields of the various classes

상속구조의 모든 변수들을 단일 테이블에 저장 (join 최소화)
- loading into memory - need a column specifying class (in the inheritance hiararchy)
- loading data - read the code first to determine class
- on saving data -> the code need to be written by superclass?

pros - single table, no joints
cons - some fields are sometimes be null, wasted space in db

구현
- mapper - abstract player mapper - footballer/cricketer mapper 에서 find, save, load 구현
  - footballer는 자신의 type code 반환 - 디비의 타입 컬럼과 맞춰 보는 듯
- player mapper = mapper상속받으나 (왜?), footballer/cricketer mapper 컴포지션으로 보유 


#### Class Table Inheritance
Represents an inheritance hierarchy of classes with one table for each class

- one tip = common primary key
- biggest issue = load data from multiple table. Outer join can help (to rule out empty table) but sometimes not enough

#### Concrete table inheritance
- concrete class 별로 테이블 1개
- why worst?

abstract class는 테이블이 없음 - 다른 테이블의 객체와 abstract class가 foreign key로 연결되어 있을 때, referential integrity를 유지하려면 매핑 테이블이 필요한데, abstract class 테이블이 없어서 개 피곤해짐 (클래스 하나 추가하기라도 하면....)

pros = each table contains no null attr, no join required
cons - difficult to handle primary key,k cant enforce db relationship to abstract class, not easy to change abstract class
- a find on the superclass (which is entirely valid) makes awkward join or multiple table search

#### Inheritance Mapper
a structure to organize db mappers that handle inheritance hierarchies
- minimize save and load (for the class hierarchy)
- provide both abstract and concrete mapping behavior to save/load superclass or a subclass

### 느낀점
- 이거 sqlalchemy 쓰면 대충 돌아는 가는 거 아닌가 하다가..옛날 개발자들이 object-relational impedence mismatch 때문에 고민한 흔적이라고 생각하기로 했음 
  - 상속 쪽은 https://docs.sqlalchemy.org/en/14/orm/inheritance.html 읽어보니까 이해가 좀 된 듯
- data mapper 예제들 솔직히 다 보진 않았음. 나중에, 예를들면 coumpound key 를 쓸 때 생각나면 보러 갈 듯 ㅋㅋ
- 번외) 돌아다니다 몽고디비 락에 대한 설명을 봤는데, 이 책 pessimistic lock과 완전 동일해서 신기했음 http://mongodb.citsoft.net/?page_id=187
- https://stackoverflow.com/questions/1337095/sqlalchemy-inheritance
- 결국 키는 guid vs auto-increment?

--------------

### Chap13 Object-Relational Metadata Mapping Patterns
#### Metadata mapping
> holds details of object-relational mapping in metadata

`code generation`: write a program whose input=metadata, output=source code of class that do the mapping (?)
- generated cod should not be edited by hand, no need to be in source code control

`reflective program`: ask an obj for a method named setName, and then run an invoke method on the setName method passing in the appropriate argument
- can read in field and method names from a metadata file, and use them to carry out the mapping
- more dynamic. but slow and hard to debug

mapping changes should be rare, involves db schema changing

on most occasions you keep the metadata in a seperate file format (XML? nowadays yaml or json perhaps)

when to use - `Metadata mapping` can greatly reduce the work needed to handle db mapping. However some setup is requred (metadata mapping framework)

#### Query Object
An object that represents a db query
- application of the interpreter pattern geared to represent a SQL query
- allow client to form queries of various kinds, and to turn those obj structures into the appropriate SQL string

- easy to extend - can start with simple query object 
- represent queries in the language of the in-memory objs rather than the db schema
- instead of using table and column names, you can use (domain) obj and field names in the query obj
  - to perform the change of view (from domain to db), it needs to know how the db structure maps to the obj structure - `metadata maping` (damn)

when to use
- quite complex - one dont use them with hand built data layer. you really need them with domain model and data mapper
- advs: keep db encapsulated (schema encapsulated, support multiple dbs, schemas, optimization, ...)


interpreter pattern 찾으러 갔다가 리팩토링구루에서 없는거 보고 ㅌㅌ함
그냥...도메인 객체로 날린 쿼리를 db 쿼리로 바꿔주는 무언가...?


#### Repository
Mediates between the domain and data mapping layers usng a collection like interface for accessing domain objects

다 명문이라 걍 읽어볼 만 함
- a layer isolates domain objects from details of the db access code (good for complex domain model)
  - __abstraction over the mapping layer__
  - especly good with large/many domain classess / heavy querying, by minimizing duplication
- `repository` mediates between the domain and data mapping layers, acting like an in-memory domain obj collection
- client construct query __declaritively__ (!), submit them to repository
- obj can be added/removed from the repository (like collection), and the mapping code inside repository will do the work inside
- conceptually, `repository` encapsulates set of objs persisted in data source and (mapping) operations over them, providing more object-oriented view of the persistence layer
- helps for clean seperation + one way dependency between the domain and data mapping layers 
- combines `metadata mapping` with `query object` (?!)
  - criteria know how to add themselvs to a query, the query obj knows how to incorporate criteria objs, the metadata mapping controls the interaction in implementation detail

helps for multiple source - in-memory for unit testing, db for real
- __clients never need to think in SQL and can write code purely in terms of objects__
- 예시 - strategy pattern (in-memory / relational), composition with repository object

### Chap 14 Web Presentation Patterns

#### Model View Controller
Mvc considers 3 roles
- `model`
  - obj that represents domain. Nonvisual obj. In its most pure form it is domain model. Transaction script is also one of the model.
- `view` = rpresnets the display of the model in the UI (restricted to it)
- `controller` - any changes to the infomation are handled (sits between model and the view)
  - takes user input, manipulates the model, and cause view to update appropriately
  - __UI is the combination of the view and the controller__

Two principle separation in MVC
1. separating the presentation from the model - the most fundamental heuristocs of good sw design
  - view: UI, presentation
  - model: business policies, db interactions
  - can present same model in many different ways
  - key point - direction of the dependencies (presentation ->(depends on) model, not the other way)
    - usually many presentation depends on one model - to apply change at the same time on many presentations (without creating dependency on the other way) one need things like `observer pattern` 
2. separating the controller from the view
  - good for editable/non-editable behavior (strategy pattern, editable/non-editable strategy)

### 느낀점
metadata mapping은 잘 안쓰이는 느낌?
query object는 interpreter pattern - 뭔지 기억이 안나서 refactoring guru에 갔더니 없음 ㅋㅋ https://feedback.refactoring.guru/communities/3/topics/702-missing-interpreter-pattern-in-behavioral-section
repository - 평소에 별 생각 없이 abstract repository 만들고 메모리/디비 구현하고 테스트 짜야지...?했는데, 바텀업부터 배운 느낌이라 좋았음

view와 controller의 경계가 다소 불명확한듯...?

- application of the interpreter pattern geared to represent a SQL query
