;#############################################
;
;#############################################
clickpole proc
	push	eax
	push	edx

	mov	[lbmd],1

	mov	ax,word ptr [x]  ;x
	mov	dx,word ptr [y]  ;y
        
	cmp	ax,12
	jb	clinopole
	cmp	ax,491
	ja	clinopole
	cmp	dx,55
	jb	clinopole
	cmp	dx,310
	ja	clinopole

	mov	ax,word ptr [x] ;X
	sub	ax,12
	mov	dl,16
	div	dl	;al - index x
	mov	[masxi],al
        mov     ah,16
	mul	ah
	add	ax,12
	mov	[polex],ax

	mov	ax,word ptr [y] ;y
	sub	ax,55
	mov	dl,16
	div	dl	;al - index y
	mov	[masyi],al
	mov	ah,16
	mul	ah
	add	ax,55
	mov	[poley],ax

	push	ebp
	mov	bl,30
	xor	eax,eax
	mov	al,[masyi]
	mul	bl
	xor	bx,bx
	mov	bl,[masxi]
	add	ax,bx
	mov	ebp,eax
	mov	al,byte ptr [masscr][ebp]
	pop	ebp
	cmp	al,15
	jne	clinopole

	mov	[lbmd2],1

	push	[hwnd]
	call	GetDC
	mov	[myDC],eax

        push    [myDC]
        call    CreateCompatibleDC
        mov     [memDC2],eax

        push    [idkub]
        push    [memDC2]
        call    SelectObject
        mov     [oldbmp2],eax

        push    SRCCOPY  
        push    L 96      ;bmp y
        push    L 0       ;bmp x
        push    [memDC2]
        push    L 16      ;height
        push    L 16      ;width
	xor	eax,eax
	mov	ax,[poley]
	mov	[bakpoley],ax
        push    eax       ;src y 55
	mov	ax,[polex]
	mov	[bakpolex],ax
        push    eax       ;src x 12
        push    [myDC]
        call    BitBlt

        push    [oldbmp2]
        push    [memDC2]
        call    SelectObject

        push    [memDC2]
        call    DeleteDC

	push	[myDC]
	push	[hwnd]
	call	ReleaseDC

clinopole:
	pop	edx
	pop	eax
	ret
clickpole endp

;#############################################
;
;#############################################
restorekub proc
	push	eax
	push	edx

	mov	ax,word ptr [x]  ;x
	mov	dx,word ptr [y]  ;y
        
	cmp	ax,12
	jb	norest
	cmp	ax,491
	ja	norest
	cmp	dx,55
	jb	norest
	cmp	dx,310
	ja	norest

	mov	ax,word ptr [x] ;X
	sub	ax,12
	mov	dl,16
	div	dl	;al - index x
	mov	[masxi],al
        mov     ah,16
	mul	ah
	add	ax,12
	mov	[polex],ax

	mov	ax,word ptr [y] ;y
	sub	ax,55
	mov	dl,16
	div	dl	;al - index y
	mov	[masyi],al
	mov	ah,16
	mul	ah
	add	ax,55
	mov	[poley],ax

	push	ebp
	mov	bl,30
	xor	eax,eax
	mov	al,[masyi]
	mul	bl
	xor	bx,bx
	mov	bl,[masxi]
	add	ax,bx
	mov	ebp,eax
	mov	al,byte ptr [masscr][ebp]
	pop	ebp
	;cmp	al,15
	;jne	norest

	push	[hwnd]
	call	GetDC
	mov	[myDC],eax

        push    [myDC]
        call    CreateCompatibleDC
        mov     [memDC2],eax

        push    [idkub]
        push    [memDC2]
        call    SelectObject
        mov     [oldbmp2],eax

        push    SRCCOPY  
        push    L 0       ;bmp y
        push    L 0       ;bmp x
        push    [memDC2]
        push    L 16      ;height
        push    L 16      ;width
	xor	eax,eax
	mov	ax,[bakpoley]
        push    eax       ;src y 55
	mov	ax,[bakpolex]
        push    eax       ;src x 12
        push    [myDC]
        call    BitBlt

        push    [oldbmp2]
        push    [memDC2]
        call    SelectObject

        push    [memDC2]
        call    DeleteDC

	push	[myDC]
	push	[hwnd]
	call	ReleaseDC
