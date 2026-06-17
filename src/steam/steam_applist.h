#pragma once
#include "core/star_common.h"
#include "steam/isteamapplist.h"

class StarSteamAppList : public ISteamAppList {
public:
    static StarSteamAppList& get();
    uint32 GetNumInstalledApps() override;
    uint32 GetInstalledApps(AppId_t* pvecAppID, uint32 unMaxAppIDs) override;
    int GetAppName(AppId_t nAppID, char* pchName, int cchNameMax) override;
    int GetAppInstallDir(AppId_t nAppID, char* pchDirectory, int cchNameMax) override;
    int GetAppBuildId(AppId_t nAppID) override;
private:
    StarSteamAppList() = default;
};
