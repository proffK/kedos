#include "sys/syscall.h"

void syscall_write (void* param) {
	data_message* data = (data_message*) param;
	kthread* receiver = find_thread_pid (data->receiver);
	write_data (receiver->buffer, data);
}	

void syscall_read (dword param1, void* param2) {
	data_message* data = NULL;
	kthread* receiver = find_thread_pid (param1);
	data = (data_message*) read_data (receiver->buffer); 
	if (data != NULL) 
		memcpy (data->data, param2, data->size);
}

void sc_th_write (pid sender, pid receiver, void* str) {
	data_message* data = (data_message*) kcalloc (1, sizeof (data_message));
	data->sender = sender;
	data->receiver = receiver;
	data->size = strlen (str) + 1;
	data->data = str;
	asm volatile (	"mov %%ip, #0\t\n"
			"mov %%r1, %0\t\n"
			"swi #0x0\t\n"
			:: "r"(data));
}

void sc_th_read (void* str) {
	asm volatile (	"mov %%r1, %%r0\t\n"
			"mov %%r0, %0\t\n"
			"mov %%ip, #1\t\n"
			"swi #0x1\t\n"
			:: "r"(cur_thread->pid));
	_get_cpsr();
	_get_cpsr();
	_get_cpsr();

}