norest:
	pop	edx
	pop	eax	
	ret
restorekub endp

;#############################################
;
;#############################################
showmina proc
	push	eax
	push	edx

	mov	ax,word ptr [x]  ;x
	mov	dx,word ptr [y]  ;y
        
	cmp	ax,12
	jb	shownopole
	cmp	ax,491
	ja	shownopole
	cmp	dx,55
	jb	shownopole
	cmp	dx,310
	ja	shownopole

	mov	[flaginit],0

	mov	ax,word ptr [x] ;X
	sub	ax,12
	mov	dl,16
	div	dl	;al - index x
	mov	[masxi],al
        mov     ah,16
	mul	ah
	add	ax,12
	mov	[polex],ax

	mov	ax,word ptr [y] ;y
	sub	ax,55
	mov	dl,16
	div	dl	;al - index y
	mov	[masyi],al
	mov	ah,16
	mul	ah
	add	ax,55
	mov	[poley],ax

	push	ebp
	mov	bl,30
	xor	eax,eax
	mov	al,[masyi]
	mul	bl
	xor	bx,bx
	mov	bl,[masxi]
	add	ax,bx
	mov	ebp,eax
	mov	al,byte ptr [masmain][ebp]
	mov	bl,byte ptr [masscr][ebp]
	cmp	bl,14
	je	noswap
	cmp	al,10
	jne	nonono
	mov	byte ptr [masscr][ebp],12
	jmp	noswap
nonono:
	mov	byte ptr [masscr][ebp],al
noswap:
	pop	ebp
	
	push	eax
	push	ebx

        mov     [rr.rcLeft],12
        mov     [rr.rcTop],55
        mov     [rr.rcRight],491
        mov     [rr.rcBottom],310

        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect

	pop	ebx
	pop	eax
	cmp	al,10
	jne	noboom
	cmp	bl,14
	je	noboom
	call	boom
	jmp	shownopole
noboom:
	cmp	al,0
	jne	shownopole
	cmp	bl,14
	je	shownopole
	xor	ebx,ebx
	mov	bl,[masyi]
	push	ebx
	mov	bl,[masxi]
	push	ebx
	call	poisk

shownopole:
	pop	edx
	pop	eax
	ret
showmina endp

;#############################################
;
;#############################################
poisk proc xx:DWORD, yy:DWORD

        push eax
        push ebx
        push edx
        push ecx
        push ebp

	mov	bl,30
	xor	eax,eax
	mov	eax,[yy]
	mov	dl,byte ptr [yy]
	mul	bl
	mov	ebx,[xx]
	mov	dh,byte ptr [xx]
	add	eax,ebx	
        mov	ebp,eax
	mov     ecx,eax
        	
        cmp dl,0
        je pnomina1
        cmp byte ptr dh,0
        je pnomina1
        mov ebp,ecx
        sub ebp,31
        cmp byte ptr [masmain][ebp],0
        jne pnomina1
        cmp byte ptr [masscr][ebp],15
	jne pnomina1
	mov byte ptr [masscr][ebp],0
	xor eax,eax
	mov al,dl
	dec eax
	push eax
	xor eax,eax
	mov al,dh
	dec eax
	push eax
	call poisk
pnomina1:
	cmp byte ptr [masscr][ebp],14
	je pno1
	mov al,byte ptr [masmain][ebp]
	mov byte ptr [masscr][ebp],al
pno1:
        cmp dl,0
        je pnomina2
        mov ebp,ecx
        sub ebp,30
        cmp byte ptr [masmain][ebp],0
        jne pnomina2
        cmp byte ptr [masscr][ebp],15
	jne pnomina2
	mov byte ptr [masscr][ebp],0
	xor eax,eax
	mov al,dl
	dec eax
	push eax
	xor eax,eax
	mov al,dh
	push eax
	call poisk        
pnomina2:
	cmp byte ptr [masscr][ebp],14
	je pno2
	mov al,byte ptr [masmain][ebp]
	mov byte ptr [masscr][ebp],al
