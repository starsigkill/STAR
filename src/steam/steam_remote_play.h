#pragma once
#include "core/star_common.h"
#include "steam/isteamremoteplay.h"
#include "steam/isteamremoteplay001.h"

class StarSteamRemotePlay : public ISteamRemotePlay001
{
public:
    static StarSteamRemotePlay& get() { static StarSteamRemotePlay s; return s; }

    uint32 GetSessionCount() override { return 0; }
    RemotePlaySessionID_t GetSessionID(int) override { return 0; }
    CSteamID GetSessionSteamID(RemotePlaySessionID_t) override { return CSteamID(); }
    const char* GetSessionClientName(RemotePlaySessionID_t) override { return ""; }
    ESteamDeviceFormFactor GetSessionClientFormFactor(RemotePlaySessionID_t) override { return k_ESteamDeviceFormFactorUnknown; }
    bool BGetSessionClientResolution(RemotePlaySessionID_t, int* pX, int* pY) override
    {
        if (pX) *pX = 0;
        if (pY) *pY = 0;
        return false;
    }
    bool BSendRemotePlayTogetherInvite(CSteamID) override { return false; }
};
