#include "lib/nostdlib.h"

#include <stddef.h>
#include <stdint.h>
 
#include "bcm2836/mmio.h"
#include "bcm2836/delay.h"
#include "bcm2836/gpio.h"
#include "bcm2836/uart.h"


void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;
	(void) atags;

    uint32_t volatile ra;

    ra = 1 << 21;
    mmio_write(GPFSEL4, ra);

    ra = 1 << 15;
    
	uart_init();
    //uart_putc('c');
	uart_puts("Hello, kernel World!\r\n");
 
	while (1) {
            
            mmio_write(GPSET1, ra);
            delay(0x300000);

            mmio_write(GPCLR1, ra);
            delay(0x300000);

    }
        

		//uart_putc(uart_getc());
}
