;subroutine for loading the disk and related error checking
disk_load:
	push dx ; requested sectors

	mov ah, 0x02 ;bios function to read disk
	mov al, dh
	mov ch, 0x00 ; cylinder/track 0
	mov dh, 0x00 ; head 0
	mov cl, 0x02 ; sector 2

	int 13h

	jc disk_error

	pop dx
	cmp dh, al
	jne disk_error
	ret

disk_error:
	mov bx, DISK_ERROR
	call print_string
	jmp $

; data
DISK_ERROR db "Disk read error." , 0
