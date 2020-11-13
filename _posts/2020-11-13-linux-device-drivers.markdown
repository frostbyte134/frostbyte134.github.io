---
layout: post
title:  "Linux Device Drivers"
date:   2020-11-13 05:04:00 +0900
categories: coding
use_math: true
tags: coding python
---

> Linux Device Drivers. O'Reilly Media. Kindle Edition. 


### Chap 1

- Device drivers = `black boxes` that make a particular piece of hardware respond to a well-defined internal programming interface;
  - they hide details of how the device works. __User activities are performed by means of a set of standardized calls__ that are independent of the specific driver;
  - mapping those calls to device-specific operations that act on real hardware is then the role of the device driver.
- Most programming problems can indeed be split into two parts:
  - what capabilities are to be provided” (the `mechanism`) and 
  - how those capabilities can be used (the `policy`)
- If the two issues are addressed by different parts of the program, or even by different programs altogether, the software package is much easier to develop and to adapt to particular needs.
- write kernel code to access the hardware, but don’t force particular policies on the user, since different users have different needs. The driver should deal with making the hardware available, leaving all the issues about how to use the hardware to the applications.
- Each piece of code that can be added to the kernel at runtime is called a `module`
  - Each module is made up of `object code` (not linked into a complete executable) that can be dynamically linked to the running kernel by the `insmod` program and can be unlinked by the `rmmod` program.


#### class of devices
> This division of modules is not a rigid one; Good programmers, nonetheless, usually create a different module for each new functionality they implement, because decomposition is a key element of scalability and extendability.

__char devices__  
  - stream of bytes (like a file)
  - usually implements at least the `open`, `close`, `read`, and `write` system calls.
  - Char devices are accessed by means of filesystem nodes, such as /dev/tty1 and /dev/lp0.
    - difference between a char device / a regular file : you can always move back and forth in the regular file, whereas most char devices are just data channels, which you can only access sequentially.
    - There exist, nonetheless, char devices that look like data areas, and you can move back and forth in them; for instance, this usually applies to `frame grabbers` (!!), where the applications can access the whole acquired image using mmap or lseek.  

__block devices__  
  - Like char devices, block devices are accessed by filesystem nodes in the /dev directory. A block device is a device (e.g., a disk) that can host a filesystem.
  - In most Unix systems, a block device can only handle I/O operations that transfer one or more whole blocks, which are usually 512 bytes (or a larger power of two) bytes in length.
  - Linux, instead, allows the application to read and write a block device like a char device — it permits the transfer of any number of bytes at a time. As a result, block and char devices differ only in the way data is managed internally by the kernel, and thus in the kernel/driver software interface.
    - Block drivers have a completely different interface to the kernel than char drivers.  

__network interfaces__
  - Usually, an interface is a hardware device, but it might also be a pure software device, like the loopback interface.
  - A network driver knows nothing about individual connections; it only handles packets.
  - Not being a stream-oriented device, a network interface isn’t easily mapped to a node in the filesystem, as /dev/tty1 is. 
  - The Unix way to provide access to interfaces is still by assigning a unique name to them (such as `eth0`), but that name doesn’t have a corresponding entry in the filesystem. Communication between the kernel and a network device driver is completely different from that used with char and block drivers. Instead of read and write, the kernel calls functions related to packet transmission (vfs의 read, write란 이름은 공유하나 드라이버 레벨에선 완전히 다른 것을 말하는 듯)


MISCS
- Every `USB device` is driven by a USB module that works with the USB subsystem, but the device itself shows up in the system as a char device (a USB serial port, say), a block device (a USB memory card reader), or a network device (a USB Ethernet interface).
- A `filesystem` type determines how information is organized on a block device in order to represent a tree of directories and files. 
  - Such an entity is __not a device driver,__ in that there’s no explicit device associated with the way the information is laid down; 
  - the __filesystem type is instead a software driver,__ because it maps the low-level data structures to high-level data structures. 
    - It is the filesystem that determines how long a filename can be and what information about each file is stored in a directory entry. The filesystem module must implement the lowest level of the system calls that access directories and files, by mapping filenames and paths (as well as other information, such as access modes) to data structures stored in data blocks. Such an interface is completely independent of the actual data transfer to and from the disk (or other medium), which is accomplished by a block device driver.
