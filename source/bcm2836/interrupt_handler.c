#include "bcm2836/interrupt.h"

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

void __attribute__((interrupt("SWI"))) software_handler(void)
{
	uint8_t swi_num = 0;
	dword param1;
	void* param2;
	asm volatile (  "mov %0, %%ip" : "=r" (swi_num));
	asm volatile (  "mov %0, %%r0\t\n"
			"mov %1, %%r1\t\n":"=r"(param1), "=r"(param2));

	switch (swi_num) {
		case 0:
			syscall_write (param2);
			break;
		case 1:
			syscall_read (param1, param2);
			break;
	}
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





