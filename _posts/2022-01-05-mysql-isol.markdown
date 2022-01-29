---
layout: post
title:  "Isolation Levels (MySQL)"
date:   2022-01-05 08:00:05 +0800
categories: coding
use_math: true
tags: coding mysql db
---


일단 무지성으로 적고 집에 가서 복습하자


### bad reads
- <a href="https://docs.microsoft.com/en-us/sql/odbc/reference/develop-app/transaction-isolation-levels?view=sql-server-ver15" target="_blank">ms docs</a>
- <a href="https://stackoverflow.com/questions/11043712/what-is-the-difference-between-non-repeatable-read-and-phantom-read" target="_blank">논 리피터블 / 팬텀리드</a>
- `non-repeatable read`: 트랜잭션 내에서 단일 row의 값이 변하는 경우
- `dirty read`: commit되지 않은 데이터를 읽음. record lock을 걸지 않고 + 커밋되지 않은 데이터를 읽을 수 있으면 이렇게 되는 듯
- `Phantoms`: 트랜잭션 내에서, 처음 select 할 땐 없었는데 다음 select할 떈 나타난 유령 (ㄷㄷ). Repeatable read같은 경우 첫 select시 스냅샷을 떠버리기 때문에 이 현상이 안생김.

| Transaction isolation level  | Dirty reads | Nonrepeatable reads | Phantoms |
| ------------- | ------------- | ------------- | ------------- |
| Read uncommitted  | O | O | O |
| Read committed  |  | O | O |
| Repeatable read | | | O |
| Serializable | | | |


### isolation level
- <a href="https://suhwan.dev/2019/06/09/transaction-isolation-level-and-lock" target="_blank">대박 정리 잘됨</a>
- <a href="https://docs.microsoft.com/en-us/sql/odbc/reference/develop-app/transaction-isolation-levels?view=sql-server-ver15" target="_blank">ms꺼에서도 버릴 게 없는듯</a>

- read uncommited를 제외하고, 전부 
row lock을 
검
