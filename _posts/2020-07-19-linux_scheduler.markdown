---
layout: post
title:  "Linux scheduling"
date:   2020-07-19 09:00:05 +0800
categories: coding
use_math: true
tags: coding C
---

- 코드로 알아보는 ARM 리눅스 커널 2판
- <a href="http://jake.dothome.co.kr/scheduler/" target="_blank">http://jake.dothome.co.kr/scheduler/</a>


리눅스 스케쥴링 : TASK_RUNNING (대기) 상태의 프로세스 중 1개를 선택하여 TASK_RUNNING (실행) 상태로 바꾸는 것
- 다른 상태 : TASK_INTERRUPTIBLE, TASK_UNINTERRUPTABLE, TASK_DEAD

- 스케쥴러 클래스 선택 순서 : `stop_sched_class` -> `dl_sched_class`(deadline) -> `rt_sched_class` -> `fair_sched_class` -> `idle_sched_class` -> NULL. 따라서 스케쥴러가 실행할 것이 없을 때 동작
  - 대부분 프로세스는 `CFS`스케줄러에서 동작
  - __선점되지 않고 지속적으로 처리해야 하는__ 프로세스만 RT클래스에 등록
- 각 스케쥴러는 대기목록의 프로세스 중 우선순위가 가장 높은 프로세스를 선택
- 프로세스 입장에서는, 자신을 TASK_RUNNING (대기) 상태로 만들고 __런큐__ 에 자신을 삽입


### TASK_RUNNING (대기)
- 런 큐에 삽입된 상태
- `wake_up_process()` : TASK_UNINTERRUPTIBLE -> TASK_RUNNING (대기)
- `wake_up_interruptible()`, `wake_up_new_task()`, `yield()`, `do_nanosleep()` 등도 TASK_RUNNING으로 진입
- 뮤택스 획득 / IO연산 종료 후에도 TASK_RUNNING (대기) 상태가 됨
- 프로세스를 처음 생성하거나 관련 정보를 업데이트 할 때도 TASK_RUNNING (대기) 상태가 됨

### TASK_RUNNING (실행)
- `schedule()` 함수로만 진입가능함

```c++
static void __sched notrace __schedule(bool preempt)
{
	struct task_struct *prev, *next;
	unsigned long *switch_count;
	struct rq_flags rf;
	struct rq *rq;
	int cpu;

	cpu = smp_processor_id(); //CPU아이디 저장
	rq = cpu_rq(cpu);  //현재 CPU의 런큐 포인터를 지역변수로 가져옴
	prev = rq->curr;

	schedule_debug(prev);

	if (sched_feat(HRTICK))
		hrtick_clear(rq);

	local_irq_disable();
	rcu_note_context_switch(preempt);

	/*
	 * Make sure that signal_pending_state()->signal_pending() below
	 * can't be reordered with __set_current_state(TASK_INTERRUPTIBLE)
	 * done by the caller to avoid the race with signal_wake_up().
	 */
	rq_lock(rq, &rf);
	smp_mb__after_spinlock();

	/* Promote REQ to ACT */
	rq->clock_update_flags <<= 1;
	update_rq_clock(rq);

	switch_count = &prev->nivcsw;
	if (!preempt && prev->state) {
		if (unlikely(signal_pending_state(prev->state, prev))) {
			prev->state = TASK_RUNNING;
		} else {
			deactivate_task(rq, prev, DEQUEUE_SLEEP | DEQUEUE_NOCLOCK);
			prev->on_rq = 0;

			if (prev->in_iowait) {
				atomic_inc(&rq->nr_iowait);
				delayacct_blkio_start();
			}

			/*
			 * If a worker went to sleep, notify and ask workqueue
			 * whether it wants to wake up a task to maintain
			 * concurrency.
			 */
			if (prev->flags & PF_WQ_WORKER) {
				struct task_struct *to_wakeup;

				to_wakeup = wq_worker_sleeping(prev);
				if (to_wakeup)
					try_to_wake_up_local(to_wakeup, &rf);
			}
		}
		switch_count = &prev->nvcsw;
	}

	next = pick_next_task(rq, prev, &rf);
	clear_tsk_need_resched(prev);
	clear_preempt_need_resched();

	if (likely(prev != next)) {   //TRUE = 컨텍스트 스위칭이 일어남
		rq->nr_switches++;
		rq->curr = next;
		/*
		 * The membarrier system call requires each architecture
		 * to have a full memory barrier after updating
		 * rq->curr, before returning to user-space. For TSO
		 * (e.g. x86), the architecture must provide its own
		 * barrier in switch_mm(). For weakly ordered machines
		 * for which spin_unlock() acts as a full memory
		 * barrier, finish_lock_switch() in common code takes
		 * care of this barrier. For weakly ordered machines for
		 * which spin_unlock() acts as a RELEASE barrier (only
		 * arm64 and PowerPC), arm64 has a full barrier in
		 * switch_to(), and PowerPC has
		 * smp_mb__after_unlock_lock() before
		 * finish_lock_switch().
		 */
		++*switch_count;

		trace_sched_switch(preempt, prev, next);

		/* Also unlocks the rq: */
		rq = context_switch(rq, prev, next, &rf);
	} else {
		rq->clock_update_flags &= ~(RQCF_ACT_SKIP|RQCF_REQ_SKIP);
		rq_unlock_irq(rq, &rf);
	}

	balance_callback(rq);
}
```



