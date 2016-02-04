TARGET=libbcm2836.a
ARM=arm-none-eabi

AS=$(ARM)-gcc
AS_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

AR=$(ARM)-ar 
AR_FLAGS=rcs

CC=$(ARM)-gcc
CC_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles

OBJ=$(ARM)-objcopy

$(TARGET): uart.o
	$(AR) $(AR_FLAGS) $@ $^

uart.o: uart.c
	$(CC) $(CC_FLAGS) -c $^

clean:
	rm *.o
