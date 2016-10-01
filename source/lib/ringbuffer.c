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

#include "lib/ringbuffer.h"

rbuffer* create_rbuffer (sflag_t FLAGS, size_t size) {
	if (size < 1) {
#ifdef DEBUG
	kprint ("Incorrect ringbuffer size. It must be larger then 0.\r\n");
#endif
		return NULL;
	}

	rbuffer* buffer = (rbuffer *) kcalloc (1, sizeof (rbuffer));
	buffer->flags = FLAGS | RBUFFER_IS_EMPTY;
	buffer->size = size;
	dword i = 0;
	node* prev = (node *) kcalloc (1, sizeof (node));
	prev->rbdata = (rdata *) kcalloc (1, sizeof (rdata));
	prev->rbdata->data = NULL;
	prev->rbdata->size = 0;
	buffer->id_in = prev;
	buffer->id_out = prev;
	for (i = 1; i < size; i++) {
		node* nd = (node *) kcalloc (1, sizeof (node));
		prev->next = nd;
		nd->prev = prev;
		nd->rbdata = (rdata *) kcalloc (1, sizeof (rdata));
		nd->rbdata->data = NULL;
		nd->rbdata->size = 0;
		prev = nd;	
	}
	prev->next = buffer->id_in;
	buffer->id_in->prev = prev;
	return buffer;
}

void free_rbuffer (rbuffer* buffer) {

	if (buffer == NULL) {
		errno = ENOMEM;
#ifdef DEBUG_MEM
	kprint ("Incorrect buffer address\r\n");
#endif
		return;
	}
	
	node* iter_node = buffer->id_in;
	dword i = 1;
	for (i = 1; i < buffer->size; i++) {
		iter_node = iter_node->next;
		kfree (iter_node->prev->rbdata->data);
		kfree (iter_node->prev->rbdata);
		kfree (iter_node->prev);
	}
	kfree (iter_node->rbdata->data);
	kfree (iter_node->rbdata);
	kfree (iter_node);
	kfree (buffer);
}


void dump_rbuffer (rbuffer* buffer, void (*data_dump)(void* data)) {

	if (buffer == NULL) {
		errno = ENOMEM;
#ifdef DEBUG_MEM
	kprint ("Incorrect buffer address\r\n");
#endif
		return;
	}

	node* tmp = buffer->id_in;
	do
	{
		if (tmp == buffer->id_in)
			kprint ("ID_IN  : ");
		else if (tmp == buffer->id_out)
			kprint ("ID_OUT : ");
		else
			kprint ("INODE  : ");
		if (tmp->rbdata->data != NULL)
			data_dump (tmp->rbdata->data);
		else
			kprint ("NO DATA\r\n");
		tmp = tmp->next;
	} while (tmp != buffer->id_in);
	kprint ("Is full      : %d\r\n", FLAG_DUMP(buffer->flags & RBUFFER_IS_FULL));
	kprint ("Is empty     : %d\r\n", FLAG_DUMP(buffer->flags & RBUFFER_IS_EMPTY));
	kprint ("Is protected : %d\r\n", FLAG_DUMP(buffer->flags & RBUFFER_IS_UNDER_PROTECTION));
	kprint ("Is overflow  : %d\r\n", FLAG_DUMP(buffer->flags & RBUFFER_IS_OVERFLOW));
}

byte write_data (rbuffer* buffer, void* data, size_t size) {
	if (buffer == NULL) {
		errno = ENOMEM;
#ifdef DEBUG_MEM
	kprint ("Incorrect buffer address\r\n");
#endif
		return ENOMEM;
	}

	if (buffer->flags & RBUFFER_IS_FULL) {
		if (buffer->flags & RBUFFER_IS_UNDER_PROTECTION) {
#ifdef DEBUG
	kprint ("Can't write data. Buffer is full and protected. Lose data...\r\n");
#endif
			return 1;
		}
		if (!(buffer->flags & RBUFFER_IS_OVERFLOW)) {
			buffer->flags = buffer->flags | RBUFFER_IS_OVERFLOW;
			buffer->id_out = buffer->id_out->next;
			kfree (buffer->id_out->prev->rbdata->data);
			buffer->id_out->prev->rbdata->size = 0;
		}
	}

	if (buffer->id_in->next == buffer->id_out) 
		buffer->flags = buffer->flags | RBUFFER_IS_FULL;

	buffer->id_in->rbdata->data = (void *) kcalloc (size, sizeof (char));
	buffer->id_in->rbdata->size = size;
	memcpy (data, buffer->id_in->rbdata->data, size);

	if (buffer->flags & RBUFFER_IS_OVERFLOW) {
		buffer->id_out = buffer->id_out->next;
		kfree (buffer->id_out->prev->rbdata->data);
		buffer->id_out->prev->rbdata->size = 0;
	}
	buffer->id_in = buffer->id_in->next;
	
	if (buffer->flags & RBUFFER_IS_EMPTY)
		buffer->flags = buffer->flags & (~RBUFFER_IS_EMPTY);

	return 0;
}

byte read_data (rbuffer* buffer, void* data) {
	if (buffer == NULL) {
		errno = ENOMEM;
#ifdef DEBUG_MEM
	kprint ("Incorrect buffer address\r\n");
#endif
		return ENOMEM;
	}

	if (buffer->flags & RBUFFER_IS_EMPTY) {
#ifdef DEBUG
	kprint ("Can't read from empty buffer\r\n");
#endif
		return 1;
	}
	//TODO Create all "buckets" rbdata->data on kernel init and no free then??? for optimize
	memcpy (buffer->id_out->rbdata->data, data, buffer->id_out->rbdata->size);
	kfree (buffer->id_out->rbdata->data);
	buffer->id_out->rbdata->size = 0;

	buffer->id_out = buffer->id_out->next;

	if (buffer->flags & RBUFFER_IS_FULL) {
		buffer->flags = buffer->flags & (~RBUFFER_IS_FULL);
		buffer->flags = buffer->flags & (~RBUFFER_IS_OVERFLOW);
	}

	if (buffer->id_out == buffer->id_in)
		buffer->flags = buffer->flags | RBUFFER_IS_EMPTY;


	return 0;
}

