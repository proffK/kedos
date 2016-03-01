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

#include "mm/heap.h"

#include "test/test.h"

#define KERNEL_HEAP_SIZE 0x10000000

int global_var;

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;
	(void) atags;

        char hex[9] = {};
        uint32_t volatile ra;

        phys_area_list new_heap;

        ra = 1 << 21;
        mmio_write(GPFSEL4, ra);

        ra = 1 << 15;
    
	uart_init();
        kprint("Hello, kernel world.\r\n"
               "Kernel start in %p\r\n"
               "Kernel stack in %p\r\n"
               "Kernel global variables in %p\r\n", (void*) kernel_main, hex, &global_var);

        phys_area_init(&new_heap, new_heap.list, KERNEL_HEAP_START_SIZE);
        
        //mem_test();
        //heap_test();
        timer_test();

        kdie("First succesfull die");

	while (1) {
            
                mmio_write(GPSET1, ra);
                delay(0x300000);

                mmio_write(GPCLR1, ra);
                delay(0x300000);

        }
        

		//uart_putc(uart_getc());
}
