BUILD_DIR=build
BOOTLOADER=$(BUILD_DIR)/susloader/susloader.o
OS=$(BUILD_DIR)/sus/sample.o
DISK_IMG=$(BUILD_DIR)/disk.img.o

all: bootdisk

.PHONY: bootdisk bootloader os qemu qfast

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
	dd conv=notrunc if=$(OS) of=$(DISK_IMG) bs=512 count=1 seek=1

clean:
	make -C susloader clean
	make -C sus clean