pno2:
        cmp dl,0
        je pnomina3
        cmp dh,29
        je pnomina3
        mov ebp,ecx
        sub ebp,29
        cmp byte ptr [masmain][ebp],0
        jne pnomina3
        cmp byte ptr [masscr][ebp],15
	jne pnomina3
	mov byte ptr [masscr][ebp],0
	xor eax,eax
	mov al,dl
	dec eax
	push eax
	xor eax,eax
	mov al,dh
	inc eax
	push eax
	call poisk          
pnomina3:
	cmp byte ptr [masscr][ebp],14
	je pno3
	mov al,byte ptr [masmain][ebp]
	mov byte ptr [masscr][ebp],al
pno3:
        cmp dh,0
        je pnomina4
        mov ebp,ecx
        dec ebp
        cmp byte ptr [masmain][ebp],0
        jne pnomina4
        cmp byte ptr [masscr][ebp],15
	jne pnomina4
	mov byte ptr [masscr][ebp],0
	xor eax,eax
	mov al,dl
	push eax
	xor eax,eax
	mov al,dh
	dec eax
	push eax
	call poisk         
pnomina4:
	cmp byte ptr [masscr][ebp],14
	je pno4
	mov al,byte ptr [masmain][ebp]
	mov byte ptr [masscr][ebp],al
pno4:
        cmp dh,29
        je pnomina5
        mov ebp,ecx
        inc ebp
        cmp byte ptr [masmain][ebp],0
        jne pnomina5
        cmp byte ptr [masscr][ebp],15
	jne pnomina5
	mov byte ptr [masscr][ebp],0
	xor eax,eax
	mov al,dl
	push eax
	xor eax,eax
	mov al,dh
	inc eax
	push eax
	call poisk          
pnomina5:
	cmp byte ptr [masscr][ebp],14
	je pno5
	mov al,byte ptr [masmain][ebp]
	mov byte ptr [masscr][ebp],al
pno5:
        cmp dl,15
        je pnomina6
        cmp dh,0
        je pnomina6
        mov ebp,ecx
        add ebp,29
        cmp byte ptr [masmain][ebp],0
        jne pnomina6
        cmp byte ptr [masscr][ebp],15
	jne pnomina6
	mov byte ptr [masscr][ebp],0
	xor eax,eax
	mov al,dl
	inc eax
	push eax
	xor eax,eax
	mov al,dh
	dec eax
	push eax
	call poisk         
pnomina6:
	cmp byte ptr [masscr][ebp],14
	je pno6
	mov al,byte ptr [masmain][ebp]
	mov byte ptr [masscr][ebp],al
pno6:
        cmp dl,15
        je pnomina7
        mov ebp,ecx
        add ebp,30
        cmp byte ptr [masmain][ebp],0
        jne pnomina7
        cmp byte ptr [masscr][ebp],15
	jne pnomina7
	mov byte ptr [masscr][ebp],0
	xor eax,eax
	mov al,dl
	inc eax
	push eax
	xor eax,eax
	mov al,dh
	push eax
	call poisk        
pnomina7:
	cmp byte ptr [masscr][ebp],14
	je pno7
	mov al,byte ptr [masmain][ebp]
	mov byte ptr [masscr][ebp],al
pno7:
        cmp dl,15
       je pnomina8
        cmp dh,29
        je pnomina8
        mov ebp,ecx
        add ebp,31
        cmp byte ptr [masmain][ebp],0
        jne pnomina8
        cmp byte ptr [masscr][ebp],15
	jne pnomina8
	mov byte ptr [masscr][ebp],0
	xor eax,eax
	mov al,dl
	inc eax
	push eax
	xor eax,eax
	mov al,dh
	inc eax
	push eax
	call poisk         
pnomina8:
	cmp byte ptr [masscr][ebp],14
	je pno8
	mov al,byte ptr [masmain][ebp]
	mov byte ptr [masscr][ebp],al
pno8:

        pop  ebp
        pop  ecx
        pop  edx
        pop  ebx
        pop  eax

	ret
poisk endp


