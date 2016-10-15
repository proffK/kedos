#include <kthread.h>
#include <stdint.h>

typedef uint32_t res_type_t;

typedef struct {
        pid_t pid;
        res_type_t type;
        void* data;
        uint32_t reserved;
} res_unit;

enum first_level_res {
        RES_CPU = 0x01,
        RES_MEM,
        RES_DEV,
        RES_HAN // Interrupt handler
};

enum sec_level_res {
        RES_PAGE = 0x01,
        RES_GPIO,
        RES_UART,
        RES_SD,
        RES_USB,
        RES_GPU
};

enum third_level_res {
        RES_FS = 0x01,
        RES_TTY
}; 

static inline res_type_t res_compose(uint8_t first_level, uint8_t sec_level, 
                                     uint8_t third_level, uint8_t four_level)
{
        return (four_level << 24 | third_level << 16 | sec_level << 8 | first_level);
}
