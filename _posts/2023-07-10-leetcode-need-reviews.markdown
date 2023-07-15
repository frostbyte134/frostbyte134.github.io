---
layout: post
title:  "Leetcode problems - Need Reviews"
date:   2023-07-10 11:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review
---

잘 못풀었던지 해서 다시 풀어봐야 하는 문제들

리셋 ㄱㄱ
- 한번에 푸는 게 중요한듯 (실수 없이)
- 보자마자 opt sol이 걍 떠올라야 하는듯 ㅡ,.ㅡ
- 2022.11.25 하드100 돌파 ㅋㅋ

하...구글 떨어지고 나면 문제 다시 풀 줄 알았는데...일년동안 하나도 안풀었네 ㅋㅋ

## 쉬운데 구현상 다시 풀어야 하는 것들

### https://leetcode.com/problems/shortest-bridge/description/
- 그냥 평범한 미디엄인데..실력이 다 죽었음 ㅋㅋ

### https://leetcode.com/problems/longest-subsequence-with-limited-sum/description/
- 아니 뭐 당근 풀긴 했는데..이정도면 미디엄 아니냐? ㄷㄷ



--------------------------


## 잘 모르겠는 것들

### https://leetcode.com/problems/finding-the-number-of-visible-mountains/description/
- 아나 ㅋㅋ 답봄

### https://leetcode.com/problems/wildcard-matching/description/
- x같다 ㅋㅋㅋ 으...안보고 풀긴했는데 ㅜㅜ


### https://leetcode.com/problems/jump-game/
이걸 한번에 못푸네 ㅡㅡ https://leetcode.com/problems/jump-game/

### https://leetcode.com/problems/set-intersection-size-at-least-two/description/
- 한번에 풀진 못함

### https://leetcode.com/problems/sum-of-distances-in-tree/description/
- 와 풀었당 ㅎㅎㅎ 딕셔너리를 따로 두는게 깔끔해보이긴 하네

### https://leetcode.com/problems/max-stack/description/
https://leetcode.com/problems/max-stack/description/
- 음..풀긴 풀어서 상위 80펀데, 문제 요구조건 (read O(1))이 만족되나?ㅋㅋ

### Missing Element in Sorted Array
- O(N)으로 일단 품.
- nums[i]와 nums[i+1]간의 missing element가 누적된 값이 아닌데 어떻게 이진검색을 하나 고민했음 (부분합 배열을 만들면 이미 O(N))
<details>
   <summary>다시보기</summary> 
    nums[j] - nums[i] - 1 - (j - i) 가 i --- j 사이에 있는 missing elements. 결국 배열 전체를 고려해야 하므로, 0~mid 까지 테스트하고 이 결과로 st/ed를 갱신하는 게 직관적
   </details>
- 이것도 진심 레퍼런스 급

#### Meeting Rooms II (need review)
* <a href="https://leetcode.com/problems/meeting-rooms-ii/" target="_blank">그냥 풀기</a>
* <details>
   <summary>다시보가</summary> 
   겹치는 구간의 최대갯수 세기 = PQ. 범위 더하기 되는 구간트리 / 이분탐색으로도 풀어볼 만은 한 듯...?  
   l을 정렬해야 하고 r을 정렬하면 안되는 이유: l---r 로 되어 있으니까, l로 정렬해야 겹치는 것들을 확실하게 체크가능. r로 정렬하고 l보다 작은 것들을 필터링하면, l이 엄청 커졌다 작아지는 경우 못샘
   </details>
- 레퍼런스 각

#### Minimum Window Subsequence
* <a href="https://leetcode.com/problems/minimum-window-subsequence/" target="_blank">https://leetcode.com/problems/minimum-window-subsequence/</a>
* 몇시간 삽질해서 dp로 풀긴 함. dp 식이나 다시 세워보자
* 난 O(NM) dp로 풀었는데 투포인터가 더 효율적 (뒤에서 보면..!)
* edit distance랑 비슷하게 생각하면 되는 듯