;#############################################
;
;#############################################
setflag proc hwnd:DWORD, xx:WORD, yy:WORD
LOCAL masxxi:BYTE,masyyi:BYTE,polexx:WORD,poleyy:WORD

	push	eax
	push	ecx
	push	edx

	mov	ax,word ptr [xx] ;X
	sub	ax,12
	mov	dl,16
	div	dl	;al - index x
	mov	[masxxi],al
        mov     ah,16
	mul	ah
	add	ax,12
	mov	[polexx],ax

	mov	ax,word ptr [yy] ;y
	sub	ax,55
	mov	dl,16
	div	dl	;al - index y
	mov	[masyyi],al
	mov	ah,16
	mul	ah
	add	ax,55
	mov	[poleyy],ax

	push	ebp
	push	ebx
	mov	bl,30
	xor	eax,eax
	mov	al,[masyyi]
	mul	bl
	xor	bx,bx
	mov	bl,[masxxi]
	add	ax,bx
	mov	ebp,eax
	mov	al,byte ptr [masscr][ebp]

	cmp	al,12
	jb	uzeopen
	sub	al,1
	cmp	al,12
	jne	pokaok
	mov	al,15
pokaok:
	mov	byte ptr [masscr][ebp],al
	mov	ecx,ebp
uzeopen:
	pop	ebx
	pop	ebp

	push	ecx
	push	eax
	push	[hwnd]
	call	minusmina

        mov     [rr.rcLeft],12
        mov     [rr.rcTop],55
        mov     [rr.rcRight],491
        mov     [rr.rcBottom],310	

        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect

	pop	edx
	pop	ecx
	pop	eax
	ret
setflag endp

;#############################################
;
;#############################################
minusmina proc hwnd:DWORD,mina:DWORD,ukz:DWORD
	push	eax
	mov	eax,[mina]
	cmp	al,14
	jne	noadd
	
	push	ebp
	mov	ebp,[ukz]
	cmp	byte ptr [masmain][ebp],10
	jne	neugad
	cmp	byte ptr [kolmin],0
	je	neugad
	dec	byte ptr [kolmin]
neugad:
	pop	ebp

	cmp	[flagmp],1
	jne	minus1
	call	plus
	jmp	noadd4
minus1:
	call	minus
noadd:
	cmp	al,13
	jne	noadd4

	push	ebp
	mov	ebp,[ukz]
	cmp	byte ptr [masmain][ebp],10
	jne	neugad2
	cmp	byte ptr [kolmin],9
	je	neugad2
	inc	byte ptr [kolmin]
neugad2:
	pop	ebp

	cmp	[flagmp],1
	jne	minus2
	call	minus
	jmp	noadd4
minus2:
	call	plus
noadd4:
        mov     [rr.rcLeft],17
        mov     [rr.rcTop],16
        mov     [rr.rcRight],55
        mov     [rr.rcBottom],38	

        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect

	pop	eax
	ret

minus proc
         dec	byte ptr [showmin+2]
	 cmp	byte ptr [showmin+2],0ffh
	 jne	noadd2
	 mov	byte ptr [showmin+2],9
	 dec	byte ptr [showmin+1]
	 cmp	byte ptr [showmin+1],0ffh
	 jne	noadd2
	 mov	byte ptr [showmin+1],9
	 cmp	byte ptr [flagmp],1
	 jne    noflagmp
	dec byte ptr [showmin+3]
	mov byte ptr [showmin],12
	cmp byte ptr [showmin+3],0ffh
	jne noflagmp
	mov byte ptr [showmin+3],0
	 mov	byte ptr [showmin],0
noflagmp:
	 dec	byte ptr [showmin]
	 cmp	byte ptr [showmin],0ffh
	 jne	noadd2
	 cmp	[flagmp],1
	 jne	noflagmp2
	 mov	byte ptr [showmin+2],1
	 mov	byte ptr [showmin+1],0
	 mov	byte ptr [showmin],0
	 mov	byte ptr [flagmp],0
	 jmp	noadd2
noflagmp2:
	 mov	byte ptr [showmin+2],1
	 mov	byte ptr [showmin+1],0
	 mov	byte ptr [showmin],11
	 mov	byte ptr [flagmp],1
