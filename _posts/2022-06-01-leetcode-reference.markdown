---
layout: post
title:  "Leetcode problems - ref problems"
date:   2021-05-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review
---

뭔가 기억해두면 이득일 것 같은 문제들



### Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit (window problem, need review)
- <a href="https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/" target="_blank">https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/</a>
- 윈도우 안의 최대/최소의 차이. map으로 풀어서 하위 20퍼로 풀긴 함
- PQ/디큐 - increasing_deque는 맨 앞이 구간의 최소값, decreasing_deque는 맨 앞이 구간의 최대값임 (맨 뒤는 항상 새로 추가된 원소).
  - 이 때 조심해야 할 게, 현재 구간 (디큐들에 들어있는 아이템들의 min, max정보가 유효한 구간)은 max(inc디큐에서 제일 최근에 빠진 인덱스+1, dec디큐에서 제일 최근에 빠진 인덱스+1)이라는 것


### Valid square
<a href="https://leetcode.com/problems/valid-square/" target="_blank">https://leetcode.com/problems/valid-square/</a>

4개의 점이 주어졌을 시, 정사각형인가?
* 첨에 회전을 생각안해서 함 틀림
* 꼭 각으로 풀어야 할까...?ㅋㅋ 거지같넹. 기억정도 해 두면 좋을 듯

### https://leetcode.com/problems/minimum-number-of-refueling-stops/
https://leetcode.com/problems/minimum-number-of-refueling-stops/
- 좋은 문제인 듯. 다시풀기 필수
- 밑이랑 세트로 기억하면 좋을 듯

#### Sort Colors
* <a href="https://leetcode.com/problems/sort-colors/description/" target="_blank">https://leetcode.com/problems/sort-colors/description/</a>
* 다시 쉽게 풀긴 했는데, 풀이방법 2개 돌아보고 넣을 정도는 됨. 보기만 하고 넣자
* <details>
   <summary>풀긴 품</summary>빠르게 안됐음. 다시 한번 풀어볼 정도?</details>

#### LRU Cache
<a href="https://leetcode.com/problems/lru-cache/" target="_blank">https://leetcode.com/problems/lru-cache/</a>
linked list + hash = O(1) LRU Cache!

#### 2-sum problems
1. 2-sum - lr (O(N))
2. 3-sum - 2sum * N
3. 4-sum - 3sum * N

### https://leetcode.com/problems/image-overlap/description/
이것도 답 봄. 문제도 제대로 안보고 풀었음 ㅎㅎ 

### https://leetcode.com/problems/course-schedule-iii/description/
https://leetcode.com/problems/course-schedule-iii/description/
* <details>
   <summary>오 문제좋다</summary> 
   다시 ㄱㄱ
   </details>

#### Next permutation

<a href="https://leetcode.com/problems/next-permutation/" target="_blank">https://leetcode.com/problems/next-permutation/</a>

Permutation의 다음번째는 무엇인가? (lexicographical order)

1. Permutation이므로 swap
2. lexi-order이므로, 자릿수가 작은 숫자를
	1. 자기보다 자릿수가 더 낮으면서
	2. 값은 더 큰 숫자
	3. 중 최소의 숫자와 바꿔야 함.
	
	이렇게 i번째 숫자를 j(<i) 번째 숫자와 바꾸었으면, i-1번째부터는 작은 순으로 정렬해주어야 함. 그래야 바로 다음번이 되니까.
3. 위에 해당하는 경우가 없을 시, 모든 숫자는 자기보다 자릿수가 낮은 숫자보다 큼. (ex - 4321) 문제에서 이러면 낮은순정렬하랬으므로 1d transpose해줌




#### search a 2d matrix

<a href="https://leetcode.com/problems/search-a-2d-matrix-ii" target="_blank">https://leetcode.com/problems/search-a-2d-matrix-ii</a>

\\(m\times n\\) 행렬이, 행 / 열 별로 독립적으로 정렬되어 있을 시,

