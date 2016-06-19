#include <bcm2836/gpio.h>

#define __PTR(a) ((uint32_t *)((void *)(a)))

void gpio_set(uint8_t port)
{
	*__PTR(GPSET0) = (uint32_t)(1 << port);
}

int gpio_get(uint8_t port)
{
	return (*__PTR(GPLEV0) & (uint32_t)(1 << port));
}

void gpio_clr(uint8_t port)
{
	*__PTR(GPCLR0) = (uint32_t)(1 << port);
}

void gpio_inv(uint8_t port)
{
	if (*__PTR(GPSET0) & (uint32_t)(1 << port))
		gpio_clr(port);
	else
		gpio_set(port);
}

#undef __PTR