noadd2:
	ret
minus endp

plus proc
         inc	byte ptr [showmin+2]
	 cmp	byte ptr [showmin+2],10
	 jne	noadd3
	 mov	byte ptr [showmin+2],0
	 inc	byte ptr [showmin+1]
	 cmp	byte ptr [showmin+1],10
	 jne	noadd3
	 mov	byte ptr [showmin+1],0
	cmp [flagmp],1
	jne yesinc
	inc byte ptr [showmin+3]
	jmp noadd3
yesinc:
	 inc	byte ptr [showmin]
	 cmp	byte ptr [showmin],10
	 jne	noadd3
	 mov	byte ptr [showmin+2],0
	 mov	byte ptr [showmin+1],0
	 mov	byte ptr [showmin],0
noadd3:
	ret
plus endp

minusmina endp

;#############################################
;
;#############################################
cmppobeda proc
	push	eax
	push	ecx
	mov	al,byte ptr [showmin+2]
	mov	ah,byte ptr [showmin+1]
	mov	cl,byte ptr [showmin]
	mov	ch,byte ptr [showmin+3]
	cmp	al,0
	jne	nopobeda
	cmp	ah,0
	jne	nopobeda
	cmp	cl,0
	je	nopobeda2	
	cmp	cl,11
	jne	nopobeda
nopobeda2:
	cmp	ch,0
	jne	nopobeda
	cmp	byte ptr [kolmin],0
	jne	nopobeda

	push	ebp
	mov	ebp,0
cmpnext:
	cmp	byte ptr [masscr][ebp],15
	jne	cnext
	pop	ebp
	jmp	nopobeda
cnext:
	cmp	byte ptr [masscr][ebp],13
	jne	cnext2
	pop	ebp
	jmp	nopobeda
cnext2:
	inc	ebp
	cmp	ebp,480
	jne	cmpnext
	pop	ebp


	mov	[flagpobed],1
        push [idtimer]
        push [hwnd]
        call KillTimer
	mov	[timerstart],1
        mov     [smail],24
        mov     [rr.rcLeft],240
        mov     [rr.rcTop],16
        mov     [rr.rcRight],262
        mov     [rr.rcBottom],38	
        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect

	call	showpic

	cmp	[level],9
	je	allpobeda
        push    L MB_ICONASTERISK + MB_OK
        push    L offset tpobeda
        push    L offset mpobeda
        push    [hwnd]
        call    MessageBoxA

	call	cmprecord
	call	nextlevel
	jmp	nopobeda
allpobeda:
        push    L MB_ICONASTERISK + MB_OK
        push    L offset tall
        push    L offset mall
        push    [hwnd]
        call    MessageBoxA
	call	cmpallrec
	call	initgame
nopobeda:	
	pop	ecx
	pop	eax
	ret
cmppobeda endp

;#############################################
;
;#############################################
nextlevel proc
	push	eax
	push	edx

	mov	[flagzaem],0

        push    [idfon]
        call    DeleteObject
	inc	[fon]
        ;push    [fon]   
        ;push    [hInst]
        ;call    LoadBitmapA
        ;mov     [idfon],eax
	push	[fon]
	push	[hInst]
	call	BitmapFromResource
	mov	[idfon],eax 


	inc	[level]
	mov	al,byte ptr [timer]
	mov	byte ptr [baktimer],al
	mov	al,byte ptr [timer+1]
	mov	byte ptr [baktimer+1],al
	mov	al,byte ptr [timer+2]
	mov	byte ptr [baktimer+2],al
	mov	al,byte ptr [timer+3]
	mov	byte ptr [baktimer+3],al
	mov	[timerstart],0
	mov	[flagpobed],0
	mov	[flaginit],1
	
	mov	al,[level]
	mov	dl,10
	mul	dl
	add	al,9
	mov	[kolmin],al

	mov	byte ptr [showmin],0
	mov	al,[level]
	mov	byte ptr [showmin+1],al
	pop	edx
	pop	eax
	mov	byte ptr [showmin+2],9
	mov	byte ptr [showmin+3],0
	mov	[flagmp],0
	push	ebp
	mov	ebp,0
