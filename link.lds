ENTRY(main)


PHDRS
{
	headers PT_PHDR FILEHDR PHDRS;
	headers_load PT_LOAD PHDRS;
	code PT_LOAD FLAGS(0x1 | 0x02 | 0x4);
}

SECTIONS{
	/* . = 0x10000; */
	.text : { *(.text) } : code
	. = 0x8000000;
	.data : { *(.data) }
	.bss : { *(.bss) } 
	/DISCARD/ : { *(.eh_frame) } 	 
}
