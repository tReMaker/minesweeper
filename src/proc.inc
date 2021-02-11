;#############################################
;Рисуем рамку
;#############################################
paintpole proc
;------- Устанавливаем перо белого цвета ------
        push    L 0ffffffh
        push    L 1
        push    L 0
        call    CreatePen
        mov     [idpen],eax

        push    [idpen]
        push    [theDC]
        call    SelectObject
        mov     [idpenold],eax        
;-------------- *** 1 *** ----------------
        push    offset curpos
        push    L 321
        push    L 0
        push    [theDC]
        call    MoveToEx

        push    L 0
        push    L 0
        push    [theDC]
        call    LineTo

        push    L 0
        push    L 503
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 320
        push    L 1
        push    [theDC]
        call    MoveToEx

        push    L 1
        push    L 1
        push    [theDC]
        call    LineTo

        push    L 1
        push    L 502
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 319
        push    L 2
        push    [theDC]
        call    MoveToEx

        push    L 2
        push    L 2
        push    [theDC]
        call    LineTo

        push    L 2
        push    L 501
        push    [theDC]
        call    LineTo

;----------- *** 4 *** ------------
        push    offset curpos
        push    L 45
        push    L 10
        push    [theDC]
        call    MoveToEx

        push    L 45
        push    L 494
        push    [theDC]
        call    LineTo

        push    L 9
        push    L 494
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 44
        push    L 11
        push    [theDC]
        call    MoveToEx

        push    L 44
        push    L 493
        push    [theDC]
        call    LineTo

        push    L 10
        push    L 493
        push    [theDC]
        call    LineTo

;----------- *** 5 *** ---------------- 
 
        push    offset curpos
        push    L 313
        push    L 10
        push    [theDC]
        call    MoveToEx

        push    L 313
        push    L 494
        push    [theDC]
        call    LineTo

        push    L 52
        push    L 494
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 312
        push    L 11
        push    [theDC]
        call    MoveToEx

        push    L 312
        push    L 493
        push    [theDC]
        call    LineTo

        push    L 53
        push    L 493
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 311
        push    L 12
        push    [theDC]
        call    MoveToEx

        push    L 311
        push    L 492
        push    [theDC]
        call    LineTo

        push    L 54
        push    L 492
        push    [theDC]
        call    LineTo

;----------- *** 7 *** ---------------- 
 
        push    offset curpos
        push    L 39
        push    L 17
        push    [theDC]
        call    MoveToEx

        push    L 39
        push    L 56
        push    [theDC]
        call    LineTo

        push    L 15
        push    L 56
        push    [theDC]
        call    LineTo

;----------- *** 9 *** ---------------- 
 
        push    offset curpos
        push    L 39
        push    L 433
        push    [theDC]
        call    MoveToEx

        push    L 39
        push    L 485
        push    [theDC]
        call    LineTo

        push    L 15
        push    L 485
        push    [theDC]
        call    LineTo

;----------- *** 11 *** ---------------- 
 
        push    offset curpos
        push    L 39
        push    L 76
        push    [theDC]
        call    MoveToEx

        push    L 39
        push    L 90
        push    [theDC]
        call    LineTo

        push    L 15
        push    L 90
        push    [theDC]
        call    LineTo

;------- Устанавливаем перо серого цвета ------
        push    [idpenold]
        push    [theDC]
        call    SelectObject
        
        push    [idpen]
        call    DeleteObject

        push    L 0808080h
        push    L 1
        push    L 0
        call    CreatePen
        mov     [idpen],eax

        push    [idpen]
        push    [theDC]
        call    SelectObject
        mov     [idpenold],eax 

;------------ *** 2 *** ----------------
        push    offset curpos
        push    L 322
        push    L 1
        push    [theDC]
        call    MoveToEx

        push    L 322
        push    L 503
        push    [theDC]
        call    LineTo

        push    L 0
        push    L 503
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 321
        push    L 2
        push    [theDC]
        call    MoveToEx

        push    L 321
        push    L 502
        push    [theDC]
        call    LineTo

        push    L 1
        push    L 502
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 320
        push    L 3
        push    [theDC]
        call    MoveToEx

        push    L 320
        push    L 501
        push    [theDC]
        call    LineTo

        push    L 2
        push    L 501
        push    [theDC]
        call    LineTo

;------------- *** 3 *** -----------
        push    offset curpos
        push    L 44
        push    L 9
        push    [theDC]
        call    MoveToEx

        push    L 9
        push    L 9
        push    [theDC]
        call    LineTo

        push    L 9
        push    L 494
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 43
        push    L 10
        push    [theDC]
        call    MoveToEx

        push    L 10
        push    L 10
        push    [theDC]
        call    LineTo

        push    L 10
        push    L 493
        push    [theDC]
        call    LineTo