### Minimum Cost to Make at Least One Valid Path in a Grid (보기만)
- <a href="https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/" target="_blank">https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/</a>
- 금방 생각난 것 - level (trial횟수) 별로 bfs하기. 여기서 특정 지역을 1번만 바꿀 수 있다는 제약조건이 걸리긴 했지만, 문제 특성상 최적의 답에 특정 지역을 두번 바꾼 게 들어갈 수 없기에 그냥 함 (한번만 바꾼 것 만 있는 답을 더 빨리 발견할 것이여서)
- 결국 level별로 할 필요도 없었음. 레벨별로 하면 O(보드크기 X 맥스 레벨 (200)) 이지만, bfs하고 - 경계 저장 - 경계에서 다시 BFS - ...로 하면 O(보드크기)로 끝낼 수 있음
- 디큐도 재밌었음. 디큐를 바로 생각할 수 있는 근거는 뭘까. 같은 레벨이면 앞에 더하고 (DFS?), 다음 레벨은 뒤에 더하는 식으로 함 (레벨 별). 결국 레벨은 현재에서 현재+1을 찾게 되므로, 항상 디큐에는 레벨이 증가하는 순서로 들어가게 됨

### minimum distance to type a word using two fingers (need review)
<a href="https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/" target="_blank">https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/</a>
* 일단 O(KN^2) dp로는 쉽게 풀음
* <details>
   <summary>O(N)</summary> iterative dp로 풀면 K를 없애도 됨. 왼/오를 구분하지 않아도 되고, 항상 한쪽 손가락만 움직이는 경우보다 얼만큼 절약할 수 있나를 a[26] 상태공간에 넣으면 O(N X 26)임. Lee꺼 참조
   </details>
* 대박이네..레퍼런스급

### https://leetcode.com/problems/number-of-ways-to-build-sturdy-brick-wall/description/
https://leetcode.com/problems/number-of-ways-to-build-sturdy-brick-wall/description/
- 이게..미디엄?


### https://leetcode.com/problems/count-binary-substrings/submissions/
https://leetcode.com/problems/count-binary-substrings/submissions/
- 이게 이지? ㄷㄷ 미듐인데..생각만 ㄱㄱ
- lee 답 보기. 좀 덜덜하네...


### https://leetcode.com/problems/minimize-deviation-in-array/
https://leetcode.com/problems/minimize-deviation-in-array/
- <details>
   <summary>흠</summary> 
    빠르게 눈치채야 할 것 - 홀수가 젤 큰 수면 더 뭐 어케 해볼수가 없음. 결국 밑에 수 중하나를 두배해야 뭘 하는데, 이럼 deviation은 더 늘어나기 떄문.
   </details>
   


### https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/
- https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/
   - 이건 쫌 걸리긴 했는데 풀긴함
   - 허허 (aka like dog)

### https://leetcode.com/problems/word-search-ii/
https://leetcode.com/problems/word-search-ii/
- 살짝 만족. 구현 다시 보기만 하자
- ㅁㅊ문제였네...

### maximum-profit-in-job-scheduling
- <a href="https://leetcode.com/problems/maximum-profit-in-job-scheduling" target="_blank">https://leetcode.com/problems/maximum-profit-in-job-scheduling</a> 
<details>
   <summary>뻘짓하다 힌트 한번 봄...</summary> 
    dp라는 힌트 보고 풀음. 내가 푼 것 보다 정렬 (정해진 순서로 상태공간 탐색) + 이진탐색 을 잘 하면 상태공간을 좀 더 좁힐 수 있음. 
   </details>
- 다시푸니까 대충 풀긴 함 ㅋㅋ 이진탐색보다는 dict쓸 수 있을 때 쓰면 더 빠름


### https://leetcode.com/problems/design-file-system/
https://leetcode.com/problems/design-file-system/
- EZ. 사알짝 고민함
- 한번에 풀기 (다시!)

### Insert Delete GetRandom O(1) (다시보기)
* <a href="https://leetcode.com/problems/insert-delete-getrandom-o1/" target="_blank">dict를 잘 쓰자.</a>
* <details>
   <summary>다시보기</summary> 
    dict/set으로 inclusion/exclusion검사, 배열로 random연산, 삭제시 마지막꺼랑 스왑 후 삭제
   </details>

-----------------------------------

### https://leetcode.com/problems/split-two-strings-to-make-palindrome/
- aa

