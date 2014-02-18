
#include <windows.h>
#include <commctrl.h>

#pragma pack(1)

const char g_szUser32FunctionNames[] =
    "CreateWindowExA\0"
    "DefWindowProcA\0"
    "DestroyWindow\0"
    "DispatchMessageA\0"
    "GetMessageA\0"
    "GetWindowTextA\0"
    "InvalidateRect\0"
    "PostQuitMessage\0"
    "RegisterClassA\0"
    "SendMessageA\0"
    "SetTimer\0"
    "SetWindowPos\0"
    "SetWindowTextA\0"
    "TranslateMessage\0"
    "wsprintfA\0";
const char g_nUser32Functions = 15;
void* g_pUser32FunctionPointers[15];

// indexes
#define n_CreateWindowExA  0
#define n_DefWindowProcA   1
#define n_DestroyWindow    2
#define n_DispatchMessageA 3
#define n_GetMessageA      4
#define n_GetWindowTextA   5
#define n_InvalidateRect   6
#define n_PostQuitMessage  7
#define n_RegisterClassA   8
#define n_SendMessageA     9
#define n_SetTimer         10
#define n_SetWindowPos     11
#define n_SetWindowTextA   12
#define n_TranslateMessageA 13
#define n_wsprintfA        14

#define x_CreateWindowExA(a,b,c,d,e,f,g,h,i,j,k,l) ((HWND (WINAPI*)(DWORD,LPCTSTR,LPCTSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID))g_pUser32FunctionPointers[n_CreateWindowExA])(a,b,c,d,e,f,g,h,i,j,k,l)
#define x_DefWindowProcA(a,b,c,d) ((LRESULT (WINAPI*)(HWND,UINT,WPARAM,LPARAM))g_pUser32FunctionPointers[n_DefWindowProcA])(a,b,c,d)
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
//wsprintf is a bit weird because of the whole variable args thing... i have to do this manually because macros cannot have var args
//#define x_wsprintfA(a) ((BOOL (WINAPI*)(const MSG*))g_pUser32FunctionPointers[n_wsprintfA])(a)

typedef struct Timer
{
    int nTicks;// a tick is every time a WM_TIMER goes off...
    char bTimerSet;
    HWND idMainDisplay;
    HWND idProgress;
    HWND idRealTotal;
    HWND idTotal;
    HWND idOnOffIndicator;
    HWND idPauseButton;
    HWND idEnterTime;
} Timer;

struct Timer* pTimer1;
struct Timer* pTimer2;

#define IDC_ALWAYSONTOP                 2
#define IDC_CLOSE                       3
#define IDC_SETTIME                     4
#define IDC_SETTIME2                    5
#define IDC_RESET                       6
#define IDC_RESET2                      7
#define IDC_TIME                        8
#define IDC_TIME2                       9
#define IDC_PROGRESS                    10
#define IDC_PROGRESS2                   11
#define IDC_TRUETOTAL                   12
#define IDC_TRUETOTAL2                  13
#define IDC_TOTAL                       14
#define IDC_TOTAL2                      15
#define IDC_LIST                        16
#define IDC_LIST2                       17
#define IDC_PAUSE                       18
#define IDC_PAUSE2                      19
#define IDC_ENTERTIME                   20
#define IDC_ENTERTIME2                  21

const char g_iDefault = 0;
const char g_iExpired = 1;
const COLORREF PBBarColors[2] = {CLR_DEFAULT, RGB(225, 40, 40)};
const COLORREF PBBackColors[2] = {CLR_DEFAULT, RGB(112, 20, 20)};

const COLORREF Playing = RGB(20, 192, 60);
const COLORREF Paused = RGB(225, 128, 40);
const WORD g_DefaultTotal[2] = {7200, 180};
const unsigned char g_SecondDivisions = 10;

const INITCOMMONCONTROLSEX iccx = {sizeof(iccx), ICC_PROGRESS_CLASS | ICC_LISTVIEW_CLASSES};

int HMSToSeconds(int h, int m, int s)
{
    return ((m + (h * 60)) * 60) + s;
}

