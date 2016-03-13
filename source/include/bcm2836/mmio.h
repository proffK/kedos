#ifndef __MMIO__
#define __MMIO__
#include "defines.h"

extern void memory_flush();

extern void memory_barier();

static inline void mmio_write(aptr_t addr, reg_t data)
{
        memory_barier();
	*((volatile uint32_t*) addr) = data;
        memory_barier();
}
 
static inline reg_t mmio_read(aptr_t addr)
{
        memory_barier();
	return *(volatile reg_t*) addr;
        memory_barier();
}

static inline uint32_t mmio_dword_read(byte* addr)
{
        return (addr[0] | addr[1] << 8 | addr[2] << 16 | addr[3] << 24);
}

static inline void mmio_dword_write(byte* addr, reg_t data)
{
        addr[0] = data & 0xff;
        addr[1] = (data & 0xff00) >> 8;
        addr[2] = (data & 0xff0000) >> 16;
        addr[3] = (data & 0xff000000) >> 24;

        return;
}

static inline uint32_t byte_swap(uint32_t num)
{
        return (num & 0xff) << 24 | (num & 0xff00) << 8 |
               (num & 0xff0000) >> 8 | (num & 0xff000000) >> 24;
}
#endif
