TARGET=libsys.a
ARM=arm-none-eabi

INCLUDE=../include

SOURCES=devs.c kscheduler.c kthread.c syscall.c
OBJECTS=devs.o kscheduler.o kthread.o syscall.o
INCLUDES=$(INCLUDE)/sys/*.h



AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc
CC_FLAGS=-Wall -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles -O2 -I$(INCLUDE)

OBJ=$(ARM)-objcopy

.PHONY: clean sources asm

$(TARGET): sources asm
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

sources: $(SOURCES) $(INCLUDES)
	$(CC) $(CC_FLAGS) -c $(SOURCES) -lgcc

clean:
	rm -rf *.o
