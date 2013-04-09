include '%fasmi%\win32ax.inc'

;Código extremamente desatualizado
;Compilado com FASM (Flat assembler) 1.67.37
;
;Posso atualizar mediante solicitação, se eu estiver com muito saco para tal
;
;
;É assembly puro x8086, do not disturb.

section 'sjkdiu' code readable executable writeable

gname db 'Snake From HELL',0

gamespeed dd 55 ; This is our game loop delay

applefile db 'apple.bmp',0

struc _rect
{
.left dd 0
.top dd 0
.right dd 0
.bottom dd 0
}
rect _rect

startbonus dd 0

start: ;CODE START ============================================
push 'P'
call [GetAsyncKeyState]
invoke GetModuleHandle,0
invoke LoadBitmap,eax,10
push eax
invoke GetDC,0
invoke CreateCompatibleDC,eax
pop ecx
mov [mapple],eax
invoke SelectObject,[mapple],ecx
;Create our DC
call createmydc

;invoke CreateCompatibleDC,0
;push eax
;invoke CreateCompatibleBitmap,eax,250,30
;pop ecx
;push ecx
;invoke SelectObject,ecx,eax
;pop eax
;mov [mtext],eax
;invoke SetBkMode,[mdc],TRANSPARENT
;invoke SetTextColor,[mdc],0FFFFFFh


invoke CreateSolidBrush,0FFFFFFh
mov [clblack],eax
invoke CreateSolidBrush,0208820h
mov [clgray],eax

invoke CreateThread,0,0,createwin,0,0,0

invoke CreateThread,0,0,mainmenuproc,0,0,0
invoke GetAsyncKeyState,VK_RETURN
_main_menu:

invoke GetAsyncKeyState,VK_RETURN
test eax,eax
jz notenter

mov eax,[zmenuitem]
cmp eax,0
jne @f
call _zeroall
mov [startbonus],3
mov [gamespeed],60
call _game
jmp notenter
@@:
cmp eax,1
jne @f
call _zeroall
mov [startbonus],6
mov [gamespeed],50
call _game
jmp notenter
@@:
cmp eax,2
jne @f
call _zeroall
mov [startbonus],24
mov [gamespeed],30
call _game
jmp notenter
@@:
cmp eax,3
jne @f
call _zeroall
mov [startbonus],30
mov [gamespeed],20
call _game
jmp notenter
@@:
cmp eax,4
jne @f
call _zeroall
mov [startbonus],10
mov [gamespeed],33
mov [haswalls],1
call _game
jmp notenter
@@:
cmp eax,5
jne @f
call _zeroall
mov [startbonus],8
mov [gamespeed],25
mov [haswalls],1
call _game
jmp notenter
@@:
cmp eax,6
jne @f
mov [exitgameflag],1
@@:

notenter:

invoke Sleep,10
mov eax,[exitgameflag]
test eax,eax
jz _main_menu

;call _zeroall
;call _game ;Start main game engine

invoke ExitProcess,0DEADh
exitgameflag dd 0
isgaming dd 0
retn ; Return of main program, this should not change at all...
;##############################################################
createwin:
invoke GetModuleHandle,0
invoke DialogBoxParam,eax,37,HWND_DESKTOP,nullproc,0
retn
;##############################################################
;##############################################################
_game:
mov [isgaming],1
mov [snakesize],0

mov [applex],0ffffh
mov [appley],0ffffh

invoke VirtualAlloc,0,500h,MEM_COMMIT,PAGE_READWRITE
mov [snakebody],eax

mov ecx,[startbonus]
@@:
push ecx
call incsnake
pop ecx
loop @b

mov eax,[snakebody]
mov dword [eax],012c0190h

mov [speedx],20
mov [hasapple],0

mov [myscore],0
mov [dead],0

invoke CreateThread,0,0,dprocedure,0,0,0
_gameloop:

mov al,[ispause]
test al,al
jnz @f

call advsnake
call fixrect   ;Is our snake in place o.o"?
call makeapple ;We need an apple, dont?
call gotapple  ;Did he got the damn apple?
call isdead    ;Am i dead lol?

mov al,[dead]
test al,al
jz @f
mov [hasend],1
@@:

invoke Sleep,[gamespeed] ; Game SPEED
;The LOOP
mov al,[hasend]
test al,al
jz _gameloop

invoke DeleteDC,[mdc]
call createmydc
call scorescreen
;invoke inttohex,[myscore]
;invoke MessageBoxA,0,scorestr,'CarloS',30h
mov [isgaming],0
retn ;Return of GAME

dprocedure:
call dbackground ;First, we draw the BACKGROUND!

