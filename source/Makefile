TARGET=kernel
ARM=arm-none-eabi

INCLUDE=include
STLIBS=-L./lib -L./bcm2836 -L./mm -L./test -ltest -lmem -lbcm2836 -lbarebone -lbcm2836 -lgcc

AS=$(ARM)-gcc
AS_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

CC=$(ARM)-gcc
CC_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles -I$(INCLUDE)

LD_SCRIPT= linker.ld
LD_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -O2 -nostdlib -lgcc

OBJ=$(ARM)-objcopy

.PHONY: lib bcm2836 mm test all clean

all: lib bcm2836 mm test $(TARGET)

$(TARGET): kernel.o boot.o 
	$(CC) -T $(LD_SCRIPT) -o $(TARGET).elf $(LD_FLAGS) $^ $(STLIBS)
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

mm:
	make -C mm

test:
	make -C test

install: $(TARGET)
	cp -f ../kernel/kernel.img /run/media/$(USER)/boot/

clean:
	rm -rf *.o
	make -C lib clean
	make -C bcm2836 clean
	make -C mm clean
