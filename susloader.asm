;*********************************************
; susloader >_<
; v0.1
;*********************************************
org 0x7c00
bits 16
start: jmp boot

;; define variables and constants
msg db "Booting the sussiest OS! >uwu< ", 0ah, 0dh, 0h

boot:
    cli ; no interrupts
    cld ; for init
    hlt ; halt the system


; 512 bytes required. clear the rest with 0

times 510 - ($-$$) db 0
dw 0xAA55 ; boot signature
