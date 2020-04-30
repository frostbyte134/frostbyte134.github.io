---
layout: post
title:  "Beaglebone black (setting, GPIO, PRU, Camera)"
date:   2020-02-14 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

* <a href="https://cdn-shop.adafruit.com/datasheets/BBB_SRM.pdf" target="_blank">BBB Datasheet</a>
* <a href="http://blog.naver.com/PostList.nhn?blogId=75rudals" target="_blank"> BBB Korean blog </a>

<img src="{{site.url}}/images/embedded/bbb_ports.jpg" width="600">


### Installing linux
eMMC linux is not portable with vscode (glibc dependency).

<a href="https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone+Black" target="_blank">https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone+Black</a>

### UART
<img src="{{site.url}}/images/embedded/bbb_uart.jpg" width="600">

### GPIO


### PRU
* <a href="http://www.ti.com/lit/ug/spruij2/spruij2.pdf?ts=1588210569067" target="_blank">TI manual</a>
* <a href="https://catch22eu.github.io/website/beaglebone/beaglebone-pru-c/" target="_blank">blog?</a>

### Camera
* <a href="https://github.com/ArduCAM/BeagleboneBlack" target="_blank">Arducam (ov7670) library for BBB </a>
* <a href="https://github.com/Scorpiion/Beagleboard-xM-Linux-Kernel/blob/master/drivers/media/video/ov7670.c" target="_blank"> BBB ov7670 driver </a>
* <a href="http://embeddedprogrammer.blogspot.com/2012/07/hacking-ov7670-camera-module-sccb-cheat.html" target="_blank">ov7670 cheet sheat</a>
* <a href="https://github.com/dinuxbg/pru-gcc-examples/tree/master/ov7670-cam" target="_blank">PRU-GCC, ov7670-cam (Debian image)</a>