#ifndef __BLOCK__
#define __BLOCK__

#include <stdint.h>
#include <stddef.h>

#define MREAD_SUPPORT 0
#define MWRITE_SUPPORT 1

#define IS_DEV_SUPPORT(dev, feature) ((dev)->info & (1 << (feature)))

enum dev_type {
        BLOCK_UNDEFINED = 0,
        BLOCK_EMMC
};

struct block_dev_t {

        char* dev_name;
        unsigned long driver_id;
        uint8_t* dev_id;
        uint32_t dev_id_len;
        uint32_t info;

        size_t block_size;
        size_t num_blocks;

        void* dev;

        size_t (*read) (struct block_dev_t* dev, uint8_t* buf, 
                        size_t buf_size, uint32_t block_num);
        size_t (*write) (struct block_dev_t* dev, uint8_t* buf, 
                         size_t buf_size, uint32_t block_num);
        int (*init)  (struct block_dev_t* dev);

};

typedef struct block_dev_t block_dev;

size_t block_read (block_dev *dev, uint8_t *buf, size_t buf_size, uint32_t starting_block);

size_t block_write (block_dev *dev, uint8_t *buf, size_t buf_size, uint32_t starting_block);

#endif
