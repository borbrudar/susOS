print_string:
pusha ; push registers to stack

start_print_string:
mov al, [bx] ; set stack pointer to message
cmp al, 0
je end_print_string

mov ah, 0x0e
int 10h

add bx,1
jmp start_print_string

end_print_string:
popa ; pop back and return
ret

print_newline:
	pusha
	mov ah, 0x0e
	mov al, 0x0a
	int 10h
	mov al, 0x0d
	int 10h
	popa
	ret
