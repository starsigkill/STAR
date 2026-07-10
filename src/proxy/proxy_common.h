#pragma once
#include <windows.h>
#include <string>
#include <filesystem>

static std::wstring STAR_FindDLLRecursive(const std::wstring& dir, const std::wstring& target_dll)
{
    std::error_code ec;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dir, std::filesystem::directory_options::skip_permission_denied, ec)) {
        if (entry.is_regular_file(ec) && _wcsicmp(entry.path().filename().c_str(), target_dll.c_str()) == 0) {
            return entry.path().wstring();
        }
    }
    return L"";
}

static DWORD WINAPI STAR_ProxyLoadThread(LPVOID)
{
    HMODULE hSteam = LoadLibraryW(L"steam_api64.dll");
    if (!hSteam) hSteam = LoadLibraryW(L"steam_api.dll");

    if (!hSteam) {
        wchar_t exe_path[MAX_PATH] = {};
        GetModuleFileNameW(NULL, exe_path, MAX_PATH);
        wchar_t* sep = wcsrchr(exe_path, L'\\');
        if (sep) *sep = 0;
        std::wstring dir(exe_path);

        std::wstring found = STAR_FindDLLRecursive(dir, L"steam_api64.dll");
        if (found.empty()) {
            found = STAR_FindDLLRecursive(dir, L"steam_api.dll");
        }
        if (!found.empty()) {
            hSteam = LoadLibraryW(found.c_str());
        }
    }

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
