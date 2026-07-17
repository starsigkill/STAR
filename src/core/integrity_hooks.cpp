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

extern "C" void STAR_install_integrity_hooks();

typedef void* (*il2cpp_domain_get_t)();
typedef void** (*il2cpp_domain_get_assemblies_t)(void* domain, size_t* size);
typedef void* (*il2cpp_assembly_get_image_t)(void* assembly);
typedef void* (*il2cpp_class_from_name_t)(void* image, const char* namespaze, const char* name);
typedef void* (*il2cpp_class_get_method_from_name_t)(void* klass, const char* name, int argsCount);
typedef void* (*il2cpp_class_get_fields_t)(void* klass, void** iter);
typedef const char* (*il2cpp_field_get_name_t)(void* field);
typedef size_t (*il2cpp_field_get_offset_t)(void* field);
typedef uint32_t (*il2cpp_field_get_flags_t)(void* field);
typedef void* (*il2cpp_class_get_field_from_name_t)(void* klass, const char* name);
typedef void (*il2cpp_field_static_set_value_t)(void* field, void* value);

typedef void (*OnRelayNetworkStatusReceived_t)(void* __this, void* param, void* method);
static OnRelayNetworkStatusReceived_t orig_OnRelayNetworkStatusReceived = nullptr;

typedef void (*SteamManager_Awake_t)(void* __this, void* method);
static SteamManager_Awake_t orig_SteamManager_Awake = nullptr;

static int g_offset_RelayNetworkAvailable = -1;
static int g_offset_NetworkNotAvailable = -1;
static int g_offset_enable = -1;

static void hooked_OnRelayNetworkStatusReceived(void* __this, void* param, void* method)
{
    STAR_LOG("OnRelayNetworkStatusReceived: Bypassed call to prevent IndexOutOfRangeException!");
    if (__this) {
        if (g_offset_RelayNetworkAvailable != -1) {
            *(bool*)((char*)__this + g_offset_RelayNetworkAvailable) = true;
        }
        if (g_offset_NetworkNotAvailable != -1) {
            *(bool*)((char*)__this + g_offset_NetworkNotAvailable) = false;
        }
        STAR_LOG("OnRelayNetworkStatusReceived: Manually set RelayNetworkAvailable = true, NetworkNotAvailable = false!");
    }
}

static void hooked_SteamManager_Awake(void* __this, void* method)
{
    STAR_LOG("SteamManager_Awake: Intercepted Awake call.");
    if (orig_SteamManager_Awake) {
        orig_SteamManager_Awake(__this, method);
    }
    if (__this && g_offset_enable != -1) {
        *(bool*)((char*)__this + g_offset_enable) = true;
        STAR_LOG("SteamManager_Awake: Forced enable = true");
    }
}

static std::atomic<bool> g_il2cpp_hooks_installed{ false };

