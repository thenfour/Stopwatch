
#include <windows.h>
#include "resource1.h"
#include <commctrl.h>

#pragma pack(1)
#pragma intrinsic(strcmp)
//#include <cmath>

const char g_szUser32FunctionNames[] =
    "CreateWindowExA\0"
    "DefWindowProcA\0"
//    "CallWindowProcA\0"
    "DestroyWindow\0"
    "DispatchMessageA\0"
    "GetMessageA\0"
    "GetWindowTextA\0"
    "InvalidateRect\0"
    "PostQuitMessage\0"
    "SendMessageA\0"
    "SetTimer\0"
    "SetWindowPos\0"
    "SetWindowTextA\0"
    "TranslateMessage\0"
    "RegisterClassA\0"
    "LoadCursorA\0"
    "LoadIconA\0"
    // other strings
    "Pause\0"//6
    "Resume\0"//7
    "Tahoma\0"//7
    "Destination time\0"//17
    "STATIC\0"//7
    "Enter time\0"//11
    "<-- Set time\0"//13
    "Reset\0"//6
    "SysListView32\0"//14
    "msctls_progress32\0"//18
    "EDIT\0"//5
    "BUTTON\0"//7
    "Always on top \0"//15
    "user32\0"//7
    ;
    //"wsprintfA\0";
const char g_nUser32Functions = 16;
void* g_pUser32FunctionPointers[16];
typedef LRESULT (WINAPI* sendmessage_t)(HWND,UINT,WPARAM,LPARAM);

#define len_Pause 6
#define len_Resume 7
#define len_Tahoma 7
#define len_DestinationTime 17
#define len_Static 7
#define len_EnterTime 11
#define len_SetTime 13
#define len_Reset 6
#define len_SysListView32 14
#define len_Progress32 18
#define len_Edit 5
#define len_Button 7
#define len_AlwaysOnTop 15
#define len_User32 7

#define offset_Pause 224
#define offset_Resume offset_Pause + len_Pause
#define offset_Tahoma offset_Resume + len_Resume
#define offset_DestinationTime offset_Tahoma + len_Tahoma
#define offset_Static offset_DestinationTime + len_DestinationTime
#define offset_EnterTime offset_Static + len_Static
#define offset_SetTime offset_EnterTime + len_EnterTime
#define offset_Reset offset_SetTime + len_SetTime
#define offset_SysListView32 offset_Reset + len_Reset
#define offset_Progress32 offset_SysListView32 + len_SysListView32
#define offset_Edit offset_Progress32 + len_Progress32
#define offset_Button offset_Edit + len_Edit
#define offset_AlwaysOnTop offset_Button + len_Button
#define offset_User32 offset_AlwaysOnTop + len_AlwaysOnTop

#define offset_ClassName offset_Pause
#define offset_Empty offset_User32 + len_User32 - 1

#define str_Pause g_szUser32FunctionNames + offset_Pause
#define str_Resume g_szUser32FunctionNames + offset_Resume
#define str_Tahoma g_szUser32FunctionNames + offset_Tahoma
#define str_DestinationTime g_szUser32FunctionNames + offset_DestinationTime
#define str_Static g_szUser32FunctionNames + offset_Static
#define str_EnterTime g_szUser32FunctionNames + offset_EnterTime
#define str_SetTime g_szUser32FunctionNames + offset_SetTime
#define str_Reset g_szUser32FunctionNames + offset_Reset
#define str_SysListView32 g_szUser32FunctionNames + offset_SysListView32
#define str_Progress32 g_szUser32FunctionNames + offset_Progress32
#define str_Edit g_szUser32FunctionNames + offset_Edit
#define str_Button g_szUser32FunctionNames + offset_Button
#define str_AlwaysOnTop g_szUser32FunctionNames + offset_AlwaysOnTop
#define str_User32 g_szUser32FunctionNames + offset_User32

