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

rbuffer* create_rbuffer (uint8_t FLAGS) {
	rbuffer* buffer = (rbuffer*) kcalloc (1, sizeof (rbuffer));
	buffer->flags = FLAGS;
	int i = 0;
	node* prev = (node*) kcalloc (1, sizeof (node));
	prev->data = 0;
	buffer->id_in = prev;
	buffer->id_out = prev;
	for (i = 1; i < RING_BUFFER_SIZE; i++) {
		node* nd = (node*) kcalloc (1, sizeof (node));
		prev->next = nd;
		nd->prev = prev;
		nd->data = 0;
		prev = nd;	
	}
	prev->next = buffer->id_in;
	buffer->id_in->prev = prev;
	return buffer;
}

void free_rbuffer (rbuffer* buffer) {

	if (buffer == NULL) {
		errno = ENOMEM;
#ifndef DEBUG_MEM
	kprint ("Incorrect buffer address");
#endif
		return NULL;
	}

	while (buffer->id_in->next != NULL)
	{
		buffer->id_in = buffer->id_in->next;
		kfree (buffer->id_in->prev);
	}
	kfree (buffer->id_in);
	kfree (buffer);
}


void dump_rbuffer (rbuffer* buffer, void (*data_dump)(void* data)) {

	if (buffer == NULL) {
		errno = ENOMEM;
#ifndef DEBUG_MEM
	kprint ("Incorrect buffer address");
#endif
		return NULL;
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
		
		data_dump (tmp->data);
		tmp = tmp->next;
	} while (tmp != buffer->id_in);
	kprint ("Is full      : %d\r\n", buffer->flags & RBUFFER_IS_FULL);
	kprint ("Is empty     : %d\r\n", buffer->flags & RBUFFER_IS_EMPTY);
	kprint ("Is protected : %d\r\n", buffer->flags & RBUFFER_IS_UNDER_PROTECTION);
	kprint ("Is overflow  : %d\r\n", buffer->flags & RBUFFER_IS_OVERFLOW);
}

int write_data (rbuffer* buffer, void* data) {
	if (buffer == NULL) {
		errno = ENOMEM;
#ifndef DEBUG_MEM
	kprint ("Incorrect buffer address");
#endif
		return 0;
	}
	if (buffer->flags & RBUFFER_IS_FULL) {
		if (buffer->flags & RBUFFER_IS_UNDER_PROTECTION) {
#ifdef DEBUG
	kprint ("Can't write data. Buffer is full and protected. Lose data...");
#endif
			return 0;
		}
		buffer->flags = buffer->flags | RBUFFER_IS_OVERFLOW;
	}
	buffer->id_in->data = data;
	buffer->id_in = buffer->id_in->next;

	if (buffer->flags & RBUFFER_IS_OVERFLOW)
		buffer->id_out = buffer->id_out->next;
	
	if (buffer->flags & RBUFFER_IS_EMPTY)
		buffer->flags = buffer->flags & (~RBUFFER_IS_EMPTY);

	if (buffer->id_in->next == buffer->id_out) 
		buffer->flags = buffer->flags | RBUFFER_IS_FULL;

	return 1;
}

void* read_data (rbuffer* buffer) {
	if (buffer == NULL) {
		errno = ENOMEM;
#ifndef DEBUG_MEM
	kprint ("Incorrect buffer address");
#endif
		return NULL;
	}

	if (buffer->flags & RBUFFER_IS_EMPTY) {
#ifdef DEBUG
	kprint ("Can't read from empty buffer");
#endif
		return NULL;
	}

	void* data = buffer->id_out->data;
	buffer->id_out = buffer->id_out->next;
	if (buffer->flags & RBUFFER_IS_FULL) {
		buffer->flags = buffer->flags & (~RBUFFER_IS_FULL);
		buffer->flags = buffer->flags & (~RBUFFER_IS_OVERFLOW);
	}

	if (buffer->id_out->next == buffer->id_in)
		buffer->flags = buffer->flags | RBUFFER_IS_EMPTY;

	return data;
}


