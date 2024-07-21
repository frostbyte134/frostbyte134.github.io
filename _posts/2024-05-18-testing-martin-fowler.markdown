---
layout: post
title:  "좋은 테스트란 뭘까"
date:   2024-05-18 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---



요약
- stub / mock 구분 (내가 지금 state / behavior 중 뭘 테스트하는지도 인지하기)
   - 이건 생각보다...잘 실천이 안됐음. 실천한다고 도움이 되나?
- hemchrest 사용 (AssertJ ㅜㅜ)
  - 굿
- given when then 구조 사용
   - 이건 테스트에 섹션을 구분해놓으니까 보기 좋은 듯
- 구현을 테스트하진 않는지 항상 생각하기. 되도록 인터페이스를 대상으로 결과만 테스트하기
   - 굿2
- Mock을 안 쓸 수 있으면 안쓰기!
   - 하고싶은데 잘안됨 ㅎ
   - 모킹이 많을수록 false positive test가 될 확률이 높다...진짜 공감가는 말인듯

https://blog.outsider.ne.kr/1275?fbclid=IwAR1Z9DPi-JJns_bSccrNZIo8zFo-0B8nAvIEHen3tu0_jaIUS34hY90FVJ0
- 공감가는 부분이 엄청 많은듯


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

> One of the big problems with statics (in most languages) is you can't use polymorphism to substitute one implementation with another. This bits us a lot because we are great fans of testing - and to test well it's important to be able to replace services with a Service Stub.

보통 config에 static을 많이 쓰는데

static config를 쓰는 객체 -> 만들때부터 static에 의존하기 때문에 테스팅이 어려움. 객체, 생성자 및 기타 메소드 다 static이 붙어야 함
- 클래스에 static obj (singleton)을 두고, 로직등엔 전부 static 때버리기 (hence substitution)

마지막엔 이런 함수 하나만 추가하고, 테스트시에 arg에 스텁 넘겨주기

```java
    public static void loadInstance(AddressBook arg) {
        soleInstance = arg;
    }
```



### is TDD dead?
https://www.martinfowler.com/articles/is-tdd-dead/

TDD는 self testing code에 도달하는 방법 중 하나일 뿐

켄트백조차 모든개발에 TDD를 쓰진 않는다고 함. 다만 TDD를 안쓴 곳에도 regression tests and short feedback loops는 사용

he (Kent) said he rarely uses them (TDD), he's concerned that those that do often find refactoring difficult, while he finds testing makes refactoring easier.


design damage - 모든 것을 테스트하기 위해, 헥사고날처럼 (port & adapter) indirection, runtime polymorphism같은걸로 다 갈아끼울수 있는 구조로 가다보면 코드가 복잡해짐
- 내지는 TDD가 addictive하게 위의 방향으로 개발하게 유도

> Kent said that ascribing test-induced damage to TDD was like driving a car to a bad place and blaming the car for it. The design David showed wasn't due to TDD, the real issue is that these indirections are all good tricks under some circumstances and we need to understand whether they are worth the cost or not


I replied that "you don't have enough tests (or good enough tests) if you can't confidently change the code," and "the sign of too much is whenever you change the code you think you expend more effort changing the tests than changing the code."
- I said I like the "can I comment out a line of code" approach when I'm unsure of my ground, it's a starting place but as I work more in an environment I can come up with better heuristics.



### AssertJ

https://xxeol.tistory.com/12 완전 좋은듯 ㅎㅎ


우린 헴크레스트였네. 뭐 일단 쓰고 보자 ㅋㅋ https://expert0226.tistory.com/335

### 유닛테스트에 대한 생각

https://gregor77.github.io/2019/08/16/about-unit-test/?source=post_page-----e6b4394f9ed--------------------------------

입력값에 대한 결과 값을 검증하는 방식으로 짜는 것이 기본
- false positive test의 가장 큰 원인 - 구현을 테스트하는 것
- ex) 서버의 리턴 상태코드를 체크하지 않고 메시지를 체크
- 가능하면 입력의 결과 또는 인터페이스만 테스트해야 함



### 효율적인 JUnit 사용

https://yozm.wishket.com/magazine/detail/1748/


진짜 별내용 없었음..



### self initializing fake

https://martinfowler.com/bliki/SelfInitializingFake.html



### Unit test

https://www.martinfowler.com/bliki/UnitTest.html

### Goto Fail, Heartbleed, and Unit Testing Culture

https://www.martinfowler.com/articles/testing-culture.html

와 개 김 ㄷㄷ 읽어볼 만한가..한국에선 별로 읽은사람이 없는듯. 하트블리드는 쬐끔 관심있긴 한데 ㅋㅋ