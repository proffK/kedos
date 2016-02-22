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

#include <lib/string.h>
#include <lib/nostdio.h>

#define D_ALIGNED(ptr) (!((uint32_t) ptr % sizeof(uint32_t)))
#define W_ALIGNED(ptr) (!((uint32_t) ptr % sizeof(uint16_t)))

void* memset(void* dst, byte z, size_t size)
{
        void* old_dst = dst;

        if (dst == NULL) {
                errno = EFAULT;
#ifdef TEDIOS_DEBUG
                kprint("\r\nError!"
                       "Zero pointer memset:\r\n"
                       "z:    %d"
                       "dst:  %p\r\n"
                       "size: %d\r\n",(int) z, dst, size);
#endif
                return NULL;
        }

        if (D_ALIGNED(dst) && D_ALIGNED(size)) {
                register dword dtemp;

                dtemp = (z << (3 * sizeof(byte))) +
                        (z << (2 * sizeof(byte))) +
                        (z << sizeof(byte)) + z;

                while (size) {
                        *((dword*) dst) = dtemp;
                        dst += sizeof(dword);
                        size -= sizeof(dword);
                }

                return old_dst;
        }

        if (W_ALIGNED(dst) && W_ALIGNED(size)) {
                register word wtemp;

                wtemp = (z << sizeof(byte)) + z;

                while (size) {
                        *((word*) dst) = wtemp;
                        dst += sizeof(word);
                        size -= sizeof(word);
                }

                return old_dst;
        }

        while (size) {
                *((byte*) dst++) = z;
                size--;
        }

        return old_dst;
} 
