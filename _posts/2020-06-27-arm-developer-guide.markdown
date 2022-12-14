---
layout: post
title:  "ARM System Developer's Guide"
date:   2020-06-27 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

> Sloss, Andrew (2004-05-09T22:58:59). ARM System Developer's Guide (ISSN) . Elsevier Science. Kindle Edition. 


### Chap1

#### 1.1 The RISC design philosophy
The `RISC` philosophy concentrates on __reducing the complexity of instructions performed by the hardware__ because it is easier to provide greater flexibility and intelligence in software rather than hardware. As a result, a __RISC design places greater demands on the compiler.__ In contrast, the traditional complex instruction set computer (CISC) relies more on the hardware for instruction functionality, and consequently the CISC instructions are more complicated. 

<img src="{{ site.url }}/images/coding/arm/cisc_risc.jpg" width="600" class="center"/>  

The RISC philosophy is implemented with four major design rules:
1. The compiler or programmer synthesizes complicated operations (for example, a divide operation) by combining several simple instructions.  
2. `Pipelines` — The processing of instructions is broken down into smaller units that can be executed in parallel by pipelines.  
3. `Registers` — RISC machines have a large general-purpose register set. Any register can contain either data or an address. Registers act as the fast local memory store for all data processing operations. In contrast, CISC processors have dedicated registers for specific purposes.  
4. `Load-store architecture` — The processor operates on data held in registers. Separate load and store instructions transfer data between the register bank and external memory. Memory accesses are costly, so separating memory accesses from data processing provides an advantage because you can use data items held in the register bank multiple times without needing multiple memory accesses. In contrast, with a CISC design the data processing operations can act on memory directly.


#### 1.2 The ARM design philosophy

The ARM core is not a pure RISC architecture because of the constraints of its primary application—the embedded system. In some sense, the strength of the ARM core is that it does not take the RISC concept too far. In today’s systems the key is not raw processor speed but total effective system performance and power consumption.

1. Instruction Set for Embedded systems  
The ARM instruction set differs from the pure RISC definition in several ways
   * Variable cycle execution for certain instructions—Not every ARM instruction executes in a single cycle. For example, load-store-multiple instructions vary in the number of execution cycles depending upon the number of registers being transferred.
   *  `Inline barrel shifter` leading to more complex instructions—The inline barrel shifter is a hardware component that preprocesses one of the input registers before it is used by an instruction. (while transfered from register to cpu)
   * `Thunb 16-bit instruction set` - The 16-bit instructions improve code density by about 30% over 32-bit fixed-length instructions.
   * `Conditional execution` — An instruction is only executed when a specific condition has been satisfied. This feature improves performance and code density by reducing branch instructions.


#### 1.3 Embedded System Hardward
Each box represents a feature or function. The lines connecting the boxes are the buses carrying data.  
We can separate the device into four main hardware components: `ARM`, `controller` (Interrupt / Memory / ...), peripherals, bus

<img src="{{ site.url }}/images/coding/arm/soc.jpg" width="600" class="center"/>  

bus: AMBA. The ARM processor cor is a bus master, perihperals tend to be bus slaves


__memory__  
- Although the cache increases the general performance of the system, it does not help real-time system response.
- `DRAM` is dynamic — it needs to have its storage cells refreshed and given a new electronic charge every few milliseconds, so you need to set up a DRAM controller before using the memory. 
- Static random access memory (`SRAM`) is faster than the more traditional DRAM, but requires more silicon area. SRAM is static—the RAM does not require refreshing.
- Synchronous dynamic random access memory (`SDRAM`) is one of many subcategories of DRAM. It can run at much higher clock speeds than conventional
- All ARM peripherals are memory mapped — the programming interface is a set of memory-addressed registers. The address of these registers is an offset from a specific peripheral base address. Controllers are specialized peripherals that implement higher levels of functionality within an embedded system. Two important types of controllers are memory controllers and interrupt controllers.
- `memory controller` - Memory controllers connect different types of memory to the processor bus. On power-up a memory controller is configured in hardware to allow certain memory devices to be active. These memory devices allow the initialization code to be executed. Some memory devices must be set up by software; for example, when using DRAM, you first have to set up the memory timings and refresh rate before it can be accessed.
- `interrupt controller` (1.3.4.2) - When a peripheral or device requires attention, it raises an interrupt to the processor. An interrupt controller provides a programmable governing policy that allows software to determine which peripheral or device can interrupt the processor at any specific time by setting the appropriate bits in the interrupt controller registers. There are two types of interrupt controller available for the ARM processor: the standard interrupt controller and the vector interrupt controller (`VIC`).


