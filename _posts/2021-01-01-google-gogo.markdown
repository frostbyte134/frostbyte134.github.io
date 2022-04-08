---
layout: post
title:  "well"
date:   2021-01-07 08:00:05 +0800
categories: probability
use_math: true
tags: math probability bandit basic_regret_decomposition_identity
---


머신 러닝 엔지니어 면접 구성은 다음과 같음

구글 온사이트 기준 (다른 큰 회사들도 대동소이함)
코딩 인터뷰 x 2
코딩+머신러닝 인터뷰 x 1
시스템디자인+머신러닝 인터뷰 x 1
인성 인터뷰 x 1

코딩 인터뷰 x 2 이건 그냥 릿코드 양치기 돌리면 되니까 이글에선 안다루겠음. 일반 swe의 코딩인터뷰랑 완전히 같음
코딩+머신러닝은 그냥 코딩인터뷰랑 진행형식은 완전히 같은데 머신러닝 지식 없으면 못푸는 문제들. 그러니까 머신러닝 엔지니어는 릿코드도 풀어야되고 ML유형 코딩인터뷰도 풀어야됨.

여러 회사 면접보면서 본 기출들 공유해봄

1. 부동산 가격을 예측하는 모델을 만들고 싶다. 데이터를 모았는데 데이터셋 중 일부는 어떤 피쳐들이 누락되었다. 이때 이에 대처하는 모델을 구현하라. 피쳐 일부가 누락된 데이터셋을 그냥 버리면 당연히 안된다.
Follow-up) 샘플들이 어떤 피쳐가 누락되었는지 종류가 샘플별로 다르다면?
Follow-up2) 피쳐가 완전히 온전한 샘플이 하나도 없다면?

2. 아마존에서 똑같은 상품의 판매자가 여럿 있다. 각각 판매자의 리뷰 좋아요/싫어요 수가 있을 때 이를 기반으로 가장 나은 판매자를 베이지안식으로 구현하라.
Follow-up) 좋아요/싫어요가 아니라 1~5까지 별점갯수로 주어진다면?

3. 체스에서 매칭에 쓰이는 내부 레이팅 함수를 구현하라.
Follow-up) 롤처럼 다대다 게임이 된다면?

시스템디자인)
유튜브 추천시스템 디자인
구글 검색엔진 시스템 디자인
구글렌즈 활자인식 시스템 디자인

---------------------------


구글코리아는 아니고 미국 구글 대졸신입 인터뷰를 몇개월 전에 봤어요.

저는 말씀하신대로 면접관이랑 이야기 하면서 솔루션 만들어갔어요.

일단 처음에 문제 받으면 바로 코딩시작하진 않고, 문제에서 정의되지 않았지만 문제 해결을 위해 필요한 질문들 몇가지를 해서 vague한 requirement를 정의를 했어요.

그 다음에 "문제를 읽어보니 이 부분 때문에 일단 이러이러한 자료구조가 떠오른다. 이 문제가 원하는게 이러이러한 솔루션이니 이 자료구조를 이렇게이렇게 사용해 알고리즘을 이렇게 이렇게 짜면 될거같다. 알고리즘을 이렇게 짜면 런타임은 이러이러해서 O(n)(예시) 가 되고 space complexity도 이러이러해서 O(n)(예시) 가 된다" 이런 얘기를 좀 더 살을 붙여서 면접관이랑 하다가 코딩 시작했습니다. 코딩 하면서도 내가 이 코드를 왜 이렇게 하는지 면접관이랑 계속 얘기도 하고요.

내 솔루션을 만들어갈때 왜 이렇게 하는지를 면접관에게 이해시키지 않고 띡 풀어버리기만 하면 탈락될 가능성이 높을 것 같습니다.

문제 푸는 과정은 구글이 자체적으로 만든 web text editor가 따로 있어거 거기다가 했어요


--------------------

### 영어 긴거
https://www.youtube.com/watch?v=XKu_SEDAykw
- 코딩 시작하기전 3개 솔루션 다 다룸
- 엣지케이스 (empty array)도 언급 (이거 중요한 듯), 이걸 어떻게 해결할껀지도 말함
- 난 값의 범위, 정렬도ㅒㅆ는지만 물어봤는데 중복허용도 중요했는듯
- 마지막에 let me go through examples to make sure - 이거 시간끌기 좋은듯 
  
### 한국꺼
https://www.youtube.com/watch?v=BF3FLDAzWxo

### 음
https://www.youtube.com/watch?v=OMkfujDPpwc

### 미쿡2?
https://www.youtube.com/watch?v=uQdy914JRKQ


### 파이썬 해싱
- open addressing이긴 한데 (chaining은 아니고), <a href="https://github.com/python/cpython/blob/3.7/Objects/dictobject.c#L133" target="_blank">linear probing보다 좀 더 복잡</a>


### 음
https://medium.com/acing-ai/google-ai-interview-questions-acing-the-ai-interview-1791ad7dc3ae


### 해시테이블
1. direct address = ps할때 많이 하는거. 키 그대로 사용
2. hash table
    1. chaining = worst search O(N), avg O(1) if 테이블 크기가 키 크기에 대충 비례한다면. __worst insert O(1)__ - doubly linked 쓰면 바로 맨 뒤로 ㄱㄱ 가능
    2. open addressing
        - 삭제를 걍 하면 안됨 (이후 search probing 중 거기서 끊김) -> NIL과 DELETED 구분해야 함
