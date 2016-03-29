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

#include <lib/nostdio.h>
#include <lib/nostdlib.h>
#include <lib/error.h>
#include <lib/string.h>

#include <mm/heap.h>

#define CHUNK_INIT(kchunk, nnext, nprev, nsize, narea_size) \
        (kchunk)->next = (nnext); \
        (kchunk)->prev = (nprev); \
        (kchunk)->size = (nsize); \
        (kchunk)->area_size = (narea_size);

struct kmem_chunk_t {
        struct kmem_chunk_t* next;
        struct kmem_chunk_t* prev;
        size_t size;
        size_t area_size;         /* if area_size == 0 its 
                                     first chunk in memory area
                                     if area_size != 0 && size == 0
                                     it is last chunk in memory area */

};

typedef struct kmem_chunk_t kmem_chunk;

static kmem_chunk* kernel_heap = NULL; 

#define IS_BEGIN(c_chunk) ((c_chunk)->area_size != 0)

#define IS_END(c_chunk) ((c_chunk)->area_size == 0 && (c_chunk)->size == 0)

#define FREE_AFTER(c_chunk)   (IS_END(c_chunk) ? \
                                0 : (size_t) \
                                (((void*) (c_chunk)->next - (void*) (c_chunk)) \
                                - (c_chunk)->size - sizeof(kmem_chunk)))

/* ^ This macro return 0 if it is end page chunk
 * | and return free space after chunk for common chunk
 */

#define POISON -66

static int kmem_chunk_dump(kmem_chunk* ch)
{
        if (ch == NULL) {
                kprint("ch = NULL\r\n");
                errno = EINVAL;
                return -1;
        }

        kprint("Kernel memory chunk info:\r\n"
                "ch_addr:    %p\r\n"
                "begin:      %p\r\n"
                "size:       %d\r\n"
                "area_size:  %d\r\n"
                "next:       %p\r\n"
                "prev:       %p\r\n", ch,(void*) ch + sizeof(kmem_chunk),
                ch->size, ch->area_size, ch->next, ch->prev);

        return 0;
}

static int page_chunk_init(phys_area_info* elem, kmem_chunk* next
                                               , kmem_chunk* prev)
{
        kmem_chunk* a_begin = elem->begin;
        kmem_chunk* a_end = elem->end - sizeof(kmem_chunk) + 1;

        if (elem == NULL) kdie("page_chunk_init: elem == NULL");

        a_begin->prev = prev;
        a_begin->next = a_end;
        a_begin->size = 0;
        a_begin->area_size = AREA_SIZE(elem);

        a_end->next = next;
        a_end->prev = a_begin;
        a_end->size = 0;
        a_end->area_size = 0;

#ifdef TEDIOS_MAL_DEBUG
        kprint("Area is initialized.\r\n"
               "Begin chunk:\r\n"); 
        kmem_chunk_dump(a_begin);
        kprint("End chunk:\r\n"); 
        kmem_chunk_dump(a_end);
#endif

        return 0;
}

static int kmem_init()
{
        if (heap_list == NULL) {
                errno = EINVAL;
                kdie("Trying to use kmalloc before heap init\r\n");
                return -1;
        }

        kernel_heap = (kmem_chunk*) heap_list->first_elem->begin;
        page_chunk_init(heap_list->first_elem, NULL, NULL);
#ifdef TEDIOS_MAL_DEBUG
                kprint("Kernel heap succesfully initialized\r\n"
                        "Kernel heap pointer: %p\r\n", kernel_heap);
#endif

        return 0;
}

