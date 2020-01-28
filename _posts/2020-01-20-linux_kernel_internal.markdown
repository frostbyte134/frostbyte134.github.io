---
layout: post
title:  "리눅스 커널 내부구조 (1판)"
date:   2020-01-20 09:00:05 +0800
categories: coding
use_math: true
tags: os linux
---


### Chap 3
* 스택은 위에서 밑으로 (낮은 주소로), 힙은 아래서 위로. 힙 바로밑에는 고정크기의 data영역(전역변수), 텍스트 에어리어 (functions, literals?)
* vfork: Copy On Write (Demand paging?)
  
#### Process vs Thread
1. Linux에서는 동일한 `task_struct` 자료구조로 관리 - 프로세스든 쓰레드든 내부선 거의 동일하게 관리됨
2. 둘 다, 내부적으론 `do_fork()`함수를 사용하여 생성 - param이 다름
3. 수행 이미지를 공유하는가, 같은 쓰레드 그룹에 속해 있는가 등은 다름.
4. 모든 task_struct자료구조는 유일한 `pid`를 가짐 - `syscall(__NR_getid)`로 호출
5. 부모가 같은 쓰레드 밑 부모는 동일한 `TGID`를 가짐 (POSIX 표준) - `getpid()` (주의!)
6. 모든 task들 (bijection with `task_struct`)은 doubly linked list로 연결되어 있음. Init_task가 root. TASK_RUNNING상태는 run_list필드를 통해 따로 연결되어 있음.

#### 상태 전이와 실행 수준 변화
* ZOMBIE 태스크: 대부분의 자원 반환 (메모리 제외? GPU은 반환 안함). 자신이 종료된 이유, 자신이 사용한 자원의 통계 정보 등 보유. 추후 부모 task가 `wait()`등 호출 시, 유지하던 자완 반환 후 종료.
* 부모가 자식 ZOMBIE의 wait을 실행하기도 전에 종료 -> init_task의 자식이 됨. 
* `TASK_RUNNING`(running)의 상태는 2가지로 분류 - user lvl running & kernel lvl running (syscall or interrupt에 의해 천이)
* kernel program도 C프로그램이기 때문에 stack 필요 - 항상 공간이 할당되어 있음.
  * 결론적으로, task할당시 `task_struct`와 `kernel_stack` 2개가 할당됨
* `open()` syscall 호출 시,
    1. 해당 시스템 콜의 호출번호는 unistd.h에 있고, 인텔CPU기준 eax레지스터에 저장
    2. 3개 인자들은 ebx, ecx, edx에 저장 - 해당 레지스터들의 내용을 pt_regs구조체에 담아 커널 스택에 저장 후, 복귀시 재할당

#### 프로세스 스케쥴링
* 1 CPU = 1 Run Queue

1. 프로세스 처음 생성시, init_test가 해드인 doubly linked list 뒤에 붙음
2. TASK_RUNNING이 될 시, 특별한 일이 없으면 부모 task가 돌아가는 run queue로 먼저 삽입 (cache affinity

#### Deadline 스케쥴링
- 데드라인이 있는 테스크들 (1/30초마다 화면 표시 등)에 쓰임
- 우선순위, nice level다 필요없고 deadline을 Red Black Tree에 넣어 동작


#### 컨택스트 스위치
- program counter, stack pointer, 범용 레지스터 상태 등을 `struct thread_struct`구조체에 저장
- A태스크가 B태스크로 문맥교환이 될 시
    1. A태스크 수행중 -> 커널로 문맥교환  
    태스크 A의 커널스택에 레지스터 정보 저장
    2. 커널이 B태스크 선정  
    태스크 A의 `thread_struct`에 A 레지스터 저장  
    태스크 B의 `thread_struct`정보를 B의 커널 스택에 복원
    3. 커널 -> B태스크로 교환  
    태스크 B의 커널스택의 정보를 레지스토에 복원

#### kill -9 1234 시 무슨 일이 일어나나
* kill은 `TGID`를 공유하는 태스크들 (쓰레드 그룹)에게 전달됨 - 해당 task의 task_struct 구조체의 signal필드에 저장 후, 커널이 메시지 전파. 다른 task들에게 전할 필요 없는 경우, pending에 저장.
* 수신한 시그널의 처리는 태스크가 커널 수준에서 사용자 수준으로 전이할 때 이루어짐. ()

#### Proc 파일시스템
* https://www.joinc.co.kr/w/Site/system_programing/proc/ProcFsPrograming#WHY


L1, L2 cache - https://it.donga.com/215/
https://it.donga.com/files/2010/05/19/03.jpg


### Chap 4 메모리 관리
32bit - 프로세스당 2^32=4GB, 64bit=over 1TB?

#### 물리 메모리 관리 자료구조
1. `NUMA`: Non-Uniform Memory Access, `UMA`: Uniform Memory Access
2. `bank`: 메모리 접근속도가 같은 메모리 집합. `node` 구조체로 관리  
   \\(\rightarrow\) `NUMA`: multiple nodes (banks), connected via linked list
3. `page frame`: 물리메모리의 최소 단위. `page`구조체로 관리(부팅시 모든 page frame당 구조체 생성)  
   \\(\rightarrow\) `NUMA`: N nodes -> M zones -> K pages
4. `buddy allocator`: 페이지(4KB)들을 2^i 단위로 묶어 할당. 2^2에 속하는 2개의 2^1 들이 서로 buddy임. 해제할때 바로 합치지 않는 것이 `lazy buddy`
5. `slab allocator`: 4KB보다 작은 공간을 buddy로부터 받아옴.
6. 각 task를 `task_struct`구조체로 관리 -> `mm_struct`구조체 내부에, 공통의 속성을 갖는 페이지들끼리 `vm_area_struct`로 묶어 관리

#### 가상 메모리와 물리 메모리의 연결 및 변환
1. 프로그램(ELF) 실행 
2. ELF내의 텍스트 및 데이터 영역을 읽어 실제 메모리 할당 - 페이지 테이블 이용
   1. 이 단계에선 할당만 이루어졌으므로, 실제 적재는 안됨
3. 해당 메모리가 엑세스됨 - page fault - interrupt후 실제 메모리에 적재 (`demang paging`!)
4. 보통 페이지 테이블은 3~4단계의 해싱 (`MMU`라는 하드웨어 이용)
5. 연속적인 가상 메모리는 실제로 불연속적일 수 있음 - `vmalloc()`으로 이런식으로 할당가능