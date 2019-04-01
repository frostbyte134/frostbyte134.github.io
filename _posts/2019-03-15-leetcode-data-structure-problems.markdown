---
layout: post
title:  "Leetcode - Data Structure Problems"
date:   2019-03-15 1:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode array stack queue need_review
---

### Min stack
<a href="https://leetcode.com/problems/min-stack/" target="_blank">https://leetcode.com/problems/min-stack/</a>

stack의 최소값 - pair를 저장하면 됨. 큐와는 달리 top 밑에 있는 애들이 안빠지므로..


### Rotate image

<a href="https://leetcode.com/problems/rotate-image/submissions/" target="_blank">https://leetcode.com/problems/rotate-image/submissions/</a>

행렬 90도 rotation

1. transpose + column exchange
2. 4개의 점끼리만 바꾸기. Row 2개로 swap하려고 해서 잘 안풀려서 1번으로 풀음


### Sudoku Solver

답이 무적권 있다고 해서 backtracking에서 각 시도 중 답이 무조건 나오는 게 아니지...취소해야 할 수도 있는 것인데요 ㅡㅡ

너무 오랜만에 문제풀이를 하나...
	

### Container With Most Water

<a href="https://leetcode.com/problems/container-with-most-water/" target="_blank">https://leetcode.com/problems/container-with-most-water/</a>

기본시도: 정렬가능시 정렬 (이문제 아님), 왼 안되면 왼+오, ...

스택으로 푸는 그 문제인 줄 알았다 ㅡㅡ 낙시쩔음

```python
class Solution:
    def maxArea(self, height: 'List[int]') -> 'int':
        fr, to = 0, len(height)-1
        ans = 0
        while(fr < to):
            ans = max(ans, min(height[fr], height[to]) * (to - fr))
            if height[fr] < height[to]:
                fr = fr + 1
            else:
                to = to - 1
        return ans
                         
                
```

### Smallest Range
<a href="https://leetcode.com/problems/smallest-range-ii/" target="_blank">https://leetcode.com/problems/smallest-range-ii/</a>

1. 처음엔 [2][10000]의 동적계획법인가 했었다. 
	1. 부분문제 구조가 없어 보이고
	2. 상태공간 구성이 말도 안되서 포기
2. min-max 로 풀 수 있는 그리디인가 싶어 계속 해맴
3. 핵심은 결국, 리스트 정렬시 [K를 더하는 쪽, K를 빼는 쪽] 으로 나뉜다는 것.  
그렇다면 리스트를 임의로 나눴을 시 유의미한 숫자는 4개,
	1. K를 더하는 쪽의 첫번째 + K
	2. K를 더하는 쪽의 마지막 + K
	1. K를 빼는 쪽의 첫번째 - K
	2. K를 빼는 쪽의 마지막 - K
	
	4개만 검사하면 됨.
	

```python
class Solution:
    
    def smallestRangeII(self, A: 'List[int]', K: 'int') -> 'int':
        
        A.sort()
        maxx, minn = A[-1] - K, A[0] - K
        ans = maxx - minn
        for i in range(len(A)-1):
            ary = [A[-1] - K, A[0] + K, A[i] + K, A[i+1] - K]
            ans = min(ans, max(ary) - min(ary))
        
        return ans
```

### Twosum

<a href="https://leetcode.com/problems/two-sum/" target="_blank">https://leetcode.com/problems/two-sum/</a>


1. Naive \\(O(N^2)\\)
```python
class Solution:
    def twoSum(self, nums: 'List[int]', target: 'int') -> 'List[int]':
        dic = {}
        for i in range(len(nums)-1):
            if nums[i] in dic: continue
            dic[nums[i]] = 1;
            for j in range(i+1, len(nums)):
                if nums[i] + nums[j] == target:
                    return [i, j]
```

2. reducing 1 iteration with hash
```python
class Solution:
    def twoSum(self, nums: 'List[int]', target: 'int') -> 'List[int]':
        dic = {}
        for i, num in enumerate(nums):
            if num in dic:
                return [i, dic[num]]
            dic[target - num] = i
```