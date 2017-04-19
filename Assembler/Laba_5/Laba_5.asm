; Knazz, 18.04.2017
; Lab work №5. Work with file
; Write in file lines from input file that contains certain set of letters
.MODEL small        
.STACK 100h
.DATA       
    LENGTH equ 6

    BUFFER db 10 dup(?)
    
    ARRAY_SYMBOLS db 8 dup(?) 
    
    PATH db 'input.txt', 0;126 dup(0) 
    
    PATH_OUT db 'output.txt', 0 
    
    LEN_STR dw 0     
    
    IO_ERROR db "Unable to open the file.$"                   
                                                    
    COMMAND_ERROR db "Empty command line.$"    
                 
    TEMP_STR db ? 
    
    buff db ?    
.CODE  

OUTPUT MACRO outLine                  ; макрос вывода строки на экран
    mov ah, 09h  
    lea dx, outLine
    int 21h     
endm 

INPUT MACRO line 
    mov line[0], LENGTH 
    lea dx, line
    mov ah, 0Ah
    int 21h
    
    push bx
    xor bx, bx 
    mov bl, line[1]
    add bl, 2
    mov line[bx], '$'  
    pop bx 
endm 

start:  
 
    mov ax, @data
    mov ds, ax 
    INPUT [ARRAY_SYMBOLS]
    lea si, ARRAY_SYMBOLS
    xor si, si                
    mov dl, ARRAY_SYMBOLS[1]
    xor dx, dx
    xor si, si                
    ;lea di, PATH         
    ;call PARSE_PATH                 
       
    lea dx, PATH                        ; путь до открываемого файла
    mov ah, 3Dh                        ; функция отрытия файла 
    mov al, 00h                        ; только чтение
    int 21h   
    
    jc file_Undefined                      ; если не отрыли выводим ошибку 
    
    mov bx,ax 
    lea di,TEMP_STR
    xor di, di
read:     
    mov ah, 3Fh                        ; чтение из файла
    mov cx, 1                          ; 1024 байт
    lea dx, BUFFER                     ; в массив buffer
    int 21h 
    cmp ax, cx                         ; если не совпадает то мы вычитали все из файла
    jnz exit
        
    mov cx, ax    
    dec cx
    
    cmp BUFFER[0], 0Dh
    je read
    cmp BUFFER[0], 0Ah
    je calc_Str
    
    mov al, BUFFER[0]
    mov TEMP_STR[di], al
    inc di   
    inc LEN_STR
    
    mov dl, BUFFER[0]
    mov ah,2
    int 21h   
     
jmp read     
    mov ah,3Eh                         ; функция закрытия файла
    int 21h      
    
    jmp exit
    
file_Undefined:                            
    OUTPUT [IO_ERROR]
    jmp exit  
    
command_Undefined:
    OUTPUT [COMMAND_ERROR]              
    jmp exit    

exit:  
    mov ah, 4ch
    int 21h 

calc_Str:
    call CHECK_STRING
    xor di, di 
    mov LEN_STR, 0
    jmp read
    
PARSE_PATH PROC                     ; процедура парсинга командной строки
    xor cx,cx          
    mov si, 80h
    mov cl, es:[si]                    ; кол-во символов в командной строке
    
    cmp cx, 0
    je command_Undefined
    
    inc si
cycle:       
    mov al, es:[si] 
    cmp al, ' '
    je next_step 
    cmp al, 13
    je next_step
    mov [di], al   
    inc di
next_step:
    inc si 
    loop cycle
    ret
endp

inc_score:
    inc al
    inc si
    cmp si, LEN_STR
    je check_cycle  
    jne inner_cycle

inc_symbol_score:
    inc ah
    mov al, 0
    jmp check_cycle 
    
CHECK_STRING PROC
    pusha
    xor di, di
    xor dx, dx
    xor bx, bx 
    xor ax, ax
    lea si, TEMP_STR
    lea di, ARRAY_SYMBOLS
    xor si, si
    xor di, di
    add di, 1
    mov bl, ARRAY_SYMBOLS[1]
    add bl,2
    push ax
check_cycle:
    cmp al, 0
    jne inc_symbol_score
    inc di
    cmp bx, di
    je checking
    mov dl, ARRAY_SYMBOLS[di]
    xor si, si
    inner_cycle:
        cmp TEMP_STR[si], dl
        je inc_score
        inc si
        cmp si, LEN_STR
        je check_cycle  
        jne inner_cycle
        
checking:
    sub bl, 2 
    cmp bl, ah
    jne ex
write_or_not:    
    call WRITE_TO_FILE
    inc si
    cmp si, LEN_STR
ex: 
    pop ax
    mov ah,3Eh              ;Функция DOS 3Eh (закрытие файла)
    mov bx,ax         ;Дескриптор
    int 21h      
    popa
    ret
endp      

WRITE_TO_FILE PROC
    mov ah, 3Ch                        ; функция отрытия файла
    lea dx, PATH_OUT 
    int 21h    
    mov bx, ax 
    
    mov ah, 42h
    mov al, 2
    mov cx, 0
    mov dx, 0
    int 21h
      
    mov ah, 40h  
    mov dx, offset TEMP_STR
    mov cx, LEN_STR      
    int 21h
    
    mov dx, 0Dh
    mov buff, dl
    
    mov ah, 40h  
    mov dx, offset buff
    mov cx, 1      
    int 21h
    
    mov dx, 0Ah
    mov buff, dl
    
    mov ah, 40h  
    mov dx, offset buff
    mov cx, 1      
    int 21h  
    ret    
endp
end start