---
layout: post
title:  "refactoring"
date:   2023-01-09 07:00:05 +0800
categories: coding
use_math: true
tags: coding
---

아..집에있던거 커밋을 안하고 왔네 ㅋㅋ

> Fowler, Martin. Refactoring (Addison-Wesley Signature Series (Fowler)) (p. 33). Pearson Education. Kindle Edition.


### Chap 1

When you have to add a feature to a program but the code is not structured in a convenient way, first refactor the program to make it easy to add the feature, then add the feature.
- 이번에 어드민 리팩토링 하는데 진짜 맞말 같음. 구조가 안좋으니까 한번에 바꿔야 하는 것의 범위가 너무 불확실하고 큼. 테스트 더하기도 어렵고...

ensure to a solid set of tests for the refactoring target code
- easier said...reality bites.
- refactoring changes the program in small steps (easier to find the cause of mistake)



variable names are a key to clear code
- breaking a large function into smaller ones only adds value if the names are good (no need to peek into details if names are good)
- not easy to get good names right the first time -> need continous refactoring (least twice)

replaced few local variables to inline calls
- "it makes it much easier to do extractions, since there is less local scope to deal with"
- temp vars are only useful within their own routine, and therefore they encourge long, complex (own) routines - "i prefer to replace with a declared function"

JS - [object.assign](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Object/assign) = shallow copy over 1 level enumerable

conditional to polymorphic
- if-else문을 객체 생성 안으로 몰아넣는거 아닌가 싶긴 하지만.. -> 이 상속구조에 기대는 코드들이 더 생길수록 이득이라는 듯
- 일단 로직의 위치를 옮기고, 다음 상속구조에 따른 polymorphic change를 적용하는듯 (나였으면 상속구조부터 짰을 듯...)

> I believe, however, that we can go beyond taste and say that the true test of good code is how easy it is to change it

small steps are key
- in this case: decomposing into small, nested functions (with good names) -> use Split Phase (?) to seperate the calc/printing -> introduce polymorphism
- but what if a big bunch of codes depends on many external resources?zz

느낀점
- 리액트 공부중이라 자바스크립트인게 좋은 듯
- 파라미터가 없는 함수 좀 그런데 (특히 오록스 보면서 좀 많았음. 난 사이드 이펙트다 라는 느낌. 코드 보기도 어려움), 중간 코드긴 하지만 자주 보인 듯.
- 코드에도 줄넘어갈때마다 하이픈 붙는것때문에 좀 그럼...


### Chap 2
> Refactoring(noun): a change made to the internal structure of sw to make it easier to understand and cheaper to modify without changeing its `observable behavior`

if the code was broken for some days, then it is not refactoring (zz)


`observable behavior`: internal details (call stack status, level) which are not observable doesnt matter

refactoring is always done to make the code easier to understand and cheaper to modify

#### Why we should refactor?

code decays
- often people add code without a full understanding of architecture
- -> breaks uniformity / constraints of entire codebase -> harder to see the architecture just by reading the code
- harder to see the design of code -> harder to preserve the structure -> code decays much faster! zz

more code
- = more dependency = harder to refactor (more change to break system in somewhere)

> By clarifying the structure of the program, I clarify certain assumptions I've made - to a point where even I can't avoid spotting the bugs

#### When should we refactor?
The best time to refactor is just before I need to add a new featre to the codebase

By refactoring I move the understanding from my head into the code itself (Ward Cunningham)

excellent code (also) needs plenty of refactoring too
- whenever we code we make choice between tradeoffs - it was valid yesterday but could be wrong next day - as business changes / system changes
- the advantage is that clean code is easier to refactor

To change from one library to another, start by introducing a new abstraction that can act as an interface to either libs
- `branch by abstraction`


code reviews help spread knowledge through a dev team

A schedule-driven manager wants me to do things the fastest way I can; how I do it is my responsibility (so do the refactorign without telling them zz)

I’ve found that refactoring helps me review someone else’s code (based on experiences)