initnext2:
	mov	byte ptr [masmain][ebp],0
	mov	byte ptr [masscr][ebp],15
	inc	ebp
	cmp	ebp,480
	jne	initnext2
	pop	ebp
        call    rand
        call    countmin

        push [idtimer]
        push [hwnd]
        call KillTimer

        mov     [rr.rcLeft],0
        mov     [rr.rcTop],0
        mov     [rr.rcRight],533
        mov     [rr.rcBottom],322	
        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect	

	ret
nextlevel endp

;#############################################
;
;#############################################
boom proc
	mov	[flagpobed],2
        push [idtimer]
        push [hwnd]
        call KillTimer
	mov	[timerstart],0
	push	ebp
	push	eax
	mov	ebp,0
loopnext:
	mov	al,byte ptr [masmain][ebp]
	mov	ah,byte ptr [masscr][ebp]
	cmp	al,10
	jne	next
	cmp	ah,14
	je	next2
	cmp	ah,12
	je	next2
	mov	byte ptr [masscr][ebp],10
next:
	cmp	ah,14
	jne	next2
	mov	byte ptr [masscr][ebp],11
next2:
	inc	ebp
	cmp	ebp,480
	jne	loopnext
	pop	eax
	pop	ebp

        mov     [smail],48
        mov     [rr.rcLeft],0
        mov     [rr.rcTop],0
        mov     [rr.rcRight],533
        mov     [rr.rcBottom],322	
        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect

        push    L MB_ICONASTERISK + MB_OK
        push    L offset tboom
        push    L offset mboom
        push    [hwnd]
        call    MessageBoxA

	call	restartgame

	ret
boom endp

;#############################################
;
;#############################################
initgame proc
	mov	[flagzaem],0
	mov	[fon],4001
        push    [idfon]
        call    DeleteObject
        ;push    [fon]   
        ;push    [hInst]
        ;call    LoadBitmapA
        ;mov     [idfon],eax
	push	[fon]
	push	[hInst]
	call	BitmapFromResource
	mov	[idfon],eax 

	mov	byte ptr [timer],0
	mov	byte ptr [timer+1],0
	mov	byte ptr [timer+2],0
	mov     byte ptr [timer+3],0
	mov	byte ptr [baktimer],0
	mov	byte ptr [baktimer+1],0
	mov	byte ptr [baktimer+2],0
	mov     byte ptr [baktimer+3],0
	mov	[timerstart],0
	mov	[flaginit],1
	mov	[flagpobed],0
	mov	[kolmin],9
	mov	byte ptr [showmin],0
	mov	byte ptr [showmin+1],0
	mov	byte ptr [showmin+2],9
	mov	byte ptr [showmin+3],0
	mov	[flagmp],0
	mov	[level],0
	push	ebp
	mov	ebp,0
initnext:
	mov	byte ptr [masmain][ebp],0
	mov	byte ptr [masscr][ebp],15
	inc	ebp
	cmp	ebp,480
	jne	initnext
	pop	ebp
        call    rand
        call    countmin

        push [idtimer]
        push [hwnd]
        call KillTimer

        mov     [rr.rcLeft],0
        mov     [rr.rcTop],0
        mov     [rr.rcRight],533
        mov     [rr.rcBottom],322	
        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect
	ret
initgame endp

;#############################################
;
;#############################################
restartgame proc
	push	eax
	push	edx
	mov     [flagzaem],0
	mov	al,byte ptr [baktimer]
	mov	byte ptr [timer],al
	mov	al,byte ptr [baktimer+1]
	mov	byte ptr [timer+1],al
	mov	al,byte ptr [baktimer+2]
	mov	byte ptr [timer+2],al
	mov	al,byte ptr [baktimer+3]
	mov	byte ptr [timer+3],al
	mov	[timerstart],0
	mov	[flaginit],1
	mov	[flagpobed],0
	
	mov	al,[level]
	mov	dl,10
	mul	dl
	add	al,9
	mov	[kolmin],al

	mov	byte ptr [showmin],0
	mov	al,[level]
	mov	byte ptr [showmin+1],al
	pop	edx
	pop	eax
	mov	byte ptr [showmin+2],9
	mov	byte ptr [showmin+3],0
	mov	[flagmp],0
	push	ebp
	mov	ebp,0
