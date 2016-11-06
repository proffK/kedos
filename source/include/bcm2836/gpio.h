/**
 * \file bcm2836/gpio.h
 * 
 * This file contains interface for general-purpose i/o
 * for both bcm2835(bcm2836).
 *
 * $Copyright: (C) 2016 by Andrew Bezzubtsev $
 *
 * This file is part of kedos.
 * kedos is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * kedos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kedos.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \defgroup io
 */

#ifndef __BCM2836_GPIO_H__
#define __BCM2836_GPIO_H__

#include <stdint.h>
#include "defines.h"

#define GPIO_NUM  54
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

/**
 * \ingroup io
 *
 * \arg port port being setted
 *
 * This function sets given port
 * to "HIGH", aka makes it enabled.
 * 
 * \code
 * gpio_set(0);
 * if (!gpio_get(1)) {
 *     kprint("Error!\n1 pin is zero!\n");
 *     return;
 * }
 * \endcode
 *
 * \see gpio_get(), gpio_clr(), gpio_inv()
 */
void gpio_set(int port);

/**
 * \ingroup io
 *
 * \arg port port being checked
 *
 * This function checks for the port is having
 * any electricity, or not
 * 
 * \code
 * gpio_set(0);
 * if (!gpio_get(1)) {
 *     kprint("Error!\n1 pin is zero!\n");
 *     return;
 * }
 * \endcode
 *
 * \see gpio_set(), gpio_clr(), gpio_inv()
 */
int gpio_get(int port);

/**
 * \ingroup io
 *
 * \arg port port being cleared
 *
 * This function sets given port
 * to "LOW", aka makes it disabled.
 *
 * \code
 * gpio_clr(0);
 * if (gpio_get(1)) {
 *     kprint("Error!\nI can still see electricity on 1 port!");
 *     return;
 * }
 * \endcode
 *
 * \see gpio_set(), gpio_get(), gpio_inv()
 */
void gpio_clr(int port);

/**
 * \ingroup io
 *
 * \arg port port being inverted
 *
 * This function checks port for being setted, and
 * inverts it. If it was "HIGH", it becomes "LOW".
 * Else it becomes "HIGH".
 *
 * \code
 * int old_state = gpio_get(1);
 * gpio_inv(0);
 * if (gpio_get(1) == old_state) {
 *	kprint("Error!\nI can't see any difference on 1st port!\n");
 *      return;
 * }
 * \endcode
 *
 * \see gpio_set gpio_get(), gpio_clr()
 */
void gpio_inv(int port);

#endif
