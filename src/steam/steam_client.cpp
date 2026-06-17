#include "steam/steam_client.h"
#include "core/callbacks.h"
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
#include "steam/isteamclient.h"

StarSteamClient& StarSteamClient::get()
{
    static StarSteamClient instance;
    return instance;
}

static char g_dummy_interface[16] = { 0 };

static bool ver_is(const char* ver, const char* code)
{
    return ver && strstr(ver, code) != nullptr;
}

#define STAR_VER(IFACE, code, obj) \
    reinterpret_cast<IFACE*>(static_cast<IFACE##code*>(obj))

void* StarSteamClient::GetClientInterface(const char* ver)
{
    StarSteamClient* o = this;
    if (ver_is(ver, "012")) return STAR_VER(ISteamClient, 012, o);
    if (ver_is(ver, "013")) return STAR_VER(ISteamClient, 013, o);
    if (ver_is(ver, "014")) return STAR_VER(ISteamClient, 014, o);
    if (ver_is(ver, "015")) return STAR_VER(ISteamClient, 015, o);
    if (ver_is(ver, "016")) return STAR_VER(ISteamClient, 016, o);
    if (ver_is(ver, "017")) return STAR_VER(ISteamClient, 017, o);
    if (ver_is(ver, "018")) return STAR_VER(ISteamClient, 018, o);
    if (ver_is(ver, "019")) return STAR_VER(ISteamClient, 019, o);
    if (ver_is(ver, "020")) return STAR_VER(ISteamClient, 020, o);
    if (ver_is(ver, "021")) return STAR_VER(ISteamClient, 021, o);
    if (ver_is(ver, "022")) return STAR_VER(ISteamClient, 022, o);
    if (ver_is(ver, "001") || ver_is(ver, "002") || ver_is(ver, "003") || ver_is(ver, "004") ||
        ver_is(ver, "005") || ver_is(ver, "006") || ver_is(ver, "007") || ver_is(ver, "008") ||
        ver_is(ver, "009") || ver_is(ver, "010") || ver_is(ver, "011")) {
        STAR_LOG("GetClientInterface: unsupported legacy version '%s'", ver ? ver : "(null)");
        return nullptr;
    }
    return static_cast<ISteamClient*>(o);
}

HSteamPipe StarSteamClient::CreateSteamPipe() { return 1; }
bool StarSteamClient::BReleaseSteamPipe(HSteamPipe hSteamPipe) { STAR_UNREFERENCED(hSteamPipe); return true; }
HSteamUser StarSteamClient::ConnectToGlobalUser(HSteamPipe hSteamPipe) { STAR_UNREFERENCED(hSteamPipe); return 1; }
HSteamUser StarSteamClient::CreateLocalUser(HSteamPipe* phSteamPipe, EAccountType eAccountType) { STAR_UNREFERENCED(eAccountType); if(phSteamPipe) *phSteamPipe=1; return 1; }
void StarSteamClient::ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser) { STAR_UNREFERENCED(hSteamPipe); STAR_UNREFERENCED(hUser); }

ISteamUser* StarSteamClient::GetISteamUser(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p);
    StarSteamUser* o = &StarSteamUser::get();

    if (ver_is(ver, "001") || ver_is(ver, "002") || ver_is(ver, "004") ||
        ver_is(ver, "005") || ver_is(ver, "006") || ver_is(ver, "007")) {
        return nullptr;
    }
    if (ver_is(ver, "008")) return STAR_VER(ISteamUser, 008, o);
    if (ver_is(ver, "009")) return STAR_VER(ISteamUser, 009, o);
    if (ver_is(ver, "010")) return STAR_VER(ISteamUser, 010, o);
    if (ver_is(ver, "011")) return STAR_VER(ISteamUser, 011, o);
    if (ver_is(ver, "012")) return STAR_VER(ISteamUser, 012, o);
    if (ver_is(ver, "013")) return STAR_VER(ISteamUser, 013, o);
    if (ver_is(ver, "014")) return STAR_VER(ISteamUser, 014, o);
    if (ver_is(ver, "015")) return STAR_VER(ISteamUser, 015, o);
    if (ver_is(ver, "016")) return STAR_VER(ISteamUser, 016, o);
    if (ver_is(ver, "017")) return STAR_VER(ISteamUser, 017, o);
    if (ver_is(ver, "018")) return STAR_VER(ISteamUser, 018, o);
    if (ver_is(ver, "019")) return STAR_VER(ISteamUser, 019, o);
    if (ver_is(ver, "020")) return STAR_VER(ISteamUser, 020, o);
    if (ver_is(ver, "021")) return STAR_VER(ISteamUser, 021, o);
    if (ver_is(ver, "022")) return STAR_VER(ISteamUser, 022, o);
    return static_cast<ISteamUser*>(o);
}

