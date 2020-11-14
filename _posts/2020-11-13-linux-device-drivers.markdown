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


__MISCS__
- Every `USB device` is driven by a USB module that works with the USB subsystem, but the device itself shows up in the system as a char device (a USB serial port, say), a block device (a USB memory card reader), or a network device (a USB Ethernet interface).
- A `filesystem` type determines how information is organized on a block device in order to represent a tree of directories and files. 
  - Such an entity is __not a device driver,__ in that there’s no explicit device associated with the way the information is laid down; 
  - the __filesystem type is instead a software driver,__ because it maps the low-level data structures to high-level data structures. 
    - It is the filesystem that determines how long a filename can be and what information about each file is stored in a directory entry. The filesystem module must implement the lowest level of the system calls that access directories and files, by mapping filenames and paths (as well as other information, such as access modes) to data structures stored in data blocks. Such an interface is completely independent of the actual data transfer to and from the disk (or other medium), which is accomplished by a block device driver.
- The filesystem module must implement the lowest level of the system calls that access directories and files, by mapping filenames and paths (as well as other information, such as access modes) to data structures stored in data blocks. Such an interface is completely independent of the actual data transfer to and from the disk (or other medium), which is accomplished by a block device driver.
- Linux is licensed under Version 2 of the GNU General Public License (GPL),


#### Overview of the book
- Chapter 2 introduces `modularization`, explaining the secrets of the art and showing the code for running modules. 
- Chapter 3 talks about `char drivers` and shows the complete code for a memory-based device driver that can be read and written for fun. Using memory as the hardware base for the device allows anyone to run the sample code without the need to acquire special hardware.
- `Debugging techniques` are vital tools for the programmer and are introduced in Chapter 4. 
- Equally important for those who would hack on contemporary kernels is the `management of concurrency and race conditions`. Chapter 5 concerns itself with the problems posed by concurrent access to resources and introduces the Linux mechanisms for controlling concurrency. 
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
  - `linux/module.h` contains a great many definitions of symbols and functions needed by loadable modules. 
  - You need `linux/init.h` to specify your initialization and cleanup functions,
  - Most modules also include `moduleparam.h` to enable the passing of parameters to the module at load time;


#### Kernel Space vs User Space
- _A module runs in kernel space, whereas applications run in user space._
  - 사용자에게 consistent한 hw view를 제공하기 위한 hierarchical 구조 (restricting)

Unix transfers execution from user space to kernel space whenever an application issues a system call or is suspended by a hardware interrupt. 
  - Kernel code executing a system call is working in the context of a process — it operates on behalf of the calling process and is able to access data in the process’s address space. 
  - Code that handles interrupts, on the other hand, is __asynchronous__ with respect to processes and is not related to any particular process.


#### Concurrency in Kernel
> even the simplest kernel modules must be written with the idea that many things can be happening at once.

Few sources of concurrency
- Linux multiprocessing
- interrupt
- several SW abstraction (ex - kernel timers, Chap7) run async as well
- `SMP` system (your driver can run on many CPU)
- preemptible

As a result, Linux kernel code, including driver code, must be `reentrant` — it must be capable of running in more than one context at the same time.
- Data structures must be carefully designed to keep multiple threads of execution separate, 
- and the code must take care to access shared data in ways that prevent corruption of the data. 
- Writing code that handles concurrency and avoids race conditions (situations in which an unfortunate order of execution causes undesirable behavior) requires thought and can be tricky.
- Chap 5 is dedicated for it
- In 2.6, kernel code can (almost) never assume that it can hold the processor over a given stretch of code.

#### Current process
- global item `current`, defined in `asm/current.h` : yields a pointer to struct `task_struct` (defined in `linux/sched.h`)
- The current pointer refers to the process that is currently executing
- During the execution of a system call, such as open or read, the current process is the one that invoked the call.
- Kernel code can use process-specific information by using current

> Actually, current is not truly a global variable. The need to support SMP systems forced the kernel developers to develop a mechanism that finds the current process on the relevant CPU. This mechanism must also be fast, since references to current happen frequently. The result is an architecture-dependent mechanism that, usually, hides a pointer to the task_struct structure on the kernel stack.

```
printk(KERN_INFO "The process is \"%s\" (pid %i)\n",
        current->comm, current->pid);
```
- a device driver can just include <linux/sched.h> and refer to the current process.

