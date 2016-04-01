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

#include <test/test.h>

int heap_test()
{
        void* p0;
        void* p1;
        void* p2;
        void* p3;
        void* p4;

        p0 = kmalloc(5600);
        p1 = kmalloc(4);
        p2 = kmalloc(256);
        p3 = kcalloc(1, 7);
        p4 = kcalloc(2, 42);

        kmem_full_dump();
        
        kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);

        kfree(p1);
        p1 = NULL;
        kfree(p1);

        kmem_full_dump();

        kfree(p2);
        p2 = NULL;

        p1 = kcalloc(2, 64);
	p1 = krealloc(p1, 128);
	kprint("krealloc complited");
        kmem_full_dump();

       
        kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);
	p0 = krealloc (p0, 2);

	kmem_full_dump();

        kfree(p0);
        
        kmem_full_dump();
        
        kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);

        kfree(p1);
        kfree(p2);
        kfree(p3);
        kfree(p4);

        kmem_full_dump();

        return 0;

}