#define str_ClassName g_szUser32FunctionNames + offset_ClassName
#define str_Empty g_szUser32FunctionNames + offset_Empty

// indexes
#define n_CreateWindowExA  0
#define n_DefWindowProcA   1
//#define n_CallWindowProcA   1
#define n_DestroyWindow    2
#define n_DispatchMessageA 3
#define n_GetMessageA      4
#define n_GetWindowTextA   5
#define n_InvalidateRect   6
#define n_PostQuitMessage  7
#define n_SendMessageA     8
#define n_SetTimer         9
#define n_SetWindowPos     10
#define n_SetWindowTextA   11
#define n_TranslateMessageA 12
#define n_RegisterClassA        13
#define n_LoadCursorA        14
#define n_LoadIconA        15
//#define n_wsprintfA        15
//#define n_GetClientRect        16
//#define n_ShowWindow       14
//#define n_MoveWindow       15

#define x_CreateWindowExA(a,b,c,d,e,f,g,h,i,j,k,l) ((HWND (WINAPI*)(DWORD,LPCTSTR,LPCTSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID))g_pUser32FunctionPointers[n_CreateWindowExA])(a,b,c,d,e,f,g,h,i,j,k,l)
#define x_DefWindowProcA(a,b,c,d) ((LRESULT (WINAPI*)(HWND,UINT,WPARAM,LPARAM))g_pUser32FunctionPointers[n_DefWindowProcA])(a,b,c,d)
//#define x_CallWindowProcA(a,b,c,d,e) ((LRESULT (WINAPI*)(WNDPROC,HWND,UINT,WPARAM,LPARAM))g_pUser32FunctionPointers[n_CallWindowProcA])(a,b,c,d,e)
#define x_DestroyWindow(a) ((BOOL (WINAPI*)(HWND))g_pUser32FunctionPointers[n_DestroyWindow])(a)
#define x_DispatchMessageA(a) ((BOOL (WINAPI*)(const MSG*))g_pUser32FunctionPointers[n_DispatchMessageA])(a)
#define x_GetMessageA(a,b,c,d) ((BOOL (WINAPI*)(MSG*,HWND,UINT,UINT))g_pUser32FunctionPointers[n_GetMessageA])(a,b,c,d)
#define x_GetWindowTextA(a,b,c) ((int (WINAPI*)(HWND,LPTSTR,int))g_pUser32FunctionPointers[n_GetWindowTextA])(a,b,c)
#define x_InvalidateRect(a,b,c) ((BOOL (WINAPI*)(HWND,CONST RECT*,BOOL))g_pUser32FunctionPointers[n_InvalidateRect])(a,b,c)
#define x_PostQuitMessage(a) ((void (WINAPI*)(int))g_pUser32FunctionPointers[n_PostQuitMessage])(a)
#define x_RegisterClassA(a) ((ATOM (WINAPI*)(CONST WNDCLASS *))g_pUser32FunctionPointers[n_RegisterClassA])(a)
#define x_SendMessageA(a,b,c,d) ((LRESULT (WINAPI*)(HWND,UINT,WPARAM,LPARAM))g_pUser32FunctionPointers[n_SendMessageA])(a,b,c,d)
#define x_SetTimer(a,b,c,d) ((UINT_PTR (WINAPI*)(HWND,UINT_PTR,UINT,TIMERPROC))g_pUser32FunctionPointers[n_SetTimer])(a,b,c,d)
#define x_SetWindowPos(a,b,c,d,e,f,g) ((BOOL (WINAPI*)(HWND,HWND,int,int,int,int,UINT))g_pUser32FunctionPointers[n_SetWindowPos])(a,b,c,d,e,f,g)
#define x_SetWindowTextA(a,b) ((BOOL (WINAPI*)(HWND,PCTSTR))g_pUser32FunctionPointers[n_SetWindowTextA])(a,b)
#define x_TranslateMessageA(a) ((BOOL (WINAPI*)(const MSG*))g_pUser32FunctionPointers[n_TranslateMessageA])(a)
#define x_LoadCursorA(a,b) ((HCURSOR (WINAPI*)(HINSTANCE,LPCTSTR))g_pUser32FunctionPointers[n_LoadCursorA])(a,b)
#define x_LoadIconA(a,b) ((HICON (WINAPI*)(HINSTANCE,LPCTSTR))g_pUser32FunctionPointers[n_LoadIconA])(a,b)
//#define x_GetClientRect(a,b) ((BOOL (WINAPI*)(HWND,LPRECT))g_pUser32FunctionPointers[n_GetClientRect])(a,b)
//#define x_ShowWindow(a,b) ((BOOL (WINAPI*)(HWND,int))g_pUser32FunctionPointers[n_ShowWindow])(a,b)
//#define x_MoveWindow(a,b,c,d,e,f) ((BOOL (WINAPI*)(HWND,int,int,int,int,BOOL))g_pUser32FunctionPointers[n_MoveWindow])(a,b,c,d,e,f)

