#ifndef __RINGBUFFER__
#define __RINGBUFFER__


#include "lib/nostdlib.h"
#include "lib/nostdio.h"

typedef struct rdata_t { 
	void* data;
	size_t size;
} rdata;

typedef struct node_t {
	rdata* rbdata;
	struct node_t* next;
	struct node_t* prev;
} node;

typedef struct rbuffer_t {
	sflag_t flags;  //1st bit - buffer is full
			//2nd bit - buffer is empty
			//3rd bit - buffer protected from overflow
			//4th bit - buffer is overflow
	dword size;
	node* id_in;
	node* id_out;
} rbuffer;

rbuffer* create_rbuffer (sflag_t FLAGS, size_t size);

void free_rbuffer (rbuffer* buffer);

void dump_rbuffer (rbuffer* buffer, void (*data_dump)(void* data));

byte write_data (rbuffer* buffer, void* data, size_t size);

byte read_data (rbuffer* buffer, void* data);

#endif
