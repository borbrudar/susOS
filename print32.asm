[bits 32]
;32bit protected mode routine for printing strings to screen

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; print string saved on the address pointed to by ebx
print32:
pusha
mov edx, VIDEO_MEMORY ; edx is set to start of vga

print32_loop:
mov al, [ebx] ; load next char
mov ah, WHITE_ON_BLACK ; and color

cmp al,0
je print32_done ; finish if we reach null

mov [edx], ax ; write char to vga

add ebx, 1 ; next char in our string
add edx, 2 ; next pos in vga array

jmp print32_loop

print32_done:
popa
ret
