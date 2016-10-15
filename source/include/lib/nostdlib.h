#ifndef __NOSTDLIB__
#define __NOSTDLIB__

#include <stddef.h>
#include <stdint.h>
#include "error.h"
#include "../bcm2836/defines.h"
#include "../bcm2836/flags.h"
#include "../lib/ringbuffer.h"
#include "../lib/string.h"

//#define DEBUG

#define FLAG_DUMP(param) (param) > 0 ? 1 : 0

void* kmalloc(size_t size);

void* kcalloc(int n, size_t size);

void* krealloc(void* block, size_t size);

int kfree(void* block);

int kmem_full_dump();

void kdie(char* err_msg);

int hex2str(uint32_t hex, char* str);

void dump_registers(reg_t* arr);

extern void _enable_interrupts (void);

extern void _disable_interrupts (void);

#endif
