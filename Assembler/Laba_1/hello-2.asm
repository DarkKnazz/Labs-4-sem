.MODEL SMALL
.STACK 100h
.DATA                              
    HelloMessage DB 'Hello, $'
    Mes DB 'Enter your name: ',13,10,'$'
    Your DB (?)
    
.CODE
START:
    mov ax,@data
    mov ds,ax
    mov ah,09h
    mov dx,OFFSET Mes  
    int 21h 
    
    mov ah,3fh
    mov bx,0
    mov cx,82
    mov dx,offset Your
    int 21h
    
    ;???????? ? ????? ?????? ?????? '$'
    mov si,dx
    add si,ax
    mov byte ptr [si],'$'
    
    mov ah,09h
    MOV   DX,  offset HelloMessage    
    int 21h
    mov ah,09h
    mov dx,OFFSET Your
    int 21h  
    
    mov ah,4ch
    int 21h
END START