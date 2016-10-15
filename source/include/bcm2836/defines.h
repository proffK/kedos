#ifndef __BCM2836_DEFS__
#define __BCM2836_DEFS__
#include <stdint.h>

#define PBASE 0x3F000000

#define PAGE_SIZE                    0x00001000
#define HEAP_TABLE_ADDR     ((void*) 0x00200000)
#define HEAP_START          ((void*) 0x01000000)
#define HEAP_END            ((void*) 0x3EFFFFFF)
#define HEAP_SIZE           ((HEAP_START - HEAP_END) / PAGE_SIZE)

/****************************************************************************/
/******************************* Memory map *********************************/
/****************************************************************************/
//0x00000000 - 0x00000020 : Interrupt handlers
//0x00000020 - 0x00008000 : Kernel stack
//0x00008000 - 0x00200000 : Kernel code
//0x00200000 - 0x00600000 : Memory area structs
//0x00600000 - 0x00800000 : Resources table
//0x00800000 - 0x01000000 : Unused
//0x01000000 - 0x3F000000 : Available memory
//0x3F000000 - 0x3FFFFFFF : Hardware mapping
/****************************************************************************/

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
typedef uint32_t pid_t;
typedef uint8_t sflag_t;

#endif
