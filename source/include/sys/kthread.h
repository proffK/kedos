#ifndef KTHREAD_H
#define KTHREAD_H

#include "lib/nostdlib.h"
#include "mm/heap.h"
#include "sys/kscheduler.h"
#include "lib/dlink_list.h"

enum thread_state {ACTIVE, WAIT, BLOCKED};

extern reg_t kernel_sp;
extern pid_t cur_pid;

extern void _kernel_entry (void);


typedef struct kthread_t {
	dl_node node;
	dl_node active;
	rbuffer* buffer;
	reg_t* program_counter;
	reg_t* stack_base;        
	reg_t* stack_pointer;	
	pid_t pid;
	byte state;
	sflag_t flags;
} kthread;

define_list (node, kthread)
define_list (active, kthread)

extern kthread* cur_thread;
extern node_head* thread_head;
extern active_head* th_active_head;

typedef struct data_message_t {
	char data[256];
	pid_t sender;
	pid_t receiver;
	dword size;
} data_message;

kthread* kthread_init (sflag_t flags, pid_t pid, void* func);
int kthread_delete (kthread* thread);
void kthread_dump (kthread* thread);
node_head* kthread_list_init ();
int kthread_list_delete();
void add_kthread (sflag_t flags, void* func);
void delete_kthread (pid_t pid);
void kthread_list_dump ();
kthread* find_thread_pid (pid_t pid);
void run();

//static inline void thread_exit () {
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
			::"r"(&cur_thread->program_counter), "r"(_kernel_entry): "%sp", "%lr", "%r1", "memory");\
}

static inline void thread_entry (reg_t sp, reg_t lr) {
	asm volatile (  "mov %%sp, %0\t\n"
			"mov %%lr, %1\t\n"
			"pop {%%r0-%%r12}\t\n"
			"mov %%pc, %%lr\t\n"
			:: "r"(sp), "r"(lr): "%sp", "memory");
}

inline void thread_set_pc (reg_t* func) {
	asm volatile (  "bx %0\t\n"
			::"r"(func));
}

#endif 
