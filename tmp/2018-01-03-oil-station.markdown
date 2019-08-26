---
layout: post
title:  "BOJ 13308: 주유소"
date:   2018-01-01 15:57:05 
categories: problem_solving
use_math: true
tags: problem_solving graph
---
<a target="_blank" href="https://www.acmicpc.net/problem/13308">https://www.acmicpc.net/problem/13308</a><br/>
<br/>
약간 더 최적화가 가능할 거 같긴 한데..<br/>
<br/>
엣지 수가 작은 경우에, \\(V^3\\) 보다 \\(V^2log(E)\\)가 훨씬 작은 특수한 경우, <br/>
다익스트라를 V번 돌리는 게 플로이드보다 나을 수 있다는 게 포인트.<br/>
<br/>
PQ를 이용한 다익스트라에서 visited처리를 안해주면 타임오버가 난다. 평소엔 N나오면 종료하니까 괜찮았지만..<br/>
<br/>

[quan]: https://github.com/nailbrainz/Algospot/blob/master/QUANTIZE/QUANTIZE.cpp