;----------- *** 6 *** ---------------- 
 
        push    offset curpos
        push    L 312
        push    L 9
        push    [theDC]
        call    MoveToEx

        push    L 52
        push    L 9
        push    [theDC]
        call    LineTo

        push    L 52
        push    L 494
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 311
        push    L 10
        push    [theDC]
        call    MoveToEx

        push    L 53
        push    L 10
        push    [theDC]
        call    LineTo

        push    L 53
        push    L 493
        push    [theDC]
        call    LineTo

        push    offset curpos
        push    L 310
        push    L 11
        push    [theDC]
        call    MoveToEx

        push    L 54
        push    L 11
        push    [theDC]
        call    LineTo

        push    L 54
        push    L 492
        push    [theDC]
        call    LineTo

;----------- *** 8 *** ---------------- 
 
        push    offset curpos
        push    L 38
        push    L 16
        push    [theDC]
        call    MoveToEx

        push    L 15
        push    L 16
        push    [theDC]
        call    LineTo

        push    L 15
        push    L 56
        push    [theDC]
        call    LineTo

;----------- *** 10 *** ---------------- 
 
        push    offset curpos
        push    L 38
        push    L 432
        push    [theDC]
        call    MoveToEx

        push    L 15
        push    L 432
        push    [theDC]
        call    LineTo

        push    L 15
        push    L 485
        push    [theDC]
        call    LineTo

;----------- *** 12 *** ---------------- 
 
        push    offset curpos
        push    L 38
        push    L 76
        push    [theDC]
        call    MoveToEx

        push    L 15
        push    L 76
        push    [theDC]
        call    LineTo

        push    L 15
        push    L 90
        push    [theDC]
        call    LineTo

;---------- Удаляем перо  ----------
        push    [idpenold]
        push    [theDC]
        call    SelectObject
        
        push    [idpen]
        call    DeleteObject

        ret
paintpole endp


;#############################################
;Рисуем цифры, рожицу, фон, плитки и т.п.
;#############################################
paintdigit proc
        push    [theDC]
        call    CreateCompatibleDC
        mov     [memDC],eax

        push    [iddigit]
        push    [memDC]
        call    SelectObject
        mov     [oldbmp],eax
;-------------- Счетчик мин ----------------
        push    eax
        push    ebx
        xor     eax,eax
        mov     al,byte ptr [showmin]
        mov     bl,23
        mul     bl
        mov     ebx,253
        sub     bx,ax
        mov     [digit],ebx
        pop     ebx
        pop     eax

        push    SRCCOPY 
        push    [digit]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 23      ;height
        push    L 13      ;width
        push    L 16      ;src y
        push    L 17      ;src x
        push    [theDC]
        call    BitBlt

        push    eax
        push    ebx
        xor     eax,eax
        mov     al,byte ptr [showmin+1]
        mov     bl,23
        mul     bl
        mov     ebx,253
        sub     bx,ax
        mov     [digit],ebx
        pop     ebx
        pop     eax

        push    SRCCOPY 
        push    [digit]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 23      ;height
        push    L 13      ;width
        push    L 16      ;src y
        push    L 30      ;src x
        push    [theDC]
        call    BitBlt

        push    eax
        push    ebx
        xor     eax,eax
        mov     al,byte ptr [showmin+2]
        mov     bl,23
        mul     bl
        mov     ebx,253
        sub     bx,ax
        mov     [digit],ebx
        pop     ebx
        pop     eax

        push    SRCCOPY 
        push    [digit]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 23      ;height
        push    L 13      ;width
        push    L 16      ;src y
        push    L 43      ;src x
        push    [theDC]
        call    BitBlt
;------------- Таймер ------------------
        push    eax
        push    ebx
        xor     eax,eax
        mov     al,byte ptr [timer]
        mov     bl,23
        mul     bl
        mov     ebx,253
        sub     bx,ax
        mov     [digit],ebx
        pop     ebx
        pop     eax

        push    SRCCOPY 
        push    [digit]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 23      ;height
        push    L 13      ;width
        push    L 16      ;src y
        push    L 433     ;src x
        push    [theDC]
        call    BitBlt

        push    eax
        push    ebx
        xor     eax,eax
        mov     al,byte ptr [timer+1]
        mov     bl,23
        mul     bl
        mov     ebx,253
        sub     bx,ax
        mov     [digit],ebx
        pop     ebx
        pop     eax

        push    SRCCOPY 
        push    [digit]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 23      ;height
        push    L 13      ;width
        push    L 16      ;src y
        push    L 446     ;src x
        push    [theDC]
        call    BitBlt

        push    eax
        push    ebx
        xor     eax,eax
        mov     al,byte ptr [timer+2]
        mov     bl,23
        mul     bl
        mov     ebx,253
        sub     bx,ax
        mov     [digit],ebx
        pop     ebx
        pop     eax

        push    SRCCOPY 
        push    [digit]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 23      ;height
        push    L 13      ;width
        push    L 16      ;src y
        push    L 459     ;src x
        push    [theDC]
        call    BitBlt

        push    eax
        push    ebx
        xor     eax,eax
        mov     al,byte ptr [timer+3]
        mov     bl,23
        mul     bl
        mov     ebx,253
        sub     bx,ax
        mov     [digit],ebx
        pop     ebx
        pop     eax

        push    SRCCOPY 
        push    [digit]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 23      ;height
        push    L 13      ;width
        push    L 16      ;src y
        push    L 472     ;src x
        push    [theDC]
        call    BitBlt
