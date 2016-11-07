/* Copyright (C) 2013 by Klim Kireev <edvmartell@gmail.com> <https://github.com/proffK>

*   This file is part of kedos.

*   kedos is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.

*   kedos is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.

*   You should have received a copy of the GNU General Public License
*   along with kedos.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "lib/nostdlib.h"
#include "lib/nostdio.h"

#include <stddef.h>
#include <stdint.h>
 
#include "bcm2836/mmio.h"
#include "bcm2836/delay.h"
#include "bcm2836/gpio.h"
#include "bcm2836/uart.h"
#include "bcm2836/interrupt.h"
#include "sys/kthread.h"
#include "mm/heap.h"

#include "sys/devs.h"

#include "test/test.h"

int global_var = 0;
reg_t kernel_sp = 0;

#define KERNEL_HEAP_SIZE 0x10000000

static void __attribute__((naked())) kernel (void); 

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;
	(void) atags;
	int retv;

        char hex[9] = {};
        phys_area_list new_heap;

	uart_init();
	kprint("Hello, kernel world.\r\n"
               "Kernel start in %p\r\n"
               "Kernel stack in %p\r\n"
               "Kernel global variables in %p\r\n", (void*) kernel_main, hex, &global_var);

/********************************************************************/

	phys_area_init(&new_heap, KERNEL_HEAP_START_SIZE);

	mem_test();
    	heap_test();
		res_table_init();
    	hardware_init();

/********************************************************************/

	retv = kthread_list_init();
	if (retv != 0)
		kdie ("Can't init thread list");

/********************************************************************/

	kthread* thread = (kthread*) kcalloc (1, sizeof (kthread));

	if (thread == NULL) 
		kdie ("Can't init kernel thread");

	thread->program_counter = (reg_t) kernel;	
	thread->pid = 0; // Kernel thread init
	thread->buffer = create_rbuffer (0, KERNEL_MSGBUF_SIZE);
	init_dl_node (&thread->node);
	node_add_tail (thread_head, thread);


/********************************************************************/

	//kprint("Power set: %x\r\n", bcm2835_vc_set_power_state(BCM2835_VC_POWER_ID_SDCARD, BCM2835_VC_SET_POWER_STATE_ON_WAIT));
	//bdevs_init();
	//sd_test();

/********************************************************************/
	
	//timer_test();
	//lib_test(); 
	//rbuffer_test();	
	thread_test();

/********************************************************************/

	InitIrqController();
	sys_timer_init();	
	_enable_interrupts();
	run();

/********************************************************************/

	kdie("First succesfull death");
	uart_putc(uart_getc());
}

static void __attribute__((naked())) kernel (void) {
	kscheduler();
	thread_entry(cur_thread->stack_pointer, cur_thread->program_counter);
}

void __attribute__((naked())) kernel_entry(void) {
	_disable_interrupts();
	asm volatile ( 	"str %%sp, [%0]\t\n"
					"mov %%sp, %1\t\n"
					"mov %%r0, %2\t\n"
					"bx %%r0\t\n" :: "r"(&cur_thread->stack_pointer), 
					"r"(node_head_prev(thread_head)->stack_pointer), 
					"r"(kernel): "%r0", "%sp", "memory");
}

