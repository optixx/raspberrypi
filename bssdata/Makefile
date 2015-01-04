
ARMGNU ?= arm-none-eabi

COPS = -g -Wall -O2 -nostdlib -nostartfiles -ffreestanding 

gcc : bssdata.hex bssdata.bin fun.list

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc

vectors.o : vectors.s
	$(ARMGNU)-as -g vectors.s -o vectors.o

bssdata.o : bssdata.c
	$(ARMGNU)-gcc $(COPS) -c bssdata.c -o bssdata.o

qemu.o : qemu.c
	$(ARMGNU)-gcc $(COPS) -c qemu.c -o qemu.o

bssdata.elf : memmap vectors.o bssdata.o qemu.o 
	$(ARMGNU)-ld -g vectors.o qemu.o bssdata.o -T memmap -o bssdata.elf
	$(ARMGNU)-objdump -D bssdata.elf > bssdata.list

bssdata.bin : bssdata.elf
	$(ARMGNU)-objcopy bssdata.elf -O binary bssdata.bin

bssdata.hex : bssdata.elf
	$(ARMGNU)-objcopy bssdata.elf -O ihex bssdata.hex


fun.list : start.s simple fun.c
	$(ARMGNU)-as start.s -o start.o
	$(ARMGNU)-gcc $(COPS) -c fun.c -o fun.o
	$(ARMGNU)-ld -T simple start.o fun.o -o fun.elf
	$(ARMGNU)-objdump -D fun.elf > fun.list

qemu: bssdata.elf  
	qemu-system-arm -m 128 -kernel bssdata.elf -serial stdio -machine integratorcp -S -s

rungdb:
	cgdb -d arm-none-eabi-gdb -- --init-command=gdbinit
