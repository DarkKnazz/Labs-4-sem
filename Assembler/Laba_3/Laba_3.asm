.model small
.data
    LENGTH equ 6
    BASE_COUNT equ 10
    MAX equ 32767
    MAS_LEN equ 30
    
    str1 db 8 dup(?)
    str2 db 8 dup(?)
    msg1 db "Введите начало диапазона: ",10,13,'$' 
    msg2 db "Введите конец диапазона: ",10,13,'$' 
    msg3 db "Граница начальная больше конечной!",10,13,'$' 
    msg4 db "Количество чисел из данного диапазона: ",10,13,'$'
    msg5 db "Диапазон это одно число!", 10, 13, '$'
    errNum db "Вы не ввели число",10,13,'$'
    errOver db "Произошло переполнение числа!",10,13,'$'
    endl db 10,13,'$'
    
    mas dw 1, 3, -4, 7, 10, -5, 2, 8, 0, 1, 15, -7, 9, 0, 4, 6, -2, -9, 3, 13, 1, 0, 5, -9, 10, -3, 6, 2, 32, 45
    num1 dw 0
    num2 dw 0
    
    kol dw 0
    
    sign dw 0
.code

OUTPUT MACRO line1
    mov ah, 09h  
    lea dx, line1
    int 21h     
endm   

INPUT MACRO line2 
    mov line2[0], LENGTH 
    lea dx, line2
    mov ah, 0Ah
    int 21h
    
    push bx
    xor bx, bx 
    mov bl, line2[1]
    add bl, 2
    mov line2[bx], '$'  
    pop bx 
endm 

start:
    mov ax, @data
    mov ds,ax
    OUTPUT [msg1]
    INPUT  [str1]
    OUTPUT [endl]
    
    lea bx, num1
    lea di, str1
    call ATOI
    
    OUTPUT [msg2]
    INPUT  [str2]
    OUTPUT [endl]
    
    lea bx, num2
    lea di, str2
    call ATOI
    xor ax, ax
    xor si, si
    mov dx, num2
    xor bx, num1
    cmp dx, bx
    je EqualNum
    jl BorderLow 
exit:      
    mov ah, 4ch
    int 21h
    
ATOI PROC  
    push bx 
    xor ax, ax
    xor bx, bx
    xor cx, cx 
    
    mov bx, di
    add bx, 2 
    cmp [bx], '-'
    jne check_NUM
    mov sign, 1
    inc bx
    
check_NUM:
    cmp [bx], '$'
    je cyclStart    
    cmp [bx], '0'
    jl ErrorNotNum 
    cmp [bx], '9'
    jg ErrorNotNum
    inc bx
    jmp check_NUM

cyclStart:    
    mov cl, 1[di] 
    sub cx, sign
    add di, 2
    add di, sign
    mov bl, BASE_COUNT
    xor dx, dx   
    
mainCycl:
    mul bx
    jo ErrorOver 
    mov dl, [di]
    sub dl, 30h
    add ax, dx  
    inc di
    cmp ax, MAX
    ja ErrorOver
    loop mainCycl
    
    cmp sign, 0
    je finish
    not ax
    inc ax
    
finish:    
    pop bx
    mov [bx], ax 
    mov sign, 0
    ret
    
ErrorNotNum: 
    pop bx 
    mov sign, 0
    OUTPUT [errNum]
    jmp exit
      
ErrorOver: 
    pop bx         
    mov sign, 0
    OUTPUT [errOver]
    jmp exit    
ATOI endp

EqualNum:
    OUTPUT [msg5]
    jmp exit
    
BorderLow:
    OUTPUT [msg3]
    jmp exit

end start         