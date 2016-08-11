#include "sys/kernel_lib.h"

int k_send (void* param) {
	int retv = -1;
	data_message* data = (data_message*) param;
	kthread* receiver = find_thread_pid (data->receiver);
	
	if (receiver == NULL) {
#ifdef DEBUG
	kprint ("There are no receiver with %d pid\r\n", data->receiver);
#endif
		return retv;
	}

	byte ret = write_data (receiver->buffer, data, sizeof (data_message));
	if (!ret) {
#ifdef DEBUG
	kprint ("Can't write data to thread with %d pid\r\n", receiver->pid);
#endif
		return retv;
	}

	if (receiver->state == BLOCKED) {
		receiver->state = WAIT;
		active_add_tail (th_active_head, receiver);
	}
	retv = data->size;
	kprint ("SEND\r\n");
	return retv;
}	

void thread_exit_shell() { 
	asm volatile (	"mov %%fp, %%sp\t\n"
			:::"%fp", "memory");
	thread_exit();
}

int k_receive (dword param1, void* param2) {
	int retv = -1;
	data_message* data = (data_message *) kcalloc (1, sizeof (data_message));
	kthread* receiver = find_thread_pid (param1);
	if (!receiver) {
#ifdef DEBUG
	kprint ("Can't find receiver thread with %d pid\r\n", param1);
#endif
		return retv;
	}

	byte ret = read_data (receiver->buffer, (void *) data); 
	if (ret == 0) 
		memcpy (data->data, param2, data->size);
	else {
		cur_thread->state = BLOCKED;
		unpin_node (&cur_thread->active);
		thread_exit_shell ();
		memcpy (data->data, param2, data->size);
	}
	kfree (data);
	retv = data->size;
	kprint ("RECEIVE\r\n");
	return retv;
}

void data_dump (void* data) {
	data_message* d = (data_message *) data;
	kprint ("sender %d receiver %d msg %s\r\n", d->sender, d->receiver, d->data);
}

int k_try_receive (dword param1, void* param2) {
	int retv = -1;
	data_message* data = (data_message *) kcalloc (1, sizeof (data_message));
	kthread* receiver = find_thread_pid (param1);
	if (!receiver) {
#ifdef DEBUG
	kprint ("Can't find receiver thread with %d pid\r\n", param1);
#endif
		return retv;
	}

//	dump_rbuffer (receiver->buffer, data_dump);		
	byte ret = read_data (receiver->buffer, (void *) data); 
	if (ret == 0) {
		memcpy (data->data, param2, data->size);
		kprint ("%s\r\n",(char*) param2);	
		retv = data->size;
	}
	kfree (data);
	kprint ("TRY RECEIVE\r\n");
	return retv;
}

