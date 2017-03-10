.MODEL small
.STACK 100h
;������� 11. �������� ��������� ������� � ������
.CODE
BEGIN:
mov ax, @data
mov ds, ax
mov es, ax       
xor ax, ax

;���� ����� � ����� ���������
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
mov cl, str1l       ; �������� � cx ���������� �������� � �������� ������
sub cl, str2l
inc cl              
cld                 
lea di, str2        ; �������� � di ����� ������ ��� ������
lea si, str1        ; �������� � si ����� �������� ������
xor ax, ax
call TRANSLATE

CHECK_STRING:       ; ��������� ����������� ����� ��� �� ���
mov def, 0          ; �������� ������� ��������
call SEARCH_SUBSTRING
inc si
add si, def         ;�������� ������� �� ���������� ����������� ��������
mov dx, def
add ins, dx         ;����������� ������ ���������
add str1_[1], dl    ;��������� ����� ������
inc ins
loop CHECK_STRING

call DELETE_SPACE
lea dx, MSG4
call OUTPUT_STRING
lea dx, str1        ; ������� �������� ������
call OUTPUT_STRING 

END:
mov ax, 4c00h
int 21h

; **** Procedures ****

; ��������� ����� ������
INPUT_STRING proc
    push ax
    mov ah, 0ah
    int 21h
    pop ax
    ret
INPUT_STRING endp

;��������� ������ ������
OUTPUT_STRING proc
    push ax
    mov ah, 09h
    int 21h
    pop ax 
    ret
OUTPUT_STRING endp

; ��������� ���������� ���������
; ��������� �������� �� ������,
; ������� ������, ������� ���
; � �������� �� ����� ��� ������
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

; �������� ��������� �� �������� ������
; ����� ����������� ���� �� si � di
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

;��������� ������� ����� � ������
CHANGE proc
    pusha
    push ins                            ;���������� � ����� ������� ���������
    lea si, str1_
    lea di, str3_
    ;len1
    mov ch, str1_[1]                    ;����������� ����� �����
    mov cl, str3_[1]
    xor bx, bx
    xor di, di
    Outer_Cycl:
        mov dl, str3[di]                ;�������� � ���� ��������� �������� �� ���������
        push dx
        mov bl, ch
        mov si, bx
        cycl:                           ;� ����� �������� ������ ������ �� ������� ���������
            mov dl, str1[si-1]
            mov str1[si], dl
            dec si
            cmp ins, si
            jne cycl
        pop dx
        mov str1[si], dl                ;��������� ������
        
        inc si
        inc di
        inc ch
        inc ins
        inc def
        xor dx, dx
        mov dl, cl
        cmp di, dx 
        jne Outer_Cycl                  ;���� ��������� ����� ���������
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
    mov ch, str2_[1]                    ;����������� ����� �����
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
MSG1 DB "������� ������: $"
MSG2 DB 0Ah, 0Dh, "������� ������ ��� ������: $"
MSG3 DB 0Ah, 0Dh, "������� ������ ��� ������: $"
MSG4 DB 0Ah, 0Dh, "������ ����� ������: $"
LENGTH equ 200
str1_ DB LENGTH
str1l DB '$'                  ;�������� ������
str1 DB LENGTH dup('$')

str2_ DB LENGTH
str2l DB '$'                  ;������ ��� ������
str2 DB LENGTH dup('$')

str3_ DB LENGTH
str3l DB '$'                  ;������ ��� ������
str3 DB LENGTH dup('$')

space DB ' ' 
ins dw 0
def dw 0
trans dw 0
drt dw 0

end BEGIN