;The program is deleting all files according to the entered pattern
code segment
ASSUME  CS:code,DS:code,ES:code
ORG 100H
;=====================================================================
print_mes macro message
local msg, nxt
    push AX
    push DX
 
    mov DX, offset msg
    mov AH, 09h
    int 21h
 
    pop DX
    pop AX
 
    jmp nxt
    msg DB message,"$"
    nxt:
endm
;=====================================================================
start_new_line macro
    push AX
    push DX
    
    mov DL, CR
    mov AH, 02h
    int 21h
    mov DL, LF
    mov AH, 02h
    int 21h
    
    pop DX
    pop AX
endm
;=====================================================================
start:
    ; вводим файл
    start_new_line
    print_mes 'Input File Name > '
    mov AH, 0Ah
    mov DX, offset FileName
    int 21h
    start_new_line
    start_new_line
    
    xor BH, BH
    mov BL, FileName[1]
    mov FileName[BX+2], 0
    
    ; по умолчанию DTA находится в PSP, но мы можем задать ей другое расположение
    mov ah,1ah
    mov dx,offset dta
    int 21h
;=====================================================================
    ; ищем первый файл
    mov ah,4eh
    xor cx,cx
    mov dx,offset FileName+2
    int 21h
    jc not_found
;=====================================================================
delete_next:
    mov si,offset dta + 1eh
    mov dh,0Dh 
    call print_filename
    print_mes ' is deleted'
    start_new_line
    
    ; удаляем
    mov ah, 41h
    mov dx, offset dta + 1eh
    int 21h
    
    ; ищем следующий файл
    mov ah,4fh
    mov dx,offset dta
    int 21h
    jnc delete_next
    jmp quit
;=====================================================================
print_filename proc near
    Cycle:
        mov     dl,[si]
        cmp     dl, ''      
        jne    Print
        jmp _end
    Print:
        mov     ah,02h          
        int     21h
        inc     si
        loop Cycle      
    _end:
        ret
print_filename endp
;=====================================================================
not_found:
    print_mes 'File is not found'
    jmp quit
;=====================================================================
quit:
    start_new_line
    mov ah,9h
    mov dx,offset message
    int 21h
    
    ; задержка
    xor ax,ax
    int 16h
   
    mov ah,4ch
    int 21h
;=====================================================================
CR      EQU 0Dh
LF      EQU 0Ah
FileName     db 20 dup (' ')
dta      db     2ch dup (?)
;        db "$"
message  db 'Press any key...','$'
;=====================================================================
code ends
end start