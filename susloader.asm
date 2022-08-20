;*********************************************
; susloader >_<
; v0.1
;*********************************************
org 0x7c00
bits 16
start: jmp boot

;; define variables and constants
msg: dq "Booting the sussiest OS! >w< "
endmsg:

putChar:
    mov ah, 2 ; move cursor to pos
    int 10h ; BIOS code 10, subroutine 2 to move cursor to pos
    lodsb ; load first byte pointed to by si into al
    mov ah, 9 ; write char to screen
    int 10h  ; BIOS 10/9
    inc dl ; increase the thingy
    jmp print

boot:
    cli ; no interrupts
    cld ; for init

    ;init 
    mov si, msg ; si points to first byte of our message
    xor dx, dx ; to 0
    mov ds, dx ; to 0
    mov bl, 03h ; cyan color nya~
    mov cx, 1 ; 1 char repeat
    
   
    mov bh, 0 
    mov dh, 13 ; row
    mov dl, 25 ; column 
print:       
    cmp si, endmsg ; print until end of message
    jne putChar ; print 1 char
    hlt ; halt the system

; 512 bytes required. clear the rest with 0

times 510 - ($-$$) db 0
dw 0xAA55 ; boot signature