#### 1.4 Embedded System Software
- `Booting` involves loading an image and handing control over to that image.
- Booting an image is the final phase, but first you must load the image. Loading an image involves anything from copying an entire program including code and data into RAM, to just copying a data area containing volatile variables into RAM. Once booted, the system hands over control by modifying the program counter to point into the start of the image.

__Example 1.1__  
- Initializing or organizing memory is an important part of the initialization code because many operating systems expect a known memory layout before they can start. 
- Figure 1.5 shows memory before and after reorganization. It is common for ARM-based embedded systems to provide for memory remapping because it allows the system to start the initialization code from ROM at power-up. The initialization code then redefines or remaps the memory map to place RAM at address 0x00000000—an important step because then the exception vector table can be in RAM and thus can be reprogrammed. We will discuss the vector table in more detail in Section 2.4.

<img src="{{ site.url }}/images/coding/arm/mem_remap.jpg" width="300" class="center"/>  

#### SUMMARY
- Pure RISC is aimed at high performance, but ARM uses a modified RISC design philosophy that also targets good code density and low power consumption. An embedded system consists of a processor core surrounded by caches, memory, and peripherals. The system is controlled by operating system software that manages application tasks. 
- The key points in a RISC design philosophy are to improve performance by reducing the complexity of instructions, to speed up instruction processing by using a pipeline, to provide a large register set to store data near the core, and to use a load-store architecture. 
 
The ARM design philosophy also incorporates some non-RISC ideas:
- It allows variable cycle execution on certain instructions to save power, area, and code size.  
- It adds a barrel shifter to expand the capability of certain instructions.  It uses the Thumb 16-bit instruction set to improve code density.  
- It improves code density and performance by conditionally executing instructions.  
- It includes enhanced instructions to perform digital signal processing type functions. 
 
An embedded system includes the following hardware components: `ARM processors` are found embedded in chips. Programmers access `peripherals` through memory-mapped registers. There is a special type of peripheral called a `controller`, which embedded systems use to configure higher-level functions such as memory and interrupts. The `AMBA` on-chip bus is used to connect the processor and peripherals together. 

An embedded system also includes the following software components: Initialization code configures the hardware to a known state. Once configured, operating systems can be loaded and executed. Operating systems provide a common programming environment for the use of hardware resources and infrastructure. Device drivers provide a standard interface to peripherals. An application performs the task-specific duties of an embedded system.


### Chapter 2

<img src="{{ site.url }}/images/coding/arm/arm_core_dataflow.jpg" width="300" class="center"/>  

* A programmer can think of an `ARM core` as __functional units connected by data buses,__ as shown in Figure 2.1,
* Figure 2.1 shows a `Von Neumann implementation` of the ARM—data items and instructions share the same bus. 
* The ARM processor, like all RISC processors, uses a `load-store architecture`.
  * load instructions copy data from memory to registers in the core
  * conversely the store instructions copy data from registers to memory. 
  * There are no data processing instructions that directly manipulate data in memory.
* The `sign extend hardware` converts signed 8-bit and 16-bit numbers to 32-bit values as they are read from memory and placed in a register.
* ARM instructions typically have two source registers, \\(Rn\\) and \\(Rm\\), and a single result or destination register, \\(Rd\\)
  * Source operands are read from the register file using the internal buses A and B, respectively.
  * The ALU (arithmetic logic unit) or MAC (multiply-accumulate unit) takes the register values \\(Rn\\) and \\(Rm\\) from the A and B buses and computes a result. 
  * Data processing instructions write the result in \\(Rd\\) directly to the register file. 
  * Load and store instructions use the `ALU` to generate an address to be held in the address register and broadcast on the Address bus.
* After passing through the functional units, the result in \\(Rd\\) is written back to the register file using the __Result bus__.
  * For load and store instructions the incrementer updates the address register before the core reads or writes the next register value from or to the next sequential memory location.

