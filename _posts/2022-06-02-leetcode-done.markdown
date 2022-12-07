---
layout: post
title:  "Leetcode problems - Done"
date:   2021-05-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review
---

굳이 리뷰할필요 없는 느낌쓰들



### Done

### https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
- 난 2-pass로 풀었는데 (나름 맘에듬), general solution이 있었음. 제너럴한걸로 풀어 보자
- dp말고 계산할거를 따로 저장할떈 이거 초기값 등도 잘 신경써야 함

### Step-By-Step Directions From a Binary Tree Node to Another
- <a href="https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/" target="_blank">https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/</a>
<details>
   <summary>트리 구현 문제로는 좋은듯</summary> 
    값도 유니크하니까 LCA도 됨
   </details>


#### https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/description/
ez. 리뷰만 (설명하기)

#### https://leetcode.com/problems/continuous-subarray-sum/description/
흠. 답 보긴 봤음. 다시 ㄱㄱ
- 다시했을땐 풀긴 함. 배라는 것이 중요
#### https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/
- 쉽게 풀긴 했는데, 더 깔끔한 풀이 유도하기


### https://leetcode.com/problems/reverse-nodes-in-k-group/
https://leetcode.com/problems/reverse-nodes-in-k-group/
- 아씨...글쓰면서 (예제 만들면서 주절주절) 하자

### unique-paths-iii

* <a href="https://leetcode.com/problems/unique-paths-iii/description/" target="_blank">https://leetcode.com/problems/unique-paths-iii/description/</a>
* <details>
   <summary>Aㅏ...</summary>늙었구나...</details>


#### Optimal Account Balancing
* <a href="https://leetcode.com/problems/optimal-account-balancing/" target="_blank">https://leetcode.com/problems/optimal-account-balancing/</a>
* <details>
   <summary>잘 생각해 보면</summary>우선 transaction의 역순으로 하면 되니까 이거보다 큰 답은 없고, transaction을 압축하는 형태로 최적의 답이 나올 테니 각 노드의 값을 이상하게 쪼개는 경우는 없을 듯. 있는 거 다 쓰면서 완탐하면 될 듯
   . 어째 갈수록 느려지네...;_;</details>

### https://leetcode.com/problems/top-k-frequent-elements
https://leetcode.com/problems/top-k-frequent-elements
- nlogN은 개껌이고, N으로 다시 풀어 보기 (쪼금 햇갈림)

#### Merge Intervals

<a href="https://leetcode.com/problems/merge-intervals/" target="_blank">https://leetcode.com/problems/merge-intervals/</a>

1. 인터벌 (a, b)들을 오름차순으로 정렬
2. valid non-intersecting interval 집합을 유지한다고 할 시, 현재 고려중인 interval은 
    1. valid 집합의 마지막 interval보다 a값은 크다
    2. 따라서, valid 집합의 마지막 interval과 머지되지 않을 시, 나머지들과 머지될 일은 없음.
3. 변형이 좀 있을 수 있는 듯 ㅋㅋ



### https://leetcode.com/problems/word-ladder/
https://leetcode.com/problems/word-ladder/
- 효과적으로 풀 수 있는 방법 생각나면 DONE으로

### https://leetcode.com/problems/binary-tree-maximum-path-sum/
https://leetcode.com/problems/binary-tree-maximum-path-sum/
- 보기만


### https://leetcode.com/problems/jump-game-ii/
https://leetcode.com/problems/jump-game-ii/
- 걍 보기만


#### https://leetcode.com/problems/number-of-good-paths/description/
- https://leetcode.com/problems/number-of-good-paths/description/
- 너무하네...
* <details>
   <summary>오 두번쨰는 잘 풀음 ㅎㅎ</summary>두번쨰에서 count한 뒤 나보다 큰 인접노드까지 merge할라고 했는데 이럼 넘 큰 것까지 merge되어버림. 그냥 시작할 때 자기랑 같은 거 머지하면 됨. 또, nC2 = n-1까지의 합 ㅋㅋ</details>

   
#### Path with Maximum Gold
<a href="https://leetcode.com/problems/path-with-maximum-gold/" target="_blank">https://leetcode.com/problems/path-with-maximum-gold/</a>

2차원 grid에서, 재방문이 불가 & 0을 방문하지 못할 시, 모을 수 있는 가장 많은 값은? (방문시 값 get)
* n, m이 해봐야 15, 논제로 아이템이 25개가 맥시멈 -> 완탐
* dp도 되지 않을까? 논제로 아이템 25개에 대한 상태공간 (25bit)만...안되겠네



#### Minimum Area Rectangle
- <a href="https://leetcode.com/problems/minimum-area-rectangle/" target="_blank">Minimum Area Rectangle</a>
- 쉬운 문제고 어렵지 않게 풀긴 했는데, 검사조건을 명확하게 도출하지 못함. 다시 해보자. 다시 했음. 이전문제는 좀 naive하게 풀었던거 같음.
- 그림 안그렸으면 한번에 솔브 못했을듯?ㅋㅋ...



#### https://leetcode.com/problems/sum-of-subarray-ranges/
- https://leetcode.com/problems/sum-of-subarray-ranges/



#### https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/
풀긴 걍 풀음 ㅎㅎ 아직 죽진 않았구먼


#### Longest Increasing Path in a Matrix
- <a href="https://leetcode.com/problems/longest-increasing-path-in-a-matrix/" target="_blank">https://leetcode.com/problems/longest-increasing-path-in-a-matrix/</a>
- 하드인데 쉬웠음. 보드에서의 increasing path이므로, 왔던 곳으로 다시 못 감 - cache 이용가능 



### Flip Equivalent Binary Trees
- https://leetcode.com/problems/flip-equivalent-binary-trees/
- 그냥 생각만...일부 노드면 flip된 경우를 flip equivalent라고 할 경우, 두 트리가 서로 flip equivalent일 조건은?


### Validate Stack Sequences
* <a href="https://leetcode.com/problems/validate-stack-sequences/" target="_blank">꼭 다시 보자 (보기만)</a>
* <details>
   <summary>다시보기</summary> 
   we can try man (indeed)
   </details>

### delete nodes and return forest
- <a href="https://leetcode.com/problems/delete-nodes-and-return-forest/" target="_blank">https://leetcode.com/problems/delete-nodes-and-return-forest</a>
- 복습까진 필요없는 듯. 중복정보를 본인도 처리하고 자손도 중복으로 처리해서 느렸다. 자손에서 return으로 보내 줬으면 됐을 껄...이거 면접에서 이래 죽쓰면 풀긴 풀었는데 감점 엄청 당할듯.
