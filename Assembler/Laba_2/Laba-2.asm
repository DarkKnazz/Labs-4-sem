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

lea dx, MSG2
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

lea dx, MSG3
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
    xor bx, bx
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

ins dw 0
def dw 0

end BEGIN