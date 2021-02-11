inputname proc hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD
	LOCAL hinst2:DWORD, fhandle:DWORD, yy:DWORD

	cmp [wmsg],WM_INITDIALOG
	je  _setfocus
	cmp [wmsg],WM_CLOSE
	je  closedlg42
	cmp [wmsg],WM_COMMAND
	je  closedlg41
	jmp defdlg43
_setfocus:
        push	1001
	push	[hwnd]
	call    GetDlgItem
	push	eax
	call	SetFocus
	xor	eax,eax
	ret
closedlg41:
	cmp [wparam],IDOK
	jne defdlg43
	push ecx
	push ebp
	mov ecx,13
	mov ebp,0
resetuser:
	mov [username][ebp],20h
	inc ebp
	loop resetuser
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
	mov al,byte ptr [level]
	mov bl,17
	mul bl
	add ax,187
	xor ebp,ebp
	mov bp,ax
	push ecx
	mov ecx,17
	xor ebx,ebx
copystr:
	push ebp
	mov ebp,ebx
	mov al,byte ptr [username][ebp]
	pop ebp
	cmp ecx,4
	ja nextcopy2
	add al,30h
nextcopy2:
	cmp al,0
	jne nextcopy
	mov al,20h
nextcopy:
	mov byte ptr [bufer_rw][ebp],al
	inc ebx
	inc ebp
	loop copystr
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
closedlg42:
	push L 0
	push [hwnd]
	call EndDialog
defdlg43:    
	mov eax,0
	ret

inputname endp