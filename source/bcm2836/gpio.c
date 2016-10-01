#include <bcm2836/gpio.h>

#define __PTR(a) ((uint32_t *)((void *)(a)))

void gpio_set(int port)
{
	*__PTR(GPSET0) = (uint32_t)(1 << port);
}

int gpio_get(int port)
{
	return (*__PTR(GPLEV0) & (uint32_t)(1 << port));
}

void gpio_clr(int port)
{
	*__PTR(GPCLR0) = (uint32_t)(1 << port);
}

void gpio_inv(int port)
{
	if (*__PTR(GPSET0) & (uint32_t)(1 << port))
		gpio_clr(port);
	else
		gpio_set(port);
}

#undef __PTR
