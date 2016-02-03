#ifndef __BCM2836_GPIO__
#define __BCM2836_GPIO__

#include "defines.h"

#define GPIO_BASE (PBASE + 0x200000)

#define GPFSEL0 GPIO_BASE
#define GPFSEL1 (GPIO_BASE + 0x4)
#define GPFSEL2 (GPIO_BASE + 0x8)
#define GPFSEL3 (GPIO_BASE + 0xC)
#define GPFSEL4 (GPIO_BASE + 0x10)
#define GPFSEL5 (GPIO_BASE + 0x14)

#define GPSET0 (GPIO_BASE + 0x1C)
#define GPSET1 (GPIO_BASE + 0x20)
                               
#define GPCLR0 (GPIO_BASE + 0x28)
#define GPCLR1 (GPIO_BASE + 0x2C)
                               
#define GPLEV0 (GPIO_BASE + 0x34)
#define GPLEV1 (GPIO_BASE + 0x38)

#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)
#define GPPUDCLK1 (GPIO_BASE + 0x9C)

#endif
