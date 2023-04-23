[bits 16]
switch_to_pm:
; switch to 32-bit protected mode
cli ; disable interrupts
lgdt [gdt_descriptor] ; load the gdt descriptor

mov eax, cr0 ; set control register0 to 1
or eax, 0x1
mov cr0, eax

; finally, perform a far jump to flush the pipeline
; and load our kernel
jmp CODE_SEG:init_pm

[bits 32]
; initialize registers and stack in protected mode

init_pm:
	mov ax, DATA_SEG ; after switching to pm, old segments are
	mov ds, ax       ; useless, so reload them, now as defined in
	mov ss, ax       ; the gdt
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000 ; update stack position to the top of free space
	mov esp, ebp
	call BEGIN_PM
