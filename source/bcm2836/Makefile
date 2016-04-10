TARGET=libbcm2836.a
ARM=arm-none-eabi

SOURCES=uart.c timer.c sd.c mbox.c cache.c videocore.c
OBJECTS=uart.o timer.o sd.o mbox.o cache.o videocore.o mmio.o
INCLUDE=../include

AS_SOURCES=mmio.S
AS=$(ARM)-gcc
AS_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc
CC_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles -O0 -I$(INCLUDE)

OBJ=$(ARM)-objcopy

.PHONY:sources clean asm

$(TARGET): sources asm
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

sources: $(SOURCES)
	$(CC) $(CC_FLAGS) -c $^

asm: $(AS_SOURCES)
	$(AS) $(AS_FLAGS) -c $^

clean:
	rm -rf *.o