initnext3:
	mov	byte ptr [masmain][ebp],0
	mov	byte ptr [masscr][ebp],15
	inc	ebp
	cmp	ebp,480
	jne	initnext3
	pop	ebp
        call    rand
        call    countmin

        push [idtimer]
        push [hwnd]
        call KillTimer

        mov     [rr.rcLeft],0
        mov     [rr.rcTop],0
        mov     [rr.rcRight],533
        mov     [rr.rcBottom],322	
        push    L 0
        push    offset rr
        push    [hwnd]
        call    InvalidateRect	

	ret
restartgame endp

;#############################################
;
;#############################################
showpic proc
	;push	[hwnd]
	;call	GetDC
	;mov	[myDC],eax

;       push    [myDC]
;        call    CreateCompatibleDC
;        mov     [memDC2],eax

;        push    [idfon]
;        push    [memDC2]
;        call    SelectObject
;        mov     [oldbmp2],eax

;        push    SRCCOPY  
;        push    L 0       ;bmp y
;        push    L 0       ;bmp x
;        push    [memDC2]
;        push    L 256      ;height
;        push    L 480      ;width
;        push    L 55
;        push    L 12
;        push    [myDC]
;        call    BitBlt

;        push    [oldbmp2]
;        push    [memDC2]
;        call    SelectObject

;        push    [memDC2]
;        call    DeleteDC

;	push	[myDC]
;	push	[hwnd]
;	call	ReleaseDC

	push	ebp
	mov	ebp,0
initnext9:
	mov	byte ptr [masscr][ebp],0
	inc	ebp
	cmp	ebp,480
	jne	initnext9
	pop	ebp

	ret
showpic endp

;#############################################
;
;#############################################
cmprecord proc
	push	eax
	push	ebx
	push	ebp

	mov al,byte ptr [timer+3]
	mov bl,byte ptr [baktimer+3]
	sub al,bl
	cmp al,10
	jb  nextsub1
	sub al,6
	and al,0fh
	mov [flagzaem],1
nextsub1:
	mov byte ptr [timerec+3],al
	mov al,byte ptr [timer+2]
	cmp [flagzaem],1
	jne nozaem1
	cmp al,0
	je nozero1
	mov [flagzaem],0
nozero1:
	dec al
nozaem1:
	mov bl,byte ptr [baktimer+2]
	sub al,bl
	cmp al,10
	jb nextsub2
	sub al,6
	and al,0fh
	mov [flagzaem],1
nextsub2: 
	mov byte ptr [timerec+2],al
	mov al,byte ptr [timer+1]
	cmp [flagzaem],1
	jne nozaem2
	cmp al,0
	je nozero2
	mov [flagzaem],0
nozero2:
	dec al
nozaem2:
	mov bl,byte ptr [baktimer+1]
	sub al,bl
	cmp al,10
	jb nextsub3
	sub al,6
	and al,0fh
	mov [flagzaem],1
nextsub3: 
	mov byte ptr [timerec+1],al
	mov al,byte ptr [timer]
	cmp [flagzaem],1
	jne nozaem3
	cmp al,0
	jne nozero3
	mov [flagzaem],0
nozero3:
	dec al
nozaem3:
	mov bl,byte ptr [baktimer]
	sub al,bl
nextsub4: 
	mov byte ptr [timerec],al

	mov al,byte ptr [level]
	mov bl,17
	mul bl
	add ax,200
	xor ebp,ebp
	mov bp,ax

	mov al,byte ptr [bufer_rw][ebp]
	sub al,30h
	mov byte ptr [timerec2],al
 	inc ebp
	mov al,byte ptr [bufer_rw][ebp]
	sub al,30h
	mov byte ptr [timerec2+1],al
	inc ebp
	mov al,byte ptr [bufer_rw][ebp]
	sub al,30h
	mov byte ptr [timerec2+2],al
	inc ebp
	mov al,byte ptr [bufer_rw][ebp]
	sub al,30h
	mov byte ptr [timerec2+3],al
	pop	ebp
	pop	ebx

	mov al,byte ptr [timerec]
	cmp al,byte ptr [timerec2]
	jb newrec
	cmp al,byte ptr [timerec2]
	jne nonewrec
	
	mov al,byte ptr [timerec+1]
	cmp al,byte ptr [timerec2+1]
	jb newrec
	cmp al,byte ptr [timerec2+1]
	jne nonewrec

	mov al,byte ptr [timerec+2]
	cmp al,byte ptr [timerec2+2]
	jb newrec
	cmp al,byte ptr [timerec2+2]
	jne nonewrec

	mov al,byte ptr [timerec+3]
	cmp al,byte ptr [timerec2+3]
	jb newrec	
	jmp nonewrec
