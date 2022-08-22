define hook-stop
	# define segment:offset format to translate into a physical address
	print "[%4x:%4x] " , $cs, $eip
	x/i $cs*16+$eip

end

set disassembly-flavor intel

layout asm
layout reg

set architecture i8086

target remote localhost:26000
b *0x7c00


