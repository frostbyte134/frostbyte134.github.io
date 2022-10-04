---
layout: post
title:  "Patterns of Enterprise APP Architecture 2"
date:   2020-09-26 09:10:05 +0800
categories: coding
use_math: true
tags: coding
---

### Chap 5 Concurrency
- concurrency is hard - not easy to enumerate all scenarios / hard to test for
- `transaction` helps us to avoid many tricky aspects of concurrency in enterprise APPs
  - `offline concurrency`: concurrency control for data thats manipulated during multiple database transactions
    - managing concurency when data spans multiple transactions

#### Essential Problems of Concurrency
- `Lost Update` = A - B - B end - A end -> work of B become lost when A commit
- `Inconsistent read`
  - b4 work - A works - B works - B ends - A still reads and works - A commits - after work
  - read of A is inconsistent 
- `liveness`: how much concurrent activity can go on


#### Execution Contexts
2 import contexts (from the perspective of interacting outer works)
- `request`: can be blocking / non-blocking (cancel must be issued with another request)
- `session`: long-running interaction between a client and a server, commonly consists of a series of reqs
  - server SW may have multiple sessions: HTTPs with client and DBs with many dbs

2 import terms from OS
- threads: lightweighted, shares memory (some provided isolated threads)
- process: heavy, isolated in nature. Issuing process for each req is deprecated, but serving 1 req with 1 proc is quite common

`transaction`: pull together several requests that the cli wants reated as if thery were a single request
- can occur from Apps to DBs (a `system transaction`)
- or from the user to an App (a `business transaction`)

#### Isolation and Immutability
- 2 import solutions for the problem of concurrency

1. `isolation`: partition the data, so that any piece of it can only be accessed by one active agent
  - processes work like this in OS memory / file locks
  - reduces the chance of errors
2. when data are not changed, we dont need to worry about concurrency - `immutable`
  - of course not all data can be immutable, but identifying ones helps us alot

#### Optimistic / Pessimistic Concurrency Control
1. optimistic - allow concurrent editing, accept only one (conflict detection)
  - lock is only held during commit
  - everyone (involved in conflict) has to checkout and commit newer version
    - good enough for code control (with auto merge) but business data is often too complicate and restrictive for auto merge
2. pessimistic - only allow one to edit (conflict prevention)
  - reduces concurrency


Preventing Inconsistent Read
- pessimistic - read lock (many locks, but when someone has read lock nobody can get write locks, only additional read locks are possible) / write lock (exclusive)
- optimistic - version marker on the data (GIT?)
  - timestamp / sequential counter / (doesnt git uses hash?)
  - comparing marker on every file is often a burden - discriminate read / modified file/data


Deadlocks
- problems in pessimistic techniques (when two have read lock each and want to get write lock at the same time)
- timeout / detection and select victims
- not easy - enterprise app often relies on transactions

#### Transactions
- __a bounded seqeunce of work__ (start, end are well defined)
- all participating resources must be in consistent state, both in begin / end
- __all or nothing__

SW transactions are often described in terms of the `ACID` properties
- Atomicity: all or nothing (for all steps)
- Consistency: resources must be consistent, both the start and end
- isolation: the result of an individual steps must not be visible to any other open transactions, until it commits
- durability: any result of commit must be made permanent

Transactional Resources
- DB / msg queues / printers / ...
- anty source that uses transactions to control concurrency
- = database in this book (so every time we say database, it uses transaction)
- `long transaction`: spans multiple requests, problematicsd
- `request transation`: simple model
  - `late transaction`: open as late as possible

When using transactions, it is good to know what is locked
- many DBs rows are lcoed
  - `lock escalation`: when there are too many (row) locks, DBs lock entire table
  - hurts concurrency so bad

Reducing Transaction Isolation for Liveness
4 levels of reducing
1. serializable: sacrifice nothing (no consideration for Liveness, __most stable__ )
2. repeatable read: allows phantom rows (reads results of other commits during transaction)
3. read committed: allows unrepeatable reads
4. read uncommited: allows dirty reads (most unstable)


#### Business transactions
- fitting one business transaction to a single system transaction is possible, but easily becomes a bottleneck
- usually, a transaction from user perspective is break down into many system transactions
  - you are left to your own devices to support the ACID properties of business transactions between system transactions - a problem we call `offline concurrency`
  - easy to support atomicity and durability (using the commit of system transaction)
  - tracking changes (for rollback) can be difficult - __with domain model, use Unit of Work__ (not easy with mere transactional script (which is not transactional at all in this context))

hard part - isolation, consistency
- inconsistent reads

__Convention__ : single session is composed of many business transaction
- it is possible to have multiple sessions for one business transactions, but it will get complicated easily

비즈니스 transaction != system transaction일 때, 고통스러운 길의 starting point
- Optimistic Offline Lock (실패를 commit시에 알게 됨 - 일부 비즈니스 룰에서는 엄청난 제한)
- pessimistic Offline Lock (heavy locks)

concurrency를 결정할 땐 일반적인 인식과 달리 domain 지식이 필요

