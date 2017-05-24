.model tiny
.org 100h  
.data    
    
     PATH db 126 dup(0)
     BUFFER          db      64      dup('$')
     IO_ERROR        db "Unable to open the file.$"                                                             
     COMMAND_ERROR   db "Empty command line.$"
     HANDLE          dw      0           
        
OUTPUT MACRO outLine                   ; макрос вывода строки на экран
    mov ah, 09h  
    lea dx, outLine
    int 21h     
endm                            
    
PARSE_PATH PROC                        ; процедура парсинга командной строки
    xor cx,cx          
    mov si, 80h
    mov cl, es:[si]                    ; кол-во символов в командной строке
    
    cmp cx, 0
    je command_Undefined
    
    inc si
    mov al, es:[si] 
    cmp al, ' '
    je next_step
cycle:
    mov al, es:[si]        
    cmp al, 13
    je next_step 
    cmp al, ' '    
    mov [di], al   
    inc di
next_step:
    inc si 
    loop cycle
    ret
endp 

file_Undefined:                            
    OUTPUT [IO_ERROR]
    jmp exit  
    
command_Undefined:
    OUTPUT [COMMAND_ERROR]              
    jmp exit 


OPEN_FILE proc
        pusha
        lea dx, PATH                       ; путь до открываемого файла
        mov ah, 3Dh                        ; функция отрытия файла 
        mov al, 00h                        ; только чтение
        int 21h 
    
        jc file_Undefined                  
        
        mov [HANDLE], ax              
       
        popa        
        ret                                

OPEN_FILE endp 

CLOSE_FILE proc
        pusha
        mov     ah, 3eh 
        mov     bx, [HANDLE]   
        int     21h 
        popa        
CLOSE_FILE endp  
   
NEW_INT proc near 
        pushf
        cli    
interruptCycle:        
        mov     ah, 01h                   
        int     16h                      
        jz      interruptCycle               
        sti
        popf                               
        iret                            
        
NEW_INT endp    
   
PRINT_FILE proc
        mov bx, [HANDLE]        
startWriting:                         
        
        mov     cx, 1h                    
        mov     ah, 3fh                   
        lea     dx, es:[BUFFER]             
        int     21h                    
        
        cmp     ax, 0                   
        je      EXIT_WRITING_FROM_FILE                 
        
        mov     ah, 09h               
        mov     dx, offset es:[BUFFER]    
        int     21h                       
        
        mov     cx, 00H                    
        mov     dx, 6666H              
        mov     ah, 86H                   
        int     15H                       
        
        jmp     startWriting                      

EXIT_WRITING_FROM_FILE:  
        ret 
       
PRINT_FILE endp    
               
.code   
        OLD_INT dd 0
               
START:  
        lea di, PATH     
        call    PARSE_PATH  
        lea dx, PATH
        xor     ax, ax                   
        call    OPEN_FILE                
        mov     ax, 351Bh
        int     21h
        
        mov     word ptr old_int, bx        
        mov     word ptr old_int+2, es 
        
        mov     ax, 251Bh                   
        push    cx                          
        push    ds                          
        mov     dx, offset NEW_INT          
        int     21h                         
        call    PRINT_FILE
        call    CLOSE_FILE       
        
exit:                       
        mov     ax, 4c00h    
        int     21h                        

end START