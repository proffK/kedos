#include "sys/kthread.h"
#include "lib/nostdlib.h"


kthread_list* thread_list = NULL;
kthread* cur_thread = NULL;

kthread* kthread_init (sflag_t flags, dword pid, void* func) {
	kthread* thread = (kthread*) kcalloc (1, sizeof (kthread));
	thread->registers = (dword*) kcalloc (15, sizeof (dword));
	thread->flags = flags; 
	thread->pid = pid;
	thread->registers[13] = (dword*)phys_page_alloc (THREAD_PAGE_COUNT, pid) + PAGE_SIZE - 1;
	thread->stack_base = thread->registers[13];
	thread->buffer = create_rbuffer (RBUFFER_IS_EMPTY);
	thread->registers[14] = func;
	return thread;
}

int kthread_delete (kthread* thread) {
	if (thread == NULL) {
		kprint ("Incorrect thread address");
		errno = ENOMEM;
		return -1;
	}
	phys_page_free ((void *)thread->stack_base);
	free_rbuffer (thread->buffer);
	kfree (thread->registers);
	kfree (thread);
	return 0;
}

#ifdef DEBUG
void kthread_dump (kthread* thread) {
	kprint ("\r\nTHREAD %d DUMP: \r\n"
		"STATE: %d \r\n"
		"FLAGS: %d \r\n"
		"REGISTERS: \r\n" 
		"r0 = %d\r\n"
		"r1 = %d\r\n"
		"r2 = %d\r\n"
		"r3 = %d\r\n"
		"r4 = %d\r\n"
		"r5 = %d\r\n"
		"r6 = %d\r\n"
		"r7 = %d\r\n"
		"r8 = %d\r\n"
		"r9 = %d\r\n"
		"r10 = %d\r\n"
		"r11 = %d\r\n"
		"r12 = %d\r\n"
		"sp = %d\r\n"
		"lr = %d\r\n"
		,thread->pid, thread->state, thread->flags,
	       	thread->registers[0], thread->registers[1], thread->registers[2], thread->registers[3],
	       	thread->registers[4], thread->registers[5], thread->registers[6], thread->registers[7],
	       	thread->registers[8], thread->registers[9], thread->registers[10], thread->registers[11],
	       	thread->registers[12], thread->registers[13], thread->registers[14]);
}
#endif

kthread_list* kthread_list_init () {
	thread_list = (kthread_list*) kcalloc (1, sizeof (kthread_list));
	thread_list->head = NULL;
	thread_list->tail = NULL;
	thread_list->cur_pid = 0;
	return thread_list;
}

int kthread_list_delete () {
        if (thread_list == NULL) {
	        kprint ("Thread list doesn't exist\r\n");
		errno = ENOMEM;
		return -1;
	}
	kthread* cur = thread_list->head;
	while (cur != thread_list->tail || cur != NULL) {
	        cur = cur->next;
		kthread_delete (cur);
	}
	if (cur != NULL)
	        kthread_delete (cur);
	kfree (thread_list);
	return 0;
}

kthread_list* add_kthread (sflag_t flags, void* func) {
	if (thread_list == NULL) {
		kprint ("Thread list doesn't exist\r\n");
		errno = ENOMEM;
		return NULL;
	}
	
	kthread* thread = kthread_init (flags, thread_list->cur_pid, func);
	thread_list->cur_pid++;
	if (thread_list->head == NULL || thread_list->tail == NULL) {
		thread_list->head = thread;
		thread_list->tail = thread;
		thread->prev = thread;
		thread->next = thread;
		cur_thread = thread;
	} else {
		thread->prev = thread_list->tail;
		thread_list->head->prev = thread;
		thread_list->tail->next = thread;
		thread->next = thread_list->head;
		thread_list->tail = thread;
	}
	return thread_list;
}

kthread_list* delete_kthread (dword pid) {
	if (thread_list == NULL) {
		kprint ("Thread list doesn't exist\r\n");
		errno = ENOMEM;
		return NULL;
	}
	kthread* thread = find_thread_pid (pid);
       
	thread->next->prev = thread->prev;
	thread->prev->next = thread->next;
	if (thread == thread_list->head && thread == thread_list->tail) {
	        thread_list->head = NULL;
	        thread_list->tail = NULL;
		kprint ("head = tail, thread # %d\r\n", thread->pid);
	}
	else if (thread == thread_list->head) 
		thread_list->head = thread->next;
	else if (thread == thread_list->tail)
		thread_list->tail = thread->prev;
	kthread_delete (thread);

	return thread_list;
}

void kthread_list_dump () {
	if (thread_list->head == NULL || thread_list->tail == NULL) {
		kprint ("List is empty\r\n");
		return;
	}
	kprint ("\r\nThread list: \r\n");
	kthread* cur = thread_list->head;
	if (cur != NULL)
	        do {
		        kthread_dump (cur);
		        cur = cur->next;
		} while (cur != thread_list->head);
}

kthread* find_thread_pid (dword pid) {
	kthread* cur = thread_list->head;
	do {
		if (cur->pid == pid)
			return cur;
		cur = cur->next;
	} while (cur != thread_list->head);
#ifdef DEBUG
	kprint ("There are no thread with pid = %d\r\n", pid);
#endif
	return NULL;
}

void run() {
	_set_sp (cur_thread->registers[13]);
	kprint ("sp :%x\r\n", _get_stack_pointer());
	thread_set_pc (cur_thread->registers[14]);
}

void context_switch (void) {
	thread_exit (cur_thread->registers);
	kscheduler();
	thread_entry (cur_thread->registers);
}



