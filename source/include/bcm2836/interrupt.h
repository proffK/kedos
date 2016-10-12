#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "bcm2836/timer.h"
#include "lib/nostdio.h"
#include "sys/kernel_lib.h"
#include "sys/kthread.h"


#define INTERRUPT_CONTROLLER_BASE   ( PBASE + 0xB200 )
#define BASIC_ARM_TIMER_IRQ         (1 << 0)
#define BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)


typedef struct {

	volatile uint32_t IRQ_basic_pending;
	volatile uint32_t IRQ_pending_1;
	volatile uint32_t IRQ_pending_2;
	volatile uint32_t FIQ_control;
	volatile uint32_t Enable_IRQs_1;
	volatile uint32_t Enable_IRQs_2;
	volatile uint32_t Enable_Basic_IRQs;
	volatile uint32_t Disable_IRQs_1;
	volatile uint32_t Disable_IRQs_2;
	volatile uint32_t Disable_Basic_IRQs;

} irq_controller;

#define SWI_EXIT(sp, retv) \
	asm volatile (	"mov %%r1, %%sp\t\n"\
					"mov %%sp, %1\t\n"\
					"pop {%%r0}\t\n"\
					"mov %%r0, %0\t\n"\
					"push {%%r0}\t\n"\
					"mov %%sp, %%r1\t\n"\
					::"r"(retv), "r"(sp):"%r0", "%r1", "%sp", "memory");

#define SWI_PROCESSING(swi_num, param1, param2) \
	asm volatile (  "ldr %%r2, [%%lr, #-4]\t\n"\
					"bic %%r2, %%r2, #0xff000000\t\n"\
					"mov %0, %%r2\t\n"\
 					"mov %1, %%r0\t\n"\
					"mov %2, %%r1\t\n"\
					 : "=r" (swi_num), "=r"(param1), "=r"(param2)::"%r0", "%r1", "%r2", "memory");



extern irq_controller* GetIrqController( void );
void InitIrqController (void);

#endif
