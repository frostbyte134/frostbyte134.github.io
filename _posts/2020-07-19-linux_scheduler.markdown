---
layout: post
title:  "Linux scheduler"
date:   2020-07-19 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

- 코드로 알아보는 ARM 리눅스 커널 2판
- <a href="http://jake.dothome.co.kr/scheduler/" target="_blank">http://jake.dothome.co.kr/scheduler/</a>


스케쥴러 순서 : `stop_sched_class` -> `dl_sched_class`(deadline) -> `rt_sched_class` -> `fair_sched_class` -> `idle_sched_class` -> NULL. 따라서 스케쥴러가 실행할 것이 없을 때 동작

### load weight
- 태스크의 중요도. 중요도가 높을수록 `CFS` 에서 시간을 많이 할당함
- __태스크가 분배받는 시간__ 은 `CFS` 런큐의 모든 task의 load weight 합에서 현재 태스크의 load_weight이 차지하는 비율로 결정됨
- `RT_priority` (커널에서만 설정가능)는 0~99, `normal_priority`는 100~139까지 (priority가 낮으면 좋은 것)
  - 이 중 `CFS`는 normal priority (100~139)를 88761~15 까지의 `load_weight`으로 매핑함. 

### virtual runtime
- 스케줄러의 선택 기준 (실행 시간은 아님)
- \\(\text\{virtual runtime\} = \text\{real_runtime\}\times\frac\{1024\}\{\text\{load_weight\}\}\\)
- virtual runtime이 작은 태스크를 선택
  - 실행이 적게 되었을수록, load weight가 높을 수록 우선순위를 가짐
  - `min vruntime`이 존재 (처음 생성된 process에게 약간의 disadvantage)
    - If a process sleeps, its vruntime will remain unchanged. Because the per-queue min_vruntime will increase in the meantime, the sleeper process will be placed more to the left after waking up because the key(mentioned above) got smaller. <a href="https://stackoverflow.com/questions/39725102/how-linux-process-scheduler-prevents-starvation-of-a-process" target="_blank">(link)</a>
  - 결국 시간이 지나면, load weight비율 만큼의 시간을 전부 할당받음
- `rbtree`에 저장한다고 함
- 스케줄러는 `spinlock`으로 동시성 보장한다고 함
- 

### 그룹 스케줄링
- 유저별로 공정한 스케줄링 보장
- 현재는 `cgroup`을 이용한다고 함. 어떻게 하는거지


### 태스크 런타임 체크
- 주기적으로 타이머 인터럽트 (`hrtick`, `periodic tick?`)가 실행되는데, 이걸로 현재 태스크의 런타임을 소진시키는 듯 함. 런타임은 정확히 뭐로 계산하지?