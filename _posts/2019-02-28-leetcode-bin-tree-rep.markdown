---
layout: post
title:  "Leetcode - Binary tree Problems"
date:   2019-02-28 8:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review recursive binary_tree
---


### Representation

<a href="https://support.leetcode.com/hc/en-us/articles/360011883654-What-does-1-null-2-3-mean-in-binary-tree-representation-" target="_blank">https://support.leetcode.com/hc/en-us/articles/360011883654-What-does-1-null-2-3-mean-in-binary-tree-representation-</a>

https://support.leetcode.com/hc/article_attachments/360021719613/Screen_Shot_2018-12-26_at_4.45.25_PM.png


### Binary Tree Inorder Traversal
recursive - trivial 

<a href="https://leetcode.com/problems/binary-tree-inorder-traversal/submissions/" target="_blank">Binary Tree Inorder Traversal</a>

iterative: 
1. maintain a stack and an iterator
2. iterator = root
3. if iterator is not null, then save the current node to stack, and move the iterator to the left
4. if iterator is null, it means that  
    1. we've traversed all nodes in the left
    2. node in the top of the stack is the most recent node
    
    pop from the stack, print it (inorder!), move iterator to the right.

```python
def inorderTraversal(self, root):
    """
    :type root: TreeNode
    :rtype: List[int]
    """
    
    st, cur = [], root
    ret = []
    while len(st) or cur != None:
        if cur:
            st.append(cur)
            cur = cur.left
        else:
            nd = st.pop()
            ret += [nd.val]
            cur = nd.right
            
    return ret
```