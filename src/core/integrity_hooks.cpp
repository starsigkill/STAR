#include "core/integrity_hooks.h"
#include "core/star_common.h"
#include <MinHook.h>
#include <atomic>
#include <cctype>
#include <cwctype>

static std::wstring g_exe_name;
static std::string g_exe_name_a;

typedef DWORD(WINAPI* GetFileAttributesW_t)(LPCWSTR lpFileName);
static GetFileAttributesW_t orig_GetFileAttributesW = nullptr;
typedef DWORD(WINAPI* GetFileAttributesA_t)(LPCSTR lpFileName);
static GetFileAttributesA_t orig_GetFileAttributesA = nullptr;

static DWORD safe_get_attributes_w(LPCWSTR lpFileName)
{
    return orig_GetFileAttributesW ? orig_GetFileAttributesW(lpFileName) : GetFileAttributesW(lpFileName);
}

static DWORD safe_get_attributes_a(LPCSTR lpFileName)
{
    return orig_GetFileAttributesA ? orig_GetFileAttributesA(lpFileName) : GetFileAttributesA(lpFileName);
}

static void init_redirect_paths()
{
    static bool paths_initialized = false;
    if (paths_initialized) return;
    paths_initialized = true;

    wchar_t exe_path_buf[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, exe_path_buf, MAX_PATH);
    std::wstring exe_path = exe_path_buf;
    size_t last_slash = exe_path.find_last_of(L"\\/");
    if (last_slash != std::wstring::npos) {
        g_exe_name = exe_path.substr(last_slash + 1);
    } else {
        g_exe_name = exe_path;
    }

    char exe_path_buf_a[MAX_PATH] = { 0 };
    GetModuleFileNameA(NULL, exe_path_buf_a, MAX_PATH);
    std::string exe_path_a = exe_path_buf_a;
    size_t last_slash_a = exe_path_a.find_last_of("\\/");
    if (last_slash_a != std::string::npos) {
        g_exe_name_a = exe_path_a.substr(last_slash_a + 1);
    } else {
        g_exe_name_a = exe_path_a;
    }
}

static bool path_ends_with(const std::wstring& path, const std::wstring& suffix)
{
    if (path.length() < suffix.length()) return false;
    size_t off = path.length() - suffix.length();
    for (size_t i = 0; i < suffix.length(); ++i) {
        if (towlower(path[off + i]) != towlower(suffix[i])) return false;
    }
    if (off > 0 && path[off - 1] != L'\\' && path[off - 1] != L'/') return false;
    return true;
}

static bool path_ends_with_a(const std::string& path, const std::string& suffix)
{
    if (path.length() < suffix.length()) return false;
    size_t off = path.length() - suffix.length();
    for (size_t i = 0; i < suffix.length(); ++i) {
        if (tolower((unsigned char)path[off + i]) != tolower((unsigned char)suffix[i])) return false;
    }
    if (off > 0 && path[off - 1] != '\\' && path[off - 1] != '/') return false;
    return true;
}

static bool resolve_redirect_w(LPCWSTR lpFileName, std::wstring& redirected_path)
{
    if (!lpFileName) return false;

    init_redirect_paths();

    std::wstring path(lpFileName);

    if (!g_exe_name.empty() && path_ends_with(path, g_exe_name)) {
        std::wstring bak_path = path + L".bak";
        if (safe_get_attributes_w(bak_path.c_str()) != INVALID_FILE_ATTRIBUTES) {
            redirected_path = bak_path;
            return true;
        }
    }

    if (path_ends_with(path, L"steam_api64.dll") || path_ends_with(path, L"steam_api.dll")) {
        std::wstring bak_path = path + L".bak";
        if (safe_get_attributes_w(bak_path.c_str()) != INVALID_FILE_ATTRIBUTES) {
            redirected_path = bak_path;
            return true;
        }
    }

    return false;
}

static bool resolve_redirect_a(LPCSTR lpFileName, std::string& redirected_path)
{
    if (!lpFileName) return false;

    init_redirect_paths();

    std::string path(lpFileName);

    if (!g_exe_name_a.empty() && path_ends_with_a(path, g_exe_name_a)) {
        std::string bak_path = path + ".bak";
        if (safe_get_attributes_a(bak_path.c_str()) != INVALID_FILE_ATTRIBUTES) {
            redirected_path = bak_path;
            return true;
        }
    }

    if (path_ends_with_a(path, "steam_api64.dll") || path_ends_with_a(path, "steam_api.dll")) {
        std::string bak_path = path + ".bak";
        if (safe_get_attributes_a(bak_path.c_str()) != INVALID_FILE_ATTRIBUTES) {
            redirected_path = bak_path;
            return true;
        }
    }

    return false;
}

typedef HANDLE(WINAPI* CreateFileW_t)(
    LPCWSTR               lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
);
static CreateFileW_t orig_CreateFileW = nullptr;

static HANDLE WINAPI hooked_CreateFileW(
    LPCWSTR               lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
)
{
    std::wstring new_path;
    if (resolve_redirect_w(lpFileName, new_path)) {
        STAR_LOG("CreateFileW: Redirecting %ls to %ls", lpFileName, new_path.c_str());
        return orig_CreateFileW(
            new_path.c_str(),
            dwDesiredAccess,
            dwShareMode,
            lpSecurityAttributes,
            dwCreationDisposition,
            dwFlagsAndAttributes,
            hTemplateFile
        );
    }
    return orig_CreateFileW(
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile
    );
}

