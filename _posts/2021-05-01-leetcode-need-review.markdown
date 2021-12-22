---
layout: post
title:  "Leetcode problems"
date:   2021-05-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review
---

solve the problem while explain it to yourself, and write examples (must!)

막히면?
- 뒤에서
- 가운데부터
- 문제 재정의, 다시 읽기
- 웰노운들 적용시켜 보기

### Missing Element in Sorted Array
- O(N)으로 일단 품.
- nums[i]와 nums[i+1]간의 missing element가 누적된 값이 아닌데 어떻게 이진검색을 하나 고민했음 (부분합 배열을 만들면 이미 O(N))
<details>
   <summary>다시보기</summary> 
    nums[j] - nums[i] - 1 - (j - i) 가 i --- j 사이에 있는 missing elements. 결국 배열 전체를 고려해야 하므로, 0~mid 까지 테스트하고 이 결과로 st/ed를 갱신하는 게 직관적
   </details>


#### Shortest Subarray with Sum at Least K
- <a href="https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/" target="_blank">https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/</a>
<details>
   <summary>좋은 문제인 듯</summary> 
    문제를 잘 읽기 (좀 햇갈림. 면졉같은데 내긴 좋진 않은듯). N^2 -> NlogN은 직관적인데, NlogN -> N은 바로 생각하긴 쉽지 않을 수도?
   </details>

#### Optimal Account Balancing
* <a href="https://leetcode.com/problems/optimal-account-balancing/" target="_blank">https://leetcode.com/problems/optimal-account-balancing/</a>
* <details>
   <summary>잘 생각해 보면</summary>우선 transaction의 역순으로 하면 되니까 이거보다 큰 답은 없고, transaction을 압축하는 형태로 최적의 답이 나올 테니 각 노드의 값을 이상하게 쪼개는 경우는 없을 듯. 있는 거 다 쓰면서 완탐하면 될 듯
   . 어째 갈수록 느려지네...;_;</details>

#### Partition Equal subset sum
* <a href="https://leetcode.com/problems/partition-equal-subset-sum/submissions/" target="_blank">https://leetcode.com/problems/partition-equal-subset-sum/submissions/</a>
* <details>
   <summary>실력이 퇴화하나....?</summary>제약조건을 잘 활용해 보자. DICT쓰면 특이케이스에 걸리는 게 별로 없는데 배열 써서...아니 그리고 제출하기 전 까지 생각이 안 나서 계속 틀림 ;_;....</details>


#### Meeting Rooms II (need review)
* <a href="https://leetcode.com/problems/meeting-rooms-ii/" target="_blank">그냥 풀기</a>
* <details>
   <summary>다시보가</summary> 
   겹치는 구간의 최대갯수 세기 = PQ. 범위 더하기 되는 구간트리 / 이분탐색으로도 풀어볼 만은 한 듯...?  
   l을 정렬해야 하고 r을 정렬하면 안되는 이유: l---r 로 되어 있으니까, l로 정렬해야 겹치는 것들을 확실하게 체크가능. r로 정렬하고 l보다 작은 것들을 필터링하면, l이 엄청 커졌다 작아지는 경우 못샘
   </details>

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


#### Partition Array into Two Arrays to Minimize Sum Difference

* <a href="https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/submissions/" target="_blank">그냥</a>
* 쉬운 미디엄인데..실수하기 좋은 (한번에 풀기 어려운) 링크드리스트 문제여서...


--------------------------------

### https://leetcode.com/problems/search-a-2d-matrix/
쉬운데 추가풀이가 재밌네

### maximum-profit-in-job-scheduling
- <a href="https://leetcode.com/problems/maximum-profit-in-job-scheduling" target="_blank">https://leetcode.com/problems/maximum-profit-in-job-scheduling</a> 
<details>
   <summary>뻘짓하다 힌트 한번 봄...</summary> 
    dp라는 힌트 보고 풀음. 내가 푼 것 보다 정렬 (정해진 순서로 상태공간 탐색) + 이진탐색 을 잘 하면 상태공간을 좀 더 좁힐 수 있음. 
   </details>


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

### find peak element
- <a href="https://leetcode.com/problems/find-peak-element/" target="_blank">https://leetcode.com/problems/find-peak-element/</a> 눈으로 보기만
<details>
   <summary>다시보기</summary> 
    재귀식 잘짜보기 (조건 따지기). 올만이네..
   </details>

