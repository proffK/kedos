#ifndef SYSCALL_H
#define SYSCALL_H

#include "sys/kthread.h"
#include "lib/nostdlib.h"

void syscall_write (void* param);
void syscall_read (dword param1, void* param2);



void sc_th_read (void* str);
void sc_th_write (pid sender, pid receiver, void* str);

#endif