### https://leetcode.com/problems/meeting-rooms-iii/description/
- https://leetcode.com/problems/meeting-rooms-iii/description/
- 풀긴 풀었는데 좀 더럽게 풀음...깔끔하게 푼거 참고하자. lee꺼가 좋은 듯
- 레퍼런스급


### https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/description/
https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/description/


#### Kadane
- Maximum subarray sum (이걸 까먹네 ㅋㅋ)
- Substring with Largest Variance - ㅅㅂ
   - 문자 2개씩 보는 것만 기억할 만 한듯

#### 
- https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/description/ 아직 
ㅁㅗㅅ봄

#### https://leetcode.com/problems/range-module/description/
- ㅁㅊ...C++이면 쉽게 풀었을 듯

### https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/description/
다시 ㄱ
- 꼬리문제 https://leetcode.com/problems/minimum-adjacent-swaps-to-make-a-valid-array/

### https://leetcode.com/problems/sum-of-total-strength-of-wizards/description/
아니...일단 다시 풀어 보자. 풀이 일부러 안적음. 왜 이런 걸 내는거야. 리트코드 함 보고 오라는 건가?


### https://leetcode.com/problems/median-of-two-sorted-arrays/
https://leetcode.com/problems/median-of-two-sorted-arrays/
- 이거 꼭 다시 (주말내에)
- <a href="https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2511/Intuitive-Python-O(log-(m%2Bn))-solution-by-kth-smallest-in-the-two-sorted-arrays-252ms" target="_blank">discussion</a>이 좋다고 생각해 본 게 오랜만이네..

### https://leetcode.com/problems/integer-to-english-words/description/
Integer to English Words
- 풀어볼 만 한듯 (한번에 제출, 설명, 깔끔)


### 보기만





### https://leetcode.com/problems/plates-between-candles/solutions/

* <a href="https://leetcode.com/problems/plates-between-candles/description/" target="_blank">https://leetcode.com/problems/plates-between-candles/description/</a>
* <details>
   <summary>개굿</summary>nlogn으로 풀었는데, 훨씬 더 깔끔한 방법이 있네. 어쨋든 지금 ps 근육이 없음. 많이 풀어야 할 듯</details>


- https://leetcode.com/discuss/general-discussion/462981/leetcode-questions-sorted-by-vote-count
- https://medium.com/hackernoon/google-interview-questions-deconstructed-the-knights-dialer-f780d516f029


solve the problem while explain it to yourself, and write examples (must!)

막히면?
- 뒤에서
- 가운데부터
- 조건을 확인하고, 약한 조건 이용하기
- 문제 재정의, 다시 읽기
- 웰노운들 적용시켜 보기
- 곱하기 있을 시 0 조심
- 글쓰면서 (예제 만들면서 주절주절)
- 비교할 때 항상 경계를 생각하자! 그럼 바로 풀림 ㅎㅎ
- 제출전 리뷰 필수
- 순차적으로
- __list test cases__
   - empty, simple, edges

### OrderedDict
ordereddict = linked list + dict (dict는 내부 링크드리스트에 대한 주소 저장)
- Big-O running times for all methods are the same as regular dictionaries.
- The internal self.__map dict maps keys to links in a doubly linked list.
- The circular doubly linked list starts and ends with a sentinel element.


### PQ
```
from queue import PriorityQueue
PQ = PriorityQueue()
PQ.put(sth1)
PQ.put(sth2)

while len(PQ) > 0:
   item = PQ.get()

from heapq import heappush, heappop
Q = []
heappush(Q, val)
heappop(Q)

```

### Iterator
```
iter_val = iter(iterable)
nxt = next(iter_val, None)
```


#### Shortest Subarray with Sum at Least K
- <a href="https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/" target="_blank">https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/</a>
<details>
   <summary>좋은 문제인 듯</summary> 
    문제를 잘 읽기 (좀 햇갈림. 면졉같은데 내긴 좋진 않은듯). N^2 -> NlogN은 직관적인데, NlogN -> N은 바로 생각하긴 쉽지 않을 수도?
   </details>