//wsprintf is a bit weird because of the whole variable args thing... i have to do this manually because macros cannot have var args
//#define x_wsprintfA(a) ((BOOL (WINAPI*)(const MSG*))g_pUser32FunctionPointers[n_wsprintfA])(a)

typedef unsigned long MilliSeconds;

class Timer
{
public:
  Timer()
  {
    qwBaseTime = 0;
    newStartTime = GetTickCount();
    bTimerSet = true;
  }

  char IsPaused() const
  {
    return bTimerSet;
  }

  inline void SetTotalTimeSeconds(DWORD secs)
  {
    qwBaseTime = secs;
    qwBaseTime *= 1000;
    newStartTime = GetTickCount();
  }

  inline void TogglePause()
  {
    if(bTimerSet)
    {
      // need to pause
      qwBaseTime += GetLatestSegment();// commit the latest segment
      bTimerSet = false;
    }
    else
    {
      // need to un-pause
      newStartTime = GetTickCount();
      bTimerSet = true;
    }
  }

  __declspec(noinline) MilliSeconds GetTotalElapsed() const
  {
    MilliSeconds r(qwBaseTime);
    if(bTimerSet)
    {
      r += GetLatestSegment();
    }
    return r;
  }

  inline DWORD GetSecondsElapsed() const
  {
    return (DWORD)(GetTotalElapsed()/1000);
  }

  __declspec(noinline) MilliSeconds GetLatestSegment() const
  {
    DWORD now = GetTickCount();
    MilliSeconds r;
    if(now < newStartTime)
    {
      // handle GetTickCount() overflow case
      r = now - newStartTime;
    }
    else
    {
      r = (MilliSeconds)((DWORD)0 - (newStartTime - now));
    }
    return r;
  }

  HWND idMainDisplay;
  HWND idProgress;
  HWND idRealTotal;
  HWND idTotal;
  HWND idOnOffIndicator;
  HWND idPauseButton;
  HWND idEnterTime;

  HWND idTimeLeft;

private:
  MilliSeconds qwBaseTime;// in milliseconds; time BEFORE newStartTime
  DWORD newStartTime;// the exact time that we started timing from (after the last un-pause)
  char bTimerSet;
};

const char g_TimerCount = 4;
Timer* pTimers;

const WORD g_DefaultTotal[g_TimerCount] = {7200, 60, 120, 180};

const long IDC_ALWAYSONTOP                 = 2;// only 1

const long IDC_SETTIME                     = 4;
const long IDC_RESET                       = g_TimerCount + IDC_SETTIME;
const long IDC_TIME                        = g_TimerCount + IDC_RESET;
const long IDC_PROGRESS                    = g_TimerCount + IDC_TIME;
const long IDC_TRUETOTAL                   = g_TimerCount + IDC_PROGRESS;
const long IDC_TOTAL                       = g_TimerCount + IDC_TRUETOTAL;
const long IDC_LIST                        = g_TimerCount + IDC_TOTAL;
const long IDC_PAUSE                       = g_TimerCount + IDC_LIST;
const long IDC_ENTERTIME                   = g_TimerCount + IDC_PAUSE;
const long IDC_TIMELEFT                    = g_TimerCount + IDC_ENTERTIME;