invoke inttohex,[myscore]
invoke TextOutA,[mdc],2,2,scorestr,32

;invoke BitBlt,[mdc],0,0,250,30,[mtext],0,0,SRCCOPY

invoke BitBlt,[mdc],[applex],[appley],20,20,[mapple],0,0,SRCCOPY
call dsnake

mov al,[ispause]
test al,al
jz @f
invoke TextOutA,[mdc],335,30,'GAME PAUSED',11
@@:

;invoke BitBlt,[mdc],0,0,20,20,[mapple],0,0,SRCCOPY
;Write to OUR screen... lol
invoke GetDC,0
push eax
invoke BitBlt,eax,0,0,800,600,[mdc],0,0,SRCCOPY
pop eax
invoke DeleteDC,eax
call hotkeys	;My hotkeys are set here =P
invoke Sleep,8 ; "60 fps"? should be 16, but 12 is ok dont?
mov al,[hasend]
test al,al
jz dprocedure
retn

;Drawing functions #############$$$$$$$$$$$$$$$$$$$$$$$$$$$$

dbackground:
mov [rect.left],0
mov [rect.top],0
mov [rect.right],800
mov [rect.bottom],600
invoke FillRect,[mdc],rect,[clblack]
retn

dbackground2:
mov [rect.left],0
mov [rect.top],0
mov [rect.right],800
mov [rect.bottom],600
invoke CreateSolidBrush,0h
invoke FillRect,[mdc],rect,eax
retn

dsnake:
mov eax,[snakesize]
test eax,eax
jz _dsnakeend
mov ecx,eax
@@:
mov eax,4
mul ecx
add eax,[snakebody]
sub eax,4
mov dx,[eax]
add eax,2
mov ax,[eax]
xchg ax,dx
; AX = Right word ; DX = Left word ; Y,X respectivamente
movzx esi,ax
mov [rect.left],esi
add esi,20
mov [rect.right],esi
movzx esi,dx
mov [rect.top],esi
add esi,20
mov [rect.bottom],esi
push ecx
invoke FillRect,[mdc],rect,[clgray]
pop ecx
loop @b
_dsnakeend:

retn

hotkeys:

invoke GetAsyncKeyState,VK_ESCAPE
test eax,eax
jz @f
mov [hasend],1
@@:

invoke GetAsyncKeyState,VK_RIGHT
test eax,eax
jz @f
mov ax,[speedy]
test ax,ax
jz @f
mov [speedy],0
mov [speedx],20
@@:
invoke GetAsyncKeyState,VK_LEFT
test eax,eax
jz @f
mov ax,[speedy]
test ax,ax
jz @f
mov [speedy],0
mov [speedx],-20
@@:

invoke GetAsyncKeyState,VK_UP
test eax,eax
jz @f
mov ax,[speedx]
test ax,ax
jz @f
mov [speedx],0
mov [speedy],-20
@@:
invoke GetAsyncKeyState,VK_DOWN
test eax,eax
jz @f
mov ax,[speedx]
test ax,ax
jz @f
mov [speedx],0
mov [speedy],20
@@:
push 'P'
call [GetAsyncKeyState]
test eax,eax
jz @f
_not01:
push 'P'
call [GetAsyncKeyState]
test eax,eax
jnz _not01
xor [ispause],1
@@:

retn

incsnake:
mov eax,[snakesize]
inc eax
mov ecx,4
mul ecx
sub eax,4
add eax,[snakebody]
mov dword [eax],0ffffffffh
inc [snakesize]
retn

advsnake:
mov ecx,[snakesize]
mov eax,[snakebody]
@@:
mov eax,4
mul ecx
sub eax,4   ;Reach our spot
test eax,eax
jz @f	    ;if our spot is 0, we dont need it anymore
add eax,[snakebody]
mov edx,eax
sub edx,4   ;Lower body
mov edx,dword [edx]
mov dword [eax],edx
loop @b
@@:
mov eax,[snakebody]
mov dx,[speedx]
add word [eax],dx
add eax,2
mov dx,[speedy]
add word [eax],dx
retn

