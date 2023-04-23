# $^ -- all dependencies of a target
# $< -- first dependency
# $@ -- target name

#predefined variables, compiler/linker names etc
CC=i386-elf-g++
LD=i386-elf-ld


# sources n shit, convert to obj files
C_SOURCES = $(wildcard kernel/*.c kernel/*.cpp drivers/*.c)
HEADERS = $(wildcard kernel/*.h driver/*.c)
OBJ = ${C_SOURCES:.c=.o}


all: os-image

run : all
	qemu-system-i386 -fda os-image


#build os image --- rember: boot.bin must be first
os-image: boot/boot.bin kernel.bin
	cat $^ > $@


#build kernel lib
kernel.bin : kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

#build kernel object file
%.o : %.c ${HEADERS}
	${CC} -ffreestanding -c $< -o $@

#assemble the kernel entry
%.o : %.asm
	nasm -f elf $< -o $@


%.bin : %.asm
	nasm -f bin -I 'boot/' $< -o $@

#main boot assembly file
#boot/boot.bin: boot/boot.asm
#	nasm -f bin $^ -o $@


# phony clean target
clean:
	rm -rf *.bin *.o *.dis os-image
	rm -rf kernel/*.o boot/*.bin drivers/*.o

# disassemble
kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@