### number-of-matching-subsequences (복습필수)
- <a href="https://leetcode.com/problems/number-of-matching-subsequences/" target="_blank">https://leetcode.com/problems/number-of-matching-subsequences/</a>
- 어떤 식으로 순회할 것인가
<details>
   <summary>다시보기</summary> 
    M * N * len(word[N]) 을 잘 해서 M * N * 26 으로 줄여야 함. 포인터 / iterator
   </details>
- https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/ 동일문제

### max-area-of-island
- <a href="https://leetcode.com/problems/max-area-of-island/submissions/" target="_blank">https://leetcode.com/problems/max-area-of-island/submissions/</a>
- 많이 풀어 본 보드문제
<details>
   <summary>다시보기</summary> 
    예전에는 bfs + set으로 풀었던 거 같은데 그럴필요 없음.
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




### 윈도우 문제
- monotonic하게 움직이는 윈도우에서, __최대__ (=최소) 빠르게 찾기
  - 윈도우가 움직이므로 가장 옛날 값을 제거해야 하고 새 값도 넣어야 하는 와중에, 최대 최소도 빨리 (logN / 1) 만에 찾아야 함
  - 직관적으로는 AVL tree (map)임 (logN)
  - 최대값을 구해야 하므로
    - 현재보다 이전 인덱스인데 현 값보다 작으면 필요없음. 윈도우는 점점 ->로 가므로 현재 값에 가려저서 답에 contribution할 일은 없을 것임. 
    - 따라서 decreasing dequeue를 유지하면서 맨 앞의 값을 가져오면 됨
- 투포인터와 겹치는 부분이 있는 듯. increasing 이든 decreasing 이든 배열을 유지하는건, 앞+뒤 정보를 가지고 있는 것이니까.

### Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit (window problem, need review)
- <a href="https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/" target="_blank">https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/</a>
- 윈도우 안의 최대/최소의 차이. map으로 풀어서 하위 20퍼로 풀긴 함
- 디큐 - increasing_deque는 맨 앞이 구간의 최소값, decreasing_deque는 맨 앞이 구간의 최대값임 (맨 뒤는 항상 새로 추가된 원소).
  - 이 때 조심해야 할 게, 현재 구간 (디큐들에 들어있는 아이템들의 min, max정보가 유효한 구간)은 max(inc디큐에서 제일 최근에 빠진 인덱스+1, dec디큐에서 제일 최근에 빠진 인덱스+1)이라는 것


### Minimum Cost to Make at Least One Valid Path in a Grid (보기만)
- <a href="https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/" target="_blank">https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/</a>
- 금방 생각난 것 - level (trial횟수) 별로 bfs하기. 여기서 특정 지역을 1번만 바꿀 수 있다는 제약조건이 걸리긴 했지만, 문제 특성상 최적의 답에 특정 지역을 두번 바꾼 게 들어갈 수 없기에 그냥 함 (한번만 바꾼 것 만 있는 답을 더 빨리 발견할 것이여서)
- 결국 level별로 할 필요도 없었음. 레벨별로 하면 O(보드크기 X 맥스 레벨 (200)) 이지만, bfs하고 - 경계 저장 - 경계에서 다시 BFS - ...로 하면 O(보드크기)로 끝낼 수 있음
- 디큐도 재밌었음. 디큐를 바로 생각할 수 있는 근거는 뭘까. 같은 레벨이면 앞에 더하고 (DFS?), 다음 레벨은 뒤에 더하는 식으로 함 (레벨 별). 결국 레벨은 현재에서 현재+1을 찾게 되므로, 항상 디큐에는 레벨이 증가하는 순서로 들어가게 됨

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


### Alien Dictionary  (보기만)
* <a href="https://leetcode.com/problems/alien-dictionary/" target="_blank">단어 사전이 valid한가?</a>
* <details>
   <summary>다시보가</summary> 
   dfs 로 사이클 찾기 
   </details>

### String Transforms Into Another String (보기만)
* <a href="https://leetcode.com/problems/string-transforms-into-another-string/" target="_blank">예외케이스를 찾아보자</a>
* <details>
   <summary>다시보가</summary> 
   둘 다 26개씩 쓰였으면, 완전히 같지 않은 이상 못바꿈
   </details>

### Max Sum of Rectangle No Larger Than K (need review)

