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
#ifndef __HEAP__
#define __HEAP__

#include <bcm2836/defines.h>
#include <lib/error.h>
#include <lib/nostdio.h>
#include <stddef.h>
#include <stdint.h>

#define HEAP_LIST_SIZE 0x00000400
#define KERNEL_HEAP_START_SIZE 0x00010000

#define DEBUG

#define AREA_SIZE(area) (area->end - area->begin + 1)

typedef struct phys_area_info_t {

        void* begin; /* if begin = NULL this struct not used */
        void* end;
        struct phys_area_info_t* next;
        int owner; /*-1 for free, 
                     0 for kernel, PID for others */

} phys_area_info;

typedef struct {
        
        phys_area_info list[HEAP_LIST_SIZE];
        /* phys_area_info* last_elem; */
        phys_area_info* first_elem;
        size_t cur_size;

} phys_area_list;

extern phys_area_list* heap_list;

int phys_area_init(phys_area_list* new_list, phys_area_info* info_arr, 
                   size_t start_kheap_size);

void* phys_page_alloc(uint32_t n, uint32_t owner);

void* phys_page_realloc(void* old_page, uint32_t new_n, uint32_t new_owner);

int phys_page_free(void* page_addr);

phys_area_info* phys_list_free_elem();

phys_area_info* phys_list_findb_elem(void* begin);

phys_area_info* phys_list_finde_elem(void* end);

phys_area_info* phys_list_findn_elem(phys_area_info* next);

phys_area_info* phys_list_findb_pelem(void* begin);

phys_area_info* phys_list_finde_pelem(void* end);

/* phys_list_findX_elem - X may be:
 * e - end
 * b - begin
 * n - next
 * !Its find pre-elem
 */

int phys_list_del_elem(phys_area_info* old_elem);


#define phys_area_info_init(new_info, new_begin,  new_end, new_owner, new_next)\
        (new_info)->begin = (new_begin); \
        (new_info)->end = (new_end); \
        (new_info)->owner = (new_owner); \
        (new_info)->next = (new_next); 

#ifdef DEBUG

int phys_area_info_dump(phys_area_info* info);

int phys_area_list_dump(void);

#endif

#endif
