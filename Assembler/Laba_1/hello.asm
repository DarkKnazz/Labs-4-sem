.model tiny
.code
org 100h
start:
    mov ax, 9
    mov dx, offset message
    int 21h
    ret
    message db "Hello world!", 0Dh, 0Ah, "$"
end start