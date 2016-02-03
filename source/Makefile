TARGET=kernel
ARM=arm-none-eabi

AS=$(ARM)-gcc
AS_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

CC=$(ARM)-gcc
CC_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles

LD_SCRIPT= linker.ld
LD_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -O2 -nostdlib

OBJ=$(ARM)-objcopy

$(TARGET): kernel.o boot.o
	$(CC) -T $(LD_SCRIPT) -o $(TARGET).elf $(LD_FLAGS) $^ -lgcc
	$(OBJ) $(TARGET).elf -O binary $(TARGET).bin
	mv $(TARGET).bin ../kernel/kernel.img

kernel.o: kernel.c
	$(CC) $(CC_FLAGS) -c -g $^ -o $@ -O2 -Wall -Wextra -lgcc

boot.o: boot.S
	$(AS) $(AS_FLAGS) -c -g $^ -o $@

install: $(TARGET)
	cp -f ../kernel/kernel.img /run/media/$(USER)/boot/

clean:
	rm *.o
