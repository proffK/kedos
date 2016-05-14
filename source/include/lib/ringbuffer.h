#ifndef __RINGBUFFER__
#define __RINGBUFFER__


#include "lib/nostdlib.h"
#include "lib/nostdio.h"

typedef struct node_t {
	void* data;
	struct node_t* next;
	struct node_t* prev;
} node;

typedef struct rbuffer_t {
	uint8_t flags;  //1st bit - buffer is full
			//2nd bit - buffer is empty
			//3rd bit - buffer protected from overflow
			//4th bit - buffer is overflow
	uint32_t size;
	node* id_in;
	node* id_out;
} rbuffer;

rbuffer* create_rbuffer (uint8_t FLAGS);

void free_rbuffer (rbuffer* buffer);

void dump_rbuffer (rbuffer* buffer, void (*data_dump)(void* data));

int write_data (rbuffer* buffer, void* data);

void* read_data (rbuffer* buffer);

#endif