리팩토링 때문에 초기 코스트는 좀 들어가도, 코드복잡도에 비해 개발시간이 선형으로 들어가게 됨 (안그럼 로그)

#### Problems with Refactoring
- Slowing Down New Features
- Still, the evidence I hear from my colleagues in the industry is that too little refactoring is far more prevalent than too much.

a `healthy code base`-of the power that comes from easily combining existing parts into new configurations to quickly enable complicated new features.

dangerous wayto justify refactoring = in terms of “clean code,” “good engineering practice,” or similar moral reasons
- The point of refactoring isn’t to show how sparkly a code base is—it is __purely economic__

code ownership (wrt published interface)
- When renaming a function, I need to use Rename Function (124) and to retain the old declaration as a pass-through to the new one.
- Due to these complexities, I recommend against fine-grained strong code ownership (team member is the unit of ownership)

Branching (feature branch)
- mainstream approach = each member makes branch, make bunch of code, then merge (to trunk, master, dev, whatever)
- makes main branch clear, but not easy to integrate when isolation gets longer

I distinguish between merging and integration. If I merge mainline into my code, this is a oneway movement — my branch changes but the mainline doesn’t. I use `integrate` to mean a two-way process that pulls changes from mainline into my branch and then pushes the result back into mainline, changing both (isn't this two way concepts actually makes things too complicate?)

> Many people, therefore, argue for keeping feature branches short—perhaps just a couple of days. Others, such as me, want them even shorter than that. This is an approach called `Continuous Integration` (CI), also known as Trunk-Based Development.

With CI, 
- each team member integrates with mainline at least once per day.
- this prevents codes to diverting too far and thus greatly reduces the complexity of merges
- CI doesn’t come for free
   - It means you use practices to ensure the mainline is healthy
   - learn to break large features into smaller chunks, and
   - use feature toggles (aka feature flags) to switch off any in-process features that can’t be broken down.

CI is compatible with refactoring - Refactorings often involve making lots of little changes all over the code base

I’m not saying that you should never use feature branches. If they are sufficiently short, their problems are much reduced. (Indeed, users of CI usually also use branches, but integrate them with mainline each day.)

Even if you don’t go to full CI, I certainly urge you to integrate as frequently as possible.

Testing
- key characteristics of refactoring - doesn’t change the observable behavior of the program
- but what if i make mistake?zz
- in most cases, if I want to refactor, I need to have self-testing code

Refactoring can be a fantastic tool to help understand a legacy system.
- But the dragon guarding this happy tale is the common lack of tests

> The obvious answer to this problem is that you add tests. But while this sounds a simple, if laborious, procedure, it’s often much more tricky in practice. Usually, a system is only easy to put under test if it was designed with testing in mind—in which case it would have the tests and I wouldn’t be worrying about it.

crudely, it advises you to get the system under test by finding seams in the program where you can insert tests. Creating these seams involves refactoring—which is much more dangerous since it’s done without tests, but is a necessary risk to make progress.

database
- One difference from regular refactorings is that database changes often are best separated over multiple releases to production. This makes it easy to reverse any change that causes a problem in production. So, when renaming a field, my first commit would add the new database field but not use it.


#### Yagni

refactoring made changes in sw development
- prev: finish define archi -> coding
- now: continuous modification on archi


> The real impact of refactoring on architecture is in how it can be used to form a well-designed code base that can respond gracefully to changing needs. The biggest issue with finishing architecture before coding is that such an approach assumes the requirements for the software can be understood early on. But experience shows that this is often, even usually, an unachievable goal.

One way of dealing with future changes is to put flexibility mechanisms into the software.

As I write some function, I can see that it has a general applicability. To handle the different circumstances that I anticipate it to be used in, I can see a dozen parameters I could add to that function. These parameters are flexibility mechanisms—and, like most mechanisms, they are not a free lunch. Adding all those parameters complicates the function for the one case it’s used right now. If I miss a parameter, all the parameterization I have added makes it harder for me to add more. I find I often get my flexibility mechanisms wrong—either because the changing needs didn’t work out the way I expected or my mechanism design was faulty. Once I take all that into account, most of the time my flexibility mechanisms actually slow down my ability to react to change.

With refactoring, I can use a different strategy. Instead of speculating on what flexibility I will need in the future and what mechanisms will best enable that, I build software that solves only the currently understood needs, but I make this software excellently designed for those needs.

I use refactoring to adapt the architecture to those new demands.

이런 스타일을 `YAGNI` (You Ain’t Gonna Need it): 지금 필요한 것 만 넣자, 지금 필요 없으면 만들지 말자
- yagni를 하기 위해선 결국 리팩토링이 필요하다
- it is better to deal with issues later when I understand them better.

The first foundation for refactoring is self-testing code (meh)

#### performance
Refactoring can certainly make software go more slowly—but it also makes the software more amenable to performance tuning.


느낀점
- 그 테크톡(톡서버 자바 리팩토링) 발표에 리팩토링 책 이야기 나왔음 (난 거의 졸긴 함)
   - 인터페이스 의존성 (컴포지션 주입?)보다 함수 의존성이 더 좋다는 것처럼 말하던데 사실 파이썬 덕타이핑이 함수형 의존성 아닌가? 하는 생각이 들었음
- 짧은 커밋, observable change가 중요하다 - 어드민 리팩토링 중인데 알파배포 수십번은 한듯 ㅋㅋ
- 매니저가 이해못하면 말하지 않고 리팩토링해라 ㄷㄷ
- feature 단위로 브랜치를 따는 것이 리팩토링/CI와는 맞지 않는다고 해서 놀랐음 (피쳐가 커졌을 때 문제가 된다고 함)
   - 리팩토링 시의 작은 단위로 브랜치를 따면 되나?
- automated refactoring - 잘 되는 걸 본 적이...?
- 스타게이트 - 리팩토링 코스트가 너무 큰 케이스? ㅋㅋ
   - 테스트 - 손으로 많이 보고 있음...ㅜㅜ
-  yagni를 하기 위해선 결국 리팩토링이 필요하다 (제이)

### Chap 3 Bad smells in Code
Deciding when to start refactoring—and when to stop—is just as important to refactoring as knowing how to operate the mechanics of it.

we have learned to look for certain structures in the code that suggest—sometimes, scream for—the possibility of refactoring.

One thing we won’t try to give you is precise criteria for when a refactoring is overdue. In our experience, no set of metrics rivals informed human intuition.

#### Mysterious Names
- our code needs to be mundane and clear - One of the most important parts of clear code is good names.
- Renaming is not just an exercise in changing names. When you can’t think of a good name for something, it’s often a sign of a deeper design malaise.

#### duplicated codes
meh


#### Long function
In our experience, the programs that live best and longest are those with short functions
- All of the payoffs of indirection — explanation, sharing, and choosing — are supported by small functions
- real key to making it easy to understand small functions is good naming.
- A heuristic we follow is that whenever we feel the need to comment something, we write a function instead. Such a function contains the code that we wanted to comment but is named after the intention of the code rather than the way it works.
   - A block of code with a comment that tells you what it is doing can be replaced by a method whose name is based on the comment.

#### Long Parameter List
better than global variables, but long param lists are confusing in their own right

Classes are a great way to reduce parameter list sizes. They are particularly useful when multiple functions share several parameter values.

#### Global data
The problem with global data is that it can be modified from anywhere in the code base, and there’s no mechanism to discover which bit of code touched it.
   - At least when you have it wrapped by a function, you can start seeing where it’s modified and start to control its access.

#### Mutable data
Changes to data can often lead to unexpected consequences and tricky bugs.
- an entire school of software development—functional programming—is based on the notion that data should never change and that updating a data structure should always return a new copy of the structure with the change, leaving the old data pristine.

#### Divergent Change
The database interaction and financial processing problems are separate contexts, and we can make our programming life better by moving such contexts into separate modules.

#### Feature Envy
When we modularize a program, we are trying to separate the code into zones to maximize the interaction inside a zone and minimize interaction between zones.
- The fundamental rule of thumb is to put things together that change together.

#### Data Clumps
A good test is to consider deleting one of the data values. If you did this, would the others make any sense? If they don’t, it’s a sure sign that you have an object that’s dying to be born.

#### Replaced switch (to poly-sth)
The problem with such duplicate switches is that, whenever you add a clause, you have to find all the switches and update them.
- 객체구조로 만들면 안그래도 됨 ㅋㅋ

#### Loops
These days, however, first-class functions are widely supported, so we can use Replace Loop with Pipeline (231) to retire those anachronisms. (loops to pipeline?)
- pipeline operations, such as filter and map, help us quickly see the elements


#### Remove Middle Man
Encapsulation often comes with delegation. You ask a director whether she is free for a meeting; she delegates the message to her diary and gives you an answer. All well and good. There is no need to know whether the director uses a diary, an electronic gizmo, or a secretary to keep track of her appointments. c However, this can go too far. You look at a class’s interface and find half the methods are delegating to this other class. After a while, it is time to use Remove Middle Man (192)


#### Large Class
- When a class is trying to do too much, it often shows up as too many fields.
- common prefixes or suffixes for some subset of the variables in a class suggest the opportunity for a component.
- As with a class with too many instance variables, a class with too much code is a prime breeding ground for duplicated code, chaos, and death.

#### Data Class

Data classes are often a sign of behavior in the wrong place, which means you can make big progress by moving it (the functions over that class) from the client into the data class itself.



느낀점
- A heuristic we follow is that whenever we feel the need to comment something, we write a function instead. Such a function contains the code that we wanted to comment but is named after the intention of the code rather than the way it works. A block of code with a comment that tells you what it is doing can be replaced by a method whose name is based on the comment.
- Classes are a great way to reduce parameter list sizes. They are particularly useful when multiple functions share several parameter values.
   - 오브잭트 책에서는 철저히 협력 관계의 객체를 생각하라고 했던 것 같은데, 이런 바텀업도 뭐 나쁘진 않을 듯
- 뭐를 써서 어케 고칠 수 있다 하는데 뭐를 아직 안봐서 모르겠음. 두번 보기를 권장하는 구조인 듯
- Remove Middle Man: 아직 middle man이 생길 정도로 메시지를 왕창 주고받는 상황을 못 만들어 본 듯
- comments are often used as a deodorant zz


### Chap 4 Building Tests 

> To do refactoring properly, I need a solid suite of tests to spot my inevitable mistakes.

- most time is spent during debugging
- Make sure all tests are fully automatic and that they check their own results.
- Run the test frequently
  - so that only few subset of codes are possible cause of bug just spotted by the test
- Writing the tests means a lot of extra code to write.
  - This is not helped by the fact that many people have never learned to write tests or even to think about tests.

In fact, one of the most useful times to write tests is before I start programming. When I need to add a feature, I begin by writing the test.
- Writing the test also concentrates me on the interface rather than the implementation (always a good thing). It also means I have a clear point at which I’m done coding—when the test works.

The style I follow is to look at all the things the class should do and test each one of them for any conditions that might cause the class to fail.
- no need to test all functions (where the bugs are not likely to occur)

This pattern—write with a placeholder for the expected value, replace the placeholder with the code’s actual value, inject a fault, revert the fault—is a common one I use when adding tests to existing code.

sharing fixtures between tests is not good - it makes interaction between tests, which lead to nondeterminist result
- const in java only means that the ref is const. change in the obj that the var refers may happen
- make new fixture objs before each test


> nondeterminism in the tests that can lead to long and difficult debugging at best (and a collapse of confidence in the tests at worst)

setup - exercise - teardown

As a general rule, it’s wise to have only a single verify statement in each it clause. This is because the test will fail on the first verification failure—which can often hide useful information when you’re figuring out why a test is broken.

Think of the boundary conditions under which things might go wrong and concentrate your tests there.
- = playing the part of an enemy to my code

 many testing frameworks distinguish between this situation
 - `error` - an exception raised during an earlier phase (ex - setup).
 - regular `failure` indicates a verify step where the actual value is outside the bounds expected by the verify statement


type errors in input - How should the code respond to such a case?
- One approach is to add some handling that would give a better error response — either raising a more meaningful error message, or just setting producers to an empty array (with perhaps a log message). But there may also be valid reasons to leave it as it is. Perhaps the input object is produced by a trusted source—such as another part of the same code base. Putting in lots of validation checks between modules in the same code base can result in duplicate checks that cause more trouble than they are worth, especially if they duplicate validation done elsewhere. But if that input object is coming in from an external source, such as a JSON-encoded request, then validation checks are needed, and should be tested. In either case, writing tests like this raises these kinds of questions.

you cannot prove that a program has no bugs by testing. That’s true, but it does not affect the ability of testing to speed up programming.
- There is a law of diminishing returns in testing,

> Look at a function and consider the likely areas of error. Your tests will not find every bug, but as you refactor, you will understand the program better and thus find more bugs.

Architectures often are, rightly, judged on their testability.


느낀점
- 코멘트 -  encapsulation시킬 수 없으므로 관리 포인트가 늘어난다는 점에서 안좋은듯. 어드민 코드에 막 코멘트 넣다가 느낌
- "Writing the tests means a lot of extra code to write" - 진짜 그런 듯. 맨 처음 했을 떈 완전 별로였음
- 테스트 먼저 작성하면 좋다고 많이 들었는데 잘 안되는 듯. 프로젝트가 어느정도 만들어지고 나서는 좀 되긴 하는 듯
- 1년 전 쯤에는 랜덤데이터로 테스트하는게 가짓수도 늘어나지 않고 좋지 않나 하는 생각도 했었음 - 도메인이 간단해서 당시에는 별 문제 없었지만 좀만 복잡해져도 난리났을 듯
- 테스트 1개당 assert 1개는 너무..테스트가 늘어나지 않으려나 ㄷㄷ


### Chap 6 A First Set of Refactoring
most common refactoring - extraction (function / variable)

> Extraction is all about giving names, and I often need to change the names as I learn (about the system)

#### extract function
when to make (enclose to) new function?

> separation between intention and implementation. If you have to spend effort looking at a fragment of code and figuring out what it’s doing, then you should extract it into a function and name the function after the “what.”

any function with more than 6 lines of code starts to smell
- it’s not unusual for me to have functions that are a single line of code
- when there is distance between the intention of the code and its implementation, even len(func_name) > len(code) is accepted


#### extract variable
local variables may help break the expression down into something more manageable.


#### change function declaration
A good name allows me to understand what the function does when I see it called, without seeing the code that defines its implementation.

The parameters of a function dictate how a function fits in with the rest of its world. Parameters set the context in which I can use a function.
 (+applicability)


#### Encapsulate Variable
So if I want to move widely accessed data, often the best approach is to first encapsulate it by routing all its access through functions.

#### Rename Variable
Naming things well is the heart of clear programming. Variables can do a lot to explain what I’m up to—


#### Combine Functions into Class
Classes are a fundamental construct in most modern programming languages. They bind together data and functions into a shared environment, exposing some of that data and function to other program elements for collaboration. They are the primary construct in object-oriented languages,

#### Split phase
When I run into code that’s dealing with two different things, I look for a way to split it into separate modules. I endeavor to make this split because, if I need to make a change, I can deal with each topic separately and not have to hold both in my head together.


느낀점
- 코드를 읽고 뭐하는건지 알아내야 할 때 함수로 만들고 이름을 줘라. 지금까지는 책에 나왔던 대로 맨위에 코멘트 한 줄 달았는데, 앞으론 함수로 빼내야 할 듯
   - 단일 라인이라도 함수로 만드는 경우가 많다고 함 ㄷㄷ
- step by step으로 (내부 함수로 -> 가짜 파라미터 추가 등) 바꾸는 과정이 인상깊었음. 이건 의식적으로 따라해 봐야 할 듯
- 뭔가...지난날 했던 삽질이 떠오르면서 와닿는 부분이 있고 그런가? 하는 부분도 있음 (transformation 같은 부분). 아직 경험 (코드로 받은 고통?) 이 모자란 듯
- 함수 이름을 짓기 위한 좋은 방법 = 함수 밑에 코멘트를 달고 그걸 이름으로 바꾸기
- It is my habit to make all mutable data encapsulated
   - 다들 pydantic에서도 굳이 immutable로 만들고 카피해서 쓰긴 하니까..
- "although in a dynamically typed language like JavaScript, I do like to put the type into the name (hence parameter names like aCustomer)."
- split phase
  - 컴파일러 얘기를 하니까 와닿았음.
  - 차근차근 intermediate data를 만들고 함수를 분리하는 과정은 좋아보이긴 했는데...중간 데이터로 json (dict)를 쓰는 게 좋은 건진 잘 모르겠음. 너무 암시적이고, 이걸 받는 입장에선 안에 뭐가 있는지 모르니까 재사용하기도 힘들고..



### Chap 8 Encapsulation
"Classes were designed for information hiding."

As well as hiding the internals of classes, it’s often useful to hide connections between classes, which I can do with Hide Delegate (189). But too much hiding leads to bloated interfaces, so I also need its reverse: Remove Middle Man (192).

#### Encapsulate Record

This is why I favor objects over records for __mutable data__
- With objects, can hide what is stored and provide methods for all three values.

hashmap (python dicts) - The downside of using them is they are aren’t explicit about their fields.


#### Encapsulate Collection
- when getter returns the collection itself, it can be modified easily
   - provide update methods
   - java provides proxy for the col (raise exception when modification is tried)
   - never think that the ppl who take your method will not modify the collection zz

#### Replace Temp with Query
temp vars are useful when explaining its meaning and avoiding dup codes
- but sometimes its good to replace with func
- Putting this logic into functions often also sets up a stronger boundary between the extracted logic and the original function
- can reuse the funcs
- This refactoring works best if I’m inside a class, since the class provides a shared context for the methods I’m extracting.

그냥 모든 변수에 대한 ref를 펑션콜로 바꾸네
- 사이드 이펙트가 없는 함수로 바꿔야

#### Extract Class

> You’ve probably read guidelines that a class should be a crisp abstraction, only handle a few clear responsibilities, and so on. In practice, classes grow. You add some operations here, a bit of data there. You add a responsibility to a class feeling that it’s not worth a separate class—but as that responsibility grows and breeds, the class becomes too complicated. Soon, your class is as crisp as a microwaved duck.

Fowler, Martin. Refactoring (Addison-Wesley Signature Series (Fowler)) (p. 182). Pearson Education. Kindle Edition. 


splitting the class
- A good sign is when a subset of the data and a subset of the methods seem to go together.

#### Hide Delegate

- a.b.c() 보다는 a.b()가 당연히 좋긴 하고, 인캡슐레이션도 되긴 하겠지만..가능하면 피해야 하는 상황 아닐까 싶긴 함


#### Remove Middle man
Every time the client wants to use a new feature of the delegate, I have to add a simple delegating method to the server. After adding features for a while, I get irritated with all this forwarding. The server class is just a middle man (Middle Man (81)), and perhaps it’s time for the client to call the delegate directly. (This smell often pops up when people get overenthusiastic about following the Law of Demeter, which I’d like a lot more if it were called the Occasionally Useful Suggestion of Demeter.)

느낀점
- 코멘트 - 이전에 코멘트는 실행도 안되고 encapsulation도 안되고 그래서 결국 페브리즈 느낌이라고 했는데 openapi 문서용으로 쓰이는 코멘트는 괜찮지 않을까...하는 생각이 들었음 (많이들 보니까)
- Encapsulating a record means going deeper than just the variable itself; I want to control how it’s manipulated.
- In general, I find it wise to be moderately paranoid about collections and I’d rather copy them unnecessarily than debug errors due to unexpected modifications.
- inline class - 쓸일이 있을까 ㄷㄷ 책에 나온 대로 리팩토링 과정 중 합치고 다시 나누는 용도 외엔 잘 모르겠음
- remove middle man: - a.b.c() 보다는 a.b()가 당연히 좋긴 하고, 인캡슐레이션도 되긴 하겠지만..가능하면 피해야 하는 상황 아닐까 싶긴 함 - 이라고 생각했더니 다음 장에 바로 나옴
- 디미터의 법칙 - 객체지향 스터디떄 봤는데 기억이 안나서 다시 봤음..


- 클래스에 들어온 값 검증하는 걸 책임으로 주는 예제가 있던데, pydantic같은 거 쓰면 이런거 할 필요 없지 않나...도메인이 너무 휑하니 비어서 뭘 넣어야 할지 좀 애매함


### Chap 8 Moving Features


### move function
오..시작부터 명언작렬 ㄷㄷ

> The heart of a good software design is its modularity—which is my ability to make most modifications to a program while only having to understand a small part of it. To get this modularity, I need to ensure that related software elements are grouped together and the links between them are easy to find and understand. But my understanding of how to do this isn’t static—as I better understand what I’m doing, I learn how to best group together software elements. To reflect that growing understanding, I need to move elements around.

In OOP, the core modular context is a class

함수 이동 시, 함수의 컨텍스트를 고려한다 -> 함수의 컨텍스트를 생각해 본 적이 그닥 없는 것 같음..

polymorphic method일 시 이동이 어려워짐 -> 상속을 너무 쓰면 결합도를 높이긴 하는 것 같음..


#### move field


Programming involves writing a lot of code that implements behavior—but the strength of a program is really founded on its data structures. If I have a good set of data structures that match the problem, then my behavior code is simple and straightforward. But poor data structures lead to lots of code whose job is merely dealing with the poor data. And it’s not just messier code that’s harder to understand; it also means the data structures obscure what the program is doing.
- I may seek to move data because I find I always need to pass a field from one record whenever I pass another record to a function.
- Change is also a factor; if a change in one record causes a field in another record to change too, that’s a sign of a field in the wrong place.

역시 천천히 한 스텝씩 진행하는 게 인상적

#### Move Statements into Function

If I see the same code executed every time I call a particular function, I look to combine that repeating code into the function itself.


#### Move statement to caller
- 예시 (emitPhotoData) 보니까 어떤 동작인진 알았는데, 왜 옮기는 지는 좀 이해가 안됐음 (단순하게 설명하려고 만든 예시인 듯 함)

Functions are the basic building block of the abstractions we build as programmers. And, as with any abstraction, we don’t always get the boundaries right. As a code base changes its capabilities—as most useful software does—we often find our abstraction boundaries shift. For functions, that means that what might once have been a cohesive, atomic unit of behavior becomes a mix of two or more different things.

One trigger for this is when common behavior used in several places needs to vary in some of its calls. Now, we need to move the varying behavior out of the function to its callers.

함수가 여러 곳에서 조금씩 변형된 형태로 사용되서 파라미터도 많고 복잡해질 때, 바뀌는 내용을 때내서 caller들에게 주면 좋다

파이프라인 쪽 -> 플링크로?


#### Slide Statements
Code is easier to understand when things that are related to each other appear together.
- 사이드 이펙트를 내는 함수는 옮기기도 쉽지 않음. 예외 정도 말고는 가능하면 내지 말자고 생각했음

#### Split loop
- 확실히 도는 루프가 같다고 묶는 것 보단 의미상 다르면 떼어놓는 게 결합도를 낮추긴 할 듯

#### Replace Loop with Pipeline
- 최근 스타게이트 로깅 파이프라인을 플링크로 다시 짜고 있는데, 확실히 이런 류의 변환이 좋긴 한 것 같음
- ..설명


느낀점
- 파이프라인
- 별 내용은 없지만 remove dead code 챕터를 따로 만든 거 보니, 프로덕션에서 어려 컨설팅 하면서 죽은 코드에 고통을 많이 받으셨던 듯...? 코멘팅 하지 말고 깃을 이용하