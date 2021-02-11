.486
locals
jumps
.model flat,STDCALL
include def.inc           ; some 32-bit constants and structures

.data?
msg              MSGSTRUCT   <?>
wc               WNDCLASS    <?>
lppaint          PAINTSTRUCT <?>
curpos           POINT       <?>
pos              POINT       <?>
rr               RECT        <?>

idpen            dd ?
idpenold         dd ?
iddigit          dd ?
idsmail          dd ?
idfon            dd ?
idkub            dd ?
oldbmp           dd ?
oldbmp2          dd ?

theDC            dd ?
myDC             dd ?
memDC            dd ?
memDC2           dd ?

polex		 dw ?
poley		 dw ?
bakpolex	 dw ?
bakpoley	 dw ?

masxi		 db ?
masyi		 db ?

x		 dw ?
y		 dw ?


.data
; --- Структуры ---
szTitleName      db 'Сапер',0
szClassName      db 'MyWin',0
szAbout          db 'About', 0
sztop10		 db 'top10',0
sztoptime        db 'toptime',0
szinputname      db 'inputname',0
szinputname2      db 'inputname2',0
menu_name db 'IDM_MENU',0 
IDM_START = 101 
 IDM_BEST     = 201
 IDM_BESTTIME = 202 
IDM_EXIT  = 103
IDM_HELP  = 111
IDM_ABOUT = 112
IDM_PAUSE = 121

hInst            dd 0 ;ID - приложения
newhwnd          dd 0 ;ID - окна

smail            dd 96
kubik            dd 0
typekub          dd 0
flmouse          db 0
flmouses         db 0

i                db 0
j                db 0
opmul            db 30
rand1            db 45h
rand2            db 33h
kolmin           db 9
showmin	 	 db 0,0,9,0
flagmp		 db 0
masmain          db 480 dup (0)
masscr           db 480 dup (15)
lbmd		 db 0
lbmd2 		 db 0

messtbox         db 'INDEX',0
messbox          db '  :         ',0

idtimer          dd 0
digit            dd 0
timer            db 0,0,0,0
baktimer	 db 0,0,0,0
timerstart	 db 0
username	 db 13 dup (20h)
timerec		 db 0,0,0,0,0
timerec2         db 0,0,0,0
flagzaem	 db 0
flaginit	 db 0
pause		 db 0

mesto		 dd 0
dmesto	         db 20h,20h
level		 db 0
fon		 dd 4001

nmfont           db 'MS Sans Serif',0
newfont	         dd 0
oldfont		 dd 0
countread	 dd 0
bufer_rw         db 374 dup (0)
bufer_i		 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
		 db '                 '
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'
                 db 'Неизвестен   9999'

flagpobed	 db 0
tpobeda		 db 'Поздравляем !!!',0
mpobeda		 db 'Вы нашли все мины и переходите на следующий уровень.',0
tboom		 db 'Ба-Бах.',0
mboom		 db 'Родина вас незабудет !!!',0
tall		 db 'Поздравляем !!!',0
mall		 db 'Вы прошли все уровни.',0

url              db 'http://rm-soft.h10.ru',0
metod            db 'open',0

filename	 db MAX_PATH DUP(?)
filename2        db 'miner.cfg',0

;debug1           db 0,0,0,0,'!',0
;debug2           db '*','*','*','*','!',0
.code
;-----------------------------------------------------------------------------
;
;                  Начальная загрузка приложения
;
;-----------------------------------------------------------------------------
start:
        call    rand
        call    countmin
	;call    initgame

        push    L 0
        call    GetModuleHandleA        ; получаем ID приложения
        mov     [hInst], eax            ; 

	push	MAX_PATH
	push	offset filename
	push	0
	call	GetModuleFileNameA
	mov	eax,offset filename2
bslash:
	cmp	byte ptr [eax],'\'
	je	backslash
	dec	eax
	jmp	bslash
backslash:
	inc	eax
	mov	ecx,10
	mov	edx,offset filename2
	push	ebx
