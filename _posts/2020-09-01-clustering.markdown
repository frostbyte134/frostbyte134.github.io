---
layout: post
title:  "clustering"
date:   2020-09-01 09:10:05 +0800
categories: math
use_math: true
tags: math
---

### References
- <a href="https://people.csail.mit.edu/dsontag/courses/ml14/notes/Luxburg07_tutorial_spectral_clustering.pdf" target="_blank">https://people.csail.mit.edu/dsontag/courses/ml14/notes/Luxburg07_tutorial_spectral_clustering.pdf</a>

- <a href="https://www.cs.toronto.edu/~tijmen/csc321/slides/mog.pdf" target="_blank">https://www.cs.toronto.edu/~tijmen/csc321/slides/mog.pdf</a>


<a href="https://www.quora.com/How-is-the-k-nearest-neighbor-algorithm-different-from-k-means-clustering" target="_blank">맨날 해깔리는 k-nn</a>
- k-nn is a classification (voting wrt K-nearest neighbors), supervised (voting between supervised labels)


Category
- parametric - `K-means`
- graph-based - `spectral clustering`

### Clustering intro
- <a href="https://sparse-plex.readthedocs.io/en/latest/book/clustering/intro.html#sec-clustering-performance-measure-intro" target="_blank">https://sparse-plex.readthedocs.io/en/latest/book/clustering/intro.html#sec-clustering-performance-measure-intro</a>
- distance : `Mahanalobis distance` \\[d^2(x\_s, \mu\_k) = \|\| x\_s - \mu\_k\|\|^2\_\{\Sigma\_k\}=(x\_s-\mu\_k)^T\Sigma\_k^\{-1\}(x\_s-\mu\_k).\\]
  - is used, since it invariant to the change of basis
  - For Gaussian distributions, this is proportional to the negative of the log-likelihood of a sample point
- Simple ways : dot prod (cos), 

### Spectral algorithm
> <a href="https://people.csail.mit.edu/dsontag/courses/ml14/notes/Luxburg07_tutorial_spectral_clustering.pdf" target="_blank">A Tutorial on Spectral Clustering</a>

References
- <a href="https://techblog-history-younghunjo1.tistory.com/93?category=863123" target="_blank">https://techblog-history-younghunjo1.tistory.com/93?category=863123</a>
- <a href="https://elecs.tistory.com/167?category=643381" target="_blank">https://elecs.tistory.com/167?category=643381</a>
- <a href="https://ratsgo.github.io/machine%20learning/2017/04/27/spectral/" target="_blank">https://ratsgo.github.io/machine%20learning/2017/04/27/spectral/</a>



### Hungarian algorithm (Ensembel k-means and Assignment problem)



1. <a href="https://sohnnn.tistory.com/entry/Ensemble-Kmeans" target="_blank">Cluster matching to assignment problem</a>
    - 2번의 k-means operation을 가정.
      - 특정 point가 i번째에는 cluster p, j번째에는 cluster q에 할당되었다면 mat(i, j) += 1. 
    - 결국 N x N의 행렬이 나오고, 여기서 값을 최대화하는 assignment를 찾으면 됨. 헝가리안은 minimum perfect matching을 찾으니 negate 해줘야 함
2. <a href="https://gazelle-and-cs.tistory.com/29" target="_blank">https://gazelle-and-cs.tistory.com/29</a> Assignment problem은 Hungarian으로 풀 수 있음
    - 이 assignment problem은 bipartite graph에서의 perfect matching임 (n == m). 
    - 이분그래프에서는 maximum matching = minimum vertex cover임 <a href="https://gazelle-and-cs.tistory.com/12" target="_blank">(Konig's Theorem)</a>. 따라서, maximum matching대신 minimum vertex cover를 찾을 것임
    - adjacency matrix에 row / column단위로 최소값을 빼 준 뒤, 0을 갖는 원소에 주목함
      - "vertex cover는 adj mat에서 행과 열을 선택하는 것에 대응"
      - 행과 열을 합해서 n개보다 적게 뽑아 행렬의 모든 0-valued element를 덮는 방법이
            1. 있다 : minimum vertex cover가 n보다 작음. matching도 n보다 작음. 의미가 없는 결과
                - 있는 것중, 가장 크기가 작은 것 (어떻게 찾지)에서, 덮어지지 않는 가장 작은 matrix element를 \\(\epsilon\\)라고 함. 이 값을 덮어지지 않는 행에 대해 빼고, 덮인 열에 대해 더해줌. -  이 과정에서 행렬의 모든 원소의 총합이 monotonic하게 감소하게 되므로 (\\(\epsilon > 0\\) 이용. 증명은 페이지 봅시다), 알고리즘이 종료하게 됨 
            2. 없다 : 딱 n일시, n = min vertex cover = max matching. break
3. break시, 행과 열을 합해서 n개만큼 뽑아 행렬의 모든 0 원소를 덮는 방법이 있음. 이건 그 뭐냐 dfs로 이분그래프 매칭해주면 될듯. 