void* kmalloc(size_t size)
{
        kmem_chunk* cur_elem;
        kmem_chunk* new_elem;

        size = (size % sizeof(dword)) ? 
                (size / sizeof(dword) + 1) * sizeof(dword) :
                size;
        
        if (kernel_heap == NULL) {
                kmem_init(); /* if kernel_heap is NULL */
                             /* we need initialization */
                if (kernel_heap == NULL) kdie("Can't init kernel heap.");

                if ((kernel_heap->area_size - 2 * sizeof(kmem_chunk)) >= size) {
                        kernel_heap->size = size;
#ifdef TEDIOS_MAL_DEBUG
                        kprint("Memory first allocation with size %u\r\n", size);
                        kmem_chunk_dump(kernel_heap);
#endif
                        return ((void*) kernel_heap + sizeof(kmem_chunk));
                } else {
                        errno = ENOMEM;
                        return NULL;
                }
        }

        if (size == 0) return NULL;

        cur_elem = kernel_heap;
        
        while (!(cur_elem == NULL || FREE_AFTER(cur_elem) 
                 >= (size + sizeof(kmem_chunk)))) {
              cur_elem = cur_elem->next;
        }
#ifdef TEDIOS_MAL_DEBUG
        kprint("I found FREE SPACE! (or end :) )\r\n"
                "Chunk addr: %p\r\n"
                "Chunk size: %x\r\n"
                "Free size:  %x\r\n", cur_elem, cur_elem->size,
                FREE_AFTER(cur_elem));
#endif
        if (cur_elem == NULL) return NULL;

        new_elem = (kmem_chunk*) ((void*) cur_elem 
                                  + cur_elem->size + sizeof(kmem_chunk));

        CHUNK_INIT(new_elem,
                   cur_elem->next,
                   cur_elem,
                   size,
                   0)

        cur_elem->next->prev = new_elem;
        cur_elem->next = new_elem;

#ifdef TEDIOS_MAL_DEBUG
        kprint("Memory was allocated with size %d\r\n", size);
        kmem_chunk_dump(new_elem);
#endif

        return ((void*) new_elem + sizeof(kmem_chunk));
}

void* kcalloc(int n, size_t size)
{
        void* mem;

        if (n < 0) {
                errno = EINVAL;
                kdie("kcalloc get negative n");
        }

        mem = kmalloc(n * size);

        if (mem == NULL) return NULL;

        memset(mem, 0, n * size);

        return mem;
}

void* krealloc(void* block, size_t size)
{
	kmem_chunk* re_elem;

	if (block == NULL) return NULL;
      
	re_elem = block - sizeof (kmem_chunk);
	
	if (re_elem->area_size != 0 && re_elem->size == 0)
		return NULL;

	if (size < 0) {
		errno = EINVAL;
		kdie("krealloc get negative size");
	}
	
	if (size > re_elem->size) {

		if (FREE_AFTER(re_elem) >= size - re_elem->size) {
			re_elem->size = size;
			return (void*) re_elem;
		} else if (re_elem->area_size != 0) {
			
			void* new_elem = kmalloc (size);
			if (new_elem == NULL) return NULL;

			memcpy ((void*) re_elem, (void*) new_elem, re_elem->size);
			kfree ((void*) re_elem);
			return (void*) new_elem;
		}

	} else {		
		re_elem->size = size;
		return (void*) re_elem;
	}	 
        return NULL;
}

int kfree(void* block)
{
        kmem_chunk* del_elem;
        if (block == NULL) return 0;

        del_elem = block - sizeof(kmem_chunk);

        if (IS_BEGIN(del_elem)) {
                del_elem->size = 0;
                return 0;
        }

        del_elem->prev->next = del_elem->next;
        del_elem->next->prev = del_elem->prev;

        memset(del_elem, POISON, sizeof(kmem_chunk));
#ifdef TEDIOS_MAL_DEBUG
                kprint("Chunk has made free: %p\r\n", del_elem);
#endif
        return 0;
}

int kmem_full_dump()
{
        kmem_chunk* cur_elem = kernel_heap;
        if (cur_elem == NULL) {
                kprint("Kernel memory heap is NULL\r\n");
                return -1;
        }

        kprint("Full kernel heap dump:\r\n"
                "Kernel heap:   %p\r\n\r\n", kernel_heap);

        while (cur_elem != NULL) {
                kmem_chunk_dump(cur_elem);
                cur_elem = cur_elem->next;
        }

        return 0;
}