copyfile:
	mov	bl,byte ptr [edx]
	mov	byte ptr [eax],bl
	inc	edx
	inc	eax
	loop	copyfile
        pop	ebx

	call	verfile

        push    L 3001   
        push    [hInst]
        call    LoadBitmapA
        mov     [idkub],eax 

        push    L 3002   
        push    [hInst]
        call    LoadBitmapA
        mov     [iddigit],eax 

        push    L 3003   
        push    [hInst]
        call    LoadBitmapA
        mov     [idsmail],eax 

        ;push    L 4001   
        ;push    [hInst]
        ;call    LoadBitmapA
        ;mov     [idfon],eax 
	push	L 4001
	push	[hInst]
	call	BitmapFromResource
	mov	[idfon],eax 

;
; Инициализация класса окна
;
        mov     [wc.clsStyle], CS_HREDRAW + CS_VREDRAW + CS_GLOBALCLASS ; Стиль окна
        mov     [wc.clsLpfnWndProc], offset WndProc ; Имя оконной процедуры
        mov     [wc.clsCbClsExtra], 0 ; Число байт доп. инфы о классе
        mov     [wc.clsCbWndExtra], 0 ; Число байт доп. инфы об окне
        mov     eax, [hInst]
        mov     [wc.clsHInstance], eax ; ID приложения
; Получаем ID иконки
        push    L 2001 
        push    [hInst]
        call    LoadIconA
        mov     [wc.clsHIcon], eax ; ID иконки приложения
; Получаем ID курсора
        push    L IDC_ARROW
        push    L 0
        call    LoadCursorA
        mov     [wc.clsHCursor], eax ;ID курсора приложения
        mov     [wc.clsHbrBackground],COLOR_WINDOW ; ID кисти для фона окна
        mov     dword ptr [wc.clsLpszMenuName], 0 ; Указатель на строку с именем меню окна
        mov     dword ptr [wc.clsLpszClassName], offset szClassName ; Указатель на строку с именем класса окна

        push    offset wc
        call    RegisterClassA ; Регистрируем класс окна

        push    L 0                      ; Параметры
        push    [hInst]                  ; ID приложения

        push offset menu_name  
        push [hInst] 
        call LoadMenuA

        push    eax                      ; Меню
        push    L 0                      ; ID окна предка
        push    L 367                    ; высота
        push    L 510                    ; ширина
        push    L CW_USEDEFAULT          ; y
        push    L CW_USEDEFAULT          ; x
        push    L WS_CAPTION OR WS_SYSMENU OR WS_VISIBLE OR WS_MINIMIZEBOX; Стиль окна
        push    offset szTitleName       ; Заголовок окна
        push    offset szClassName       ; Имя класса
        push    L 1                      ; Специальный стиль окна
        call    CreateWindowExA
        mov     [newhwnd], eax           ; ID окна

        push    L SW_SHOWNORMAL
        push    [newhwnd]
        call    ShowWindow              ; Показать окно

        push    [newhwnd]
        call    UpdateWindow            ; обновляем окно

; рабочий цикл
msg_loop:
        push    L 0
        push    L 0
        push    L 0
        push    offset msg
        call    GetMessageA

        cmp     ax,0 ;QUIT
        je      end_loop

        push    offset msg
        call    TranslateMessage

        push    offset msg
        call    DispatchMessageA

        jmp     msg_loop

end_loop:
        push    [msg.msWPARAM]
        call    ExitProcess


;-----------------------------------------------------------------------------
WndProc          proc uses ebx edi esi, hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD
;
; WARNING: Win32 requires that EBX, EDI, and ESI be preserved!  We comply
; with this by listing those regs after the 'uses' statement in the 'proc'
; line.  This allows the Assembler to save them for us.
;

        cmp     [wmsg], WM_DESTROY
        je      wmdestroy
        cmp     [wmsg], WM_SIZE
        je      wmsize
        cmp     [wmsg], WM_CREATE
        je      wmcreate
        cmp     [wmsg], WM_PAINT
        je      wmpaint
        cmp     [wmsg],WM_RBUTTONDOWN
        je      wmrbutdown
        cmp     [wmsg],WM_LBUTTONDOWN
        je      wmlbutdown
        cmp     [wmsg],WM_LBUTTONUP
        je      wmlbutup
        cmp     [wmsg],WM_MOUSEMOVE
        je      wmmousemov
        cmp     [wmsg],WM_TIMER
        je      wmtimer
	cmp	[wmsg],WM_COMMAND
	je	wmmenu
	cmp	[wmsg],WM_ACTIVATE
	je	wmactiv
        jmp     defwndproc

