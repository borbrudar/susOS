OUTPUT(susloader)

SECTIONS{
	.text 0x7c00 : { *(.text)}
	.data : { *(.data)}
}