;---------------- Уровень ----------------
        push    eax
        push    ebx
        xor     eax,eax
        mov     al,byte ptr [level]
        mov     bl,23
        mul     bl
        mov     ebx,253
        sub     bx,ax
        mov     [digit],ebx
        pop     ebx
        pop     eax

        push    SRCCOPY 
        push    [digit]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 23      ;height
        push    L 13      ;width
        push    L 16      ;src y
        push    L 77     ;src x
        push    [theDC]
        call    BitBlt
;---------------- Рожица -----------------
        push    [idsmail]
        push    [memDC]
        call    SelectObject

        push    SRCCOPY 
        push    [smail]   ;bmp y 96
        push    L 0       ;bmp x
        push    [memDC]
        push    L 24      ;height
        push    L 24      ;width
        push    L 16      ;src y
        push    L 240     ;src x
        push    [theDC]
        call    BitBlt

;------------------ Картинка ---------------------
;        push    [idfon]
;        push    [memDC]
;        call    SelectObject

;        push    SRCCOPY 
;        push    L 0       ;bmp y
;        push    L 0       ;bmp x
;        push    [memDC]
;        push    L 256     ;height
;        push    L 480     ;width
;        push    L 55      ;src y
;        push    L 12      ;src x
;        push    [theDC]
;        call    BitBlt

;----------------- Плиты ----------------

mov edx,55
mov ecx,16
cycl2:
 mov  byte ptr [j],cl
 push ecx
 mov eax,12
 mov ecx,30
  cycl1:
  mov byte ptr [i],cl
  push ecx
  push edx
  push eax

         push    eax        
         push    ebp
         push    ebx
         mov     eax,16
         sub     al,byte ptr [j]
         mul     byte ptr [opmul]
         mov     bp,ax
         mov     eax,30
         sub     al,byte ptr [i]
         xor     ah,ah
         add     ax,bp
          xor     ebp,ebp
          mov     bp,ax
          mov     bl,byte ptr [masscr][ebp] ;masscr
          mov     al,15
          sub     al,bl
          mov     bl,16
          mul     bl
          xor     ebx,ebx
          mov     bx,ax
          mov     [kubik],ebx
          mov     [typekub],SRCCOPY
          cmp     ebx,240
          jne     yesfon

	push	edx
        push    [idfon]
        push    [memDC]
        call    SelectObject
	pop	edx

	pop	ebx
	pop	ebp
	pop	eax
	push	eax
	push	ebp
	push	ebx

        push    SRCCOPY 
	sub	edx,55
        push    edx       ;bmp y
	add	edx,55
	sub	eax,12
        push    eax       ;bmp x
	add	eax,12
        push    [memDC]
        push    L 16     ;height
        push    L 16     ;width
        push    edx      ;src y
        push    eax      ;src x
        push    [theDC]
        call    BitBlt
          mov     [typekub],SRCAND
yesfon:
	push	edx
        push    [idkub]
        push    [memDC]
        call    SelectObject
	pop	edx

         pop     ebx
         pop     ebp     
         pop     eax
         
        push    [typekub]  
        push    [kubik]   ;bmp y
        push    L 0       ;bmp x
        push    [memDC]
        push    L 16      ;height
        push    L 16      ;width
        push    edx      ;src y 55
        push    eax      ;src x 12
        push    [theDC]
        call    BitBlt

  pop eax
  pop edx
  pop ecx
  add eax,16
 loop cycl1
 pop ecx
 add edx,16
loop cycl2 
      
        push    [oldbmp]
        push    [memDC]
        call    SelectObject

        push    [memDC]
        call    DeleteDC

        ret
paintdigit endp

;#############################################
;Заполняем массив минами
;#############################################
rand proc
        push eax
        push edx
        push ebp
        push ecx      

        xor ecx,ecx
        mov cl, byte ptr [kolmin]
        call GetTickCount
        mov byte ptr [rand1],al
        dec al
        dec al
        mov byte ptr [rand2],al
        mov ebp,0   
