#include "test/test.h"
#include "bcm2836/gpio.h"
#include "bcm2836/mmio.h"

int p1 = 1;
int p2 = 1;

#define SEND_STR(param, size) {\
	memcpy (param, str, size);\
	send (2, str, size);\
}

uint32_t reg = 1 << 21;


void thread_1_func() {
	char* str = (char*) kcalloc (256, sizeof (char));\
	while(1) {
		if (p1 == 1) {
			p1 = 0;
			size_t size = strlen ("Hello#1\r\n") + 1;
			memcpy ("Hello#1\r\n", str, size);
			kprint ("%d\n", send (2, str, size));
		}
		p2 = 1;
//		mmio_write(GPSET1, reg);
	}
}

void thread_2_func() {
	char* str = (char*) kcalloc (256, sizeof (char));\
	while(1) {
		if (p2 == 1) {
			p2 = 0;
			SEND_STR ("Hello #2\r\n", strlen ("Hello #2\r\n") + 1);
		}
		p1 = 1;
//		mmio_write(GPCLR1, reg);
	}
}

void terminal_func() {
	char* str = (char*) kcalloc (256, sizeof (char));
	while(1) {
		int ret = try_receive (str);
		if (ret > 0)
			kprint ("%s\r\n", str);
	}
}

void bled_func() {
	while (1) {
		if (p2 == 0)
			mmio_write(GPSET1, reg);

		if (p1 == 0)
			mmio_write(GPCLR1, reg);
	}
}

void data_message_dump (void* data) {
	data_message* message = (data_message*) data;
	kprint ("%d %d %d %s\r\n", message->sender, message->receiver, message->size, message->data);
}

int thread_test() {

	mmio_write (GPFSEL4, reg);
	reg = 1 << 15;

	node_head* tlist = kthread_list_init();
	add_kthread (0, &thread_1_func);
	//tlist = add_kthread (0, &bled_func);
       	add_kthread (0, &thread_2_func);
	add_kthread (0, &terminal_func);

	kthread_list_dump ();
	//thread_set_pc (&thread_1_func);
	//delete_kthread (1);


	return 0;
}