const char g_iDefault = 0;
const char g_iExpired = 1;
const COLORREF PBBarColors[2] = {CLR_DEFAULT, RGB(225, 40, 40)};
const COLORREF PBBackColors[2] = {CLR_DEFAULT, RGB(112, 20, 20)};

const COLORREF Playing = RGB(20, 192, 60);
const COLORREF Paused = RGB(225, 128, 40);

const INITCOMMONCONTROLSEX iccx = {sizeof(iccx), ICC_PROGRESS_CLASS | ICC_LISTVIEW_CLASSES};

// in order to pack each value into a byte, we just multiply by 2.
const unsigned char g_Xs[] = {10>>1, 109>>1, 190>>1, 271>>1, 352>>1};
const unsigned char g_Yspacing = 92;// not scaled
const unsigned char g_Ys[] = {// not scaled
  15,  // top of everything
  30,  // top of edit boxes
  54,  // progress bar top
  74
};
const unsigned char g_Ws[] = {75>>1, 90>>1, 93>>1, 417>>1, 255>>1};
const unsigned char g_Hs[] = {16, 23, 37, 13};// not scaled
const short g_yOffset = 18;
const short g_windowWidth = 444;
const short g_initialWindowHeight = 239;
const short g_frameY = 36;

// the rect is actually 4 sets of 4 indexes to our array of different values to choose from.
// that arg also contains the control ID in the HIWORD.
// here is a breakdown of that arg:
// bit  31          - client edge?               10000000000000000000000000000000 >> 31
//                     since WS_EX_CLIENTEDGE is 00000000000000000000001000000000, we can just shift bit 31 down
// bits 30-19       - control ID                 01111111111110000000000000000000 >> 19
// bit  18          - firstrow                   00000000000001000000000000000000 >> 18
// bit  17 16       - row                        00000000000000110000000000000000 >> 16
// bits 15 14 13 12 - X                          00000000000000001111000000000000 >> 12
// bits 11 10  9  8 - Y                          00000000000000000000111100000000 >> 8
// bits  7  6  5  4 - W                          00000000000000000000000011110000 >> 4
// bits  3  2  1  0 - H                          00000000000000000000000000001111

// use 4 for row for the first row.
#define MakeRectAndID(clientedge, id, x, y, w, h, row) ((clientedge)<<31)|((id) << 19)|((row)<<16)|(((x)<<12)|((y)<<8)|((w)<<4)|(h))

HWND g_firstTimerWindow;
HWND g_CreateControlHParent;
HWND __CreateControl(DWORD Style, DWORD rect_and_id, const char* classname, const char* caption)
{
  short row = (short)((rect_and_id & 0x70000) >> 16);
  short x = g_Xs[(rect_and_id & 0xF000) >> 12] << 1;
  short y = (g_Ys[(rect_and_id & 0xF00) >> 8]) + (g_Yspacing * row) + g_yOffset;
  short w = g_Ws[(rect_and_id & 0xF0) >> 4] << 1;
  short h = g_Hs[rect_and_id & 0xF];
  if(row == g_TimerCount)// the "always on top" button
  {
    y = 8;
  }
  HWND r = x_CreateWindowExA((rect_and_id & 0x80000000) >> 22, classname, caption, WS_CHILD | WS_VISIBLE | Style,
      x, y, w, h,
      g_CreateControlHParent,
      (HMENU)((rect_and_id & 0x7FFE0000) >> 19), (HINSTANCE)0x00400000, 0);
  x_SendMessageA(r, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);
  return r;
}

