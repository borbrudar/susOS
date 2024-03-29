;GDT
;------------------------------------------------------------------------
gdt_start:

gdt_null: ; mandatory null descriptor
	dd 0x0 ; double word (4 bytes)
	dd 0x0

gdt_code: ; code segment
	; base = 0x0, limit = 0xfffff
	; 1st flags: present=1, privilege=00, descriptor type = 1  --->1001b
	; type flags: code=1, conforming=0, readable= 1, accessed=0 ----> 1010b
	; 2nd flags: granularity=1, 32-bit=1, 64-bit= 0, avl=0 ----> 1100b
	dw 0xffff     ; limit (bits 0-15)
	dw 0x0        ; base (0-15)
	db 0x0        ; base (16-23)
	db 10011010b ; 1st flags, type flags
	db 11001111b ; 2nd flags, limit(16-19)
	db 0x0        ; base (24-31)

gdt_data: ; data segment
	; same as code except for the flags:
	; type flags: code=0, expand down = 0, writable=1, accessed=0 -> 0010b
	dw 0xffff     ; limit (0-15)
	dw 0x0        ; base (0-15)
	db 0x0        ; base (16-23)
	db 10010010b ; 1st flags, type flags
	db 11001111b ; 2nd flags, limit(16-19)
	db 0x0        ; base(24-31)

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start -1 ; size of gdt, -1 just because
	dd gdt_start


; define constants for gdt segment descriptor offsets, to help segment registers
; when in protected mode
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

;GDT END
;------------------------------------------------------------------------