* <a href="https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/" target="_blank">2차원 부분합이지만 진짜로 2차원 부분합으로 풀면 못풀음</a>
* <details>
   <summary>다시풀기</summary> 
   1차원 부분합 (row)들만 구하고, i - j 로 로우를 고정해놓고 컬럼은 k를 0부터 증가시켜가며, 정렬된 ary를 만들고 여기서 이분탐색으로 답도 찾고 인덱스도 찾음
   </details>


### Insert Delete GetRandom O(1) (다시보기)
* <a href="https://leetcode.com/problems/insert-delete-getrandom-o1/" target="_blank">dict를 잘 쓰자.</a>
* <details>
   <summary>다시보기</summary> 
    dict/set으로 inclusion/exclusion검사, 배열로 random연산, 삭제시 마지막꺼랑 스왑 후 삭제
   </details>

### Validate Stack Sequences
* <a href="https://leetcode.com/problems/validate-stack-sequences/" target="_blank">꼭 다시 보자 (보기만)</a>
* <details>
   <summary>다시보기</summary> 
   we can try man (indeed)
   </details>

### basic calculator 2
* https://leetcode.com/problems/basic-calculator-ii/
* 외우는게 좋은듯



### Flip Equivalent Binary Trees
- https://leetcode.com/problems/flip-equivalent-binary-trees/
- 그냥 생각만...일부 노드면 flip된 경우를 flip equivalent라고 할 경우, 두 트리가 서로 flip equivalent일 조건은?

### Minimum Remove to Make Valid Parentheses
- https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
- 이것도 생각만. 2-pass로 품.

### Next Closest Time
- <a href="https://leetcode.com/problems/next-closest-time/" target="_blank">https://leetcode.com/problems/next-closest-time/</a>
- 구현이 거지같았던 문제. 근데 시간이 넘어가면 다음 날 시간을 계산안해도 되서 풀만했던듯?

### First Missing Positive (need review)
<a href="https://leetcode.com/problems/first-missing-positive/" target="_blank">https://leetcode.com/problems/first-missing-positive/</a>
* smallest nonnegative
* <details>
   <summary>다시풀기</summary> 
   smallest nonnegative = 배열에 저장 가능
   </details>

### divide array in sets of k consecutive numbers (need review)
<a href="https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers" target="_blank">https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers</a>
* 일단 하위30퍼로 풀긴 풀음
* consequtive란 단서 때문에 더 빠르게 풀 수 있음. 그림을 잘 그려 보자

### minimum distance to type a word using two fingers (need review)
<a href="https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/" target="_blank">https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/</a>
* 일단 O(KN^2) dp로는 쉽게 풀음
* <details>
   <summary>O(N)</summary> iterative dp로 풀면 K를 없애도 됨. 왼/오를 구분하지 않아도 되고, 항상 한쪽 손가락만 움직이는 경우보다 얼만큼 절약할 수 있나를 a[26] 상태공간에 넣으면 O(N X 26)임 
   </details>


### Robot Room Cleaner
- 재밌는 하드 문제였음
- __범위가 주어지지 않은 보드판__을, 로봇이 front / left, right만 갈 수 있을 때 완전탐색하는 법
- 상대좌표로 vis를 찍는 dfs. dfs이기 때문에, 돌아오는 연산도 구현해 줘야 함 (왼2, 전진, 다시 왼2). 안그럼 vis가 정확하지 않기 때문에 무한루프 돔. 


### delete nodes and return forest
- <a href="https://leetcode.com/problems/delete-nodes-and-return-forest/" target="_blank">https://leetcode.com/problems/delete-nodes-and-return-forest</a>
- 복습까진 필요없는 듯. 중복정보를 본인도 처리하고 자손도 중복으로 처리해서 느렸다. 자손에서 return으로 보내 줬으면 됐을 껄...이거 면접에서 이래 죽쓰면 풀긴 풀었는데 감점 엄청 당할듯.

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

#### Minimum Window Subsequence
* <a href="https://leetcode.com/problems/minimum-window-subsequence/" target="_blank">https://leetcode.com/problems/minimum-window-subsequence/</a>
* 몇시간 삽질해서 dp로 풀긴 함. dp 식이나 다시 세워보자
* 난 O(NM) dp로 풀었는데 더 효율적으로 푸는 dp가 있다네. 그럴 꺼 같긴 했는데...