### TASK_INTERRUPTIBLE
- `wait_event_interruptible()`, `do_sightimedwait()`, `sys_pause()`, `do_nanosleep()` 등으로 진입

### TASK_UNINTERRUPTIBLE
- `io_wait_event()`, `mutex_lock()`, `msleep()`등으로 진입

### Run queue (런큐)

- `struct task_struct *curr, *idle, *stop;` : curr에 CPU를 점유하면서 실행 중인 프로세스를 저장
- `struct cfs_rq cfs`, `struct rt_rq rt`, `struct dl_rq dl` (RT/CFS/Deadline 서브 런큐들)
- 스핀락 사용 (어디에?)
- `nr_running` : 런큐에 삽입된 모든 프로세스 개수 (맞나?)
- `nr_uninterruptible` : 런큐의 태크스 중 TASK_UNINTERRUPTIBLE 개수
- `curr` : 현재 실행 중인 프로세스의 테스크 디스크립터 포인터
- `idle` : 아이들 프로세스의 태스크 디스크립터
- `struct list_head` : CFS런큐에 삽입된 모든 일반 프로세스의 연결 리스트
- KERNEL/kernel/sched/sched.h


```c++
struct rq {
	/* runqueue lock: */
	raw_spinlock_t lock;

	/*
	 * nr_running and cpu_load should be in the same cacheline because
	 * remote CPUs use both these fields when doing load calculation.
	 */
	unsigned int nr_running;
#ifdef CONFIG_NUMA_BALANCING
	unsigned int nr_numa_running;
	unsigned int nr_preferred_running;
#endif
	#define CPU_LOAD_IDX_MAX 5
	unsigned long cpu_load[CPU_LOAD_IDX_MAX];
#ifdef CONFIG_NO_HZ_COMMON
#ifdef CONFIG_SMP
	unsigned long last_load_update_tick;
#endif /* CONFIG_SMP */
	unsigned long nohz_flags;
#endif /* CONFIG_NO_HZ_COMMON */
#ifdef CONFIG_NO_HZ_FULL
	unsigned long last_sched_tick;
#endif
	/* capture load from *all* tasks on this cpu: */
	struct load_weight load;
	unsigned long nr_load_updates;
	u64 nr_switches;

	struct cfs_rq cfs;
	struct rt_rq rt;
	struct dl_rq dl;

#ifdef CONFIG_FAIR_GROUP_SCHED
	/* list of leaf cfs_rq on this cpu: */
	struct list_head leaf_cfs_rq_list;
	struct list_head *tmp_alone_branch;
#endif /* CONFIG_FAIR_GROUP_SCHED */

	/*
	 * This is part of a global counter where only the total sum
	 * over all CPUs matters. A task can increase this counter on
	 * one CPU and if it got migrated afterwards it may decrease
	 * it on another CPU. Always updated under the runqueue lock:
	 */
	unsigned long nr_uninterruptible;

	struct task_struct *curr, *idle, *stop;
	unsigned long next_balance;
	struct mm_struct *prev_mm;

	unsigned int clock_update_flags;
	u64 clock;
	u64 clock_task;

	atomic_t nr_iowait;

#ifdef CONFIG_SMP
	struct root_domain *rd;
	struct sched_domain *sd;

	unsigned long cpu_capacity;
	unsigned long cpu_capacity_orig;

	struct callback_head *balance_callback;

	unsigned char idle_balance;
	/* For active balancing */
	int active_balance;
	int push_cpu;
	struct cpu_stop_work active_balance_work;
	/* cpu of this runqueue: */
	int cpu;
	int online;

	struct list_head cfs_tasks;

	u64 rt_avg;
	u64 age_stamp;
	u64 idle_stamp;
	u64 avg_idle;

	/* This is used to determine avg_idle's max value */
	u64 max_idle_balance_cost;
#endif

#ifdef CONFIG_IRQ_TIME_ACCOUNTING
	u64 prev_irq_time;
#endif
#ifdef CONFIG_PARAVIRT
	u64 prev_steal_time;
#endif
#ifdef CONFIG_PARAVIRT_TIME_ACCOUNTING
	u64 prev_steal_time_rq;
#endif

	/* calc_load related fields */
	unsigned long calc_load_update;
	long calc_load_active;

#ifdef CONFIG_SCHED_HRTICK
#ifdef CONFIG_SMP
	int hrtick_csd_pending;
	call_single_data_t hrtick_csd;
#endif
	struct hrtimer hrtick_timer;
#endif

#ifdef CONFIG_SCHEDSTATS
	/* latency stats */
	struct sched_info rq_sched_info;
	unsigned long long rq_cpu_time;
	/* could above be rq->cfs_rq.exec_clock + rq->rt_rq.rt_runtime ? */

	/* sys_sched_yield() stats */
	unsigned int yld_count;

	/* schedule() stats */
	unsigned int sched_count;
	unsigned int sched_goidle;

	/* try_to_wake_up() stats */
	unsigned int ttwu_count;
	unsigned int ttwu_local;
#endif

#ifdef CONFIG_SMP
	struct llist_head wake_list;
#endif

#ifdef CONFIG_CPU_IDLE
	/* Must be inspected within a rcu lock section */
	struct cpuidle_state *idle_state;
#endif
};
```