### Few other details
__stack__
- Applications are laid out in virtual memory with a very large stack area.
- The kernel, instead, has a very small stack; it can be as small as a single, 4096-byte page. Your functions must share that stack with the entire kernel-space call chain. Thus, it is never a good idea to declare large automatic variables; __if you need larger structures, you should allocate them dynamically at call time.__
- Often, as you look at the kernel API, you will encounter function names starting with a double underscore (_ _). Functions so marked are generally a low-level component of the interface and should be used with caution. Essentially, the double underscore says to the programmer: "If you call this function, be sure you know what you are doing."
- __Kernel code cannot do floating point arithmetic.__ Enabling floating point would require that the kernel save and restore the floating point processor’s state on each entry to, and exit from, kernel space — at least, on some architectures. Given that there really is no need for floating point in kernel code, the extra overhead is not worthwhile.


### Compiling and Loading
- The files found in the `Documentation/kbuild` directory in the kernel source are required reading for anybody wanting to understand all that is really going on beneath the surface.


__Makefile__
- for the “hello world” example shown earlier in this chapter, a single line will suffice: (kernel build system handles the rest)  
  ```
  obj-m := hello.o
  ```
- If, instead, you have a module called module.ko that is generated from two source files (called, say, file1.c and file2.c), the correct incantation would be: obj-m := module.o  
  ```
  module-objs := file1.o file2.o
  ```
- For a makefile like those shown above to work, it must be invoked within the context of the larger kernel build system. If your kernel source tree is located in, say, your `~/kernel-2.6` directory, the make command required to build your module would be:  
  ```
  make -C ~/kernel-2.6 M=`pwd` modules
  ```
- makefile idiom  
  ```
  # If KERNELRELEASE is defined, we've been invoked from the
  # kernel build system and can use its language.
  ifneq ($(KERNELRELEASE),)
      obj-m := hello.o 

  # Otherwise we were called directly from the command
  # line; invoke the kernel build system.
  else

      KERNELDIR ?= /lib/modules/$(shell uname -r)/build
      PWD  := $(shell pwd)

  default:
      $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

  endif

  Linux Device Drivers (p. 45). O'Reilly Media. Kindle Edition. 
  ```
- Once again, we are seeing the extended GNU make syntax in action. This makefile is read twice on a typical build. When the makefile is invoked from the command line, it notices that the KERNELRELEASE variable has not been set. It locates the kernel source directory by taking advantage of the fact that the symbolic link build in the installed modules directory points back at the kernel build tree.


#### insmod / rmmod
__insmod__
- `insmod` the module code and data into the kernel, which, in turn, __performs a function similar to that of ld,__ in that it links any unresolved symbol in the module to the __symbol table of the kernel.__
  - Unlike the linker, however, the kernel doesn’t modify the module’s disk file, but rather an in-memory copy. (linker + loader?)
  - __how the kernel supports insmod:__ it relies on a system call defined in kernel/module.c. The function sys_init_module allocates kernel memory to hold a module (this memory is allocated with vmalloc ; see the Section 8.4 in Chapter 2); it then copies the module text into that memory region, resolves kernel references in the module via the kernel symbol table, and calls the module’s initialization function to get everything going.
  - __names of the system calls are prefixed with sys_.__ This is true for all system calls and no other functions;

__modprobe__
- `modprobe`, like insmod, loads a module into the kernel. 
  - It differs in that it will look at the module to be loaded to see whether it references any symbols that are not currently defined in the kernel. 
  - If any such are found, modprobe looks for other modules in the current module search path that define the relevant symbols. When modprobe finds those modules (which are needed by the module being loaded), it loads them into the kernel as well. 
  - If you use `insmod` in this situation instead, the command fails with an `unresolved symbols` message left in the system logfile.


__rmmod__
- module removal fails if the kernel believes that the module is still in use (e.g., a program still has an open file for a device exported by the modules),
- It is possible to configure the kernel to allow “forced” removal of modules, even when they appear to be busy. If you reach a point where you are considering using this option, however, things are likely to have gone wrong badly enough that a reboot may well be the better course of action.

__lsmod__
- lists the modules loaded in the kernel
- works by reading the `/proc/modules` virtual file
  - the info (loaded modules) can also be found at `/sys/module`

#### versioning
`linux/module.h` defines the following macros:
- `UTS_RELEASE` : This macro expands to a string describing the version of this kernel tree. For example, "2.6.10“.
- `LINUX_VERSION_CODE` : This macro expands to the binary representation of the kernel version, one byte for each part of the version release number. For example, the code for 2.6.10 is 132618 (i.e., 0x02060a). With this information, you can (almost) easily determine what version of the kernel you are dealing with.
- `KERNEL_VERSION(major,minor,release)` : This is the macro used to build an integer version code from the individual numbers that build up a version number. For example, KERNEL_VERSION(2,6,10) expands to 132618.



