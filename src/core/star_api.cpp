#include "core/star_common.h"
#include "core/callbacks.h"
#include "core/settings.h"
#include "core/storage.h"
#include "core/config.h"
#include "steam/steam_client.h"
#include "steam/isteamnetworkingsockets.h"
#include "steam/isteamnetworkingutils.h"
#include "steam/isteaminventory.h"
#include "steam/isteamhtmlsurface.h"
#include "steam/isteaminput.h"
#include "steam/isteammusic.h"
#include "steam/steam_user.h"
#include "steam/steam_friends.h"
#include "steam/steam_utils.h"
#include "steam/steam_matchmaking.h"
#include "steam/steam_matchmaking_servers.h"
#include "steam/steam_user_stats.h"
#include "steam/steam_apps.h"
#include "steam/steam_networking.h"
#include "steam/steam_remote_storage.h"
#include "steam/steam_screenshots.h"
#include "steam/steam_http.h"
#include "steam/steam_controller.h"
#include "steam/steam_ugc.h"
#include "steam/steam_applist.h"
#include "steam/steam_music.h"
#include "steam/steam_music_remote.h"
#include "steam/steam_html_surface.h"
#include "steam/steam_inventory.h"
#include "steam/steam_video.h"
#include "steam/steam_unified_messages.h"
#include "steam/steam_game_server.h"
#include "steam/steam_game_server_stats.h"
#include "steam/steam_input.h"
#include "steam/steam_networking_sockets.h"
#include "steam/steam_networking_utils.h"
#include "steam/steam_parental_settings.h"
#include "steam/steam_parties.h"
#include "steam/steam_remote_play.h"
#include "overlay/overlay.h"

#define STAR_EXPORT extern "C"

enum ESteamAPIInitResult {
    k_ESteamAPIInitResult_OK = 0,
    k_ESteamAPIInitResult_FailedGeneric = 1,
    k_ESteamAPIInitResult_NoSteamClient = 2,
    k_ESteamAPIInitResult_VersionMismatch = 3,
};

enum EServerMode {
    eServerModeInvalid = 0,
    eServerModeNoAuthentication = 1,
    eServerModeAuthentication = 2,
    eServerModeAuthenticationAndSecure = 3,
};

static HMODULE g_dll_module = nullptr;
static bool g_initialized = false;
static std::string g_dll_dir;
static uintptr_t g_lifetime_counter = 1;

typedef uint64 uint64_steamid;

struct SteamContextInitData {
    void(*fn)(void*);
    uintptr_t counter;

};

static std::string get_dll_dir()
{
    wchar_t path[MAX_PATH] = {};
    GetModuleFileNameW(g_dll_module, path, MAX_PATH);
    wchar_t* sep = wcsrchr(path, L'\\');
    if (sep) *sep = 0;
    return wstring_to_utf8(path);
}

static std::string find_settings_dir()
{
    return get_dll_dir() + "\\STAR";
}

void STAR_WriteLog(const char* fmt, ...)
{
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    char out_buf[1280];
    snprintf(out_buf, sizeof(out_buf), "[STAR] %s\n", buf);

    OutputDebugStringA(out_buf);

    static std::wstring log_wpath;
    if (log_wpath.empty()) {
        log_wpath = utf8_to_wstring(get_dll_dir() + "\\STAR\\star.log");
    }

    std::ofstream f(log_wpath, std::ios::app);
    if (f.is_open()) {
        f << out_buf;
    } else {
        wchar_t temp_path[MAX_PATH];
        if (GetTempPathW(MAX_PATH, temp_path) > 0) {
            std::wstring fallback_path = std::wstring(temp_path) + L"star.log";
            std::ofstream f_fallback(fallback_path, std::ios::app);
            if (f_fallback.is_open()) {
                f_fallback << out_buf;
            }
        }
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        g_dll_module = hModule;
        DisableThreadLibraryCalls(hModule);
        STAR_LOG("STAR loaded");
        break;
    case DLL_PROCESS_DETACH:
        if (lpReserved == nullptr && g_initialized) {
            StarOverlay::get().shutdown();
            CoUninitialize();
            g_initialized = false;
        }
        break;
    }
    return TRUE;
}

static bool star_init_internal()
{
    if (g_initialized) return true;

    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    g_dll_dir = get_dll_dir();
    std::string settings_dir = find_settings_dir();

    STAR_LOG("Settings dir: %s", settings_dir.c_str());
    Settings::get().load(settings_dir);

    if (Settings::get().app_id == 0) {
        wchar_t exe_path[MAX_PATH] = {};
        GetModuleFileNameW(nullptr, exe_path, MAX_PATH);
        wchar_t* sep = wcsrchr(exe_path, L'\\');
        if (sep) {
            *sep = 0;
            std::wstring app_id_path = std::wstring(exe_path) + L"\\steam_appid.txt";
            std::ifstream f(app_id_path);
            if (f.is_open()) {
                std::string s;
                std::getline(f, s);
                while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' '))
                    s.pop_back();
                try { Settings::get().app_id = (uint32_t)std::stoul(s); } catch (...) {}
            }
        }
    }

    Storage::get().init(Settings::get().app_id, Settings::get().steam_id);
    StarSteamUserStats::get().load_from_storage();

    std::string appid_str = std::to_string(Settings::get().app_id);
    SetEnvironmentVariableA("SteamAppId", appid_str.c_str());
    SetEnvironmentVariableA("SteamGameId", appid_str.c_str());

    SteamServersConnected_t connected{};
    STAR_PostCallback(SteamServersConnected_t::k_iCallback, &connected, sizeof(connected));

    UserStatsReceived_t stats_recv{};
    stats_recv.m_nGameID = Settings::get().app_id;
    stats_recv.m_eResult = k_EResultOK;
    stats_recv.m_steamIDUser = CSteamID(Settings::get().steam_id);
    STAR_PostCallback(UserStatsReceived_t::k_iCallback, &stats_recv, sizeof(stats_recv));

    StarOverlay::get().init();

    g_initialized = true;
    STAR_LOG("STAR initialized: AppID=%u SteamID=%llu Name=%s",
        Settings::get().app_id, Settings::get().steam_id, Settings::get().account_name.c_str());
    return true;
}

STAR_EXPORT bool SteamAPI_Init()
{
    return star_init_internal();
}

STAR_EXPORT bool SteamAPI_InitSafe(char* pszInternalCheckInterfaceVersions)
{
    STAR_UNREFERENCED(pszInternalCheckInterfaceVersions);
    return star_init_internal();
}

STAR_EXPORT ESteamAPIInitResult SteamAPI_InitEx(char* pszInternalCheckInterfaceVersions)
{
    STAR_UNREFERENCED(pszInternalCheckInterfaceVersions);
    bool ok = star_init_internal();
    return ok ? k_ESteamAPIInitResult_OK : k_ESteamAPIInitResult_FailedGeneric;
}

STAR_EXPORT ESteamAPIInitResult SteamInternal_SteamAPI_Init(const char* pszInternalCheckInterfaceVersions, char* pOutErrMsg)
{
    STAR_UNREFERENCED(pszInternalCheckInterfaceVersions);
    if (pOutErrMsg) {
        pOutErrMsg[0] = '\0';
    }
    bool ok = star_init_internal();
    return ok ? k_ESteamAPIInitResult_OK : k_ESteamAPIInitResult_FailedGeneric;
}

STAR_EXPORT void SteamAPI_Shutdown()
{
    if (!g_initialized) return;
    StarOverlay::get().shutdown();
    CoUninitialize();
    g_initialized = false;
    STAR_LOG("SteamAPI_Shutdown");
}

STAR_EXPORT bool SteamAPI_IsSteamRunning()
{
    return true;
}

STAR_EXPORT const char* SteamAPI_GetSteamInstallPath()
{
    static std::string path = g_dll_dir;
    return path.c_str();
}

STAR_EXPORT bool SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID)
{
    STAR_UNREFERENCED(unOwnAppID);
    return false;
}

STAR_EXPORT void SteamAPI_ReleaseCurrentThreadMemory() {}

STAR_EXPORT void SteamAPI_RunCallbacks()
{
    STAR_RunCallbacks();

}

STAR_EXPORT void SteamGameServer_RunCallbacks()
{
    STAR_RunCallbacks();
}

STAR_EXPORT void SteamAPI_RegisterCallback(CCallbackBase* pCallback, int iCallback)
{
    STAR_RegisterCallback(pCallback, iCallback);
}

STAR_EXPORT void SteamAPI_UnregisterCallback(CCallbackBase* pCallback)
{
    STAR_UnregisterCallback(pCallback);
}

STAR_EXPORT void SteamAPI_RegisterCallResult(CCallbackBase* pCallback, SteamAPICall_t hAPICall)
{
    STAR_RegisterCallResult(pCallback, hAPICall);
}

STAR_EXPORT void SteamAPI_UnregisterCallResult(CCallbackBase* pCallback, SteamAPICall_t hAPICall)
{
    STAR_UnregisterCallResult(pCallback, hAPICall);
}