void SecondsToHMS(int secs, int* h, int* m, int* s)
{
    *s = secs % 60;
    *h = secs / 3600;
    *m = (secs % 3600) / 60;
}

// like strcspn but returns the 0-based index in sz of the first occurrance
// of any characters NOT in szSet, or the index of the NULL terminator in sz
// if all characters were good
//size_t xcsncspn(const char* sz, const char* szSet)
//{
//    const char* sz2 = sz;
//    while(sz2)
//    {
//        if(StrChr(szSet, *sz2) == NULL) break;
//        sz2 ++;
//    }
//    return sz2 - sz;
//}

// in order to pack each value into a byte, we just multiply by 2.
const unsigned char g_Xs[] = {10>>1, 109>>1, 190>>1, 271>>1, 352>>1};
const unsigned char g_Yspacing = 88;// not scaled
const unsigned char g_Ys[] = {15, 30, 54, 74, 191, 196};// not scaled
const unsigned char g_Ws[] = {75>>1, 90>>1, 93>>1, 417>>1, 255>>1};
const unsigned char g_Hs[] = {16, 23, 37, 13};// not scaled

// the rect is actually 4 sets of 4 indexes to our array of different values to choose from.
// that arg also contains the control ID in the HIWORD.
// here is a breakdown of that arg:
// bit  31          - client edge?               10000000000000000000000000000000 >> 31
//                     since WS_EX_CLIENTEDGE is 00000000000000000000001000000000, we can just shift bit 31 down
// bits 30-17       - control ID                 01111111111111100000000000000000 >> 17
// bit  16          - add 88 to Y? 1=yes, 0=no   00000000000000010000000000000000 >> 16
// bits 15 14 13 12 - X                          00000000000000001111000000000000 >> 12
// bits 11 10  9  8 - Y                          00000000000000000000111100000000 >> 8
// bits  7  6  5  4 - W                          00000000000000000000000011110000 >> 4
// bits  3  2  1  0 - H                          00000000000000000000000000001111
#define MakeRectAndID(clientedge, id, Row, x, y, w, h) ((clientedge)<<31)|((id) << 17)|((Row)<<16)|(((x)<<12)|((y)<<8)|((w)<<4)|(h))

HWND g_CreateControlHParent;
HWND __CreateControl(DWORD Style, DWORD rect_and_id, const char* classname, const char* caption)
{
    HWND r = x_CreateWindowExA((rect_and_id & 0x80000000) >> 22, classname, caption, WS_CHILD | WS_VISIBLE | Style,
        g_Xs[(rect_and_id & 0xF000) >> 12] << 1,
        (g_Ys[(rect_and_id & 0xF00) >> 8]) + (g_Yspacing * ((rect_and_id & 0x10000) >> 16)),
        g_Ws[(rect_and_id & 0xF0) >> 4] << 1,
        g_Hs[rect_and_id & 0xF],
        g_CreateControlHParent,
        (HMENU)((rect_and_id & 0x7FFE0000) >> 17), (HINSTANCE)0x00400000, 0);
    x_SendMessageA(r, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);
    return r;
}