fixrect:
mov eax,[haswalls]
test eax,eax
jnz _haswall
mov eax,[snakebody]
mov dx,[eax]
add eax,2
mov ax,[eax]
;DX = X ; AX = Y
cmp dx,800
jne @f
mov ecx,[snakebody]
mov word [ecx],0
jmp _endfixrect
@@:
cmp dx,-20
jne @f
mov ecx,[snakebody]
mov word [ecx],800
jmp _endfixrect
@@:
cmp ax,600
jne @f
mov ecx,[snakebody]
add ecx,2
mov word [ecx],0
jmp _endfixrect
@@:
cmp ax,-20
jne @f
mov ecx,[snakebody]
add ecx,2
mov word [ecx],600
jmp _endfixrect
@@:
_endfixrect:
retn
_haswall:
mov eax,[snakebody]
mov dx,[eax];X
add eax,2
mov ax,[eax];Y
cmp dx,800
jne @f
mov [dead],1
@@:
cmp ax,600
jne @f
mov [dead],1
@@:
cmp dx,-20
jne @f
mov [dead],1
@@:
cmp ax,-20
jne @f
mov [dead],1
@@:
retn

makeapple:
mov al,[hasapple]
test al,al
jnz @f
mov ebx,20
mov [hasapple],1
call [GetTickCount]
and eax,39
mul ebx
mov [applex],eax
call [GetTickCount]
and eax,29
mul ebx
mov [appley],eax
@@:
retn

gotapple:
xor edx,edx
mov eax,[snakebody]
mov dx,[eax]
add eax,2
mov ax,[eax]
and eax,0ffffh
cmp edx,[applex]
jne @f
cmp eax,[appley]
jne @f
mov [hasapple],0
mov [applex],0ffffh
call incsnake
mov eax,70
sub eax,[gamespeed]
mul eax
mov ecx,5
;mul ecx
mov ecx,[snakesize]
mul ecx
mov ecx,[haswalls]
inc ecx
mul ecx
add [myscore],eax
@@:
retn

isdead:
mov ecx,[snakesize]
mov eax,[snakebody]
xor edx,edx
mov dx,[eax]
add eax,2
mov ax,[eax]
and eax,0ffffh
mov edi,edx
mov ebx,eax ;At this rate, DI = X; BX = Y
@@:
mov eax,4
mul ecx
sub eax,4
test eax,eax
jz @f
add eax,[snakebody]
cmp di,[eax]
jne _continue01
add eax,2
cmp bx,[eax]
jne _continue01
mov [dead],1
_continue01:
loop @b
@@:
retn

_zeroall:
mov ecx,_zend-_zstart-1
@@:
mov eax,_zstart
add eax,ecx
mov byte [eax],0
loop @b
retn

createmydc:
invoke GetDC,0
invoke CreateCompatibleDC,eax
mov [mdc],eax
invoke GetDC,0
invoke CreateCompatibleBitmap,eax,800,600
mov [mbmp],eax
invoke SelectObject,[mdc],[mbmp]
invoke SetBkMode,[mdc],TRANSPARENT
invoke SetTextColor,[mdc],0050588h

retn

zmenuitem dd 0
mainmenuproc:
mov eax,[isgaming]
test eax,eax
jnz _do023

invoke GetAsyncKeyState,VK_ESCAPE
test eax,eax
jz @f
invoke ExitProcess,0DEADh
@@:

invoke GetAsyncKeyState,VK_DOWN
test eax,eax
jz @f
mov eax,[zmenuitem]
cmp eax,6
je @f
inc [zmenuitem]
_001:
invoke GetAsyncKeyState,VK_DOWN
test eax,eax
jnz _001
@@:

invoke GetAsyncKeyState,VK_UP
test eax,eax
jz @f
mov eax,[zmenuitem]
test eax,eax
jz @f
dec [zmenuitem]
_002:
invoke GetAsyncKeyState,VK_UP
test eax,eax
jnz _002
@@:

call dbackground2
invoke TextOutA,[mdc],150,50,'Snake from HELL III [ASM with COLORS = TOTAL WIN!]',50

invoke TextOutA,[mdc],50,10,'Carlão o gostosão WINs!',23

invoke TextOutA,[mdc],300,100+100-30,'Ramayan (gay) mode',18
invoke TextOutA,[mdc],300,150+100-30,'I almost have balls',19
invoke TextOutA,[mdc],300,200+100-30,'My cock kill people',19
invoke TextOutA,[mdc],300,250+100-30,'Satan is my best friend',23
invoke TextOutA,[mdc],300,300+100-30,'Damn im GOD! [Almost-Ultimate]',30
invoke TextOutA,[mdc],300,350+100-30,'I am the devil itself [Ultimate]',33
invoke TextOutA,[mdc],300,400+100-30,'Exit game',10


mov [rect.left],270
mov eax,[zmenuitem]
mov ecx,50
mul ecx
add eax,200-30
mov [rect.top],eax
mov [rect.right],285
add eax,15
mov [rect.bottom],eax
invoke CreateSolidBrush,0FFh
invoke FillRect,[mdc],rect,eax

