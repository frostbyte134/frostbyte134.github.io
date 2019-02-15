---
layout: post
title:  "Leetcode - Two Sum"
date:   2019-02-14 10:59:00
categories: python
use_math: true
tags: problem_solving leetcode need_review
---

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