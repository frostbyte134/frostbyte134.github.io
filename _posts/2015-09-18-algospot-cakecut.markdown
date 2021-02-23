---
layout: post
title:  "Algospot: Cakecut"
date:   2015-09-18 23:11:05 
categories: problem_solving
use_math: true
tags: problem_solving
---

마찬가지 dp. 연습 겸 예전에 풀었던 문제들이나 다시 풀어보는 중.<br/>
lartest piece가 minimum이 되어야 하므로, min( max ) 가 됨.<br/>
dp[ 넓이 ][ 길이 ][ 쪼갤 수 있는 갯수 ]= 넓이와 길이, 쪼갤 수 있는 갯수를 훑는데 필요한 for문 3개 + 각 (넓이+쪼갤 수 있는 갯수) 와 (길이+쪼갤 수 있는 갯수)를 이등분하는데 쓰이는 for문 2개를 더하여 5중 for문인데..<br/>
일단 90도 돌려도 답은 변하지 않으므로 w>h란 제약을 걸면 반으로 줄겠고..<br/>
점화식을 좀 좋게 짜면 더 빨리 풀릴 것 같긴 한데 지금은 잘 모르겠다.<br/>
<br/>
문제 링크 : https://algospot.com/judge/problem/read/CAKECUT<br/>
git link : [CAKECUT][ccut]<br/>
<br/>


[ccut]: https://github.com/nailbrainz/Algospot/blob/master/CAKECUT/source.cpp