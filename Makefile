# $^ -- all dependencies of a target
# $< -- first dependency
# $@ -- target name

#build kernel lib
kernel.bin : kernel_entry.o kernel.o
	i386-elf-ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary

#build kernel object file
kernel.o : kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

#build the kernel entry with entry object file
kernel_entry.o : kernel_entry.asm
	nasm -f elf $< -o $@


# phony clean target
clean:
	rm *.bin *.o
