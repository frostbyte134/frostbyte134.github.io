---
layout: post
title:  "BOJ 2873: 롤러코스터"
date:   2018-05-25 10:47:00 +0900
categories: problem_solving
use_math: true
tags: problem_solving reference_problem
problem: 2873
---

<a target="_blank" href="https://www.acmicpc.net/problem/{{page.problem}}">https://www.acmicpc.net/problem/{{page.problem}}</a><br/><br/>

왓더...쉬워보였는데 아니었다. 보드문제는 dp나 네트워크플로우를 못쓰면 바로 거지같아지네..

R, C가 홀수/홀수, 홀수/짝수인 경우에는 모든 노드를 방문할 수 있다. 짝수/홀수인 경우는 스왑하면 됨.  
따라서 짝수/짝수인 경우가 문제인데, 난 이 경우엔 직접 보드를 두시간동안 그려보고 노드 위치가 (짝, 홀)이나 (홀, 짝)인 곳 중 하나를 빼고 나머지를 다 방문할 수 있다는 걸 알았음.  

<a href="https://codersbrunch.blogspot.kr/2016/09/2873.html">`다른 풀이`</a>에서는, 결국 (R, C)=(짝, 짝)인 경우에는 모든 노드를 두 집합 A={(짝, 짝), (홀, 홀)} 과 {(홀, 짝), (짝, 홀)}로 나누면 상하좌우 방문시에는 짝홀여부가 둘 중 하나만 반전되므로 홀수번의 방문으로 시작(짝, 짝) -> 끝(짝, 짝)의 경로로 모든 노드를 방문할 수 없다는 것을 보임.  

출력은 의외로 짧게 됨. 짝/짝만 특이케이스이기 때문에...

보드판의 짝홀을 좀 신경써보자.