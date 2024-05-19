---
layout: post
title:  "Testing (with Martin Fowler)"
date:   2024-05-18 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---



테스트를 짤 일이 많아져서 (ㅎㅎ) 마음의 숙제 중 하나인 테스트에 대한 정리를 해보려고 함
- 목표: 읽기 쉬운 (면서도 효과적인) 테스트 쓰기



https://www.martinfowler.com/testing/


### 맨날 까먹는 거

#### Test double 

https://martinfowler.com/bliki/TestDouble.html
- `Fake` objects actually have working implementations, but usually take some shortcut which makes them not suitable for production (an InMemoryTestDatabase is a good example).
- `Stubs` provide canned answers to calls made during the test, usually not responding at all to anything outside what's programmed in for the test.
- `Mocks` are pre-programmed with expectations which form a specification of the calls they are expected to receive. They can throw an exception if they receive a call they don't expect and are checked during verification to ensure they got all the calls they were expecting.

#### given when then

https://martinfowler.com/bliki/GivenWhenThen.html
- The `given` part describes the state of the world before you begin the behavior you're specifying in this scenario. You can think of it as the pre-conditions to the test.
- The `when` section is that behavior that you're specifying.
- Finally the `then` section describes the changes you expect due to the specified behavior.


JUnit은 테스트 한번 돌릴 때 마다 클래스를 새로 만든다 함 - 지금도 그런가?


### Mocks Aren't Stubs

mocks = behavior verification
- others = state verification (usually)


1. With state verification we do this by asserts against the warehouse’s state
2. Mocks use behavior verification, where we instead check to see if the order made the correct calls on the warehouse. We do this check by telling the mock what to expect during setup and asking the mock to verify itself during verification. Only the order is checked using asserts, and if the method doesn’t change the state of the order there’s no asserts at all


목 - 미리 expects 를 설정해 놓고 behavior verification을 함
- 흠...
- stub - 다 실행한 담에 assert로 state 체크
- 난어째 목으로 상태체크만 맨날 한거같은데?ㅋㅋ

Mock objects always use behavior verification, a stub can go either way

https://frostbyte134.github.io/coding/2022/12/31/mocks-arenot-stubs.html

https://martinfowler.com/articles/mocksArentStubs.html

https://stackoverflow.com/questions/3459287/whats-the-difference-between-a-mock-stub


### 모킹이 안좋은 경우 / 의견

https://stackoverflow.com/questions/1595166/why-is-it-so-bad-to-mock-classes

Mocking is used for protocol testing - it tests how you'll use an API, and how you'll react when the API reacts accordingly.
- behavior testing과도 통하는게 있는 듯

Every class has an implicit interface, which is the set of public methods and constructors it defines. There is nothing wrong in seeing this as the "protocol" of the class. So, "protocol testing" does not imply that classes should not be mocked. Also, creating a mock does not mean that each and every mocked method must be explicitly specified in the test. Expectations can be either strict or non-strict, where the non-strict ones are freely allowed to occur any number of times in the code under test. In other words, a stub is just a type of mock where all expectations are non-strict by default.

어쨋거나 목은 행동 검사를 하면서 expect도 추가로 달고 복잡한게 꽤 많아지는 듯


mocking interface vs class

https://www.reddit.com/r/haskell/comments/qdexgu/cs_syd_why_mocking_is_a_bad_idea/



https://www.yegor256.com/2014/09/23/built-in-fake-objects.html
- mocking framework를 피해라?
- 근데 첫문단 문제는 주로 클래스 디자인이 잘못된거같은데 (특히 SRP위반). 하긴 협력관계가 복잡한경우...도 포함이 되는 듯
- Fake를 production code하고 같이 shipping해준다......?
   - 나도 추천팀에서 테스트목적 인메모리 디비 만들고 후회했던적 있던거같은데 ㅋㅋ
   - 결국 이 페이크 클레스에 대해서도 알아야 하는거아닌가? 복잡도를 뒤로 숨기는 느낌...?
   - 어쨋거나 목대상 객체가 복잡하면 expect세팅은 곱절로 복잡하니까...선형으로 끊자는 거 같은데..


### test cancer

https://www.martinfowler.com/bliki/TestCancer.html

시작부터 노답문제라고 박고 들어감

typically there are as many lines of code of tests as there are of functional code ㅋㅋ

음...다들 테케 읽기 싫어하는건 비슷한가 봄 ㅋㅋ



### making stubs

https://martinfowler.com/bliki/MakingStubs.html

테스트에서의 스텁 활용법
- abstract factory로 (흠...)
- prototype으로 (아니...굳이?)

실제 케이스를 본적이없어서 좀...실용성이 있나? 이렇게까지 해야하나 느낌


### static substitution

https://martinfowler.com/bliki/StaticSubstitution.html



### self initializing fake

https://martinfowler.com/bliki/SelfInitializingFake.html



### Unit test

https://www.martinfowler.com/bliki/UnitTest.html


### is TDD dead?
https://www.martinfowler.com/articles/is-tdd-dead/

- 테스트와 디자인 데미지는 좀 보고 싶음


### Goto Fail, Heartbleed, and Unit Testing Culture


https://www.martinfowler.com/articles/testing-culture.html

와 개 김 ㄷㄷ 읽어볼 만한가..한국에선 별로 읽은사람이 없는듯. 하트블리드는 쬐끔 관심있긴 한데 ㅋㅋ