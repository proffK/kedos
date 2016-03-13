/**
 * @file sd.h
 *
 */
/* Copyright (C) 2015, 2016 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
 * Based on
 * https://github.com/jncronin/rpi-boot/blob/master/emmc.c
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SD_H_
#define SD_H_

#include <stdint.h>
#include <stddef.h>
#include <fs/block.h>
#include <bcm2836/videocore.h>
#include <bcm2836/sdhci.h>

#define DEBUG
// Enable EXPERIMENTAL (and possibly DANGEROUS) SD write support
#define SD_WRITE_SUPPORT

#define SD_OK                0
#define SD_ERROR             -1
#define SD_TIMEOUT           -2
#define SD_BUSY              -3
#define SD_NO_RESP           -5
#define SD_ERROR_RESET       -6
#define SD_ERROR_CLOCK       -7
#define SD_ERROR_VOLTAGE     -8
#define SD_ERROR_APP_CMD     -9
#define SD_CARD_CHANGED      -10
#define SD_CARD_ABSENT       -11
#define SD_CARD_REINSERTED   -12

int sd_card_init(block_dev* dev);
size_t sd_read(block_dev* dev, uint8_t* buf, 
			size_t buf_size, uint32_t block_no);

#ifdef SD_WRITE_SUPPORT
size_t sd_write(block_dev* dev, uint8_t* buf, 
                    size_t buf_size, uint32_t block_no);
#endif



#define TIMEOUT_WAIT(stop_if_true, usec) 						\
do {															\
	uint32_t micros_now = sys_timer->counter_lo;						\
	do {														\
		if(stop_if_true)										\
			break;												\
	} while( sys_timer->counter_lo - micros_now < (uint32_t)usec);	\
} while(0);

struct sd_scr {
	uint32_t scr[2];
	uint32_t sd_bus_widths;
	int sd_version;
};

struct emmc_block_dev {
	block_dev* bd;
	uint32_t card_supports_sdhc;
	uint32_t card_supports_18v;
	uint32_t card_ocr;
	uint32_t card_rca;
	uint32_t last_interrupt;
	uint32_t last_error;

	struct sd_scr scr;

	int failed_voltage_switch;

	uint32_t last_cmd_reg;
	uint32_t last_cmd;
	uint32_t last_cmd_success;
	uint32_t last_r0;
	uint32_t last_r1;
	uint32_t last_r2;
	uint32_t last_r3;

	void *buf;
	int blocks_to_transfer;
	size_t block_size;
	int card_removal;
	unsigned base_clock;
};

#define SD_CLOCK_ID         	4000000
#define SD_CLOCK_NORMAL     	25000000
#define SD_CLOCK_HIGH       	50000000
#define SD_CLOCK_100        	100000000
#define SD_CLOCK_208        	208000000

#define SD_VER_UNKNOWN      	0
#define SD_VER_1            	1
#define SD_VER_1_1          	2
#define SD_VER_2            	3
#define SD_VER_3            	4
#define SD_VER_4            	5

#define SD_CMD_INDEX(a)				(uint32_t)((a) << 24)
#define SD_CMD_TYPE_NORMAL			0x0
#define SD_CMD_TYPE_SUSPEND			(1 << 22)
#define SD_CMD_TYPE_RESUME			(2 << 22)
#define SD_CMD_TYPE_ABORT			(3 << 22)
#define SD_CMD_TYPE_MASK			(3 << 22)
#define SD_CMD_ISDATA				(1 << 21)
#define SD_CMD_IXCHK_EN				(1 << 20)
#define SD_CMD_CRCCHK_EN			(1 << 19)
#define SD_CMD_RSPNS_TYPE_NONE		0			// For no response
#define SD_CMD_RSPNS_TYPE_136		(1 << 16)	// For response R2 (with CRC), R3,4 (no CRC)
#define SD_CMD_RSPNS_TYPE_48		(2 << 16)	// For responses R1, R5, R6, R7 (with CRC)
#define SD_CMD_RSPNS_TYPE_48B		(3 << 16)	// For responses R1b, R5b (with CRC)
#define SD_CMD_RSPNS_TYPE_MASK 		(3 << 16)
#define SD_CMD_MULTI_BLOCK			(1 << 5)
#define SD_CMD_DAT_DIR_HC			0
#define SD_CMD_DAT_DIR_CH			(1 << 4)
#define SD_CMD_AUTO_CMD_EN_NONE		0
#define SD_CMD_AUTO_CMD_EN_CMD12	(1 << 2)
#define SD_CMD_AUTO_CMD_EN_CMD23	(2 << 2)
#define SD_CMD_BLKCNT_EN			(1 << 1)
#define SD_CMD_DMA          		1

#define SD_ERR_CMD_TIMEOUT		0
#define SD_ERR_CMD_CRC			1
#define SD_ERR_CMD_END_BIT		2
#define SD_ERR_CMD_INDEX		3
#define SD_ERR_DATA_TIMEOUT		4
#define SD_ERR_DATA_CRC			5
#define SD_ERR_DATA_END_BIT		6
#define SD_ERR_CURRENT_LIMIT	7
#define SD_ERR_AUTO_CMD12		8
#define SD_ERR_ADMA				9
#define SD_ERR_TUNING			10
#define SD_ERR_RSVD				11

#define SD_ERR_MASK_CMD_TIMEOUT		(1 << (16 + SD_ERR_CMD_TIMEOUT))
#define SD_ERR_MASK_CMD_CRC			(1 << (16 + SD_ERR_CMD_CRC))
#define SD_ERR_MASK_CMD_END_BIT		(1 << (16 + SD_ERR_CMD_END_BIT))
#define SD_ERR_MASK_CMD_INDEX		(1 << (16 + SD_ERR_CMD_INDEX))
#define SD_ERR_MASK_DATA_TIMEOUT	(1 << (16 + SD_ERR_CMD_TIMEOUT))
#define SD_ERR_MASK_DATA_CRC		(1 << (16 + SD_ERR_CMD_CRC))
#define SD_ERR_MASK_DATA_END_BIT	(1 << (16 + SD_ERR_CMD_END_BIT))
#define SD_ERR_MASK_CURRENT_LIMIT	(1 << (16 + SD_ERR_CMD_CURRENT_LIMIT))
#define SD_ERR_MASK_AUTO_CMD12		(1 << (16 + SD_ERR_CMD_AUTO_CMD12))
#define SD_ERR_MASK_ADMA			(1 << (16 + SD_ERR_CMD_ADMA))
#define SD_ERR_MASK_TUNING			(1 << (16 + SD_ERR_CMD_TUNING))

#define SD_RESP_NONE        SD_CMD_RSPNS_TYPE_NONE
#define SD_RESP_R1          (SD_CMD_RSPNS_TYPE_48 | SD_CMD_CRCCHK_EN)
#define SD_RESP_R1b         (SD_CMD_RSPNS_TYPE_48B | SD_CMD_CRCCHK_EN)
#define SD_RESP_R2          (SD_CMD_RSPNS_TYPE_136 | SD_CMD_CRCCHK_EN)
#define SD_RESP_R3          SD_CMD_RSPNS_TYPE_48
#define SD_RESP_R4          SD_CMD_RSPNS_TYPE_136
#define SD_RESP_R5          (SD_CMD_RSPNS_TYPE_48 | SD_CMD_CRCCHK_EN)
#define SD_RESP_R5b         (SD_CMD_RSPNS_TYPE_48B | SD_CMD_CRCCHK_EN)
#define SD_RESP_R6          (SD_CMD_RSPNS_TYPE_48 | SD_CMD_CRCCHK_EN)
#define SD_RESP_R7          (SD_CMD_RSPNS_TYPE_48 | SD_CMD_CRCCHK_EN)

#define SD_DATA_READ        (SD_CMD_ISDATA | SD_CMD_DAT_DIR_CH)
#define SD_DATA_WRITE       (SD_CMD_ISDATA | SD_CMD_DAT_DIR_HC)

#define SD_CMD_RESERVED(a)  (uint32_t)0xffffffff

#define SD_COMMAND_COMPLETE		(1 << 0)
#define SD_TRANSFER_COMPLETE	(1 << 1)
#define SD_BLOCK_GAP_EVENT		(1 << 2)
#define SD_DMA_INTERRUPT		(1 << 3)
#define SD_BUFFER_WRITE_READY	(1 << 4)
#define SD_BUFFER_READ_READY	(1 << 5)
#define SD_CARD_INSERTION		(1 << 6)
#define SD_CARD_REMOVAL			(1 << 7)
#define SD_CARD_INTERRUPT		(1 << 8)

#define SUCCESS(a)          	(a->last_cmd_success)
#define FAIL(a)            	 	(a->last_cmd_success == 0)
#define TIMEOUT(a)         		(FAIL(a) && (a->last_error == 0))
#define CMD_TIMEOUT(a)     		(FAIL(a) && (a->last_error & (1 << 16)))
#define CMD_CRC(a)        	 	(FAIL(a) && (a->last_error & (1 << 17)))
#define CMD_END_BIT(a)     		(FAIL(a) && (a->last_error & (1 << 18)))
#define CMD_INDEX(a)       		(FAIL(a) && (a->last_error & (1 << 19)))
#define DATA_TIMEOUT(a)  		(FAIL(a) && (a->last_error & (1 << 20)))
#define DATA_CRC(a)				(FAIL(a) && (a->last_error & (1 << 21)))
#define DATA_END_BIT(a)			(FAIL(a) && (a->last_error & (1 << 22)))
#define CURRENT_LIMIT(a)		(FAIL(a) && (a->last_error & (1 << 23)))
#define ACMD12_ERROR(a)			(FAIL(a) && (a->last_error & (1 << 24)))
#define ADMA_ERROR(a)			(FAIL(a) && (a->last_error & (1 << 25)))
#define TUNING_ERROR(a)			(FAIL(a) && (a->last_error & (1 << 26)))

// The actual command indices
#define GO_IDLE_STATE           0
#define ALL_SEND_CID            2
#define SEND_RELATIVE_ADDR      3
#define SET_DSR                 4
#define IO_SET_OP_COND          5
#define SWITCH_FUNC             6
#define SELECT_CARD             7
#define DESELECT_CARD           7
#define SELECT_DESELECT_CARD    7
#define SEND_IF_COND            8
#define SEND_CSD                9
#define SEND_CID                10
#define VOLTAGE_SWITCH          11
#define STOP_TRANSMISSION       12
#define SEND_STATUS             13
#define GO_INACTIVE_STATE       15
#define SET_BLOCKLEN            16
#define READ_SINGLE_BLOCK       17
#define READ_MULTIPLE_BLOCK     18
#define SEND_TUNING_BLOCK       19
#define SPEED_CLASS_CONTROL     20
#define SET_BLOCK_COUNT         23
#define WRITE_BLOCK             24
#define WRITE_MULTIPLE_BLOCK    25
#define PROGRAM_CSD             27
#define SET_WRITE_PROT          28
#define CLR_WRITE_PROT          29
#define SEND_WRITE_PROT         30
#define ERASE_WR_BLK_START      32
#define ERASE_WR_BLK_END        33
#define ERASE                   38
#define LOCK_UNLOCK             42
#define APP_CMD                 55
#define GEN_CMD                 56

#define IS_APP_CMD              0x80000000
#define ACMD(a)                 (a | IS_APP_CMD)
#define SET_BUS_WIDTH           (6 | IS_APP_CMD)
#define SD_STATUS               (13 | IS_APP_CMD)
#define SEND_NUM_WR_BLOCKS      (22 | IS_APP_CMD)
#define SET_WR_BLK_ERASE_COUNT  (23 | IS_APP_CMD)
#define SD_SEND_OP_COND         (41 | IS_APP_CMD)
#define SET_CLR_CARD_DETECT     (42 | IS_APP_CMD)
#define SEND_SCR                (51 | IS_APP_CMD)

#define SD_GET_CLOCK_DIVIDER_FAIL	0xffffffff

#define MIN_FREQ 400000
#define BCM2835_EMMC_WRITE_DELAY       (((2 * 1000000) / MIN_FREQ) + 1)

#if defined (EMMC_DEBUG) || defined (SD_DEBUG)
extern int kprint(const char *format, ...);
#endif

#ifdef DEBUG
#define EMMC_DEBUG
#define SD_DEBUG
#endif

//#define EMMC_DEBUG

#ifdef EMMC_DEBUG
#define EMMC_TRACE(...)     {										\
        kprint("EMMC %s:%4d[%s] : ", __FILE__, __LINE__, __func__);	\
        kprint(__VA_ARGS__);										\
        kprint("\n\r"); }
#else
#define EMMC_TRACE(...)
#endif

//#define SD_DEBUG

#ifdef SD_DEBUG
#define SD_TRACE(...)     {											\
        kprint("SD   %s:%4d[%s] : ", __FILE__, __LINE__, __func__);	\
        kprint(__VA_ARGS__);										\
        kprint("\n\r"); }
#else
#define SD_TRACE(...)
#endif

// Enable 1.8V support
//#define SD_1_8V_SUPPORT

// Enable 4-bit support
#define SD_4BIT_DATA

// Enable SDXC maximum performance mode
#define SDXC_MAXIMUM_PERFORMANCE

#ifdef SD_DEBUG
static char *sd_versions[] = { "unknown", "1.0 and 1.01", "1.10", "2.00", "3.0x", "4.xx" };

static char *err_irpts[] = { "CMD_TIMEOUT", "CMD_CRC", "CMD_END_BIT", "CMD_INDEX",
	"DATA_TIMEOUT", "DATA_CRC", "DATA_END_BIT", "CURRENT_LIMIT",
	"AUTO_CMD12", "ADMA", "TUNING", "RSVD" };
#endif


#endif /* SD_H_ */
