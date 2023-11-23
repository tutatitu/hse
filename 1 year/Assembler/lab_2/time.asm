;The program displays a message on the screen at the specified day and time.
;The resident is protected from reloading, the unloading of the resident is implemented.
.286
;+--------------------------------------------------------------------------
code_seg segment
        ASSUME  CS:CODE_SEG,DS:code_seg,ES:code_seg
    org 100h
start:
    jmp begin
;----------------------------------------------------------------------------
int_2Fh_vector  DD  ?
old_1ch         DD  ?
PRINT       PROC FAR
    MOV AH,09H
    INT 21H
    RET
PRINT       ENDP
;----------------------------------------------------------------------------
 
print_hex proc FAR
and DL,0Fh
add DL,30h
cmp DL,3Ah
jl $print
add DL,07h
$print:
int 21H
 ret
print_hex endp
PRINT_CRLF macro 
     push AX
     push DX
     mov DL,13
     mov AH,02
     int 21h ; print CR
     mov DL,10
     mov AH,02
     int 21h ; print LF
     pop DX
     pop AX
 ENDm
 print_reg_AX proc FAR
    push AX
    push BX
    push CX
    push DX
    ;
    mov BX, AX
    mov AH,02
     mov DL,BH
    rcr DL,4
    call print_hex
     mov DL,BH
    call print_hex
    mov DL,BL
    rcr DL,4
    call print_hex
    mov DL,BL
    call print_hex
    pop DX
    pop CX
    pop BX
    pop AX
    ret
    print_reg_AX endp
;============================================================================
new_1ch proc far                  ;новый обработчик прерывания 1Ch
    jmp data
    menu        DB  'Please write a time in following format dd:hh:mm:ss',13,10,'$'
    days        DB  'Monday - mn',13,10,'Tuesday - ts',13,10,'Wednesday - ws',13,10,'Thursday - th',13,10,'Friday - fr',13,10,'Saturday - st',13,10,'Sunday - sd',13,10,'$'
    wrong_format    DB  'WRONG FORMAT!',13,10,'$'
    buffer DB 42,0,42 dup (0)
    minutes     DB  ?
    hours       DB  ?
    seconds     DB  ?
    day_of_week DB  2 dup(0),'$'
    day_of_week_number  DB  ?
    current_day     DB  ?
    current_hour    DB  ?
    current_minute  DB  ?
    current_second  DB  ?
    flag            DB  0
    flag2           DB  0
    mess            DB  'ok','$'
    text1           DB  'Hello world!',13,10,'$'
    data:
    sti                 ; Не будем мешать таймеру
    in      AL,61h      ; Введем содержимое порта B
    or      AL,80h      ; Установим старший бит
    out     61h,AL      ; и вернем в порт B.
    and     AL,7Fh      ; Снова разрешим работу клавиатуры,
    out     61h,AL      ; сбросив старший бит порта B.
    cli
    mov     AL, 20h      ; Пошлем
    ;сброс происходит для того, чтобы могли выполнятся прерывания с меньшим приоритетом
    out     20h,AL       ; приказ END OF INTERRUPT (EOF)
    pushf
    pusha
    push ds
    push cs
    pop ds
    cmp flag2,0
    je input1
        jmp input
    input1:
        mov flag2,1
        mov day_of_week_number,10h
        pusha
        mov dx,offset menu
        call print
        mov dx,offset days
        call print
        mov AH, 0Ah ;ввод строки
        mov DX, offset buffer ;в буфер 
        int 21h
        PRINT_CRLF
        xor Bx, Bx
        mov BL, buffer[1]
        mov buffer[BX+2], '$'
        cmp bx,0BH
        je wrong_format_metka
            mov dx,offset wrong_format
            call print
            int 20h
        wrong_format_metka:
        mov al,buffer[2]
        mov day_of_week[0],al
        mov al,buffer[3]
        mov day_of_week[1],al
        cmp day_of_week[0],'m'
        jne monday1
            cmp day_of_week[1],'n'
            jne monday2
                mov day_of_week_number,1
            monday2:
        monday1:
        
        cmp day_of_week[0],'t'
        jne tuesday1
            cmp day_of_week[1],'s'
            jne tuesday2
                mov day_of_week_number,2
            tuesday2:
        tuesday1:
        
        cmp day_of_week[0],'w'
        jne wednesday1
            cmp day_of_week[1],'s'
            jne wednesday2
                mov day_of_week_number,3
            wednesday2:
        wednesday1:
        
        cmp day_of_week[0],'t'
        jne thursday1
            cmp day_of_week[1],'h'
            jne thursday2
                mov day_of_week_number,4
            thursday2:
        thursday1:
        
        cmp day_of_week[0],'f'
        jne friday1
            cmp day_of_week[1],'r'
            jne friday2
                mov day_of_week_number,5
            friday2:
        friday1:
        
        cmp day_of_week[0],'s'
        jne saturday1
            cmp day_of_week[1],'t'
            jne saturday2
                mov day_of_week_number,6
            saturday2:
        saturday1:
        
        cmp day_of_week[0],'s'
        jne sunday1
            cmp day_of_week[1],'d'
            jne sunday2
                mov day_of_week_number,0
            sunday2:
        sunday1:
        
        
        mov al,buffer[5]
        sub al,'0'
        mov bl,10
        mul bl
        add hours,al
        mov al,buffer[6]
        sub al,'0'
        add hours,al
        
        mov al,buffer[8]
        sub al,'0'
        mov bl,10
        mul bl
        add minutes,al
        mov al,buffer[9]
        sub al,'0'
        add minutes,al
        
        mov al,buffer[11]
        sub al,'0'
        mov bl,10
        mul bl
        add seconds,al
        mov al,buffer[12]
        sub al,'0'
        add seconds,al
        cmp day_of_week_number,10h
        jne wrong_format_day
            mov dx,offset wrong_format
            call print
            int 20h
        wrong_format_day:
        cmp hours,24
        jbe wrong_format_hours
            mov dx,offset wrong_format
            call print
            int 20h
        wrong_format_hours:
        cmp minutes,60
        jbe wrong_format_minutes
            mov dx,offset wrong_format
            call print
            int 20h
        wrong_format_minutes:
        cmp seconds,60
        jbe wrong_format_seconds
            mov dx,offset wrong_format
            call print
            int 20h
        wrong_format_seconds:
        popa
    input:
    mov ah,2ah
    int 21h
    mov current_day,al
    mov ah,2ch
    int 21h
    mov current_hour,ch
    mov current_minute,cl
    mov current_second,dh
    mov ah,CS:day_of_week_number
    cmp CS:current_day,ah
    jne right_day
        mov ah,CS:hours
        cmp current_hour,ah
        jne right_hour
            mov ah,CS:minutes
            cmp current_minute,ah
            jne right_minute
                mov ah,CS:seconds
                cmp current_second,ah
                jne right_second
                    cmp flag,0
                    jne all_is_good
                        mov dx,offset text1
                        call print
                        mov flag,1
                    all_is_good:
                right_second:
            right_minute:
        right_hour:
    right_day:
    mov ah,CS:seconds
    cmp current_second,ah
    je dec_flag
        mov flag,0
    dec_flag:
    pop ds
    popa
    popf
    jmp     dword ptr CS:[old_1ch]
    iret
