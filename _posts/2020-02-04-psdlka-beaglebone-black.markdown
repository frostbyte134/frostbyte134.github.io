---
layout: post
title:  "Beaglebone black + PSDKLA / TI-RTOS (SYS/BIOS?)"
date:   2020-02-11 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

* Processor SDK RTOS Automotive (`PSDKRA`) and Processor SDK Linux Automotive (`PSDKLA`)

* <a href="https://archlinuxarm.org/platforms/armv7/ti/beaglebone-black" target="_blank">BBB spec</a>
  * TI Sitara AM3359 1-GHz superscalar ARM Cortex-A8
  * 2x 200MHz ARM7 programmable real-time coprocessors
  * 5 serial ports (1 via debug header, 4 more on side headers)



* https://beagleboard.org/pru

* ti `PSDKLA` - <a href="https://www.ti.com/tool/PROCESSOR-SDK-AM335X" target="_blank">https://www.ti.com/tool/PROCESSOR-SDK-AM335X</a>
* <a href="http://software-dl.ti.com/processor-sdk-linux/esd/docs/06_01_00_08/linux/Overview_Getting_Started_Guide.html#linux-sd-card-creation-guide" target="_blank">processor-sdk-linux</a>

현재 설치 완료, PL2303으로 콘솔 접속. vscode테스트는 안해봤네.

TODO
* linux로 크로스 컴파일 - 완료
* vision_apps 돌려보기. 근데 돌릴 수 있게 나오나? 잘 모르겠네?
  * 돌릴 수 없음. 근데 뭐든 하려면 CCS를 써야되는데, 단순 serial 연결 가지곤 CCS를 쓸 수가 없음 `JTAG`이 필요함. 사야할듯




### training.ti.com/processor-sdk-training-series
* <a href="https://training.ti.com/processor-sdk-training-series" target="_blank">https://training.ti.com/processor-sdk-training-series</a>


