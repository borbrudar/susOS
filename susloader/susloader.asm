;*********************************************
; susloader >_<
; v0.2
;*********************************************
;org 0x7c00
bits 16
start: jmp boot

;; define variables and constants
msg: dq "Booting the sussiest OS! >w< "
endmsg:
clr: db " "

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
   
    ;clear screen
    mov cx, 1
    xor dx, dx ; start at 0,0
    mov ds, dx
    mov bl, 00h ; black
clearScr:
    mov si, msg
    mov ah, 2 
    int 10h
    lodsb
    mov ah, 9
    int 10h 
    inc dl
    
    cmp dl, 80 ; wrap around the whole screen
    jne clearScr
    inc dh
    xor dl, dl ; inc row and set column to 0
    
    cmp dh,25 
    jne clearScr

    ;init 
    mov si, msg ; si points to first byte of our message
    xor dx, dx ; to 0
    mov ds, dx ; to 0
    mov bl, 03h ; cyan color nya~
    mov cx, 1 ; 1 char repeat
    
   
    mov bh, 0 
    mov dh, 10 ; row
    mov dl, 25 ; column 
print:       
    cmp si, endmsg ; print until end of message
    jne putChar ; print 1 char

    ; load the sample into ram and execute it
    mov ax, 0x50
    mov es, ax ; set buffer
    xor bx, bx
    xor ax, ax
    xor cx, cx
    xor dx, dx

    mov al, 2 ; number of sectors to read
    mov ch, 0 ; track number
    mov cl, 2 ; sector number (1st is bootloader itself)
    mov dh, 0 ; head number
    mov dl, 0 ; drive numer (0- floppy 1-floppy 2, 80h-drive 0,81h-drive 1 etc)
    
    mov ah, 0x02 ; BIOS function 13, subroutine 2, reading from disk 
    int 0x13 ; BIOS call      
    ; jmp 0x50:0x0 ; jump to sector 
    jmp 0x500 ; apparently relative addressing doesnt resolve correctly (?)    

    hlt ; halt the system

; 512 bytes required. clear the rest with 0

times 510 - ($-$$) db 0
dw 0xAA55 ; boot signature