new_1ch endp
;============================================================================
 
;============================================================================
;============================================================================
int_2Fh proc far
    cmp     AH,0C7h         ; Наш номер?
    jne     Pass_2Fh        ; Нет, на выход
    cmp     AL,00h          ; Подфункция проверки на повторную установку?
    je      inst            ; Программа уже установлена
    cmp     AL,01h          ; Подфункция выгрузки?
    je      unins           ; Да, на выгрузку
    jmp     short Pass_2Fh  ; Неизвестная подфункция - на выход
inst:
    mov     AL,0FFh         ; Сообщим о невозможности повторной установки
    iret
Pass_2Fh:
    jmp dword PTR CS:[int_2Fh_vector]
;
; -------------- Проверка - возможна ли выгрузка программы из памяти ? ------
unins:
    push    BX
    push    CX
    push    DX
    push    ES
;
    mov     CX,CS   ; Пригодится для сравнения, т.к. с CS сравнивать нельзя
    
    mov     AX,351Ch    ; Проверить вектор 1Ch
    int     21h ; Функция 35h в AL - номер прерывания. Возврат-вектор в ES:BX
;
    mov     DX,ES
    cmp     CX,DX
    jne     Not_remove
;
    cmp     BX, offset CS:new_1ch
    jne     Not_remove
    mov     AX,352Fh    ; Проверить вектор 2Fh
    int     21h ; Функция 35h в AL - номер прерывания. Возврат-вектор в ES:BX
;
    mov     DX,ES
    cmp     CX,DX
    jne     Not_remove
;
    cmp     BX, offset CS:int_2Fh
    jne     Not_remove
; ---------------------- Выгрузка программы из памяти ---------------------
;
    push    DS
 
    lds     DX, CS:old_1ch   ; Эта команда эквивалентна следующим двум
    mov     AX,251Ch        ; Заполнение вектора старым содержимым
    int     21h
;
    lds     DX, CS:int_2Fh_vector   ; Эта команда эквивалентна следующим двум
    mov     AX,252Fh
    int     21h
;
    pop     DS
;
    mov     ES,CS:2Ch       ; ES -> окружение
    mov     AH, 49h         ; Функция освобождения блока памяти
    int     21h
;
    mov     AX, CS
    mov     ES, AX          ; ES -> PSP выгрузим саму программу
    mov     AH, 49h         ; Функция освобождения блока памяти
    int     21h
;
    mov     AL,0Fh          ; Признак успешной выгрузки
    jmp     short pop_ret