#### 2.1 Registers
> General-purpose registers hold either data or an address.



* r13 = `SP`, r14 = `LR`, r15 = `PC`
* Depending upon the context, registers r13 and r14 can also be used as general-purpose registers, which can be particularly useful since these registers are banked during a processor mode change.
* `banked` : replicated register exists on other modes
* In ARM state the registers r0 to r13 are __orthogonal__ — any instruction that you can apply to r0 you can equally well apply to any of the other registers. However, there are instructions that treat r14 and r15 in a special way.

#### 2.2 CPSR

<img src="{{ site.url }}/images/coding/arm/cpsr.jpg" width="400" class="center"/>  

<img src="{{ site.url }}/images/coding/arm/processor_modes.jpg" width="400" class="center"/>  

#### banked registers
* 20 registers are hidden from a program at different times. These registers are called `banked registers` and are identified by the shading in the diagram. They are available only when the processor is in a particular mode;
* All processor modes __except system mode__ have a set of associated banked registers that are a subset of the main 16 registers.
* `spsr` : stores the previous mode’s cpsr.
* Another important feature to note is that the cpsr is not copied into the spsr when a mode change is forced due to a program writing directly to the cpsr. The saving of the cpsr only occurs when an exception or interrupt is raised.
* When power is applied to the core, it starts in supervisor mode, which is privileged. Starting in a privileged mode is useful since initialization code can use full access to the cpsr to set up the stacks for each of the other modes.
* The state of the core determines which instruction set is being executed. There are three instruction sets: ARM, Thumb, and Jazelle.

#### Thumb mode
 - skipped

#### 2.2.5 Condition flags
* Condition flags are updated by comparisons and the result of ALU operations that specify the S instruction suffix. 
* For example, if a `SUBS` subtract instruction results in a register value of zero, then the Z flag in the cpsr is set. __This particular subtract instruction specifically updates the cpsr__
* With processor cores that include the __DSP extensions,__ the Q bit indicates if an overflow or saturation has occurred in an enhanced DSP instruction.

> In this book we use a notation that presents the cpsr data in a more human readable form. When a bit is a binary 1 we use a capital letter; when a bit is a binary 0, we use a lowercase letter. For the condition flags a capital letter shows that the flag has been set. For interrupts a capital letter shows that an interrupt is disabled.

<img src="{{ site.url }}/images/coding/arm/cpsr_conventions.jpg" width="400" class="center"/>  

`Conditional execution` controls whether or not the core will execute an instruction. 
* Most instructions have a condition attribute that determines if the core will execute it based on the setting of the condition flags. 
* __Prior to execution, the processor compares the condition attribute with the condition flags in the cpsr.__ 
* If they match, then the instruction is executed; otherwise the instruction is ignored.

<img src="{{ site.url }}/images/coding/arm/conditional_mnemonics.jpg" width="400" class="center"/>  

#### 2.3 pipeline
* `Fetch` loads an instruction from memory.  
* `Decode` identifies the instruction to be executed.  
* `Execute` processes the instruction and writes the result back to a register.
  * __The ARM pipeline has not processed an instruction until it passes completely through the execute stage.__ For example, an ARM7 pipeline (with three stages) has executed an instruction only when the fourth instruction is fetched. __(it takes effect (setting bits to 0 or 1, for example) when fourth instruction is fetched)__
* The ARM9 adds a `memory` and `writeback` stage, which gives the ARM9 an increase in instruction throughput by around 13% compared with an ARM7.
* the `PC` always points to the address of the instruction being executed plus two instructions ahead.

There are three other characteristics of the pipeline worth mentioning. 
* First, the execution of a branch instruction or branching by the direct modification of the pc causes the ARM core to __flush its pipeline.__ (!?) 
* Second, __ARM10 uses branch prediction,__ which reduces the effect of a pipeline flush by predicting possible branches and loading the new branch address prior to the execution of the instruction. 
* Third, an instruction in the execute stage will complete even though an interrupt has been raised. Other instructions in the pipeline will be abandoned, and the processor will start filling the pipeline from the appropriate entry in the vector table.