STAR_EXPORT void SteamAPI_ManualDispatch_Init()
{
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    g_manual_dispatch_enabled = true;
    STAR_LOG("SteamAPI_ManualDispatch_Init");
}

STAR_EXPORT void SteamAPI_ManualDispatch_RunFrame(HSteamPipe hSteamPipe)
{
    STAR_UNREFERENCED(hSteamPipe);
    if (!g_manual_dispatch_enabled) {
        STAR_RunCallbacks();
    }
}

STAR_EXPORT bool SteamAPI_ManualDispatch_GetNextCallback(HSteamPipe hSteamPipe, CallbackMsg_t* pCallbackMsg)
{
    STAR_UNREFERENCED(hSteamPipe);
    if (!pCallbackMsg) return false;

    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    if (g_manual_callback_queue.empty()) {
        return false;
    }

    auto msg = std::move(g_manual_callback_queue.front());
    g_manual_callback_queue.pop_front();

    g_last_callback_data = std::move(msg.data);

    pCallbackMsg->m_hSteamUser = msg.hSteamUser;
    pCallbackMsg->m_iCallback = msg.iCallback;
    pCallbackMsg->m_pubParam = g_last_callback_data.empty() ? nullptr : g_last_callback_data.data();
    pCallbackMsg->m_cubParam = (int)g_last_callback_data.size();

    STAR_LOG("SteamAPI_ManualDispatch_GetNextCallback: callback=%d size=%d", msg.iCallback, pCallbackMsg->m_cubParam);
    return true;
}

STAR_EXPORT void SteamAPI_ManualDispatch_FreeLastCallback(HSteamPipe hSteamPipe)
{
    STAR_UNREFERENCED(hSteamPipe);
}

static bool consume_pending_result(SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed, const char* caller)
{
    if (!pCallback || !pbFailed) return false;

    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    auto it = g_pending_results.find(hSteamAPICall);
    if (it == g_pending_results.end()) {
        *pbFailed = true;
        STAR_LOG("%s: call %llu not found", caller, hSteamAPICall);
        return false;
    }

    const auto& pr = it->second;
    if (pr.callback_id != iCallbackExpected) {
        STAR_LOG("%s: call %llu ID mismatch: expected=%d actual=%d", caller, hSteamAPICall, iCallbackExpected, pr.callback_id);
    }

    int copy_sz = std::min(cubCallback, (int)pr.data.size());
    memcpy(pCallback, pr.data.data(), copy_sz);
    *pbFailed = pr.io_failure;

    STAR_LOG("%s: call %llu completed, size=%d, failed=%d", caller, hSteamAPICall, copy_sz, *pbFailed);

    g_pending_results.erase(it);
    return true;
}

STAR_EXPORT bool SteamAPI_ManualDispatch_GetAPICallResult(HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed)
{
    STAR_UNREFERENCED(hSteamPipe);
    return consume_pending_result(hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed, "ManualDispatch_GetAPICallResult");
}

STAR_EXPORT bool SteamAPI_IsCallbackRegistered(int iCallback)
{
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    auto it = g_callbacks.find(iCallback);
    return (it != g_callbacks.end() && !it->second.empty());
}

STAR_EXPORT HSteamPipe SteamAPI_GetHSteamPipe()
{
    return 1;
}

STAR_EXPORT HSteamUser SteamAPI_GetHSteamUser()
{
    return 1;
}

STAR_EXPORT HSteamPipe SteamGameServer_GetHSteamPipe()
{
    return 1;
}

STAR_EXPORT HSteamUser SteamGameServer_GetHSteamUser()
{
    return 1;
}

STAR_EXPORT void SteamAPI_SetMiniDumpComment(const char* pchMsg)
{
    STAR_UNREFERENCED(pchMsg);
}

STAR_EXPORT void SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID)
{
    STAR_UNREFERENCED(uStructuredExceptionCode);
    STAR_UNREFERENCED(pvExceptionInfo);
    STAR_UNREFERENCED(uBuildID);
}

STAR_EXPORT void* SteamInternal_ContextInit(void* pContextInitData)
{
    if (!pContextInitData) return nullptr;

    uintptr_t* data = (uintptr_t*)pContextInitData;
    void* local_ctx = &data[2];

    if (data[1] != g_lifetime_counter) {
        void(*fn)(void*) = (void(*)(void*))data[0];
        data[1] = g_lifetime_counter;
        if (fn) {
            fn(pContextInitData);
        }
    }

    return local_ctx;
}

STAR_EXPORT void* SteamInternal_CreateInterface(const char* ver)
{
    if (!ver) return nullptr;
    STAR_LOG("SteamInternal_CreateInterface: %s", ver);

    if (strstr(ver, "SteamClient")) return StarSteamClient::get().GetClientInterface(ver);
    return StarSteamClient::get().GetISteamGenericInterface(1, 1, ver);
}

STAR_EXPORT void* SteamInternal_FindOrCreateUserInterface(HSteamUser hSteamUser, const char* pszVersion)
{
    STAR_UNREFERENCED(hSteamUser);
    return SteamInternal_CreateInterface(pszVersion);
}

STAR_EXPORT void* SteamInternal_FindOrCreateGameServerInterface(HSteamUser hSteamUser, const char* pszVersion)
{
    STAR_UNREFERENCED(hSteamUser);
    return SteamInternal_CreateInterface(pszVersion);
}

STAR_EXPORT ISteamClient* SteamClient()
{
    return reinterpret_cast<ISteamClient*>(StarSteamClient::get().GetClientInterface("SteamClient017"));
}

STAR_EXPORT ISteamUser* SteamUser()
{
    return reinterpret_cast<ISteamUser*>(static_cast<ISteamUser017*>(&StarSteamUser::get()));
}

STAR_EXPORT ISteamFriends* SteamFriends()
{
    return reinterpret_cast<ISteamFriends*>(static_cast<ISteamFriends014*>(&StarSteamFriends::get()));
}

STAR_EXPORT ISteamUtils* SteamUtils()
{
    return reinterpret_cast<ISteamUtils*>(static_cast<ISteamUtils006*>(&StarSteamUtils::get()));
}

STAR_EXPORT ISteamMatchmaking* SteamMatchmaking()
{
    return &StarSteamMatchmaking::get();
}

STAR_EXPORT ISteamMatchmakingServers* SteamMatchmakingServers()
{
    return &StarSteamMatchmakingServers::get();
}

STAR_EXPORT ISteamUserStats* SteamUserStats()
{
    return reinterpret_cast<ISteamUserStats*>(static_cast<ISteamUserStats011*>(&StarSteamUserStats::get()));
}

STAR_EXPORT ISteamApps* SteamApps()
{
    return reinterpret_cast<ISteamApps*>(static_cast<ISteamApps006*>(&StarSteamApps::get()));
}

STAR_EXPORT ISteamNetworking* SteamNetworking()
{
    return &StarSteamNetworking::get();
}

STAR_EXPORT ISteamRemoteStorage* SteamRemoteStorage()
{
    return reinterpret_cast<ISteamRemoteStorage*>(static_cast<ISteamRemoteStorage012*>(&StarSteamRemoteStorage::get()));
}

STAR_EXPORT ISteamScreenshots* SteamScreenshots()
{
    return &StarSteamScreenshots::get();
}

STAR_EXPORT ISteamHTTP* SteamHTTP()
{
    return &StarSteamHTTP::get();
}

STAR_EXPORT ISteamController* SteamController()
{
    return reinterpret_cast<ISteamController*>(&StarSteamController::get());
}

STAR_EXPORT ISteamUGC* SteamUGC()
{
    return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get());
}

STAR_EXPORT ISteamAppList* SteamAppList()
{
    return &StarSteamAppList::get();
}

STAR_EXPORT ISteamMusic* SteamMusic()
{
    return &StarSteamMusic::get();
}

STAR_EXPORT ISteamMusicRemote* SteamMusicRemote()
{
    return &StarSteamMusicRemote::get();
}

STAR_EXPORT ISteamHTMLSurface* SteamHTMLSurface()
{
    return &StarSteamHTMLSurface::get();
}

STAR_EXPORT ISteamInventory* SteamInventory()
{
    return &StarSteamInventory::get();
}

STAR_EXPORT ISteamVideo* SteamVideo()
{
    return &StarSteamVideo::get();
}

STAR_EXPORT ISteamParentalSettings* SteamParentalSettings()
{
    return &StarSteamParentalSettings::get();
}

STAR_EXPORT ISteamGameServer* SteamGameServer()
{
    return &StarSteamGameServer::get();
}

STAR_EXPORT ISteamGameServerStats* SteamGameServerStats()
{
    return &StarSteamGameServerStats::get();
}

STAR_EXPORT ISteamUtils* SteamGameServerUtils()
{
    return static_cast<ISteamUtils*>(&StarSteamUtils::get());
}

STAR_EXPORT ISteamNetworking* SteamGameServerNetworking()
{
    return &StarSteamNetworking::get();
}

#pragma warning(push)
#pragma warning(disable: 4190)
STAR_EXPORT CSteamID SteamAPI_ISteamUser_GetSteamID(ISteamUser* self)
{
    STAR_LOG("SteamAPI_ISteamUser_GetSteamID(self=%p)", self);
    return StarSteamUser::get().GetSteamID();
}
#pragma warning(pop)

