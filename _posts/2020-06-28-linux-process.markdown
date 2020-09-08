---
layout: post
title:  "Linux process"
date:   2020-06-28 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

> 디버깅을 통해 배우는 리눅스 커널의 구조와 원리

파일 디스크립터를 프로세스끼리 바로 못나누는지는 몰랐네...

TODO
- current 매크로 추가

### task_struct 구조체
- = `Task descriptor`
- `TCB` in embedded OS
- 프로세스를 관리하는 자료구조이자 객체. 아키텍처 독립적인 부분을 저장
- 리눅스 커널은 프로세스를 중심으로 중요한 데이터를 저장하고 로딩
  - __프로세스 리소스 : 파일 디스크립터, 가상메모리, 시그널, ...(추가바람)__
  - `char comm[TASK_COMM_LEN];` : 프로세스 이름
  - `pid_t pid;` : PID
  - `pid_t tgid;` : 쓰레드 그룹 아이디
    - 해당 프로세스가 쓰레드 리더인 경우 : tgid == pid, 아닌 경우 tgid != pid
  - `volatile long state` : 프로세스 상태 저장
    - `TASK_RUNNING` : CPU 에서 실행 중이거나, 런큐에서 대기 중인 상태
    - `TASK_INTERRUPTABLE` : 웨이트 중이라 인터럽트 가능
    - `TASK_UNINTERRUPTIBLE` : IO연산 등 중이라, 인터럽트 불가능. 뮤텍스도 포함
  - `unsigned int flags` : 플래그 (KERNEL/include/linux/sched.h)
    - ```
      #define PF_IDLE			0x00000002	/* I am an IDLE thread */
      #define PF_EXITING		0x00000004	/* Getting shut down */
      #define PF_VCPU			0x00000010	/* I'm a virtual CPU */
      #define PF_WQ_WORKER		0x00000020	/* I'm a workqueue worker */
      #define PF_FORKNOEXEC		0x00000040	/* Forked but didn't exec */
      #define PF_MCE_PROCESS		0x00000080      /* Process policy on mce errors */
      #define PF_SUPERPRIV		0x00000100	/* Used super-user privileges */
      #define PF_DUMPCORE		0x00000200	/* Dumped core */
      #define PF_SIGNALED		0x00000400	/* Killed by a signal */
      #define PF_MEMALLOC		0x00000800	/* Allocating memory */
      #define PF_NPROC_EXCEEDED	0x00001000	/* set_user() noticed that RLIMIT_NPROC was exceeded */
      #define PF_USED_MATH		0x00002000	/* If unset the fpu must be initialized before use */
      #define PF_USED_ASYNC		0x00004000	/* Used async_schedule*(), used by module init */
      #define PF_NOFREEZE		0x00008000	/* This thread should not be frozen */
      #define PF_FROZEN		0x00010000	/* Frozen for system suspend */
      #define PF_KSWAPD		0x00020000	/* I am kswapd */
      #define PF_MEMALLOC_NOFS	0x00040000	/* All allocation requests will inherit GFP_NOFS */
      #define PF_MEMALLOC_NOIO	0x00080000	/* All allocation requests will inherit GFP_NOIO */
      #define PF_LESS_THROTTLE	0x00100000	/* Throttle me less: I clean memory */
      #define PF_KTHREAD		0x00200000	/* I am a kernel thread */
      #define PF_RANDOMIZE		0x00400000	/* Randomize virtual address space */
      #define PF_SWAPWRITE		0x00800000	/* Allowed to write to swap */
      #define PF_NO_SETAFFINITY	0x04000000	/* Userland is not allowed to meddle with cpus_allowed */
      #define PF_MCE_EARLY		0x08000000      /* Early kill for mce process policy */
      #define PF_MUTEX_TESTER		0x20000000	/* Thread belongs to the rt mutex tester */
      #define PF_FREEZER_SKIP		0x40000000	/* Freezer should not count it as freezable */
      #define PF_SUSPEND_TASK		0x80000000      /* This thread called freeze_processes() and should not be frozen */
      ```


### thread_info 구조체
- 아키텍처 의존적 (cpu context = reg)인 부분을 저장 (인터럽트 마스킹 등도 포함인듯)
- 쓰레드는 다른 스레드와 FD, 파일 및 시그널 정보에 대한 주소공간을 공유 - 컨텍스트 스위치 시간이 짧음
- 선점 스케쥴링 실행여부, 시그널 전달 여부, 인터럽트 컨텍스트 여부 등도 저장
- 스택이 아래에서 위로 자란다고 할때, 스택의 최상위에 저장됨. 보통 최하단이 높은 주소임.
- C코드에서는 함수 호출시 레지스터 푸시/팝을 볼 수 없음 - 알다시피 asm이 알아서 처리해줌. __운영체제에서 할 일이 아니라, 아키텍처 의존적인 컴파일러에서 할 일__

