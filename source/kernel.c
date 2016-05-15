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

#define KERNEL_HEAP_SIZE 0x10000000

void  __attribute__ ((interrupt ("IRQ"))) irq_handler(void) {
	thread_exit (cur_thread->registers);
  	_disable_interrupts();
  	kscheduler();
	sys_timer->compare1 = sys_timer->counter_lo + TIMER_RATE;
	sys_timer->control_status = ~0;
  	_enable_interrupts();
  	thread_entry (cur_thread->registers);
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;
	(void) atags;

        char hex[9] = {};
        uint32_t volatile ra;

        phys_area_list new_heap;

	uart_init();
        kprint("Hello, kernel world.\r\n"
               "Kernel start in %p\r\n"
               "Kernel stack in %p\r\n"
               "Kernel global variables in %p\r\n", (void*) kernel_main, hex, &global_var);

        phys_area_init(&new_heap, new_heap.list, KERNEL_HEAP_START_SIZE);


	// mem_test();
        //heap_test();
	//timer_test();
	//lib_test();
	//rbuffer_test();
	kprint("Power set: %x\r\n", bcm2835_vc_set_power_state(BCM2835_VC_POWER_ID_SDCARD, BCM2835_VC_SET_POWER_STATE_ON_WAIT));
	bdevs_init();

	thread_test();

	InitIrqController();
	sys_timer_init();	
	_enable_interrupts();
	run();


	while (1)
        {
		kprint ("sp: %x\r\n", _get_stack_pointer());
	}
	// kdie("First succesfull death");

//	while (1) {
//            
//                mmio_write(GPSET1, ra);
//                delay(0x300000);
//
//                mmio_write(GPCLR1, ra);
//                delay(0x300000);
//
//        }
        

		//uart_putc(uart_getc());
}