ISteamGameServer* StarSteamClient::GetISteamGameServer(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamGameServer::get();
}

void StarSteamClient::SetLocalIPBinding(uint32 ip, uint16 port) { STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); }

ISteamFriends* StarSteamClient::GetISteamFriends(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p);
    StarSteamFriends* o = &StarSteamFriends::get();

    if (ver_is(ver, "001") || ver_is(ver, "002") || ver_is(ver, "003") || ver_is(ver, "004") ||
        ver_is(ver, "005") || ver_is(ver, "006") || ver_is(ver, "007") || ver_is(ver, "008") ||
        ver_is(ver, "009") || ver_is(ver, "010") || ver_is(ver, "011") || ver_is(ver, "012") ||
        ver_is(ver, "013")) {
        return nullptr;
    }
    if (ver_is(ver, "014")) return STAR_VER(ISteamFriends, 014, o);
    if (ver_is(ver, "015")) return STAR_VER(ISteamFriends, 015, o);
    if (ver_is(ver, "016")) return STAR_VER(ISteamFriends, 016, o);
    if (ver_is(ver, "017")) return STAR_VER(ISteamFriends, 017, o);
    return static_cast<ISteamFriends*>(o);
}

ISteamUtils* StarSteamClient::GetISteamUtils(HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(p);
    StarSteamUtils* o = &StarSteamUtils::get();
    if (ver_is(ver, "001")) return STAR_VER(ISteamUtils, 001, o);
    if (ver_is(ver, "002")) return STAR_VER(ISteamUtils, 002, o);
    if (ver_is(ver, "003")) return STAR_VER(ISteamUtils, 003, o);
    if (ver_is(ver, "004")) return STAR_VER(ISteamUtils, 004, o);
    if (ver_is(ver, "005")) return STAR_VER(ISteamUtils, 005, o);
    if (ver_is(ver, "006")) return STAR_VER(ISteamUtils, 006, o);
    if (ver_is(ver, "007")) return STAR_VER(ISteamUtils, 007, o);
    if (ver_is(ver, "008")) return STAR_VER(ISteamUtils, 008, o);
    if (ver_is(ver, "009")) return STAR_VER(ISteamUtils, 009, o);
    return static_cast<ISteamUtils*>(o);
}

ISteamMatchmaking* StarSteamClient::GetISteamMatchmaking(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamMatchmaking::get();
}

ISteamMatchmakingServers* StarSteamClient::GetISteamMatchmakingServers(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamMatchmakingServers::get();
}

void* StarSteamClient::GetISteamGenericInterface(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p);
    if (!ver) return nullptr;

    if (strstr(ver, "SteamMatchMakingServers")) return &StarSteamMatchmakingServers::get();
    if (strstr(ver, "SteamMatchMaking") || strstr(ver, "SteamMatchmaking")) return &StarSteamMatchmaking::get();
    if (strstr(ver, "SteamGameServerStats")) return &StarSteamGameServerStats::get();
    if (strstr(ver, "SteamGameServer")) return &StarSteamGameServer::get();
    if (strstr(ver, "STEAMMUSICREMOTE")) return &StarSteamMusicRemote::get();
    if (strstr(ver, "STEAMMUSIC")) return &StarSteamMusic::get();
    if (strstr(ver, "SteamUser")) return GetISteamUser(1, 1, ver);
    if (strstr(ver, "SteamFriends")) return GetISteamFriends(1, 1, ver);
    if (strstr(ver, "SteamUtils")) return GetISteamUtils(1, ver);
    if (strstr(ver, "STEAMUSERSTATS")) return GetISteamUserStats(1, 1, ver);
    if (strstr(ver, "STEAMAPPLIST")) return &StarSteamAppList::get();
    if (strstr(ver, "STEAMAPPS") || strstr(ver, "SteamApps")) return GetISteamApps(1, 1, ver);
    if (strstr(ver, "SteamNetworking")) return &StarSteamNetworking::get();
    if (strstr(ver, "STEAMREMOTESTORAGE")) return GetISteamRemoteStorage(1, 1, ver);
    if (strstr(ver, "STEAMSCREENSHOTS")) return &StarSteamScreenshots::get();
    if (strstr(ver, "STEAMHTTP")) return &StarSteamHTTP::get();
    if (strstr(ver, "SteamController")) return &StarSteamController::get();
    if (strstr(ver, "STEAMUGC")) return &StarSteamUGC::get();
    if (strstr(ver, "STEAMHTMLSURFACE")) return &StarSteamHTMLSurface::get();
    if (strstr(ver, "STEAMINVENTORY")) return &StarSteamInventory::get();
    if (strstr(ver, "STEAMVIDEO")) return &StarSteamVideo::get();
    if (strstr(ver, "STEAMUNIFIEDMESSAGES")) return &StarSteamUnifiedMessages::get();
    STAR_LOG("GetISteamGenericInterface: unhandled interface '%s', returning dummy pointer", ver);
    return g_dummy_interface;
}

