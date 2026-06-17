#include "steam/steam_user.h"
#include "core/callbacks.h"
#include "core/settings.h"
#include "core/storage.h"
#include "steam/isteamuser.h"

const uint8_t StarSteamUser::dummy_ticket_[64] = {
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
    0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
    0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
    0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
    0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,
    0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
    0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40
};

StarSteamUser& StarSteamUser::get()
{
    static StarSteamUser instance;
    return instance;
}

HSteamUser StarSteamUser::GetHSteamUser()
{
    return 1;
}

bool StarSteamUser::BLoggedOn()
{
    return true;
}

CSteamID StarSteamUser::GetSteamID()
{
    return CSteamID(Settings::get().steam_id);
}

int StarSteamUser::InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
    STAR_UNREFERENCED(steamIDGameServer);
    STAR_UNREFERENCED(unIPServer);
    STAR_UNREFERENCED(usPortServer);
    STAR_UNREFERENCED(bSecure);
    if (!pAuthBlob || cbMaxAuthBlob <= 0) return 0;
    int bytes = std::min(cbMaxAuthBlob, (int)sizeof(dummy_ticket_));
    memcpy(pAuthBlob, dummy_ticket_, bytes);
    return bytes;
}

int StarSteamUser::InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
    STAR_UNREFERENCED(gameID);
    return InitiateGameConnection(pAuthBlob, cbMaxAuthBlob, steamIDGameServer, unIPServer, usPortServer, bSecure);
}

int StarSteamUser::InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, CGameID gameID, uint32 unIPServer, uint16 usPortServer, bool bSecure, void* pvSteam2Key, int cbSteam2Key)
{
    STAR_UNREFERENCED(gameID); STAR_UNREFERENCED(pvSteam2Key); STAR_UNREFERENCED(cbSteam2Key);
    return InitiateGameConnection(pAuthBlob, cbMaxAuthBlob, steamIDGameServer, unIPServer, usPortServer, bSecure);
}

void StarSteamUser::RefreshSteam2Login() {}

void StarSteamUser::TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
{
    STAR_UNREFERENCED(unIPServer);
    STAR_UNREFERENCED(usPortServer);
}

void StarSteamUser::TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char* pchExtraInfo)
{
    STAR_UNREFERENCED(gameID);
    STAR_UNREFERENCED(eAppUsageEvent);
    STAR_UNREFERENCED(pchExtraInfo);
}

bool StarSteamUser::GetUserDataFolder(char* pchBuffer, int cubBuffer)
{
    if (!pchBuffer || cubBuffer <= 0) return false;
    const std::string& path = Storage::get().base_path();
    strncpy_s(pchBuffer, cubBuffer, path.c_str(), _TRUNCATE);
    return true;
}

void StarSteamUser::StartVoiceRecording() {}
void StarSteamUser::StopVoiceRecording() {}

EVoiceResult StarSteamUser::GetCompressedVoice(void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten)
{
    STAR_UNREFERENCED(pDestBuffer); STAR_UNREFERENCED(cbDestBufferSize);
    if (nBytesWritten) *nBytesWritten = 0;
    return k_EVoiceResultNotRecording;
}

EVoiceResult StarSteamUser::GetAvailableVoice(uint32* pcbCompressed, uint32* pcbUncompressed)
{
    return GetAvailableVoice(pcbCompressed, pcbUncompressed, 0);
}

EVoiceResult StarSteamUser::GetAvailableVoice(uint32* pcbCompressed, uint32* pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate)
{
    STAR_UNREFERENCED(nUncompressedVoiceDesiredSampleRate);
    if (pcbCompressed) *pcbCompressed = 0;
    if (pcbUncompressed) *pcbUncompressed = 0;
    return k_EVoiceResultNotRecording;
}

EVoiceResult StarSteamUser::GetVoice(bool bWantCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten,
    bool bWantUncompressed, void* pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32* nUncompressBytesWritten,
    uint32 nUncompressedVoiceDesiredSampleRate)
{
    STAR_UNREFERENCED(bWantCompressed); STAR_UNREFERENCED(pDestBuffer); STAR_UNREFERENCED(cbDestBufferSize);
    STAR_UNREFERENCED(bWantUncompressed); STAR_UNREFERENCED(pUncompressedDestBuffer); STAR_UNREFERENCED(cbUncompressedDestBufferSize);
    STAR_UNREFERENCED(nUncompressedVoiceDesiredSampleRate);
    if (nBytesWritten) *nBytesWritten = 0;
    if (nUncompressBytesWritten) *nUncompressBytesWritten = 0;
    return k_EVoiceResultNotRecording;
}

EVoiceResult StarSteamUser::GetVoice(bool bWantCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten,
    bool bWantUncompressed, void* pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32* nUncompressBytesWritten)
{
    return GetVoice(bWantCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten,
        bWantUncompressed, pUncompressedDestBuffer, cbUncompressedDestBufferSize, nUncompressBytesWritten, 0);
}

EVoiceResult StarSteamUser::DecompressVoice(const void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, uint32 nDesiredSampleRate)
{
    STAR_UNREFERENCED(pCompressed); STAR_UNREFERENCED(cbCompressed); STAR_UNREFERENCED(pDestBuffer);
    STAR_UNREFERENCED(cbDestBufferSize); STAR_UNREFERENCED(nDesiredSampleRate);
    if (nBytesWritten) *nBytesWritten = 0;
    return k_EVoiceResultNotRecording;
}

EVoiceResult StarSteamUser::DecompressVoice(void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten)
{
    return DecompressVoice((const void*)pCompressed, cbCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, 0);
}

