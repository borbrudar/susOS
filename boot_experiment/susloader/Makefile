BUILD_DIR=../build/susloader

BOOTLOADER_SRCS := $(wildcard *.asm)
BOOTLOADER_OBJS := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(BOOTLOADER_SRCS))

all: $(BOOTLOADER_OBJS)

$(BUILD_DIR)/%.o: %.asm
	nasm -f elf -F dwarf -g $< -o $@
	ld -m elf_i386 -T susloader.lds $@ -o $@.elf
	objcopy -O binary $(BUILD_DIR)/susloader.o.elf $@

clean:
	rm $(BUILD_DIR)/*
