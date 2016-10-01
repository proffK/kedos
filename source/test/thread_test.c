#include "test/test.h"
#include "bcm2836/gpio.h"
#include "bcm2836/mmio.h"

int p1 = 1;
int p2 = 1;

#define SEND_STR(param, size) {\
	memcpy (param, str, size);\
	send (1, str, size);\
}

uint32_t reg = 1 << 21;


void thread_1_func() {
	char* str = (char*) kcalloc (256, sizeof (char));\
	while(1) {
		if (p1 == 1) {
			p1 = 0;
			if (sys_timer->counter_lo % 10 > sys_timer->counter_lo % 5)
				SEND_STR ("Hello #1\r\n", strlen ("Hello #1\r\n") + 1);
		}
		p2 = 1;
	}
}

void thread_2_func() {
	char* str = (char*) kcalloc (256, sizeof (char));\
	while(1) {
		if (p2 == 1) {
			p2 = 0;
			if (sys_timer->counter_lo % 10 > sys_timer->counter_lo % 5)
				SEND_STR ("Hello #2\r\n", strlen ("Hello #2\r\n") + 1);
		}
		p1 = 1;
	}
}


void data_d (void* data) {
	data_message* d = (data_message *) data;
	kprint ("sender %d receiver %d msg %s\r\n", d->sender, d->receiver, d->data);
}


void terminal_func() {
	char* str = (char*) kcalloc (256, sizeof (char));
	int retv = -1;
	dump_rbuffer (cur_thread->buffer, data_d);
	while(1) {
		retv = try_receive (str);
		kprint ("%d ", retv);
		if (retv >= 0)
			kprint ("%s", str);
		
	}
}


void data_message_dump (void* data) {
	data_message* message = (data_message*) data;
	kprint ("%d %d %d %s\r\n", message->sender, message->receiver, message->size, message->data);
}

int thread_test() {

	node_head* tlist = kthread_list_init();
	add_kthread (0, &thread_1_func);
	add_kthread (0, &terminal_func);
	add_kthread (0, &thread_2_func);
	kthread_list_dump ();
	return 0;
}