cyclrand:          
        shl [rand1],1
        jnc mrand
        mov al,[rand1]
        xor al,[rand2]
        mov [rand1],al
mrand:
        xor edx,edx
        mov dl,byte ptr [rand1]
        add ebp,edx
crand:
        cmp ebp,479
        ja daleko
        cmp byte ptr [masmain][ebp],10
        je  oopsrand
        mov byte ptr [masmain][ebp],10
       loop cyclrand

        pop ecx
        pop ebp
        pop edx
        pop eax
        ret
oopsrand:
        inc ebp

        inc byte ptr [rand1]
        ;inc byte ptr [rand2]

        jmp crand
daleko:
        sub ebp,480

        inc byte ptr [rand1]
        ;inc byte ptr [rand2]

        jmp crand
rand endp

;#############################################
;Считаем мины
;#############################################
countmin proc
        push eax
        push ebx
        push edx
        push ecx
        push ebp

        mov eax,0
nextmina:
        mov bl,0
        push eax
        mov dl,30
        div dl
        mov dl,al ;y
        mov dh,ah ;x
        pop eax
        mov ebp,eax
        cmp byte ptr [masmain][ebp],10
        jne nomina
        inc eax
        cmp eax,480
        je countall
        jmp nextmina
nomina:
        cmp dl,0
        je nomina1
        cmp dh,0
        je nomina1
        mov ebp,eax
        sub ebp,31
        cmp byte ptr [masmain][ebp],10
        jne nomina1
        inc bl
nomina1:
        cmp dl,0
        je nomina2
      ;cmp dh,0
      ;je nomina2
        mov ebp,eax
        sub ebp,30
        cmp byte ptr [masmain][ebp],10
        jne nomina2
        inc bl
nomina2:
        cmp dl,0
        je nomina3
        cmp dh,29
        je nomina3
        mov ebp,eax
        sub ebp,29
        cmp byte ptr [masmain][ebp],10
        jne nomina3
        inc bl
nomina3:
      ;cmp dl,0
      ;je nomina4
        cmp dh,0
        je nomina4
        mov ebp,eax
        dec ebp
        cmp byte ptr [masmain][ebp],10
        jne nomina4
        inc bl
nomina4:
      ;cmp dl,0
      ;je nomina5
        cmp dh,29
        je nomina5
        mov ebp,eax
        inc ebp
        cmp byte ptr [masmain][ebp],10
        jne nomina5
        inc bl
nomina5:
        cmp dl,15
        je nomina6
        cmp dh,0
        je nomina6
        mov ebp,eax
        add ebp,29
        cmp byte ptr [masmain][ebp],10
        jne nomina6
        inc bl
nomina6:
        cmp dl,15
        je nomina7
      ;cmp dh,0
      ;je nomina7
        mov ebp,eax
        add ebp,30
        cmp byte ptr [masmain][ebp],10
        jne nomina7
        inc bl
nomina7:
        cmp dl,15
        je nomina8
        cmp dh,29
        je nomina8
        mov ebp,eax
        add ebp,31
        cmp byte ptr [masmain][ebp],10
        jne nomina8
        inc bl
nomina8:
        mov ebp,eax
        mov byte ptr [masmain][ebp],bl
       inc eax
       cmp eax,480
       jne nextmina
countall:
        pop  ebp
        pop  ecx
        pop  edx
        pop  ebx
        pop  eax
        ret
countmin endp

;#############################################
;
;#############################################
verfile proc
	LOCAL fhandle:DWORD

	push L 0
	push FILE_ATTRIBUTE_ARCHIVE
	push OPEN_ALWAYS
	push L 0
	push FILE_SHARE_READ or FILE_SHARE_WRITE
	push GENERIC_READ or GENERIC_WRITE
	push offset filename
	call CreateFileA
	mov  [fhandle],eax

	push L 0
	push offset [countread]
	push L 358
	push offset [bufer_rw]
	push [fhandle]
	call ReadFile

	cmp  [countread],357
	je  fileex
	push L 0
	push offset [countread]
	push L 357
	push offset [bufer_i]
	push [fhandle]
	call WriteFile
fileex:
	push [fhandle]
	call CloseHandle

	push L 0
	push FILE_ATTRIBUTE_ARCHIVE
	push OPEN_ALWAYS
	push L 0
	push FILE_SHARE_READ or FILE_SHARE_WRITE
	push GENERIC_READ or GENERIC_WRITE
	push offset filename
	call CreateFileA
	mov  [fhandle],eax

	push L 0
	push offset [countread]
	push L 357
	push offset [bufer_rw]
	push [fhandle]
	call ReadFile

	push [fhandle]
	call CloseHandle
	ret
verfile endp