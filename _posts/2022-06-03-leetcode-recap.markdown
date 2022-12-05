---
layout: post
title:  "Leetcode problems - recap"
date:   2021-05-01 09:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review
---


다시 대충 훑어보기만 해도 되는 문제들
아 빨리 블로그 만들어야 하는데..........




### https://leetcode.com/problems/edit-distance/
https://leetcode.com/problems/edit-distance/
- 아씨..복습만 (눈팅)
- +1

#### https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/description/
- https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/description/
- 풀만했는데 못풀었음 ㅡㅡ 정줄 좀 놓은 듯..

#### https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
- https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
- 흠..낫배드. 어렵지 않은데 해맸네..
- 다시풀어도 좀 해매긴..했음 ㅋㅋ


#### Burst Baloons
<a href="https://leetcode.com/problems/burst-balloons/" target="_blank">https://leetcode.com/problems/burst-balloons/</a>
<details>
<summary>보기만 - 아니 다시 보니까 못풀음 ㅡㅡ</summary> 
    l-r 사이에서 i번째 풍선을 마지막에 터트렸을 때 얻을 수 있는 최대값 (결국 어느 풍선이던 마지막에 터트려야 함) = 결국엔 마지막에 i번째만 남았다는 듯. nums[l-1] * nums[i] * nums[r+1] (범위 밖 풍선과 묶여야 하니까) + dp[l][i-1] + dp[i+1][r]. 첨에 nums = [1] + nums + [1]해놓으면 편함
    터트렸을 때 얻을 수 있는 최대값을 dp로 잡았어야 했나..
   </details>


### max-area-of-island
- <a href="https://leetcode.com/problems/max-area-of-island/submissions/" target="_blank">https://leetcode.com/problems/max-area-of-island/submissions/</a>
- 많이 풀어 본 보드문제 (눈으로 보기만)
<details>
   <summary>다시보기</summary> 
    예전에는 bfs + set으로 풀었던 거 같은데 그럴필요 없음. 
   </details>


### sequentially-ordinal-rank-tracker
* <a href="https://leetcode.com/problems/sequentially-ordinal-rank-tracker/description/" target="_blank">https://leetcode.com/problems/sequentially-ordinal-rank-tracker/description/</a>
* <details>
   <summary>방법은 금방 알았는데 (ㅋㅋ)</summary>순차적으로 늘어나니까..ㅎㅎ heapq 연습문제</details>
- 파이썬으로 풀기에 좋지 않은 듯. 왜 좋지 않은지 빨리 생각해내기

### https://leetcode.com/problems/detonate-the-maximum-bombs/description/
- 이걸 이렇게 헷갈린다고? 너무 빨리 풀려고 한듯. 실수를 몇번 한거야..
- 지금 나에게 다시보기 좋은듯

#### LRU Cache
<a href="https://leetcode.com/problems/lru-cache/" target="_blank">https://leetcode.com/problems/lru-cache/</a>
- linked list + hash = O(1) LRU Cache! - 이거 복습 한번만 ㅋㅋ
- 내지는 PQ도 가능?

### https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/

* <a href="https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/" target="_blank">https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/</a>
* <details>
   <summary>와 풀긴 푸음</summary>난 이진탐색 2번으로 풀었는데, 투포인터 + 이진탐색이 더 빠른 듯? 이거 cand_diff >= k 인 것 중 최소를 찾아야 하는 이유 = 진짜 있는 거를 찾아야 하기 때문. cand_diff <= k 인 것 중 최대는 없는 숫자가 선택될 수도 있음 (ex - 3, 4, 5, 6 다 cand_diff가 같고 실제 있는 pair diff는 3인 경우. 실제 diff가 4가 될순 없음. 그럼 3은 4보다 자기보다 작은 숫자가 더 작을 테니까) </details>
   투포인터로 어케 풀지? - num[i] 보다 cand_diff만큼 큰 num[j] 이거 둘다 순증가해서 투포인터 가능 (순증가 투포인터는 첨보네...)ㅇ

우리가 이진탐색으로 찾는 cand_diff = 3, 4, 5, 6 다 자기보다 작거나 같은 diff의 갯수가 같고, 실제 pair끼리 diff에는 4만 있는 경우, 3 / 5 / 6은 답이 될 수 없음. 이때 3에는 contradiction 남 (자기보다 작거나 "같은" 떄문에, 3과 4의 자기보다 같은 diff 갯수는 동일). 그러므로 cand_diff중 최소인 것을 찾으면 됨

### K inverse pairs
* <a href="https://leetcode.com/problems/k-inverse-pairs-array/description/" target="_blank">링크</a>

* <details>
   <summary>다시보기만</summary> 
   버벅거리면서 풀긴 함 ㅋㅋ. 중간식이 진짜 맞는 거 같으면 초기조건은 대충 때우자
   </details>
