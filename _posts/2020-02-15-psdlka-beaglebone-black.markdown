---
layout: post
title:  "Beaglebone black + PSDKLA / TI-RTOS (SYS/BIOS?)"
date:   2020-02-15 09:00:05 +0800
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
  * <a href="https://training.ti.com/sites/default/files/docs/Processor_SDK_RTOS_P1_Slides.pdf" target="_blank">rtos chap 1</a>
  * <a href="https://training.ti.com/sites/default/files/docs/Processor_SDK_RTOS_P2_Slides_0.pdf" target="_blank">rtos chap 2</a>



<img src="{{site.url}}/images/coding/ti-cores.png" width="900">

#### Cores Determine software
- `PRU`: not much memory (bare-metal, real-time)
- TI-RTOS work can be done on Linux.
-  TI-RTOS is better at IPC (Inter-Processor Communication) than bare metal.
- Bare metal could be done with either host. But Windows predominates.

DSP
- TI-RTOS (SYS/BIOS?)
1. if ARM uses `PSDKLA` - uses `OpenCL` to communicate with ARM core - RTOS on DSP has the libraries
2. if ARM uses `RTOS` - uses IPC to communicate with ARM cores

PRU, `ARM M4`
- uses `IPC` __(lighter than openCL)__ for the comm with ARM cores


### TI-RTOS
* <a href="http://software-dl.ti.com/processor-sdk-rtos/esd/docs/latest/rtos/index_faq.html#ti-rtos" target="_blank">http://software-dl.ti.com/processor-sdk-rtos/esd/docs/latest/rtos/index_faq.html#ti-rtos</a>
* https://processors.wiki.ti.com/index.php/SYS/BIOS_with_GCC_(CortexA) damn
* https://training.ti.com/getting-started-ti-rtos-chapter-0-workshop-intro-oob?context=1134422-1139902 `Workshop` - TODO
* https://processors.wiki.ti.com/index.php/SYS/BIOS_FAQs
* https://www.embeddedadvantage.com/ti-rtos#targets well
* https://processors.wiki.ti.com/index.php?title=Category:SYSBIOS wiki
* http://www.ti.com/lit/ug/spruex3u/spruex3u.pdf doc


#### Creating IMG of TI-RTOS
- https://e2e.ti.com/support/processors/f/791/t/587982
- for `BBB`, ~/pdk_am335x_1_0_16/packages/pdkAppImageCreate.sh does the job (img file)
    - pdkAppImageCreate.sh `PDK_PATH` `CG_TOOL_PATH` `APP_PATH` `APP_NAME` `SOC` `PROCESSOR` `SECUREMODE=yes/no`
    - looks like this file firstly reads `APP_NAME.out` from  `CG_TOOL_PATH`, and generates bin file.
    - `app` file and `MLO` file must be in some SDCard or MMC. What does the `MLO` file does?

#### Socket
run pdk_path / pdkProjectCreate.sh (source pdksetupenv.sh first) to generate example project. (set ccs_path in the sh file). It builds, but dident tested on board

### FAQ
- https://processors.wiki.ti.com/index.php/SYS/BIOS_FAQs
- build outside CCS