### Alien Dictionary  (보기만)
* <a href="https://leetcode.com/problems/alien-dictionary/" target="_blank">단어 사전이 valid한가?</a>
* <details>
   <summary>다시보가 (엣지케이스만)</summary> 
   dfs 로 사이클 찾기
   </details>

### https://leetcode.com/problems/distinct-subsequences/
https://leetcode.com/problems/distinct-subsequences/
- 아직 안품


### https://leetcode.com/problems/trapping-rain-water/
https://leetcode.com/problems/trapping-rain-water/
- 에반데. 3년전에 왜캐 잘했지. 지금하고 반대로 (가로 vs 세로) 풀었네 ㅋㅋ



### 복습 (need review)

### https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/
- https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description
- 썩 맘에들진 않는데..데이터에 따라 tle날수도 있으니까. union and find가 젤 좋은듯. 보기만 하자

### Reaching Points
- https://leetcode.com/problems/reaching-points/
- <details>
   <summary>하드 수월하게 풀었네 ㅋㅋ 생각정리가 중요함</summary> 
    tl < tr인 경우엔 둘 다 스왑하면 됨 ㅋㅋ. tl >>> tr인 경우엔 tl에서 tr만큼 계속 뺼 수 밖에 없다는 걸 알아채는게 포인트. 둘 다 비슷하면 금방 끝날꺼라는 것도.
   </details>



### https://leetcode.com/problems/count-of-smaller-numbers-after-self/
https://leetcode.com/problems/count-of-smaller-numbers-after-self/
- 오우 쉣. 보기만

### Longest Palindromic Substring
- asd

#### Longest Valid Parenthesis
<a href="https://leetcode.com/problems/longest-valid-parentheses/submissions/" target="_blank">https://leetcode.com/problems/longest-valid-parentheses/submissions/</a>

핵심: `이전` valid parenthesis의 시작으로 거리를 구하는 것. cur에 저장

cur = -1

