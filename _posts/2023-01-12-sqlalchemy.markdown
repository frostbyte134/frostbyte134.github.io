---
layout: post
title:  "SQLAlchemy Conceps"
date:   2023-01-12 07:00:05 +0800
categories: coding
use_math: true
tags: coding
---

맨날 까먹어서 정리 한번 해 두면 좋을 듯..ㅋㅋ

### Overviews
https://docs.sqlalchemy.org/en/20/intro.html#overview

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

#### Session with ORM
- `session`: entrypoint of ORM part
- very similar to that of the Connection (in fact as uses Connection inside)
- `with engine.connect() as conn` -> `with Session(engine) as session`
- gets a new Connection from the Engine the next time it needs to execute SQL against the database


#### Join
https://stackoverflow.com/questions/27900018/flask-sqlalchemy-query-join-relational-tables