ISteamUserStats* StarSteamClient::GetISteamUserStats(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p);
    StarSteamUserStats* o = &StarSteamUserStats::get();
    if (ver_is(ver, "001")) return STAR_VER(ISteamUserStats, 001, o);
    if (ver_is(ver, "002")) return STAR_VER(ISteamUserStats, 002, o);
    if (ver_is(ver, "003")) return STAR_VER(ISteamUserStats, 003, o);
    if (ver_is(ver, "004")) return STAR_VER(ISteamUserStats, 004, o);
    if (ver_is(ver, "005")) return STAR_VER(ISteamUserStats, 005, o);
    if (ver_is(ver, "006")) return STAR_VER(ISteamUserStats, 006, o);
    if (ver_is(ver, "007")) return STAR_VER(ISteamUserStats, 007, o);
    if (ver_is(ver, "008")) return STAR_VER(ISteamUserStats, 008, o);
    if (ver_is(ver, "009")) return STAR_VER(ISteamUserStats, 009, o);
    if (ver_is(ver, "010")) return STAR_VER(ISteamUserStats, 010, o);
    if (ver_is(ver, "011")) return STAR_VER(ISteamUserStats, 011, o);
    if (ver_is(ver, "012")) return STAR_VER(ISteamUserStats, 012, o);
    return static_cast<ISteamUserStats*>(o);
}

ISteamGameServerStats* StarSteamClient::GetISteamGameServerStats(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamGameServerStats::get();
}

ISteamApps* StarSteamClient::GetISteamApps(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p);
    StarSteamApps* a = &StarSteamApps::get();
    if (ver_is(ver, "001")) return STAR_VER(ISteamApps, 001, a);
    if (ver_is(ver, "002")) return STAR_VER(ISteamApps, 002, a);
    if (ver_is(ver, "003")) return STAR_VER(ISteamApps, 003, a);
    if (ver_is(ver, "004")) return STAR_VER(ISteamApps, 004, a);
    if (ver_is(ver, "005")) return STAR_VER(ISteamApps, 005, a);
    if (ver_is(ver, "006")) return STAR_VER(ISteamApps, 006, a);
    if (ver_is(ver, "007")) return STAR_VER(ISteamApps, 007, a);
    if (ver_is(ver, "008")) return STAR_VER(ISteamApps, 008, a);
    return static_cast<ISteamApps*>(a);
}

ISteamNetworking* StarSteamClient::GetISteamNetworking(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamNetworking::get();
}

ISteamRemoteStorage* StarSteamClient::GetISteamRemoteStorage(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p);
    StarSteamRemoteStorage* o = &StarSteamRemoteStorage::get();
    if (ver_is(ver, "001")) return STAR_VER(ISteamRemoteStorage, 001, o);
    if (ver_is(ver, "002")) return STAR_VER(ISteamRemoteStorage, 002, o);
    if (ver_is(ver, "003")) return STAR_VER(ISteamRemoteStorage, 003, o);
    if (ver_is(ver, "004")) return STAR_VER(ISteamRemoteStorage, 004, o);
    if (ver_is(ver, "005")) return STAR_VER(ISteamRemoteStorage, 005, o);
    if (ver_is(ver, "006")) return STAR_VER(ISteamRemoteStorage, 006, o);
    if (ver_is(ver, "007")) return STAR_VER(ISteamRemoteStorage, 007, o);
    if (ver_is(ver, "008")) return STAR_VER(ISteamRemoteStorage, 008, o);
    if (ver_is(ver, "009")) return STAR_VER(ISteamRemoteStorage, 009, o);
    if (ver_is(ver, "010")) return STAR_VER(ISteamRemoteStorage, 010, o);
    if (ver_is(ver, "011")) return STAR_VER(ISteamRemoteStorage, 011, o);
    if (ver_is(ver, "012")) return STAR_VER(ISteamRemoteStorage, 012, o);
    if (ver_is(ver, "013")) return STAR_VER(ISteamRemoteStorage, 013, o);
    if (ver_is(ver, "014")) return STAR_VER(ISteamRemoteStorage, 014, o);
    if (ver_is(ver, "015")) return STAR_VER(ISteamRemoteStorage, 015, o);
    return static_cast<ISteamRemoteStorage*>(o);
}

