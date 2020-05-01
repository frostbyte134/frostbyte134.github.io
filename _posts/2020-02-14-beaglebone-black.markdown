---
layout: post
title:  "Beaglebone black (setting, GPIO, PRU, Camera)"
date:   2020-02-14 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

* <a href="https://cdn-shop.adafruit.com/datasheets/BBB_SRM.pdf" target="_blank">BBB Datasheet</a>
* <a href="https://github.com/derekmolloy/boneDeviceTree" target="_blank">BBB debice tree</a>
  * - has a header table at doc folder
* <a href="https://www.ti.com/lit/ug/spruh73q/spruh73q.pdf" target="_blank">AM337X Tech Ref Manual (memory map)</a>

* <a href="http://blog.naver.com/PostList.nhn?blogId=75rudals" target="_blank"> BBB Korean blog </a>

<img src="{{site.url}}/images/embedded/bbb_ports.png" width="600">


### Installing embedded linux
eMMC linux is not portable with vscode (glibc dependency).

<a href="https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone+Black" target="_blank">https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone+Black</a>

### UART
<img src="{{site.url}}/images/embedded/bbb_uart.jpg" width="600">

### GPIO
* <a href="https://webnautes.tistory.com/699?category=610469" target="_blank">LED + GPIO (gnd + gpio directly)</a>
* <a href="https://hoban123.tistory.com/57" target="_blank">https://hoban123.tistory.com/57</a>
* <a href="https://embejied.tistory.com/82" target="_blank">LED + GPIO (gnd + gpio directly)</a>
* <a href="https://memnoth.github.io/2016/05/beagleboard-handle-gpio-by-mmap-01/" target="_blank">MMAP gpio</a>

EX) GPIO 2번 핀 쓰기 (레지스터로 조종)
1. <a href="https://www.ti.com/lit/ug/spruh73q/spruh73q.pdf" target="_blank">AM337X Tech Ref Manual (memory map)</a>의 메모리 맵 참고
2. 2.1의 메모리멥에서 2번 핀의 레지스터들은 `0x481A_CFFF` 에 매핑되어 있음 (4KB: 1000h = 0x1000 사용). 
3. 25.4.1에서 GPIO_OE는 offset이 134h임: `0x481A_CFFF + 0x134`에 핀번호 참고해서 (ex: 3번핀: 1\<\<3) 쓰면 됨
4. 데이터아웃 레지스터도 참고해서 쓰면 됨

recent kernel - GPIO 1, 2, 3 is not automatically enabled - must enable CM_PER_GPIO2_CLKCTRL?

### PRU
* <a href="http://www.ti.com/lit/ug/spruij2/spruij2.pdf?ts=1588210569067" target="_blank">TI manual</a>
* <a href="https://catch22eu.github.io/website/beaglebone/beaglebone-pru-c/" target="_blank">blog?</a>

### Camera
* <a href="https://github.com/ArduCAM/BeagleboneBlack" target="_blank">Arducam (ov7670) library for BBB </a>
* <a href="https://github.com/Scorpiion/Beagleboard-xM-Linux-Kernel/blob/master/drivers/media/video/ov7670.c" target="_blank"> BBB ov7670 driver </a>
* <a href="http://embeddedprogrammer.blogspot.com/2012/07/hacking-ov7670-camera-module-sccb-cheat.html" target="_blank">ov7670 cheet sheat</a>
* <a href="https://github.com/dinuxbg/pru-gcc-examples/tree/master/ov7670-cam" target="_blank">PRU-GCC, ov7670-cam (Debian image)</a>


### LED
* <a href="https://robotic-controls.com/learn/beaglebone/beaglebone-black-built-leds" target="_blank"> build-in leds with file</a>