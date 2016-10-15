#include "test/test.h"

int sd_test() {

	byte* fake_buffer;
	byte* buffer;
	int i = 0;
	int j = 0;


	fake_buffer = (byte*) kmalloc (2 * PAGE_SIZE);
	buffer = (byte*) (((dword) fake_buffer & (~0xFFF)) + PAGE_SIZE);
	kprint ("Buffer %p\r\n", buffer);

	block_read(&block_dev_table[SD_CARD], buffer, PAGE_SIZE, 0);
	
	kprint ("Successeful read\r\n");
	
	for (i = 0; i < 128; ++i) {
		for (j = 0; j < 32; ++j) {
			kprint("%x ", buffer[32 * i + j]);
		}
		kprint("\r\n");
	}
	buffer[0] = 0xE;
	buffer[1] = 0xDA;
	block_write(&block_dev_table[SD_CARD], buffer, PAGE_SIZE, 0);
	block_read(&block_dev_table[SD_CARD], buffer, PAGE_SIZE, 0);

	for (i = 0; i < 128; ++i) {
		for (j = 0; j < 32; ++j) {
			kprint("%x ", buffer[32 * i + j]);
		}
		kprint("\r\n");
	}

	if (buffer[0] == 0xE && buffer[1] == 0xDA)
		kprint ("Successeful write\r\n");
	else 
		return -1;

	return 0;
}