### PS 명령어
- 유저 프로세스 = init프로세스를 표현하는 자료구조인 init_task 전역변수의 tasks 필드에 모든 프로세스가 linked list로 등록됨 - 이를 순회하며 task_struct의 정보를 출력

### 프로세스 관계
- <a href="https://www.joinc.co.kr/w/Site/system_programing/process/Process_Relation" target="_blank">https://www.joinc.co.kr/w/Site/system_programing/process/Process_Relation</a>
- 세션 == 터미널 (`/dev/ttyX`)
  - 세션 1개는 최대 1개의 foreground process group을 가질 수 있음. foreground process group이외에서 터미널의 signal을 받으려고 하면 `SIGTTIN` 발생
  - N개 프로세스 그룹 \\(\in\\) 1개 세션
    - 세션 리더 - session id == pid.
    - 데몬은  
  - N개 프로세스 \\(\in\\) 1개 프로세스 그룹
    - 프로세스 그룹 리더 - pgid == pid
    - fg에 준 시그널이 bg에 가면 안됨 - 시그널/pipe등은 내부 프로세스 그룹끼리만 유효
- <a href="https://mug896.github.io/bash-shell/session_and_process-group.html" target="_blank">잘 쓴듯. 읽어볼 만 함</a>

### init process
- <a href="https://stackoverflow.com/questions/44274648/which-one-is-pid1-sbin-init-or-systemd" target="_blank">systemd vs /sbin/init</a>  
  > On my system, /sbin/init is a symlink to "/lib/systemd/systemd". This is likely similar to your system. We can see what information ps -aux is using by straceing it.


### 유저 모드 vs 커널 모드
- 유저공간에서 `getpid()` 함수 호출 - 이에 대응하는 syscall handler인 `sys_getpid()` 함수가 호출
- 유저모드는 커널에 시스템 콜로 요청을 날림
- 유저 모드에 해당하는 파일들 : 리눅스에서 링크하는 라이브러리들 (동적, 정적)

### fork
- 자식이 종료 시 부모에게 신호를 알림. 부모가 종료 시 조부모가 부모 프로세스가 되며, 대부분 `init` 프로세스가 조부모 역할을 수행
- __생성 시__ 자식은 부모의 `task_struct`를 `parent`포인터에, 부모는 자식을 `children` 연결리스트에 등록.  형제끼리는 `sibling`으로 연결되는 듯
- 유저공간에서 fork : `glibc`라이브러리의 도움을 받아 커널에게 프로세스 생성 요청
- 커널공간에서 fork : 시스템 콜 없이 (당연!) 커널 내부에서 자체적으로 `kthread_create()` 함수 호출
- 둘 다 `_do_fork()` (KERNEL/kernel/fork.c) 함수를 호출함. 이 함수는
  - `_copy_process()` (같은 파일) 함수를 호출해 프로세스 생성
    - `task_struct` 구조체 및 stack공간 할당 (kmalloc?)
    - 프로세스의 파일 디스크립터 초기화
      - 프로세스끼리 file descriptor 공유 : __fd가 정수인 이유는, 각 프로세스의 fd table의 인덱스이기 때문.__ 따라서 숫자만 공유하면 안되고, fork로 공유하든지 <a href="https://stackoverflow.com/questions/2358684/can-i-share-a-file-descriptor-to-another-process-on-linux-or-are-they-local-to-t" target="_blank">소켓 등으로 file descriptor 구조체를 공유해 줘야 한다고 함</a>
  - `wake_up_new_task()` (KERNEL/kernel/sched/core.c) 함수를 호출해 생성한 프로세스 깨움
    - 프로세스 상태를 TASK_RUNNING으로 변경
    - 현재 실행중인 CPU번호를 thread_info구조체에 기록
    - 런큐에 프로세스 큐잉
  - 생성한 PID를 반환

### 커널 쓰레드
- 커널이 직접 관리 = 시스템 콜 없음. 유저영역과 상호작용 X
  - 이 부분이 `데몬 쓰레드`와의 차이점임
- 부팅 과정에서 주로 생성
- 부팅 과정이 아닌 경우
  - ex 1. 리눅스 드라이버에서 많은 워크를 워크큐에 큐잉 -> 워커 쓰레드 (커널쓰레드) 생성
  - ex 2. 메모리 부족 시 kswapd 쓰레드 생성
- `kthreadd` : 모든 커널 쓰레드의 부모 (보통 2번)
- 워커 쓰레드 (워크큐에 큐잉된 Work를 실행)
- soft irq, irq쓰레드 등 처리

### 프로세스 종료
- 유저 프로세스
  - 스스로 exit POSIX syscall을 호출해 소멸가능
  - 결국 시스템 콜 핸들러인 `sys_exit_group()` 함수가 호출됨

