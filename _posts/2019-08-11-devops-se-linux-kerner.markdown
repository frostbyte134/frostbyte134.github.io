---
layout: post
title:  "Devops와 SE를 위한 리눅스 커널 이야기 복습노트"
date:   2019-08-10 09:10:05 +0800
categories: linux
use_math: true
tags: linux process os
---

### 시스템 구성 정보
1. `uname -a`: 커널 버전
2. `dmesg`: 커널 디버그 메시지
3. `dmidecode`
   * -t bios: 바이오스 버전, 펌웨어 버전
   * -t system: 장비 모델명
   * -t processor: cpu 정보 (`socket`: 물리 CPU갯수, `core count`: 컴퓨팅 코어 갯수, `thread cound`: 하이퍼스레딩으로 제공되는 최종 코어 갯수 (근데 하이퍼스레딩은 결국 파이프라이닝 빈칸을 잘 이용하는 거라서 2개처럼 잘 동작안할수도 있지 않나))  
   `cat /proc/cpuinfo`, `lscpu`로도  비슷한 내용 확인가능
   * -t memory 
4. 디스크
   * `df -h`: HW구성까지는 모름. Logical volume인 경우에 RAID이겠거니..
   * `smartctl -a /dev/sdx -d ???`: HW구성까지 확인가능 (-d: RAID컨트롤러의 드라이버에 따라 추가옵션으로 HW정보 제공. 제조사마다 추가옵션이 다른듯)
   * `lsmod`: 사용중인 RAID컨트롤러 드라이버  
5. 네트워크
   * `lspci`: 물리 NIC카드정보?
   * `ethtool`: 연결 상태  
        * `-g`: Ring buffer (네트워크 카드의 버퍼. 패킷도달시 Ring buffer에 저장후 커널에 통보)
        * `tcp-offload`: MTU (Maximum Transfer Unit)크기 이상 패킷의 분할을 CPU말고 카드에서 진행하게 해 줌. 대역폭 높을 시 이슈 발생 가능.
   
### top, 프로세스 정보
* `top`: load average, 사용자 수, 프로세스 수, CPU, MEM, SWAP사용량
* __PR + NI__: 낮을수록 프로세스 우선순위 (`Run queue`에서 나오는 순서) 높음. NI는 조절가능

#### 메모리 (Memory commit)
* `VIRT`: The total amout of vietual memory used by the task
* `RES`: A task's currently used share of available physical memory
* `SHR`: the amout of shared memory used by a task (공용 커널 라이브러리 등)

\\[\text\{RES\}\subseteq \text\{VIRT\}\\]
SHR은 일부분이 RES에 포함됨

`memory commit`: `demand paging`. lazy allocation of memory. `fork()`시 일단 복사하고 보는데, 이전 메모리를 아예 안 쓸 수도 있으므로...  
1. `sar`로 봤을 시, `%commit`란이 메모리 커밋 비율 (실제 할당 X)인 메모리.
2. 가상메모리를 실제 가용 메모리보다 크게 할당할 수 있음. `vm.overcommit_memory`로 제어 가능
   1. 0: page cache + swap + slab reclaimable
   2. 1: infinite overcommit: 일단 가상메모리는 주고 봄
   3. 2: 제한적

#### 프로세스 상태

* `D` (io대기. Uninterruptable sleep) + `R`이 __load로 잡힘__
* `S`: interruptable sleep (sleep() 등)
* 생성가능 최대 PID: kernel.pid_max (기본값: 65536  - 1~65536)  
  `sysctl -a | grep -i pid_max` (-i : 대소문자구분 X)


### Load Average, 시스템 부하
> from the `man proc`, `load average`: The first 3 fields in this file are load average figures giving the # of jobs in the run queue (state `R`, `nr_running`) or waiting for disk I/O (state `D`, `nr_interruptable`) average 1, 5, and 15 minutes

> 시스템에 있는 CPU 코어수에 따라 상대적으로 해석해야 함

ex) 코어가 많을 수록, 높은 load average가 문제가 안 될 확률이 높음

* `vmstat`에서, `R` 및 `D` 갯수를 확인가능 - 어디에서 부하가 올라가고 있는지 확인
* CPU기반의 부하 / IO기반의 부하는 상황에 따라 시스템에 주는 임팩트가 다름

### free 명령어, 메모리
free명령어의
* `cached`: 디스크 I/O용 캐시 (`page cache`)
* `buffers`: 파일시스템의 메타데이터용 cache

메모리를 (anon - 사용 영역), cache영역, 가용 영역으로 나눈다면
1. 초반에는 사용 / 가용 뿐
2. 점점 많은 메모리를 사용하며, 사용/cache/가용 3등분
3. 사용 / cache로
4. cache걸 떼다가 사용하기 시작

#### cat /proc/meminfo
1. swapcached: `swap area` (=HDD)로 빠졌다가 다시 돌아온 영역. 지우지 않았으므로, 다시 swap으로 내보낼 시 이 부분을 참조만 하면 됨
2. `Active` / `Inactive` : LRU에서, 최근에 참조된 / 참조되지 않은 영역
   1. Active -> Inactive로의 전환은 최대한 늦게 (메모리가 거의 꽉 찼을 때 - kswapd process)
