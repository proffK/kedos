#include <fs/block.h>
#include <lib/nostdio.h>
#include <lib/nostdlib.h>
#include <lib/error.h>

size_t block_read (block_dev* dev, uint8_t* buf, size_t buf_size, uint32_t starting_block)
{
        size_t ret_val = 0;

        if (dev == NULL) kdie("NULL dev pointer");
        if (buf == NULL) kdie("Try read to NULL buf pointer");

        if (starting_block >= dev->num_blocks) {
                kdie("Incorrect block number");
        }

        if (dev->read == NULL) {
#ifdef TEDIOS_BLOCK_DEBUG
                kprint("Reading functions not implemented for dev %s\r\n",
                        dev->dev_name);
#endif
                errno = ENOTSUP;
                return -1;
        }

        if (buf_size == 0) return 0;

#ifdef TEDIOS_BLOCK_DEBUG
        if (buf_size % dev->block_size != 0) {
                kprint("Warning:\r\n"
                        "block_read: buf_size %% block_size != 0!");
        }
#endif

        if (IS_DEV_SUPPORT(dev, MREAD_SUPPORT)) {
                return dev->read(dev, buf, buf_size, starting_block);
        }

        while (buf_size != 0) {

                ret_val += dev->read(dev, buf, 
                                     dev->block_size, starting_block);

                buf_size -= dev->block_size;
                buf += dev->block_size;

                if (buf_size <= dev->block_size) buf_size = 0;
                starting_block++;

        }

        return ret_val;
}

size_t block_write (block_dev* dev, uint8_t* buf, 
                    size_t buf_size, uint32_t starting_block)
{
        size_t ret_val = 0;

        if (dev == NULL) kdie("NULL dev pointer");
        if (buf == NULL) kdie("Try write to NULL buf pointer");

        if (starting_block >= dev->num_blocks) {
                kdie("Incorrect block number");
        }

        if (dev->write == NULL) {
#ifdef TEDIOS_BLOCK_DEBUG
                kprint("Writing functions not implemented for dev %s\r\n",
                        dev->dev_name);
#endif
                errno = ENOTSUP;
                return -1;
        }

        if (buf_size == 0) return 0;

#ifdef TEDIOS_BLOCK_DEBUG
        if (buf_size % dev->block_size != 0) {
                kprint("Warning:\r\n"
                        "block_write: buf_size %% block_size != 0!");
        }
#endif

        if (IS_DEV_SUPPORT(dev, MWRITE_SUPPORT)) {
                return dev->write(dev, buf, buf_size, starting_block);
        }

        while (buf_size != 0) {

                ret_val += dev->write(dev, buf, 
                                     dev->block_size, starting_block);

                buf_size -= dev->block_size;
                buf += dev->block_size;

                if (buf_size <= dev->block_size) buf_size = 0;
                starting_block++;

        }

        return ret_val;
}
