TARGET=libsys.a
ARM=arm-none-eabi

INCLUDE=../include

SOURCES=devs.c kscheduler.c kthread.c syscall.c kernel_lib.c
OBJECTS=devs.o kscheduler.o kthread.o syscall.o kernel_lib.o
INCLUDES=$(INCLUDE)/sys/*.h

AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc

OBJ=$(ARM)-objcopy

.PHONY: clean sources asm

$(TARGET): sources asm
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

sources: $(SOURCES) $(INCLUDES)
	$(CC) $(CC_FLAGS) -I$(INCLUDE) -c $(SOURCES) -lgcc

clean:
	rm -rf *.o
