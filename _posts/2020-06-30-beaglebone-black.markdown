---
layout: post
title:  "Beaglebone black (setting, GPIO, PRU, Camera)"
date:   2020-06-30 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

Plans (7월까지 하기)
- elf파일 분석하는 절차 어디 적어놓기
  - /home/nailbrainz/ti/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-gcc -o main.out main.c --specs=nosys.specs
  - /home/nailbrainz/ti/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-objdump -d main.out > main_swap_objdump_d.txt
  - /home/nailbrainz/ti/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-objdump -x main.out > main_swap_objdump.txt
- NO OS booting (U-boot)
- ISR하나 추가해보기
- PRU사용
- Context switch 실제로 보기 (리눅스로 보는게 편할듯)
- 디버거는..돈이 없어서요


* <a href="https://cdn-shop.adafruit.com/datasheets/BBB_SRM.pdf" target="_blank">BBB Datasheet</a>
* <a href="https://github.com/derekmolloy/boneDeviceTree" target="_blank">BBB debice tree</a>
  * - has a header table at doc folder
* <a href="https://www.ti.com/lit/ug/spruh73q/spruh73q.pdf" target="_blank">AM337X Tech Ref Manual (memory map)</a>

* <a href="http://blog.naver.com/PostList.nhn?blogId=75rudals" target="_blank"> BBB Korean blog </a>

<img src="{{site.url}}/images/embedded/bbb_ports.png" width="600">


### Compiling & Installing embedded linux

#### 커널 컴파일 절차
```
export CC=`pwd`/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
cd bb-kernel/
./build_kernel.sh
export kernel_version=4.14.177-bone35 #find this version on the stdout
sudo cp -v ./bb-kernel/deploy/${kernel_version}.zImage /media/nailbrainz/rootfs/boot/vmlinuz-${kernel_version}
sudo tar xfv ./bb-kernel/deploy/${kernel_version}-modules.tar.gz -C /media/nailbrainz/rootfs/
sync
```


eMMC linux is not compatible with vscode ssh extension (glibc dependency).

<a href="https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone+Black" target="_blank">https://www.digikey.com/eewiki/display/linuxonarm/BeagleBone+Black</a>
* 써있는대로 하면 잘 됨. `bb-kernel`만 쓰는 거 같은데 다른 임베디드리눅스는 왜 받으라고 한거지
* 커널 컴파일 완료. `load_average()` 계산하는 함수에 printk 넣음. 5초마다 잘 찍히는 것 확인  
    <img src="{{site.url}}/images/embedded/prinkt.jpg" width="300">
    * dmesg 가 `/var/log/messages`가 아니고 `/var/log/syslog`로 메시지를 보내도록 바뀌였네..
    * `KERNEL/kernel/sched/loadavg.c/calc_load()`
    * `printk(KERN_CRIT "calc_load() - load : %lu\n", load);`
* device tree 함 봐야되는데..이번주내로 보자
* 이번 설치한 리눅스에 vscode원격접속 되면, eMMC의 리눅스도 이걸로 바꾸자

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

#### GPIO Interrputs
1. gpio sysfs는 /sys/class/gpio에 있음. export/unexport는 다른 번호를 알고 있어야 하는 듯. 지금은 안됨.
  * `direction`에 in/out, `value`에 값을 넣을 수 있음
