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
#include <lib/nostdio.h>
#include <bcm2836/registers.h>

inline void kdie(char* err_msg)
{
        reg_t regarr[REGS_NUM] = {};
        reg2arr(regarr);

        kprint("System is dead.\r\n"
                "%s\r\n"
                "Core dump:\r\n"
                "r0 = %x\r\n"
                "r1 = %x\r\n"
                "r2 = %x\r\n"
                "r3 = %x\r\n"
                "r4 = %x\r\n"
                "r5 = %x\r\n"
                "r6 = %x\r\n"
                "r7 = %x\r\n"
                "r8 = %x\r\n"
                "r9 = %x\r\n"
                "r10 = %x\r\n"
                "r11 = %x\r\n"
                "r12 = %x\r\n"
                "sp = %x\r\n"
                "lr = %x\r\n"
                "pc = %x\r\n",
                err_msg,
                regarr[0],
                regarr[2],
                regarr[3],
                regarr[4],
                regarr[5],
                regarr[6],
                regarr[7],
                regarr[8],
                regarr[9],
                regarr[10],
                regarr[11],
                regarr[12],
                regarr[13],
                regarr[14],
                regarr[1]);
        while (1);
}
