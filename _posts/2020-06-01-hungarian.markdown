---
layout: post
title:  "Hungarian algorithm"
date:   2020-06-01 07:00:05 +0800
categories: math
use_math: true
tags: math
---

https://gazelle-and-cs.tistory.com/29

1. Cluster matching to assignment problem
    - 2번의 k-means operation을 가정.
      - 특정 point가 i번째에는 cluster p, j번째에는 cluster q에 할당되었다면 mat(i, j) += 1. 
    - 결국 N x N의 행렬이 나오고, 여기서 값을 최대화하는 assignment를 찾으면 됨 (negate 하던지 뭐...)
2. Assignment problem은 Hungarian으로 풀 수 있음
    - 이 assignment problem은 bipartite graph에서의 matching임. 
    - 이분그래프에서는 maximum matching = minimum vertex cover임 <a href="https://gazelle-and-cs.tistory.com/12" target="_blank">(Konig's Theorem)</a>. 따라서, maximum matching대신 minimum vertex cover를 찾을 것임
    - adjacency matrix에 row / column단위로 최소값을 빼 준 뒤, 0을 갖는 원소에 주목함
      - "vertex cover는 adj mat에서 행과 열을 선택하는 것에 대응"
      - 행과 열을 합해서 n개보다 적게 뽑아 행렬의 모든 0-valued element를 덮는 방법이
            1. 있다 : minimum vertex cover가 n보다 작음. matching도 n보다 작음. 의미가 없는 결과
                - 있는 것중, 가장 크기가 작은 것 (어떻게 찾지)에서, 덮어지지 않는 가장 작은 matrix element를 \\(\eps\\)라고 함. 이 값을 덮어지지 않는 행에 대해 빼고, 덮인 열에 대해 더해줌. -  이 과정에서 행렬의 모든 원소의 총합이 monotonic하게 감소하게 되므로 (\\(\eps > 0\\) 이용. 증명은 페이지 봅시다), 알고리즘이 종료하게 됨 
            2. 없다 : 딱 n일시, n = min vertex cover = max matching. break
3. break시, 행과 열을 합해서 n개만큼 뽑아 행렬의 모든 0 원소를 덮는 방법이 있음. 이건 그 뭐냐 dfs로 이분그래프 매칭해주면 될듯. 