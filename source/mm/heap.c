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

#include <mm/heap.h>

#define KERNEL 0
#define FREE -1

#define DEBUG_MEM

phys_area_list* heap_list;

int phys_area_init(phys_area_list* new_list, phys_area_info* info_arr, 
                   size_t start_kheap_size)
{
        int i;

        for (i = 0; i < HEAP_LIST_SIZE; ++i) {

                (new_list->list[i]).begin = NULL;

        }

        new_list->first_elem=info_arr;

        phys_area_info_init(new_list->first_elem, 
                            HEAP_START,
                            (HEAP_START + start_kheap_size - 1), 
                            KERNEL, 
                            &info_arr[1]);

        phys_area_info_init(&info_arr[1], 
                            new_list->first_elem->end + 1,
                            HEAP_END,
                            FREE,
                            NULL);

        heap_list = new_list;
        heap_list->cur_size = 2;

#ifdef DEBUG_MEM
        phys_area_list_dump();
#endif

        return 0;
}

/* --------------------------------------------------------------------------
 *                           all heap
 * ( kernel_heap )(                     free                               )
 */

void* phys_page_alloc(uint32_t n, uint32_t owner)
{
        phys_area_info* cur_elem = heap_list->first_elem;
        
        while (!(cur_elem == NULL || 
                (cur_elem->owner == FREE && 
                AREA_SIZE(cur_elem) > n * PAGE_SIZE) 
                )) {

                cur_elem = cur_elem->next;

        }

        if (!cur_elem) {
                errno = ENOMEM;
#ifdef DEBUG_MEM
                kprint("No free page area!\r\n");
#endif
                return NULL;
        }

        if (n * PAGE_SIZE == AREA_SIZE(cur_elem)) {
                cur_elem->owner = owner;
        } else {
                phys_area_info* new_info = phys_list_free_elem();

                if (!(new_info)) {
                        errno = ENOMEM;
#ifdef DEBUG_MEM
                kprint("No free elem in heap list!\r\n");
#endif
                        return NULL;
                }

                phys_area_info_init(new_info,
                                    cur_elem->begin + n * PAGE_SIZE,
                                    cur_elem->end,
                                    FREE,
                                    cur_elem->next);

                phys_area_info_init(cur_elem,
                                    cur_elem->begin,
                                    cur_elem->begin + n * PAGE_SIZE - 1,
                                    owner,
                                    new_info);

                heap_list->cur_size++;
        }

        return cur_elem->begin;

}

void* phys_page_realloc(void* old_page, uint32_t new_n, uint32_t new_owner)
{	
	if (old_page == NULL) {

		errno = ENOMEM;
#ifdef DEBUG_MEM
	kprint("Incorrect old_page address\r\n");
#endif
                return NULL;
	}
	if (new_owner == 0) {
#ifdef DEBUG_MEM
	kprint ("Kernel can't realloc memory\r\n");
#endif
		return NULL;
	}
	
	if (new_owner == -1 || new_n == 0) {
		phys_page_free (old_page);
		return NULL;
	}

	phys_area_info* cur_page = phys_list_findb_elem (old_page);
	uint32_t old_n = AREA_SIZE (cur_page) / PAGE_SIZE;
	if (new_n > old_n) {
		if (cur_page->next != 0 &&
		    cur_page->next->owner == -1 &&
		    AREA_SIZE (cur_page->next) > (new_n - old_n) * PAGE_SIZE) {

			cur_page->end += (new_n - old_n) * PAGE_SIZE;
			cur_page->owner = new_owner;
			return cur_page->begin;
		} else {
			void* new_page = phys_page_alloc (new_n, new_owner);
			if (!new_page) {
				errno = ENOMEM;
#ifdef DEBUG_MEM
	kprint("No free page area!\r\n");
#endif
				return NULL;
			}

			memcpy (cur_page->begin, new_page, old_n * PAGE_SIZE);

			phys_page_free (cur_page->begin);
			return new_page;
		}
	} else {
		cur_page->end += (new_n - old_n) * PAGE_SIZE;
		cur_page->owner = new_owner;
		return cur_page->begin;
	}
        return NULL;
}