#### Copy list with Random Pointer
* 다시 풀 필요는 없고, 생각정도는 해볼 만 함
* linked list를 deep copy할 시, random pointer도 갖고 있으면 이건 어떻게 deep copy에 반영하나?
* 일단 풀기는 python으로, `dic[node]=len(lis)` 를 통해 주소를 넣으면 index를 주는 dic만들어 풀음
* 이게 결국, 주소를 받았을 때 이 주소가 몇 번째 아이템인지 (내지는 deep copy된 배열의 corresponding item의 주소를) 받을 수 있어야 함.
* C++이면 어캐해야 하나. 지금 생각나는 건, 결국 포인터도 정수이므로 pair{pointer, index}를 만들고 정렬시킨 후 pointer를 받으면 binary search 로 찾으면 될듯.
* Damn! give this guy a Novel prize! https://raw.githubusercontent.com/hot13399/leetcode-graphic-answer/master/138.%20Copy%20List%20with%20Random%20Pointer.jpg
* 에전에 K사 면접문제. 끝을 모르는 링크드 리스트에서 뒤에서 K번째를 찾을 때 그 느낌하고 비슷한가 했는데 비슷하진 않네

#### Minimum Swaps To Make Sequences Increasing
- <a href="https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/" target="_blank">https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/</a>
- 미디엄이라 쉽게 보고 O(N*2) dp로 풀음
- O(N) 풀이가 존재하네....? 다시 풀어봅시다

#### Longest Increasing Path in a Matrix
- <a href="https://leetcode.com/problems/longest-increasing-path-in-a-matrix/" target="_blank">https://leetcode.com/problems/longest-increasing-path-in-a-matrix/</a>
- 하드인데 쉬웠음. 보드에서의 increasing path이므로, 왔던 곳으로 다시 못 감 - cache 이용가능 

#### Minimum Area Rectangle
- <a href="https://leetcode.com/problems/minimum-area-rectangle/" target="_blank">Minimum Area Rectangle</a>
- 쉬운 문제고 어렵지 않게 풀긴 했는데, 검사조건을 명확하게 도출하지 못함. 다시 해보자. 다시 했음. 이전문제는 좀 naive하게 풀었던거 같음.


#### Search Autocomplete system (need review)
<a href="https://leetcode.com/problems/design-search-autocomplete-system/" target="_blank">https://leetcode.com/problems/design-search-autocomplete-system/</a>
- B형이랑 쪼까 비슷한듯
- 연관문제도 풀어볼까
- 제약조건이 좀 약하긴 함. 그래서 매 query마다 소팅을 하는데, 효율적으로 풀 수 없을까

#### Valid square
<a href="https://leetcode.com/problems/valid-square/" target="_blank">https://leetcode.com/problems/valid-square/</a>

4개의 점이 주어졌을 시, 정사각형인가?
* 첨에 회전을 생각안해서 함 틀림
* 좌표가 같은지아닌지로 하려다 계속 틀려서, 벡터 + 내적 (90도 판별)로 풀음.
* 말하면서 풀어야 하는데..넘모 귀찮은 것임

#### Path with Maximum Gold
<a href="https://leetcode.com/problems/valid-square/" target="_blank">https://leetcode.com/problems/valid-square/</a>


2차원 grid에서, 재방문이 불가 & 0을 방문하지 못할 시, 모을 수 있는 가장 많은 값은? (방문시 값 get)
* n, m이 해봐야 15, 논제로 아이템이 25개가 맥시멈 -> 완탐
* dp도 되지 않을까? 논제로 아이템 25개에 대한 상태공간 (25bit)만...안되겠네

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

#### Minimum Knight Moves (복습요망)
<a href="https://leetcode.com/problems/minimum-knight-moves/" target="_blank">https://leetcode.com/problems/minimum-knight-moves/</a>

#### Time Based Key-Value Store (medium)
- <a href="https://leetcode.com/problems/time-based-key-value-store/" target="_blank">https://leetcode.com/problems/time-based-key-value-store/</a>
- 문제를 잘 읽읍시다..
- 그나저나, 새 item이 계속 추가되는 상태에서 정렬된 배열을 유지하는 건 계속 나오네. 이 문제의 경우는 increasing하는 순서로 주어져서 별 상관 없었지만. 문제를 잘 읽지 않은 덕분에 파이썬으로 어떻게 구현해야 하는지 계속 생각함.
  1. map (splay tree) - lower_bnd연산을 구현하면 쉬울듯.
  2. key가 정해져있고 좌표압축이 가능하며 범위가 작은 경우 - random access linked list로 짜면 될 듯. 근데 이거 만들어 본 적이 없어서..연습요망

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

