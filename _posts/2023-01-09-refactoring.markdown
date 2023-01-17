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
