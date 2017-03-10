.MODEL small
.STACK 100h
;Вариант 11. Заменить подстроку строкой в строке
.CODE
BEGIN:
mov ax, @data
mov ds, ax
mov es, ax       
xor ax, ax

;Ввод строк и вывод сообщений
lea dx, MSG1
call OUTPUT_STRING

lea dx, str1_
call INPUT_STRING

lea dx, MSG2
call OUTPUT_STRING

lea dx, str2_
call INPUT_STRING

lea dx, MSG3
call OUTPUT_STRING

lea dx, str3_
call INPUT_STRING

xor cx, cx
mov cl, str1l       ; помещает в cx количество символов в исходной строке
sub cl, str2l
inc cl              
cld                 
lea di, str2        ; помещает в di адрес строки для поиска
lea si, str1        ; помещает в si адрес исходной строки
xor ax, ax
call TRANSLATE

CHECK_STRING:       ; повторять уменьшенную длину кол во раз
mov def, 0          ; обнулить счетчик разности
call SEARCH_SUBSTRING
inc si
add si, def         ;сдвинуть счетчик на количество вставленных символов
mov dx, def
add ins, dx         ;переместить индекс вхождения
add str1_[1], dl    ;увеличить длину строки
inc ins
loop CHECK_STRING

call DELETE_SPACE
lea dx, MSG4
call OUTPUT_STRING
lea dx, str1        ; вывести исходную строку
call OUTPUT_STRING 

END:
mov ax, 4c00h
int 21h

; **** Procedures ****

; процедура ввода строки
INPUT_STRING proc
    push ax
    mov ah, 0ah
    int 21h
    pop ax
    ret
INPUT_STRING endp

;процедура вывода строки
OUTPUT_STRING proc
    push ax
    mov ah, 09h
    int 21h
    pop ax 
    ret
OUTPUT_STRING endp

; процедура нахождения подстроки
; процедура проходит по строке,
; находит нужное, удаляет его
; и заменяет на слово для замены
SEARCH_SUBSTRING proc
    push cx
    push di
    push si
    mov bx, si
    mov cl, str2l
    repe cmpsb              
    je _EQ
    jne _NEQ
    _EQ:
    pusha
    push ins 
    xor si, si
    xor dx, dx
    mov dl, str2_[1]
    add ins, dx
    mov dx, ins
    mov si, dx
    mov bl, str1[si]
    cmp str1[si], ' '
    pop ins
    popa
    jne _NEQ                        
    call DELETE
    call CHANGE
    inc al
    _NEQ:
    pop si
    pop di
    pop cx
    ret
SEARCH_SUBSTRING endp

; удаление подстроки из исходной строки
; путем перемещения байт из si в di
DELETE proc
    push bx
    push di
    push si
    mov di, bx 
    xor cx, cx
    mov cl, str1l
    repe movsb              
    pop si
    pop di
    pop bx
    ret
DELETE endp

;процедура вставки слова в строку
CHANGE proc
    pusha
    push ins                            ;сохранение в стеке индекса вхождения
    lea si, str1_
    lea di, str3_
    ;len1
    mov ch, str1_[1]                    ;определение длины строк
    mov cl, str3_[1]
    xor bx, bx
    xor di, di
    Outer_Cycl:
        mov dl, str3[di]                ;помещаем в стек очередное значение из подстроки
        push dx
        mov bl, ch
        mov si, bx
        cycl:                           ;в цикле сдвигаем строку вправо до индекса вхождения
            mov dl, str1[si-1]
            mov str1[si], dl
            dec si
            cmp ins, si
            jne cycl
        pop dx
        mov str1[si], dl                ;вставляем символ
        
        inc si
        inc di
        inc ch
        inc ins
        inc def
        xor dx, dx
        mov dl, cl
        cmp di, dx 
        jne Outer_Cycl                  ;пока непройдем слово полностью
    pop ins
    dec def    
    popa
    ret
CHANGE endp

TRANSLATE PROC
    pusha
    lea si, str2_
    lea di, str3_
    xor bx, bx
    xor di, di
    xor si, si
    mov ch, str2_[1]                    ;определение длины строк
    mov cl, str3_[1]
    mov bl, ch
    mov si, bx
    cycl1:
            mov dl, str2[si-1]
            mov str2[si], dl
            dec si
            cmp trans, si
            jne cycl1
    mov dl, space
    mov str2[si], dl
    add str2_[1], 1
    mov bl, cl
    mov di, bx
    cycl2:
            mov dl, str3[di-1]
            mov str3[di], dl
            dec di
            cmp trans, di
            jne cycl2
    mov dl, space
    mov str3[di], dl
    add str3_[1], 1
    lea si, str1_
    xor si, si
    xor cx, cx
    mov ch, str1_[1]
    mov bl, ch
    mov si, bx
    cycl3:
            mov dl, str1[si-1]
            mov str1[si], dl
            dec si
            cmp trans, si
            jne cycl3
    mov dl, space
    mov str1[si], dl
    add str1_[1], 1
    xor si, si
    xor cx, cx
    mov ch, str1_[1]
    mov bl, ch
    mov si, bx
    mov dl, space
    mov str1[si], dl
    add str1_[1], 1        
    popa
    ret
endp TRANSLATE

DELETE_SPACE PROC
    pusha
    lea si, str1_
    xor si, si
    xor cx, cx
    xor dx, dx
    mov ch, str1_[1]
    mov bl, ch
    mov di, bx
    xor si, si
    cycle:
        mov dl, str1[si+1]
        mov str1[si], dl
        inc si
        cmp si, di
        jne cycle
    sub str1_[1], 1
    popa
    ret    
endp DELETE_SPACE    

.DATA
MSG1 DB "Введите строку: $"
MSG2 DB 0Ah, 0Dh, "Введите строку для поиска: $"
MSG3 DB 0Ah, 0Dh, "Введите строку для замены: $"
MSG4 DB 0Ah, 0Dh, "Строка после замены: $"
LENGTH equ 200
str1_ DB LENGTH
str1l DB '$'                  ;исходная строка
str1 DB LENGTH dup('$')

str2_ DB LENGTH
str2l DB '$'                  ;строка для поиска
str2 DB LENGTH dup('$')

str3_ DB LENGTH
str3l DB '$'                  ;строка для замены
str3 DB LENGTH dup('$')

space DB ' ' 
ins dw 0
def dw 0
trans dw 0
drt dw 0

end BEGIN