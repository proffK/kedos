#ifndef KTHREAD_H
#define KTHREAD_H

#include "lib/nostdlib.h"
#include "mm/heap.h"
#include "sys/syscall.h"




inline void thread_exit (dword* reg) {
	asm volatile (	"push {%%r0-%%r7, %%r12, %%r14}\t\n"
			"add %%r8, %%sp, #40\t\n"
			"mov %%r9, %0\t\n"
			"ldmia %%r8, {%%r0-%%r7, %%r12, %%r14}\t\n"
			//"add %%lr, %%lr, #4\t\n"
			"stmia %%r9, {%%r0-%%r12}\t\n"
			"pop {%%r0-%%r7, %%r12, %%r14}\t\n"
			"add %%sp, %%sp, #40\t\n"
		      :: "r"(reg));
}



inline void thread_entry (dword* reg) {
	asm volatile (  "mov %%r0, %0\t\n"
			"add %%r0, %%r0, #4\t\n"
			//"add %%sp, %%sp, #40\t\n"
			"ldmia %%r0!, {%%r1-%%r13, %%pc}^\t\n"
			:: "r"(reg));
}




inline void thread_set_pc (dword* func) {
	asm volatile (  "bx %0\t\n"
			:: "r" (func));
}

typedef struct kthread_t {
	byte state;
	sflag_t flags;
	struct kthread_t* next;
	struct kthread_t* prev;
	rbuffer* buffer;
	dword* registers;
        dword* stack_base;	
	dword pid;
} kthread;

typedef struct kthread_list_t {
	kthread* head;
	kthread* tail;
	dword cur_pid;
        dword a;
} kthread_list;

typedef struct data_message_t {
	pid sender;
	pid receiver;
	dword size;
	void* data;
} data_message;

extern kthread_list* thread_list;
extern kthread* cur_thread;

kthread* kthread_init (sflag_t flags, dword pid, void* func);
int kthread_delete (kthread* thread);
void kthread_dump (kthread* thread);
kthread_list* kthread_list_init();
int kthread_list_delete();
kthread_list* add_kthread (sflag_t flags, void* func);
kthread_list* delete_kthread (dword pid);
void kthread_list_dump ();
kthread* find_thread_pid (dword pid);
void run();
void context_switch ();


#endif 