;******************************
wmpaint:
        push    offset lppaint
        push    [hwnd]
        call    BeginPaint
        mov     [theDC], eax

         call   paintpole
         call   paintdigit

        push    offset lppaint
        push    [hwnd]
        call    EndPaint

        mov     eax, 0
        jmp     finish
;******************************
wmcreate:
        mov byte ptr [timer],0
        mov byte ptr [timer+1],0
        mov byte ptr [timer+2],0         

        mov     eax, 0
        jmp     finish

;******************************
defwndproc:
        push    [lparam]
        push    [wparam]
        push    [wmsg]
        push    [hwnd]
        call    DefWindowProcA
        jmp     finish

;******************************
wmdestroy:

        push [idtimer]
        push [hwnd]
        call KillTimer

        push    [idkub]
        call    DeleteObject

        push    [iddigit]
        call    DeleteObject

        push    [idsmail]
        call    DeleteObject

        push    [idfon]
        call    DeleteObject

        push    L 0
        call    PostQuitMessage
        mov     eax, 0
        jmp     finish

;******************************
wmsize:
        mov     eax, 0
        jmp     finish

;******************************
wmlbutdown:

        mov     [flmouse],1
        mov     [flmouses],2
        mov     [smail],72

        mov     [rr.rcLeft],240
        mov     [rr.rcTop],16
        mov     [rr.rcRight],264
        mov     [rr.rcBottom],40

        mov     ax,word ptr [lparam+2]
        mov     [pos.ptY],ax
	mov	[y],ax
        mov     ax,word ptr [lparam]
        mov     [pos.ptX],ax
	mov	[x],ax
        
        cmp     word ptr [pos.ptX],241
        jb      mimo
        cmp     word ptr [pos.ptX],263
        ja      mimo
        cmp     word ptr [pos.ptY],17
        jb      mimo
        cmp     word ptr [pos.ptY],39
        ja      mimo

        mov     [flmouses],1        
        mov     [smail],0
	call	initgame
mimo:
        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect
cmp byte ptr [flagpobed],0
jne lookpobed
        call    clickpole       
lookpobed:
        mov     eax, 0
        jmp     finish

;******************************
wmlbutup:

        mov    [flmouse],0
        mov    [smail],96

        mov     [rr.rcLeft],240
        mov     [rr.rcTop],16
        mov     [rr.rcRight],264
        mov     [rr.rcBottom],40

        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect    ; repaint window

	cmp	[lbmd],1
        jne	nolbmd2
        mov     ax,word ptr [lparam+2]
	mov	[y],ax
        mov     ax,word ptr [lparam]
	mov	[x],ax

cmp byte ptr [flagpobed],0
jne lookpobed2
	call	restorekub
	call	showmina
	call	cmppobeda
lookpobed2:
	mov	[lbmd],0
	mov	[lbmd2],0
nolbmd2:
	cmp	[timerstart],0
	jne	timergo
	cmp	[flaginit],0
	jne	timergo
        push    L 0
        push    L 1000
        push    L 10
        push    [hwnd]
        call    SetTimer
        mov     [idtimer],eax
	mov	[timerstart],1
timergo:

        mov     eax, 0
        jmp     finish

;******************************
wmmousemov:
        cmp     [flmouse],1
        jne     nold
        mov     [smail],72
        cmp     [flmouses],1
        jne     nono
        mov     [smail],96
nono:
        mov     [rr.rcLeft],240
        mov     [rr.rcTop],16
        mov     [rr.rcRight],264
        mov     [rr.rcBottom],40

        mov     ax,word ptr [lparam+2]
        mov     [pos.ptY],ax
        mov     ax,word ptr [lparam]
        mov     [pos.ptX],ax
        
        cmp     [flmouses],1
        jne     mimo2

        cmp     word ptr [pos.ptX],241
        jb      mimo2
        cmp     word ptr [pos.ptX],263
        ja      mimo2
        cmp     word ptr [pos.ptY],17
        jb      mimo2
        cmp     word ptr [pos.ptY],39
        ja      mimo2
        
        mov     [smail],0
mimo2:
        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect    ; repaint window
