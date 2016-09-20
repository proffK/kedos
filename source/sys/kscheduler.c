#include "sys/kscheduler.h"

void kscheduler() {
	if (cur_thread->state == ACTIVE)
		cur_thread->state = WAIT;
	if (cur_thread->state == BLOCKED) {
		kthread* tmp = active_next (cur_thread);	
		unpin_node (&cur_thread->active);
		cur_thread = tmp;
	}
	else
		cur_thread = active_next (cur_thread);

	if (!active_is_last (th_active_head, cur_thread))
		cur_thread = active_next (cur_thread);

	cur_thread->state = ACTIVE;
}