1. 난 그냥 m*logn으로 풀음
2. 행렬은 각 element 별로 4개로 쪼갤 수 있다. 왼위가 자기보다 무조건 작은 곳, 오른아래가 무조건 자기보다 큰 곳.  
   왼쪽 위부터 시작하지 말고, 오른쪽 위부터 시작해서
   1. ary[i][j] < target: 더 큰 수 를 찾아야 하므로, 오른 아래는 무조건 없다. 왼쪽으로 빠꾸. 위는 예전에 갔으므로 갈 필요가 없음.
   2. ary[i][j] > target: 더 작은 수를 찾아야 하므로, 왼위는 무조건 없다. 아래로 ㄱ. 오른쪽은 오른쪽부터 시작했으므로 갈 필요가 없음.  
   의 방식으로 \\(\mathop\{O\}(m+n\\) 탐색 가능.
3. 오른쪽 위부터 시작할 수 있는 근거 - 맨 왼쪽은 자기보다 작은 것 들, 아래는 자기보다 큰 것들만 있어서. 이 속성을 계속 유지가능




#### First Missing Positive (need review)
<a href="https://leetcode.com/problems/first-missing-positive/" target="_blank">https://leetcode.com/problems/first-missing-positive/</a>
* smallest nonnegative
* <details>
   <summary>다시풀기</summary> 
   smallest nonnegative = 배열에 저장 가능. 내지는 마킹해놓기 (모듈로로 판별)
   </details>


### Minimum Window Substring
<a href="https://leetcode.com/problems/minimum-window-substring/" target="_blank">https://leetcode.com/problems/minimum-window-substring/</a>

* 긴 string s에서 짧은 string t의 permutation을 포함하는 substing의 최소길이를 찾아야 함
* Permutation을 포함만 하면 되므로, count가 적었다가 같아지는 순간이 중요
* 윈도우 (2 indices - st, ed)로 체크함.   
    1. ed : 고정된 st에서, permutation을 포함하는 최소 끝점을 찾음
    2. st : 해당 ed에서, permutation을 포함할 때 까지 줄여감
* 왠일로 하드를 수월하게 풀었네...?

#### Merge Intervals

<a href="https://leetcode.com/problems/merge-intervals/" target="_blank">https://leetcode.com/problems/merge-intervals/</a>

1. 인터벌 (a, b)들을 오름차순으로 정렬
2. valid non-intersecting interval 집합을 유지한다고 할 시, 현재 고려중인 interval은 
    1. valid 집합의 마지막 interval보다 a값은 크다
    2. 따라서, valid 집합의 마지막 interval과 머지되지 않을 시, 나머지들과 머지될 일은 없음.



#### Finding cycle in linked list
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

그러므로, \\(L\_1+L\_2=C \quad\rightarrow\quad L\_1=C-L\_2\\). 만일 fast와 slow가 만났다면 (cycle 있음), 현재 slow위치에서 1칸씩 앞으로 나가고, 다시 starting point에서 1칸씩 앞으로 나가서 만나는곳이 cycle entry가 됨.

<a href="https://leetcode.com/problems/linked-list-cycle-ii/discuss/44781/Concise-O(n)-solution-by-using-C%2B%2B-with-Detailed-Alogrithm-Description" target="_blank">editorial</a>

#### Task Scheduler
<a href="https://leetcode.com/problems/task-scheduler/" target="_blank">https://leetcode.com/problems/task-scheduler/</a>

1. task 갯수가 n+1번째보다 많을 시, 억지로 n+1에 끼워넣기보단 n+1보다 더 벌리는 것이 좋음. 그림을 그러보면 알기 쉬운데, 전자는 net loss가 발생하기 때문
   1. A가 가장 많이 발생했다고 할 때, A??A??A??A 에서 ??에 나머지를 끼워 넣을 수 있는 경우, 마지막 A가 답. 없는 경우 그만큼 싸이클을 더 늘리면 만사 OK!
2. 위와 같이 하고, 중복 고려해서 마지막 끝나는 시간을 찾으면 됨

우선순위 큐를 써도, 결국 N+1에 끼워맞추는거보단 N+1보다 더 큰 cycle을 쓰는 것이 좋아서 


#### Generate Parentheses

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



#### N-Queens (reference problem)
<a href="https://leetcode.com/problems/n-queens/" target="_blank">https://leetcode.com/problems/n-queens/</a>

1. Naive - on the board
2. 보드보다 상태공간을 더 잘 표현할 수 있음
    1. queen의 위치는, 1-d array의 위치가 row, 값이 column
    2. position의 조건이, rowInd+colInd와 rowInd-colInd 가 같으면 같은 대각에 있는 것이므로, 위의 두 값을 queen의 위치와 같이 저장. 같은 row/col체크는 하지 않을 것 (위에서 이미 결정하고 오므로)
    3. naive board solution은 정말 보드를 다 찾아보지만 이 solution은 row별로 어디에 놓을지만 결정해도 되므로 시간절약도 많이 될듯


#### Smallest Range 
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
4. 면접에 나오는 문제는 아니지만...함 봐보자

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


### Reviewed

#### Coin change

<a href="https://leetcode.com/problems/coin-change/" target="_blank">https://leetcode.com/problems/coin-change/</a>

문제자체는 별거 없는, 동전교환 dp인데..
```python
dp[val] = min([dp[val - c]+1 if val - c >= 0 else float("inf") for c in coins])
```
으로 푸는게 2차원 배열에 동전갯수번만큼 min 을 해주는 것보다 2배는 빨랐다. ㄷㄷ해.  
결론:
1. 다수의 min/max보다는 List comprehension을 쓰자!
2. `float("inf")`






#### Rotate image

<a href="https://leetcode.com/problems/rotate-image/submissions/" target="_blank">https://leetcode.com/problems/rotate-image/submissions/</a>

행렬 90도 rotation
<details>
   <summary>보기만</summary> 
    transpose + column exchange / 4개의 점끼리만 바꾸기. Row 2개로 swap하려고 해서 잘 안풀려서 1번으로 풀음
   </details>



### Stock Price Fluctuation
<a href="https://leetcode.com/problems/stock-price-fluctuation" target="_blank">https://leetcode.com/problems/stock-price-fluctuation</a>
- EZ




#### Regular expression
 
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

### Max Sum of Rectangle No Larger Than K (need review)

* <a href="https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/" target="_blank">2차원 부분합이지만 진짜로 2차원 부분합으로 풀면 못풀음</a>
* <details>
   <summary>다시풀기</summary> 
   1차원 부분합 (row)들만 구하고, i - j 로 로우를 고정해놓고 컬럼은 k를 0부터 증가시켜가며, 정렬된 ary를 만들고 여기서 이분탐색으로 답도 찾고 인덱스도 찾음
   </details>
* 생각만 하자..
* 이게 이렇게 쉽게 풀린다고? bisect는 신인가...

#### Skyline Problems
* <a href="https://leetcode.com/problems/the-skyline-problem/description/" target="_blank">https://leetcode.com/problems/the-skyline-problem/description/</a>
* <details>
   <summary>풀긴 품</summary>이것도 어케 답 안보고 풀긴했는데 이전에도 풀어본거라...ㅎㅎ 생각 정리나 집중도 잘 안됐음..</details>

#### Min stack (reference problem))
<a href="https://leetcode.com/problems/min-stack/" target="_blank">https://leetcode.com/problems/min-stack/</a>
<details>
<summary>보기만</summary> 
    stack의 최소값 - pair를 저장하면 됨. 큐와는 달리 top 밑에 있는 애들이 안빠지므로..
   </details>

   
### amount-of-new-area-painted-each-day
https://leetcode.com/problems/amount-of-new-area-painted-each-day/
- 다시 풀어보자
- (22.06.01) 예외조건 하나를 못찾았음. 생각만 해 보자


### https://leetcode.com/problems/maximal-rectangle/submissions/
https://leetcode.com/problems/maximal-rectangle/submissions/
- 걍 다시 풇어보기