#### Exceptions, Interrupts, and the Vector Table
* When an exception or interrupt occurs, the processor sets the pc to a specific memory address. The address is within a special address range called the `vector table`. The entries in the vector table are instructions that branch to specific routines designed to handle a particular exception or interrupt.
* Each vector table entry contains a form of branch instruction pointing to the start of a specific routine:

(vector table, exception name / shorthand, addr, addr(high))
* `Reset vector` is the location of the first instruction executed by the processor when power is applied. This instruction branches to the initialization code.  
* `Undefined instruction` vector is used when the processor cannot decode an instruction.  
* `Software interrupt` vector is called when you execute a `SWI` instruction. The SWI instruction is frequently used as the mechanism to invoke an operating system routine.  
* `Prefetch abort` vector occurs when the processor attempts to fetch an instruction from an address without the correct access permissions. __The actual abort occurs in the decode stage.__
* `Data abort` vector is similar to a prefetch abort but is raised when an instruction attempts to access data memory without the correct access permissions.  
* `Interrupt request` vector is used by external hardware to interrupt the normal execution flow of the processor. __It can only be raised if IRQs are not masked in the cpsr.__   
* `Fast interrupt request` vector is similar to the interrupt request but is reserved for hardware requiring faster response times (many banked register). It can only be raised if FIQs are not masked in the cpsr. 


#### Cache and Tightly Coupled Memory
* A cache provides an overall increase in performance but at the expense of predictable execution. 
* But for real-time systems it is paramount that code execution is deterministic—the time taken for loading and storing instructions or data must be predictable. This is achieved using a form of memory called `tightly coupled memory (TCM)`. 
  * TCM is fast SRAM located close to the core and guarantees the clock cycles required to fetch instructions or data—critical for real-time algorithms requiring deterministic behavior. __TCMs appear as memory in the address map and can be accessed as fast memory.__


<img src="{{ site.url }}/images/coding/arm/havard_cache_tcm.jpg" width="400" class="center"/>  


#### Memory mgmt
* `Nonprotected memory` is fixed and provides very little flexibility. It is normally used for small, simple embedded systems that require no protection from rogue applications.
* `MMU`s are the most comprehensive memory management hardware available on the ARM.

Sloss, Andrew. ARM System Developer's Guide (ISSN) . Elsevier Science. Kindle Edition. 

#### Coprocessors
`Coprocessors` can be attached to the ARM processor. 
   * A coprocessor extends the processing features of a core by __extending the instruction set or by providing configuration registers.__ More than one coprocessor can be added to the ARM core via the coprocessor interface. The coprocessor can be accessed through a group of dedicated ARM instructions that provide a load-store type interface. 
   * Consider, for example, `coprocessor 15`: The ARM processor uses coprocessor 15 registers to __control the cache, TCMs, and memory management.__ 
   * The coprocessor can also __extend the instruction set__ by providing a specialized group of new instructions. For example, there are a set of specialized instructions that can be added to the standard ARM instruction set to process `vector floating-point (VFP)` operations. 
   * These new instructions are processed in the decode stage of the ARM pipeline. 
     * If the decode stage sees a coprocessor instruction, then it offers it to the relevant coprocessor. But if the coprocessor is not present or doesn’t recognize the instruction, then the ARM takes an undefined instruction exception, which allows you to emulate the behavior of the coprocessor in software.

#### Architecture revisions
> Every ARM processor implementation executes a specific `instruction set architecture (ISA)`, although an ISA revision may have more than one processor implementation.

refer to the book

#### Arm family
* The `ARM7` core has a __Von Neumann–style architecture__, where both data and instructions use the same bus. The core has a three-stage pipeline and executes the architecture ARMv4T instruction set.
   * `ARM7TDMI`
* The `ARM9` family was announced in 1997.
   * memory system has been redesigned to follow the Harvard architecture, which separates the data D and instruction I buses.
   * The first processor in the ARM9 family was the ARM920T, which includes a separate D + I cache and an MMU.

#### 2.8 SUMMARY 
> In this chapter we focused on the hardware fundamentals of the actual ARM processor. 