int xcstoint(const char* _sz)
{
    const char* sz;
    int r = 0;
    sz = _sz;
    while((*sz >= '0') && (*sz <= '9'))
    {
        r = (r * 10) + (*sz - '0');
        sz ++;
    }
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

void SetDlgItemTime(HWND hwnd, int h, int m, int s)
{
    char sz[11];
    char sz2[11];
    //wsprintf(sz, "%2.02d:%02d.%02d", h, m, s);
    ((int (__cdecl*)(LPTSTR,LPCTSTR,...))g_pUser32FunctionPointers[n_wsprintfA])(sz, "%2.02d:%02d.%02d", h, m, s);

    x_GetWindowTextA(hwnd, sz2, 11);
    if(lstrcmp(sz, sz2))
    {
        x_SetWindowTextA(hwnd, sz);
    }
}

int StrCpyNToInt(char* start, int len)
{
    char sz[11];
    sz[0] = 0;
    lstrcpyn(sz, start, len);
    return xcstoint(sz);
}

char ExtractSecondsFromEdit(HWND hEdit, HWND hTrueTotal, int* result)
{
    // parse the "total" text and see if we can make heads or tails of it.
    char sz[11];
    char r = 0;
    int h = 0, m = 0, s = 0;
    size_t l;
    char *pPeriod, *pColon, *pNull, *pColonPlus1, *pPeriodPlus1, *pNullPlus1;
    char bOK = 1;
    char* szTest;
    char c;

    x_GetWindowTextA(hEdit, sz, 10);
    l = lstrlen(sz);

    pNull = sz + l;
    pNullPlus1 = pNull + 1;

    // make sure the only characters are numbers or : or .
    if(l)
    {
        szTest = sz;
        while(c = *szTest)
        {
            if(c <= '0')
            {
                if(c >= '9')
                {
                    if(c != '.')
                    {
                        if(c != ':')
                        {
                            bOK = 0;
                        }
                    }
                }
            }
            szTest ++;
        }

        if(bOK)
        {
            pPeriod = xcschr(sz, '.');
            pPeriodPlus1 = pPeriod + 1;
            pColon = xcschr(sz, ':');
            pColonPlus1 = pColon + 1;
            r = 1;
            if(pPeriod)
            {
                if(pColon && (pColon < pPeriod))
                {
                    // both period and colon, and the colon is before the period.
                    // hh:mm.ss
                    h = StrCpyNToInt(sz, pColonPlus1 - sz);
                    m = StrCpyNToInt(pColonPlus1, pPeriodPlus1 - pColonPlus1);
                    s = StrCpyNToInt(pPeriodPlus1, pNullPlus1 - pPeriodPlus1);
                }
                else
                {
                    // just a period.  mm.ss
                    //h = 0;
                    m = StrCpyNToInt(sz, pPeriodPlus1 - sz);
                    s = StrCpyNToInt(pPeriodPlus1, pNullPlus1 - pPeriodPlus1);
                }
            }
            else
            {
                if(pColon)
                {
                    // just o colon...    hh:mm
                    h = StrCpyNToInt(sz, pColonPlus1 - sz);
                    m = StrCpyNToInt(pColonPlus1, pNullPlus1 - pColonPlus1);
                    //s = 0;
                }
                else
                {
                    // no punctuation at all.   ss
                    //h = 0;
                    //m = 0;
                    s = xcstoint(sz);
                }
            }

            // correct values
            *result = HMSToSeconds(h, m, s);
            if(hTrueTotal)
            {
                SecondsToHMS(*result, &h, &m, &s);
                SetDlgItemTime(hTrueTotal, h, m, s);
            }
        }
    }

    return r;
}

void SetPBColors(HWND hP, char i)
{
    x_SendMessageA(hP, PBM_SETBARCOLOR, 0, PBBarColors[i]);
    x_SendMessageA(hP, PBM_SETBKCOLOR, 0, PBBackColors[i]);
}

// uses the time info to update display, progress bar, etc...
void UpdateTimer(struct Timer* p)
{
    int h, m, s;
    PBRANGE r;
    UINT pos;
    char bAlreadyWithinBounds;

    SecondsToHMS(p->nTicks / g_SecondDivisions, &h, &m, &s);
    SetDlgItemTime(p->idMainDisplay, h, m, s);

    x_SendMessageA(p->idProgress, PBM_GETRANGE, FALSE, (LPARAM)&r);
    pos = x_SendMessageA(p->idProgress, PBM_GETPOS, 0, 0);
    bAlreadyWithinBounds = (pos <= (UINT)r.iHigh) ? 1 : 0;
    if(0 == r.iHigh)
    {
        // 0 total means forget it.
        x_SendMessageA(p->idProgress, PBM_SETPOS, 0, 0);
        if(!bAlreadyWithinBounds)
        {
            SetPBColors(p->idProgress, g_iDefault);
        }
    }
    else
    {
        if(pos != (p->nTicks % r.iHigh))// is it different than the current position?
        {
            x_SendMessageA(p->idProgress, PBM_SETPOS, p->nTicks % r.iHigh, 0);
        }
        if((p->nTicks > r.iHigh) && (bAlreadyWithinBounds))
        {
            // its out of bounds and it was IN bounds before
            SetPBColors(p->idProgress, g_iExpired);
        }
    }
    return;
}

void OnTotal(struct Timer* p, DWORD wParam)
{
    int nTotalSeconds;
    char b;
    int Max;
    if((wParam >> 16) == EN_CHANGE)
    {
        b = ExtractSecondsFromEdit(p->idTotal, p->idRealTotal, &nTotalSeconds);
        if(b)
        {
            Max = nTotalSeconds * g_SecondDivisions;
            x_SendMessageA(p->idProgress, PBM_SETRANGE32, 0, Max);
            UpdateTimer(p);
            // this is the only time besides RESET that we can go from OUT of bounds to IN bounds.
            if(p->nTicks <= Max)
            {
                SetPBColors(p->idProgress, g_iDefault);
            }
        }
    }
}


void OnPause(struct Timer* p)
{
    if(p->bTimerSet == 1)
    {
        p->bTimerSet = 0;
        x_SendMessageA(p->idOnOffIndicator, LVM_SETBKCOLOR, 0, Paused);
        x_SetWindowTextA(p->idPauseButton, "Resume");
    }
    else
    {
        p->bTimerSet = 1;
        x_SendMessageA(p->idOnOffIndicator, LVM_SETBKCOLOR, 0, Playing);
        x_SetWindowTextA(p->idPauseButton, "Pause");
    }
    x_InvalidateRect(p->idOnOffIndicator, NULL, TRUE);
}


void OnSetTime(struct Timer* p)
{
    int secs;
    if(ExtractSecondsFromEdit(p->idEnterTime, 0, &secs))
    {
        p->nTicks = secs * g_SecondDivisions;
        UpdateTimer(p);
    }
}

void OnReset(struct Timer* p)
{
    p->nTicks = 0;
    SetPBColors(p->idProgress, g_iDefault);
    UpdateTimer(p);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int i;//, iwnd;
    //HWND* pwnd;
    int h, m, s;
    WORD idc;
    HWND hTopmost;
    HFONT hFont;

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
    case WM_TIMER:
        {
            for(i = 0; i <= 1; i ++)
            {
                pTimer1[i].nTicks += pTimer1[i].bTimerSet;
                UpdateTimer(pTimer1 + i);
            }
            break;
        }
    case WM_CREATE:
        {
            // create our controls
            g_CreateControlHParent = hWnd;
            __CreateControl(BS_AUTOCHECKBOX, MakeRectAndID(0, IDC_ALWAYSONTOP, 0, 0, 4, 1, 0), "BUTTON", "Always on top");
            __CreateControl(0, MakeRectAndID(0, IDC_CLOSE, 0, 4, 4, 0, 1), "BUTTON", "Close");

            hFont = CreateFont(
                -19,
                0, 0, 0,
                FW_BOLD,
                FALSE, FALSE, FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                FF_DONTCARE,
                "Tahoma"
                );

            for(i = 0; i <= 1; i ++)
            {
                pTimer1[i].bTimerSet = 1;
                pTimer1[i].nTicks = 0;

                pTimer1[i].idMainDisplay = __CreateControl(ES_READONLY, MakeRectAndID(1, IDC_TIME + i, i, 0, 0, 2, 2), "EDIT", "");
                pTimer1[i].idRealTotal  = __CreateControl(ES_READONLY, MakeRectAndID(1, IDC_TRUETOTAL + i, i, 3, 1, 0, 1), "EDIT", "");
                pTimer1[i].idTotal = __CreateControl(0, MakeRectAndID(1, IDC_TOTAL + i, i, 4, 1, 0, 1), "EDIT", "");
                pTimer1[i].idEnterTime = __CreateControl(0, MakeRectAndID(1, IDC_ENTERTIME + i, i, 1, 1, 0, 1), "EDIT", "");

                pTimer1[i].idProgress = __CreateControl(1, MakeRectAndID(1, IDC_PROGRESS + i, i, 0, 2, 3, 3), "msctls_progress32", "");
                pTimer1[i].idOnOffIndicator = __CreateControl(0, MakeRectAndID(0, IDC_LIST + i, i, 0, 3, 4, 1), "SysListView32", "");
                pTimer1[i].idPauseButton = __CreateControl(0, MakeRectAndID(0, IDC_PAUSE + i, i, 3, 3, 0, 1), "BUTTON", "Pause");

                __CreateControl(0, MakeRectAndID(0, IDC_RESET + i, i, 4, 3, 0, 1), "BUTTON", "Reset");
                __CreateControl(0, MakeRectAndID(0, IDC_SETTIME + i, i, 2, 1, 0, 1), "BUTTON", "<-- Set Time");
                __CreateControl(0, MakeRectAndID(0, 0, i, 1, 0, 0, 3), "STATIC", "Enter Time");
                __CreateControl(0, MakeRectAndID(0, 0, i, 3, 0, 0, 3), "STATIC", "Destination Time");

                x_SendMessageA(pTimer1[i].idProgress, PBM_SETRANGE32, 0, g_DefaultTotal[i] * g_SecondDivisions);
                SecondsToHMS(g_DefaultTotal[i], &h, &m, &s);
                SetDlgItemTime(pTimer1[i].idRealTotal, h, m, s);
                x_SendMessageA(pTimer1[i].idMainDisplay, WM_SETFONT, (WPARAM)hFont, TRUE);
                x_SendMessageA(pTimer1[i].idOnOffIndicator, LVM_SETBKCOLOR, 0, Playing);
                UpdateTimer(pTimer1 + i);
            }
            x_SetTimer(hWnd, 0, 1000 / g_SecondDivisions, 0);
            break;
        }
    case WM_COMMAND:
        {
            idc = LOWORD(wParam);
            switch(idc)
            {
            case IDC_CLOSE:
                {
                    x_DestroyWindow(hWnd);
                    break;
                }
            case IDC_ALWAYSONTOP:
                {
                    if(HIWORD(wParam) == BN_CLICKED)
                    {
                        hTopmost = (BST_CHECKED == x_SendMessageA((HWND)lParam, BM_GETCHECK, 0, 0)) ? HWND_TOPMOST : HWND_NOTOPMOST;
                        x_SetWindowPos(hWnd, hTopmost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    }
                    break;
                }
            case IDC_TOTAL:
            case IDC_TOTAL2:
                OnTotal(pTimer1 + idc - IDC_TOTAL, wParam);
                break;
            case IDC_PAUSE:
            case IDC_PAUSE2:
                OnPause(pTimer1 + idc - IDC_PAUSE);
                break;

            case IDC_RESET:
            case IDC_RESET2:
                OnReset(pTimer1 + idc - IDC_RESET);
                break;
            case IDC_SETTIME:
            case IDC_SETTIME2:
                OnSetTime(pTimer1 + idc - IDC_SETTIME);
                break;
            }
            break;
        }
    }
    return TRUE;
}

const WNDCLASS wcx = { CS_VREDRAW | CS_HREDRAW, WndProc, 0, 0, (HINSTANCE)0x00400000, 0, 0, (HBRUSH)(COLOR_BTNFACE + 1), 0, "]"};

#ifdef NDEBUG
int WinMainCRTStartup()
{
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE _, PSTR __, int ___)
{
#endif
    MSG msg;
    HMODULE hm;
    struct Timer x[2];
    int i;
    const char* szFuncName;

    pTimer1 = x;
    pTimer2 = x+1;

    hm = LoadLibrary("user32");
    szFuncName = g_szUser32FunctionNames;
    for(i = 0; i < g_nUser32Functions; i ++)
    {
        g_pUser32FunctionPointers[i] = GetProcAddress(hm, szFuncName);
        szFuncName += lstrlen(szFuncName) + 1;
    }

    InitCommonControlsEx((INITCOMMONCONTROLSEX*)&iccx);

    x_RegisterClassA(&wcx);
    x_CreateWindowExA(0, "]", "Stopwatch", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 444, 244, 0, 0, (HINSTANCE)0x00400000, 0);

    while(x_GetMessageA(&msg, 0, 0, 0))
    {
        x_TranslateMessageA(&msg);
        x_DispatchMessageA(&msg);
    }
    return 0;
}
