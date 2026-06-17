#pragma once
#include "core/star_common.h"

#include "steam/isteamclient012.h"
#include "steam/isteamclient013.h"
#include "steam/isteamclient014.h"
#include "steam/isteamclient015.h"
#include "steam/isteamclient016.h"
#include "steam/isteamclient017.h"
#include "steam/isteamclient018.h"
#include "steam/isteamclient019.h"
#include "steam/isteamclient020.h"
#include "steam/isteamclient021.h"
#include "steam/isteamclient022.h"

class StarSteamClient :
    public ISteamClient012,
    public ISteamClient013,
    public ISteamClient014,
    public ISteamClient015,
    public ISteamClient016,
    public ISteamClient017,
    public ISteamClient018,
    public ISteamClient019,
    public ISteamClient020,
    public ISteamClient021,
    public ISteamClient022,
    public ISteamClient {
public:
    static StarSteamClient& get();

    void* GetClientInterface(const char* pchVersion);

    HSteamPipe CreateSteamPipe() override;
    bool BReleaseSteamPipe(HSteamPipe hSteamPipe) override;
    HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe) override;
    HSteamUser CreateLocalUser(HSteamPipe* phSteamPipe, EAccountType eAccountType) override;
    void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser) override;
    ISteamUser* GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamGameServer* GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    void SetLocalIPBinding(uint32 unIP, uint16 usPort) override;
    ISteamFriends* GetISteamFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamUtils* GetISteamUtils(HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamMatchmaking* GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamMatchmakingServers* GetISteamMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    void* GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamUserStats* GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamGameServerStats* GetISteamGameServerStats(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamApps* GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamNetworking* GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamRemoteStorage* GetISteamRemoteStorage(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamScreenshots* GetISteamScreenshots(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    void RunFrame() override;
    uint32 GetIPCCallCount() override;
    void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction) override;
    bool BShutdownIfAllPipesClosed() override;
    ISteamHTTP* GetISteamHTTP(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    void* DEPRECATED_GetISteamUnifiedMessages(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamController* GetISteamController(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamUGC* GetISteamUGC(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamAppList* GetISteamAppList(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamMusic* GetISteamMusic(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamMusicRemote* GetISteamMusicRemote(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamHTMLSurface* GetISteamHTMLSurface(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    void DEPRECATED_Set_SteamAPI_CPostAPIResultInProcess(void(*)()) override;
    void DEPRECATED_Remove_SteamAPI_CPostAPIResultInProcess(void(*)()) override;
    void Set_SteamAPI_CCheckCallbackRegisteredInProcess(SteamAPI_CheckCallbackRegistered_t func) override;
    ISteamInventory* GetISteamInventory(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamVideo* GetISteamVideo(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamParentalSettings* GetISteamParentalSettings(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;

    ISteamUnifiedMessages* GetISteamUnifiedMessages(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;

    void Set_SteamAPI_CPostAPIResultInProcess(SteamAPI_PostAPIResultInProcess_t func) override;
    void Remove_SteamAPI_CPostAPIResultInProcess(SteamAPI_PostAPIResultInProcess_t func) override;

    ISteamGameSearch* GetISteamGameSearch(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamInput* GetISteamInput(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;
    ISteamParties* GetISteamParties(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;

    ISteamRemotePlay* GetISteamRemotePlay(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) override;

    void SetLocalIPBinding(const SteamIPAddress_t& unIP, uint16 usPort) override;

    void DestroyAllInterfaces() override;

private:
    StarSteamClient() = default;
};
