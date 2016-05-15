#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "sys/kscheduler.h"
#include "bcm2836/timer.h"
#include "lib/nostdio.h"
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


extern irq_controller* GetIrqController( void );
void InitIrqController (void);

#endif
