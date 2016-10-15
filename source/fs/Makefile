TARGET=libfs.a
ARM=arm-none-eabi

INCLUDE=../include

SOURCES=block.c
OBJECTS=block.o
INCLUDES=$(INCLUDE)/fs/*.h

AS=$(ARM)-gcc

AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc

OBJ=$(ARM)-objcopy

.PHONY: clean sources

$(TARGET): sources 
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

sources: $(SOURCES) $(INCLUDES)
	$(CC) $(CC_FLAGS) -I$(INCLUDE) -c $(SOURCES) -lgcc

clean:
	rm -rf *.o
