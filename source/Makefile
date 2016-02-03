TARGET=kernel
ARM=arm-none-eabi

AS=$(ARM)-gcc
AS_FLAGS=-mcpu=arm1176jzf-s -fpic -ffreestanding -nostartfiles

CC=$(ARM)-gcc
CC_FLAGS=-mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -nostartfiles

LD_SCRIPT= linker.ld
LD_FLAGS=-ffreestanding -O2 -nostdlib

OBJ=$(ARM)-objcopy

$(TARGET): kernel.o boot.o
	$(CC) -T $(LD_SCRIPT) -o $(TARGET).elf $(LD_FLAGS) $^
	$(OBJ) $(TARGET).elf -O binary $(TARGET).bin
	mv $(TARGET).bin ../kernel/kernel.img

kernel.o: kernel.c
	$(CC) $(CC_FLAGS) -c $^ -o $@ -O2 -Wall -Wextra

boot.o: boot.S
	$(AS) $(AS_FLAGS) -c $^ -o $@

install: $(TARGET)
	cp -f ../kernel/kernel.img /run/media/$(USER)/boot/

clean:
	rm *.o
