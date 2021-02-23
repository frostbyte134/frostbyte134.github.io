---
layout: post
title:  "BOJ 8872: 빌라봉"
date:   2018-05-14 14:44:00 +0900
categories: problem_solving
use_math: true
tags: problem_solving dp graph need_review reference_problem
problem: 8872
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/><br/>
  
  
트리의 모든 노드에 대해, 다른 노드로 갈 수 있는 최장거리(max)의 최소값(min)을 찾아야 함. 이를 트리의 `minmax 거리`로 정의.
처음에는 각 엣지에 대한 dp를 생각했으나 timeout. 
  
엣지에 대해 dp를 생각한 이유는, 한 노드를 root로 잡아 탐색을 한번 돌리는걸로는 각 노드의 최장거리를 못구한다고 생각해서였으나 구할 수 있었음...  
  
{:.acounter}  
1. dp[node]를 해당 노드의 parent방향을 제외한 최장거리라고 정의. 탐색1번만에 구할 수 있으며, root에서만 거리가 제대로 구해진다.
2. 다음으로는 같은 root에서 2번째 탐색을 진행하며, root에서 제대로 구한 거리를 전파함. root쪽에서 넘어온 최장거리 + 해당쪽의 엣지 weight을 더하면 root쪽의 거리를 구할 수 있음. root를 제외한 부분의 거리는 1번 탐색에서 구했으므로, 전부 비교하면 최장거리를 구할 수 있음.
3. 최장거리를 구한 후 자손들에게 거리를 전파할 때 2번째 최장거리가 필요해지는데, 왜냐면  
  -1. 최장거리 == dp[해당 자손] + 그 방향의 weight  
  이라면, 2번째 큰 최장거리를 넘김. 자손이 본인방향의 최장거리를 받아 봤자 중복이므로.  
  -2. 아니라면, 최장거리를 넘기면 됨.  
{:.acounter}
    
그리고 트리 내부의 최장거리도 구해야 함. <a href="{{site.url}}/problem_solving/2018/03/13/time-to-live.html" target="_blank">bfs2번으로 구할수도 있으나</a>, 2번째 dfs중 1번째 최장거리 + 2번째 최장거리로 구할 수 있음.

마지막으로, 각 부분 트리를 합쳐 최장거리가 가장 짧은 트리를 만들어야 함. 우선 `minmax 거리`가 가장 긴 트리에 (해당 `minmax 거리`를 보유한 노드에) 나머지 노드들을 붙일 것임. 이 때 첫 번째로 생각할 수 있는 최장거리 후보는
`minmax 거리`가 가장 긴 subtree + L + 2번째로 긴 subtree  
임. 위와 같이 하지 않았을 시, 어디에선가  
`minmax 거리`가 가장 긴 subtree + 2L + 2번째로 긴 subtree + \\(\alpha\\)  
의 구조가 생기기 때문에, 나머지를 아무리 잘 배열하더라도 2번째는 1번째보다 최장거리가 김.   
그러나 1번째 경우에서도 2번째 subtree + 2L + 3번째 subtree가 더 길 수 있으므로, 3가지 값
1. 모든 subtree에서 가장 긴 최장거리
2. minmax 거리가 가장 긴 subtree + L + 2번째로 긴 subtree
3. 2번째 subtree + 2L + 3번째 subtree  
를 비교해야 답이 나옴. 마지막 `모든 subtree에서 가장 긴 최장거리`를 고려하지 않아 좀 해맸다..