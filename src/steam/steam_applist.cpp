#include "steam/steam_applist.h"
#include "core/settings.h"

StarSteamAppList& StarSteamAppList::get() { static StarSteamAppList i; return i; }

uint32 StarSteamAppList::GetNumInstalledApps() { return 1; }

uint32 StarSteamAppList::GetInstalledApps(AppId_t* pvecAppID, uint32 unMaxAppIDs)
{
    if (pvecAppID && unMaxAppIDs >= 1) {
        pvecAppID[0] = Settings::get().app_id;
        return 1;
    }
    return 0;
}

int StarSteamAppList::GetAppName(AppId_t nAppID, char* pchName, int cchNameMax)
{
    STAR_UNREFERENCED(nAppID);
    if (pchName && cchNameMax > 0) {
        strncpy_s(pchName, cchNameMax, "Unknown", _TRUNCATE);
        return (int)strlen(pchName);
    }
    return -1;
}

int StarSteamAppList::GetAppInstallDir(AppId_t nAppID, char* pchDirectory, int cchNameMax)
{
    STAR_UNREFERENCED(nAppID);
    char exe_path[MAX_PATH] = {};
    GetModuleFileNameA(nullptr, exe_path, MAX_PATH);
    char* last_sep = strrchr(exe_path, '\\');
    if (last_sep) *last_sep = 0;
    if (pchDirectory && cchNameMax > 0) {
        strncpy_s(pchDirectory, cchNameMax, exe_path, _TRUNCATE);
        return (int)strlen(pchDirectory);
    }
    return -1;
}

int StarSteamAppList::GetAppBuildId(AppId_t nAppID) { STAR_UNREFERENCED(nAppID); return 0; }
