---
layout: post
title:  "SW Design Patterns (GOF + GURU) 개발-패턴"
date:   2022-04-02 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---

(작성-중) 


<a href="https://refactoring.guru/design-patterns/catalog" target="_blank">https://refactoring.guru/design-patterns/catalog</a>

정리를 그냥 [여기](https://github.com/nailbrainz/issues)다가 해 놨음. 가서 보기


### Glossary
- `concrete subclass` - abstract method를 전부 구현한 서브클래스 (자바 관련인듯?)

### SOLID
- solid = 마틴 어쩌고 님이 짜깁기한 거
- 일단 코드를 짜보고 민감하게 신경 쓴 경험치가 필요
- 남용하면 가독성/직관성이 떨어진다
- `yagni` - you ain't gonna need it
- "변경, 유지보수를 쉽게 하기 위한 것"
    - 변경이 필요없으면 오버킬
    - 너무 원칙을 적용하면 리더빌리티를 해칠 수 있음

#### SRP
보통 책임 = 협력관계 내에서 오브젝트가 가지는 역할, 스코프
- srp에서의 책임 = 클래스의 변경 (?)
- 클래스를 변경하는 이유가 2가지가 되어서는 안됨
    - animal의 행동 묘사 + db에 저장 (persistent)
    - 행동이 바뀔 때에도 animal 클래스 변경, db에 저장할때도 변경 = SRP violation

제일 중요
- "책임"의 정의에 따라 적용이 달라질 수 있음
- 제이의 팁 = 멤버변수가 너무 많아지먄 srp를 어기지 않았나 생각해 보는 것도 좋음

#### ocp (open-closed principle, 확장에 열리고 변경에 닫힘)
- 클래스를 갖다 쓰는 곳에서는 구조에 대해 몰라도 되고, 인터페이스만 알면 됨
- 구조를 참고해서 쓰면 구조 변경 시 갖다쓰는 곳에서도 변경 필요. 인터페이스만 알면 몰라도 됨
- isinstance, dynamic_cast, 복잡한 이프엘스문이 많으면 의심해 볼 것

#### LSP (Liskov substitution)
상위객체를 하위객체로 바꿀 수 있어야 함 (상위 = 추상화, 하위 = 구현 세부사항이 담긴 하부 객체)
- rectangle / square problem
- rect을 상속받아 square를 만듬 (width/height 각자 설정해도  - 다른 것 까지 변함) = height2배, width2배 하는 경우 square는 16배 됨
- ocp와 마찬가지로 isinstance, dynamic_cast, 복잡한 이프엘스문 (인스턴스에 따라 다른 행동을 해야 하므로)

추상화의 목적이 아니라 공통코드의 모음으로 베이스 클레스를 사용하는 경우
- 이 경우 고치기가 힘듬. 인터페이스 화가 되어야 함. 역할로 구분지은 것이 아니라 코드만 모아 놓은 것임.
- 이 경우 (공통코드 모음집) 다른 클래스가 나와서 컴포지션이 되는 것이 좋음 (흠...)

__circle and ellipse problem__
- 믹스인? 상속이랑 구별되니까 좋다? 뭐지 이게 (c++의 템플릿처럼)

#### interface segragation principle
DIP를 해결하기 위해 DI (dependency injection)을 씀


### Creational Patterns
- abstracts the instantiation process (객체 생성에서도 추상에 의존하기 위함, DIP)
- class creation / object creation?? 다른 건가
- 시스템이 알게 되는 것은 객체성성용 인터페이스 뿐 (각 concrete class들의 디테일/서로 어떻게 연결되어 있는지는 몰라도 됨)
- <a href="https://github.com/nailbrainz/issues/4" target="_blank">abstract factory / factory / singleton</a>
- <a href="https://github.com/nailbrainz/issues/5" target="_blank">prototype / singleton / adapter</a>
- <a href="https://github.com/nailbrainz/issues/6" target="_blank">Bridge / Composite / Decorator</a>