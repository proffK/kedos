#ifndef SYSCALL_H
#define SYSCALL_H

#include "sys/kthread.h"
#include "lib/nostdlib.h"
#include "lib/string.h"

#define SYSCALL_PARAM(sp, param0, param1, retv) \
	asm volatile (	"mov %%r0, %3\t\n"\
					"push {%%r0}\t\n"\
					"str %%sp, [%2]\t\n"\
					"mov %%r0, %0\t\n"\
					"mov %%r1, %1\t\n"\
					::"r"(param0), "r"(param1), "r"(&sp), "r"(retv):"%r0", "%r1", "memory");


#define SYSCALL_END(retv) \
	asm volatile (	"pop {%%r0}\t\n"\
					"mov %0, %%r0\t\n"\
					:"=r"(retv)::"%r0", "memory");


int send (pid_t receiver, void* str, size_t size);
int receive (void* str);
int try_receive (void* str);

#endif

