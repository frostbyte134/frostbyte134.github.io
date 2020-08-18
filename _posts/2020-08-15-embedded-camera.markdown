---
layout: post
title:  "Embedded Camera"
date:   2020-07-24 09:00:05 +0800
categories: coding
use_math: true
tags: coding
---

- https://m.blog.naver.com/msnayana/80198879870

### Acronyms
- `WDR` : Wide dynamic range
- `CSI` : camera serial interface
  - 카메라 센서에서도 `CSI-2`, AP (ARM)에서도 CSI-2
- `VISS` : visionm imaging sub-system
- `ISP` : image signal processing
- `bpp` : bits per pixel
- `I2C` : inter-integrated circuit
- `MIPI` : Mobile Industry Processor Interface
    - MIPI CSI-2 is a sensor interface commonly used in embedded systems to connect an image sensor to an embedded board that controls it and processes the image data.
    - `D-PHY` : 주로 카메리/디스플레이의 physical layer
    - `M-PHY` : 주로 와이파이
    - 신호전송 : 주로 LVDS


### lane
- 각 채널 (카메라) 별로, 데이터 전송속도를 늘리기 위해 가져갈 수 있는 내부 채널
- <a href="https://www.nxp.com/docs/en/application-note/AN5305.pdf" target="_blank">https://www.nxp.com/docs/en/application-note/AN5305.pdf</a>
  - MIPI block has four __data lanes__
  - The number of lanes determines the bandwidth of the MIPI bus
  - The I2C bus is required to configure most of the camera sensors
  - > CSI-2 is a lane-scalable specification. The applications that require more bandwidth than what is provided by one data lane or those trying to avoid high clock rates can expand the data path to two, three, or four lanes and obtain approximately linear increases in the peak bus bandwidth. The data stream is distributed between the lanes. This __figure(4)__ shows an example of a 4-lane transmission


### virtual channel
- The purpose of the virtual channel identifier is to provide separate channels for different data flows that are interleaved in the data stream.