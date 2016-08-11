TARGET=libbarebone.a
ARM=arm-none-eabi

SOURCES=kprint.c strlen.c error.c kmalloc.c kdie.c memset.c memcpy.c registers_dump.c ringbuffer.c 
OBJECTS=kprint.o strlen.o error.o kmalloc.o kdie.o memset.o memcpy.o registers_dump.o ringbuffer.o 
INCLUDE=../include

AS=$(ARM)-gcc
AS_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc
CC_FLAGS=-Wall -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles -O2 -I$(INCLUDE)

OBJ=$(ARM)-objcopy

.PHONY:sources clean 

$(TARGET): sources
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

sources: $(SOURCES)
	$(CC) $(CC_FLAGS) -c $(SOURCES) -lgcc

clean:
	rm -rf *.o