#### LRU Cache
<a href="https://leetcode.com/problems/lru-cache/" target="_blank">https://leetcode.com/problems/lru-cache/</a>
linked list + hash = O(1) LRU Cache!

#### 2-sum problems
1. 2-sum - lr (O(N))
2. 3-sum - 2sum * N
3. 4-sum - 3sum * N




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



#### Best time to buy and sell stock
<a href="https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/submissions/" target="_blank">https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/</a>

1. DP
\\[\text\{maxx\}[i] = \max(\text\{maxx\}[i], \text\{maxx\}[i-1], ary[i] - ary[j] + \text\{maxx\}[j-2]),\\ j=1,...,i-1\\]
when j<2, maxx[j-2] = 0 (there is no profit we can obtain in day=i=0, 1)
2. __Notice__ that, the term \\(- ary[j] + \text\{maxx\}[j-2])\\) is calculated over and over

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

#### Find All Numbers Disappeared in an Array
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

Cycle 찾기 문제. 이게 이지라고?

#### search a 2d matrix

<a href="https://leetcode.com/problems/search-a-2d-matrix-ii" target="_blank">https://leetcode.com/problems/search-a-2d-matrix-ii</a>


\\(m\times n\\) 행렬이, 행 / 열 별로 독립적으로 정렬되어 있을 시,

1. 난 그냥 m*logn으로 풀음
2. 행렬은 각 element 별로 4개로 쪼갤 수 있다. 왼위가 자기보다 무조건 작은 곳, 오른아래가 무조건 자기보다 큰 곳.  
   왼쪽 위부터 시작하지 말고, 오른쪽 위부터 시작해서
   1. ary[i][j] < target: 더 큰 수 를 찾아야 하므로, 오른 아래는 무조건 없다. 왼쪽으로 빠꾸. 위는 예전에 갔으므로 갈 필요가 없음.
   2. ary[i][j] > target: 더 작은 수를 찾아야 하므로, 왼위는 무조건 없다. 아래로 ㄱ. 오른쪽은 오른쪽부터 시작했으므로 갈 필요가 없음.  
   의 방식으로 \\(\mathop\{O\}(m+n\\) 탐색 가능.

이런 문제를 바로바로 풀어야 할 텐데...


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


#### Longest Valid Parenthesis
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



#### N-Queens (reference problem)
<a href="https://leetcode.com/problems/n-queens/" target="_blank">https://leetcode.com/problems/n-queens/</a>

1. Naive - on the board
2. 보드보다 상태공간을 더 잘 표현할 수 있음
    1. queen의 위치는, 1-d array의 위치가 row, 값이 column
    2. position의 조건이, rowInd+colInd와 rowInd-colInd 가 같으면 같은 대각에 있는 것이므로, 위의 두 값을 queen의 위치와 같이 저장. 같은 row/col체크는 하지 않을 것 (위에서 이미 결정하고 오므로)
    3. naive board solution은 정말 보드를 다 찾아보지만 이 solution은 row별로 어디에 놓을지만 결정해도 되므로 시간절약도 많이 될듯

	

#### Container With Most Water

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

#### Subarray Sum Equals K
https://leetcode.com/problems/subarray-sum-equals-k/
<summary>보기만</summary> 
    부분합문제인데 N^2로 풀면 TLE남.  
힌트는 값의 범위가 좁다는거였음. dic에 지금까지 나온 값들 저장해놓고 체크하면 됨.  
`collections.counter`를 쓰면 더 빨라지는듯?
   </details>




#### Find All Numbers Disappeared in an Array (reference problem)
<a href="https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/" target="_blank">https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/</a>

<summary>보기만</summary> 
    리스트 값이 리스트 내부와 range가 같고, 리스트를 체크해야 할 시 리스트 값이 -를 해두면 좋은듯
   </details>



#### Min stack (reference problem))
<a href="https://leetcode.com/problems/min-stack/" target="_blank">https://leetcode.com/problems/min-stack/</a>
<summary>보기만</summary> 
    stack의 최소값 - pair를 저장하면 됨. 큐와는 달리 top 밑에 있는 애들이 안빠지므로..
   </details>



#### Rotate image

<a href="https://leetcode.com/problems/rotate-image/submissions/" target="_blank">https://leetcode.com/problems/rotate-image/submissions/</a>

행렬 90도 rotation
<details>
   <summary>보기만</summary> 
    transpose + column exchange / 4개의 점끼리만 바꾸기. Row 2개로 swap하려고 해서 잘 안풀려서 1번으로 풀음
   </details>



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