1. (를 만났을 시
    1. `이전` 레벨의 시작(cur)을 스택에 저장 - 이어붙이기 기능
    2. 현재 레벨의 시작을 cur에 세팅
2. )를 만났을 시
    1. 이전에 쌓은 (가 없는 경우 - cur을 현재로 갱신해줌 (이제 valid한 것 못만드므로 reset)
    2. 있는 경우 - 이전 레벨의 시작 (st.top())과 현재의 거리를 답에 반영 후, pop. 

이렇게 하는 이유는, ()()나 (()()) 같은 경우를 해결하기 위해서.



#### Container With Most Water

<a href="https://leetcode.com/problems/container-with-most-water/" target="_blank">https://leetcode.com/problems/container-with-most-water/</a>

기본시도: 정렬가능시 정렬 (이문제 아님), 왼 안되면 왼+오, ...
- 스택으로 푸는 그 문제인 줄 알았다 ㅡㅡ 낙시쩔음
- 증명 영어로

#### Subarray Sum Equals K
<a href="https://leetcode.com/problems/subarray-sum-equals-k/" target="_blank">https://leetcode.com/problems/subarray-sum-equals-k/</a>

<details>
<summary>보기만</summary> 
    부분합문제인데 N^2로 풀면 TLE남.  
힌트는 값의 범위가 좁다는거였음. dic에 지금까지 나온 값들 저장해놓고 체크하면 됨.  
`collections.counter`를 쓰면 더 빨라지는듯?
   </details>


### https://leetcode.com/problems/3sum-with-multiplicity/
https://leetcode.com/problems/3sum-with-multiplicity/
- ncr recurrence rel
- ncr = n-1cr-1 + n-1Cr


### number-of-matching-subsequences (복습필수)
- <a href="https://leetcode.com/problems/number-of-matching-subsequences/" target="_blank">https://leetcode.com/problems/number-of-matching-subsequences/</a>
- 어떤 식으로 순회할 것인가
<details>
   <summary>다시보기</summary> 
    M * N * len(word[N]) 을 잘 해서 M * N * 26 으로 줄여야 함. 포인터 / iterator
   </details>
- https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/ 동일문제
- 아니 근데 C++로 걍 풀면 되지 않나? 안되네. 다 끝난 걸 제외할 수 있는 게 핵심인 듯 


### https://leetcode.com/problems/lfu-cache/
https://leetcode.com/problems/lfu-cache/
- 풀긴 풀음. 다시
- 또 풀긴 풀음 ㅡㅡ 
* <details>
   <summary>아나</summary> 
   방금 삽입된 아이템이 캐시에 없던 거면, 이게 유력한 least frequently used임 (use_counter=1). 난 캐시 값 갱신 (1) ->  PQ에 삽입 (2) -> 꽊찼으면 하나 제거 (3) 순으로 하면 안되고 (넣자마자 없어질 수 있음), 132로 해야 하고, 1/2에서 큐사이즈가 첨부터 0일 때 고려해야 함. 아님 뭐 다른 방법으로 사이즈 꽉 찬거 체크하던지
   </details>

### Find original array from doubled array
<a href="https://leetcode.com/problems/find-original-array-from-doubled-array/" target="_blank">https://leetcode.com/problems/find-original-array-from-doubled-array/</a>
- <details>
   <summary>ㅡㅡ</summary> 
    ㅡㅡ 곱하기가 있다? 항상 그 값 조심
   </details>

### find and replace in string
<a href="https://leetcode.com/problems/find-original-array-from-doubled-array/" target="_blank">https://leetcode.com/problems/find-original-array-from-doubled-array/</a>
- <details>
   <summary>생각정도만</summary> 
    뒤에서 풀면 왜 좋을까? 파이썬 문자열은 const임. 새로 만들어야 함
   </details>

#### Remove All Ones With Row and Column Flips
<a href="https://leetcode.com/problems/remove-all-ones-with-row-and-column-flips/" target="_blank">https://leetcode.com/problems/remove-all-ones-with-row-and-column-flips/</a>
- <details>
   <summary>WTF</summary> 
    같은 row를 두번 Flip해야만 새로 나오는 답이 있을까? - 0번은 2번과 같고, 1번은 3번과 같음. 
    답 찾기 = 1번쨰 row와 다른 row를 뒤집으면, 결국 row끼리도 다 같아야 함
   </details>

#### detect-squares
<a href="https://leetcode.com/problems/detect-squares/" target="_blank">https://leetcode.com/problems/detect-squares/</a>
- <details>
   <summary>어...음...좌표문제는 항상 노트가 있음 좋겠다는 생각이 듬</summary> 
    두번쨰로 천천히 푸니까 금방 품. 천천히!
   </details>

### swap adjacent in lr string
https://leetcode.com/problems/swap-adjacent-in-lr-string/
- <details>
   <summary>보기만</summary> 
    이름에 힌트가 있었네. 문제 잘 살펴보기 
   </details>

### https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/
https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/
- 바이너리 서치 정리하기 (생각만)


### https://leetcode.com/problems/sentence-screen-fitting/
- 해깔림. 다시 풀어 보자
- 인덱스 의미 조심-


### 눈팅선
- 이 위로 눈팅만 필요 (위쪽이 중요)


### https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/
- 뭐 맞추긴 했는데 한번엔 안됨. 다시 풀어 보자
- 한번에 좀 ㅡㅡ


-------------------------------------------

### single-threaded-cpu
https://leetcode.com/problems/single-threaded-cpu/
- 이것도 깔끔하게 안풀림...
- 다시 풀었는데도 깔끔하게 안풀림 ㅡ,.ㅡ
- 비교할 때 항상 경계를 생각하자! 그럼 바로 풀림 ㅎㅎ



#### Partition Equal subset sum
* <a href="https://leetcode.com/problems/partition-equal-subset-sum/submissions/" target="_blank">https://leetcode.com/problems/partition-equal-subset-sum/submissions/</a>
* <details>
   <summary>실력이 퇴화하나....?</summary>제약조건을 잘 활용해 보자. DICT쓰면 특이케이스에 걸리는 게 별로 없는데 배열 써서...아니 그리고 제출하기 전 까지 생각이 안 나서 계속 틀림 ;_;....</details>

#### Partition Equal Subset Sum
* <a href="https://leetcode.com/problems/partition-equal-subset-sum/" target="_blank">https://leetcode.com/problems/partition-equal-subset-sum/</a>
* <details>
   <summary>다시보가</summary> 
   집합에서 합이 되는 부분집합의 개수. 직접 더해서 모든 경우의 수를 만들어볼 때 큰 값부터 고려해야 함 (현재 아이템을 여러번 쓸 수 있음)
   </details>

#### Partition Array into Two arrays to minimize sum diff
* <a href="https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/" target="_blank">중간에서 만나요</a>
* <details>
   <summary>다시보가</summary> 
   풀이가 합리적이네...글고 문제를 또 안읽음
   </details>


#### remove-duplicates-from-sorted-list-ii

* <a href="https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/submissions/" target="_blank">그냥</a>
* 쉬운 미디엄인데..실수하기 좋은 (한번에 풀기 어려운) 링크드리스트 문제여서...


--------------------------------

### https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
- nlong말고 n으로 (생각정리만, 글로)
- 레벨벨로 풀면 걍 ez


### minimum-number-of-increments-on-subarrays-to-form-a-target-array/
- <a href="https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/" target="_blank">https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array</a> 
<details>
   <summary>그냥 쉬운 하드인가 했는데</summary> 
    스택으로 풀었는데 생각해보니 더 쉽게 풀 수 있음. 아 글고 스택인데 자꾸 [0] 체크하네. 넘올만이여서 그런듯
   </details>

### https://leetcode.com/problems/asteroid-collision/
- <a href="https://leetcode.com/problems/asteroid-collision/" target="_blank">https://leetcode.com/problems/asteroid-collision/</a> 이정돈 이제 뭐...(2)
<details>
   <summary>심심하면 다시보기. 걍 풀긴 함</summary> 
    경우를 잘 따져봅시다 (2). 충돌의 성질 상 스택처럼 풀 수 있음. 
   </details>

### Minimum Difference Between Largest and Smallest Value in Three Moves
- <a href="https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/" target="_blank">https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/</a> 이정돈 이제 뭐...
<details>
   <summary>심심하면 다시보기. 걍 풀긴 함</summary> 
    경우를 잘 따져봅시다. 상태공간이 넓은 듯 안넓은듯
   </details>


### 4sums
- 기존 확장밖에 없네
<details>
   <summary>다시보기</summary> 
    2sum확장. 중복처리로 1/10 깎고, 가지치기로 1/5도 깎음
   </details>



### Maximum product subarray
- <a href="https://leetcode.com/problems/maximum-product-subarray/" target="_blank">https://leetcode.com/problems/maximum-product-subarray/</a>
- 원칙 적용시켜 보기. 내가 이런 생각을 했었다고? ㄷㄷ
- <details>
   <summary>생각만</summary> 
    0이 있으면 쪼개기. -x ... -y 인 경우는 고려안해도 되니까, 답은 항상 한쪽에만 -1이 있는 경우 (또는 -가 아예 없거나 안쪽에 -가 짝수로 있는 경우). 반대부터 보기도 굳
   </details>
### Bricks Falling When Hit
<a href="https://leetcode.com/problems/bricks-falling-when-hit/" target="_blank">https://leetcode.com/problems/bricks-falling-when-hit/</a>

<details>
   <summary>다시 풀면 좋을텐데 코드가 넘 김</summary> 
    뒤로부터 풀기 + 마킹 + djset. 천장에 붙으면 vis인거고. 아니근데 djset 필요없지 않나? 없이 한번 풀어보자
   </details>


### consecutive Numbers Sum
<a href="https://leetcode.com/problems/consecutive-numbers-sum/" target="_blank">https://leetcode.com/problems/consecutive-numbers-sum/</a>
<details>
   <summary>다시보기</summary> 
    구간합 공식을 이용한 투포인터
   </details>


### https://leetcode.com/problems/peeking-iterator/
https://leetcode.com/problems/peeking-iterator/
- 씽크빅 ㅋㅋ

### 윈도우 문제
- monotonic하게 움직이는 윈도우에서, __최대__ (=최소) 빠르게 찾기
  - 윈도우가 움직이므로 가장 옛날 값을 제거해야 하고 새 값도 넣어야 하는 와중에, 최대 최소도 빨리 (logN / 1) 만에 찾아야 함
  - 직관적으로는 AVL tree (map)임 (logN)
  - 최대값을 구해야 하므로
    - 현재보다 이전 인덱스인데 현 값보다 작으면 필요없음. 윈도우는 점점 ->로 가므로 현재 값에 가려저서 답에 contribution할 일은 없을 것임. 
    - 따라서 decreasing dequeue를 유지하면서 맨 앞의 값을 가져오면 됨
- 투포인터와 겹치는 부분이 있는 듯. increasing 이든 decreasing 이든 배열을 유지하는건, 앞+뒤 정보를 가지고 있는 것이니까.



TODO: make a post on
* https://www.educative.io/courses/grokking-the-system-design-interview

### Cherry pickup (need review)
* <a href="https://leetcode.com/problems/cherry-pickup/" target="_blank">https://leetcode.com/problems/cherry-pickup/</a>
* 워매...
* <details>
   <summary>다시풀기</summary> 
    왔다-갔다 X. 2개를 동시에 앞으로. 매턴마다 아래/오른은 가야 하므로, 둘이 겹치는 경우도 쉽게 처리가능. 덤으로 x+y=p+q이므로 x, y, p만 상태공간이 됨. 마지막에 계속 틀린건, -1때문에 아래/오른을 못가는 경우에도 (막다른 골목!) 적당한 답을 반환해서 그랬음. 엄청 큰 -로 페널티를 줘야 함.
   </details>


### Range Sum Query 2D - Mutable
- 2차원 구간합인데 mutable함. 이거 맨날 생각하는데 해싱같은거로 대충 풀지 않았나? 백준에서..
- 2차원 세그트리같은건 아니었고...1차원 구간합을 효율적으로 갱신하면 상위권 됨

### Sliding Puzzle
* <a href="https://leetcode.com/problems/sliding-puzzle/" target="_blank"> 보드가 작아 bijection 가능. DFS하니까 메모리 리밋 뜸 ㅡㅡ</a>

### String Transforms Into Another String (보기만)
* <a href="https://leetcode.com/problems/string-transforms-into-another-string/" target="_blank">예외케이스를 찾아보자</a>
* <details>
   <summary>다시보가</summary> 
   둘 다 26개씩 쓰였으면, 완전히 같지 않은 이상 못바꿈
   </details>


### basic calculator 2
* https://leetcode.com/problems/basic-calculator-ii/
* 외우는게 좋은듯



### Next Closest Time
- <a href="https://leetcode.com/problems/next-closest-time/" target="_blank">https://leetcode.com/problems/next-closest-time/</a>
- 구현이 거지같았던 문제. 근데 시간이 넘어가면 다음 날 시간을 계산안해도 되서 풀만했던듯?

### divide array in sets of k consecutive numbers (need review)
<a href="https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers" target="_blank">https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers</a>
* 일단 하위30퍼로 풀긴 풀음
* consequtive란 단서 때문에 더 빠르게 풀 수 있음. 그림을 잘 그려 보자


### Robot Room Cleaner
- 재밌는 하드 문제였음
- __범위가 주어지지 않은 보드판__을, 로봇이 front / left, right만 갈 수 있을 때 완전탐색하는 법
- 상대좌표로 vis를 찍는 dfs. dfs이기 때문에, 돌아오는 연산도 구현해 줘야 함 (왼2, 전진, 다시 왼2). 안그럼 vis가 정확하지 않기 때문에 무한루프 돔. 


#### Minimum Swaps to make subsequences increasing
* <a href="https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/" target="_blank">https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/</a>
* 일단 O(N * range(val))dp로 풀음
* <details>
   <summary>다시 풀어 보기</summary> O(N) dp로 가능. swap[i] = i번째 스왑이 일어났다는 가정 하에, 필요한 최소의 스왑 / notswap[i] = i번째 스왑이 일어나지 않았다는 가정 하에, 필요한 최소의 스왑. 밑에번부터 어떻게 채울지 생각하면 풀린다. 
   </details>

#### Split Array into Consecutive Subsequences
* <a href="https://leetcode.com/problems/split-array-into-consecutive-subsequences/" target="_blank">https://leetcode.com/problems/split-array-into-consecutive-subsequences/</a>
* 무식하게 풀었던 거 같음. 구현연습에 좋은듯.
* 아니면 각 숫자별로 count 샌 다음에 없애면서 나가도 되지 않나?
* <details>
   <summary>다시 풀어 보기</summary> 그리디하게 가능. 작은 숫자부터, 1. 이 숫자가 기존 list의 맨 뒤에 붙거나, 2. 그 숫자로부터 이어지는 숫자 2개가 더 있어야 함. 그리디네...
   </details>


#### Copy list with Random Pointer
* 다시 풀 필요는 없고, 생각정도는 해볼 만 함
* linked list를 deep copy할 시, random pointer도 갖고 있으면 이건 어떻게 deep copy에 반영하나?
* 일단 풀기는 python으로, `dic[node]=len(lis)` 를 통해 주소를 넣으면 index를 주는 dic만들어 풀음
* 이게 결국, 주소를 받았을 때 이 주소가 몇 번째 아이템인지 (내지는 deep copy된 배열의 corresponding item의 주소를) 받을 수 있어야 함.
* C++이면 어캐해야 하나. 지금 생각나는 건, 결국 포인터도 정수이므로 pair{pointer, index}를 만들고 정렬시킨 후 pointer를 받으면 binary search 로 찾으면 될듯.
* Damn! give this guy a Novel prize! https://raw.githubusercontent.com/hot13399/leetcode-graphic-answer/master/138.%20Copy%20List%20with%20Random%20Pointer.jpg
* 에전에 K사 면접문제. 끝을 모르는 링크드 리스트에서 뒤에서 K번째를 찾을 때 그 느낌하고 비슷한가 했는데 비슷하진 않네


#### Split Array Largest Sum
<a href="https://leetcode.com/problems/split-array-largest-sum/" target="_blank">https://leetcode.com/problems/split-array-largest-sum/</a>

* 배열을 m개의 non-empty subarray로 나눔.
* 각 subary의 합의 최대를 x라 하면, 최소의 x는?
* x를 픽스했을 시 각 trial을 만들기 쉽고, 범위가 정해져 있음 (0~원래 array의 합)
  * 이분탐색

#### https://leetcode.com/problems/shortest-way-to-form-string/ (review)
<a href="https://leetcode.com/problems/path-with-maximum-gold/" target="_blank">https://leetcode.com/problems/path-with-maximum-gold/</a>

1. 그리디함 증명
2. next table - 뒤부터 iter돌면서 만듬

#### Design Hit Counter
<a href="https://leetcode.com/problems/design-hit-counter/" target="_blank">https://leetcode.com/problems/design-hit-counter/</a>
increasing하게 들어오는 timestamp. 특정 시점의 300초전까지의 hit수를 구해야 함. 제약조건을 이용해 이진탐색으로 풀음

#### Text justification
- <a href="https://leetcode.com/problems/text-justification/submissions/" target="_blank">https://leetcode.com/problems/text-justification/submissions/</a>, hard
- 큰 루프 두고, 예외케이스 3개 두고 풀음
  - 단어가 N개 (마지막에 whitespace 두지 않음)
  - 단어가 N개이나 마지막 (1번씩 띄고 left정렬)
  - 단어가 1개 (마지막 whitesapce 둠)
- 각 case에 규칙을 consistent하게 적용해야 하는데 이게 아직 잘 안되네. 이건 머리로 체크하는 수 밖에 없는 듯.
- round-robin

#### Minimum Domino Rotations For Equal Row
문제자체는 엄청 쉬웠다. 첫 submission은 맞았는데 실행시간이 바닥을 달림. 숫자가 consequtive하게 나와야 한다는 것 (강한 조건)을 이용해 필터링 함.

#### Guess the Word (hard)
- <a href="https://leetcode.com/problems/guess-the-word/" target="_blank">https://leetcode.com/problems/guess-the-word/</a>
- SWE B번예시같았다. 현재까지 던진 query와, 대상이 될 문자열들 candidate가 있다고 할 시, query와 최대한 겹치지 않는 걸 candidate에서 찾아서 query넣어봄 (최대한 많은 정보 획득).

### reference problems

#### 2-sum problems
1. 2-sum - lr (O(N))
2. 3-sum - 2sum * N
3. 4-sum - 3sum * N



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

### Need review



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
