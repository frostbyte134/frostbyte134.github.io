---
layout: post
title:  "Patterns of Enterprise APP Architecture 1"
date:   2020-09-13 09:10:05 +0800
categories: coding
use_math: true
tags: coding
---

### Intro

Two common elements of the term `architecture`
- highest lvl breakdown of a system into parts (mainly to layer, which the author prefers)
- the decisions that are hard to change
- = shared understandings (in both cases). There can be many architectures (views) for a single system, which change over time


Enterprise App
- EX) payroll, supply chain, insurance, foreign exchange trading, ...
- usually involve `persistent data`
  - several years of persistency, even after the app dies
  - many changes happen during its lifetime
- a lot of data - usually GBs with mills of records
- access to data concurrently
- a lot of user interface screens
- `conceptual dissonance` between business process and data
  - ex) definition of a customer - person with agreement / person who had agreement at least once before (on other division) / ...
- doesnt necessarily mean a large project
  - rather, one of the best things can do is turn a large project into a small one, by simplifying its architecture and process

Business logic
- just given to you
- in real business, little tweak (of the logic) can make big difference - a few thousand of these one-off special cases is what leads to the __complex business illogic__

Enterprise App Examples
- B2C online retailer: simple domain logic, many users, easy access (easy and simple web repr)
- leasing agreement application: fewer users leads to simple system. Complex business logic (rules are arbitrary) - more complex UI, complex Transaction
- small, simple expanse tracking system
  - simple but still cannot avoid change over time
  - may grow (exponentially) later - some initial design choices are important
  - systems are small, but may be distributed to many places - (result of) changes are not trivial

#### Thinking about performance
- `Response time`: amount of the time it takes for a system to process a request from the outside
- `Responsiveness`: How quickly the system acts a request. It does not have to finish producing final results before making response
- `Latency`: minimum time required to get ant form of response
- `Throughput`: how much stuff you cna do in a given amout of time

When building enterprise systems, it often makes sense to build for hardware scalability rather than capacity or even efficiency
- adding more servers often cheaper than adding more programmers - providing that a system is scalable


#### Patterns
> Each pattern describes a problem which occures over and over again in our env, and then describes the core of the solution to that problem, in such a way that you cna use this solution a mill times over, without ever doing it the same way twice, Christopher Alexander (who is an architect!)

Patterns are rooted in practice
- you find patterns by __observing__ what people do, then look for the core of the solution (pattern)

Each pattern is relatively independent, the boundaries are naturally fuzzy
- but often one patten leads to another (Domain Model -> Class Table Inheritance)

The value of pattern is not that it gives you a new idea; the value lies in helping you communicate your idea
- pattern names are crucial (for better comm)

### Chap 1 Layering

Layering is one of the most common techniques that sw designers use to break apart a complicated sw systems
- Machine architecture (OS -> derivers, CPU inst set -> logic gates), network (FTP -> TCP -> IP -> ethernet)

higher layer uses the services defined by the lower layer
- lower layer is unaware of the higher layer
- each layer usually hides its more lower layer from the higher layers (2 -x-> 4)

PROS
- can understand layer by layer
- can substitute each layer
- minimize dependencies between layers
- can reuse lower, detailed layers (TCP/IP is used by FTP, telnet, SSH, and HTTP)

CONS
- layer does not encalsulate all - sometimes get cascading changes
- extra layers can harm performance

#### Evol of layers in Enterprise Apps
- started from server-client (UI)
- the problem came with domain logc: business rule, validations, calcs, ...
- embedding them in screens make it easy to duplicate code
- store them in DB -> DB has limited structuring mechanism
- OOP was rising - with the proposal of three-layer system
  - presentation / domain / data source
  - with the advant of web (and Java), 3-layer approach are becoming dominant


layer vs tier: different tier (server-client) implies seperation is physical
  - for layer, it does not have to


#### 3 layers
1. Presentation layer
  - provision of service, disp of info (HTML,...), initially handling user requests, CMD line
  - display info to the user, and to interpret commands from the user into action upon the domain and data source