#### CFS_RQ

```cpp

/* CFS-related fields in a runqueue */
struct cfs_rq {
	struct load_weight load;
	unsigned int nr_running, h_nr_running;

	u64 exec_clock;
	u64 min_vruntime;
#ifndef CONFIG_64BIT
	u64 min_vruntime_copy;
#endif

	struct rb_root_cached tasks_timeline;

	/*
	 * 'curr' points to currently running entity on this cfs_rq.
	 * It is set to NULL otherwise (i.e when none are currently running).
	 */
	struct sched_entity *curr, *next, *last, *skip;

#ifdef	CONFIG_SCHED_DEBUG
	unsigned int nr_spread_over;
#endif

#ifdef CONFIG_SMP
	/*
	 * CFS load tracking
	 */
	struct sched_avg avg;
	u64 runnable_load_sum;
	unsigned long runnable_load_avg;
#ifdef CONFIG_FAIR_GROUP_SCHED
	unsigned long tg_load_avg_contrib;
	unsigned long propagate_avg;
#endif
	atomic_long_t removed_load_avg, removed_util_avg;
#ifndef CONFIG_64BIT
	u64 load_last_update_time_copy;
#endif

#ifdef CONFIG_FAIR_GROUP_SCHED
	/*
	 *   h_load = weight * f(tg)
	 *
	 * Where f(tg) is the recursive weight fraction assigned to
	 * this group.
	 */
	unsigned long h_load;
	u64 last_h_load_update;
	struct sched_entity *h_load_next;
#endif /* CONFIG_FAIR_GROUP_SCHED */
#endif /* CONFIG_SMP */

#ifdef CONFIG_FAIR_GROUP_SCHED
	struct rq *rq;	/* cpu runqueue to which this cfs_rq is attached */

	/*
	 * leaf cfs_rqs are those that hold tasks (lowest schedulable entity in
	 * a hierarchy). Non-leaf lrqs hold other higher schedulable entities
	 * (like users, containers etc.)
	 *
	 * leaf_cfs_rq_list ties together list of leaf cfs_rq's in a cpu. This
	 * list is used during load balance.
	 */
	int on_list;
	struct list_head leaf_cfs_rq_list;
	struct task_group *tg;	/* group that "owns" this runqueue */

#ifdef CONFIG_CFS_BANDWIDTH
	int runtime_enabled;
	s64 runtime_remaining;

	u64 throttled_clock, throttled_clock_task;
	u64 throttled_clock_task_time;
	int throttled, throttle_count;
	struct list_head throttled_list;
#endif /* CONFIG_CFS_BANDWIDTH */
#endif /* CONFIG_FAIR_GROUP_SCHED */
};
```

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

### 그룹 스케줄링
- 유저별로 공정한 스케줄링 보장
- 현재는 `cgroup`을 이용한다고 함. 어떻게 하는거지


### 태스크 런타임 체크
- 주기적으로 타이머 인터럽트 (`hrtick`, `periodic tick?`)가 실행되는데, 이걸로 현재 태스크의 런타임을 소진시키는 듯 함. 런타임은 정확히 뭐로 계산하지?

### Preemptive scheduling
__Preemptive 되는 시점__
  - 인터럽트 핸들링 후
  - 시스템콜 핸들링 후



### Non-preemptive scheduling

프로세스가 __자발적으로__ TASK_UNINTERRUPTIBLE로 들어가는 것 (IO연산, 뮤텍스 대기 등)


### 스케줄러 코드
- KERNEL/kernel/sched/sched.h
- next필드 (deadline - rt - cfs)와 함수포인터들을 확인할 수 있음

