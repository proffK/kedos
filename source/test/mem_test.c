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

int mem_test()
{
        void* p0;
        void* p1;
        void* p2;
        void* p3;
        void* p4;

        p0 = phys_page_alloc(5, 1);
        p1 = phys_page_alloc(6, 2);
        p2 = phys_page_alloc(6, 3);
        p3 = phys_page_alloc(7, 4);
        p4 = phys_page_alloc(3, 5);

        kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);

        phys_area_list_dump();

	p1 = phys_page_realloc (p1, 7, 2);
	p0 = phys_page_realloc (p1, 7, 1);
	p2 = phys_page_realloc (p1, 3, 3);

	 kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);

        phys_area_list_dump();

        phys_page_free(p1);
        phys_page_free(p2);

        phys_area_list_dump();

        p1 = phys_page_alloc(8, 4);

        kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);

	

        phys_area_list_dump();

	

        p2 = phys_page_alloc(4, 3);

        kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);

        phys_area_list_dump();

        phys_page_free(p3);

        kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);

        phys_area_list_dump();

        phys_page_free(p4);

        kprint("p0: %p\r\np1: %p\r\n"
                "p2: %p\r\np3: %p\r\n"
                "p4: %p\r\n", p0, p1, p2, p3, p4);

        phys_area_list_dump();

        return 0;
}
