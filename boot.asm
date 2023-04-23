[org 0x7c00]

KERNEL_OFFSET equ 0x1000
mov [BOOT_DRIVE], dl ; bios stores boot drive in dl

mov bp, 0x9000 ;stack init
mov sp, bp

mov bx, HELLO
call print_string

call load_kernel
call switch_to_pm ; never return from here

jmp $

; includes
%include "print.asm"
%include "print_hex.asm"
%include "disk.asm"
%include "gdt.asm"
%include "print32.asm"
%include "switch_to_pm.asm"

[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print_string

	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]

BEGIN_PM:
	mov ebx, HELLO32
	call print32

	call KERNEL_OFFSET ; jump to kernel position yatta

	jmp $

;globals
BOOT_DRIVE : db 0
HELLO  db "Hello 16-bit world!", 0
HELLO32  db "Hello 32-bit world!", 0
MSG_LOAD_KERNEL db "Loading kernel." ,0

;rest is 0 and magic
times 510-($-$$) db 0
dw 0xaa55
