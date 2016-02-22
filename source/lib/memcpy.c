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

void* memcpy(void* src, void* dst, size_t size) 
{
        void* old_dst = dst;

        if (src == NULL || dst == NULL) {
                errno = EFAULT;
#ifdef TEDIOS_DEBUG
                kprint("\r\nError!"
                       "Zero pointer memcpy:\r\n"
                       "src:  %p\r\n"
                       "dst:  %p\r\n"
                       "size: %d\r\n", src, dst, size);
#endif
                return NULL;
        }

        if (D_ALIGNED(src) && D_ALIGNED(dst) && D_ALIGNED(size)) {
                while(size) {
                        *((dword*) dst) = *((dword*) src);
                        dst += sizeof(dword);
                        src += sizeof(dword);
                        size -= sizeof(dword);
                }

                return old_dst;
        }

        if (W_ALIGNED(src) && W_ALIGNED(dst) && W_ALIGNED(size)) {
                while(size) {
                        *((word*) dst) = *((word*) src);
                        dst += sizeof(word);
                        src += sizeof(word);
                        size -= sizeof(word);
                }

                return old_dst;
        }

        while(size) {
                *((byte*) dst++) = *((byte*) src++); 
                size--;
        }

        return old_dst;
}
