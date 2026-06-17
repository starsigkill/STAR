#include "steam/steam_apps.h"
#include "core/settings.h"
#include "core/callbacks.h"

StarSteamApps& StarSteamApps::get()
{
    static StarSteamApps instance;
    return instance;
}

int StarSteamApps::GetAppData(AppId_t nAppID, const char* pchKey, char* pchValue, int cchValueMax)
{
    STAR_UNREFERENCED(nAppID); STAR_UNREFERENCED(pchKey);
    if (pchValue && cchValueMax > 0) pchValue[0] = 0;
    return 0;
}

bool StarSteamApps::BIsSubscribed() { return true; }
bool StarSteamApps::BIsLowViolence() { return false; }
bool StarSteamApps::BIsCybercafe() { return false; }
bool StarSteamApps::BIsVACBanned() { return false; }

const char* StarSteamApps::GetCurrentGameLanguage()
{
    return Settings::get().language.c_str();
}

const char* StarSteamApps::GetAvailableGameLanguages()
{
    return Settings::get().supported_languages_str.c_str();
}

bool StarSteamApps::BIsSubscribedApp(AppId_t appID)
{
    STAR_UNREFERENCED(appID);
    return true;
}

bool StarSteamApps::BIsDlcInstalled(AppId_t appID)
{
    auto& s = Settings::get();
    if (s.unlock_all_dlc) return true;
    if (appID == (AppId_t)s.app_id) return true;
    for (auto& dlc : s.dlc_list) {
        if (dlc.app_id == (uint32_t)appID) return true;
    }
    return false;
}

uint32 StarSteamApps::GetEarliestPurchaseUnixTime(AppId_t nAppID)
{
    STAR_UNREFERENCED(nAppID);

    return 1577836800u;
}

bool StarSteamApps::BIsSubscribedFromFreeWeekend() { return false; }

int StarSteamApps::GetDLCCount()
{
    return (int)Settings::get().dlc_list.size();
}

bool StarSteamApps::BGetDLCDataByIndex(int iDLC, AppId_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize)
{
    auto& dlcs = Settings::get().dlc_list;
    if (iDLC < 0 || iDLC >= (int)dlcs.size()) return false;
    if (pAppID) *pAppID = dlcs[iDLC].app_id;
    if (pbAvailable) *pbAvailable = true;
    if (pchName && cchNameBufferSize > 0) {
        strncpy_s(pchName, cchNameBufferSize, dlcs[iDLC].name.c_str(), _TRUNCATE);
    }
    return true;
}

void StarSteamApps::InstallDLC(AppId_t nAppID) { STAR_UNREFERENCED(nAppID); }
void StarSteamApps::UninstallDLC(AppId_t nAppID) { STAR_UNREFERENCED(nAppID); }
void StarSteamApps::RequestAppProofOfPurchaseKey_OLD(AppId_t nAppID) { STAR_UNREFERENCED(nAppID); }

bool StarSteamApps::GetCurrentBetaName(char* pchName, int cchNameBufferSize)
{
    auto& s = Settings::get();
    if (!s.is_beta_branch) return false;
    if (pchName && cchNameBufferSize > 0) {
        strncpy_s(pchName, cchNameBufferSize, s.branch_name.c_str(), _TRUNCATE);
    }
    return true;
}

bool StarSteamApps::MarkContentCorrupt(bool bMissingFilesOnly)
{
    STAR_UNREFERENCED(bMissingFilesOnly);
    return false;
}

uint32 StarSteamApps::GetInstalledDepots(AppId_t appID, DepotId_t* pvecDepots, uint32 cMaxDepots)
{
    STAR_UNREFERENCED(appID); STAR_UNREFERENCED(pvecDepots); STAR_UNREFERENCED(cMaxDepots);
    return 0;
}

uint32 StarSteamApps::GetAppInstallDir(AppId_t appID, char* pchFolder, uint32 cchFolderBufferSize)
{
    STAR_UNREFERENCED(appID);

    char exe_path[MAX_PATH] = {};
    GetModuleFileNameA(nullptr, exe_path, MAX_PATH);

    char* last_sep = strrchr(exe_path, '\\');
    if (last_sep) *last_sep = 0;

    if (pchFolder && cchFolderBufferSize > 0) {
        strncpy_s(pchFolder, cchFolderBufferSize, exe_path, _TRUNCATE);
    }
    return (uint32)strlen(exe_path);
}

