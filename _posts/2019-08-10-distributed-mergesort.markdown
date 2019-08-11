---
layout: post
title:  "Distributed/External Merge Sort"
date:   2019-08-10 10:04:00 +0900
categories: coding
use_math: true
tags: sort distributed
---

## External Merge Sort
* `record`: single item
* `run`: sorted chunk of records

Say that, \\(m\\) elements can be load onto the memory.
* `replacement selection` method uses 2 PQ to make runs larger than \\(m\\).  
     1. load \\(m\\) records onto PQ1
     2. while PQ1 not empty  
        1. if the top record of PQ1 is larger than the end of current (incomplete) run, write it on the back (or, store it on the block for lazy writing)
        2. if not, add it to PQ2


## Distributed Merge Sort

* <a href="https://stanford.edu/~rezab/classes/cme323/S16/notes" target="_blank">https://stanford.edu/~rezab/classes/cme323/S16/notes</a>

lecture 1~4

### Preliminaries

* `RAM` model: sequential, random access memory
* `PRAM` model: parallel processor, shared memory.
* further complications: cache, comm cost, ...


#### Brent's Theorem
Let
* \\(T\_p\\): amout of (wall-clock) time algorithm takes on \\(p\\) processor(s)
* `Work`: # of processors \\(\times\\) the amount of time required to complete all computations
* lower bound\\[\frac\{T\_1\}\{p\}\leq T\_p\\] holds trivially
* `Depth`: depth of the computation DAG. Importantly,\\[\text\{Depth of the computation DAG\} \equiv \{T\_\infty\}\\]\\[\text\{# of nodes in the computation DAG\} \equiv \{T\_1\}\\]

Now,
> __Brent's theorem__: We claim that \\[\frac\{T\_1\}\{p\}\leq T\_p\leq \frac\{T\_1\}\{p\} + T\_\infty\\]

Let \\(m\_i\\) be the # of operations in level \\(i\\). Then with \\(T\_\infty = n\\) levels, \\[T\_1=\sum\_\{i=1\}^\{n\}m\_i\\]
For each level, which can be executed in parallel (no inter-dependencies), the time taken by \\(p\\) processors is
\\[T\_p^i=\lceil\frac\{m\_i\}\{p\}\rceil \leq \frac\{m\_i\}\{p\} + 1\\] Then,
\\[T\_p=\sum\_\{i=1\}^\{n\}T\_p^i\leq \sum\_\{i=1\}^\{n\} \frac\{m\_i\}\{p\} + 1 = \frac\{T\_1\}\{p\}+T\_infty\\]

EX) __Summation__: using tournament method, the depth is \\(\log n\\), so that
\\[T\_p\leq n/p + \log\_2n\\]


### Locality of reference
https://stackoverflow.com/questions/30867112/does-partition-function-gives-quick-sort-its-locality-of-reference
In general, code has good locality of reference if the memory accesses it makes tend to be sequentially located around a small number of areas of memory. For example, linear search over an array has great locality of reference because all the elements appear adjacent in memory, but linear search over a linked list has poor locality because the linked list cells don't necessarily appear consecutively in memory.

Let's take a look at quicksort. The "meat" of the quicksort algorithm is the partitioning step, where elements are rearranged around a pivot. There are several strategies for implementing the partition algorithm, most of which have excellent locality. One common approach works by scanning inward from the ends of the array toward the center, swapping elements whenever they're relatively out of place. This algorithm keeps most of the array accesses confined to two regions - the ends of the array - and accesses elements sequentially, so it has great locality.

Another partitioning strategy works by scanning from the left of the array to the right, storing two pointers delimiting the regions holding the smaller values and the greater values. Again, the array accesses are all sequential, so the locality is really good.

Now, contrast that with heapsort. In heapsort, the heap operations require you to repeatedly compare elements at one position with elements whose index is twice or half the index of that element. This means that the array accesses are scattered across the array rather than sequential, so the overall locality is a lot worse.

Mergesort actually has somewhat decent locality due to how the merge step works. However, because it maintains an auxiliary buffer array that's as large as the input array, it has to pay the cost of extra memory and its accesses are therefore a bit more scattered than quicksort's accesses.