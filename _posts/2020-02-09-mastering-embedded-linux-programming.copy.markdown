---
layout: post
title:  "임베디드 리눅스 프로그래밍 완전정복"
date:   2020-02-09 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

임베디드 리눅스 4요소
- 툴체인 (크로스 컴파일을 위한 모든 도구)
- 부트로더, 커널, 루트 파일시스템 (커널의 초기화 뒤 로딩되는 init ram disk보유)

### 툴체인
고려 요소 - CPU아키텍처, 네이티브/크로스, c라이브러리, (glibc, ulibc)