느낀점 - lock escalation이 진짜 일어나나? 한번도 들은 적 없긴 요
카카오 디폴틀값이 뭐더라

#### App server concurrency
- process per session
- (pooled) process per request: thread per request이 더 가볍긴 하지만 거의 비슷함 ㅋㅋ. 오늘날 스탠다드인 듯
- thread per request일 시, 글로벌/스태틱/싱글톤 등 조심 필요


### Chap 6 Session State

일부 세션은 inherently stateful함

OOP에서 Obj는 method와 state (attribute)을 동시에 가짐
- 여기서의 stateless = stateless objs (which is often a bad design)
- distrubuted enteprise APP에서의 statless는 method call (request)간의 stateless임 (obj들은 per request state를 가짐)


Everything should be stateless? - it would be if it could be
- many client interactions are inherently stateful
- many business transactions are statefull -> implies that the session has to be stateful
  - good news: we can use a stateless server to implelent a stateful session

`session states` = 세션 내부에서만 유지
- commit 전에는 validation rule을 어기는 경우가 많음
- `record data`: 세션간에도 유지

ways to store session states
- client session state: 트래픽이 크면 안좋음
- server session state: 간편, 간단
- database session state: `session migration`에 좋은 듯 (한 세션을 여기저기서 처리가능) / `Server affinity`: 특정세션은 특정워커에서만


스타게이트 세션: session migration + database session state?


### Chap 7
Distribution Strategies
- seperating objects (in terms of machines/processes) makes interface coarse-grained
  - a local interface is best as `fine-grained interface`
    - is good b/c it follows the OO principle: lots of little pieces that can be combined and overriden in various ways to extend the design into the future
- `transparency`: allows objects to call each other within a process or between a process without having to know if the callee is in the same process / in same machine

__First Law of Distributed object Design__: Don't distribute your objects
- using multiple processors: by `clustering` (put all the classes into a single process, and run multiple copies of it)

When you have to distribute
- client-server
- server-db (db interfaces are designed to be remote)
- web/app server

When using distribution
1. use `remote facade` to seperate (and explicitly declare) the additional interfaces required for distrubution
  - fine grained part / coarse grained part (seperate using facade)
2. Interface for distribution
- we begun to see interfaces based on XML over HTTP (...) 언제적 얘기지
- http 인터페이스와 OOP interface를 layering하기? 이거 fastapi에선 나름 되지 않나
- increasinly, my preference is for a msg based approach thats inherently async


### Chap 8 Putting it altogether

architectural refactoring is hard, but still possible

3 technical practices
- continuous integration, test driben development, refactoring

#### Domain Layer
which pattern to choose: complexity of doamin layer (which is not quantifiable)

`transaction script`
- procedural model, encapsulates logic of each system transaction in a comprehensible script (not a good word zz)
- easy to build on relational DB
- doesnt work well when logic gets complex

`domain layer`
- good almost of times
- has steep learning curve
- connection with DB is bit awkard (link direction)

`table module`
- middle ground (지금 쓰이나?)

#### Data Source Layer
- transaction script: it is easy for it to have own db logic, but it is better to avoid it (seperate it to patterns like `row data gateway` or `table data gateway`)
- domain model: main weakness (connection to the DB is complicated). Data mapper is good pattern to seperate and connect to DB, but is complicated

#### Presentation layer
- movel view controller pattern is good place to start

#### 느낀점
CI가 2006년 쓴 글이네?ㄷㄷㄷㄷㄷㄷㄷ
대전게임 / 데바데 같은 건 consistency 관리를 어떻게 할까...
커맨드 패턴 복습 (아래)


### Chap 9 Domain Logic Patterns

#### Transaction Script

> Organizes business logic by procedures, where each precudere handles a single request from the presentation

business app = series of transactions

each interaction of server/client contains some part of logic
- a `Transaction script` organizes all this logic primarily as a single procedure
- thin DB wrapper / direct call to DB
- domain logic is organized by the transactions that you run in the system

For each TS
- get input, query to the db, mungu, and save the result to db
- no need to care about other TS

2 ways to organize transaction scripts
1. several TS in single class, each class defines area of related transaction script
  - straight, most common
2. one TS in single class, inheritance, using the Command pattern
  - can manipulate instances of scripts as objects at runtime


When to use TS -
- when business logic is simple
- when it becomes complicated -> duplication arises
  - b/c each transaction script are line of codes that cares about processing input/output
  - careful factoring can alleviate, but eventually Domain Model will be requred in the end

#### Revenue Regocnigition Problem

Company sell 3 `products` - word processors, db, spreadsheat
- wp: get revenue right away
- spreadsheat: 1/3 today, 1/3 60days, 1/3 90days
- db: 1/3 today, 1/3 30days, 1/3 60days

#### TS with code
- everything is function, manipulate SQL directly
- not easy to maintain coherent design with TS once things get complicated


### Domain Model
- add a domain model in an app = inserting a whole layer of objs that model the business area you're working with
- mostly, the data and process are combined to cluster the processess close to the data they work with __(obj = method + state)__