3. `anon` / `file`: anon은 익명 (의 프로세스)의 메모리. file은 file cache (page cache)영역
4. `Dirty`: 커널은 block단위로 쓰기를 하는데, block만큼 모이지 않았을 시 보관하는 메모리
5. `Slab`: Kernel의 cache. Inode / dentry (파일구조계층)를 주로 저장  
    * __원래 메모리는 page (4kb)단위__ 이지만, 이 캐쉬는 그렇게 많이 필요하지 않으므로 page를 쪼개 사용 (애매하게 남은 경우 페이지 2개에 1개의 slab이 겹치는것도 가능)
    * `free`등에서는 used로 잡히기 때문에 (cache가 아님!), 누수 발생시 추적 어려움


### Swap, 메모리 증설의 포인트
`buddy system`
* page를 연속적인 단위로 관리 (4kb -> 1, 2, 4, 8, ...)\
* kernel은 버디 시스템을 통해 피로세스에 메모리를 할당

커널은
1. 유휴 메모리가 있을 경우  cache로 활용
2. 메모리가 모자라게 되면 cache먼저 내줌
3. 다음도 모자라면, inactive를 swap으로 보내고 해당 영역을 사용줌 (조절 가능)
   1. `vm.swappiness`: 얼마나 공격적으로 swap영역을 활용하나
   2. swap때문에 불필요한 disk I/O가 많이 생김. 계속 메모리가 모자란 상황이면 더 많이 생김
   3. `smem`으로 swap영역 상황 확인가능


### NUMA 메모리
* `UMA` (Uniform Memory Access): 공용 bus이용. 0번 소켓의 CPU가 메모리 접근시 1번CPU는 접근불가
* `NUMA`: Non uniform. 각 CPU는 각자의 Local memory를 갖고 (`local access`), 다른 CPU의 local memory접근시 (`remote access`)만 공용 bus활용. 이 연산이 최대한 적게 일어나야 성능이 향상됨
* `node`: cpu + corresponding local memory
* modes
    1. default: 현재 프로세스가 실행되는 노드 내에서 가능한 할당
    2. bind: 특정 프로세스를 특정 노드에 바인딩
    3. prefferec: 선호 노드 지정가능
    4. interleaved: round robin

### Dirty page
- `page cache`에서, write가 이루어질 시 메모리의 cache 내용이 hdd의 내용과는 다르게 되는데, 이를 체크하기 위한 것. 명시적 / 주기적 / 백그라운드 동기화 (`flush`, as one could guess) 가 이루어지며, 파라미터로 설정 가능.  
> 동기화가 너무 빠르면 flush kernel thread가 너무 자주 깨어나게 되며, 너무 느리면 동기화해야할 dirty page가 너무 많아짐. disk 쓰기 성능이 허락하는 정도 크기에서 dirty page 한도를 정하는 것이 가장 좋은듯?

### IO scheduler
- `cfo`: 공정성, `deadline`: 데드라인, `no-op`. ssd에서는 noop면 됨 (디스크 헤드를 고려한 섹터별 정렬을 하지 않고 병합만 함)


### TIME_WAIT, CLOSE_WAIT
* <a href="http://tech.kakao.com/2016/04/21/closewait-timewait/" target="_blank">http://tech.kakao.com/2016/04/21/closewait-timewait/</a>
* <a href="http://docs.likejazz.com/time-wait/" target="_blank">http://docs.likejazz.com/time-wait/</a>

결국...
* TIME_WAIT은 종료요청을 먼저 한 쪽에서 FIN을 보낸 뒤 상대에게서 ACK, FIN을 받고 일정 시간 기다려주는 시간 (유실된 패킷 등을 위해)이고, 
* CLOSE_WAIT은 종료요청을 받은 쪽에서 close()함수를 호출해 ACK(FIN에 대한)를 보낸 뒤, FIN을 보내기 전 상태. 근데 굳이 sleep같은걸 끼워넣지 않으면 이게 문제될 일이 많나?...잘모르것네


해결책
1. Client side: `tw_reuse`를 통한 TIME_WAIT상태 소켓 재사용 (TIME_WAIT의 안정화 효과를 못 보는 것이니 비추천), 코딩 잘 해서 connection less -> connection pool 로 연결 유지 
2. 서버
   - 서버는 대부분, (예를들면) get요청을 클라이언트로 받은 후 keepalive가 설정되 있지 않을 시, 시간지나고 서버측에서 자동으로 connection을 끊으며 `TIME_WAIT`이 발생
   - `keepalive`로 연결 살리기 (추천), `tw_recycle`로 빠른 회수 (RTO의 2배로. RTO는 ms단위이므로 빨리 없어짐) 



### Keepalive
- 3way handshake후, 주기적으로 생존확인패킷을 보내 연결 유지
- 좀비 소켓연결도 체크 후 응답없으면 파기 - 커널 레벨에서의 소켓 관리

### TCP 재전송
- ACK를 못받았을 시, 패킷을 계속 보내는 주기
- RTO (Retransmission timeout): 기본 RTT (Round Trip Time) 2배씩