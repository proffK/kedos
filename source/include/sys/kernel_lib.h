#ifndef KERNEL_LIB_H
#define KERNEL_LIB_H

#include "sys/kthread.h"
#include "lib/nostdlib.h"
#include "lib/string.h"

int k_send (void* param);
int k_receive (dword param1, void* param2);
int k_try_receive (dword param, void* param2);

#endif
