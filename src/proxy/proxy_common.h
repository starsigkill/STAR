#pragma once
#include <windows.h>

static DWORD WINAPI STAR_ProxyLoadThread(LPVOID)
{
    HMODULE hSteam = LoadLibraryW(L"steam_api64.dll");
    if (!hSteam) hSteam = LoadLibraryW(L"steam_api.dll");
    if (hSteam) {
        typedef void(*STAR_install_integrity_hooks_t)();
        STAR_install_integrity_hooks_t pfn =
            (STAR_install_integrity_hooks_t)GetProcAddress(hSteam, "STAR_install_integrity_hooks");
        if (pfn) {
            pfn();
        }
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, STAR_ProxyLoadThread, NULL, 0, NULL);
    }
    return TRUE;
}
