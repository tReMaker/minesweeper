toptime proc hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD
	LOCAL hinst2:DWORD, fhandle:DWORD, yy:DWORD

	cmp [wmsg],WM_PAINT
	je  paintdlg2
	cmp [wmsg],WM_INITDIALOG
	je  initdlg2
	cmp [wmsg],WM_CLOSE
	je  closedlg22
	cmp [wmsg],WM_COMMAND
	je  closedlg21
	jmp defdlg23

paintdlg2:
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
	mov	eax,offset bufer_rw+187
printtab2:
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
	loop	printtab2
	pop	eax
	pop	ecx
	
	call selfonte

        push    offset lppaint
        push    [hwnd]
        call    EndPaint
	jmp defdlg23
initdlg2:
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

	jmp defdlg23
closedlg21:
	cmp [wparam],IDOK
	jne defdlg23
closedlg22:
	push L 0
	push [hwnd]
	call EndDialog
defdlg23:    
	mov eax,0
	ret
toptime endp


