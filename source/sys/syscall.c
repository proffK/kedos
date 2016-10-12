#include "sys/syscall.h"


int send (pid_t receiver, void* str, size_t size) {
	_disable_interrupts();
	data_message* data = (data_message*) kcalloc (1, sizeof (data_message));
	data->sender = cur_thread->pid;
	data->receiver = receiver;
	data->size = size;
	memcpy (str, data->data, size);
	int retv = -1;

	SYSCALL_PARAM (cur_thread->stack_pointer, 0, data, retv);

	asm volatile ("swi #0x00\t\n":::"memory");

	SYSCALL_END (retv);
	kfree (data);
	_enable_interrupts();	
	return retv;
}

int receive (void* str) {
	_disable_interrupts();
	int retv = -1;

	SYSCALL_PARAM (cur_thread->stack_pointer, cur_thread->pid, str, retv);

	asm volatile ("swi #0x01\t\n":::"memory");

	SYSCALL_END (retv);

	_enable_interrupts();
	return retv;
}

int try_receive (void* str) {
	_disable_interrupts();
	int retv = -1;

	SYSCALL_PARAM (cur_thread->stack_pointer, cur_thread->pid, str, retv);

	asm volatile ("swi #0x02\t\n":::"memory");

	SYSCALL_END (retv);

	_enable_interrupts();	
	return retv;
}