short xcstoint(const char* sz)
{
    short r = 0;
    if(sz < (char*)2) goto omg;
    unsigned char digit;
    for(;;)
    {
      digit = *sz - '0';
      if(digit < 10)
      {
        r = (r * 10) + digit;
      }
      else
      {
        break;
      }
      sz ++;
    }
omg:
    return r;
}

char* xcschr(char* sz, char c)
{
    while(*sz)
    {
        if(*sz == c) return sz;
        sz++;
    }
    return 0;
}

inline char StringDoesNotEqual(const char* a, const char* b)
{
  //return (strcmp(a, b) != 0);

  // this results in smaller code than intrinsic strcmp
  for(;;)
  {
    if(*a != *b)
    {
      return true;
    }
    if(!(*a | *b))
    {
      return false;// if both are empty
    }
    a ++;
    b ++;
  }
  return false;
}

void SetDlgItemTime(HWND hwnd, int secsTotal)
{
  // 0 1 2 3 4 5 6 7 8 9
  // x x : x x . x x 0
  WORD digits[128];
  char sz[12];
  char sz2[12];

  // EAX:EDX = divide
  // ECX = counter
  // EBX = divisor arg (10);
  // EDI = pDigits
  __asm
  {
    // generate an array of digits from 0-128. (we only need 100, but 128 saves 3 bytes by using jno (2) instead of cmp cl (3) / jl (2) )
    xor ecx, ecx;//2 counter
    xor ebx, ebx;//2
    xor esi, esi;//2 - required for stosw to work.
    lea edi, digits;// 6(!)
lol:
    mov eax, ecx;//2 numerator
    mov bl, 10;//2 denominator
    idiv bl;//2

    add ax, 0x3030;//4
    stosw;//2 - copies AX to [SI:EDI] and increments EDI by 2

    inc cl;//2 stop the loop?
    jno lol;//2

    // NOW format the string.
    mov bx, 3600;//4 denom... i can safely use BX here because of the previous code - it's always less than a WORD value.
    mov eax, DWORD ptr [secsTotal];// numerator
    cdq;
    idiv ebx;

    lea edi, sz;// pointer into the string.
    lea esi, digits;

    // now hours is in EAX.
    // copy the hours digit to sz0
    mov ax, word ptr [esi+eax*2];
    stosw;
    mov dword ptr [edi], 0x2e00003a;// 2e = ':', 3a = '.'
    inc edi;

    mov cl, 60;// denom... cl is 100 from the loop before so high bytes are zero
    mov eax, edx;// remainder
    cdq;
    idiv ecx;

    // minutes is in EAX
    mov ax, word ptr [esi+eax*2];
    stosw;

    // seconds is in EDX
    inc edi;
    mov ax, word ptr [esi+edx*2];
    stosd;
  }

  x_GetWindowTextA(hwnd, sz2, 12);
  if(StringDoesNotEqual(sz, sz2))
  {
    BOOL (WINAPI* setwindowtext)(HWND,PCTSTR) = (BOOL (WINAPI*)(HWND,PCTSTR))g_pUser32FunctionPointers[n_SetWindowTextA];
    setwindowtext(hwnd, sz);
    if(g_firstTimerWindow == hwnd)
    {
      setwindowtext(g_CreateControlHParent, sz);
    }
  }
}

char ExtractSecondsFromEdit(HWND hEdit, HWND hTrueTotal, int* result)
{
    // parse the "total" text and see if we can make heads or tails of it.
    char sz[11];
    char r = 0;
    short h = 0, m = 0, s = 0;
    char *pPeriod, *pColon;

    x_GetWindowTextA(hEdit, sz, 10);
    sz[10] = 0;

    // make sure the only characters are numbers or : or .
    pPeriod = xcschr(sz, '.');
    pColon = xcschr(sz, ':');
    r = 1;
    short iBeg = xcstoint(sz);
    short iAfterPeriod = xcstoint(pPeriod + 1);
    short iAfterColon = xcstoint(pColon + 1);
    if(pPeriod)
    {
      if(pColon && (pColon < pPeriod))
      {
        // both period and colon, and the colon is before the period.
        // hh:mm.ss
        h = iBeg;
        m = iAfterColon;
        s = iAfterPeriod;
      }
      else
      {
        // just a period.  mm.ss
        m = iBeg;
        s = iAfterPeriod;
      }
    }
    else
    {
        if(pColon)
        {
          // just a colon...    hh:mm
          h = iBeg;
          m = iAfterColon;
        }
        else
        {
          s = iBeg;
        }
    }

    // correct values
    *result = (((int)m + (h * 60)) * 60) + s;
    if(hTrueTotal)
    {
        SetDlgItemTime(hTrueTotal, *result);
    }

    return r;
}

