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
    kol_Str db 8 dup(?)
    
    mas dw 0,0,0,0,0,0,0,0,0,0
    num1 dw 0
    num2 dw 0 
    
    kol dw 0
    tmp dw 0
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
    mov dx, num2
    cmp num1, dx
    jg exit
    xor si, si
array_Enter:
    INPUT [str2]
    OUTPUT [endl]
    lea bx, tmp    
    lea di, str2
    call ATOI
    mov dx, tmp
    mov mas[si], dx
    add si, 2
    cmp si, 20
jne array_Enter
             
xor si, si
xor dx, dx             
array_Kol:
    mov dx, num1
    cmp mas[si], dx
    jge cont1
    incr:
    add si, 2
    cmp si, 20
jne array_Kol

    lea bx, kol
    lea di, kol_Str
    call ITOA
    OUTPUT [msg4]
    OUTPUT [kol_Str]
    OUTPUT [endl]

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

ITOA PROC

    mov ax, [bx]
    mov bx, 10
    xor cx, cx 
    
    cmp ax, MAX
    jbe division
    dec ax
    not ax
    mov [di], '-'
    inc di
    
division:
    xor dx, dx
    div bx       
    push dx
    inc cx
    cmp ax, 0
    jne division

save_in_str:
    pop dx
    add dl, 30h
    mov [di], dl
    inc di
    loop save_in_str
    
    mov [di], '$'    
    
    ret
ITOA endp

EqualNum:
    OUTPUT [msg5]
    jmp exit
    
BorderLow:
    OUTPUT [msg3]
    jmp exit

cont1:
    mov dx, num2
    cmp mas[si], dx
    jle cont2:
    jg incr

cont2:
    inc kol
    jmp incr    

end start         