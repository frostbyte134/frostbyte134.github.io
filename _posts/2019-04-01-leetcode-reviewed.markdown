---
layout: post
title:  "Leetcode - reviewed"
date:   2019-04-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode
---

### Subarray Sum Equals K
https://leetcode.com/problems/subarray-sum-equals-k/

부분합문제인데 N^2로 풀면 TLE남.  
힌트는 값의 범위가 좁다는거였음. dic에 지금까지 나온 값들 저장해놓고 체크하면 됨.  
`collections.counter`를 쓰면 더 빨라지는듯?


### Find All Numbers Disappeared in an Array
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

리스트 값이 리스트 내부와 range가 같고, 리스트를 체크해야 할 시 리스트 값이 -를 해두면 좋은듯


### Min stack
<a href="https://leetcode.com/problems/min-stack/" target="_blank">https://leetcode.com/problems/min-stack/</a>

stack의 최소값 - pair를 저장하면 됨. 큐와는 달리 top 밑에 있는 애들이 안빠지므로..


### Rotate image

<a href="https://leetcode.com/problems/rotate-image/submissions/" target="_blank">https://leetcode.com/problems/rotate-image/submissions/</a>

행렬 90도 rotation

1. transpose + column exchange
2. 4개의 점끼리만 바꾸기. Row 2개로 swap하려고 해서 잘 안풀려서 1번으로 풀음


### Regular expression
 
```python
class Solution:
    
    def cache_memoization(func):
        __cache = {}
        def wrapper(*args):
            if args in __cache:
                return __cache[args]
            else:
                result = func(*args)
                __cache.update({args:result})
                return result
        return wrapper
    
    @cache_memoization
    def isMatch(self, s: 'str', p: 'str') -> 'bool':
        if not p:
            return not s
        
        if len(p) >= 2 and p[1] == '*':
            if len(s) > 0:
                if p[0] == '.' or p[0] == s[0]:
                    return self.isMatch(s[1:], p) or self.isMatch(s[1:], p[2:]) or self.isMatch(s, p[2:])
            return self.isMatch(s, p[2:])
        
        
        if len(s) > 0 and len(p) > 0 and (s[0] == p[0] or p[0] == '.'):
            return self.isMatch(s[1:], p[1:])
        
        return False
        
```

* 클래스 내부에서 멤버함수 호출: 멤버변수와 같이 self.붙여줘야
* 메모이제이션 쩌네. 2차원 dp로 풀라다 실패. 생각해보니 이렇게 재귀함수 짜고 2차원 dp했어도 걍 풀었을듯. 재귀 먼저 짜자