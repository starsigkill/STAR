#pragma once
#include "core/star_common.h"
#include "steam/isteamapps001.h"
#include "steam/isteamapps002.h"
#include "steam/isteamapps003.h"
#include "steam/isteamapps004.h"
#include "steam/isteamapps005.h"
#include "steam/isteamapps006.h"
#include "steam/isteamapps007.h"
#include "steam/isteamapps008.h"

class StarSteamApps :
    public ISteamApps001,
    public ISteamApps002,
    public ISteamApps003,
    public ISteamApps004,
    public ISteamApps005,
    public ISteamApps006,
    public ISteamApps007,
    public ISteamApps008,
    public ISteamApps {
public:
    static StarSteamApps& get();

    int GetAppData(AppId_t nAppID, const char* pchKey, char* pchValue, int cchValueMax) override;

    bool BIsSubscribed() override;
    bool BIsLowViolence() override;
    bool BIsCybercafe() override;
    bool BIsVACBanned() override;
    const char* GetCurrentGameLanguage() override;
    const char* GetAvailableGameLanguages() override;
    bool BIsSubscribedApp(AppId_t appID) override;

    bool BIsDlcInstalled(AppId_t appID) override;

    uint32 GetEarliestPurchaseUnixTime(AppId_t nAppID) override;
    bool BIsSubscribedFromFreeWeekend() override;
    int GetDLCCount() override;
    bool BGetDLCDataByIndex(int iDLC, AppId_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize) override;
    void InstallDLC(AppId_t nAppID) override;
    void UninstallDLC(AppId_t nAppID) override;

    void RequestAppProofOfPurchaseKey_OLD(AppId_t nAppID) override;

    bool GetCurrentBetaName(char* pchName, int cchNameBufferSize) override;
    bool MarkContentCorrupt(bool bMissingFilesOnly) override;

    uint32 GetInstalledDepots(DepotId_t* pvecDepots, uint32 cMaxDepots) override;

    uint32 GetInstalledDepots(AppId_t appID, DepotId_t* pvecDepots, uint32 cMaxDepots) override;
    uint32 GetAppInstallDir(AppId_t appID, char* pchFolder, uint32 cchFolderBufferSize) override;
    bool BIsAppInstalled(AppId_t appID) override;

    CSteamID GetAppOwner() override;
    const char* GetLaunchQueryParam(const char* pchKey) override;

    bool GetDlcDownloadProgress(AppId_t nAppID, uint64* punBytesDownloaded, uint64* punBytesTotal) override;
    int GetAppBuildId() override;

    void RequestAppProofOfPurchaseKey(AppId_t nAppID) override;
    void RequestAllProofOfPurchaseKeys() override;
    SteamAPICall_t GetFileDetails(const char* pszFileName) override;
    int GetLaunchCommandLine(char* pszCommandLine, int cubCommandLine) override;
    bool BIsSubscribedFromFamilySharing() override;
    bool BIsTimedTrial(uint32* punSecondsAllowed, uint32* punSecondsPlayed) override;
    bool SetDlcContext(AppId_t nAppID) override;
    int GetNumBetas(int* pnAvailable, int* pnPrivate) override;
    bool SetActiveBeta(const char* pchBetaName) override;

    bool GetBetaInfo(int iBetaIndex, uint32* punFlags, uint32* punBuildID, char* pchBetaName, int cchBetaName, char* pchDescription, int cchDescription) override;

    bool GetBetaInfo(int iBetaIndex, uint32* punFlags, uint32* punBuildID, char* pchBetaName, int cchBetaName, char* pchDescription, int cchDescription, uint32* punLastUpdated) override;

private:
    StarSteamApps() = default;
};
