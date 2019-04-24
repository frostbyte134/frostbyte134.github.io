---
layout: post
title:  "Leetcode - reference problems"
date:   2019-04-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review reference_problem
---

### Best time to buy and sell stock
<a href="https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/submissions/" target="_blank">https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/</a>

1. DP
\\[\text\{maxx\}[i] = \max(\text\{maxx\}[i], \text\{maxx\}[i-1], ary[i] - ary[j] + \text\{maxx\}[j-2]),\\ j=1,...,i-1\\]
when j<2, maxx[j-2] = 0 (there is no profit we can obtain in day=i=0, 1)
2. __Notice__ that, the term \\(- ary[j] + \text\{maxx\}[j-2])\\) is calculated over and over

### Next permutation

<a href="https://leetcode.com/problems/next-permutation/" target="_blank">https://leetcode.com/problems/next-permutation/</a>

Permutation의 다음번째는 무엇인가? (lexicographical order)

1. Permutation이므로 swap
2. lexi-order이므로, 자릿수가 작은 숫자를
	1. 자기보다 자릿수가 더 낮으면서
	2. 값은 더 큰 숫자
	3. 중 최소의 숫자와 바꿔야 함.
	
	이렇게 i번째 숫자를 j(<i) 번째 숫자와 바꾸었으면, i-1번째부터는 작은 순으로 정렬해주어야 함. 그래야 바로 다음번이 되니까.
3. 위에 해당하는 경우가 없을 시, 모든 숫자는 자기보다 자릿수가 낮은 숫자보다 큼. (ex - 4321) 문제에서 이러면 낮은순정렬하랬으므로 1d transpose해줌



### Finding cycle in linked list
<a href="https://leetcode.com/problems/linked-list-cycle-ii/" target="_blank">https://leetcode.com/problems/linked-list-cycle-ii/</a>

1. travel with `slow` (goes 1 pointer in a time) and `fast` (goes 2 point in a time)
2. Let
* \\(L\_1\\): distance between the starting point and cycle entrance
* \\(L\_2\\): distance between the cycle entrance and meeting point
* \\(C\\): cycle length
* \\(n\\): number of times `fast` ran through circle until it meets with `slow`
그러면,
1. \\(2(L\_1+L\_2)=L\_1+L\_2+nC\\)
2. \\(n=1\\): 어차피 `fast`와 `slow`는 1번에 1칸씩밖에 차이가 안나기때문에, `fast`는 1번의 순회만으로 `slow`와 만남.

그러므로, \\(L\_1+L\_2=C \quad\rightarrow\quad L\_1=C-L\_2\\). 현재 slow위치에서 계속 앞으로 나가고, starting point에서 앞으로 나가면 만나는곳이 cycle entry가 됨.

### Coin change

<a href="https://leetcode.com/problems/coin-change/" target="_blank">https://leetcode.com/problems/coin-change/</a>

문제자체는 별거 없는, 동전교환 dp인데..
```python
dp[val] = min([dp[val - c]+1 if val - c >= 0 else float("inf") for c in coins])
```
으로 푸는게 2차원 배열에 동전갯수번만큼 min 을 해주는 것보다 2배는 빨랐다. ㄷㄷ해.  
결론:
1. 다수의 min/max보다는 List comprehension을 쓰자!
2. `float("inf")`

### Task Scheduler
<a href="https://leetcode.com/problems/task-scheduler/" target="_blank">https://leetcode.com/problems/task-scheduler/</a>

1. task 갯수가 n+1번째보다 많을 시, 억지로 n+1에 끼워넣기보단 n+1보다 더 벌리는 것이 좋음. 그림을 그러보면 알기 쉬운데, 전자는 net loss가 발생하기 때문
2. 위와 같이 하고, 중복 고려해서 마지막 끝나는 시간을 찾으면 됨