STAR_EXPORT bool SteamAPI_ISteamUser_BLoggedOn(ISteamUser* self)
{
    STAR_LOG("SteamAPI_ISteamUser_BLoggedOn(self=%p)", self);
    return StarSteamUser::get().BLoggedOn();
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_RequestCurrentStats(ISteamUserStats* self)
{
    STAR_LOG("SteamAPI_ISteamUserStats_RequestCurrentStats(self=%p)", self);
    return StarSteamUserStats::get().RequestCurrentStats();
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_GetAchievement(ISteamUserStats* self, const char* pchName, bool* pbAchieved)
{
    STAR_LOG("SteamAPI_ISteamUserStats_GetAchievement(self=%p, name=%s)", self, pchName ? pchName : "null");
    return StarSteamUserStats::get().GetAchievement(pchName, pbAchieved);
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_SetAchievement(ISteamUserStats* self, const char* pchName)
{
    STAR_LOG("SteamAPI_ISteamUserStats_SetAchievement(self=%p, name=%s)", self, pchName ? pchName : "null");
    return StarSteamUserStats::get().SetAchievement(pchName);
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_ClearAchievement(ISteamUserStats* self, const char* pchName)
{
    STAR_LOG("SteamAPI_ISteamUserStats_ClearAchievement(self=%p, name=%s)", self, pchName ? pchName : "null");
    return StarSteamUserStats::get().ClearAchievement(pchName);
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_StoreStats(ISteamUserStats* self)
{
    STAR_LOG("SteamAPI_ISteamUserStats_StoreStats(self=%p)", self);
    return StarSteamUserStats::get().StoreStats();
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_GetStatInt32(ISteamUserStats* self, const char* pchName, int32* pData)
{
    STAR_LOG("SteamAPI_ISteamUserStats_GetStatInt32(self=%p, name=%s)", self, pchName ? pchName : "null");
    return StarSteamUserStats::get().GetStat(pchName, pData);
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_GetStatFloat(ISteamUserStats* self, const char* pchName, float* pData)
{
    STAR_LOG("SteamAPI_ISteamUserStats_GetStatFloat(self=%p, name=%s)", self, pchName ? pchName : "null");
    return StarSteamUserStats::get().GetStat(pchName, pData);
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_SetStatInt32(ISteamUserStats* self, const char* pchName, int32 nData)
{
    STAR_LOG("SteamAPI_ISteamUserStats_SetStatInt32(self=%p, name=%s)", self, pchName ? pchName : "null");
    return StarSteamUserStats::get().SetStat(pchName, nData);
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_SetStatFloat(ISteamUserStats* self, const char* pchName, float fData)
{
    STAR_LOG("SteamAPI_ISteamUserStats_SetStatFloat(self=%p, name=%s)", self, pchName ? pchName : "null");
    return StarSteamUserStats::get().SetStat(pchName, fData);
}

STAR_EXPORT uint32 SteamAPI_ISteamUtils_GetAppID(ISteamUtils* self)
{
    STAR_LOG("SteamAPI_ISteamUtils_GetAppID(self=%p)", self);
    return StarSteamUtils::get().GetAppID();
}

STAR_EXPORT bool SteamAPI_ISteamApps_BIsSubscribed(ISteamApps* self)
{
    STAR_LOG("SteamAPI_ISteamApps_BIsSubscribed(self=%p)", self);
    return StarSteamApps::get().BIsSubscribed();
}

STAR_EXPORT bool SteamAPI_ISteamApps_BIsDlcInstalled(ISteamApps* self, AppId_t appID)
{
    STAR_LOG("SteamAPI_ISteamApps_BIsDlcInstalled(self=%p, dlc=%u)", self, appID);
    return StarSteamApps::get().BIsDlcInstalled(appID);
}

STAR_EXPORT const char* SteamAPI_ISteamApps_GetCurrentGameLanguage(ISteamApps* self)
{
    STAR_LOG("SteamAPI_ISteamApps_GetCurrentGameLanguage(self=%p)", self);
    return StarSteamApps::get().GetCurrentGameLanguage();
}

STAR_EXPORT const char* SteamAPI_ISteamFriends_GetPersonaName(ISteamFriends* self)
{
    STAR_LOG("SteamAPI_ISteamFriends_GetPersonaName(self=%p)", self);
    return StarSteamFriends::get().GetPersonaName();
}

STAR_EXPORT bool SteamAPI_ISteamRemoteStorage_FileWrite(ISteamRemoteStorage* self, const char* pchFile, const void* pvData, int32 cubData)
{
    STAR_LOG("SteamAPI_ISteamRemoteStorage_FileWrite(self=%p, file=%s)", self, pchFile ? pchFile : "null");
    return StarSteamRemoteStorage::get().FileWrite(pchFile, pvData, cubData);
}

STAR_EXPORT int32 SteamAPI_ISteamRemoteStorage_FileRead(ISteamRemoteStorage* self, const char* pchFile, void* pvData, int32 cubDataToRead)
{
    STAR_LOG("SteamAPI_ISteamRemoteStorage_FileRead(self=%p, file=%s)", self, pchFile ? pchFile : "null");
    return StarSteamRemoteStorage::get().FileRead(pchFile, pvData, cubDataToRead);
}

STAR_EXPORT bool SteamAPI_ISteamRemoteStorage_FileExists(ISteamRemoteStorage* self, const char* pchFile)
{
    STAR_LOG("SteamAPI_ISteamRemoteStorage_FileExists(self=%p, file=%s)", self, pchFile ? pchFile : "null");
    return StarSteamRemoteStorage::get().FileExists(pchFile);
}

STAR_EXPORT bool SteamGameServer_Init(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char* pchVersionString)
{
    STAR_UNREFERENCED(unIP); STAR_UNREFERENCED(usSteamPort); STAR_UNREFERENCED(usGamePort);
    STAR_UNREFERENCED(usQueryPort); STAR_UNREFERENCED(eServerMode); STAR_UNREFERENCED(pchVersionString);
    return true;
}

STAR_EXPORT void SteamGameServer_Shutdown() {}

STAR_EXPORT bool SteamGameServer_BSecure() { return false; }
STAR_EXPORT uint64 SteamGameServer_GetSteamID() { return Settings::get().steam_id; }
STAR_EXPORT bool SteamInternal_GameServer_Init(uint32 unIP, uint16 usPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char* pchVersionString) { STAR_UNREFERENCED(unIP); STAR_UNREFERENCED(usPort); STAR_UNREFERENCED(usGamePort); STAR_UNREFERENCED(usQueryPort); STAR_UNREFERENCED(eServerMode); STAR_UNREFERENCED(pchVersionString); return true; }

STAR_EXPORT HSteamPipe SteamAPI_ISteamClient_CreateSteamPipe(ISteamClient* self)
{
    return self ? self->CreateSteamPipe() : 0;
}

STAR_EXPORT bool SteamAPI_ISteamClient_BReleaseSteamPipe(ISteamClient* self, HSteamPipe hSteamPipe)
{
    return self ? self->BReleaseSteamPipe(hSteamPipe) : false;
}

STAR_EXPORT HSteamUser SteamAPI_ISteamClient_ConnectToGlobalUser(ISteamClient* self, HSteamPipe hSteamPipe)
{
    return self ? self->ConnectToGlobalUser(hSteamPipe) : 0;
}

STAR_EXPORT HSteamUser SteamAPI_ISteamClient_CreateLocalUser(ISteamClient* self, HSteamPipe* phSteamPipe, EAccountType eAccountType)
{
    return self ? self->CreateLocalUser(phSteamPipe, eAccountType) : 0;
}

STAR_EXPORT void SteamAPI_ISteamClient_ReleaseUser(ISteamClient* self, HSteamPipe hSteamPipe, HSteamUser hUser)
{
    if (self) self->ReleaseUser(hSteamPipe, hUser);
}

STAR_EXPORT ISteamUser* SteamAPI_ISteamClient_GetISteamUser(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamUser(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamGameServer* SteamAPI_ISteamClient_GetISteamGameServer(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamGameServer(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT void SteamAPI_ISteamClient_SetLocalIPBinding(ISteamClient* self, const SteamIPAddress_t& unIP, uint16 usPort)
{
    if (self) self->SetLocalIPBinding(unIP, usPort);
}

STAR_EXPORT ISteamFriends* SteamAPI_ISteamClient_GetISteamFriends(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamFriends(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamUtils* SteamAPI_ISteamClient_GetISteamUtils(ISteamClient* self, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamUtils(hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamMatchmaking* SteamAPI_ISteamClient_GetISteamMatchmaking(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamMatchmaking(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamMatchmakingServers* SteamAPI_ISteamClient_GetISteamMatchmakingServers(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamMatchmakingServers(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT void* SteamAPI_ISteamClient_GetISteamGenericInterface(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamGenericInterface(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamUserStats* SteamAPI_ISteamClient_GetISteamUserStats(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamUserStats(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamGameServerStats* SteamAPI_ISteamClient_GetISteamGameServerStats(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamGameServerStats(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamApps* SteamAPI_ISteamClient_GetISteamApps(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamApps(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamNetworking* SteamAPI_ISteamClient_GetISteamNetworking(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamNetworking(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamRemoteStorage* SteamAPI_ISteamClient_GetISteamRemoteStorage(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamRemoteStorage(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamScreenshots* SteamAPI_ISteamClient_GetISteamScreenshots(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamScreenshots(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamGameSearch* SteamAPI_ISteamClient_GetISteamGameSearch(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    STAR_UNREFERENCED(self);
    return StarSteamClient::get().GetISteamGameSearch(hSteamuser, hSteamPipe, pchVersion);
}

STAR_EXPORT uint32 SteamAPI_ISteamClient_GetIPCCallCount(ISteamClient* self)
{
    return self ? self->GetIPCCallCount() : 0;
}

STAR_EXPORT void SteamAPI_ISteamClient_SetWarningMessageHook(ISteamClient* self, SteamAPIWarningMessageHook_t pFunction)
{
    if (self) self->SetWarningMessageHook(pFunction);
}

STAR_EXPORT bool SteamAPI_ISteamClient_BShutdownIfAllPipesClosed(ISteamClient* self)
{
    return self ? self->BShutdownIfAllPipesClosed() : false;
}

STAR_EXPORT ISteamHTTP* SteamAPI_ISteamClient_GetISteamHTTP(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamHTTP(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamController* SteamAPI_ISteamClient_GetISteamController(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamController(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamUGC* SteamAPI_ISteamClient_GetISteamUGC(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamUGC(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamAppList* SteamAPI_ISteamClient_GetISteamAppList(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    STAR_UNREFERENCED(self);
    return StarSteamClient::get().GetISteamAppList(hSteamUser, hSteamPipe, pchVersion);
}

STAR_EXPORT ISteamMusic* SteamAPI_ISteamClient_GetISteamMusic(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamMusic(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamMusicRemote* SteamAPI_ISteamClient_GetISteamMusicRemote(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    STAR_UNREFERENCED(self);
    return StarSteamClient::get().GetISteamMusicRemote(hSteamuser, hSteamPipe, pchVersion);
}

STAR_EXPORT ISteamHTMLSurface* SteamAPI_ISteamClient_GetISteamHTMLSurface(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamHTMLSurface(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamInventory* SteamAPI_ISteamClient_GetISteamInventory(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamInventory(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamVideo* SteamAPI_ISteamClient_GetISteamVideo(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamVideo(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamParentalSettings* SteamAPI_ISteamClient_GetISteamParentalSettings(ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamParentalSettings(hSteamuser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamInput* SteamAPI_ISteamClient_GetISteamInput(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamInput(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamParties* SteamAPI_ISteamClient_GetISteamParties(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamParties(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}

STAR_EXPORT ISteamRemotePlay* SteamAPI_ISteamClient_GetISteamRemotePlay(ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion)
{
    return self ? self->GetISteamRemotePlay(hSteamUser, hSteamPipe, pchVersion) : nullptr;
}


STAR_EXPORT int SteamAPI_ISteamApps_GetLaunchCommandLine(ISteamApps* self, char* pszCommandLine, int cubCommandLine)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pszCommandLine); STAR_UNREFERENCED(cubCommandLine);
    return 0;
}

STAR_EXPORT void SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialogConnectString(ISteamFriends* self, const char* pchConnectString)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pchConnectString);
}

STAR_EXPORT bool SteamAPI_ISteamFriends_HasFriend(ISteamFriends* self, uint64_steamid steamIDFriend, int iFriendFlags)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(iFriendFlags);
    return false;
}

STAR_EXPORT void SteamAPI_ISteamFriends_SetPlayedWith(ISteamFriends* self, uint64_steamid steamIDUserPlayedWith)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(steamIDUserPlayedWith);
}

STAR_EXPORT bool SteamAPI_ISteamFriends_SetRichPresence(ISteamFriends* self, const char* pchKey, const char* pchValue)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pchKey); STAR_UNREFERENCED(pchValue);
    return true;
}

STAR_EXPORT uint64 SteamAPI_ISteamGameServer_GetSteamID(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
    return Settings::get().steam_id;
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_Find(ISteamHTMLSurface* self, HHTMLBrowser hHTMLBrowser, const char* pchSearchStr, bool bCurrentlyOnPage, bool bReverse)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hHTMLBrowser); STAR_UNREFERENCED(pchSearchStr); STAR_UNREFERENCED(bCurrentlyOnPage); STAR_UNREFERENCED(bReverse);
}

STAR_EXPORT const char* SteamAPI_ISteamInput_GetGlyphPNGForActionOrigin(ISteamInput* self, EInputActionOrigin eOrigin, ESteamInputGlyphSize eSize, uint32 unFlags)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(eOrigin); STAR_UNREFERENCED(eSize); STAR_UNREFERENCED(unFlags);
    return "";
}


STAR_EXPORT EInputActionOrigin SteamAPI_ISteamInput_TranslateActionOrigin(ISteamInput* self, ESteamInputType eDestinationInputType, EInputActionOrigin eSourceOrigin)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(eDestinationInputType); STAR_UNREFERENCED(eSourceOrigin);
    return k_EInputActionOrigin_None;
}

STAR_EXPORT bool SteamAPI_ISteamInventory_GenerateItems(ISteamInventory* self, SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayItemDefs, const uint32* punArrayQuantity, uint32 unArrayLength)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pResultHandle); STAR_UNREFERENCED(pArrayItemDefs); STAR_UNREFERENCED(punArrayQuantity); STAR_UNREFERENCED(unArrayLength);
    return false;
}

STAR_EXPORT float SteamAPI_ISteamMusic_GetVolume(ISteamMusic* self)
{
    STAR_UNREFERENCED(self);
    return 0.0f;
}

STAR_EXPORT void SteamAPI_ISteamMusic_PlayNext(ISteamMusic* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamNetworkingConnectionSignaling_Release(void* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingSockets_AcceptConnection(ISteamNetworkingSockets* self, HSteamNetConnection hConn)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hConn);
    return k_EResultFail;
}

STAR_EXPORT bool SteamAPI_ISteamNetworkingSockets_CloseConnection(ISteamNetworkingSockets* self, HSteamNetConnection hPeer, int nReason, const char* pszDebug, bool bEnableLinger)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hPeer); STAR_UNREFERENCED(nReason); STAR_UNREFERENCED(pszDebug); STAR_UNREFERENCED(bEnableLinger);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamNetworkingSockets_CloseListenSocket(ISteamNetworkingSockets* self, HSteamListenSocket hSocket)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hSocket);
    return true;
}

STAR_EXPORT HSteamNetConnection SteamAPI_ISteamNetworkingSockets_ConnectByIPAddress(ISteamNetworkingSockets* self, const SteamNetworkingIPAddr* pAddr, int nOptions, const SteamNetworkingConfigValue_t* pOptions)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pAddr); STAR_UNREFERENCED(nOptions); STAR_UNREFERENCED(pOptions);
    return 0;
}

STAR_EXPORT HSteamNetConnection SteamAPI_ISteamNetworkingSockets_ConnectP2P(ISteamNetworkingSockets* self, const SteamNetworkingIdentity* identityRemote, int nVirtualPort, int nOptions, const SteamNetworkingConfigValue_t* pOptions)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(identityRemote); STAR_UNREFERENCED(nVirtualPort); STAR_UNREFERENCED(nOptions); STAR_UNREFERENCED(pOptions);
    return 0;
}

STAR_EXPORT HSteamListenSocket SteamAPI_ISteamNetworkingSockets_CreateListenSocketIP(ISteamNetworkingSockets* self, const SteamNetworkingIPAddr* pAddr, int nOptions, const SteamNetworkingConfigValue_t* pOptions)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pAddr); STAR_UNREFERENCED(nOptions); STAR_UNREFERENCED(pOptions);
    return 0;
}

STAR_EXPORT HSteamListenSocket SteamAPI_ISteamNetworkingSockets_CreateListenSocketP2P(ISteamNetworkingSockets* self, int nVirtualPort, int nOptions, const SteamNetworkingConfigValue_t* pOptions)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nVirtualPort); STAR_UNREFERENCED(nOptions); STAR_UNREFERENCED(pOptions);
    return 0;
}

STAR_EXPORT HSteamNetPollGroup SteamAPI_ISteamNetworkingSockets_CreatePollGroup(ISteamNetworkingSockets* self)
{
    STAR_UNREFERENCED(self);
    return 0;
}

STAR_EXPORT bool SteamAPI_ISteamNetworkingSockets_DestroyPollGroup(ISteamNetworkingSockets* self, HSteamNetPollGroup hPollGroup)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hPollGroup);
    return true;
}

STAR_EXPORT int SteamAPI_ISteamNetworkingSockets_ReceiveMessagesOnPollGroup(ISteamNetworkingSockets* self, HSteamNetPollGroup hPollGroup, SteamNetworkingMessage_t** ppOutMessages, int nMaxMessages)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hPollGroup); STAR_UNREFERENCED(ppOutMessages); STAR_UNREFERENCED(nMaxMessages);
    return 0;
}

STAR_EXPORT void SteamAPI_ISteamNetworkingSockets_RunCallbacks(ISteamNetworkingSockets* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingSockets_SendMessageToConnection(ISteamNetworkingSockets* self, HSteamNetConnection hConn, const void* pData, uint32 cbData, int nSendFlags, int64* pOutMessageNumber)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hConn); STAR_UNREFERENCED(pData); STAR_UNREFERENCED(cbData); STAR_UNREFERENCED(nSendFlags); STAR_UNREFERENCED(pOutMessageNumber);
    return k_EResultFail;
}

STAR_EXPORT bool SteamAPI_ISteamNetworkingSockets_SetConnectionPollGroup(ISteamNetworkingSockets* self, HSteamNetConnection hConn, HSteamNetPollGroup hPollGroup)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hConn); STAR_UNREFERENCED(hPollGroup);
    return true;
}

STAR_EXPORT void SteamAPI_ISteamNetworkingUtils_InitRelayNetworkAccess(ISteamNetworkingUtils* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamNetworkingUtils_SteamNetworkingIPAddr_ToString(ISteamNetworkingUtils* self, const SteamNetworkingIPAddr* addr, char* buf, uint32 cbBuf, bool bWithPort)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(addr); STAR_UNREFERENCED(bWithPort);
    if (buf && cbBuf > 0) {
        strncpy_s(buf, cbBuf, "127.0.0.1", _TRUNCATE);
    }
}

STAR_EXPORT void SteamAPI_ISteamNetworkingUtils_SteamNetworkingIdentity_ToString(ISteamNetworkingUtils* self, const SteamNetworkingIdentity* identity, char* buf, uint32 cbBuf)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(identity);
    if (buf && cbBuf > 0) {
        strncpy_s(buf, cbBuf, "steamid", _TRUNCATE);
    }
}

STAR_EXPORT bool SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete(ISteamRemoteStorage* self, SteamAPICall_t hCall, void* pvBuffer, uint32 cubToRead)
{
    return self ? self->FileReadAsyncComplete(hCall, pvBuffer, cubToRead) : false;
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_FileWriteAsync(ISteamRemoteStorage* self, const char* pchFile, const void* pvData, uint32 cubData)
{
    return self ? self->FileWriteAsync(pchFile, pvData, cubData) : k_uAPICallInvalid;
}

STAR_EXPORT int32 SteamAPI_ISteamRemoteStorage_GetFileSize(ISteamRemoteStorage* self, const char* pchFile)
{
    return self ? self->GetFileSize(pchFile) : 0;
}

STAR_EXPORT const char* SteamAPI_ISteamUserStats_GetAchievementName(ISteamUserStats* self, uint32 iAchievement)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(iAchievement);
    return "";
}

STAR_EXPORT uint32 SteamAPI_ISteamUserStats_GetNumAchievements(ISteamUserStats* self)
{
    STAR_UNREFERENCED(self);
    return 0;
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_IndicateAchievementProgress(ISteamUserStats* self, const char* pchName, uint32 nCurProgress, uint32 nMaxProgress)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pchName); STAR_UNREFERENCED(nCurProgress); STAR_UNREFERENCED(nMaxProgress);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUserStats_ResetAllStats(ISteamUserStats* self, bool bAchievementsToo)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(bAchievementsToo);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUtils_IsSteamInBigPictureMode(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return false;
}

STAR_EXPORT bool SteamAPI_ISteamUtils_IsSteamRunningOnSteamDeck(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return false;
}

STAR_EXPORT void SteamAPI_ISteamUtils_SetWarningMessageHook(ISteamUtils* self, SteamAPIWarningMessageHook_t pFunction)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pFunction);
}

STAR_EXPORT bool SteamAPI_ISteamUtils_ShowFloatingGamepadTextInput(ISteamUtils* self, EFloatingGamepadTextInputMode eKeyboardMode, int nTextFieldXPosition, int nTextFieldYPosition, int nTextFieldWidth, int nTextFieldHeight)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(eKeyboardMode); STAR_UNREFERENCED(nTextFieldXPosition); STAR_UNREFERENCED(nTextFieldYPosition); STAR_UNREFERENCED(nTextFieldWidth); STAR_UNREFERENCED(nTextFieldHeight);
    return false;
}

STAR_EXPORT HSteamPipe GetHSteamPipe()
{
    return 1;
}

STAR_EXPORT HSteamUser GetHSteamUser()
{
    return 1;
}

STAR_EXPORT void SteamAPI_SetBreakpadAppID(uint32 unAppID)
{
    STAR_UNREFERENCED(unAppID);
}

STAR_EXPORT void SteamAPI_SetTryCatchCallbacks(bool bTryCatchCallbacks)
{
    STAR_UNREFERENCED(bTryCatchCallbacks);
}

STAR_EXPORT void SteamAPI_UseBreakpadCrashHandler()
{
}

STAR_EXPORT ESteamAPIInitResult SteamInternal_GameServer_Init_V2(uint32 unIP, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char* pchVersionString, const char* pszInternalCheckInterfaceVersions, char* pOutErrMsg)
{
    STAR_UNREFERENCED(unIP); STAR_UNREFERENCED(usGamePort); STAR_UNREFERENCED(usQueryPort); STAR_UNREFERENCED(eServerMode); STAR_UNREFERENCED(pchVersionString); STAR_UNREFERENCED(pszInternalCheckInterfaceVersions);
    if (pOutErrMsg) pOutErrMsg[0] = '\0';
    return k_ESteamAPIInitResult_OK;
}

STAR_EXPORT ISteamUser* SteamAPI_SteamUser_v020() { return reinterpret_cast<ISteamUser*>(static_cast<ISteamUser020*>(&StarSteamUser::get())); }
STAR_EXPORT ISteamUser* SteamAPI_SteamUser_v021() { return reinterpret_cast<ISteamUser*>(static_cast<ISteamUser021*>(&StarSteamUser::get())); }
STAR_EXPORT ISteamUser* SteamAPI_SteamUser_v022() { return reinterpret_cast<ISteamUser*>(static_cast<ISteamUser022*>(&StarSteamUser::get())); }
STAR_EXPORT ISteamUser* SteamAPI_SteamUser_v023() { return static_cast<ISteamUser*>(&StarSteamUser::get()); }

STAR_EXPORT ISteamFriends* SteamAPI_SteamFriends_v017() { return reinterpret_cast<ISteamFriends*>(static_cast<ISteamFriends017*>(&StarSteamFriends::get())); }
STAR_EXPORT ISteamFriends* SteamAPI_SteamFriends_v018() { return static_cast<ISteamFriends*>(&StarSteamFriends::get()); }

STAR_EXPORT ISteamUtils* SteamAPI_SteamUtils_v009() { return reinterpret_cast<ISteamUtils*>(static_cast<ISteamUtils009*>(&StarSteamUtils::get())); }
STAR_EXPORT ISteamUtils* SteamAPI_SteamUtils_v010() { return static_cast<ISteamUtils*>(&StarSteamUtils::get()); }
STAR_EXPORT ISteamUtils* SteamAPI_SteamGameServerUtils_v009() { return reinterpret_cast<ISteamUtils*>(static_cast<ISteamUtils009*>(&StarSteamUtils::get())); }
STAR_EXPORT ISteamUtils* SteamAPI_SteamGameServerUtils_v010() { return static_cast<ISteamUtils*>(&StarSteamUtils::get()); }

STAR_EXPORT ISteamMatchmaking* SteamAPI_SteamMatchmaking_v009() { return &StarSteamMatchmaking::get(); }
STAR_EXPORT ISteamMatchmakingServers* SteamAPI_SteamMatchmakingServers_v002() { return &StarSteamMatchmakingServers::get(); }

STAR_EXPORT ISteamUserStats* SteamAPI_SteamUserStats_v011() { return reinterpret_cast<ISteamUserStats*>(static_cast<ISteamUserStats011*>(&StarSteamUserStats::get())); }
STAR_EXPORT ISteamUserStats* SteamAPI_SteamUserStats_v012() { return reinterpret_cast<ISteamUserStats*>(static_cast<ISteamUserStats012*>(&StarSteamUserStats::get())); }
STAR_EXPORT ISteamUserStats* SteamAPI_SteamUserStats_v013() { return static_cast<ISteamUserStats*>(&StarSteamUserStats::get()); }

STAR_EXPORT ISteamApps* SteamAPI_SteamApps_v008() { return reinterpret_cast<ISteamApps*>(static_cast<ISteamApps008*>(&StarSteamApps::get())); }
STAR_EXPORT ISteamApps* SteamAPI_SteamApps_v009() { return static_cast<ISteamApps*>(&StarSteamApps::get()); }
STAR_EXPORT ISteamApps* SteamAPI_SteamGameServerApps_v008() { return reinterpret_cast<ISteamApps*>(static_cast<ISteamApps008*>(&StarSteamApps::get())); }
STAR_EXPORT ISteamApps* SteamAPI_SteamGameServerApps_v009() { return static_cast<ISteamApps*>(&StarSteamApps::get()); }

STAR_EXPORT ISteamNetworking* SteamAPI_SteamNetworking_v006() { return &StarSteamNetworking::get(); }
STAR_EXPORT ISteamNetworking* SteamAPI_SteamGameServerNetworking_v006() { return &StarSteamNetworking::get(); }

STAR_EXPORT ISteamRemoteStorage* SteamAPI_SteamRemoteStorage_v014() { return &StarSteamRemoteStorage::get(); }
STAR_EXPORT ISteamRemoteStorage* SteamAPI_SteamRemoteStorage_v016() { return &StarSteamRemoteStorage::get(); }

STAR_EXPORT ISteamScreenshots* SteamAPI_SteamScreenshots_v003() { return &StarSteamScreenshots::get(); }

STAR_EXPORT ISteamHTTP* SteamAPI_SteamHTTP_v003() { return &StarSteamHTTP::get(); }
STAR_EXPORT ISteamHTTP* SteamAPI_SteamGameServerHTTP_v003() { return &StarSteamHTTP::get(); }

STAR_EXPORT ISteamInput* SteamAPI_SteamInput_v001() { return &StarSteamInput::get(); }
STAR_EXPORT ISteamInput* SteamAPI_SteamInput_v002() { return &StarSteamInput::get(); }
STAR_EXPORT ISteamInput* SteamAPI_SteamInput_v005() { return &StarSteamInput::get(); }
STAR_EXPORT ISteamInput* SteamAPI_SteamInput_v006() { return &StarSteamInput::get(); }

STAR_EXPORT ISteamController* SteamAPI_SteamController_v007() { return reinterpret_cast<ISteamController*>(&StarSteamController::get()); }
STAR_EXPORT ISteamController* SteamAPI_SteamController_v008() { return reinterpret_cast<ISteamController*>(&StarSteamController::get()); }

STAR_EXPORT ISteamUGC* SteamAPI_SteamUGC_v014() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }
STAR_EXPORT ISteamUGC* SteamAPI_SteamUGC_v015() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }
STAR_EXPORT ISteamUGC* SteamAPI_SteamUGC_v016() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }
STAR_EXPORT ISteamUGC* SteamAPI_SteamUGC_v017() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }
STAR_EXPORT ISteamUGC* SteamAPI_SteamUGC_v018() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }
STAR_EXPORT ISteamUGC* SteamAPI_SteamUGC_v019() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }
STAR_EXPORT ISteamUGC* SteamAPI_SteamUGC_v020() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }
STAR_EXPORT ISteamUGC* SteamAPI_SteamUGC_v021() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }
STAR_EXPORT ISteamUGC* SteamAPI_SteamGameServerUGC_v014() { return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get()); }

STAR_EXPORT ISteamAppList* SteamAPI_SteamAppList_v001() { return &StarSteamAppList::get(); }

STAR_EXPORT ISteamHTMLSurface* SteamAPI_SteamHTMLSurface_v005() { return &StarSteamHTMLSurface::get(); }

STAR_EXPORT ISteamInventory* SteamAPI_SteamInventory_v003() { return &StarSteamInventory::get(); }
STAR_EXPORT ISteamInventory* SteamAPI_SteamGameServerInventory_v003() { return &StarSteamInventory::get(); }

STAR_EXPORT ISteamVideo* SteamAPI_SteamVideo_v001() { return &StarSteamVideo::get(); }
STAR_EXPORT ISteamVideo* SteamAPI_SteamVideo_v002() { return &StarSteamVideo::get(); }
STAR_EXPORT ISteamVideo* SteamAPI_SteamVideo_v007() { return &StarSteamVideo::get(); }

STAR_EXPORT ISteamMusic* SteamAPI_SteamMusic_v001() { return &StarSteamMusic::get(); }
STAR_EXPORT ISteamMusicRemote* SteamAPI_SteamMusicRemote_v001() { return &StarSteamMusicRemote::get(); }

STAR_EXPORT ISteamNetworkingSockets* SteamAPI_SteamNetworkingSockets_v008()
{
    return reinterpret_cast<ISteamNetworkingSockets*>(&StarSteamNetworkingSockets::get());
}

STAR_EXPORT ISteamNetworkingSockets* SteamAPI_SteamGameServerNetworkingSockets_v008()
{
    return reinterpret_cast<ISteamNetworkingSockets*>(&StarSteamNetworkingSockets::get());
}

STAR_EXPORT ISteamNetworkingUtils* SteamAPI_SteamNetworkingUtils_v003()
{
    return reinterpret_cast<ISteamNetworkingUtils*>(&StarSteamNetworkingUtils::get());
}

STAR_EXPORT ISteamParentalSettings* SteamAPI_SteamParentalSettings_v001()
{
    return &StarSteamParentalSettings::get();
}

STAR_EXPORT ISteamParties* SteamAPI_SteamParties_v002()
{
    return &StarSteamParties::get();
}

STAR_EXPORT ISteamRemotePlay001* SteamAPI_SteamRemotePlay_v001()
{
    return &StarSteamRemotePlay::get();
}

STAR_EXPORT void SteamAPI_SteamNetworkingIPAddr_Clear(SteamNetworkingIPAddr* self)
{
    if (self) self->Clear();
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIPAddr_IsIPv6AllZeros(const SteamNetworkingIPAddr* self)
{
    return self ? self->IsIPv6AllZeros() : true;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIPAddr_SetIPv6(SteamNetworkingIPAddr* self, const uint8* ipv6, uint16 nPort)
{
    if (self) self->SetIPv6(ipv6, nPort);
}

STAR_EXPORT void SteamAPI_SteamNetworkingIPAddr_SetIPv4(SteamNetworkingIPAddr* self, uint32 nIP, uint16 nPort)
{
    if (self) self->SetIPv4(nIP, nPort);
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIPAddr_IsIPv4(const SteamNetworkingIPAddr* self)
{
    return self ? self->IsIPv4() : false;
}

STAR_EXPORT uint32 SteamAPI_SteamNetworkingIPAddr_GetIPv4(const SteamNetworkingIPAddr* self)
{
    return self ? self->GetIPv4() : 0;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIPAddr_SetIPv6LocalHost(SteamNetworkingIPAddr* self, uint16 nPort)
{
    if (self) self->SetIPv6LocalHost(nPort);
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIPAddr_IsLocalHost(const SteamNetworkingIPAddr* self)
{
    return self ? self->IsLocalHost() : false;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIPAddr_ToString(const SteamNetworkingIPAddr* self, char* buf, uint32 cbBuf, bool bWithPort)
{
    if (!self || !buf || cbBuf == 0) return;
    if (self->IsIPv4()) {
        uint32 ip = self->GetIPv4();
        if (bWithPort) {
            snprintf(buf, cbBuf, "%u.%u.%u.%u:%d", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF, self->m_port);
        } else {
            snprintf(buf, cbBuf, "%u.%u.%u.%u", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
        }
    } else {
        if (self->IsLocalHost()) {
            if (bWithPort) {
                snprintf(buf, cbBuf, "[::1]:%d", self->m_port);
            } else {
                strncpy_s(buf, cbBuf, "::1", _TRUNCATE);
            }
        } else {
            strncpy_s(buf, cbBuf, "::", _TRUNCATE);
        }
    }
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIPAddr_ParseString(SteamNetworkingIPAddr* self, const char* pszStr)
{
    if (!self || !pszStr) return false;
    self->Clear();
    unsigned int ip[4];
    unsigned int port = 0;
    int items = sscanf_s(pszStr, "%u.%u.%u.%u:%u", &ip[0], &ip[1], &ip[2], &ip[3], &port);
    if (items >= 4) {
        uint32 nIP = (ip[0] << 24) | (ip[1] << 16) | (ip[2] << 8) | ip[3];
        self->SetIPv4(nIP, (uint16)port);
        return true;
    }
    if (strstr(pszStr, "::1") || strstr(pszStr, "localhost") || strstr(pszStr, "127.0.0.1")) {
        self->SetIPv6LocalHost();
        return true;
    }
    return false;
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIPAddr_IsEqualTo(const SteamNetworkingIPAddr* self, const SteamNetworkingIPAddr* x)
{
    return (self && x) ? (*self == *x) : false;
}

STAR_EXPORT ESteamNetworkingFakeIPType SteamAPI_SteamNetworkingIPAddr_GetFakeIPType(const SteamNetworkingIPAddr* self)
{
    return self ? self->GetFakeIPType() : k_ESteamNetworkingFakeIPType_NotFake;
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIPAddr_IsFakeIP(const SteamNetworkingIPAddr* self)
{
    return self ? self->IsFakeIP() : false;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_Clear(SteamNetworkingIdentity* self)
{
    if (self) self->Clear();
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIdentity_IsInvalid(const SteamNetworkingIdentity* self)
{
    return self ? self->IsInvalid() : true;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_SetSteamID(SteamNetworkingIdentity* self, uint64 steamID)
{
    if (self) self->SetSteamID(CSteamID(steamID));
}

STAR_EXPORT uint64 SteamAPI_SteamNetworkingIdentity_GetSteamID(const SteamNetworkingIdentity* self)
{
    return self ? self->GetSteamID().ConvertToUint64() : 0;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_SetSteamID64(SteamNetworkingIdentity* self, uint64 steamID)
{
    if (self) self->SetSteamID64(steamID);
}

STAR_EXPORT uint64 SteamAPI_SteamNetworkingIdentity_GetSteamID64(const SteamNetworkingIdentity* self)
{
    return self ? self->GetSteamID64() : 0;
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIdentity_SetXboxPairwiseID(SteamNetworkingIdentity* self, const char* pszString)
{
    return self ? self->SetXboxPairwiseID(pszString) : false;
}

STAR_EXPORT const char* SteamAPI_SteamNetworkingIdentity_GetXboxPairwiseID(const SteamNetworkingIdentity* self)
{
    return self ? self->GetXboxPairwiseID() : nullptr;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_SetPSNID(SteamNetworkingIdentity* self, uint64 id)
{
    if (self) self->SetPSNID(id);
}

STAR_EXPORT uint64 SteamAPI_SteamNetworkingIdentity_GetPSNID(const SteamNetworkingIdentity* self)
{
    return self ? self->GetPSNID() : 0;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_SetStadiaID(SteamNetworkingIdentity* self, uint64 id)
{
    if (self) self->SetStadiaID(id);
}

STAR_EXPORT uint64 SteamAPI_SteamNetworkingIdentity_GetStadiaID(const SteamNetworkingIdentity* self)
{
    return self ? self->GetStadiaID() : 0;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_SetIPAddr(SteamNetworkingIdentity* self, const SteamNetworkingIPAddr* addr)
{
    if (self && addr) self->SetIPAddr(*addr);
}

STAR_EXPORT const SteamNetworkingIPAddr* SteamAPI_SteamNetworkingIdentity_GetIPAddr(const SteamNetworkingIdentity* self)
{
    return self ? self->GetIPAddr() : nullptr;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_SetIPv4Addr(SteamNetworkingIdentity* self, uint32 nIPv4, uint16 nPort)
{
    if (self) self->SetIPv4Addr(nIPv4, nPort);
}

STAR_EXPORT uint32 SteamAPI_SteamNetworkingIdentity_GetIPv4(const SteamNetworkingIdentity* self)
{
    return self ? self->GetIPv4() : 0;
}

STAR_EXPORT ESteamNetworkingFakeIPType SteamAPI_SteamNetworkingIdentity_GetFakeIPType(const SteamNetworkingIdentity* self)
{
    return self ? self->GetFakeIPType() : k_ESteamNetworkingFakeIPType_NotFake;
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIdentity_IsFakeIP(const SteamNetworkingIdentity* self)
{
    return self ? self->IsFakeIP() : false;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_SetLocalHost(SteamNetworkingIdentity* self)
{
    if (self) self->SetLocalHost();
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIdentity_IsLocalHost(const SteamNetworkingIdentity* self)
{
    return self ? self->IsLocalHost() : false;
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIdentity_SetGenericString(SteamNetworkingIdentity* self, const char* pszString)
{
    return self ? self->SetGenericString(pszString) : false;
}

STAR_EXPORT const char* SteamAPI_SteamNetworkingIdentity_GetGenericString(const SteamNetworkingIdentity* self)
{
    return self ? self->GetGenericString() : nullptr;
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIdentity_SetGenericBytes(SteamNetworkingIdentity* self, const void* data, uint32 cbLen)
{
    return self ? self->SetGenericBytes(data, cbLen) : false;
}

STAR_EXPORT const uint8* SteamAPI_SteamNetworkingIdentity_GetGenericBytes(const SteamNetworkingIdentity* self, int* cbLen)
{
    return (self && cbLen) ? self->GetGenericBytes(*cbLen) : nullptr;
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIdentity_IsEqualTo(const SteamNetworkingIdentity* self, const SteamNetworkingIdentity* x)
{
    return (self && x) ? (*self == *x) : false;
}

STAR_EXPORT void SteamAPI_SteamNetworkingIdentity_ToString(const SteamNetworkingIdentity* self, char* buf, uint32 cbBuf)
{
    if (!self || !buf || cbBuf == 0) return;
    if (self->m_eType == k_ESteamNetworkingIdentityType_SteamID) {
        snprintf(buf, cbBuf, "steamid:%llu", self->GetSteamID64());
    } else if (self->m_eType == k_ESteamNetworkingIdentityType_IPAddress) {
        const SteamNetworkingIPAddr* ip = self->GetIPAddr();
        if (ip) {
            char ip_str[64];
            SteamAPI_SteamNetworkingIPAddr_ToString(ip, ip_str, sizeof(ip_str), true);
            snprintf(buf, cbBuf, "ip:%s", ip_str);
        } else {
            strncpy_s(buf, cbBuf, "ip:::", _TRUNCATE);
        }
    } else if (self->m_eType == k_ESteamNetworkingIdentityType_GenericString) {
        snprintf(buf, cbBuf, "str:%s", self->GetGenericString());
    } else {
        strncpy_s(buf, cbBuf, "anonymous", _TRUNCATE);
    }
}

STAR_EXPORT bool SteamAPI_SteamNetworkingIdentity_ParseString(SteamNetworkingIdentity* self, const char* pszStr)
{
    if (!self || !pszStr) return false;
    self->Clear();
    if (strncmp(pszStr, "steamid:", 8) == 0) {
        uint64 steamID = 0;
        if (sscanf_s(pszStr + 8, "%llu", &steamID) == 1) {
            self->SetSteamID64(steamID);
            return true;
        }
    } else if (strncmp(pszStr, "ip:", 3) == 0) {
        SteamNetworkingIPAddr addr;
        if (SteamAPI_SteamNetworkingIPAddr_ParseString(&addr, pszStr + 3)) {
            self->SetIPAddr(addr);
            return true;
        }
    } else if (strncmp(pszStr, "str:", 4) == 0) {
        return self->SetGenericString(pszStr + 4);
    }
    return false;
}


STAR_EXPORT void SteamAPI_SteamNetworkingMessage_t_Release(SteamNetworkingMessage_t* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamFriends_ActivateGameOverlay(ISteamFriends* self, const char* pchDialog)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pchDialog);
}

STAR_EXPORT void SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog(ISteamFriends* self, uint64 steamIDLobby)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(steamIDLobby);
}

STAR_EXPORT void SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage(ISteamFriends* self, const char* pchURL, int eMode)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pchURL); STAR_UNREFERENCED(eMode);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_GoBack(ISteamHTMLSurface* self, uint32 hBrowser)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hBrowser);
}

STAR_EXPORT bool SteamAPI_ISteamHTMLSurface_Init(ISteamHTMLSurface* self)
{
    STAR_UNREFERENCED(self);
    return true;
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_KeyDown(ISteamHTMLSurface* self, uint32 hBrowser, uint32 nNativeKeyCode, int eHTMLKeyModifiers, bool bIsSystemKey)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hBrowser); STAR_UNREFERENCED(nNativeKeyCode); STAR_UNREFERENCED(eHTMLKeyModifiers); STAR_UNREFERENCED(bIsSystemKey);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_KeyUp(ISteamHTMLSurface* self, uint32 hBrowser, uint32 nNativeKeyCode, int eHTMLKeyModifiers)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hBrowser); STAR_UNREFERENCED(nNativeKeyCode); STAR_UNREFERENCED(eHTMLKeyModifiers);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_Reload(ISteamHTMLSurface* self, uint32 hBrowser)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hBrowser);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_SetSize(ISteamHTMLSurface* self, uint32 hBrowser, uint32 cx, uint32 cy)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hBrowser); STAR_UNREFERENCED(cx); STAR_UNREFERENCED(cy);
}

STAR_EXPORT bool SteamAPI_ISteamHTMLSurface_Shutdown(ISteamHTMLSurface* self)
{
    STAR_UNREFERENCED(self);
    return true;
}

STAR_EXPORT const char* SteamAPI_ISteamInput_GetGlyphForActionOrigin_Legacy(ISteamInput* self, int eActionOrigin)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(eActionOrigin);
    return "";
}

STAR_EXPORT bool SteamAPI_ISteamInput_Init(ISteamInput* self, bool bExplicitRunFrame)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(bExplicitRunFrame);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamInput_Shutdown(ISteamInput* self)
{
    STAR_UNREFERENCED(self);
    return true;
}

STAR_EXPORT void SteamAPI_ISteamMusic_Pause(ISteamMusic* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamMusic_Play(ISteamMusic* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT uint32 SteamAPI_ISteamNetworking_CreateListenSocket(ISteamNetworking* self, int nVirtualP2PPort, SteamIPAddress_t nIP, uint16 nPort, bool bAllowUseOfPacketRelay)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nVirtualP2PPort); STAR_UNREFERENCED(nIP); STAR_UNREFERENCED(nPort); STAR_UNREFERENCED(bAllowUseOfPacketRelay);
    return 0;
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_FileReadAsync(ISteamRemoteStorage* self, const char* pchFile, uint32 nOffset, uint32 cubToRead)
{
    return self ? self->FileReadAsync(pchFile, nOffset, cubToRead) : k_uAPICallInvalid;
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_SubscribePublishedFile(ISteamRemoteStorage* self, uint64 unPublishedFileId)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(unPublishedFileId);
    return 0;
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_CreateItem(ISteamUGC* self, uint32 nConsumerAppId, int eFileType)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nConsumerAppId); STAR_UNREFERENCED(eFileType);
    return 0;
}

STAR_EXPORT uint64 SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest(ISteamUGC* self, uint64* pvecPublishedFileID, uint32 unNumPublishedFileIDs)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pvecPublishedFileID); STAR_UNREFERENCED(unNumPublishedFileIDs);
    return 0;
}

STAR_EXPORT uint64 SteamAPI_ISteamUGC_CreateQueryUserUGCRequest(ISteamUGC* self, uint32 unAccountID, int eUserUGCList, int eUserUGCListSortOrder, int eMatchingUGCType, uint32 nCreatorAppID, uint32 nConsumerAppID, uint32 unPage)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(unAccountID); STAR_UNREFERENCED(eUserUGCList); STAR_UNREFERENCED(eUserUGCListSortOrder); STAR_UNREFERENCED(eMatchingUGCType); STAR_UNREFERENCED(nCreatorAppID); STAR_UNREFERENCED(nConsumerAppID); STAR_UNREFERENCED(unPage);
    return 0;
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_DeleteItem(ISteamUGC* self, uint64 nPublishedFileID)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nPublishedFileID);
    return 0;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_DownloadItem(ISteamUGC* self, uint64 nPublishedFileID, bool bHighPriority)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nPublishedFileID); STAR_UNREFERENCED(bHighPriority);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_GetItemInstallInfo(ISteamUGC* self, uint64 nPublishedFileID, uint64* punSizeOnDisk, char* pchFolder, uint32 cchFolderSize, uint32* punTimeStamp)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nPublishedFileID);
    if (punSizeOnDisk) *punSizeOnDisk = 0;
    if (pchFolder && cchFolderSize > 0) pchFolder[0] = '\0';
    if (punTimeStamp) *punTimeStamp = 0;
    return false;
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetItemState(ISteamUGC* self, uint64 nPublishedFileID)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nPublishedFileID);
    return 0;
}

STAR_EXPORT int SteamAPI_ISteamUGC_GetItemUpdateProgress(ISteamUGC* self, uint64 handle, uint64* punBytesProcessed, uint64* punBytesTotal)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle);
    if (punBytesProcessed) *punBytesProcessed = 0;
    if (punBytesTotal) *punBytesTotal = 0;
    return 0;
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetNumSubscribedItems(ISteamUGC* self)
{
    STAR_UNREFERENCED(self);
    return 0;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_GetQueryUGCChildren(ISteamUGC* self, uint64 handle, uint32 index, uint64* pvecPublishedFileID, uint32 cMaxPublishedFileIDs)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(index); STAR_UNREFERENCED(pvecPublishedFileID); STAR_UNREFERENCED(cMaxPublishedFileIDs);
    return false;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_GetQueryUGCResult(ISteamUGC* self, uint64 handle, uint32 index, void* pDetails)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(index); STAR_UNREFERENCED(pDetails);
    return false;
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetSubscribedItems(ISteamUGC* self, uint64* pvecPublishedFileID, uint32 cMaxPublishedFileIDs)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pvecPublishedFileID); STAR_UNREFERENCED(cMaxPublishedFileIDs);
    return 0;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_ReleaseQueryUGCRequest(ISteamUGC* self, uint64 handle)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle);
    return true;
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_SendQueryUGCRequest(ISteamUGC* self, uint64 handle)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle);
    return 0;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetAllowCachedResponse(ISteamUGC* self, uint64 handle, uint32 unMaxAgeSeconds)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(unMaxAgeSeconds);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetItemContent(ISteamUGC* self, uint64 handle, const char* pszContentFolder)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(pszContentFolder);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetItemDescription(ISteamUGC* self, uint64 handle, const char* pchDescription)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(pchDescription);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetItemPreview(ISteamUGC* self, uint64 handle, const char* pszPreviewFile)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(pszPreviewFile);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetItemTags(ISteamUGC* self, uint64 handle, const void* pTags)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(pTags);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetItemTitle(ISteamUGC* self, uint64 handle, const char* pchTitle)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(pchTitle);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetItemVisibility(ISteamUGC* self, uint64 handle, int eVisibility)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(eVisibility);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetReturnChildren(ISteamUGC* self, uint64 handle, bool bReturnChildren)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(bReturnChildren);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetReturnLongDescription(ISteamUGC* self, uint64 handle, bool bReturnLongDescription)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(bReturnLongDescription);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamUGC_SetSearchText(ISteamUGC* self, uint64 handle, const char* pSearchText)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(pSearchText);
    return true;
}

STAR_EXPORT uint64 SteamAPI_ISteamUGC_StartItemUpdate(ISteamUGC* self, uint32 nConsumerAppId, uint64 nPublishedFileID)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nConsumerAppId); STAR_UNREFERENCED(nPublishedFileID);
    return 0;
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_SubmitItemUpdate(ISteamUGC* self, uint64 handle, const char* pchChangeNote)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(handle); STAR_UNREFERENCED(pchChangeNote);
    return 0;
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_SubscribeItem(ISteamUGC* self, uint64 nPublishedFileID)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(nPublishedFileID);
    return 0;
}

STAR_EXPORT int SteamAPI_ISteamUtils_GetAPICallFailureReason(ISteamUtils* self, SteamAPICall_t hSteamAPICall)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(hSteamAPICall);
    return 0;
}

STAR_EXPORT bool SteamAPI_ISteamUtils_GetAPICallResult(ISteamUtils* self, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed)
{
    STAR_UNREFERENCED(self);
    return consume_pending_result(hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed, "ISteamUtils_GetAPICallResult");
}

STAR_EXPORT bool SteamAPI_ISteamUtils_IsAPICallCompleted(ISteamUtils* self, SteamAPICall_t hSteamAPICall, bool* pbFailed)
{
    STAR_UNREFERENCED(self);
    if (!pbFailed) return false;

    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    auto it = g_pending_results.find(hSteamAPICall);
    if (it == g_pending_results.end()) {
        *pbFailed = false;
        return false;
    }
    *pbFailed = it->second.io_failure;
    return true;
}

STAR_EXPORT const char* SteamAPI_ISteamFriends_GetFriendPersonaName(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(steamIDFriend);
    return "";
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetFriendMessage(ISteamFriends* self, uint64_steamid steamIDFriend, int iMessageID, void* pvData, int cubData, int* peChatEntryType)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(iMessageID);
    if (pvData && cubData > 0) ((char*)pvData)[0] = 0;
    if (peChatEntryType) *peChatEntryType = 0;
    return 0;
}

STAR_EXPORT uint32 SteamAPI_ISteamUser_GetVoiceOptimalSampleRate(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return 48000;
}

STAR_EXPORT int SteamAPI_ISteamMatchmaking_GetLobbyChatEntry(ISteamMatchmaking* self, uint64_steamid steamIDLobby, int iChatID, uint64_steamid* pSteamIDUser, void* pvData, int cubData, int* peChatEntryType)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(steamIDLobby); STAR_UNREFERENCED(iChatID);
    if (pSteamIDUser) *pSteamIDUser = 0;
    if (pvData && cubData > 0) ((char*)pvData)[0] = 0;
    if (peChatEntryType) *peChatEntryType = 0;
    return 0;
}

STAR_EXPORT void SteamAPI_ISteamInventory_DestroyResult(ISteamInventory* self, SteamInventoryResult_t resultHandle)
{
    if (self) self->DestroyResult(resultHandle);
}

STAR_EXPORT bool SteamAPI_ISteamInventory_GetItemDefinitionIDs(ISteamInventory* self, SteamItemDef_t* pItemDefIDs, uint32* punItemDefIDsArraySize)
{
    if (punItemDefIDsArraySize) *punItemDefIDsArraySize = 0;
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(pItemDefIDs);
    return true;
}

STAR_EXPORT bool SteamAPI_ISteamInventory_GetResultItemProperty(ISteamInventory* self, SteamInventoryResult_t resultHandle, uint32 unItemIndex, const char* pchPropertyName, char* pchValueBuffer, uint32* punValueBufferSizeOut)
{
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(resultHandle); STAR_UNREFERENCED(unItemIndex); STAR_UNREFERENCED(pchPropertyName);
    if (pchValueBuffer && punValueBufferSizeOut && *punValueBufferSizeOut > 0) pchValueBuffer[0] = 0;
    if (punValueBufferSizeOut) *punValueBufferSizeOut = 0;
    return false;
}

STAR_EXPORT bool SteamAPI_ISteamInventory_GetResultItems(ISteamInventory* self, SteamInventoryResult_t resultHandle, SteamItemDetails_t* pOutItemsArray, uint32* punItemsArraySize)
{
    if (punItemsArraySize) *punItemsArraySize = 0;
    STAR_UNREFERENCED(self); STAR_UNREFERENCED(resultHandle); STAR_UNREFERENCED(pOutItemsArray);
    return false;
}



