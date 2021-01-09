---
layout: post
title:  "Ford-Fulkerson Algorithm"
date:   2018-02-24 11:24:05 
categories: problem_solving
use_math: true
tags: problem_solving graph network_flow
---
1. 방식  
BFS로 1개의 증가경로 탐색 -> flow 업데이트 (symmetry).  
 
2. 증명  
-1. 종료 시 정당성 (답을 찾았는가)  
Min cut max flow theorem (링크) 덕분에 우리는 augmenting path 가 없는 flow network에서 찾은 flow가 max flow임을 알 수   있음. (???종만북 증명이 먼가...서로 물렸네)  
  
3. time complexity  
total flow increases by (at least) 1 when we find the augmenting path with BFS.  
BFS requires \\(O(|V|+|E|)\\), and we have to run it at least f times, which gives  
\\(O((|V|+|E|)f)\\) complexity.   
  
```c++
int tf = 0, src = 1, dst = N;
while (true){
    vector<int> p(MAX_V, -1);
    queue<int> Q;
    p[src] = src;
    Q.push(src);
    while (Q.size() && p[dst] == -1){
        int nd = Q.front();
        Q.pop();
        for (int there = 0; there < MAX_V; there++){
            if (cap[nd][there] - flow[nd][there] > 0 && p[there] == -1){
                Q.push(there);
                p[there] = nd;
            }
        }
    }
    if (p[dst] == -1)break;
    int amt = INF;
    for (int nd = dst; p[nd] != nd; nd = p[nd]){
        amt = min(amt, cap[p[nd]][nd] - flow[p[nd]][nd]);
    }
    for (int nd = dst; p[nd] != nd; nd = p[nd]){
        flow[p[nd]][nd] += amt;
        flow[nd][p[nd]] -= amt;
    }
    tf += amt;
}
```