ISteamScreenshots* StarSteamClient::GetISteamScreenshots(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamScreenshots::get();
}

void StarSteamClient::RunFrame() { STAR_RunCallbacks(); }
uint32 StarSteamClient::GetIPCCallCount() { return 1; }
void StarSteamClient::SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction) { STAR_UNREFERENCED(pFunction); }
bool StarSteamClient::BShutdownIfAllPipesClosed() { return false; }

ISteamHTTP* StarSteamClient::GetISteamHTTP(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamHTTP::get();
}

void* StarSteamClient::DEPRECATED_GetISteamUnifiedMessages(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamUnifiedMessages::get();
}

ISteamController* StarSteamClient::GetISteamController(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return reinterpret_cast<ISteamController*>(&StarSteamController::get());
}

ISteamUGC* StarSteamClient::GetISteamUGC(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return reinterpret_cast<ISteamUGC*>(&StarSteamUGC::get());
}

ISteamAppList* StarSteamClient::GetISteamAppList(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamAppList::get();
}

ISteamMusic* StarSteamClient::GetISteamMusic(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamMusic::get();
}

ISteamMusicRemote* StarSteamClient::GetISteamMusicRemote(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamMusicRemote::get();
}

ISteamHTMLSurface* StarSteamClient::GetISteamHTMLSurface(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamHTMLSurface::get();
}

void StarSteamClient::DEPRECATED_Set_SteamAPI_CPostAPIResultInProcess(void(*)()) {}
void StarSteamClient::DEPRECATED_Remove_SteamAPI_CPostAPIResultInProcess(void(*)()) {}
void StarSteamClient::Set_SteamAPI_CCheckCallbackRegisteredInProcess(SteamAPI_CheckCallbackRegistered_t func) { STAR_UNREFERENCED(func); }

ISteamInventory* StarSteamClient::GetISteamInventory(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamInventory::get();
}

ISteamVideo* StarSteamClient::GetISteamVideo(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return &StarSteamVideo::get();
}


ISteamParentalSettings* StarSteamClient::GetISteamParentalSettings(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return reinterpret_cast<ISteamParentalSettings*>(g_dummy_interface);
}

ISteamUnifiedMessages* StarSteamClient::GetISteamUnifiedMessages(HSteamUser h, HSteamPipe p, const char* ver)
{
    STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver);
    return reinterpret_cast<ISteamUnifiedMessages*>(&StarSteamUnifiedMessages::get());
}

void StarSteamClient::Set_SteamAPI_CPostAPIResultInProcess(SteamAPI_PostAPIResultInProcess_t func) { STAR_UNREFERENCED(func); }
void StarSteamClient::Remove_SteamAPI_CPostAPIResultInProcess(SteamAPI_PostAPIResultInProcess_t func) { STAR_UNREFERENCED(func); }

ISteamGameSearch* StarSteamClient::GetISteamGameSearch(HSteamUser h, HSteamPipe p, const char* ver) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver); return reinterpret_cast<ISteamGameSearch*>(g_dummy_interface); }
ISteamInput* StarSteamClient::GetISteamInput(HSteamUser h, HSteamPipe p, const char* ver) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver); return reinterpret_cast<ISteamInput*>(g_dummy_interface); }
ISteamParties* StarSteamClient::GetISteamParties(HSteamUser h, HSteamPipe p, const char* ver) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver); return reinterpret_cast<ISteamParties*>(g_dummy_interface); }
ISteamRemotePlay* StarSteamClient::GetISteamRemotePlay(HSteamUser h, HSteamPipe p, const char* ver) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(ver); return reinterpret_cast<ISteamRemotePlay*>(g_dummy_interface); }

void StarSteamClient::SetLocalIPBinding(const SteamIPAddress_t& unIP, uint16 usPort) { STAR_UNREFERENCED(unIP); STAR_UNREFERENCED(usPort); }
void StarSteamClient::DestroyAllInterfaces() {}
