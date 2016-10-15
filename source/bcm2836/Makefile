TARGET=libbcm2836.a
ARM=arm-none-eabi

SOURCES=uart.c timer.c sd.c mbox.c cache.c videocore.c armtimer.c interrupt_handler.c gpio.c
OBJECTS=uart.o timer.o sd.o mbox.o cache.o videocore.o armtimer.o interrupt_handler.o gpio.o mmio.o
INCLUDE=../include

AS_SOURCES=mmio.S
AS=$(ARM)-gcc
#AS_FLAGS=-mfpu=neon -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc
#CC_FLAGS=-mfpu=neon -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles -O0 -I$(INCLUDE)

OBJ=$(ARM)-objcopy

.PHONY:sources clean asm

$(TARGET): sources asm
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

sources: $(SOURCES)
	$(CC) $(CC_FLAGS) -I$(INCLUDE) -c $^

asm: $(AS_SOURCES)
	$(AS) $(AS_FLAGS) -c $^

clean:
	rm -rf *.o
