#include "test/test.h"
int p1 = 0;
int p2 = 1;
void thread_1_func() {
	while(1) {	
		p2 = 1;
		if (p1 == 1) {
			p1 = 0;
			char* str = (char*) kcalloc (12, sizeof (char));
			memcpy ("Hello #1!\r\n", str, 12);
			sc_th_write (cur_thread->pid, 2, str);
		}
	}
}

void thread_2_func() {
	while(1) {
		p1 = 1;
		if (p2 == 1) {
			p2 = 0;
			char* str = (char*) kcalloc (12, sizeof (char));
			memcpy ("Hello #2!\r\n", str, 12);
			sc_th_write (cur_thread->pid, 2, str);
		}

	}
}

void terminal_func() {
	char* str = (char*) kcalloc (12, sizeof (char));
	while(1) {
		sc_th_read(str);
		if (*str != '\0')
			kprint ("%s", str);
		*str = '\0';
	}
}

void data_message_dump (void* data) {
	data_message* message = (data_message*) data;
	kprint ("%d %d %d %s\r\n", message->sender, message->receiver, message->size, message->data);
}

int thread_test() {
	kthread_list* tlist = kthread_list_init();
	tlist = add_kthread (0, &thread_1_func);
       	tlist = add_kthread (0, &thread_2_func);
	tlist = add_kthread (0, &terminal_func);

	kthread_list_dump ();
	//thread_set_pc (&thread_1_func);
	//delete_kthread (1);


	return 0;
}

