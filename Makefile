# $^ -- all dependencies of a target
# $< -- first dependency
# $@ -- target name

#predefined variables, compiler/linker names etc
CC=i386-elf-g++
LD=i386-elf-ld
GDB=i386-elf-gdb
FLAGS=-ffreestanding -g -fpermissive
#DEBUG_FLAGS=-g


# sources n shit, convert to obj files
C_SOURCES = $(wildcard kernel/*.c kernel/*.cpp drivers/*.c)
HEADERS = $(wildcard kernel/*.h driver/*.c)
OBJ = ${C_SOURCES:.c=.o}


all: os-image.bin

run : all
	qemu-system-i386 -fda os-image.bin


#build os image --- rember: boot.bin must be first
os-image.bin: boot/boot.bin kernel.bin
	cat $^ > $@


#build kernel lib
kernel.bin : boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

#build kernel object file
%.o : %.c ${HEADERS}
	${CC} ${FLAGS} -c $< -o $@

#assemble the kernel entry
%.o : %.asm
	nasm -f elf $< -o $@


%.bin : %.asm
	nasm -f bin -I 'boot/' $< -o $@

#debug, also need kernel with dbg info obv
kernel.elf : boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"


# phony clean target
clean:
	rm -rf *.bin *.o *.dis os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o kernel/*.elf drivers/*.elf

# disassemble
kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@
