TARGET=kernel
ARM=arm-none-eabi

AS=$(ARM)-gcc
AS_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

CC=$(ARM)-gcc
CC_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles

LD_SCRIPT= linker.ld
LD_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -O2 -nostdlib

OBJ=$(ARM)-objcopy

all: lib bcm2836 $(TARGET)

$(TARGET): kernel.o boot.o 
	$(CC) -T $(LD_SCRIPT) -o $(TARGET).elf $(LD_FLAGS) $^ -lgcc -L./lib -L./bcm2836 -lbcm2836 -lbarebone
	$(OBJ) $(TARGET).elf -O binary $(TARGET).bin
	mv $(TARGET).bin ../kernel/kernel.img

kernel.o: kernel.c 
	$(CC) $(CC_FLAGS) -c -g $^ -o $@ -O2 -Wall -Wextra -lgcc

boot.o: boot.S
	$(AS) $(AS_FLAGS) -c -g $^ -o $@

lib:
	make -C lib

bcm2836:
	make -C bcm2836

install: $(TARGET)
	cp -f ../kernel/kernel.img /run/media/$(USER)/boot/

clean:
	rm *.o
	make -C lib clean
	make -C bcm2836 clean