- The filesystem module must implement the lowest level of the system calls that access directories and files, by mapping filenames and paths (as well as other information, such as access modes) to data structures stored in data blocks. Such an interface is completely independent of the actual data transfer to and from the disk (or other medium), which is accomplished by a block device driver.
- Linux is licensed under Version 2 of the GNU General Public License (GPL),


#### Overview of the book
- Chapter 2 introduces modularization, explaining the secrets of the art and showing the code for running modules. 
- Chapter 3 talks about char drivers and shows the complete code for a memory-based device driver that can be read and written for fun. Using memory as the hardware base for the device allows anyone to run the sample code without the need to acquire special hardware.
- Debugging techniques are vital tools for the programmer and are introduced in Chapter 4. 
- Equally important for those who would hack on contemporary kernels is the management of concurrency and race conditions. Chapter 5 concerns itself with the problems posed by concurrent access to resources and introduces the Linux mechanisms for controlling concurrency. 
- With debugging and concurrency management skills in place, we move to advanced features of char drivers, such as blocking operations, the use of select, and the important ioctl call; these topics are the subject of Chapter 6. 
- Before dealing with hardware management, we dissect a few more of the kernel’s software interfaces: Chapter 7 shows how time is managed in the kernel, and 
- Chapter 8 explains memory allocation. Next we focus on hardware. 
- Chapter 9 describes the management of I/O ports and memory buffers that live on the device; 
- after that comes interrupt handling, in Chapter 10. Unfortunately, not everyone is able to run the sample code for these chapters, because some hardware support is actually needed to test the software interface interrupts. We’ve tried our best to keep required hardware support to a minimum, but you still need some simple hardware, such as a standard parallel port, to work with the sample code for these chapters. 
- Chapter 11 covers the use of data types in the kernel and the writing of portable code. The second half of the book is dedicated to more advanced topics. 
- We start by getting deeper into the hardware and, in particular, the functioning of specific peripheral buses. 
- Chapter 12 covers the details of writing drivers for PCI devices, and 
- Chapter 13 examines the API for working with USB devices. With an understanding of peripheral buses in place, we can take a detailed look at the Linux device model, which is the abstraction layer used by the kernel to describe the hardware and software resources it is managing. 
- Chapter 14 is a bottom-up look at the device model infrastructure, starting with the kobject type and working up from there. It covers the integration of the device model with real hardware; it then uses that knowledge to cover topics like hot-pluggable devices and power management. 
- In Chapter 15, we take a diversion into Linux memory management. This chapter shows how to map kernel memory into user space (the mmap system call), map user memory into kernel space (with get_user_pages), and how to map either kind of memory into device space (to perform direct memory access [DMA] operations). Our understanding of memory will be useful for the following two chapters, which cover the other major driver classes. Chapter 16 introduces block drivers and shows how they are different from the char drivers we have worked with so far. Then Chapter 17 gets into the writing of network drivers. We finish up with a discussion of serial drivers and a bibliography.


### Chap2

`printk`
- The kernel needs its own printing function because it runs by itself, without the help of the C library. 
- The module can call printk because, after insmod has loaded it, the module is linked to the kernel and can access the kernel’s public symbols (functions and variables, as detailed in the next section).
- _lacks floating points support?_ (even up to now?)


#### Kernel Modules vs Apps
- while not all applications are event-driven, each and every kernel module is (ex - `module_init` and `module_exit`)
- an application can call functions it doesn’t define: the `linking stage` resolves external references using the appropriate library of functions. printf is one of those callable functions and is defined in libc. 
- __A module, on the other hand, is linked only to the kernel,__ and the only functions it can call are the ones exported by the kernel; there are no libraries to link to.
  - Because no library is linked to modules, source files should never include the usual header files, `<stdarg.h>` and very special situations being the only exceptions. 
  - Only functions that are actually part of the kernel itself may be used in kernel modules. Anything related to the kernel is declared in headers found in the kernel source tree you have set up and configured; most of the relevant headers live in `include/linux` and `include/asm`,

#### Kernel Space vs User Space
- _A module runs in kernel space, whereas applications run in user space._
  - 사용자에게 consistent한 hw view를 제공하기 위해서

Unix transfers execution from user space to kernel space whenever an application issues a system call or is suspended by a hardware interrupt. 
  - Kernel code executing a system call is working in the context of a process — it operates on behalf of the calling process and is able to access data in the process’s address space. 
  - Code that handles interrupts, on the other hand, is asynchronous with respect to processes and is not related to any particular process.


