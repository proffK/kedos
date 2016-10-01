TARGET=libtest.a
ARM=arm-none-eabi

SOURCES=mem_test.c heap_test.c timer_test.c lib_test.c rbuffer_test.c thread_test.c sd_test.c
OBJECTS=mem_test.o heap_test.o timer_test.o lib_test.o rbuffer_test.o thread_test.o sd_test.o
INCLUDE=../include

AS=$(ARM)-gcc
AS_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc
CC_FLAGS=-Wall -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles -O2 -I../include

OBJ=$(ARM)-objcopy

.PHONY: sources clean

$(TARGET): sources
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

sources: $(SOURCES)
	$(CC) $(CC_FLAGS) -c $(SOURCES) -lgcc

clean:
	rm -rf *.o
