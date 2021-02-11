L          equ <LARGE>
FALSE	   equ 0
TRUE	   equ 1

MAX_PATH   equ 260

UCHAR      EQU <db>
USHORT     EQU <dw>  ; used only if we really need 16 bits
UINT       EQU <dd>  ; 32 bits for WIN32
ULONG      EQU <dd>

RECT    struc
        rcLeft          UINT ?
        rcTop           UINT ?
        rcRight         UINT ?
        rcBottom        UINT ?
RECT    ends

POINT   struc
        ptX             dw      ?
        ptY             dw      ?
POINT   ends

WNDCLASS struc
        clsStyle          UINT     ?   ; class style
        clsLpfnWndProc    ULONG    ?
        clsCbClsExtra     UINT     ?
        clsCbWndExtra     UINT     ?
        clsHInstance      UINT     ?   ; instance handle
        clsHIcon          UINT     ?   ; class icon handle
        clsHCursor        UINT     ?   ; class cursor handle
        clsHbrBackground  UINT     ?   ; class background brush
        clsLpszMenuName   ULONG    ?   ; menu name
        clsLpszClassName  ULONG    ?   ; far ptr to class name
WNDCLASS ends

MSGSTRUCT struc
    msHWND          UINT    ?
    msMESSAGE       UINT    ?
    msWPARAM        UINT    ?
    msLPARAM        ULONG   ?
    msTIME          ULONG   ?
    msPT            ULONG   ?
MSGSTRUCT ends

PAINTSTRUCT STRUC
    PShdc         UINT             ?
    PSfErase      UINT             ?
    PSrcPaint     UCHAR            size RECT dup(?)
    PSfRestore    UINT             ?
    PSfIncUpdate  UINT             ?
    PSrgbReserved UCHAR            16 dup(?)
PAINTSTRUCT ENDS
;-------------------------------------
; ќбъ€вление внешних функций программы
;-------------------------------------
extrn            CreateWindowExA:PROC
extrn            DefWindowProcA:PROC
extrn            DispatchMessageA:PROC
extrn            ExitProcess:PROC
extrn            GetModuleHandleA:PROC
extrn            LoadIconA:PROC
extrn            LoadCursorA:PROC
extrn            LoadMenuA:PROC
extrn            PostQuitMessage:PROC
extrn            RegisterClassA:PROC
extrn            ShowWindow:PROC
extrn            TranslateMessage:PROC
extrn            UpdateWindow:PROC
extrn            GetMessageA:PROC
extrn            SetPixel:PROC
extrn            BeginPaint:PROC
extrn            EndPaint:PROC
extrn            Rectangle:PROC
extrn            CreatePen:PROC
extrn            SelectObject:PROC
extrn            DeleteObject:PROC
extrn            LineTo:PROC
extrn            MoveToEx:PROC
extrn            LoadBitmapA:PROC
extrn            CreateCompatibleDC:PROC
extrn            BitBlt:PROC
extrn            DeleteDC:PROC
extrn            InvalidateRect:PROC
extrn            MessageBoxA:PROC
extrn            GetTickCount:PROC
extrn            SetTimer:PROC
extrn            KillTimer:PROC
extrn		 GetDC:PROC
extrn		 ReleaseDC:PROC
extrn		 SendMessageA:PROC
extrn		 DialogBoxParamA:PROC
extrn		 EndDialog:PROC
extrn	 	 CreateFileA:PROC
extrn		 ReadFile:PROC
extrn		 WriteFile:PROC
extrn		 CloseHandle:PROC
extrn		 SetTextColor:PROC
extrn		 TextOutA:PROC
extrn		 CreateFontA:PROC
extrn		 SetBkMode:PROC
extrn		 SetTextAlign:PROC
extrn	         GetDlgItemTextA:PROC
extrn		 SetFocus:PROC
extrn		 GetDlgItem:PROC
extrn		 ShellExecuteA:PROC
extrn		 GetModuleFileNameA:PROC

;-------------------------------------
CS_VREDRAW         = 0001h
CS_HREDRAW         = 0002h
CS_GLOBALCLASS     = 4000h

IDC_ARROW          = 32512

IDOK     	   =   1

COLOR_WINDOW       = 5

CW_USEDEFAULT   EQU    8000h

WS_CAPTION         = 000C00000h
WS_SYSMENU         = 000080000h
WS_VISIBLE         = 010000000h
WS_MINIMIZEBOX     = 000020000h

SW_SHOWNORMAL      = 1
SW_MINIMIZE        = 6

WM_SIZE            = 0005h
WM_CREATE          = 0001h
WM_DESTROY         = 0002h
WM_PAINT           = 000Fh
WM_MOUSEMOVE       = 0200h
WM_LBUTTONDOWN     = 0201h
WM_LBUTTONUP       = 0202h
WM_RBUTTONDOWN     = 0204h
WM_TIMER           = 0113h
WM_COMMAND         = 0111h
WM_CLOSE           = 0010h
WM_ACTIVATE        = 0006h
WM_SHOWWINDOW      = 0018h
WM_INITDIALOG      = 0110h

WA_INACTIVE        = 0
WA_ACTIVE          = 1


BLACKNESS          = 00000042h
DSTINVERT          = 00550009h
MERGECOPY          = 00c000cah
MERGEPAINT         = 00bb0226h ;+
NOTSRCCOPY         = 00330008h
NOTSRCERASE        = 001100a6h
PATCOPY            = 00f00021h
PATINVERT          = 005a0049h
PATPAINT           = 00fb0a09h
SRCAND             = 008800c6h;
SRCCOPY            = 00cc0020h
SRCERASE           = 00440328h
SRCINVERT          = 00660046h
SRCPAINT           = 00ee0086h
WHITENESS          = 00ff0062h

MB_OK              = 0000h
MB_ICONASTERISK    = 0040h

FILE_ATTRIBUTE_ARCHIVE = 20h
FILE_SHARE_READ        = 00000001h  
FILE_SHARE_WRITE       = 00000002h  

GENERIC_READ           = 80000000h
GENERIC_WRITE          = 40000000h

OPEN_EXISTING          = 3
OPEN_ALWAYS            = 4

TA_NOUPDATECP                        equ 0
TA_UPDATECP                          equ 1
TA_LEFT                              equ 0
TA_RIGHT                             equ 2
TA_CENTER                            equ 6
TA_TOP                               equ 0
TA_BOTTOM                            equ 8
TA_BASELINE                          equ 24
TA_MASK                              equ TA_BASELINE + TA_CENTER + TA_UPDATECP
