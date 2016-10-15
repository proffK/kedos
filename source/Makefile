TARGET=kernel
ARM=arm-none-eabi

INCLUDE=include
STLIBS=-L./lib -L./bcm2836 -L./mm -L./test -L./fs -L./sys -ltest -lsys -lfs -lmem -lbcm2836 -lsys -lbarebone -lbcm2836 -lgcc

AS=$(ARM)-gcc
AS_FLAGS=-mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -nostartfiles

CC=$(ARM)-gcc
CC_FLAGS=-mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -fpic -ffreestanding -std=gnu99 -nostartfiles

LD_SCRIPT= linker.ld
LD_FLAGS= -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -O2 -nostdlib -lgcc

OBJ=$(ARM)-objcopy

.PHONY: fs lib bcm2836 mm sys test all clean count

all: lib bcm2836 mm fs sys test $(TARGET)

$(TARGET): kernel.o boot.o
	$(CC) -T $(LD_SCRIPT) -o $(TARGET).elf $(LD_FLAGS) $^ $(STLIBS)
	$(OBJ) $(TARGET).elf -O binary $(TARGET).bin
	mkdir -pv ../kernel
	mv $(TARGET).bin ../kernel/kernel7.img

kernel.o: kernel.c 
	$(CC) $(CC_FLAGS) -I$(INCLUDE) -c $^ -o $@ -O2 -Wall -Wextra -lgcc

boot.o: boot.S
	$(AS) $(AS_FLAGS) -c $^ -o $@

lib:
	AS_FLAGS="$(AS_FLAGS)" CC_FLAGS="$(CC_FLAGS)" LD_FLAGS="$(LD_FLAGS)" make -C lib

bcm2836:
	AS_FLAGS="$(AS_FLAGS)" CC_FLAGS="$(CC_FLAGS)" LD_FLAGS="$(LD_FLAGS)" make -C bcm2836

mm:
	AS_FLAGS="$(AS_FLAGS)" CC_FLAGS="$(CC_FLAGS)" LD_FLAGS="$(LD_FLAGS)" make -C mm

fs:
	AS_FLAGS="$(AS_FLAGS)" CC_FLAGS="$(CC_FLAGS)" LD_FLAGS="$(LD_FLAGS)" make -C fs

sys:
	AS_FLAGS="$(AS_FLAGS)" CC_FLAGS="$(CC_FLAGS)" LD_FLAGS="$(LD_FLAGS)" make -C sys

test:
	AS_FLAGS="$(AS_FLAGS)" CC_FLAGS="$(CC_FLAGS)" LD_FLAGS="$(LD_FLAGS)" make -C test

install: $(TARGET)
	cp -f ../kernel/kernel.img /run/media/$(USER)/boot/

clean:
	rm -rf *.o
	make -C lib clean
	make -C bcm2836 clean
	make -C mm clean
	make -C fs clean
count:
	wc -l *.c */*.c include/*/*.h
