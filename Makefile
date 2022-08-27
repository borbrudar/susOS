BUILD_DIR=build
BOOTLOADER=$(BUILD_DIR)/susloader/susloader.o
OS=$(BUILD_DIR)/sus/main
DISK_IMG=$(BUILD_DIR)/disk.img.o

all: bootdisk

.PHONY: bootdisk bootloader os qemu qfast link
	
bootloader:
	make -C susloader

os:
	make -C sus

qfast:
	qemu-system-i386 -machine q35 -fda  $(DISK_IMG) 
qemu:
	qemu-system-i386 -machine q35 -fda $(DISK_IMG) -gdb tcp::26000 -S


bootdisk: bootloader os
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880 
	dd conv=notrunc if=$(BOOTLOADER) of=$(DISK_IMG) bs=512 count=1 seek=0
	dd conv=notrunc if=$(OS) of=$(DISK_IMG) bs=512 count=$$(($(shell stat --printf="%s" $(OS))/512))	seek=1

clean:
	make -C susloader clean
	make -C sus clean


link:
	gcc -m32 -masm=intel -g -c main.c
	ld -m elf_i386 -o main -T link.lds main.o
