---
layout: post
title:  "Patterns of Enterprise Application Architecture 5"
date:   2022-09-26 09:10:05 +0800
categories: coding
use_math: true
tags: coding
---

마지막이네 ㄷㄷ

### Chap 17 Session State Patterns
`Client Session State` - stores session on the clinet side, especially on the query params
- ex) Dashboards such asKibana, Grafana
- cookies/hidden fields are also possible, but not popular
- not good when data explodes

`Server Sesion State`
- where to store? - memory, file, external storage
- boundary between `server session state` and `database session state` is not so clear


### Chap 18 Base Patterns

#### Gateway
An object that encapsulates access to an external system or resource
- common gateway, common formats
- handles versioning `/api/v1/...`, auth, etc
- one key uses for a gateway is a good point at which to apply a `service stub` (?)
  - well placed stub can make system easily testable

When to use
- when you feel your interface is awkward, dont spread it. Contain it in a gateway (zz)
- gateway usually make sistem testable by providing a point to deploy service stub
- make easy to swap resource. Change does not ripples through system but stucked in the gateway

GOF comparison
- while `facade` simplies a more complex API, it is usually done by the writer. Gateway is written by the client (!?)
- `adapter` alters implementation's interface. With gateway there is usually no existing interface

You can switch between the real service and the stub at config time by using a `Plugin`, or you can have the test setup routines initialize the env to use the `Service Stub`


#### Mapper
An object that sets up a comm between two independent objs
- insulating layer between subsystems, decoupling them
- ex) data mapper. complicated and not easy to change - use it when the interation is complicated but somehow not the main purpose of the system = domain model and data mapper!

#### Layer Supertype
A Type that acts as the supertype for all types in its layer
- can remove code duplicate

#### Separated Interface
Defines an interface in a separate package from its impl

One way to improve design quality - reduce coupling between subsystems
- one can group the classes into packages, and control dependencies between them with some rules
- ex) class in the domain layer may not call classes in the presentation layer / domain mapper

However there are times when you need to violate such rules (`General Dependency Structure`)
- in such cases, use `Separated interface` (so that domain object only know the interface of presentation layer, not the impl, for the above example)

It takes advantage of the fact that, __an impl has a dependency to its interface but not vice versa__

> Usually initialization requires knowledge of implementation -> use factory as the seperated interface. Use plugins to defer the dependency in the config time

Use this when you need to break a dependency between two parts of the system
- ex) wrote abstract codes for common cases into a framework package, that it need to call some part of app code
- domain calling data mapper

using `seperate interface` for every class is excessive. Use it only when you want to break dependency
- Having only a dependency to create on obj, and using the interface ever after is often enough

#### Registry
A Well-known object that other objects can use to find common objects and services
- essentially a global object (singleton zz), or at least it looks like one

design of registry
1. interface - author prefers static method (easy to find)

for a process-scoped Registry, usual option is a singleton
- author prefers to hide instance (Registry.getFo() over Registry.soleInstance.getFoo() )
- can be problematic in multi thread - fine as long as its immutable


When to use
- one should use registry as a last resort (access objs through regular inter-object ref)

#### Value object
A small simple obj, like money / data range, whose equality is not based on identity

Author find it useful to distinguish between `reference object` and `value object`
- `ref obj` use identity (in its programming language) as the criteria of equality
- `value obj` use field values to check equality
  - usually small (ex - datetime of python)
  - passed around as values
  - immutability is recommended


#### Money class
- value object
- shoud avoid float (use decimal / integer)

#### Plugin
links classes during config time rather than compile time

using seperated interface, we can change implementation
- factory method reads env var, generates corresponding concrete class
  - become mass when there are many factory
  - `plugin` provides centralized, runtime config

`plugin factory`
- requires its linking instructions to be stated at a single, external point
- linking to impl must occur at runtime (rather than compile time)


#### Stub

dependency of external service
- is a risk
- at leastit slow the dev process

steps
1. define access to the service with a Gateway, which better be a separated interface
- impt will be loaded using a Plugin

#### Record set
- 이제 필요없는 거 아닌가?

### 느낀짐
- Client Session State - 바로 kibana가 생각났음 ㅋㅋ 링크 하나 주면 될 듯
- Server Session State - 스타게이트 예제 들면 될 듯. 레디스/레디코크?
- seperated interface: Usually initialization requires knowledge of implementation -> use factory as the seperated interface. Use plugins to defer the dependency in the config time
 (...)
- 할말
  - 노sql 마틴파울러 공동저자 책
  - https://coffeewhale.com/packet-network1
  - 릿코드?
  - 트위터 앱에 최대 1200개의 마이크로서비스? ㅋㅋ