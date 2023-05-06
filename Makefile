# $^ -- all dependencies of a target
# $< -- first dependency
# $@ -- target name

#include dirs
INCLUDE_DIRS= -I"libc/" -I"drivers/" -I"cpu/" -I"kernel/"

#predefined variables, compiler/linker names etc
CC=/usr/local/i386elfgcc/bin/i386-elf-g++ 
LD=/usr/local/i386elfgcc/bin/i386-elf-ld
GDB=/usr/local/i386elfgcc/bin/i386-elf-gdb
FLAGS=-ffreestanding -g -fpermissive ${INCLUDE_DIRS}
#DEBUG_FLAGS=-g -fpermissive -w


# sources n shit, convert to obj files
C_SOURCES = $(wildcard kernel/*.cpp drivers/*.cpp cpu/*.cpp libc/*.cpp)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)
OBJ = ${C_SOURCES:.cpp=.o cpu/interrupt.o}


all: os-image.bin

run : all
	qemu-system-i386 -fda os-image.bin


#build os image --- repmber: boot.bin must be first
os-image.bin: boot/boot.bin kernel.bin
	cat $^ > $@
# truncate os-image.bin -s +30KB
# truncate os-image.bin --size 30KB


#build kernel lib
kernel.bin : boot/kernel_entry.o ${OBJ}
	${LD} -Tlink.ld -o $@ -Ttext 0x1000 $^ --oformat binary

# need kernel with dbg info for dbg
kernel.elf : boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

# debug
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"



#build kernel object file
%.o : %.cpp ${HEADERS}
	${CC} ${FLAGS} -c $< -o $@

#assemble the kernel entry
%.o : %.asm
	nasm -f elf $< -o $@


%.bin : %.asm
	nasm -f bin -I 'boot/' -I 'cpu/' $< -o $@

# phony clean target
clean:
	rm -rf *.bin *.o *.dis os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o kernel/*.elf drivers/*.elf
	rm -rf cpu/*.o cpu/*.elf libc/*.o
