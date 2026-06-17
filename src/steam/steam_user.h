#pragma once
#include "core/star_common.h"

#include "steam/isteamuser008.h"
#include "steam/isteamuser009.h"
#include "steam/isteamuser010.h"
#include "steam/isteamuser011.h"
#include "steam/isteamuser012.h"
#include "steam/isteamuser013.h"
#include "steam/isteamuser014.h"
#include "steam/isteamuser015.h"
#include "steam/isteamuser016.h"
#include "steam/isteamuser017.h"
#include "steam/isteamuser018.h"
#include "steam/isteamuser019.h"
#include "steam/isteamuser020.h"
#include "steam/isteamuser021.h"
#include "steam/isteamuser022.h"

class StarSteamUser :
    public ISteamUser008,
    public ISteamUser009,
    public ISteamUser010,
    public ISteamUser011,
    public ISteamUser012,
    public ISteamUser013,
    public ISteamUser014,
    public ISteamUser015,
    public ISteamUser016,
    public ISteamUser017,
    public ISteamUser018,
    public ISteamUser019,
    public ISteamUser020,
    public ISteamUser021,
    public ISteamUser022,
    public ISteamUser {
public:
    static StarSteamUser& get();

    HSteamUser GetHSteamUser() override;
    bool BLoggedOn() override;
    CSteamID GetSteamID() override;

    int InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure) override;
    int InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure) override;
    int InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure, void* pvSteam2Key, int cbSteam2Key) override;

    void TerminateGameConnection(uint32 unIPServer, uint16 usPortServer) override;
    void TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char* pchExtraInfo) override;
    void RefreshSteam2Login() override;
    bool GetUserDataFolder(char* pchBuffer, int cubBuffer) override;
    void StartVoiceRecording() override;
    void StopVoiceRecording() override;

    EVoiceResult GetCompressedVoice(void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten) override;
    EVoiceResult GetAvailableVoice(uint32* pcbCompressed, uint32* pcbUncompressed) override;
    EVoiceResult GetAvailableVoice(uint32* pcbCompressed, uint32* pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate) override;
    EVoiceResult GetVoice(bool bWantCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, bool bWantUncompressed, void* pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32* nUncompressBytesWritten) override;
    EVoiceResult GetVoice(bool bWantCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, bool bWantUncompressed, void* pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32* nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate) override;
    EVoiceResult DecompressVoice(void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten) override;
    EVoiceResult DecompressVoice(const void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten) override;
    EVoiceResult DecompressVoice(const void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, uint32 nDesiredSampleRate) override;
    uint32 GetVoiceOptimalSampleRate() override;

    HAuthTicket GetAuthSessionTicket(void* pTicket, int cbMaxTicket, uint32* pcbTicket) override;
    HAuthTicket GetAuthSessionTicket(void* pTicket, int cbMaxTicket, uint32* pcbTicket, const SteamNetworkingIdentity* pSteamNetworkingIdentity) override;
    EBeginAuthSessionResult BeginAuthSession(const void* pAuthTicket, int cbAuthTicket, CSteamID steamID) override;
    void EndAuthSession(CSteamID steamID) override;
    void CancelAuthTicket(HAuthTicket hAuthTicket) override;
    EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamID, AppId_t appID) override;
    bool BIsBehindNAT() override;
    void AdvertiseGame(CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer) override;
    SteamAPICall_t RequestEncryptedAppTicket(void* pDataToInclude, int cbDataToInclude) override;
    bool GetEncryptedAppTicket(void* pTicket, int cbMaxTicket, uint32* pcbTicket) override;
    int GetGameBadgeLevel(int nSeries, bool bFoil) override;
    int GetPlayerSteamLevel() override;
    SteamAPICall_t RequestStoreAuthURL(const char* pchRedirectURL) override;

    bool BIsPhoneVerified() override;
    bool BIsTwoFactorEnabled() override;
    bool BIsPhoneIdentifying() override;
    bool BIsPhoneRequiringVerification() override;

    SteamAPICall_t GetMarketEligibility() override;
    SteamAPICall_t GetDurationControl() override;

    bool BSetDurationControlOnlineState(EDurationControlOnlineState eNewState) override;

    HAuthTicket GetAuthTicketForWebApi(const char* pchIdentity) override;

private:
    StarSteamUser() = default;
    static const uint8_t dummy_ticket_[64];
};
