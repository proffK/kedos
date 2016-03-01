#include <bcm2836/timer.h>
#include <lib/error.h>

struct bcm2836_sys_timer* sys_timer = (void*) SYS_TIMER_BASE;

void usleep(usec_t us)
{
        volatile uint32_t ts = sys_timer->counter_lo;

        while (sys_timer->counter_lo - ts < us) ;

        return;
}

int timeout_wait(int cond, usec_t us)
{
        volatile uint32_t ts = sys_timer->counter_lo;

        do {
                if (cond != 0) return 0;
        } while (sys_timer->counter_lo - ts < us);

        errno = ETIMEDOUT;
        return -1;
}
