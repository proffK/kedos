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

void msg_d (void* data) {
	msg_t* d = (msg_t *)data;
	kprint ("sender %d param1 %d param2 %d\r\n", d->sender, d->param1, d->param2);
}

void data_d (void* data) {
	data_message* d = (data_message *) data;
	kprint ("sender %d receiver %d msg %s\r\n", d->sender, d->receiver, d->data);
}

void thread_1_func() {
	char* str = (char*) kcalloc (256, sizeof (char));
	res_type_t type = res_compose (RES_CPU, 0, 0, 0);
	int prd;
	while(1) {
		//GET_RES (prd, type, R_WAITFROM, 3);
		//GET_RES (prd, type, R_WAITFROM, 2);
		//dump_rbuffer(GET_KERNEL_THREAD()->buffer, msg_d);
		SEND_STR ("Hello #1\r\n", strlen ("Hello #1\r\n") + 1);
		kprint ("%d\r\n", prd);
		//GIVE_RES (prd, type, R_SENDTO, 0);
	}

}

void thread_2_func() {
	char* str = (char*) kcalloc (256, sizeof (char));
	res_type_t type = res_compose (RES_CPU, 0, 0, 0);
	int prd;
	GET_RES  (prd, type, 0, 0);
	while(1) {
		GET_RES  (prd, type, 2, R_WAITFROM);
		//dump_rbuffer(GET_KERNEL_THREAD()->buffer, msg_d);
		SEND_STR ("Hello #2\r\n", strlen ("Hello #2\r\n") + 1);
		kprint ("%d\r\n", prd);
		GIVE_RES (prd, type, 2, R_SENDTO);
	}
}

void terminal_func() {
	char* str = (char*) kcalloc (256, sizeof (char));
	int retv = -1;
	res_type_t type = res_compose (RES_CPU, 0, 0, 0);
	int prd;
	while(1) {
		GET_RES (prd, type, 3, R_WAITFROM);
		//dump_rbuffer(GET_KERNEL_THREAD()->buffer, msg_d);
		while (try_receive (str) >= 0)
			kprint ("%s", str);
		GIVE_RES (prd, type, 3, R_SENDTO);
	}
}


void data_message_dump (void* data) {
	data_message* message = (data_message*) data;
	kprint ("%d %d %d %s\r\n", message->sender, message->receiver, message->size, message->data);
}

int thread_test() {

//	kthread_list_init();
	add_kthread (0, &thread_1_func, HARD);
	add_kthread (0, &terminal_func, HARD);
	add_kthread (0, &thread_2_func, HARD);
	kthread_list_dump();
	return 0;
}

