#include "sys/syscall.h"


int send (pid_t receiver, void* str, size_t size) {
	_disable_interrupts();
	data_message* data = (data_message*) kcalloc (1, sizeof (data_message));
	data->sender = cur_thread->pid;
	data->receiver = receiver;
	data->size = size;
	memcpy (str, data->data, size);
	int retv = -1;
	asm volatile (	"mov %%r0, %1\t\n"
			"push {%%r0}\t\n"
			"str %%sp, [%0]\t\n"
			::"r"(&cur_thread->stack_pointer),"r"(retv):"%r0", "memory");

	asm volatile (	"mov %%r1, %0\t\n"
			"swi #0x0\t\n"
			:: "r"(data):"%r1", "memory");

	asm volatile (	"pop {%%r0}\t\n"
			"mov %0, %%r0\t\n"
			:"=r"(retv)::"%r0", "memory");

	kfree (data);
	_enable_interrupts();	
	return retv;
}

int receive (void* str) {
	_disable_interrupts();
	int retv = -1;
	asm volatile (	"mov %%r0, %1\t\n"
			"push {%%r0}\t\n"
			"str %%sp, [%0]\t\n"
			::"r"(&cur_thread->stack_pointer),"r"(retv):"%r0", "memory");

	asm volatile (	"mov %%r1, %1\t\n"
			"mov %%r0, %0\t\n"
			"swi #0x1\t\n"
			:: "r"(cur_thread->pid), "r"(str): "%r0", "%r1", "memory");

	asm volatile (	"pop {%%r0}\t\n"
			"mov %0, %%r0\t\n"
			:"=r"(retv)::"%r0", "memory");
	_enable_interrupts();
	return retv;
}

int try_receive (void* str) {
	_disable_interrupts();
	int retv = -1;
	asm volatile (	"mov %%r0, %1\t\n"
			"push {%%r0}\t\n"
			"str %%sp, [%0]\t\n"
			::"r"(&cur_thread->stack_pointer),"r"(retv):"%r0", "memory");


	asm volatile (	"mov %%r1, %1\t\n"
			"mov %%r0, %0\t\n"
			"swi #0x2\t\n"
			:: "r"(cur_thread->pid), "r"(str): "%r0", "%r1", "memory");

	asm volatile (	"pop {%%r0}\t\n"
			"mov %0, %%r0\t\n"
			:"=r"(retv)::"%r0", "memory");
	_enable_interrupts();	
	return retv;
}