Not_remove:
    mov     AL,0F0h          ; Признак - выгружать нельзя
pop_ret:
    pop     ES
    pop     DX
    pop     CX
    pop     BX
;
    iret
int_2Fh endp
;============================================================================
begin:
        ;сначала введем дату
        
        ;инициализирующая часть
        mov CL,ES:80h       ; Длина хвоста в PSP
        ;начиная с 81 находится хвост, в котором параметры
        cmp CL,0            ; Длина хвоста=0?
        je  check_install   ; Да, программа запущена без параметров,
                            ; попробуем установить
        xor CH,CH       ; CX=CL= длина хвоста
        cld             ; DF=0 - флаг направления вперед
        mov DI, 81h     ; ES:DI-> начало хвоста в PSP
        mov SI,offset key   ; DS:SI-> поле key
        mov AL,' '          ; Уберем пробелы из начала хвоста
repe    scasb   ; Сканируем хвост пока пробелы
                ; AL - (ES:DI) -> флаги процессора
                ; повторять пока элементы равны
        dec DI          ; DI-> на первый символ после пробелов
        mov CX, 4       ; ожидаемая длина команды
repe    cmpsb   ; Сравниваем введенный хвост с ожидаемым
                ; (DS:DI)-(ES:DI) -> флаги процессора
        jne check_install ; Неизвестная команда - попробуем установить
        inc flag_off
; Проверим, не установлена ли уже эта программа
check_install:
        mov AX,0C700h   ; AH=0C7h номер процесса C7h
        ;; выбрали номер C7, он закреплен за нашей программой
                        ; AL=00h -дать статус установки процесса
                        ;; для проверки, есть ли в памяти
        int 2Fh         ; мультиплексное прерывание
        ;;проходит через все обработчики C7 -пользовательский номер
        cmp AL,0FFh
        ; проверяет, установлена ли уже
        je  already_ins ; возвращает AL=0FFh если установлена
;----------------------------------------------------------------------------
    cmp flag_off,1
    je  xm_stranno
;----------------------------------------------------------------------------
    ; штатная установка программы
    
    ;получение вектора
    mov AX,352Fh                      ;   получить с помощью 35 функции в АН и 2Ф в АЛ
                                      ;   вектор
    int 21h                           ;   прерывания  2Fh
    mov word ptr int_2Fh_vector,BX    ;   ES:BX - вектор
    mov word ptr int_2Fh_vector+2,ES  ;
;
    
    ;установка вектора
    
    mov DX,offset int_2Fh           ;   получить смещение точки входа в новый
                                    ;   обработчик на DX
    mov AX,252Fh                    ;   функция установки прерывания
                                    ;   изменить вектор 2Fh
    int 21h  ; AL - номер прерыв. DS:DX - указатель программы обработки прер.
;============================================================================
    
;
    mov AX,351Ch                        ;   получить
                                        ;   вектор
    int 21h                             ;   прерывания  1Ch
    mov word ptr old_1ch,BX    ;   ES:BX - вектор
    mov word ptr old_1ch+2,ES  ;
    mov DX,offset new_1ch           ;   получить смещение точки входа в новый
;                                   ;   обработчик на DX
    mov AX,251Ch                        ;   функция установки прерывания
                                        ;   изменить вектор 1Ch
    
    int 21h ;   AL - номер прерыв. DS:DX - указатель программы обработки прер.
    
    mov DX,offset msg1  ; Сообщение об установке
    call    print
;----------------------------------------------------------------------------
    mov DX,offset   begin           ;   оставить программу ...
    int 27h                         ;   ... резидентной и выйти
;============================================================================
already_ins:
        cmp flag_off,1      ; Запрос на выгрузку установлен?
        je  uninstall       ; Да, на выгрузку
        lea DX,msg          ; Вывод на экран сообщения: already installed!
        call    print
        int 20h
; ------------------ Выгрузка -----------------------------------------------
 uninstall:
        mov AX,0C701h  ; AH=0C7h номер процесса C7h, подфункция 01h-выгрузка
        int 2Fh             ; мультиплексное прерывание
        cmp AL,0F0h
        je  not_sucsess
        cmp AL,0Fh
        jne not_sucsess
        mov DX,offset msg2  ; Сообщение о выгрузке
        call    print
        int 20h
not_sucsess:
        mov DX,offset msg3  ; Сообщение, что выгрузка невозможна
        call    print
        int 20h
xm_stranno:
        mov DX,offset msg4  ; Сообщение, программы нет, а пользователь
        call    print       ; дает команду выгрузки
        int 20h
;----------------------------------------------------------------------------
key         DB  '/off'
flag_off    DB  0
msg         DB  'already '
msg1        DB  'installed',13,10,'$'
msg4        DB  'just '
msg3        DB  'not '
msg2        DB  'uninstalled',13,10,'$'
 
 
;============================================================================
 
;;============================================================================
code_seg ends
         end start