#### Module init
```
static int _ _init initialization_function(void)
{
    /* Initialization code here */
    int err = register_this(ptr1, "thing");
    return err;
}
module_init(initialization_function);
```

- Initialization functions __should be declared static__, since they are not meant to be visible outside the specific file;
- `__init` token : compiler derictive. hint to the kernel that the func is only used at init time
- `__initdata` : similar (for data)
  - `__devinit`: translates to `__init` if kernel is not configured for hotpluggable devices (Chap 14)\
- `module_init` : macro. adds a section to the module's object code, stating where the init func can be found
- Modules can register many different types of `facilities`, including different kinds of devices, filesystems, cryptographic transforms, and more.
  - For each facility, there is a specific kernel function that accomplishes this registration. The arguments passed to the kernel registration functions are usually pointers to data structures describing the new facility and the name of the facility being registered. The data structure usually contains pointers to module functions, which is how functions in the module body get called.
- The return value of my_init_function, err, is an error code. In the Linux kernel, `error codes` are negative numbers belonging to the set defined in `linux/errno.h`.


#### Module cleanup
```
static void _ _exit cleanup_function(void)
{
    /* Cleanup code here */
}

module_exit(cleanup_function);
```

- The `__exit` modifier marks the code as being for module unload only (by causing the compiler to place it in a special ELF section).

#### Module-Loading Races
- It is possiblethat the kernel will make calls into your module while your initialization function is still running. Do not register any facility until all of your internal initialization needed to support that facility has been completed.
- You must also consider what happens if your initialization function decides to fail, but some part of the kernel is already making use of a facility your module has registered.


#### Module Parameters

- drivers for SCSI adapters often have __options__ controlling the use of tagged command queuing
- Integrated Device Electronics (IDE) drivers allow user control of DMA operations.
- such param values can be asigned at load time, by `insmod` or `modprobe`; 
  - the latter can also read parameter assignment from its configuration file (/etc/modprobe.conf ).
  - `insmod hellop howmany=10 whom="Mom"` (using insmod to pass params)  
  - in code, we need to use `module_param` macro must be used to make params available  
    ```
    static char *whom = "world";
    static int howmany = 1;
    module_param(howmany, int, S_IRUGO);
    module_param(whom, charp, S_IRUGO);
    ```

#### User space vs Kernel space
The advantages of user-space drivers are: 
- The full C library can be linked in. The driver can perform many exotic tasks without resorting to external programs (the utility programs implementing usage policies that are usually distributed along with the driver itself). 
- The programmer can run a conventional debugger on the driver code without having to go through contortions to debug a running kernel. If a user-space driver hangs, you can simply kill it. Problems with the driver are unlikely to hang the entire system, unless the hardware being controlled is really misbehaving. 
- User memory is swappable, unlike kernel memory. An infrequently used device with a huge driver won’t occupy RAM that other programs could be using, except when it is actually in use. 
- A well-designed driver program can still, like kernel-space drivers, allow concurrent access to a device. 


For example, 
- USB drivers can be written for user space; see the (still young) libusb project at libusb.sourceforge.net and “gadgetfs” in the kernel source. 
- Another example is the X server: it knows exactly what the hardware can do and what it can’t, and it offers the graphic resources to all X clients. Note, however, that there is a slow but steady drift toward frame-buffer-based graphics environments, where the X server acts only as a server based on a real kernel-space device driver for actual graphic manipulation.

Usually, the writer of a user-space driver implements a server process, taking over from the kernel the task of being the single agent in charge of hardware control. Client applications can then connect to the server to perform actual communication with the device; therefore, a smart driver process can allow concurrent access to the device. This is exactly how the X server works.

But the user-space approach to device driving has a number of drawbacks. The most important are: 
- Interrupts are not available in user space. There are workarounds for this limitation on some platforms, such as the vm86 system call on the IA32 architecture. 
- Direct access to memory is possible only by mmapping /dev/mem, and only a privileged user can do that. 
- Access to I/O ports is available only after calling ioperm or iopl. Moreover, not all platforms support these system calls, and access to /dev/port can be too slow to be effective. 
- Both the system calls and the device file are reserved to a privileged user. 
- Response time is slower, because a context switch is required to transfer information or actions between the client and the hardware. 
- Worse yet, if the driver has been swapped to disk, response time is unacceptably long. 
- Using the mlock system call might help, but usually you’ll need to lock many memory pages, because a user-space program depends on a lot of library code. mlock, too, is limited to privileged users. 
- The most important devices can’t be handled in user space, including, but not limited to, network interfaces and block devices.
