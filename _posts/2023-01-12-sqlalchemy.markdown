---
layout: post
title:  "SQLAlchemy Concepts"
date:   2023-01-12 07:00:05 +0800
categories: coding
use_math: true
tags: coding
---

맨날 까먹어서 정리 한번 해 두면 좋을 듯..ㅋㅋ

### Overviews
<a href="https://docs.sqlalchemy.org/en/20/intro.html#overview" target="_blank">https://docs.sqlalchemy.org/en/20/intro.html#overview</a>

SQLAlchemy is divided into two main pars: core and ORM

`Core`
- `SQL Expression Language`: represents SQL queries into composible objs
- objs can be executed toward targ db, along with data from dict
- architecture for SQLAlchemy as a “database toolkit”

`ORM`
- SQL statements are constructed in mostly the same way as when using Core
- DML (~= persistence of business objects in a db) is automated via [unit of work](https://docs.sqlalchemy.org/en/20/glossary.html#term-unit-of-work) pattern
- `UoL` translates changes in state against mutable objects into INSERT, UPDATE and DELETE constructs, which are then invoked in terms of those objects
- includes object persistence mechanism known as the `Session`
- extends the Core-level SQL Expression Language to allow SQL queries to be composed and invoked in terms of user-defined objects

`Result`: returned object as a query result (resultset in architecture pattern?zz)

### Establishing Connectivity - the Engine
- entrypoint of SQLAlchemy
- The Engine is created by using the `create_engine()` function (with uri specifying DBApi (`sqlite+pysqlite:///:memory:`) and other configs
- `Connection` and `Result`: primary interactive endpoints of engine
   - `Session`: ORM’s [facade](https://docs.sqlalchemy.org/en/20/glossary.html#term-facade) for these objects

textual SQL (ex - `text("select * from table")` construct)
- nowadays mostly replaced by `SQLAlchemy Expression Language` that is the primary feature of SQLAlchemy

#### commiting with engine
```python
# "commit as you go"
with engine.connect() as conn
   conn.execute(...
   conn.commit()
```


```python
# "begin once" (commited at the context managet)
with engine.begin() as conn:
   conn.execute(...
```

#### Session with ORM
- `session`: entrypoint of ORM part
- very similar to that of the Connection (in fact as uses Connection inside)
- `with engine.connect() as conn` -> `with Session(engine) as session`
- gets a new Connection from the Engine the next time it needs to execute SQL against the database


If we alter the attributes of this object, the Session tracks this change:
```python
>>> sandy.fullname = "Sandy Squirrel"
```

The object appears in a collection called Session.dirty, indicating the object is “dirty”:

```python
>>> sandy in session.dirty
True
```

### Working With Database Metadata
<a href="https://docs.sqlalchemy.org/en/20/tutorial/metadata.html" target="_blank">https://docs.sqlalchemy.org/en/20/tutorial/metadata.html</a>

how to represent database tables, columns, and constraints within SQLAlchemy using the MetaData and related objects

`SQL Expression Language` allows fluent, composable construction of SQL queries
- The foundation for these queries are Python objects that represent database concepts like tables and columns, aka `database metadata`
- database metadata includes following objs: MetaData, Table, and Column


#### Metadata
- we place our tables (Python objects that represents DB table) to the `MetaData` object
   - facade over a Python dictionary that stores a series of Table
   - also stores constraints (over the columns and tables. ex - PK, FK)
- `MetaData.create_all()` emits DDL (create table, ...) to DB

#### Declarative Table

- facade around the __Table declaration process__
- gives us [ORM mapped class](https://docs.sqlalchemy.org/en/20/glossary.html#term-ORM-mapped-class) (aka `mapped class`)
- allows us to declare our user-defined classes and Table metadata at once

Metadata with ORM
- the MetaData collection remains present, as an ORM-only construct `Declarative Base`
- to acquire a new Declarative Base, create a new class that subclasses the SQLAlchemy DeclarativeBase class
- subclassing base class `class Base(DeclarativeBase):...` gives a new ORM mapped class

```
>>> Base.metadata
MetaData()
```

emitting DDL
```
>>> Base.metadata.create_all(engine)
BEGIN (implicit)
PRAGMA main.table_...info("user_account")
...
PRAGMA main.table_...info("address")
...
COMMIT
```

#### Inserting rows with ORM

<a href="https://docs.sqlalchemy.org/en/14/orm/basic_relationships.html" target="_blank">https://docs.sqlalchemy.org/en/14/orm/basic_relationships.html</a>

#### UoW
in ORM mode, DML operations are queued to session
- flushed later when necessary (lazy persistence? zz)
- UoW generally means it accumulates changes one at a time, but does not actually communicate them to the database until needed
  - 컨트롤을 이쪽에서 가지고 있다는 뜻으로 알면 되나?



### Join
https://stackoverflow.com/questions/27900018/flask-sqlalchemy-query-join-relational-tables


#### pooling
https://docs.sqlalchemy.org/en/20/core/pooling.html
- engine에서 풀 관리 -> 세션은 엔진의 파사드이므로 팩토리로 세션 하나 만들 때 마다 알아서 엔진의 풀에서 하나씩 가져오는 듯