nold:
cmp byte ptr [flagpobed],0
jne lookpobed3
	cmp	[lbmd],1
        jne	nolbmd
        mov     ax,word ptr [lparam+2]
	mov	[y],ax
        mov     ax,word ptr [lparam]
	mov	[x],ax
	cmp	[lbmd2],1
        jne	nolbmd3
	call	restorekub
nolbmd3:
	call	clickpole
nolbmd:
lookpobed3:
        mov     eax, 0
        jmp     finish

;******************************
wmrbutdown:
cmp byte ptr [flagpobed],0
jne lookpobed4
        mov     ax,word ptr [lparam]    ;x
        mov     dx,word ptr [lparam+2]  ;y
        
        cmp     ax,12
        jb      nopole
        cmp     ax,491
        ja      nopole
        cmp     dx,55
        jb      nopole
        cmp     dx,310
        ja      nopole
	
	push	[lparam+2]
	push	[lparam]
	push	[hwnd]
	call	setflag
	call	cmppobeda
nopole:     
lookpobed4: 
        mov     eax, 0
        jmp     finish

;******************************
wmtimer:
        inc byte ptr [timer+3]
        cmp byte ptr [timer+3],10
        jne notime
        mov byte ptr [timer+3],0
        inc byte ptr [timer+2]
        cmp byte ptr [timer+2],10
        jne notime
        mov byte ptr [timer+2],0
        inc byte ptr [timer+1]
        cmp byte ptr [timer+1],10
        jne notime
        mov byte ptr [timer+1],0
        inc byte ptr [timer]
        cmp byte ptr [timer],10
	jne notime
        dec byte ptr [timer]
	mov byte ptr [timer+1],9
        mov byte ptr [timer+2],9
        mov byte ptr [timer+3],9
        push [idtimer]
        push [hwnd]
        call KillTimer
notime:
        mov     [rr.rcLeft],433
        mov     [rr.rcTop],16
        mov     [rr.rcRight],484
        mov     [rr.rcBottom],38
        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect 
        mov     eax, 0
        jmp     finish

;*****************************
wmmenu:
	cmp	[wparam],IDM_EXIT
	jne	nosel1
	push	L 0
	push	L 0
	push	WM_CLOSE
	push	[hwnd]
	call	SendMessageA
	jmp	noselect
nosel1:
	cmp	[wparam],IDM_START
	jne	nosel2
	call	initgame
	jmp	noselect
nosel2:
	cmp	[wparam],IDM_PAUSE
	jne	nosel3
        push    L SW_MINIMIZE
        push    [hwnd]
        call    ShowWindow
	cmp	[timerstart],1
	jne	noselect
        push [idtimer]
        push [hwnd]
        call KillTimer
	mov  [pause],0
	jmp	noselect
nosel3:
	cmp	[wparam],IDM_ABOUT
	jne	nosel4
	push	L 0
	push	offset about
	push	[hwnd]
	push	offset szAbout
	push	[hInst]
	call	DialogBoxParamA
	jmp	noselect
nosel4:
	cmp	[wparam],IDM_BEST
	jne	nosel5
	push	L 0
	push	offset top10
	push	[hwnd]
	push	offset sztop10
	push	[hInst]
	call	DialogBoxParamA
	jmp	noselect	
nosel5:
	cmp	[wparam],IDM_BESTTIME
	jne	nosel6
	push	L 0
	push	offset toptime
	push	[hwnd]
	push	offset sztoptime
	push	[hInst]
	call	DialogBoxParamA
	jmp	noselect
nosel6:
noselect:
        mov     eax, 0
        jmp     finish

;*****************************
wmactiv:
	cmp	[wparam],WA_ACTIVE
	jne	noactiv
	cmp	[pause],0
	jne	noactiv
	cmp	[timerstart],0
	je	noactiv
        push    L 0
        push    L 1000
        push    L 10
        push    [hwnd]
        call    SetTimer
	mov	[pause],1
        mov     [idtimer],eax
noactiv:
        mov     eax, 0
        jmp     finish
;-----------------------------
finish:
        ret
WndProc          endp

include proc.inc
include poleproc.inc
include about.inc
include top10.inc
include toptime.inc
include inputn.inc
include inputn2.inc
include \tasm\include\image\image.inc

public WndProc
ends
end start