void SetPBColors(Timer& t, char i)
{
  sendmessage_t sendmessage = (sendmessage_t)g_pUser32FunctionPointers[n_SendMessageA];
  sendmessage(t.idProgress, PBM_SETBARCOLOR, 0, PBBarColors[i]);
  sendmessage(t.idProgress, PBM_SETBKCOLOR, 0, PBBackColors[i]);
}

// uses the time info to update display, progress bar, etc...
void UpdateTimer(Timer& p)
{
    //int h, m, s;
    PBRANGE r;
    UINT pos;
    char bAlreadyWithinBounds;

    int secondsElapsed = p.GetSecondsElapsed();
    SetDlgItemTime(p.idMainDisplay, secondsElapsed);

    sendmessage_t sendmessage = (sendmessage_t)g_pUser32FunctionPointers[n_SendMessageA];
    sendmessage(p.idProgress, PBM_GETRANGE, FALSE, (LPARAM)&r);
    pos = sendmessage(p.idProgress, PBM_GETPOS, 0, 0);
    bAlreadyWithinBounds = (pos <= (UINT)r.iHigh) ? 1 : 0;
    if(0 == r.iHigh)
    {
        // 0 total means forget it.
        sendmessage(p.idProgress, PBM_SETPOS, 0, 0);
        if(!bAlreadyWithinBounds)
        {
            SetPBColors(p, g_iDefault);
        }
    }
    else
    {
        int remainder = secondsElapsed % r.iHigh;
        SetDlgItemTime(p.idTimeLeft, r.iHigh - remainder);
        if(pos != remainder)// is it different than the current position?
        {
          sendmessage(p.idProgress, PBM_SETPOS, remainder, 0);
        }
        if((secondsElapsed > r.iHigh) && (bAlreadyWithinBounds))
        {
            // its out of bounds and it was IN bounds before
            SetPBColors(p, g_iExpired);
        }
    }
    return;
}

inline void OnTotal(Timer& p, DWORD wParam)
{
    int nTotalSeconds;
    char b;
    if((wParam >> 16) == EN_CHANGE)
    {
        b = ExtractSecondsFromEdit(p.idTotal, p.idRealTotal, &nTotalSeconds);
        if(b)
        {
            x_SendMessageA(p.idProgress, PBM_SETRANGE32, 0, nTotalSeconds);
            UpdateTimer(p);
            // this is the only time besides RESET that we can go from OUT of bounds to IN bounds.
            if(p.GetSecondsElapsed() <= (DWORD)nTotalSeconds)
            {
                SetPBColors(p, g_iDefault);
            }
        }
    }
}


inline void OnPause(Timer& p)
{
  const char* t = str_Resume;
  COLORREF color = Paused;
  if(!p.IsPaused())
  {
    color = Playing;
    t = str_Pause;
  }
  p.TogglePause();
  x_SetWindowTextA(p.idPauseButton, t);
  x_SendMessageA(p.idOnOffIndicator, LVM_SETBKCOLOR, 0, color);
  x_InvalidateRect(p.idOnOffIndicator, NULL, TRUE);
}


inline void OnSetTime(Timer& p)
{
    int secs;
    if(ExtractSecondsFromEdit(p.idEnterTime, 0, &secs))
    {
        p.SetTotalTimeSeconds(secs);
        UpdateTimer(p);
    }
}

