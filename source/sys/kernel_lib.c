#include "sys/kernel_lib.h"

int k_send (void* param) {
	int retv = -1;
	data_message* data = (data_message*) param;

	if (data->receiver == 0) {
		//Message to kernel
		//processing (data);
		return data->size;
	}
	kthread* receiver = find_thread_pid (data->receiver);
	
	if (receiver == NULL) {
#ifdef DEBUG
	kprint ("There are no receiver with %d pid\r\n", data->receiver);
#endif
		return retv;
	}

	byte ret = write_data (receiver->buffer, data, sizeof (data_message));

	if (ret) {
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
	return retv;
}	

static void thread_exit_shell() { 
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
	if (!ret) 
		memcpy (data->data, param2, data->size);
	else {
		cur_thread->state = BLOCKED;
		thread_exit_shell ();
		read_data (receiver->buffer, (void *) data);
		memcpy (data->data, param2, data->size);
	}
	retv = data->size;
	kfree (data);
	return retv;
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

	byte ret = read_data (receiver->buffer, (void *) data); 
	if (!ret) {
		memcpy (data->data, param2, data->size);
		retv = data->size;
	}
	kfree (data);
	return retv;
}

