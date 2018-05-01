---
layout: post
title:  "Segment tree"
date:   2018-03-11 13:00:00
categories: problem_solving
use_math: true
tags: problem_solving dnq segment_tree
---

```c++
int ary[MAXN * 4];

int update(int ind, int val, int node, int from, int to){
	if (ind < from || to < ind)return ary[node];
	if (from == to)return ary[node] = val;
	int mid = (from + to) / 2;
	return ary[node] = update(ind, val, node * 2, from, mid) + update(ind, val, node * 2 + 1, mid+1, to);
}

int squery(int x, int y, int node, int from, int to){
	if (x > y)return 0;
	if (y < from || to < x)return 0;
	if (x <= from && to <= y)return ary[node];
	int mid = (from + to) / 2;
	return squery(x, y, node * 2, from, mid) + squery(x, y, node * 2 + 1, mid+1, to);
}
```