invoke GetDC,0
push eax
invoke BitBlt,eax,0,0,800,600,[mdc],0,0,SRCCOPY
pop eax
invoke DeleteDC,eax

_do023:
invoke Sleep,16
jmp mainmenuproc

scorescreen:
call dbackground2
invoke inttohex,[myscore]
invoke TextOutA,[mdc],300,200,scorestr,32
invoke TextOutA,[mdc],300,400,'Press [ENTER] to go back to main menu, you asshole...',53
mov eax,[gamespeed]
cmp eax,20
jne @f
mov eax,[myscore]
cmp eax,0500000h
jng @f
invoke TextOutA,[mdc],300,200,'Lol, you ate satan''s balls 4 breakfast...',42
@@:

invoke GetDC,0
push eax
invoke BitBlt,eax,0,0,800,600,[mdc],0,0,SRCCOPY
pop eax
invoke DeleteDC,eax
invoke Sleep,25
invoke GetAsyncKeyState,VK_RETURN
test eax,eax
jz scorescreen
@@:
invoke GetAsyncKeyState,VK_RETURN
test eax,eax
jnz @b

retn

nullproc:
xor eax,eax
ret
jmp nullproc

.end start ;==================================================================================================================
;==================================================================================================================
;==================================================================================================================
;==================================================================================================================
;==================================================================================================================
;==================================================================================================================
;==================================================================================================================
;==================================================================================================================

inttohex dd _inttohex
_inttohex:
jmp @f
scorestr db 'Your stupid score is: 0x'
holder dd 0,0,0 ;We should need 6 bytes to make it true
@@:
xor ebx,ebx
mov edx,[esp+4] ;This will hold the parametter
mov eax,edx
and eax,0ff000000h ;Lets get our first byte
shr eax,4*6	   ;Moving to AL
call getbits
cmp al,0ah
jge @f
sub al,7
@@:
add al,55
cmp bl,0ah
jge @f
sub bl,7
@@:
add bl,55
push 0
call setbits ;Here we set the results in the result buffer



mov eax,edx
and eax,0ff0000h ;Lets get our first byte
shr eax,4*4	   ;Moving to AL
call getbits
cmp al,0ah
jge @f
sub al,7
@@:
add al,55
cmp bl,0ah
jge @f
sub bl,7
@@:
add bl,55
push 2
call setbits ;Here we set the results in the result buffer



mov eax,edx
and eax,0ff00h ;Lets get our first byte
shr eax,4*2	   ;Moving to AL
call getbits
cmp al,0ah
jge @f
sub al,7
@@:
add al,55
cmp bl,0ah
jge @f
sub bl,7
@@:
add bl,55
push 4
call setbits ;Here we set the results in the result buffer



mov eax,edx
and eax,0ffh
call getbits
cmp al,0ah
jge @f
sub al,7
@@:
add al,55
cmp bl,0ah
jge @f
sub bl,7
@@:
add bl,55
push 6
call setbits


lea eax,[holder] ;Set the result
retn 4 ;Yes, lets free it all =P
getbits:
;This function will separate AL in 2
mov bl,al ;Duplicate AL to BL
and al,0fh
shr bl,4
retn

setbits:
lea ecx,[holder]
add ecx,[esp+4]
mov byte [ecx],bl
inc ecx
mov byte [ecx],al
retn 4


section 'crapz' resource data readable



  directory RT_DIALOG,dialogs,\
	    RT_BITMAP,bitmaps

  ;resource imag,\
  ;         1,LANG_ENGLISH+SUBLANG_DEFAULT,'apple.bmp'

  ;directory RT_DIALOG,dialogs



  resource dialogs,\
	   37,LANG_ENGLISH+SUBLANG_DEFAULT,demonstration

  dialog demonstration,'Snake From HELL',0,0,525,365,WS_VISIBLE
  ;dialogitem 'STATIC','&Caption:',-1,10,10,70,8,WS_VISIBLE
  enddialog

;directory RT_BITMAP,bitmap

resource bitmaps,\
	 10,LANG_ENGLISH+SUBLANG_DEFAULT,apple

bitmap apple,'apple.bmp'


section 'DKWKZ4R' readable writeable



mdc dd ?
mtext dd ?
mbmp dd ?
mapple dd ?
clblack dd ?
clgray dd ?

hasapple db ?
applex dd ?
appley dd ?

_zstart:
snakesize dd ?
snakebody dd ?
myscore dd ?
haswalls dd ?
dead db ?
ispause db ?
hasend db ?
speedx dw ?
speedy dw ?
_zend:



