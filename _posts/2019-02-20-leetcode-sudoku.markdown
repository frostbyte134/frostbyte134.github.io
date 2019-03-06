---
layout: post
title:  "Leetcode - Sudoku Solver"
date:   2019-02-20 8:59:00 +0800
categories: problem_solving
use_math: true
tags: problem_solving leetcode need_review recursive
---

<a href="https://leetcode.com/problems/sudoku-solver/submissions/" target="_blank">https://leetcode.com/problems/sudoku-solver/submissions/</a>

답이 무적권 있다고 해서 backtracking에서 각 시도 중 답이 무조건 나오는 게 아니지...취소해야 할 수도 있는 것인데요 ㅡㅡ

너무 오랜만에 문제풀이를 하나...
	

```python
class Solution:
    cont = True

    def solveSudoku(self, board: 'List[List[str]]') -> 'None':
        crow = [[0 for i in range(9)] for j in range(9)]
        ccol = [[0 for i in range(9)] for j in range(9)]
        cbox = [[0 for i in range(9)] for j in range(9)]

        for ind in range(81):
            if board[ind // 9][ind % 9] != '.':
                num = int(board[ind // 9][ind % 9]) - 1
                crow[ind // 9][num], ccol[ind % 9][num], cbox[((ind // 9) // 3) * 3 + (ind % 9) // 3][num] = 1, 1, 1


        def solve(ind):
            if ind >= 81:
                self.cont = False

                return

            while True:
                row, col, box = ind // 9, ind % 9, ((ind // 9) // 3) * 3 + (ind % 9) // 3
                if board[row][col] == '.':
                    for num in range(9):
                        if crow[row][num] == 0 and ccol[col][num] == 0 and cbox[box][num] == 0:
                            crow[row][num], ccol[col][num], cbox[box][num] = 1, 1, 1
                            board[row][col] = str(num + 1)
                            solve(ind + 1)
                            if not self.cont:
                                return
                            board[row][col] = '.'
                            crow[row][num], ccol[col][num], cbox[box][num] = 0, 0, 0
                    break
                else:
                    ind = ind + 1
                    if ind == 81:
                        self.cont = False
                        break

        solve(0)
```
