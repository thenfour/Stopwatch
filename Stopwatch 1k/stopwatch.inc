; Some definitions :)


LoadLibraryA PROTO :DWORD
GetProcAddress PROTO :DWORD,:DWORD

WNDCLASS STRUCT
  style             DWORD      ?
  lpfnWndProc       DWORD      ?
  cbClsExtra        DWORD      ?
  cbWndExtra        DWORD      ?
  hInstance         DWORD      ?
  hIcon             DWORD      ?
  hCursor           DWORD      ?
  hbrBackground     DWORD      ?
  lpszMenuName      DWORD      ?
  lpszClassName     DWORD      ?
WNDCLASS ENDS

TimerStruct STRUCT[4]
    nTicks           DWORD    ? ;a tick is every time a WM_TIMER goes off...
    bTimerSet        BYTE     ?
    idMainDisplay    DWORD    ?
    idProgress       DWORD    ?
    idRealTotal      DWORD    ?
    idTotal          DWORD    ?
    idOnOffIndicator DWORD    ?
    idPauseButton    DWORD    ?
    idEnterTime      DWORD    ?
TimerStruct ENDS

TimerStructSize equ <sizeof(TimerStruct)>

MessageBoxA PROTO :DWORD,:DWORD,:DWORD,:DWORD
MessageBox equ <MessageBoxA>

wsprintfA PROTO C :DWORD,:VARARG
wsprintf equ <wsprintfA>

GetMessageA PROTO :DWORD,:DWORD,:DWORD,:DWORD
TranslateMessage PROTO :DWORD
DispatchMessageA PROTO :DWORD
DefWindowProcA PROTO :DWORD,:DWORD,:DWORD,:DWORD

RegisterClassA PROTO :DWORD

CreateWindowExA PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

POINT STRUCT
  x  DWORD ?
  y  DWORD ?
POINT ENDS

MSG STRUCT
  hwnd      DWORD      ?
  message   DWORD      ?
  wParam    DWORD      ?
  lParam    DWORD      ?
  time      DWORD      ?
  pt        POINT      <>
MSG ENDS

WM_DESTROY                           equ 2h
WM_CLOSE                             equ 10h

PostQuitMessage PROTO :DWORD
DestroyWindow PROTO :DWORD