int phys_page_free(void* page_addr)
{
        phys_area_info* prev;
        phys_area_info* cur;
        phys_area_info* next;

        if (page_addr == NULL) {
                errno = EINVAL;
                return -1;
        }

        if ((prev = phys_list_findb_pelem(page_addr)) == NULL) {
                errno = EINVAL;
                return -1;
        }

        cur = prev->next;
        next = cur->next;

        if (next == NULL) {
                if (prev->owner != FREE) {
                        cur->owner = FREE;
                        return 0;
                } else {
                        prev->end = cur->end;
                        prev->next = next;
                        cur->begin = NULL;
                        heap_list->cur_size--;
                        return 0;
                }
        }

        if (prev->owner == FREE) {
                if (next->owner == FREE) {
                        prev->next = next->next;
                        prev->end = next->end;
                        cur->begin = NULL;
                        next->begin = NULL;
                        heap_list->cur_size--;
                        heap_list->cur_size--;
                        return 0;
                } else {
                        prev->next = next;
                        prev->end = cur->end;
                        cur->begin = NULL;
                        heap_list->cur_size--;
                        return 0;
                }
        } else {
                if (next->owner == FREE) {
                        prev->next = next;
                        next->begin = cur->begin;
                        cur->begin = NULL;
                        heap_list->cur_size--;
                        return 0;
                } else {
                        cur->owner = FREE;
                        return 0;
                }
        }
                        
        return -1;
}

phys_area_info* phys_list_free_elem()
{
        int i;

        for (i = 0; i < HEAP_LIST_SIZE; ++i) {

                if (heap_list->list[i].begin == NULL) {
                        return heap_list->list + i;
                }
        }

        return NULL;
}

phys_area_info* phys_list_findb_elem(void* begin)
{
        phys_area_info* cur_elem = heap_list->first_elem;

        while (!(cur_elem == NULL || cur_elem->begin == begin)) {
                cur_elem = cur_elem->next;
        }

        return cur_elem;
}


phys_area_info* phys_list_finde_elem(void* end)
{
        phys_area_info* cur_elem = heap_list->first_elem;

        while (!(cur_elem == NULL || cur_elem->end == end)) {
                cur_elem = cur_elem->next;
        }

        return cur_elem;
}

phys_area_info* phys_list_findn_elem(phys_area_info* next)
{
        phys_area_info* cur_elem = heap_list->first_elem;

        while (!(cur_elem == NULL || cur_elem->next == next)) {
                cur_elem = cur_elem->next;
        }

        return cur_elem;
}

phys_area_info* phys_list_findb_pelem(void* begin)
{
        phys_area_info* cur_elem = heap_list->first_elem;

        if (cur_elem->begin == begin) return NULL;

        while (!(cur_elem->next == NULL || cur_elem->next->begin == begin)) {
                cur_elem = cur_elem->next;
        }

        return cur_elem;
}

phys_area_info* phys_list_finde_pelem(void* end)
{
        phys_area_info* cur_elem = heap_list->first_elem;

        if (cur_elem->end == end) return NULL;

        while (!(cur_elem->next == NULL || cur_elem->next->end == end)) {
                cur_elem = cur_elem->next;
        }

        return cur_elem;
}

#ifdef DEBUG

int phys_area_info_dump(phys_area_info* info) 
{
        if (info == NULL) {
                errno = EINVAL;
                return -1;
        }

        kprint("\r\nMemory area info dump:\r\n"
                "Address in heap list:  %p\r\n"
                "Index in heap list:    %d\r\n" 
                "Area begin:            %p\r\n"
                "Area end:              %p\r\n"
                "Area size:             %d\r\n"
                "Area next:             %p\r\n"
                "Area owner:            %d\r\n", info,
                (int) ((void*) info - (void*) heap_list) / 
                sizeof(phys_area_info),
                info->begin, info->end, AREA_SIZE(info),
                info->next, info->owner);

        if (info->owner == FREE) {
                kprint("Free area\r\n");
        } else if (info->owner == KERNEL) {
                kprint("Kernel area\r\n");
        }

        return 0;
}

int phys_area_list_dump()
{
        phys_area_info* cur;

        if (heap_list == NULL || heap_list->first_elem == NULL) {
                kprint("Invalid heap list\r\n");
                errno = EINVAL;
                return -1;
        }

        cur = heap_list->first_elem;

        kprint("Heap list dump:\r\n"
                "Heap list address:     %p\r\n"
                "Heap list first elem:  %p\r\n"
                "Heap list size:         %d\r\n"
                "Heap list areas:\r\n",
                heap_list, heap_list->first_elem, heap_list->cur_size);
                
        while (cur != NULL) {
                phys_area_info_dump(cur);
                cur = cur->next;
        }

        return 0;
}
#endif