2 domain models in the field
1. table ~= objs
2. objs are complex than tables, with inheritances, patterns, interconnections (requires `data mapper`)

common concern = `bloated objects`
- too many responsibilities in a single class, each only used in a single use case (SRP!)


  - responsiblity is general -> to order class (?)
  - is specific - seperate to the usage-specific class (might be a TS or the presentation itself?)

The problem with separating usage-specific behavior is that __it can lead to duplication__
- duplication quickly lead to more complexity / inconsistency, but i've found bloating occurs much less frequently
- my adivce is not to seperate usage-specific behavior. Put it all in the object thats the natural fir. Fix the bloating when, and it, it becomes a problem



느낀점
usage-specific behavior를 전부 분리하는 것은 duplication의 위험이 큼 -> 문제가 될 때만 분리?


The problem with separating usage-specific behavior is that __it can lead to duplication__
- duplication quickly lead to more complexity / inconsistency, but i've found bloating occurs much less frequently
- my adivce is not to seperate usage-specific behavior. Put it all in the object thats the natural fir. Fix the bloating when, and it, it becomes a problem


When you use Domain model, you may want to consider Service Layer to gice your domain model a more distinct API

Every class (in the small example) contains both behavior and data.


Domain model - multiple objs interacts with each other (even simplest cases)
- with OO programs you spend lot of time hunting around from cls to cls trying to find them
- this has merits when decision on whether sth is recognizable by a certain date gets more complex, and as other objs need to know
- containing the behavior on the obj that needs to know, avoids duplication and reduces coupling between the different objs
  - ex) strategy pattern - __provide well-contained plug points to extend the app__


The OO habit of successive forwarding from obj to obj moves the behavior to the obj most qualified to handle it, but it also resolves much of the conditional behavior
- there are no conditionals in the cals
- you set up the decision path when you create the products with the appropriate stragegy
- domain model works well with similar conditions, since the similar conditionals factored out into the obj structure
- this moves complexity out of algorithm and into the relationships between objs
  - more similar the logic, you'll find the same network of relationships used by different parts of the system


Example does not contain DB
1. on purpose (whole point of domain model is to hide the db?)
2. mapping domain model - db is always hard



### Table module
- one class = one table
  - class also has some methods for data manipulation (= query to DB)
- always provide identity (PK) for each operation (no notion of identity on the obj)


### Service Layer
> Defines an app's boundary with a layer of services that establishes a set of available operations and coordinates the app's response in each operation


- common interface for (data loaders, UIs, intge gateways), to access and manipluate its data and invoke its business logic
- __service layer defines an app's boundary__ and its set of available operations, from the perspective of interfacing client layers
  - encapsulates the app's business logic, controlling transactions and coordinating responses in the implementation of its operations
  - includes the logic of interactions


`business logic` is divided into 2 kinds
- `domain logic`: pure problem domain (strategy of calcing revenue)
  - `domain model` is preferable to TS for avoding domain logic duplication
- `app logic`: having to do with app responsibilities (notifying contract admins, ...?)

putting app logic into pure domain obj class is not good
- app logic is less resuable
- hard to modify app logic
- service layer factors each of business logic into seperate layer

many impl possible, without violating characteristics stated above (?)
- the differences appear in the allocation of the responsibilities behind the service layer interface
- `domain facade`: thin. domain layer implements all the business logic, facade only establishes boundaries
- `operation script`: thick. implements app logics, delegates domain logic to domain layer


the interface of service layer class is coarse by definition, since it declares a set of application operations available to interfacing client layers
- service layer classes are well suited to remote invocation from an interface granularity perspective
  - but obj distribution is not easy - add remotability only when needed with `remote facade`


#### Idenfifying Service and Operations
- operations needed on a service layer boundary are determined by the needs of `service layer clients` ex) UI
- UI is desinged to support the use cases that actor perform with an app, we need use case model and UI design in first hand

many use cases are boring CRUD on domain objs - they're almost 1-1 correspondence between CRUD use cases and service layer operations
- however on APP side, CRUD rquires noti of other ppl/app/objs (validation aside) - these interactions/response must be coordinated, and transacted atomically by service layer operations


The benefit of service layer - defines a common set of application operations available to many kinds of clients, and it coordinates an app's response in each operations

When not to use service layer - only 1 client for app's business logic, and its use case responses dont involve multiple transactional resources

application logic - problem domain that are of interest to the app, which doesnt mean all of the app's use case responsibilities (?)

> ... Service layer combines scripting and domain obj  classes, leveraging the best aspects of both (?) ... this pattern lays the foundation for encapsulated implementation of an app's business logic and consistent invocation of that logic by its various clients



예시 - contract obj를 data gateway를 호출해 값을 읽어오고, 스스로 recognition을 계산하게 하고, emain보내고, db에 다시 저장하는 부분 (이것도 도메인 로직이지만 앱 입장에서만 관심있는 거인듯)

느낀점
- 코드로 이해하는 객체지향 설계 느낌이 났음. if-else를 객체구조로 옮기는 것이...무조건 좋지는 않은 것 같긴 한데
- coarse grained vs fine grained interface?



