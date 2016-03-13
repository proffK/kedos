#include <bcm2836/mbox.h>
#include <bcm2836/mmio.h>
#include <bcm2836/timer.h>
#include <lib/nostdio.h>

#define MAILBOX_FULL   0x80000000
#define MAILBOX_EMPTY  0x40000000

//volatile mailbox_t* gmailbox = (mailbox_t*) MBOX_BASE;

#define gmailbox ((mailbox_t*) MBOX_BASE)

uint32_t mbox_read(uint8_t chan)
{
        uint32_t data = 0;
        while (1) {
                while (gmailbox->status & MAILBOX_EMPTY) {
                        kprint("status: %x\n\r", gmailbox->status);
                        memory_barier() ;
                }
                data = gmailbox->read;

#ifdef MBOX_DEBUG
                kprint("Recived: %x", data);
#endif
                if (((uint8_t) data & 0xf) == chan) {
                        return (data & ~0xf);
                }
        }
}

void mbox_write(uint8_t chan, uint32_t data)
{
        while (gmailbox->status & MAILBOX_FULL) ;

        gmailbox->write = (data & ~0xf) | (uint32_t) (chan & 0xf);
}

void mbox_flush(void) {
        while (!(gmailbox->status & MAILBOX_EMPTY)) {
                usleep(20);
        }
}

