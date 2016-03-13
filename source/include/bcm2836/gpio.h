/**
 * @file bcm2835_gpio.h
 *
 */
/* Copyright (C) 2015, 2016 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef BCM2835_GPIO_H_
#define BCM2835_GPIO_H_

#include <stdint.h>
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

//#define BCM2835_GPIO_BASE (PBASE + 0x200000)
//
//typedef struct {
//	__IO uint32_t GPFSEL0;		///< 0x00, GPIO Function Select 0
//	__IO uint32_t GPFSEL1;		///< 0x04, GPIO Function Select 1
//	__IO uint32_t GPFSEL2;		///< 0x08, GPIO Function Select 2
//	__IO uint32_t GPFSEL3;		///< 0x0C, GPIO Function Select 3
//	__IO uint32_t GPFSEL4;		///< 0x10, GPIO Function Select 4
//	__IO uint32_t GPFSEL5;		///< 0x14, GPIO Function Select 5
//	__IO uint32_t RES1;			///< 0x18, Reserved
//	__O uint32_t GPSET0;		///< 0x1C, GPIO Pin Output Set 0
//	__O uint32_t GPSET1;		///< 0x20, GPIO Pin Output Set 1
//	__IO uint32_t RES2;			///< 0x24, Reserved
//	__O uint32_t GPCLR0;		///< 0x28, GPIO Pin Output Clear 0
//	__O uint32_t GPCLR1;		///< 0x2C, GPIO Pin Output Clear 1
//	__IO uint32_t RES3;			///< 0x30, Reserved
//	__I uint32_t GPLEV0;		///< 0x34, GPIO Pin Level 0
//	__I uint32_t GPLEV1;		///< 0x38, GPIO Pin Level 1
//	__IO uint32_t RES4;			///< 0x3C, Reserved
//	__IO uint32_t GPEDS0;		///< 0x40, GPIO Pin Event Detect Status 0
//	__IO uint32_t GPEDS1;		///< 0x44, GPIO Pin Event Detect Status 1
//	__IO uint32_t RES5;			///< 0x48, Reserved
//	__IO uint32_t GPREN0;		///< 0x4C, GPIO Pin Rising Edge Detect Enable 0
//	__IO uint32_t GPREN1;		///< 0x50, GPIO Pin Rising Edge Detect Enable 1
//	__IO uint32_t RES6;			///< 0x54, Reserved
//	__IO uint32_t GPFEN0;		///< 0x58, GPIO Pin Falling Edge Detect Enable 0
//	__IO uint32_t GPFEN1;		///< 0x5C, GPIO Pin Falling Edge Detect Enable 1
//	__IO uint32_t RES7;			///< 0x60, Reserved
//	__IO uint32_t GPHEN0;		///< 0x64, GPIO Pin High Detect Enable 0
//	__IO uint32_t GPHEN1;		///< 0x68, GPIO Pin High Detect Enable 1
//	__IO uint32_t RES8;			///< 0x6C, Reserved
//	__IO uint32_t GPLEN0;		///< 0x70, GPIO Pin Low Detect Enable 0
//	__IO uint32_t GPLEN1;		///< 0x74, GPIO Pin Low Detect Enable 1
//	__IO uint32_t RES9;			///< 0x78, Reserved
//	__IO uint32_t AREN[2];		///< 0x7C
//	__IO uint32_t RES10;		///< 0x84, Reserved
//	__IO uint32_t AFEN[2];		///< 0x88
//	__IO uint32_t RES11;		///< 0x90
//	__IO uint32_t GPPUD; 		///< 0x94, GPIO Pin Pull-up/down Enable
//	__IO uint32_t GPPUDCLK0;	///< 0x98, GPIO Pin Pull-up/down Enable Clock 0
//	__IO uint32_t GPPUDCLK1;	///< 0x9C, GPIO Pin Pull-up/down Enable Clock 1
//} BCM2835_GPIO_TypeDef;
//
//
///// Function select modes for \ref bcm2835_gpio_fsel
//typedef enum {
//	BCM2835_GPIO_FSEL_INPT = 0x00,	///< 0b000,	Input
//	BCM2835_GPIO_FSEL_OUTP = 0x01,	///< 0b001,	Output
//	BCM2835_GPIO_FSEL_ALT0 = 0x04,	///< 0b100,	Alternate function 0
//	BCM2835_GPIO_FSEL_ALT1 = 0x05,	///< 0b101,	Alternate function 1
//	BCM2835_GPIO_FSEL_ALT2 = 0x06,	///< 0b110,	Alternate function 2
//	BCM2835_GPIO_FSEL_ALT3 = 0x07,	///< 0b111,	Alternate function 3
//	BCM2835_GPIO_FSEL_ALT4 = 0x03,	///< 0b011,	Alternate function 4
//	BCM2835_GPIO_FSEL_ALT5 = 0x02,	///< 0b010,	Alternate function 5
//	BCM2835_GPIO_FSEL_MASK = 0x07	///< 0b111, Function select bits mask
//} bcm2835FunctionSelect;
//
///// Pullup/Pulldown defines for \ref bcm2835_gpio_set_pud
//typedef enum {
//	BCM2835_GPIO_PUD_OFF 	= 0x00,	///< 0b00, Off ? disable pull-up/down
//	BCM2835_GPIO_PUD_DOWN 	= 0x01,	///< 0b01, Enable Pull Down control
//	BCM2835_GPIO_PUD_UP 	= 0x02	///< 0b10, Enable Pull Up control
//} bcm2835PUDControl;
//
//#define BCM2835_GPIO	((BCM2835_GPIO_TypeDef *) BCM2835_GPIO_BASE) ///< Base register address for GPIO
///**
// * @ingroup GPIO
// *
// * Sets the specified pin output to HIGH
// *
// * @param pin GPIO number.
// */
//inline static void bcm2835_gpio_set(const uint8_t pin) {
//	BCM2835_GPIO->GPSET0 = (uint32_t) (1 << pin);
//}
//
///**
// * @ingroup GPIO
// *
// * Sets the specified pin output to LOW
// *
// * @param pin GPIO number.
// */
//inline static void bcm2835_gpio_clr(const uint8_t pin) {
//	BCM2835_GPIO ->GPCLR0 = (uint32_t) (1 << pin);
//}
//
///**
// * @ingroup GPIO
// *
// * Sets the output state of the specified pin.
// *
// * @param pin GPIO number
// * @param on \ref HIGH sets the output to HIGH and \ref LOW to LOW.
// */
//inline static void bcm2835_gpio_write(const uint8_t pin, const uint8_t on) {
//	if (on != 0) {
//		bcm2835_gpio_set(pin);
//	} else {
//		bcm2835_gpio_clr(pin);
//	}
//}
//
///**
// * @ingroup GPIO
// *
// * @param pin
// * @return
// */
//inline static uint8_t bcm2835_gpio_lev(const uint8_t pin) {
//	uint32_t value = BCM2835_GPIO ->GPLEV0; // TODO BUG pin > 32
//	return (value & (1 << pin)) ? (uint8_t)HIGH : (uint8_t)LOW;
//}
//
///**
// * @ingroup GPIO
// *
// * Sets the Pull-up/down register for the given pin. This is
// * used with \ref bcm2835_gpio_pudclk to set the  Pull-up/down resistor for the given pin.
// * However, it is usually more convenient to use \ref bcm2835_gpio_set_pud.
// *
// * @param pud The desired Pull-up/down mode. One of BCM2835_GPIO_PUD_* from \ref bcm2835PUDControl
// */
//inline static void bcm2835_gpio_pud(const uint8_t pud) {
//	BCM2835_GPIO ->GPPUD = pud;
//}
//
///**
// * @ingroup GPIO
// *
// * @param pin
// * @param on
// */
//inline static void bcm2835_gpio_pudclk(const uint8_t pin, const uint8_t on) {
//	BCM2835_GPIO ->GPPUDCLK0 = (uint32_t)((on ? 1 : 0) << pin);
//}
//
//#define BCM2835_PERI_SET_BITS(a, v, m)		a = ((a) & ~(m)) | ((v) & (m));
//
///**
// * @ingroup GPIO
// *
// * Defined in file bcm2835_gpio_fsel.S
// *
// * Sets the Function Select register for the given pin, which configures
// * the pin as Input, Output or one of the 6 alternate functions.
// *
// * @param pin GPIO number.
// * @param mode Mode to set the pin to, one of BCM2835_GPIO_FSEL_* from \ref bcm2835FunctionSelect
// */
//extern void bcm2835_gpio_fsel(const uint8_t pin, const uint8_t mode);
//
//extern void bcm2835_gpio_set_pud(const uint8_t, const uint8_t);
//
//#endif /* BCM2835_GPIO_H_ */
//*/


#endif
