; #########################################################################

    .386
    .model flat, stdcall
    option casemap:none 

; #########################################################################
    include stopwatch.inc
    includelib \masm32\lib\kernel32.lib
    includelib \masm32\lib\user32.lib
    includelib \masm32\lib\comctl32.lib
    includelib \masm32\lib\gdi32.lib
; #########################################################################

.code

start:
    ; locals:
    Timer1 equ <TimerStructSize>
    Timer2 equ <TimerStructSize + TimerStructSize>
    Msg equ <TimerStructSize + TimerStructSize + sizeof(MSG)>

    enter Msg, 0
    pushad
    
    lea g_pTimer1, [ebp-Timer1]
    lea g_pTimer2, [ebp-Timer2]

    ; Register window class
    push offset g_WndClass
    call RegisterClassA

    ; Create our window
    xor eax, eax
    push eax
    push 0400000h
    push eax
    push eax
    push 244
    push 444
    push eax
    push eax
    push 10cf0000h
    push offset g_szWindowCaption
    push offset g_szClassName
    push eax

    call CreateWindowExA

    ; Message loop
MessageLoop:
    lea edx, [ebp - Msg] ; call GetMessage
    xor eax, eax
    push eax
    push eax
    push eax
    push edx
    call GetMessageA
    test eax, eax
    jz ExitMessageLoop ; if GetMessage returns 0, end
    lea edx, [ebp - Msg]
    push edx
    call TranslateMessage
    lea edx, [ebp - Msg]
    push edx
    call DispatchMessageA
    jmp MessageLoop

ExitMessageLoop:

    popad
    leave
    ret

WndProc proc
    ;_hWnd$ = 8						; size = 4
    ;_uMsg$ = 12					; size = 4
    ;_wParam$ = 16					; size = 4
    ;_lParam$ = 20					; size = 4

    enter 0, 0

    mov edx, [ebp+12] ; uMsg
    cmp edx, WM_DESTROY
    je OnDestroy
    cmp edx, WM_CLOSE
    je OnClose
    
; Default
    mov edx, [ebp+20]; lParam
    push edx
    mov edx, [ebp+16]; wParam
    push edx
    mov edx, [ebp+12]; uMsg
    push edx
    mov edx, [ebp+8]; hWnd
    push edx
    call DefWindowProcA
    jmp EndOfMessageSwitch
    
OnDestroy:
    push 0
    call PostQuitMessage
    xor eax, eax
    jmp EndOfMessageSwitch
    
OnClose:
    mov edx, [ebp+8]; hWnd
    push edx
    call DestroyWindow
    xor eax, eax
    jmp EndOfMessageSwitch
    
EndOfMessageSwitch:
    leave
    ret
WndProc endp

    g_szThing db "the address is: 0x%08x", 0

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    g_szUser32FunctionNames db "CreateWindowExA", 0
        db "DefWindowProcA", 0
        db "DestroyWindow", 0
        db "DispatchMessageA", 0
        db "GetMessageA", 0
        db "GetWindowTextA", 0
        db "InvalidateRect", 0
        db "PostQuitMessage", 0
        db "RegisterClassA", 0
        db "SendMessageA", 0
        db "SetTimer", 0
        db "SetWindowPos", 0
        db "SetWindowTextA", 0
        db "TranslateMessage", 0
        db "wsprintfA", 0

    g_nUser32Functions equ <15> ; macro
    g_pUser32FunctionPointers DWORD g_nUser32Functions dup(?) ; array of function pointers

    g_szClassName db "]", 0
    g_szWindowCaption db "Stopwatch", 0

    g_pTimer1 DWORD ?
    g_pTimer2 DWORD ?

    ; WNDCLASS struct
    g_WndClass  DWORD 3 ; style CS_VREDRAW | CS_HREDRAW
                DWORD offset WndProc
                DWORD 0
                DWORD 0
                DWORD 400000h
                DWORD 0
                DWORD 0
                DWORD 16
                DWORD 0
                DWORD offset g_szClassName

end start