EVoiceResult StarSteamUser::DecompressVoice(const void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten)
{
    return DecompressVoice(pCompressed, cbCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, 0);
}

uint32 StarSteamUser::GetVoiceOptimalSampleRate()
{
    return 11025;
}

HAuthTicket StarSteamUser::GetAuthSessionTicket(void* pTicket, int cbMaxTicket, uint32* pcbTicket)
{
    if (pTicket && cbMaxTicket > 0) {
        int bytes = std::min(cbMaxTicket, (int)sizeof(dummy_ticket_));
        memcpy(pTicket, dummy_ticket_, bytes);
        if (pcbTicket) *pcbTicket = (uint32)bytes;
    } else {
        if (pcbTicket) *pcbTicket = sizeof(dummy_ticket_);
    }

    GetAuthSessionTicketResponse_t cb{};
    cb.m_hAuthTicket = 1;
    cb.m_eResult = k_EResultOK;
    STAR_DispatchCallback(GetAuthSessionTicketResponse_t::k_iCallback, &cb, sizeof(cb));
    return 1;
}

HAuthTicket StarSteamUser::GetAuthSessionTicket(void* pTicket, int cbMaxTicket, uint32* pcbTicket, const SteamNetworkingIdentity* pSteamNetworkingIdentity)
{
    STAR_UNREFERENCED(pSteamNetworkingIdentity);
    return GetAuthSessionTicket(pTicket, cbMaxTicket, pcbTicket);
}

EBeginAuthSessionResult StarSteamUser::BeginAuthSession(const void* pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
    STAR_UNREFERENCED(pAuthTicket); STAR_UNREFERENCED(cbAuthTicket); STAR_UNREFERENCED(steamID);
    return k_EBeginAuthSessionResultOK;
}

void StarSteamUser::EndAuthSession(CSteamID steamID) { STAR_UNREFERENCED(steamID); }
void StarSteamUser::CancelAuthTicket(HAuthTicket hAuthTicket) { STAR_UNREFERENCED(hAuthTicket); }

EUserHasLicenseForAppResult StarSteamUser::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
    STAR_UNREFERENCED(steamID); STAR_UNREFERENCED(appID);
    return k_EUserHasLicenseResultHasLicense;
}

bool StarSteamUser::BIsBehindNAT() { return false; }

void StarSteamUser::AdvertiseGame(CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
{
    STAR_UNREFERENCED(steamIDGameServer); STAR_UNREFERENCED(unIPServer); STAR_UNREFERENCED(usPortServer);
}

SteamAPICall_t StarSteamUser::RequestEncryptedAppTicket(void* pDataToInclude, int cbDataToInclude)
{
    STAR_UNREFERENCED(pDataToInclude); STAR_UNREFERENCED(cbDataToInclude);
    EncryptedAppTicketResponse_t result{};
    result.m_eResult = k_EResultOK;
    return STAR_PostCallResult(EncryptedAppTicketResponse_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamUser::GetEncryptedAppTicket(void* pTicket, int cbMaxTicket, uint32* pcbTicket)
{
    if (pTicket && cbMaxTicket > 0) {
        int bytes = std::min(cbMaxTicket, (int)sizeof(dummy_ticket_));
        memcpy(pTicket, dummy_ticket_, bytes);
        if (pcbTicket) *pcbTicket = (uint32)bytes;
        return true;
    }
    if (pcbTicket) *pcbTicket = sizeof(dummy_ticket_);
    return false;
}

int StarSteamUser::GetGameBadgeLevel(int nSeries, bool bFoil)
{
    STAR_UNREFERENCED(nSeries); STAR_UNREFERENCED(bFoil);
    return 0;
}

int StarSteamUser::GetPlayerSteamLevel() { return 1; }

SteamAPICall_t StarSteamUser::RequestStoreAuthURL(const char* pchRedirectURL)
{
    STAR_UNREFERENCED(pchRedirectURL);
    StoreAuthURLResponse_t result{};
    strncpy_s(result.m_szURL, "https://store.steampowered.com/", _TRUNCATE);
    return STAR_PostCallResult(StoreAuthURLResponse_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamUser::BIsPhoneVerified() { return true; }
bool StarSteamUser::BIsTwoFactorEnabled() { return false; }
bool StarSteamUser::BIsPhoneIdentifying() { return false; }
bool StarSteamUser::BIsPhoneRequiringVerification() { return false; }

SteamAPICall_t StarSteamUser::GetMarketEligibility()
{
    MarketEligibilityResponse_t result{};
    result.m_bAllowed = true;
    return STAR_PostCallResult(MarketEligibilityResponse_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamUser::GetDurationControl()
{
    DurationControl_t result{};
    result.m_eResult = k_EResultOK;
    result.m_appid = Settings::get().app_id;
    return STAR_PostCallResult(DurationControl_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamUser::BSetDurationControlOnlineState(EDurationControlOnlineState eNewState)
{
    STAR_UNREFERENCED(eNewState);
    return true;
}

HAuthTicket StarSteamUser::GetAuthTicketForWebApi(const char* pchIdentity)
{
    STAR_UNREFERENCED(pchIdentity);
    GetTicketForWebApiResponse_t cb{};
    cb.m_hAuthTicket = 1;
    cb.m_eResult = k_EResultOK;
    cb.m_cubTicket = (int)sizeof(dummy_ticket_);
    memcpy(cb.m_rgubTicket, dummy_ticket_, sizeof(dummy_ticket_));
    STAR_DispatchCallback(GetTicketForWebApiResponse_t::k_iCallback, &cb, sizeof(cb));
    return 1;
}