inline void OnReset(Timer& p)
{
    p.SetTotalTimeSeconds(0);
    SetPBColors(p, g_iDefault);
    UpdateTimer(p);
}

inline char CommandCheck(UINT i, UINT cmd)
{
  return i >= cmd && (i < (cmd+g_TimerCount));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WORD idc;
    HWND hTopmost;

    switch(uMsg)
    {
    default:
        {
            return x_DefWindowProcA(hWnd, uMsg, wParam, lParam);
        }
    case WM_DESTROY:
        {
            x_PostQuitMessage(0);
            break;
        }
    case WM_CLOSE:
        {
            x_DestroyWindow(hWnd);
            break;
        }
    case WM_SIZING:
      {
        RECT& rc = *((RECT*)lParam);
        rc.right = g_windowWidth + rc.left;
        char rows = (char)((rc.bottom - rc.top - g_frameY - g_yOffset + (g_Yspacing / 2)) / g_Yspacing);
        if(rows > g_TimerCount)
        {
          rows = g_TimerCount;
        }
        rc.bottom = rc.top + (rows * g_Yspacing) + g_yOffset + g_frameY;
        break;
      }
    case WM_TIMER:
        {
          for(char i = 0; i < g_TimerCount; ++i)
          {
            UpdateTimer(pTimers[i]);
          }
          break;
        }
    case WM_CREATE:
        {
          // create our controls
          g_CreateControlHParent = hWnd;
          __CreateControl(BS_AUTOCHECKBOX, MakeRectAndID(0, IDC_ALWAYSONTOP, 0, 0, 1, 0, g_TimerCount), str_Button, str_AlwaysOnTop);

          int i = g_TimerCount - 1;
          for(Timer* pTimer = pTimers + g_TimerCount - 1; pTimer >= pTimers; pTimer --)
          {
              pTimer->idMainDisplay = __CreateControl(ES_READONLY, MakeRectAndID(1, IDC_TIME + i, 0, 0, 2, 2, i), str_Edit, str_Empty);
              g_firstTimerWindow = pTimer->idMainDisplay;
              pTimer->idRealTotal  = __CreateControl(ES_READONLY, MakeRectAndID(1, IDC_TRUETOTAL + i, 3, 1, 0, 1, i), str_Edit, str_Empty);
              pTimer->idTotal = __CreateControl(0, MakeRectAndID(1, IDC_TOTAL + i, 4, 1, 0, 1, i), str_Edit, str_Empty);
              pTimer->idEnterTime = __CreateControl(0, MakeRectAndID(1, IDC_ENTERTIME + i, 1, 1, 0, 1, i), str_Edit, str_Empty);

              pTimer->idProgress = __CreateControl(1, MakeRectAndID(1, IDC_PROGRESS + i, 0, 2, 3, 3, i), str_Progress32, str_Empty);
              pTimer->idOnOffIndicator = __CreateControl(0, MakeRectAndID(0, IDC_LIST + i, 0, 3, 4, 1, i), str_SysListView32, str_Empty);
              pTimer->idPauseButton = __CreateControl(0, MakeRectAndID(0, IDC_PAUSE + i, 3, 3, 0, 1, i), str_Button, str_Pause);

              __CreateControl(0, MakeRectAndID(0, IDC_RESET + i, 4, 3, 0, 1, i), str_Button, str_Reset);
              __CreateControl(0, MakeRectAndID(0, IDC_SETTIME + i, 2, 1, 0, 1, i), str_Button, str_SetTime);
              __CreateControl(0, MakeRectAndID(0, 0, 1, 0, 0, 3, i), str_Static, str_EnterTime);
              __CreateControl(0, MakeRectAndID(0, 0, 3, 0, 0, 3, i), str_Static, str_DestinationTime);

              pTimer->idTimeLeft = __CreateControl(0, MakeRectAndID(0, IDC_TIMELEFT, 4, 0, 0, 3, i), str_Static, str_Empty);

              sendmessage_t sendmessage = (sendmessage_t)g_pUser32FunctionPointers[n_SendMessageA];
              sendmessage(pTimer->idProgress, PBM_SETRANGE32, 0, g_DefaultTotal[i]);
              SetDlgItemTime(pTimer->idRealTotal, g_DefaultTotal[i]);

              sendmessage(pTimer->idMainDisplay, WM_SETFONT, (WPARAM)CreateFont(
              -19,
              0, 0, 0,
              FW_BOLD,
              FALSE, FALSE, FALSE,
              DEFAULT_CHARSET,
              OUT_DEFAULT_PRECIS,
              CLIP_DEFAULT_PRECIS,
              DEFAULT_QUALITY,
              FF_DONTCARE,
              str_Tahoma
              ), TRUE);
              sendmessage(pTimer->idOnOffIndicator, LVM_SETBKCOLOR, 0, Playing);
              UpdateTimer(*pTimer);
              i --;
          }

          x_SetTimer(hWnd, 0, 100, 0);
        }
    case WM_COMMAND:
        {
            idc = LOWORD(wParam);
            switch(idc)
            {
            case IDC_ALWAYSONTOP:
                {
                    if(HIWORD(wParam) == BN_CLICKED)
                    {
                        hTopmost = (BST_CHECKED == x_SendMessageA((HWND)lParam, BM_GETCHECK, 0, 0)) ? HWND_TOPMOST : HWND_NOTOPMOST;
                        x_SetWindowPos(hWnd, hTopmost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    }
                    break;
                }
            }
            if(CommandCheck(idc, IDC_TOTAL)) OnTotal(pTimers[idc - IDC_TOTAL], wParam);
            if(CommandCheck(idc, IDC_PAUSE)) OnPause(pTimers[idc - IDC_PAUSE]);
            if(CommandCheck(idc, IDC_RESET)) OnReset(pTimers[idc - IDC_RESET]);
            if(CommandCheck(idc, IDC_SETTIME)) OnSetTime(pTimers[idc - IDC_SETTIME]);
        }
    }
    return TRUE;
}


WNDCLASS wcx = { CS_VREDRAW | CS_HREDRAW, WndProc, 0, 0, (HINSTANCE)0x00400000, 0, (HCURSOR)0x10013, (HBRUSH)(COLOR_BTNFACE + 1), 0, str_ClassName};

#ifdef NDEBUG
int WinMainCRTStartup()
{
#else
int WINAPI WinMain(HINSTANCE ____, HINSTANCE _, PSTR __, int ___)
{
#endif
    MSG msg;
    HMODULE hm;
    Timer x[g_TimerCount];
    int i;
    const char* szFuncName;

    g_firstTimerWindow = 0;

    pTimers = x;

    hm = LoadLibrary(str_User32);
    szFuncName = g_szUser32FunctionNames;
    for(i = 0; i < g_nUser32Functions; i ++)
    {
        g_pUser32FunctionPointers[i] = GetProcAddress(hm, szFuncName);
        szFuncName += lstrlen(szFuncName) + 1;
    }

    InitCommonControlsEx((INITCOMMONCONTROLSEX*)&iccx);

    wcx.hCursor = x_LoadCursorA(0, IDC_ARROW);
    wcx.hIcon = x_LoadIconA((HINSTANCE)0x00400000, MAKEINTRESOURCE(IDI_ICON1));

    x_RegisterClassA(&wcx);
    x_CreateWindowExA(0, str_ClassName, str_Empty, (WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE) -WS_MAXIMIZEBOX, 0, 0, g_windowWidth, g_initialWindowHeight, 0, 0, (HINSTANCE)0, 0);

    while(x_GetMessageA(&msg, 0, 0, 0))
    {
        x_TranslateMessageA(&msg);
        x_DispatchMessageA(&msg);
    }
    return 0;
}
