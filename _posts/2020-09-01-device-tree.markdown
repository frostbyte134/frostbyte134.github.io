---
layout: post
title:  "Device tree"
date:   2020-09-01 09:00:05 +0800
categories: coding
use_math: true
tags: os need_review coding
---

### References
- <a href="https://jung-max.github.io/2019/10/22/Device_Tree_%EB%AC%B8%EB%B2%95/" target="_blank">"https://jung-max.github.io/2019/10/22/Device_Tree_%EB%AC%B8%EB%B2%95/</a> : 디바이스트리는 대부분 이 페이지의 내용을 참조함
- <a href="https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html#SEC21" target="_blank">gnu linker page</a>


### TIRTOS remote firmwares memory setting

#### Device tree

example of dts file

```
&reserved_memory{
    #address-cells = <2>;
    #size-cells = <2>;

    vision_apps_memory_region: vision_apps-dma-memory@b8000000{
        compatible = "shared-dma-pool";
        reg = <0x00 0xb8000000 0x00 0x02000000>
        no-map;
    }

    vision_apps_shared_region: vision_apps-shared-memories@bc000000{
        compatible = "shared-dma-pool";
        reg = <0x00 0xbc000000 0x00 0x100000000>
    }

    vision_apps_shared_region_1: vision_apps-shared-memories_1@bc000000{
        compatible = "shared-dma-pool";
        reg = <0x00 0xcc000000 0x00 0x140000000>
    }
}
```
- .dtsi 파일은 SOC 레벨에서 정의한 인클루드 파일이고, .dts파일은 보드 레벨에서 정의한 스크립트 파일이다.
- reserved_memory : root 트리
  - `vision_apps-dma-memory@b8000000`
    - 모든 노드는 `name@unit-address` 형식의 이름을 가져야합니다.
    - name은 간단한 ASCII 문자열이며 최대 31 자까지 가능합니다. 일반적으로 노드는 노드의 종류에 따라 이름이 지정됩니다. 즉. 3com 이더넷 어댑터의 노드는 3com509가 아닌 ethernet 이름을 사용합니다.
    - 노드가 주소가있는 장치를 설명하는 경우 장치 주소가(unit-address) 포함됩니다. 일반적으로 장치 주소는 장치에 액세스하는 데 사용되는 기본 주소이며 노드의 reg 속성에 나열됩니다. 이 문서의 뒷부분에서 reg 속성을 다룰 것입니다
- `#address-cells = <2>;` : 64bit 주소 체계
- attributes : key-value 형식
  - `""` : 텍스트 문자열
    - `compatible` : 시스템명 (보통 `제조엄체,모델명` 형식) `compatible = "shared-dma-pool";`
      - > 운영 체제는 compatible 값을 사용하여 방법에 대한 결정을 내릴 것이므로 머신에서 실행하려면이 compatible에 올바른 데이터를 입력해야합니다. <a href="https://jung-max.github.io/2019/10/22/Device_Tree_%EB%AC%B8%EB%B2%95/" target="_blank">(링크)</a>
  - `<>` : 32비트 unsigned int (16진수 1개가 4bit이므로, 8개 자릿수의 hex = 32bit unsigned bit)
  - `[]` : binary data
- `reg`
  - `<addr size>`이며, 위에선 `#address-cells`에서 지정된 대로 2개의 셀이 1개의 addr/size를 지정하기 위해 필요함. 
  - 첫 번째는 `0xb8000000` 주소부터 크기 `0x02000000`의 공간을 점유 (앞 32bit은 전부 0)


#### Linker script
- Note that the TI seperated memory definition and section definition to different files
- <a href="https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html#SEC16" target="_blank">MEMORY LAYOUT</a>  
```
MEMORY{
  ...
  /* Memory for shared memory buffers in DDR [size 576.00 MB] */
  DDR_SHARED_MEM                   : ORIGIN = 0xBC0000000  ,  LENGTH = 0x10000000
  /* DDR for c7x_1 for local heap [size 448.00 MB] */
  C7X_SCRATCH_MEM          (RWIX)  : ORIGIN = 0xCC0000000  ,  LENGTH = 0x14000000
}
```
- <a href="https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_toc.html#TOC21" target="_blank">SECTION DEFINITION</a>  
```
-c
-heap 0x20000
-stack 0x20000

SECTIONS
{
  ...
  .bss   >   DDR_C7x_1
  .data  >   DDR-C7x_1
  ...
  .stack >   DDR-C7x_1   ALIGN(0x20000) /* MUST be 128KB aligned to handle nested interrupts */
  ...

  .bss:ddr_shared_mem   (NOLOAD) : {} > C7X_SCRATCH_MEM
  .bss:ddr_scratch_mem   (NOLOAD) : {} > C7X_SCRATCH_MEM
  ...
}
- `(NOLOAD)` : The `(NOLOAD)' directive will mark a section to not be loaded at run time. The linker will process the section normally, but will mark it so that a program loader will not load it into memory. For example, in the script sample below, the ROM section is addressed at memory location `0' and does not need to be loaded when the program is run. The contents of the ROM section will appear in the linker output file as usual.
- section definition
  ```
  SECTIONS {
  ...
  secname start BLOCK(align) (NOLOAD) : AT ( ldadr )
    { contents } >region :phdr =fill
  ...
  }
  ```
- asd

