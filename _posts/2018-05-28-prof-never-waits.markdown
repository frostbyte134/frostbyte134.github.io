---
layout: post
title:  "BOJ 3830: 교수님은 기다리지 않는다"
date:   2018-05-28 21:20:05 +0900
categories: problem_solving
use_math: true
tags: problem_solving djset graph reference_problem
problem: 3830
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/>
  

{:.acounter}  
1. disjoint set  
부모와의 관계만 알면 자식끼리도 상대무게를 계산할 수 있음.  
merge에서 레벨 스왑할때 부모만 스왑하고 자식은 스왑을 안해서 총 10번은 틀린듯.....
2. dfs  
노드 수 N은 꽤나 크지만, 엣지 숫자가 굉장히 작음. 입력을 다 받아놓고 답을 생성. 역순까지는 아닌듯?..역순문제 다시 풀어봐야 하는데...   
그래프 구성할때는 djset으로 가능여부를 저장해놓고, 그래프 전부 구성후 dfs로 상대길이를 구함. 이 때 기준은 맨 첨 시작노드. 가능한 답에 대해서만 상대무게를 출력해주면 됨.
{:.acounter}


  