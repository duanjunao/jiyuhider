#include <windows.h>
#include"pch.h"
HWND GetWindowHandle();
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
HWND hhh;
DWORD a;
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to the DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved   // reserved
)
{

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        GetWindowHandle();
        MessageBox(hhh, TEXT("HSDH"), TEXT("DSBUDF"), MB_ICONWARNING);
        break;
    default:
        break;
    }

    return TRUE;
}

HWND GetWindowHandle()// 获取创建偶句柄
{
    DWORD dwCurrentProcessId = GetCurrentProcessId();

    if (!EnumWindows(EnumWindowsProc, (LPARAM)&dwCurrentProcessId))
    {
        return (HWND)dwCurrentProcessId;
    }

    return NULL;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)// 回调函数
{
    DWORD dwCurProcessId = *((DWORD*)lParam);
    DWORD dwProcessId = 0;

    GetWindowThreadProcessId(hwnd, &dwProcessId);
    if (dwProcessId == dwCurProcessId)
    {
        hhh = hwnd;
        SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);
        GetWindowDisplayAffinity(hwnd, &a);
        int n = 0;
        while (a != WDA_EXCLUDEFROMCAPTURE)
        {
            n++;
            SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);
            GetWindowDisplayAffinity(hwnd, &a);
            if (n > 5)
            {
                MessageBox(hhh, (LPCWSTR)hwnd, TEXT("ERROR"), MB_ICONWARNING);
                break;
            }
        }
        return TRUE;
    }

    return TRUE;
}