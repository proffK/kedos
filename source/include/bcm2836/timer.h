#ifndef _TIMER_
#define _TIMER_

#include "defines.h"
#include <stdint.h>

#define SYS_TIMER_BASE (PBASE + 0x3000)

typedef uint32_t usec_t;

struct bcm2836_sys_timer {
    	volatile uint32_t control_status;
    	volatile uint32_t counter_lo;
    	volatile uint32_t counter_hi;
	volatile uint32_t compare0;
	volatile uint32_t compare1;
	volatile uint32_t compare2;
	volatile uint32_t compare3;
};

extern struct bcm2836_sys_timer* sys_timer;

void usleep(usec_t us);
void sys_timer_init();
struct bcm2836_sys_timer* get_sys_timer();

#define timeout_wait(cond, us) \
do {\
        volatile uint32_t ts = sys_timer->counter_lo;\
        do {\
                if ((cond) != 0) {\
                        kprint("Event %d\n", cond);\
                        break;\
                }\
        } while (sys_timer->counter_lo - ts < (uint32_t) (us));\
\
} while(0)

#endif