* The ARM processor can be abstracted into eight components — ALU, barrel shifter, MAC, register file, instruction decoder, address register, incrementer, and sign extend. 
* ARM has __three instruction sets__ — `ARM`, `Thumb`, and `Jazelle`. 
* The `register file` contains 37 registers, but only 17 or 18 registers are accessible at any point in time; the rest are banked according to processor mode. 
* The current processor mode is stored in the `cpsr`. It holds the current status of the processor core as well interrupt masks, condition flags, and state. The state determines which instruction set is being executed. 
* An ARM processor comprises a core plus the surrounding components that interface it with a bus. The __core extensions__ include the following:  
  * `Caches` are used to improve the overall system performance.  
  * `TCMs` are used to improve deterministic real-time response.  
  * `Memory management` is used to organize memory and protect system resources.  
  * `Coprocessors` are used to extend the instruction set and functionality. Coprocessor 15 controls the cache, TCMs, and memory management. 
* An ARM processor is an implementation of a specific `instruction set architecture (ISA)`. The ISA has been continuously improved from the first ARM processor design. Processors are grouped into implementation families (ARM7, ARM9, ARM10, and ARM11) with similar characteristics.



### Chapter 3 Intro to the ARM instruction SET
- read the book. Too many things to write on the blog

#### pre/post conditions  
<img src="{{ site.url }}/images/coding/arm/pre_post.jpg" width="400" class="center"/>  

- In the pre and post conds, __memory__ is denoted as  
  `mem<data_size>[address]`  
  ex) `mem32[1024]` : 32bit memory located at addr 1k.

__ARM instructions process data held in registers and only access memory with load and store instructions.__

| Instruction syntax | destination reg (Rd) | source reg 1 (Rn) | source reg 2 (Rm) |
|-------|--------|---------|---------|
| ADD r3, r1, r2 | r3 | r1 | r2 | 

__S suffix__
- If you use the __S suffix__ on a data processing instruction, then it updates the flags in the cpsr. Move and logical operations update the `carry flag C`, `negative flag N`, and `zero flag Z`. 
  - `The carry flag` is set from the result of the barrel shift as the last bit shifted out. 
  - `The N flag` is set to bit 31 of the result. 
  - `The Z flag` is set if the result is zero.

#### MOV, LDR
<img src="{{ site.url }}/images/coding/arm/mov.jpg" width="450" class="center"/>  

- mov vs ldr
  - <a href="https://www.raspberrypi.org/forums/viewtopic.php?t=16528" target="_blank">https://www.raspberrypi.org/forums/viewtopic.php?t=16528</a>
    - `ldr` is capable of loading any constant, but at the cost of speed and space.  If you open kernel.list, you'll see the ldr instruction actually get's converted to something like ldr rn,[pc,#x] and then later down the listing you'll see the constant. What the assembler has done is store the constant near the instruction in memory, and then write an instruction that loads this value from the memory.
    - `mov` is more restricted, but faster and smaller. If you look in kernel.list, you'll see the mov instruction is unchanged. It is just one instruction, and doesn't access memory. This means it will be faster, and takes less space. Unfortunately for us, mov can only load certain numbers; numbers who's binary representation is 8 1s or 0s, followed by any number of 0s, for example 1024 is valid (10000000000 in binary) but 1025 is not (10000000001 in binary).

#### Barrel shift operations

| Mnemonic | Desription | shift | Result | shift amount y |
|-------|--------|---------|---------|--------|
| LSL | logical shift left | x`LSL`y | x\<\<y | \#0~31 or Rs |
| LSR | logical shift right | x`LSR`y | x\>\>y | \#1~31 or Rs |
| ASR | arimethic right shift | x`ASL`y | (signed)x\>\>y | \#1~31 or Rs |
| ROR | rorate right | x`ROR`y | ((unsigned)x\>\>y) \| (x \<\< (32 - y)) | \#1~31 or Rs |
| RRX | rorate right extended | x`RRX`y | (c_flag \<\< 31) \| ((unsigned)x\>\>1) | none |


#### Misc
multiply instructions
- The long multiply instructions (`SMLAL`, `SMULL`, `UMLAL`, and `UMULL`) produce a 64-bit result. The result is too large to fit a single 32-bit register so the result is placed in two registers labeled RdLo and RdHi.
- The number of cycles taken to execute a multiply instruction depends on the processor implementation. For some implementations the cycle timing also depends on the value in Rs. For more details on cycle timings, see Appendix D.
- The __branch with link__, or `BL`, instruction is similar to the B instruction but overwrites the link register lr with a return address. It performs a `subroutine call`.  
  <img src="{{ site.url }}/images/coding/arm/branch.jpg" width="350" class="center"/>  
- `LDR` and `STR` instructions can load and store data on a boundary alignment that is the same as the datatype size being loaded or stored. For example, LDR can only load 32-bit words on a memory address that is a multiple of four bytes—0, 4, 8, and so on.
  - `preindex with writeback`   
  <img src="{{ site.url }}/images/coding/arm/preind1.jpg" width="350" class="center"/>   
  <img src="{{ site.url }}/images/coding/arm/preind2.jpg" width="350" class="center"/>  
  - `LDM` : load multiple regs, `STM` : save multiple regs
  - `IA` : increment after, `IB` : increment before
  - `DA` : decrement after, `DB` : decrement before
  - ex) `STMIA` - `LDMIA`
