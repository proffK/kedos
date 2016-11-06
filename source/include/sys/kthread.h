#ifndef KTHREAD_H
#define KTHREAD_H

#include "lib/nostdlib.h"
#include "mm/heap.h"
#include "sys/kscheduler.h"
#include "lib/dlink_list.h"
#include "sys/resources.h"

#define GET_KERNEL_THREAD() (node_head_prev(thread_head))

/****************************************************************************/

enum thread_state {
        ACTIVE,
        WAIT,
        BLOCKED
};

enum schedule_type {
        HARD,
        SOFT
};

/****************************************************************************/

extern reg_t kernel_sp;
extern pid_t cur_pid;

/****************************************************************************/

typedef struct kthread_t {
	dl_node node;
	dl_node active;
	enum schedule_type sched_type;
	enum thread_state state;
	rbuffer* buffer;
	reg_t program_counter;
	reg_t stack_base;        
	reg_t stack_pointer;	
	pid_t pid;
	sflag_t flags;
} kthread;

typedef struct data_message_t {
	char data[256];
	pid_t sender;
	pid_t receiver;
	size_t size;
} data_message;

/****************************************************************************/

define_list (node, kthread)
define_list (active, kthread)

/****************************************************************************/

extern kthread* cur_thread;
extern node_head* thread_head;
extern active_head* th_active_head;

/****************************************************************************/

extern void _kernel_entry (void);

void kthread_dump (kthread* thread);

int kthread_list_init ();

int kthread_list_delete();

pid_t add_kthread (sflag_t flags, void* func, enum schedule_type stype);

int delete_kthread (pid_t pid);

int kthread_list_dump ();

kthread* find_thread_pid (pid_t pid);

void run();

/****************************************************************************/

#define thread_exit() { \
	asm volatile (	"push {%%r1}\t\n"\
					"mov %%r1, %%sp\t\n"\
					"mov %%sp, %%fp\t\n"\
					"pop {%%lr}\t\n"\
					"str %%lr, [%0]\t\n"\
					"mov %%lr, %1\t\n"\
					"push {%%lr}\t\n"\
					"mov %%sp, %%r1\t\n"\
					"pop {%%r1}\t\n"\
			:: "r"(&(cur_thread->program_counter)), "r"(_kernel_entry) : "%sp", "%lr", "%r1", "memory");\
}

#define thread_entry(sp, lr) {\
	asm volatile (  "str %%sp, [%1]\t\n"\
					"mov %%sp, %0\t\n"\
					"pop {%%r0}\t\n"\
					"msr cpsr_xsf, %%r0\t\n" :: "r"(sp),\
					"r"(&GET_KERNEL_THREAD()->stack_pointer) : "%sp", "%r0");	\
\
	asm volatile(	"pop {%%r0-%%r11, %%lr}\t\n"\
					"cpsie i\t\n"\
					"mov %%pc, %0\t\n"\
					:: "r"(lr) : "%r0", "%r1", "%r2", "%r3", "%r4", "%r5", "%r6", \
					"%r7", "%r8", "%r9", "%r10", "%lr");\
}


static inline void thread_set_pc (reg_t func) {
	asm volatile (  "bx %0\t\n"
			::"r"(func));
}

#endif 
