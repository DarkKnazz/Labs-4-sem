.MODEL small
.STACK 100h
;¬ариант 11. «аменить подстроку строкой в строке
.CODE
BEGIN:
mov ax, @data
mov ds, ax
mov es, ax       
xor ax, ax

;¬вод строк и вывод сообщений
lea dx, MSG1
call OUTPUT_STRING

lea dx, str1_
call INPUT_STRING

lea dx, MSG2
call OUTPUT_STRING

lea dx, str2_
call INPUT_STRING

lea dx, MSG2
call OUTPUT_STRING

lea dx, str3_
call INPUT_STRING

xor cx, cx
mov cl, str1l       ; помещает в cx количество символов в исходной строке
sub cl, str2l
inc cl              
cld                 
lea di, str2        ; помещает в di адрес строки дл€ поиска
lea si, str1        ; помещает в si адрес исходной строки
xor ax, ax

CHECK_STRING:       ; повтор€ть уменьшенную длину кол во раз
mov def, 0          ; обнулить счетчик разности
call SEARCH_SUBSTRING
inc si
add si, def         ;сдвинуть счетчик на количество вставленных символов
mov dx, def
add ins, dx         ;переместить индекс вхождени€
add str1_[1], dl    ;увеличить длину строки
inc ins
loop CHECK_STRING

lea dx, MSG3
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

; процедура нахождени€ подстроки
; процедура проходит по строке,
; находит нужное, удал€ет его
; и замен€ет на слово дл€ замены
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
; путем перемещени€ байт из si в di
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
    push ins                            ;сохранение в стеке индекса вхождени€
    lea si, str1_
    lea di, str3_
    ;len1
    mov ch, str1_[1]                    ;определение длины строк
    mov cl, str3_[1]
    xor bx, bx
    xor di, di
    xor bx, bx
    Outer_Cycl:
        mov dl, str3[di]                ;помещаем в стек очередное значение из подстроки
        push dx
        mov bl, ch
        mov si, bx
        cycl:                           ;в цикле сдвигаем строку вправо до индекса вхождени€
            mov dl, str1[si-1]
            mov str1[si], dl
            dec si
            cmp ins, si
            jne cycl
        pop dx
        mov str1[si], dl                ;вставл€ем символ
        
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

.DATA
MSG1 DB "¬ведите строку: $"
MSG2 DB 0Ah, 0Dh, "¬ведите строку дл€ поиска: $"
MSG3 DB 0Ah, 0Dh, "¬ведите строку дл€ замены: $"
MSG4 DB 0Ah, 0Dh, "—трока после замены: $"
LENGTH equ 200
str1_ DB LENGTH
str1l DB '$'                  ;исходна€ строка
str1 DB LENGTH dup('$')

str2_ DB LENGTH
str2l DB '$'                  ;строка дл€ поиска
str2 DB LENGTH dup('$')

str3_ DB LENGTH
str3l DB '$'                  ;строка дл€ замены
str3 DB LENGTH dup('$')

ins dw 0
def dw 0

end BEGIN