```c++

struct sched_class {
	const struct sched_class *next;

	void (*enqueue_task) (struct rq *rq, struct task_struct *p, int flags);
	void (*dequeue_task) (struct rq *rq, struct task_struct *p, int flags);
	void (*yield_task) (struct rq *rq);
	bool (*yield_to_task) (struct rq *rq, struct task_struct *p, bool preempt);

	void (*check_preempt_curr) (struct rq *rq, struct task_struct *p, int flags);

	/*
	 * It is the responsibility of the pick_next_task() method that will
	 * return the next task to call put_prev_task() on the @prev task or
	 * something equivalent.
	 *
	 * May return RETRY_TASK when it finds a higher prio class has runnable
	 * tasks.
	 */
	struct task_struct * (*pick_next_task) (struct rq *rq,
						struct task_struct *prev,
						struct rq_flags *rf);
	void (*put_prev_task) (struct rq *rq, struct task_struct *p);

#ifdef CONFIG_SMP
	int  (*select_task_rq)(struct task_struct *p, int task_cpu, int sd_flag, int flags);
	void (*migrate_task_rq)(struct task_struct *p);

	void (*task_woken) (struct rq *this_rq, struct task_struct *task);

	void (*set_cpus_allowed)(struct task_struct *p,
				 const struct cpumask *newmask);

	void (*rq_online)(struct rq *rq);
	void (*rq_offline)(struct rq *rq);
#endif

	void (*set_curr_task) (struct rq *rq);
	void (*task_tick) (struct rq *rq, struct task_struct *p, int queued);
	void (*task_fork) (struct task_struct *p);
	void (*task_dead) (struct task_struct *p);

	/*
	 * The switched_from() call is allowed to drop rq->lock, therefore we
	 * cannot assume the switched_from/switched_to pair is serliazed by
	 * rq->lock. They are however serialized by p->pi_lock.
	 */
	void (*switched_from) (struct rq *this_rq, struct task_struct *task);
	void (*switched_to) (struct rq *this_rq, struct task_struct *task);
	void (*prio_changed) (struct rq *this_rq, struct task_struct *task,
			     int oldprio);

	unsigned int (*get_rr_interval) (struct rq *rq,
					 struct task_struct *task);

	void (*update_curr) (struct rq *rq);

#define TASK_SET_GROUP  0
#define TASK_MOVE_GROUP	1

#ifdef CONFIG_FAIR_GROUP_SCHED
	void (*task_change_group) (struct task_struct *p, int type);
#endif
};
```


예시 - rt class  
- KERNEL/sched/rt.c

```c++

const struct sched_class rt_sched_class = {
	.next			= &fair_sched_class,
	.enqueue_task		= enqueue_task_rt,
	.dequeue_task		= dequeue_task_rt,
	.yield_task		= yield_task_rt,

	.check_preempt_curr	= check_preempt_curr_rt,

	.pick_next_task		= pick_next_task_rt,
	.put_prev_task		= put_prev_task_rt,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_rt,

	.set_cpus_allowed       = set_cpus_allowed_common,
	.rq_online              = rq_online_rt,
	.rq_offline             = rq_offline_rt,
	.task_woken		= task_woken_rt,
	.switched_from		= switched_from_rt,
#endif

	.set_curr_task          = set_curr_task_rt,
	.task_tick		= task_tick_rt,

	.get_rr_interval	= get_rr_interval_rt,

	.prio_changed		= prio_changed_rt,
	.switched_to		= switched_to_rt,

	.update_curr		= update_curr_rt,
};
```

#### for_each_class 함수
- 스케줄러간의 우선순위가 녹아있는 함수
- KERNEL/kernel/sched/sched.h

```cpp
#define for_each_class(class) \
   for (class = sched_class_highest; class; class = class->next)
```

해당 구문이 실제로 실행되는 예시
- KERNEL/kernel/sched/core.c

```cpp
void check_preempt_curr(struct rq *rq, struct task_struct *p, int flags)
{
	const struct sched_class *class;

	if (p->sched_class == rq->curr->sched_class) {
		rq->curr->sched_class->check_preempt_curr(rq, p, flags);
	} else {
		for_each_class(class) {
			if (class == rq->curr->sched_class)
				break;
			if (class == p->sched_class) {
				resched_curr(rq);
				break;
			}
		}
	}

	/*
	 * A queue event has occurred, and we're going to schedule.  In
	 * this case, we can save a useless back to back clock update.
	 */
	if (task_on_rq_queued(rq->curr) && test_tsk_need_resched(rq->curr))
		rq_clock_skip_update(rq, true);
}
```


- 프로세스 생성 시, 부모의 스케줄러 클래스를 물려받음
- `태스크 디스크립터` 에서 확인가능
- 통계적으로 99%의 프로세스는 CFS스케줄러로, 1%정도는 RT스케줄러로.

