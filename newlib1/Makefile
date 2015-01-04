
ARMGNU ?= arm-none-eabi

COPS = -Wall -nostartfiles -ffreestanding -O2 -march=armv6zk -mtune=arm1176jzf-s

LIB = -L/home/david/devel/arch/raspberrypi/devkit/arm-none-eabi/lib -L/home/david/devel/arch/raspberrypi/devkit/lib/gcc/arm-none-eabi/4.8.3 

gcc : uartx01.hex uartx01.bin

all : gcc

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.opt.s

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

uartx01.o : uartx01.c
	$(ARMGNU)-gcc $(COPS) -c uartx01.c -o uartx01.o

uartx01.elf : memmap vectors.o uartx01.o syscalls.o
	$(ARMGNU)-ld vectors.o uartx01.o syscalls.o -T memmap -o uartx01.elf $(LIB) -lc -lgcc
	$(ARMGNU)-objdump -D uartx01.elf > uartx01.list

uartx01.bin : uartx01.elf
	$(ARMGNU)-objcopy uartx01.elf -O binary uartx01.bin

uartx01.hex : uartx01.elf
	$(ARMGNU)-objcopy uartx01.elf -O ihex uartx01.hex

syscalls.o : syscalls.c
	$(ARMGNU)-gcc $(COPS) -c $(COPS) syscalls.c -o syscalls.o

qemu: uartx01.elf
	../../../bin/qemu-system-arm -kernel uartx01.elf -cpu arm1176 -m 256 -M raspi -serial stdio  -monitor stdio




