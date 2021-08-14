---
layout: post
title:  "System Design Interive"
date:   2021-08-14 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---


### Chap 4 Rate Limiter
- [참고](https://stripe.com/blog/rate-limiters)

response header에 `X-Ratelimit-Remaining`, `X-Ratelimit-Limit` 등 넣어 줌. 표준은 아닌 것 같은데?

1. 클라 vs 미들웨어 vs 서버
   - 클라에 적용하긴 보통 쉽지않음. 누가 무슨 클라를 쓸 줄 알고?
   - 서버에 부담주기도 싫음
   - 그럼 미들웨어지 ^^ 대신 1홉이 더 생기는 듯
2. 알고리즘
   - 시간측정을 어떻게 하느냐가 문제되는 듯
   - `token bucket` / `leaky bucket` : 리필되는 토큰이 있어야 전송해 줌. 토큰 리필 처리가 중요. leaky bucket은 끝부분에 큐를 둬서 request나가는 속도를 조절
   - 토큰 리필 처리
      1. 카운트 - 누군가 주기적으로 채워줘야 함
      2. timestamp저장 - timestamp만으로 대략적인 rate 게산 가능
   - 윈도우 기반 : 윈도우 경계쪽에서 burst로 나가는 경우 문제되는 듯. 경계에선 윈도우를 쪼개 시간 비율로 계산하는 법도 있음
3. 문제
   - 동기화가 제일 큰 문제인듯. 보통 redis로 atomic하게 하지만 요청이 너무 몰리면?
     - soft limit 정도가 괜찮아 보임
   - 룰 저장은 어디에 하고 어떻게 업데이트 할 것인가? 보통 디비에 넣고 메모리에 저장해두는게 일반적일테지만..



### Chap 5 consistent hasing
- ex) 몽고디비. 키를 서버에 나눠서 저장 밑 hashing으로 찾아가기
  - 나머지 연산자는 서버 추가/삭제 시 모든 키를 재배치해야 함
  - 링 방식으로, 키는 "자기와 제일 가까운 서버"에 저장된다고 할 시 키 개수 / 서버 수 정도만 재배치하면 됨. 굳