2. dmesg에서 gpio ISR을 `printk`로 확인 가능
   1. gpio driver code
      ```c++
      #include <linux/init.h>
      #include <linux/module.h>
      #include <linux/fs.h>

      #include <linux/kernel.h>
      #include <linux/types.h>
      #include <linux/fcntl.h>
      #include <linux/gpio.h>
      #include <linux/irq.h>
      #include <linux/interrupt.h>

      MODULE_LICENSE("Dual BSD/GPL");



      #define MAJOR_NUMBER 240
      #define DEVICE_NAME "irq_dwkang_test"
      #define GPIO_DEBOUNCE_TIME 100
      #define GPIO_OUT_PIN 30
      #define GPIO_IN_PIN 60
      #define LED_CLEAR 0
      #define LED_SET 1

      int gpio_irq_num = 0;
      char toggle = 1;
      int led_open(struct inode *, struct file *);
      int led_release(struct inode *, struct file *);
      long led_unlocked_ioctl(struct file *, unsigned int, unsigned long);
      int led_init(void);
      int led_exit(void);

      int led_open(struct inode* inode_p, struct file* file_p){
          printk("[DWKANG] open() major = %d, minor = %d\n", MAJOR(inode_p->i_rdev), MINOR(inode_p->i_rdev));
          return 0;
      }

      int led_release(struct inode* inode_p, struct file* file_p){
          printk("[DWKANG] release");
          return 0;
      }

      long led_unlocked_iotcl(struct file* file_p, unsigned int command, unsigned long arg){
          switch(command){
              case 0:
              {
                  if(arg == 0){
                      gpio_set_value(GPIO_OUT_PIN, 0);
                  }else if(arg == 1){
                      gpio_set_value(GPIO_OUT_PIN, 1);
                  }
                  printk("[DWKANG] ioctl commane = %d, arg = %d\n", command, (int)arg);
              }
              break;
              default:
              printk("[dwkang] ioctl error\n");
              break;
          }
          return 0;
      }

      irqreturn_t irq_gpio(int irq, void *ident){
          printk("[DWKANG] interrupt by gpio 13\n");
          if(toggle){
              toggle = !toggle;
              gpio_set_value(GPIO_OUT_PIN, 1);
              printk("[dwkang] 1\n");
          }else{
              toggle = !toggle;
              gpio_set_value(GPIO_OUT_PIN, 0);
              printk("[dwkang] 0\n");
          }
          return IRQ_HANDLED;
      }

      struct file_operations led_file_oper = {
          .owner = THIS_MODULE,
          .open = led_open,
          .unlocked_ioctl = led_unlocked_iotcl,
          .release = led_release,
      };

      int led_init(void){
          if(gpio_request(GPIO_OUT_PIN, "DWKANG_OUT_INTERRPUT") != 0)
              printk("[DWKANG] gpio_request failed for out pin\n");
          
          if(gpio_request(GPIO_IN_PIN, "DWKANG_IN_INTERRPUT") != 0)
              printk("[DWKANG] gpio_request failed for in pin\n");

          if(gpio_export(GPIO_OUT_PIN, 1) < 0)
              printk("[DWKANG] gpio_export failed for out pin\n");
          
          if(gpio_export(GPIO_IN_PIN, 1) < 0)
              printk("[DWKANG] gpio_export failed for in pin\n");

          if(gpio_direction_output(GPIO_OUT_PIN, 1) != 0)
              printk("[DWKANG] gpio_direction_output failed for out pin\n");
          
          if(gpio_direction_input(GPIO_IN_PIN) != 0)
              printk("[DWKANG] gpio_direction_output failed for in pin\n");

          if(register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &led_file_oper) < 0){
              printk("[DWKANG] driver init failed\n");
              return -1;
          }    
          printk("1\n");
          gpio_set_debounce(GPIO_IN_PIN, GPIO_DEBOUNCE_TIME);
          printk("2\n");
          gpio_irq_num = gpio_to_irq(GPIO_IN_PIN);
          printk("3\n");
          int req_irq_rlt = request_irq(gpio_irq_num, irq_gpio, 0, "gpio_60", NULL);
          printk("4\n");
          if(req_irq_rlt < 0)
              printk("[DWKANG] request irq error with %d\n", req_irq_rlt);
          irq_set_irq_type(gpio_irq_num, IRQ_TYPE_EDGE_RISING);
          printk("[DWKANG] lef init success\n");
          return 0;
      }

      int led_exit(void){
          printk("[DWKANG] module is exiting\n");
          gpio_free(GPIO_OUT_PIN);
          gpio_free(GPIO_IN_PIN);
          printk("[DWKANG] freeing irq. why am i called?\n");
          free_irq(gpio_irq_num, NULL);
          unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
          return 0;
      }

      module_init(led_init);
      module_exit(led_exit);
      ```
   2. 이 파일을 리눅스 코드 있는 곳에 가서 컴파일해야 함. 거기 있는 make쓰는 듯. `Makefile` : 
      ```Makefile
      obj-m	:=	dwkang_gpio_driver.o
      KDIR	:= /lib/modules/$(shell uname -r)/build
      PWD		:=	$(shell pwd)	

      all:
        $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
        
      clean:
        rm -rf *.ko
        rm -rf *.mod.*
        rm -rf *.cmd
        rm -rf *.o
        rm -rf .tmp_versions
      ```
   3. `insmod ~.ko`, `rmmod ~`사용해서 커널 모듈 등록/제거 함. dmesg로 확인 가능
   4. `dmesg -C` 로 깔끔하게 보는 것도 가끔 좋은듯
   5. `register_chrdev` 는 왜 쓰는 거지? 지금 이해로는, ISR은 뭔가 장치파일로 동작하는 듯 (핸들러 등록하는 형식 보면 그런 거 같음)하며 이 장치파일을 등록할 때 필요한 듯

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