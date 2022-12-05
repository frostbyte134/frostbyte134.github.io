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