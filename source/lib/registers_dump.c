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

#include <lib/nostdlib.h>

void dump_registers(reg_t* arr)
{
	asm volatile ("str %%r0, %0\n\t"
		      "ldr %%r0, [%%fp, #-8]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r1, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r2, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r3, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r4, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r5, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r6, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r7, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r8, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r9, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r10, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r11, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%r12, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%sp, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%lr, [%%r0]\n\t"
		      "add %%r0, %%r0, #4\n\t"
		      "str %%pc, [%%r0]\n\t"
		      : "=m" (arr) : : "r0", "memory");
}
	

