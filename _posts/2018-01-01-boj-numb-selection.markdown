---
layout: post
title:  "BOJ 2230: 수 고르기"
date:   2018-01-01 15:57:05 
categories: problem_solving
use_math: true
tags: problem_solving
---
<a target="_blank" href="https://www.acmicpc.net/problem/2230">https://www.acmicpc.net/problem/2230</a><br/>
문제가 쉬워서 복습에 넣지 않음.<br/>
<br/>
문제가 쉬워서 복습에 넣지 않음.<br/>
유명한 문제인, 정렬된 수열에서 합해서 0이 되는 모든 3개의 숫자를 찾는 문제와 비슷.<br/>
두 개니까 오히려 간단할지도?<br/>
정렬 (\\(n\log n\\))후, 첫 두 숫자를 고른다. 다음 두 경우가 발생<br/>
1. 차이가 M 이하. 더 큰 숫자가 필요하므로 오른쪽 인덱스를 증가시킴.<br/>
2. 차이가 M 이상. 답 리스트에 추가하고, 여기서 오른쪽 인덱스를 증가시켜 봤자 더 좋지 않은 답을 얻을 뿐이므로, 왼쪽 인덱스를 증가시켜 새로운 답을 찾는다.<br/>

결국 2개의 인덱스를 N번 움직이므로, 총 시간복잡도는 \\(O\left(n\log n\right)\\). 


[quan]: https://github.com/nailbrainz/Algospot/blob/master/QUANTIZE/QUANTIZE.cpp