- The `BNE` is the branch instruction B with a condition mnemonic NE (not equal). If the previous compare instruction sets the condition flags of `CPSR` to not equal, the branch instruction is executed.


#### stack operations

| addressing mode | Desription | pop | =LDM | push | =STM |
|-------|--------|---------|---------|--------|----------|
| FA | full ascending | LDMFA | LDMDA | STMFA | STMIB |

> In the ATPCS, stacks are defined as being full descending stacks. Thus, the LDMFD and STMFD instructions provide the pop and push functions,

<img src="{{ site.url }}/images/coding/arm/stack_desc.jpg" width="450" class="center"/>  


When handling a checked stack there are three attributes that need to be preserved: the stack base, the stack pointer, and the stack limit. The stack base is the starting address of the stack in memory. The stack pointer initially points to the stack base; as data is pushed onto the stack, the stack pointer descends memory and continuously points to the top of stack. If the stack pointer passes the stack limit, then a stack overflow error has occurred. Here is a small piece of code that checks for stack overflow errors for a descending stack:


#### CPSR operation

#### LDR
As you can see, there are alternatives to accessing memory, but they depend upon the constant you are trying to load. Compilers and assemblers use clever techniques to avoid loading a constant from memory. These tools have algorithms to find the optimal number of instructions required to generate a constant in a register and make extensive use of the barrel shifter. If the tools cannot generate the constant by these methods, then it is loaded from memory. The LDR pseudoinstruction either inserts an MOV or MVN instruction to generate a value (if possible) or generates an LDR instruction with a pc-relative address to read the constant from a literal pool—a data area embedded within the code.

`pseudoinstruction`


| pseudo instruction | actual instruction | 
|-------|--------|
| LDR r0, =0xff | MOV r0, \#0xff |
| LDR r0, =0x55555555 | LDR r0, \[PC, \#offset_12\] |


#### Conditional execution
Most ARM instructions are conditionally executed—you can specify that the instruction only executes if the condition code flags pass a given condition or test. By using conditional execution instructions you can increase performance and code density. 

__The condition field is a two-letter mnemonic appended to the instruction mnemonic.__ The default mnemonic is `AL`, or __always execute.__ Conditional execution reduces the number of branches, which also reduces the number of pipeline flushes and thus improves the performance of the executed code. Conditional execution depends upon two components: the condition field and condition flags. The condition field is located in the instruction, and the condition flags are located in the cpsr.


#### Summary
In this chapter we covered the ARM instruction set. All ARM instructions are 32 bits in length. The arithmetic, logical, comparisons, and move instructions can all use the inline barrel shifter, which pre-processes the second register Rm before it enters into the ALU. 

The ARM instruction set has three types of load-store instructions: single-register load-store, multiple-register load-store, and swap. The multiple load-store instructions provide the push-pop operations on the stack. The ARM-Thumb Procedure Call Standard (ATPCS) defines the stack as being a full descending stack. 

The software interrupt instruction causes a software interrupt that forces the processor into SVC mode; this instruction invokes privileged operating system routines. The program status register instructions write and read to the cpsr and spsr. There are also special pseudoinstructions that optimize the loading of 32-bit constants.
