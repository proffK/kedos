#include "bcm2836/interrupt.h"
#include "sys/kthread.h"

extern void _kernel_entry (void);

static irq_controller* IRQController =
        (irq_controller*)INTERRUPT_CONTROLLER_BASE;

irq_controller* GetIrqController() {

	return IRQController;
}

void InitIrqController (void) {
        GetIrqController()->Enable_IRQs_1 = 1 << 1;
}


void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
  	kprint ("undef instruction vector\r\n");
}


void  __attribute__ ((interrupt ("IRQ"))) irq_handler(void) 
{
	//kprint ("IRQ\r\n");
	sys_timer->compare1 = sys_timer->counter_lo + TIMER_RATE;
	sys_timer->control_status = ~0;	
	thread_exit();
}

void __attribute__((interrupt("SWI"))) software_handler(void)
{
	byte swi_num = 0;
	dword param1;
	void* param2;
	int retv = -1;
	SWI_PROCESSING (swi_num, param1, param2);

	switch (swi_num) {
		case 0:
		  	retv = k_send (param2);
			break;
		case 1:
		  	retv = k_receive (param1, param2);
			break;
		case 2: 
			retv = k_try_receive (param1, param2);
			break;
	}
	SWI_EXIT (cur_thread->stack_pointer, retv);
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{
  	kprint ("prefetch abort\r\n");
}

void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{
  	kprint ("data abort\r\n");
}

void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{
	kprint ("fast interrupt\r\n");
}
