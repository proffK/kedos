#include "sys/kscheduler.h"

void kscheduler() {
	cur_thread->state = WAIT;
	cur_thread = active_next (cur_thread);
	if (!active_is_last (th_active_head, cur_thread))
		cur_thread = active_next (cur_thread);
	cur_thread->state = ACTIVE;
}
