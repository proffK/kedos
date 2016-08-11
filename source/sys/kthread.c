#include "sys/kthread.h"
#include "lib/nostdlib.h"


kthread* cur_thread = NULL;
node_head* thread_head = NULL;
active_head* th_active_head = NULL;
pid_t cur_pid = 0;

extern reg_t* _get_stack_pointer();

kthread* kthread_init (sflag_t flags, pid_t pid, void* func) {
	kthread* thread = (kthread*) kcalloc (1, sizeof (kthread));
	thread->flags = flags; 
	thread->pid = pid;
	thread->stack_pointer = (reg_t *)phys_page_alloc (THREAD_PAGE_COUNT, pid) + PAGE_SIZE - 1;
	thread->stack_base = thread->stack_pointer;	
	thread->buffer = create_rbuffer (0, RING_BUFFER_SIZE);
	thread->program_counter = (reg_t *)func;
	init_dl_node (&thread->node);
	init_dl_node (&thread->active);
	if (!cur_thread)
		cur_thread = thread;
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
	delete_node (&thread->node);
	delete_node (&thread->active);
	kfree (thread);
	return 0;
}

#ifdef DEBUG
void kthread_dump (kthread* thread) {
	kprint ("Thread #%d\r\n SB : 0x%x\r\n SP : 0x%x\r\n PC : 0x%x\r\n", 
		thread->pid, thread->stack_base, thread->stack_pointer, thread->program_counter);
}
#endif

node_head* kthread_list_init () {
	thread_head = (node_head*) kcalloc (1, sizeof (node_head));
	node_init (thread_head);
	th_active_head = (active_head*) kcalloc (1, sizeof (active_head));
	active_init (th_active_head);
	return thread_head;
}

int kthread_list_delete () {
        if (thread_head == NULL) {
	        kprint ("Thread list doesn't exist\r\n");
		errno = ENOMEM;
		return -1;
	}
	kthread* i = NULL;
	for (i = node_head_first(thread_head);
        	node_is_last(thread_head, i); i = node_next(i)) {
        	kthread_delete (i);
    	}
	kfree (thread_head);
	kfree (th_active_head);
	return 0;
}

void add_kthread (sflag_t flags, void* func) {
	if (thread_head == NULL) {
		kprint ("Thread list doesn't exist\r\n");
		errno = ENOMEM;
		return;
	}
	if (th_active_head == NULL) {
		kprint ("Thread active list doesn't exist\r\n");
		errno = ENOMEM;
		return;
	}
	kthread* thread = kthread_init (flags, cur_pid, func);
	node_add_tail (thread_head, thread);
	active_add_tail (th_active_head, thread);
	cur_pid++;
}

void delete_kthread (pid_t pid) {
	if (thread_head == NULL) {
		kprint ("Thread list doesn't exist\r\n");
		errno = ENOMEM;
		return;
	}

	if (th_active_head == NULL) {
		kprint ("Thread active list doesn't exist\r\n");
		errno = ENOMEM;
		return;
	}

	kthread* thread = find_thread_pid (pid);
	kthread_delete (thread);
}

void kthread_list_dump () {
	if (thread_head == NULL) {
		kprint ("List is empty\r\n");
		return;
	}
	kprint ("\r\nThread list: \r\n");
	for (kthread *i = node_head_first(thread_head);
        	node_is_last(thread_head, i); i = node_next(i)) {
		kthread_dump (i);        	
    	}
}

kthread* find_thread_pid (pid_t pid) {
	kthread* i = NULL;
	for (i = node_head_first(thread_head);
        	node_is_last(thread_head, i); i = node_next(i)) {
        	if (i->pid == pid)
			return i;
    	}
#ifdef DEBUG
	kprint ("There are no thread with pid = %d\r\n", pid);
#endif
	return NULL;
}

extern void _set_sp(reg_t* sp);

void __attribute__((naked())) run() {
	_set_sp (cur_thread->stack_pointer);
	thread_set_pc (cur_thread->program_counter);
}



