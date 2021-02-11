top10 proc hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD
	LOCAL hinst2:DWORD, fhandle:DWORD, yy:DWORD

	cmp [wmsg],WM_PAINT
	je  paintdlg
	cmp [wmsg],WM_INITDIALOG
	je  initdlg1
	cmp [wmsg],WM_CLOSE
	je  closedlg12
	cmp [wmsg],WM_COMMAND
	je  closedlg11
	jmp defdlg13
paintdlg:
        push    offset lppaint
        push    [hwnd]
        call    BeginPaint
        mov     [theDC], eax

	call selfonts
	mov	[yy],54

        push    L 0
        push    [theDC]
        call    SetTextColor

	push	ecx
	push	eax
	mov	ecx,10
	mov	eax,offset bufer_rw
printtab:
	push	ecx
	push	eax

        push    L 13               ; length of string
        push    eax                ; string
        push    [yy]               ; y
        push    L 32               ; x
        push    [theDC]            ; the DC
        call    TextOutA

	pop	eax
	add	eax,13
	push	eax

        push    L 4                ; length of string
        push    eax                ; string
        push    [yy]               ; y
        push    L 180              ; x
        push    [theDC]            ; the DC
        call    TextOutA

	pop	eax
	add	eax,4
	add	[yy],13
	pop	ecx
	loop	printtab
	pop	eax
	pop	ecx
	
	call selfonte

        push    offset lppaint
        push    [hwnd]
        call    EndPaint
	jmp defdlg13
initdlg1:
	push L 0
	push FILE_ATTRIBUTE_ARCHIVE
	push OPEN_EXISTING
	push L 0
	push FILE_SHARE_READ or FILE_SHARE_WRITE
	push GENERIC_READ or GENERIC_WRITE
	push offset filename
	call CreateFileA
	mov  [fhandle],eax

	push L 0
	push offset [countread]
	push L 340
	push offset [bufer_rw]
	push [fhandle]
	call ReadFile

	push [fhandle]
	call CloseHandle

        push    1
        push    [hwnd]
        call    GetDlgItem
        push    eax
        call    SetFocus

	jmp defdlg13
closedlg11:
	cmp [wparam],IDOK
	jne defdlg13
closedlg12:
	push L 0
	push [hwnd]
	call EndDialog
defdlg13:    
	mov eax,0
	ret

top10 endp

selfonts proc
        push    offset nmfont ;Facename - Шрифт
        push    L 12          ;PitchAndFamily
        push    L 2           ;Quality
        push    L 1           ;ClipPrecision
        push    L 1           ;OutputPrecision
        push    L 1           ;CharSet - Набор символов
        push    L 0           ;StrikeOut - Зачеркивание
        push    L 0           ;Underline - Подчеркивание
        push    L 0           ;Italic - Курсив
        push    L 0           ;Weight - Жирный и т.п.
        push    L 0           ;Orientation
        push    L 0           ;Escapement
        push    L 0           ;Width  
        push    L 8           ;Height - Размер
        call    CreateFontA
        mov     [newfont],eax

        push    [newfont]
        push    [theDC]
        call    SelectObject
        mov     [oldfont],eax

        push    L 1
        push    [theDC]
        call    SetBkMode ; прозрачность

        push    TA_LEFT
        push    [theDC]
        call    SetTextAlign ; выравнивание по центру

        ret
selfonts endp
;--------------------------
selfonte proc
        push    [oldfont]
        push    [theDC]
        call    SelectObject
        
        push    [newfont]
        call    DeleteObject

        ret
selfonte endp
;--------------------------

