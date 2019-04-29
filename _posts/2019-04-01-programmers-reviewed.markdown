---
layout: post
title:  "Programmers - reviewed"
date:   2019-04-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode
---

### N으로 표현
https://programmers.co.kr/learn/courses/30/lessons/42895

두 가지 고려가 필요
1. (AAA/AA+AAA..) (+-*/) (AA-AAA+..) 의, 2항을 전부 변형시켜야 함. 처음엔 재귀로 풀었는데 1번째 항만 변형시켜서 계속 틀림.  
2항만 고려하면, 나머지 경우는 lvl을 늘려가며, n번째에서 자기보다 작은 경우의 항과 연산을 다 해보면 됨. 예를들어 k를 2번씩 쓴 3항은, 6번째 계산에서 k를 2번씩 2번 쓴 (2+2) 항과 2번 쓴 항과의 모든 조합을 만들 떄 고려됨.
2. 각 n번째 탐색 시, k*n의 문자열을 넣어주어야 함.

dp라는데 별로 dp같지가 않은 느낌적인 느낌..
내 코드 말고 이 답이 좀 맘에 드네. 근데 -N도 넣어줘야 하는거 아님?
```python
def solution(N, number):
    S = [{N}]
    for i in range(2, 9):
        lst = [int(str(N)*i)]
        for X_i in range(0, int(i / 2)):
            for x in S[X_i]:
                for y in S[i - X_i - 2]:
                    lst.append(x + y)
                    lst.append(x - y)
                    lst.append(y - x)
                    lst.append(x * y)
                    if x != 0: lst.append(y // x)
                    if y != 0: lst.append(x // y)
        if number in set(lst):
            return i
        S.append(lst)
    return -1
```


### 단속카메라
https://programmers.co.kr/learn/courses/30/lessons/42884

### 섬 연결하기
https://programmers.co.kr/learn/courses/30/lessons/42861

### 쇠막대기
https://programmers.co.kr/learn/courses/30/lessons/42585  
난 stack lvl을 세는 변수를 하나 뒀는데, 그냥 스택의 길이면 됬었네. 
