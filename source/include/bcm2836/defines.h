#ifndef __BCM2836_DEFS__
#define __BCM2836_DEFS__
#include <stdint.h>

#define PBASE 0x3F000000

#define PAGE_SIZE 0x00001000
#define HEAP_START ((void*) 0x01000000)
#define HEAP_END ((void*) 0x3EFFFFFF)
#define HEAP_SIZE ((HEAP_START - HEAP_END) / PAGE_SIZE)

#define TIMER_RATE 1000000

#define ARCH_BITS 32
#define REGS_NUM  16

#define RING_BUFFER_SIZE 32

#define THREAD_PAGE_COUNT 1

#define RPI2

typedef uint32_t reg_t;
typedef uint32_t aptr_t;
typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint32_t pid;
typedef uint8_t sflag_t;

#endif
