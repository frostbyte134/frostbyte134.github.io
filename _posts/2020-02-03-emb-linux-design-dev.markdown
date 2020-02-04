---
layout: post
title:  "임베디드 리눅스 시스템 설계와 개발"
date:   2020-02-01 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

이책도 좀 된듯. 킨들에서 사야하나...

* `POSIX` 표준: 메모리 관리, 프로세스&쓰레드 생성, 통신, 파일시스템

임베디드 / PC 리눅스 차이점
* 커널 설정 방식이 다름 (ex - 임베디드 시스템은 `CRAMFS`나 `JFFS2`같은 플래시용 파일 시스템을 필요로 함)
* 임베디드 리눅스에선 `Ash`, `Tinylogin`, `BusyBox`등이 필수적으로 고려되며, glibc보단 가벼운 `uClibc`가 자주 쓰인다고 함
* X윈도우 대산 nano-X
* 주로 슈퍼유저로 동작

임베디드 리눅스는
* 동작하기 위해 4MB의 SDRAM과 2MB의 플래시 필요
* 실시간성에서 약함 (재영책임님한테 들은거같음)

실시간 커널
- MMU없음 - 메모리 변환이 느려 실제 주소를 그대로 사용 - protection없음

Monolithic kernel
- 커널은 단일 메모리 공간에 존재
- 리눅스는 동적으로 로드가능한 `kernel module`도 사용

MicroKernel
- 커널은 통신 정도만 하며, 각 커널 모듈별로 memory protection이 됨


### 임베디드 리눅스 구조

#### HAL
`HAL` = `BSP`