typedef HANDLE(WINAPI* CreateFileA_t)(
    LPCSTR                lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
);
static CreateFileA_t orig_CreateFileA = nullptr;

static HANDLE WINAPI hooked_CreateFileA(
    LPCSTR                lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
)
{
    std::string new_path;
    if (resolve_redirect_a(lpFileName, new_path)) {
        STAR_LOG("CreateFileA: Redirecting %s to %s", lpFileName, new_path.c_str());
        return orig_CreateFileA(
            new_path.c_str(),
            dwDesiredAccess,
            dwShareMode,
            lpSecurityAttributes,
            dwCreationDisposition,
            dwFlagsAndAttributes,
            hTemplateFile
        );
    }
    return orig_CreateFileA(
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile
    );
}

static DWORD WINAPI hooked_GetFileAttributesW(LPCWSTR lpFileName)
{
    std::wstring new_path;
    if (resolve_redirect_w(lpFileName, new_path)) {
        STAR_LOG("GetFileAttributesW: Redirecting %ls to %ls", lpFileName, new_path.c_str());
        return orig_GetFileAttributesW(new_path.c_str());
    }
    return orig_GetFileAttributesW(lpFileName);
}

static DWORD WINAPI hooked_GetFileAttributesA(LPCSTR lpFileName)
{
    std::string new_path;
    if (resolve_redirect_a(lpFileName, new_path)) {
        STAR_LOG("GetFileAttributesA: Redirecting %s to %s", lpFileName, new_path.c_str());
        return orig_GetFileAttributesA(new_path.c_str());
    }
    return orig_GetFileAttributesA(lpFileName);
}

typedef BOOL(WINAPI* GetFileAttributesExW_t)(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation);
static GetFileAttributesExW_t orig_GetFileAttributesExW = nullptr;

static BOOL WINAPI hooked_GetFileAttributesExW(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation)
{
    std::wstring new_path;
    if (resolve_redirect_w(lpFileName, new_path)) {
        STAR_LOG("GetFileAttributesExW: Redirecting %ls to %ls", lpFileName, new_path.c_str());
        return orig_GetFileAttributesExW(new_path.c_str(), fInfoLevelId, lpFileInformation);
    }
    return orig_GetFileAttributesExW(lpFileName, fInfoLevelId, lpFileInformation);
}

typedef BOOL(WINAPI* GetFileAttributesExA_t)(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation);
static GetFileAttributesExA_t orig_GetFileAttributesExA = nullptr;

static BOOL WINAPI hooked_GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation)
{
    std::string new_path;
    if (resolve_redirect_a(lpFileName, new_path)) {
        STAR_LOG("GetFileAttributesExA: Redirecting %s to %s", lpFileName, new_path.c_str());
        return orig_GetFileAttributesExA(new_path.c_str(), fInfoLevelId, lpFileInformation);
    }
    return orig_GetFileAttributesExA(lpFileName, fInfoLevelId, lpFileInformation);
}

static std::atomic<bool> g_integrity_hooks_installed{ false };

static bool install_hook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal, const char* name)
{
    if (!pTarget) return false;
    if (MH_CreateHook(pTarget, pDetour, ppOriginal) != MH_OK) {
        STAR_LOG("STAR_install_integrity_hooks: MH_CreateHook failed for %s", name);
        return false;
    }
    if (MH_EnableHook(pTarget) != MH_OK) {
        STAR_LOG("STAR_install_integrity_hooks: MH_EnableHook failed for %s", name);
        MH_RemoveHook(pTarget);
        return false;
    }
    return true;
}

extern "C" void STAR_install_integrity_hooks()
{
    bool expected = false;
    if (!g_integrity_hooks_installed.compare_exchange_strong(expected, true)) return;

    MH_STATUS status = MH_Initialize();
    if (status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED) {
        g_integrity_hooks_installed = false;
        return;
    }

    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    if (!hKernel32) {
        g_integrity_hooks_installed = false;
        return;
    }

    install_hook(GetProcAddress(hKernel32, "CreateFileW"), (LPVOID)&hooked_CreateFileW, (LPVOID*)&orig_CreateFileW, "CreateFileW");
    install_hook(GetProcAddress(hKernel32, "CreateFileA"), (LPVOID)&hooked_CreateFileA, (LPVOID*)&orig_CreateFileA, "CreateFileA");
    install_hook(GetProcAddress(hKernel32, "GetFileAttributesW"), (LPVOID)&hooked_GetFileAttributesW, (LPVOID*)&orig_GetFileAttributesW, "GetFileAttributesW");
    install_hook(GetProcAddress(hKernel32, "GetFileAttributesA"), (LPVOID)&hooked_GetFileAttributesA, (LPVOID*)&orig_GetFileAttributesA, "GetFileAttributesA");
    install_hook(GetProcAddress(hKernel32, "GetFileAttributesExW"), (LPVOID)&hooked_GetFileAttributesExW, (LPVOID*)&orig_GetFileAttributesExW, "GetFileAttributesExW");
    install_hook(GetProcAddress(hKernel32, "GetFileAttributesExA"), (LPVOID)&hooked_GetFileAttributesExA, (LPVOID*)&orig_GetFileAttributesExA, "GetFileAttributesExA");
}

void STAR_uninstall_integrity_hooks()
{
    if (!g_integrity_hooks_installed.exchange(false)) return;
    MH_Uninitialize();
}
