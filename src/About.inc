about proc hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD
	LOCAL hinst2:DWORD

        cmp [wmsg],WM_INITDIALOG
        je  _setfocus2
	cmp [wmsg],WM_CLOSE
	je  closedlg
	cmp [wmsg],WM_COMMAND
	je  closedlg1
	jmp defdlg
_setfocus2:
        push    1
        push    [hwnd]
        call    GetDlgItem
        push    eax
        call    SetFocus
        xor     eax,eax
        ret

closedlg1:
	cmp [wparam],1003
	jne __1_1
        push    L 0
        push    L 0
        push    L 0
        push    offset url
        push    offset metod
        push    [hwnd]
        call    ShellExecuteA	
__1_1:
	cmp [wparam],IDOK
	jne defdlg
closedlg:
	push L 0
	push [hwnd]
	call EndDialog
defdlg:    
	mov eax,0
	ret
about endp


