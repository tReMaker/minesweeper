inputname2 proc hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD
	LOCAL hinst2:DWORD, fhandle:DWORD, yy:DWORD

	cmp [wmsg],WM_INITDIALOG
	je  initdlg52
	cmp [wmsg],WM_PAINT
	je  paintdlg52
	cmp [wmsg],WM_CLOSE
	je  closedlg52
	cmp [wmsg],WM_COMMAND
	je  closedlg51
	jmp defdlg53

initdlg52:
	push ebx
	push eax
	mov bl,17
	mov eax,[mesto]
	div bl
	inc al
	cmp al,10
	jne noten
	mov [dmesto+1],30h
	mov al,1
noten:
	add al,30h
	mov [dmesto],al
	pop eax
	pop ebx
	jmp defdlg53
paintdlg52:
        push    offset lppaint
        push    [hwnd]
        call    BeginPaint
        mov     [theDC], eax

	call selfonts

        push    L 0
        push    [theDC]
        call    SetTextColor

        push    L 2                ; length of string
        push    offset dmesto      ; string
        push    L 28               ; y
        push    L 78               ; x
        push    [theDC]            ; the DC
        call    TextOutA

	
	call selfonte

        push    offset lppaint
        push    [hwnd]
        call    EndPaint

        push    1001
        push    [hwnd]
        call    GetDlgItem
        push    eax
        call    SetFocus

	jmp defdlg53

closedlg51:
	cmp [wparam],IDOK
	jne defdlg53

	push ecx
	push ebp
	mov ecx,13
	mov ebp,0
resetuser2:
	mov [username][ebp],20h
	inc ebp
	loop resetuser2
	pop ebp
	pop ecx

	push	L 13
	push	offset username
	push	L 1001
	push	[hwnd]
	call	GetDlgItemTextA


	push eax
	push ebx
	push ebp
	mov ebp,[mesto]
	push ecx
	mov ecx,17
	xor ebx,ebx
copystr2:
	push ebp
	mov ebp,ebx
	mov al,byte ptr [username][ebp]
	pop ebp
	cmp ecx,4
	ja nextcopy2
	add al,30h
nextcopy21:
	cmp al,0
	jne nextcopy
	mov al,20h
nextcopy22:
	mov byte ptr [bufer_rw][ebp],al
	inc ebx
	inc ebp
	loop copystr2
	pop ecx
	pop ebp
	pop ebx

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
	call WriteFile

	push [fhandle]
	call CloseHandle

	pop eax
closedlg52:
	push L 0
	push [hwnd]
	call EndDialog
defdlg53:    
	mov eax,0
	ret

inputname2 endp