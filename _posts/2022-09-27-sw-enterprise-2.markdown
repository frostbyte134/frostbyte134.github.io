---
layout: post
title:  "Patterns of Enterprise Application Architecture 3"
date:   2022-09-26 09:10:05 +0800
categories: coding
use_math: true
tags: coding
---

### 10 Data Source Architectural Patterns

#### Table Data Gateway

> On object acts as a gateway (466) to a database table. __One instance handles all the rows in the table__

- mixing SQL in app logic can cause several troubles
  - SRP violation
  - many programmers are not familiar with SQL logics
- simple(est) interface (several find methods and RUD)
- usually stateless (as its role is just push and retrieve)
- usually returns multiple records - problem in languages that supports only single return
  - map object: usually includes data copying
  - Data Transfer Object / Record Set can be used
- with `Domain Model`, one can return the approproiate domain object
  - bidirection dependencies between the domain obj and the gateway can happen
  - two are closely related so this is not the last thing one can do, but still not good
  - but better to use `Data Mapper`

example codes - 그냥 테이블별 CRUD 메소드를 구현한 stateless class

#### Row Data Gateway
embedding db access code in memory obj has few disadvs
- putting business logic + ad access code into single instance will increase complexity
- testing is awkward too, since if your in-memory objs are tied to a db, tests are slower to run b/c of all the db access

a `Row Data Gateway` acts as an obj that exactly mimics a single record, such as one db row
- where to put find method
  - static method -> bad with polymorphism. Better to seperate find method to another class (hierarchy)


good to use with Transaction Script (simplicity)
- for Domain Model, Active record (simple model) / Data Mapper (complex model, independent DB and domain logic)

#### Active Record

> On obj that wraps a row in a db table or view, encapsulates the db access, and adds domain logic on that data

- Active Record = Domain Model in which the class match closely the record structure of an underlying db
- Each Active Record is responsible for saving and loading to the db / and also for any domain logic that acts on the data
- the fields of active record exactly match that of db
- very similar to the `Row Data Gateway`, but active record contains small (and simple) domain logic


#### Data Mapper

> A layer of Mappers that moves data between objs and a db, while keeping them independent of each other and the mapper itself

resolves object-relation impedence 
- can ignore database
- extra layer that you don't get with active record


lazy load + association으로만 객체 로딩이 가능하게 할 수 있음 - 이 방법을 쓰면 object가 mapping layer를 어느정도 알아야 하는 듯
- 완벽한 분리 불가능? (need to know finders and other few)
- `seperated interface`를 써서, 도메인 모델이 finder interface만 갖고 매퍼에서 이거 가져다 구현은 매퍼 내부에 두는 식으로 하면 되는듯 (이게 의존성 역전이었나 뭐였지)
  - `seperatef finder` 예제
  - 그니까 이걸 하면 domain object가 finder behavior를 invoke할 수 있게 됨 (인터페이스 호출)

mapper need access to fields in the domain objs
- make fields private = crime
- in the same package = mapper를 알 필요 없는 것들 (도메인 오브젝트만 갖다쓰는) 것들에게도 매퍼 노출


when to create obj
- 한번에 다 = rich constructor
  - cyclic reference에서 문제 있음 (lazy load + empty obj로 대응 가능)

예시
- 반복적인 load many objs with condition (findbylastname) 을, sql string + parameter를 같이 가지는 인터페이스 (`StatementSource`)를 만들어서 중복제거 가능
- layer subtype이 자주 활용됨


### Chap 11. Obj-Relational Behavioral Patterns
- UOW, lazy load, identity mapping

#### UOW

> maintain a list of objs affected by a business transaction and coordinates the writing out of chanes and the resolution of concurrency problems

obj의 변경 (CRUD)에 따른 db write에 대한 책임을 전부 갖는 객체

- keep track of changes (in active or passive ways)
- commit at the end (in explicit / implicit ways)

2 ways
- caller registeration: 호출한 쪽 (객체를 만든 context)에서 등록
- object registeration: 객체 자체에서 알아서 등록 (대신 뭔가 UOW에 대한 레퍼런스를 갖고 있어야 할 듯)
- UOW controller: handles all reads from DB, and register clean objs when needed (? 이건 잚 ㅗ르계씅ㅁ)

db가 referential integrity를 체크할 때 - UOW에서 마지막 커밋할 떄 체크하면 좋음
batch update에도 좋음 (비즈니스 트랜잭션 하나에서 일어난 것들을 배치업데이트 가능한 듯)
works with any transactional resources

the fundamental problem othat UOW deals with is keeping track of the various objs manipulated, so that you know which ones you need to consider to sync your in-memory data with db

예제
- 그냥..객체 리스트 (new / dirty / removed) 갖고있고, 여기에 대한 등록 관리
- identity map을 포함하는 경우 - 여기에 등록
- commit method도 있음 (있을 시 transaction 열고 한번에 커밋하면 되는 듯)

#### Identity map

> Ensures that each obj gets loaded only once by keeping every loaded obj in a map. Looks up objs using the map when referring to them.

- db에 있는 객체와 메모리에 있는 객체간 1:1을 유지하고 싶어서 (1:N은 피곤)
- 캐시역할도

#### Lazy load

> An obj that doesnt contain all of the data you need but knows how to get it

음..일단 스킵 ㄷㄷ 잠자야겠다


느낀점
- 무의식적으로 table data gateway 느낌의 클래스들을 막 써왔던 듯 (stargate.admin의 database class, recruit.app의 db class)