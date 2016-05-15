#include "sys/kscheduler.h"

void kscheduler() {
	cur_thread = cur_thread->next;
}