2. Domain logic
  - logic that is the real point of the system
  - calc, validation, etc
3. Data source logic - db/messaging systems/transaciton managers, other packages

Presentation layer often directly access Data source
  - less pure, tends to work better in practice

There can be many packages of each 3 areas (multiple presentation = UI/CMD)

`Hexagonal architecture`: visualizes system as a core sourrounded by interfaces to external systems
  - not a leveled architecture - presentation and data sources are mere (outer) interfaces

However, asymmetry (of 3 layers) is often useful
- Presentation is an external interface for a service your system offers to someone else
- Data source is the interface to things that are providing a service to you

One doesnt need to seperate layers in different classes/modules
- often seperation on subroutine is enough (which is the minimal though)

> The domain and data source should never be dependent on the presentation

there should be no subroutine call from the domain/data source code into presentation code
- enables substition of presentation
- interation between domain and data sources can be more complex

What should be on domain logic? (most confusing part commonly)
- informal test: imagine adding a radically different layer to an app, such as a cmd-line interface to a Web app. If theres any functionality you have to dpulicate to do this, thats a sign of where domain logic has leaked into the presentation
- similarly, do you have to duplicate logic to replace a relation db with XML file? 

#### Where to run your layers
mostly about logical layers

1. on server: easy to upgrade and fix (compared to client, thinkg about embedded zz)
2. on client: responsiveness, disconnected operation

If you have to run some logic on client, seperate it to another module (which solely depends on interface)

Dont try to seperate layers into discrete processes, unless you absolutely have to

`complexity boosters`: distributions, explicit multithreading, paradigm chasms, multiplatform development, extreme performance reqs
- all carry a high cost


### Chap 2 Organizing Domain Logic
- Domain Logic: requirement from the users
- Domain Model: OOP way of handle complexity

#### Transaction script
- a `procedure` (essentially)
- takes input from presentation, process (validation, calc), store, and invoke other system
- basic organizing method = one procedure for each action user want to do
  - = script for an action / business transaction
  - easy to make duplication
- pros: simple, obvious
- cons: enot easy to deal with complex domain logics


#### Domain Model
- OOP way of dealing with complexity (has both state, method in object)
- rather than one routine hainv all the logic for user action (in if-else statement), each obj takes part of the logic relevant to it
- not easy at first sight


transcation script vs Domain model
- ts: method has to determine which action to perform, by the given condition
- OOP way: object decides by 

The cost of a Domain model come잡 from
1. the complexity of using it (hard to learn)
2. the complexity of data source layer - 모델은 보통 디비 테이블과 1:1관계이고, 많아질수록 복잡

#### Table model
- organizing domain logic around tables, rather than straight procedure / objects
- may remove some duplicate (compared to ts), but cannot use many patterns of OOP
- db구조를 가정하는 많은 서비스 (ex - GUI 프로그램)들과 잘 맞음

ts -> domain model은 해 볼만, 반대는 안하는게 좋음
These 3 patterns are not ME (보통 ts + (domain or table))

#### Service layer
- component of domain layuer
- presentation only inteacts with service layer (API for it)
- minimum (mere API) vs some logic in it (complex servce layer) -> each have their own advantages
  - midway = `controller-entity` style
  - 'controller' != controller of MVC
  - `controller` here = a logic that's particular to a single transaction/usecase, as a transaction script (`use-case controller`)
  - behavior that's used in more than one use case goes on the domain objects, which are called entities

느낀점
- transaction script vs OOP 시퀸스 다이어그램에선 자율적 객체 생각이 났음 (transaciton script에서는 항상 method가 주어진 조건으로부터 상황을 판단하고 그에 맞는 게산을 해야 하나, OOP에선 이 중 일부를 자율적인 객체에 넘길 수 있음)

### Chap 3 mapping to Relational DBs
`data source layer`: comm with various piece of infra tha an app need to do its job


