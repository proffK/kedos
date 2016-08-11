#ifndef SYSCALL_H
#define SYSCALL_H

#include "sys/kthread.h"
#include "lib/nostdlib.h"
#include "lib/string.h"

int send (pid_t receiver, void* str, size_t size);
int receive (void* str);
int try_receive (void* str);

#endif

