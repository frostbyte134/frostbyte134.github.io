---
layout: post
title:  "BOJ 4716: 풍선"
date:   2018-01-01 15:49:05 
categories: problem_solving
use_math: true
tags: problem_solving
---
<a target="_blank" href="https://www.acmicpc.net/problem/4716">https://www.acmicpc.net/problem/4716</a><br/>
문제가 쉬워서 복습에 넣지 않음.<br/>
<br/>
N개의 팀이 있고, 각 팀에 K개의 풍선을 배정해야 함.<br/>
풍선은 두 곳에 있고, 각각 A개, B개만큼의 재고가 있음. 각 팀마다 두 곳까지의 거리가 다름.<br/>
이 때 각 팀에 K개의 풍선을 배정하는 최소 거리.<br/>
<br/>
결국 각 팀에게는 K개의 풍선을 배정해야 하므로 거리의 절대크기는 중요하지 않음. 중요한 것은<br/>
각 팀마다의 두 거리 차이임. <br/>
정렬 후 그리디하게 풀음.<br/>
<br/>



[quan]: https://github.com/nailbrainz/Algospot/blob/master/QUANTIZE/QUANTIZE.cpp