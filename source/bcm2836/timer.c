#include <bcm2836/timer.h>
#include <lib/error.h>

struct bcm2836_sys_timer* sys_timer = (void*) SYS_TIMER_BASE;


void usleep(usec_t us)
{
        volatile uint32_t ts = sys_timer->counter_lo;

        while (sys_timer->counter_lo - ts < us) ;

        return;
}

void sys_timer_init() 
{
        sys_timer->control_status = 0x20;
        sys_timer->compare1 = sys_timer->counter_lo + 1000000;
}

struct bcm2836_sys_timer* get_sys_timer()
{
        return sys_timer;
}