static bool install_il2cpp_hooks()
{
    HMODULE hGameAssembly = GetModuleHandleA("GameAssembly.dll");
    if (!hGameAssembly) return false;

    auto il2cpp_domain_get = (il2cpp_domain_get_t)GetProcAddress(hGameAssembly, "il2cpp_domain_get");
    auto il2cpp_domain_get_assemblies = (il2cpp_domain_get_assemblies_t)GetProcAddress(hGameAssembly, "il2cpp_domain_get_assemblies");
    auto il2cpp_assembly_get_image = (il2cpp_assembly_get_image_t)GetProcAddress(hGameAssembly, "il2cpp_assembly_get_image");
    auto il2cpp_class_from_name = (il2cpp_class_from_name_t)GetProcAddress(hGameAssembly, "il2cpp_class_from_name");
    auto il2cpp_class_get_method_from_name = (il2cpp_class_get_method_from_name_t)GetProcAddress(hGameAssembly, "il2cpp_class_get_method_from_name");
    auto il2cpp_class_get_fields = (il2cpp_class_get_fields_t)GetProcAddress(hGameAssembly, "il2cpp_class_get_fields");
    auto il2cpp_field_get_name = (il2cpp_field_get_name_t)GetProcAddress(hGameAssembly, "il2cpp_field_get_name");
    auto il2cpp_field_get_offset = (il2cpp_field_get_offset_t)GetProcAddress(hGameAssembly, "il2cpp_field_get_offset");
    auto il2cpp_field_get_flags = (il2cpp_field_get_flags_t)GetProcAddress(hGameAssembly, "il2cpp_field_get_flags");
    auto il2cpp_field_static_set_value = (il2cpp_field_static_set_value_t)GetProcAddress(hGameAssembly, "il2cpp_field_static_set_value");

    if (!il2cpp_domain_get || !il2cpp_domain_get_assemblies || !il2cpp_assembly_get_image ||
        !il2cpp_class_from_name || !il2cpp_class_get_method_from_name) {
        return false;
    }

    void* domain = il2cpp_domain_get();
    if (!domain) return false;

    size_t size = 0;
    void** assemblies = il2cpp_domain_get_assemblies(domain, &size);
    if (!assemblies || size == 0) return false;

    bool found_steam_manager = false;

    for (size_t i = 0; i < size; ++i) {
        void* assembly = assemblies[i];
        void* image = il2cpp_assembly_get_image(assembly);
        if (!image) continue;

        void* klass = il2cpp_class_from_name(image, "", "SteamManager");
        if (!klass) {
            klass = il2cpp_class_from_name(image, "Steamworks", "SteamManager");
        }
        if (klass) {
            found_steam_manager = true;
            if (il2cpp_class_get_fields && il2cpp_field_get_name && il2cpp_field_get_offset) {
                void* iter = nullptr;
                while (void* field = il2cpp_class_get_fields(klass, &iter)) {
                    const char* name = il2cpp_field_get_name(field);
                    size_t offset = il2cpp_field_get_offset(field);
                    if (name) {
                        if (strcmp(name, "<RelayNetworkAvailable>k__BackingField") == 0) {
                            g_offset_RelayNetworkAvailable = (int)offset;
                        }
                        else if (strcmp(name, "<NetworkNotAvailable>k__BackingField") == 0) {
                            g_offset_NetworkNotAvailable = (int)offset;
                        }
                        else if (strcmp(name, "enable") == 0) {
                            uint32_t flags = il2cpp_field_get_flags ? il2cpp_field_get_flags(field) : 0;
                            bool is_static = (flags & 0x0010) != 0;
                            if (is_static) {
                                if (il2cpp_field_static_set_value) {
                                    bool true_val = true;
                                    il2cpp_field_static_set_value(field, &true_val);
                                    STAR_LOG("STAR_install_il2cpp_hooks: Set static enable = true");
                                }
                            } else {
                                g_offset_enable = (int)offset;
                            }
                        }
                    }
                }
                if (g_offset_RelayNetworkAvailable != -1 || g_offset_NetworkNotAvailable != -1 || g_offset_enable != -1) {
                    STAR_LOG("STAR_install_il2cpp_hooks: Resolved RelayNetworkAvailable=%d NetworkNotAvailable=%d enable=%d",
                        g_offset_RelayNetworkAvailable, g_offset_NetworkNotAvailable, g_offset_enable);
                }
            }

            if (g_offset_enable != -1) {
                void* awake_method = il2cpp_class_get_method_from_name(klass, "Awake", 0);
                if (awake_method) {
                    void* methodPointer = *(void**)awake_method;
                    if (methodPointer) {
                        if (MH_CreateHook(methodPointer, (LPVOID)&hooked_SteamManager_Awake, (LPVOID*)&orig_SteamManager_Awake) == MH_OK) {
                            if (MH_EnableHook(methodPointer) == MH_OK) {
                                STAR_LOG("STAR_install_il2cpp_hooks: Hooked SteamManager.Awake to force enable");
                            }
                        }
                    }
                }
            }

            void* method = il2cpp_class_get_method_from_name(klass, "OnRelayNetworkStatusReceived", 1);
            if (method) {
                void* methodPointer = *(void**)method;
                if (methodPointer) {
                    if (MH_CreateHook(methodPointer, (LPVOID)&hooked_OnRelayNetworkStatusReceived, (LPVOID*)&orig_OnRelayNetworkStatusReceived) == MH_OK) {
                        if (MH_EnableHook(methodPointer) == MH_OK) {
                            STAR_LOG("STAR_install_il2cpp_hooks: Hooked SteamManager.OnRelayNetworkStatusReceived to bypass relay crash");
                        }
                    }
                }
            }
        }
    }

    return found_steam_manager;
}

extern "C" void STAR_install_il2cpp_hooks_deferred()
{
    bool expected = false;
    if (!g_il2cpp_hooks_installed.compare_exchange_strong(expected, true)) return;

    if (!install_il2cpp_hooks()) {
        g_il2cpp_hooks_installed = false; // Try again on next initialization call
    }
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

    STAR_install_il2cpp_hooks_deferred();
}

void STAR_uninstall_integrity_hooks()
{
    if (!g_integrity_hooks_installed.exchange(false)) return;
    MH_Uninitialize();
}