#### How the domain logic talks to the DB (Architectural Patterns)
- not a easy choice to refactor
- understanding SQL is another burden - wise to seperate QL access and domain logic
- `Gateway` of table: one class per db table. 2 ways of using gateway
  - an instance for each row (returned by query) = `Row Data Gateway`. OOP way of thinking data
  - `Record set`: generic data structure of tables and rows, that mimics the table
    - when using it, we only need 1 instance(?) for each table: `Table Data Gateway` provides method to query the db that returns a record set
- with `Domain model`, one can use either Row Data or Table Data Gateway
  - simple logic - one domain class for each table (which has additional methods corresponds to domain logics)
    - in such case, better to have each domain obj to be responsible for CRUD from the DB, which is `Active Record`
    - Active Record = Row Data Gateway + domain logic as method
  - as the domain logic gets complicated, simple approach of Active Record breaks town
    - relational DBs dont handle inheritance -> cant use fancy OOP techniques to handle complexity
    - gateway can solve this partially, but it still makes __domain model dependent on schema of database__ - `Data Mapper` is complex but can make both independent! (how?)
    - author does not recommend using Gateway with domain model - use Active Recore (when simple) or Data Mapper (when complex)

#### Behavioral patterns
- `Behavioral Patterns`: how to get the various objs to load and save them to DB
- consistency (betweeen memory and DB) - `Unit Of Work` can guarantee this
  - instead of the app programmer invoking explicit save methods, the programmer tells uow to commit
  - UOW: obj that acts as the controller of the db mapping; deciding when to R/W on DB.
  - UOW results from factoring (seperating) db mapping controller behavior into its own object
- to prevent loading same obj twice from DB, use `identity map`
  - can act as cache, but main purpose is consistency
- `Lazy Load` can boost performance 


#### Reading in Data
reading data method = `finders` that wrap SQL select statement with a method-structured interface (`find(id) / findCustomer(Customer)`)

where you put the finder method depends on the interfacing patterns used
- `table based` interaction classes (one instances for each table): can combine finder methods with the inserts and updates (combine in same class?)
- `row bases` - can make find static, but with this we cannot inject it for testing purpose (`Service Stub`)
  - better to have seperate finder object

#### Structural Mapping Patterns

Central issue - objects and relations handle links differently, leading to 2 problems
1. difference in repr: obj handle links by storing ref (held runtime on memory) / relation form a key into another table
2. objects can easily use collections to handle multiple refs from single field / while normalization forces all relation links to be single valued

객체는 쉽게 다수의 다른 객체에 대한 ref를 가질 수 있으나, db에선 foreign key로만 됨 - 다수의 row가 1개의 메인row에 대한 foreign key를 갖게, 방향이 반대임
- `Identity Field`, `Identity Map`, `Foreign Key Mapping`등을 사용해 해결 (?)

many to many - 따로 table 만들어 관계 저장해야 함 (ㅋㅋ)

referential integrity - db에서 check later지원 안하면 topological sorting 해야 할 지도? (???)

table inheritance - skipped

#### Building the mapping
Wehn design of a Domain Model looks like a db design, you should beware (maybe you can simplify more)
- data mapper gives you flexibility here (if the model is simple, Active Record can work)

Connections
- asd

misc
- select * can create many problems


느낀점
- domain model - use Active Recore (when simple) or Data Mapper (when complex)
- OO database?
- Structural Mapping Pattern에 object/relation이 link를 다르게 handle - 이런 생각을 못해봤는데 좋은 듯


### Chap 4Web Presentation

2 main forms of structuring a program in web server: script / server page
1. script: a program (CGI, Servlets), which can be broken down to subroutines
2. pages: preparing HTML repsonse (PHP)

MVC(`Model View Controller`) - makes easy to format response with script
- Controller here = `input controller` (sits between web server / model (data) and view)\
  - seperates model from web presentation
- `Page Controller` - one controller per page (?)

`Application Controller` object
- in GUI, controls flow of an app, deciding which screens should appear in which order
- a seperate layer that mediates betwen the presnetation and domain layer