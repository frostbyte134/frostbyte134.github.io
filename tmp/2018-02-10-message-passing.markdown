---
layout: post
title:  "BOJ 13328: Message Passing"
date:   2018-02-10 18:18:05 
categories: problem_solving
use_math: true
tags: problem_solving dp
---

<a target="_blank" href="https://www.acmicpc.net/problem/13328">https://www.acmicpc.net/problem/13328</a><br/>
(2.10 복습완료)<br/>
<br/>
문제를 풀려면 두 단계가 필요.<br/>
1. 점화식 파트<br/>
\\(i\\)번째에 발생한 전화를 고려해 볼 때, 결국 \\(i-d\\)번째 발생한 전화가 \\( d \leq k\\) 일시 \\(i\\)번째에도 전화를 발생시키므로,
\\[ A(i)=\sum_{d\leq k}{A(i-d)} \\]
의 점화식이 생김.

2. 점화식이 크기가 큼. k는 50까지밖에 없으므로 행렬 거듭제곱으로 풀 수 있음.<br/>
이부분에서 시간이 좀 걸렸다. closed equation을 찾으려고 했음...<br/>
거듭제곱 코드
```c++
for (; T != 0; T >>= 1){
	if(T & 1)I = I * M;
	M = M * M;
}
```
를 외워놓으면 나중에 도움이 될듯.<br/>

[quan]: https://github.com/nailbrainz/Algospot/blob/master/QUANTIZE/QUANTIZE.cpp