- `do_exit`
  - `init`프로세스가 종료중이라면 덤프라도 건지게 강제 커널 패닉 유발 (보통 부팅때 발생한다고 함)
  - 이미 프로세스 `do_exit`으로 종료중인지 체크 (`TASK_DEAD`)
  - 프로세스 리소스 (파일 디스크립터, 가상메모리, 시그널) 해제
  - 프로세스는 소멸과정에서 부모 프로세스에게 `SIGCHLD`시그널 전달
  - task_struct에 상태를 `TASK_DEAD`로 기록
  - `do_task_dead`함수를 호출해 스케쥴링 실행
    - 다음 실행되는 프로세스가 `task_struct`와 프로세스 스택 해제 (`do_exit`이 스택에서 실행되고 있었으므로, 자기가 해제 못함)



### 데몬 프로세스 만들기

<a href="https://www.joinc.co.kr/w/Site/system_programing/process/daemon" target="_blank">https://www.joinc.co.kr/w/Site/system_programing/process/daemon</a>

1. read <a href="https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux">https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux</a>, and theoritical background <a href="http://www.enderunix.org/docs/eng/daemon.php" target="_blank">http://www.enderunix.org/docs/eng/daemon.php</a>
2. clone <a href="https://github.com/pasce/daemon-skeleton-linux-c" target="_blank">https://github.com/pasce/daemon-skeleton-linux-c</a>
3. steps
  1. `fork` off the parent process & let it terminate if forking was successful. -> Because the parent process has terminated, the child process now __runs in the background.__   
  2. `setsid` - Create a new session. The calling process becomes the leader of the new session and the process group leader of the new process group. The process is now detached from its controlling terminal (CTTY).
    - `session`과 `process group` : <a href="https://mug896.github.io/bash-shell/session_and_process-group.html" target="_blank">https://mug896.github.io/bash-shell/session_and_process-group.html</a>
  3. `Catch signals` - Ignore and/or handle signals.
  4. `fork again` & let the parent process terminate to ensure that you get rid of the session leading process. __(Only session leaders may get a TTY again.)__
  5. `chdir` - Change the working directory of the daemon.
  6. `umask` - Change the file mode mask according to the needs of the daemon.
  7. (optional?) redirect stdin, stdout, stderr since we dont have connected terminal anymore
  8. `close` - Close all open file descriptors that may be inherited from the parent process.
4. `ps -ejH` : 생성된 데몬 프로세스 (파일명)는 session leader도 아니고 (내 실험의 경우, `pid=5635`, `sid=5634`였음), 연결된 터미널도 없는 것을 확인할 수 있음.
5. 언제 부모가 systemd가 되는가? - <a href="https://stackoverflow.com/questions/35705451/is-changing-parent-process-necessary-when-daemonize-a-process" target="_blank">stackoverflow</a>

### 좀비 프로세스
- <a href="https://iprize.tistory.com/647" target="_blank">https://iprize.tistory.com/647</a>  
  - > 프로세스가 리눅스에서 종료될 때 그 즉시 메모리에서 제거되지 않는다. Process Descriptor가 메모리에 남는다. (Process Descriptor는 매우 적은양의 메모리만 차지한다) 프로세스 상태는 EXIT_ZOMBIE가 되며 부모 프로세스에게 자식 프로세스가 SIGCHLD 신호로 종료되었음을 알린다. 그러면 부모 프로세스는 자식 프로세스의 종료 상태와 기타 정보를 읽기 위해 wait() 시스템 콜을 실행하여야 한다. 부모 프로세스는 죽은 프로세스로부터 정보를 얻는 것이 허용되어 있다. wait()이 호출된 후 좀비 프로세스는 메모리에서 완전히 제거된다.   
  이러한 과정은 매우 빠르게 일어나기 때문에 시스템에 좀비 프로세스에 누적되는 것을 볼 수 없을 것이다. 하지만 부모 프로세스가 제대로 프로그래밍되지 않았다면 wait()을 호출하지 않을 것이며 좀비 프로세스는 메모리에 존재할 것이다. 
  - <a href="http://navigatorkernel.blogspot.com/2017/01/ch02-process-management3-process.html" target="_blank">process descriptor = task_struct</a>
- <a href="https://bencane.com/2012/07/02/when-zombies-invade-linux-what-are-zombie-processes-and-what-to-do-about-them/" target="_blank">https://bencane.com/2012/07/02/when-zombies-invade-linux-what-are-zombie-processes-and-what-to-do-about-them/</a>


### idle 쓰레드
- 스케쥴러 순서 : `stop_sched_class` -> `dl_sched_class` -> `rt_sched_class` -> `fair_sched_class` -> `idle_sched_class` -> NULL. 따라서 스케쥴러가 실행할 것이 없을 때 동작
- 모든 CPU는 1개의 idle 스레드를 지님