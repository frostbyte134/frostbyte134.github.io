---
layout: post
title:  "Max Cut Min Flow Theorem"
date:   2018-02-24 16:53:05 
categories: problem_solving
use_math: true
tags: problem_solving network_flow
---

<h1>Theorem:</h1>
<blockquote>
In a flow network, the maximum amount of flow passing from the source to the sink is equal to the total weight of the edges in the minimum cut.  
</blockquote>
  
<h1>Proof 1. Linear programming (Strong duality) - later </h1>  
  
  
<br/>
<h1>Proof 2 - Constructive proof (with Ford-Fulkerson algorithm)</h1>  
  
 Suppose that the Ford-Fulkerson algorithm terminated with a resulting flow f, and there exists no augmenting path in   the flow network. Such flow f is the maximum flow, since it is obtained by the Ford-Fulkerson.  
  
 In the residual graph G, we can divide the vertices into two sets.  
  -1. set S for vertices reachable from source  
  -2. set T for the remaining vertices  
  
In the original flow network, any residual (capacity - flow) of edges from nodes s in S to vertex t in T is 0.   Otherwise, t must be in S (reachable from s), which is a contradiction. Here we found a s-t cut, having same value with the maximum flow.  
  
Since any flow in the network is always less than or equal to the capacity of every cut, (any proofs?), obtained cut is a min cut (If there exists a lower cut c', then c'<f, which is a contradiction). QED.  