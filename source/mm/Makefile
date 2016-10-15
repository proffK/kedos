TARGET=libmem.a
ARM=arm-none-eabi

INCLUDE=../include

SOURCES=heap.c
OBJECTS=heap.o
INCLUDES=$(INCLUDE)/mm/*.h

AS=$(ARM)-gcc
#AS_FLAGS=-mfpu=neon -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc
#CC_FLAGS=-Wall -mfpu=neon -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles -O2 -I$(INCLUDE)

OBJ=$(ARM)-objcopy

.PHONY: clean sources

$(TARGET): sources 
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

sources: $(SOURCES) $(INCLUDES)
	$(CC) $(CC_FLAGS) -I$(INCLUDE) -c $(SOURCES) -lgcc

clean:
	rm -rf *.o
