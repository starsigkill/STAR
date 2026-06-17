#pragma once
#include "core/star_common.h"
#include "steam/isteamgameserverstats.h"

class StarSteamGameServerStats : public ISteamGameServerStats {
public:
    static StarSteamGameServerStats& get();
    SteamAPICall_t RequestUserStats(CSteamID steamIDUser) override;
    bool GetUserStat(CSteamID steamIDUser, const char* pchName, int32* pData) override;
    bool GetUserStat(CSteamID steamIDUser, const char* pchName, float* pData) override;
    bool GetUserAchievement(CSteamID steamIDUser, const char* pchName, bool* pbAchieved) override;
    bool SetUserStat(CSteamID steamIDUser, const char* pchName, int32 nData) override;
    bool SetUserStat(CSteamID steamIDUser, const char* pchName, float fData) override;
    bool UpdateUserAvgRateStat(CSteamID steamIDUser, const char* pchName, float flCountThisSession, double dSessionLength) override;
    bool SetUserAchievement(CSteamID steamIDUser, const char* pchName) override;
    bool ClearUserAchievement(CSteamID steamIDUser, const char* pchName) override;
    SteamAPICall_t StoreUserStats(CSteamID steamIDUser) override;
private:
    StarSteamGameServerStats() = default;
};