bool StarSteamApps::BIsAppInstalled(AppId_t appID)
{
    STAR_UNREFERENCED(appID);
    return true;
}

CSteamID StarSteamApps::GetAppOwner()
{
    return CSteamID(Settings::get().steam_id);
}

const char* StarSteamApps::GetLaunchQueryParam(const char* pchKey)
{
    STAR_UNREFERENCED(pchKey);
    return "";
}

bool StarSteamApps::GetDlcDownloadProgress(AppId_t nAppID, uint64* punBytesDownloaded, uint64* punBytesTotal)
{
    STAR_UNREFERENCED(nAppID);
    if (punBytesDownloaded) *punBytesDownloaded = 0;
    if (punBytesTotal) *punBytesTotal = 0;
    return false;
}

int StarSteamApps::GetAppBuildId() { return 1; }

uint32 StarSteamApps::GetInstalledDepots(DepotId_t* pvecDepots, uint32 cMaxDepots)
{
    return GetInstalledDepots(Settings::get().app_id, pvecDepots, cMaxDepots);
}

void StarSteamApps::RequestAppProofOfPurchaseKey(AppId_t nAppID) { STAR_UNREFERENCED(nAppID); }
void StarSteamApps::RequestAllProofOfPurchaseKeys() {}

SteamAPICall_t StarSteamApps::GetFileDetails(const char* pszFileName)
{
    STAR_UNREFERENCED(pszFileName);
    FileDetailsResult_t r{};
    r.m_eResult = k_EResultFileNotFound;
    return STAR_PostCallResult(FileDetailsResult_t::k_iCallback, &r, sizeof(r));
}

int StarSteamApps::GetLaunchCommandLine(char* pszCommandLine, int cubCommandLine)
{
    if (pszCommandLine && cubCommandLine > 0) pszCommandLine[0] = 0;
    return 0;
}

bool StarSteamApps::BIsSubscribedFromFamilySharing() { return false; }

bool StarSteamApps::BIsTimedTrial(uint32* punSecondsAllowed, uint32* punSecondsPlayed)
{
    if (punSecondsAllowed) *punSecondsAllowed = 0;
    if (punSecondsPlayed)  *punSecondsPlayed = 0;
    return false;
}

bool StarSteamApps::SetDlcContext(AppId_t nAppID) { STAR_UNREFERENCED(nAppID); return true; }

int StarSteamApps::GetNumBetas(int* pnAvailable, int* pnPrivate)
{
    if (pnAvailable) *pnAvailable = 0;
    if (pnPrivate)   *pnPrivate = 0;
    return 0;
}

bool StarSteamApps::SetActiveBeta(const char* pchBetaName) { STAR_UNREFERENCED(pchBetaName); return false; }

bool StarSteamApps::GetBetaInfo(int iBetaIndex, uint32* punFlags, uint32* punBuildID, char* pchBetaName, int cchBetaName, char* pchDescription, int cchDescription)
{
    STAR_UNREFERENCED(iBetaIndex); STAR_UNREFERENCED(punFlags); STAR_UNREFERENCED(punBuildID);
    STAR_UNREFERENCED(cchBetaName); STAR_UNREFERENCED(pchDescription); STAR_UNREFERENCED(cchDescription);
    if (pchBetaName && cchBetaName > 0) pchBetaName[0] = 0;
    return false;
}

bool StarSteamApps::GetBetaInfo(int iBetaIndex, uint32* punFlags, uint32* punBuildID, char* pchBetaName, int cchBetaName, char* pchDescription, int cchDescription, uint32* punLastUpdated)
{
    if (punLastUpdated) *punLastUpdated = 0;
    return GetBetaInfo(iBetaIndex, punFlags, punBuildID, pchBetaName, cchBetaName, pchDescription, cchDescription);
}