newrec:
	pop	eax

	mov	[timerstart],0
	mov	[flaginit],1
	mov	[flagpobed],0

        push [idtimer]
        push [hwnd]
        call KillTimer

	push	L 0
	push	offset inputname
	push	[hwnd]
	push	offset szinputname
	push	[hInst]
	call	DialogBoxParamA

	jmp newrecex
nonewrec:

	pop	eax
newrecex:
	ret
cmprecord endp

;#############################################
;
;#############################################
cmpallrec proc
	push	eax
	push	ecx
	push	ebp

	mov al,byte ptr [timer+3]
	mov byte ptr [timerec+3],al
	mov al,byte ptr [timer+2]
	mov byte ptr [timerec+2],al
	mov al,byte ptr [timer+1]
	mov byte ptr [timerec+1],al
	mov al,byte ptr [timer]
	mov byte ptr [timerec],al

	mov ebp,13
	mov ecx,1
nextmesto:
	mov al,byte ptr [bufer_rw][ebp]
	sub al,30h
	mov byte ptr [timerec2],al
 	inc ebp
	mov al,byte ptr [bufer_rw][ebp]
	sub al,30h
	mov byte ptr [timerec2+1],al
	inc ebp
	mov al,byte ptr [bufer_rw][ebp]
	sub al,30h
	mov byte ptr [timerec2+2],al
	inc ebp
	mov al,byte ptr [bufer_rw][ebp]
	sub al,30h
	mov byte ptr [timerec2+3],al
	sub ebp,3

	mov al,byte ptr [timerec]
	cmp al,byte ptr [timerec2]
	jb znewrec
	cmp al,byte ptr [timerec2]
	jne znonewrec
	
	mov al,byte ptr [timerec+1]
	cmp al,byte ptr [timerec2+1]
	jb znewrec
	cmp al,byte ptr [timerec2+1]
	jne znonewrec

	mov al,byte ptr [timerec+2]
	cmp al,byte ptr [timerec2+2]
	jb znewrec
	cmp al,byte ptr [timerec2+2]
	jne znonewrec

	mov al,byte ptr [timerec+3]
	cmp al,byte ptr [timerec2+3]
	jb znewrec	
	jmp znonewrec
znewrec:
	sub	ebp,13
	mov	[mesto],ebp

	push ebx
	mov ebp,153
	mov ebx,ebp

	mov ecx,17
swapstr:
	mov al,byte ptr [bufer_rw][ebp]
	add ebp,17
	mov byte ptr [bufer_rw][ebp],al
	sub ebp,17
	inc ebp
	loop swapstr
	cmp ebx,[mesto]
	je swapall
	sub ebx,17
	mov ebp,ebx
	mov ecx,17
	jmp swapstr
swapall:
	pop	ebx
	pop	ebp
	pop	ecx
	pop	eax

	mov	[timerstart],0
	mov	[flaginit],1
	mov	[flagpobed],0

        push [idtimer]
        push [hwnd]
        call KillTimer

	push	L 0
	push	offset inputname2
	push	[hwnd]
	push	offset szinputname2
	push	[hInst]
	call	DialogBoxParamA

	jmp znewrecex
znonewrec:
	cmp	ecx,10
	je	zzz
	add	ebp,17
	inc	ecx
	jmp	nextmesto
zzz:
	pop	ebp
	pop	ecx
	pop	eax
znewrecex:
	ret
cmpallrec endp