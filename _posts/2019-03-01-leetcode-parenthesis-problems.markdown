---
layout: post
title:  "Leetcode - Parentheses problems"
date:   2019-03-01 1:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review dp dfs bfs
---

### Generate Parentheses

<a href="https://leetcode.com/problems/generate-parentheses/" target="_blank">https://leetcode.com/problems/generate-parentheses/</a>

n개의 parentheses로 가능한 모든 조합을 만드는 문제

1. 재귀 - dp로 풀음
2. backtracking - 새로운 parentheses는 항상 오른쪽에 붙인다고 하면 backtracking 가능  
3. 어떻게 붙여도 숫자만 맞고, 오른쪽에 붙이므로 )를 먼저 다 쓰는 일 없이 r > l일때만 )를 써주면 valid함.

dfs나 bfs로 상태공간 탐색가능

```python
class Solution:
    
    def solve(self, l, r):
        if l == 0 and r == 0:
            return [""]
        ret = []
        
        if l != 0:
            ret += ["(" + item for item in self.solve(l-1, r)]
        if r != 0 and r > l:
            ret += [")" + item for item in self.solve(l, r-1)]
        if l == 0 and r != 0:
            return [")"*r]
        
        return ret
    
    def generateParenthesis(self, n: int) -> List[str]:
        return self.solve(n, n)
```


### Longest Valid Parenthesis
<a href="https://leetcode.com/problems/longest-valid-parentheses/submissions/" target="_blank">https://leetcode.com/problems/longest-valid-parentheses/submissions/</a>

핵심: `이전` 레벨의 시작으로 거리를 구하는 것. cur에 저장

cur = -1

1. (를 만났을 시
    1. `이전` 레벨의 시작(cur)을 스택에 저장
    2. 현재 레벨의 시작을 cur에 세팅
2. )를 만났을 시
    1. 이전에 쌓은 (가 없는 경우 - cur을 현재로 갱신해줌
    2. 있는 경우 - 이전 레벨의 시작 (st.top())과 현재의 거리를 답에 반영 후, pop. 

이렇게 하는 이유는, ()()나 (()()) 같은 경우를 해결하기 위해서.

```python
def longestValidParentheses(self, s: str) -> int:
    st = []
    
    lvlStart = -1
    ans = 0
    for i, ch in enumerate(s):
        if ch == '(':
            st.append(lvlStart)
            lvlStart = i
        else:
            if len(st) == 0:
                lvlStart = i
            else:
                lvlStart = st.pop()
                ans = max(ans, i - lvlStart)
        
    return ans
```