#pragma once
#include "core/star_common.h"
#include "steam/isteamuserstats001.h"
#include "steam/isteamuserstats002.h"
#include "steam/isteamuserstats003.h"
#include "steam/isteamuserstats004.h"
#include "steam/isteamuserstats005.h"
#include "steam/isteamuserstats006.h"
#include "steam/isteamuserstats007.h"
#include "steam/isteamuserstats008.h"
#include "steam/isteamuserstats009.h"
#include "steam/isteamuserstats010.h"
#include "steam/isteamuserstats011.h"
#include "steam/isteamuserstats012.h"
#include <nlohmann/json.hpp>

struct AchievementState {
    bool achieved = false;
    uint32_t unlock_time = 0;
};

struct StatValue {
    enum Type { INT_TYPE, FLOAT_TYPE } type = INT_TYPE;
    int32_t int_val = 0;
    float float_val = 0.0f;
};

struct LeaderboardInfo {
    std::string name;
    ELeaderboardSortMethod sort_method = k_ELeaderboardSortMethodDescending;
    ELeaderboardDisplayType display_type = k_ELeaderboardDisplayTypeNumeric;
    int entry_count = 0;
};

class StarSteamUserStats :
    public ISteamUserStats001,
    public ISteamUserStats002,
    public ISteamUserStats003,
    public ISteamUserStats004,
    public ISteamUserStats005,
    public ISteamUserStats006,
    public ISteamUserStats007,
    public ISteamUserStats008,
    public ISteamUserStats009,
    public ISteamUserStats010,
    public ISteamUserStats011,
    public ISteamUserStats012,
    public ISteamUserStats {
public:
    static StarSteamUserStats& get();

    uint32 GetNumStats(CGameID nGameID) override;
    const char* GetStatName(CGameID nGameID, uint32 iStat) override;
    ESteamUserStatType GetStatType(CGameID nGameID, const char* pchName) override;
    uint32 GetNumAchievements(CGameID nGameID) override;
    const char* GetAchievementName(CGameID nGameID, uint32 iAchievement) override;
    bool RequestCurrentStats(CGameID nGameID) override;
    bool GetStat(CGameID nGameID, const char* pchName, int32* pData) override;
    bool GetStat(CGameID nGameID, const char* pchName, float* pData) override;
    bool SetStat(CGameID nGameID, const char* pchName, int32 nData) override;
    bool SetStat(CGameID nGameID, const char* pchName, float fData) override;
    bool UpdateAvgRateStat(CGameID nGameID, const char* pchName, float flCountThisSession, double dSessionLength) override;
    bool GetAchievement(CGameID nGameID, const char* pchName, bool* pbAchieved) override;
    bool SetAchievement(CGameID nGameID, const char* pchName) override;
    bool StoreStats(CGameID nGameID) override;
    bool ClearAchievement(CGameID nGameID, const char* pchName) override;
    int GetAchievementIcon(CGameID nGameID, const char* pchName) override;
    const char* GetAchievementDisplayAttribute(CGameID nGameID, const char* pchName, const char* pchKey) override;
    bool IndicateAchievementProgress(CGameID nGameID, const char* pchName, uint32 nCurProgress, uint32 nMaxProgress) override;

    uint32 GetNumGroupAchievements(CGameID nGameID) override;
    const char* GetGroupAchievementName(CGameID nGameID, uint32 iAchievement) override;
    bool GetGroupAchievement(CGameID nGameID, const char* pchName, bool* pbAchieved) override;
    bool SetGroupAchievement(CGameID nGameID, const char* pchName) override;
    bool ClearGroupAchievement(CGameID nGameID, const char* pchName) override;

    SteamAPICall_t UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, int32 nScore, int32* pScoreDetails, int cScoreDetailsCount) override;

    bool GetAchievementProgressLimits(const char* pchName, int32* pnMinProgress, int32* pnMaxProgress) override;
    bool GetAchievementProgressLimits(const char* pchName, float* pfMinProgress, float* pfMaxProgress) override;

    bool RequestCurrentStats() override;
    bool GetStat(const char* pchName, int32* pData) override;
    bool GetStat(const char* pchName, float* pData) override;
    bool SetStat(const char* pchName, int32 nData) override;
    bool SetStat(const char* pchName, float fData) override;
    bool UpdateAvgRateStat(const char* pchName, float flCountThisSession, double dSessionLength) override;
    bool GetAchievement(const char* pchName, bool* pbAchieved) override;
    bool SetAchievement(const char* pchName) override;
    bool ClearAchievement(const char* pchName) override;
    bool GetAchievementAndUnlockTime(const char* pchName, bool* pbAchieved, uint32* punUnlockTime) override;
    bool StoreStats() override;
    int GetAchievementIcon(const char* pchName) override;
    const char* GetAchievementDisplayAttribute(const char* pchName, const char* pchKey) override;
    bool IndicateAchievementProgress(const char* pchName, uint32 nCurProgress, uint32 nMaxProgress) override;
    uint32 GetNumAchievements() override;
    const char* GetAchievementName(uint32 iAchievement) override;
    SteamAPICall_t RequestUserStats(CSteamID steamIDUser) override;
    bool GetUserStat(CSteamID steamIDUser, const char* pchName, int32* pData) override;
    bool GetUserStat(CSteamID steamIDUser, const char* pchName, float* pData) override;
    bool GetUserAchievement(CSteamID steamIDUser, const char* pchName, bool* pbAchieved) override;
    bool GetUserAchievementAndUnlockTime(CSteamID steamIDUser, const char* pchName, bool* pbAchieved, uint32* punUnlockTime) override;
    bool ResetAllStats(bool bAchievementsToo) override;
    SteamAPICall_t FindOrCreateLeaderboard(const char* pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType) override;
    SteamAPICall_t FindLeaderboard(const char* pchLeaderboardName) override;
    const char* GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard) override;
    int GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard) override;
    ELeaderboardSortMethod GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard) override;
    ELeaderboardDisplayType GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard) override;
    SteamAPICall_t DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd) override;
    SteamAPICall_t DownloadLeaderboardEntriesForUsers(SteamLeaderboard_t hSteamLeaderboard, CSteamID* prgUsers, int cUsers) override;
    bool GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t* pLeaderboardEntry, int32* pDetails, int cDetailsMax) override;
    SteamAPICall_t UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32* pScoreDetails, int cScoreDetailsCount) override;
    SteamAPICall_t AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC) override;
    SteamAPICall_t GetNumberOfCurrentPlayers() override;
    SteamAPICall_t RequestGlobalAchievementPercentages() override;
    int GetMostAchievedAchievementInfo(char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved) override;
    int GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved) override;
    bool GetAchievementAchievedPercent(const char* pchName, float* pflPercent) override;
    SteamAPICall_t RequestGlobalStats(int nHistoryDays) override;
    bool GetGlobalStat(const char* pchStatName, int64* pData) override;
    bool GetGlobalStat(const char* pchStatName, double* pData) override;
    int32 GetGlobalStatHistory(const char* pchStatName, int64* pData, uint32 cubData) override;
    int32 GetGlobalStatHistory(const char* pchStatName, double* pData, uint32 cubData) override;

    void load_from_storage();
    void notify_achievement_unlock(const std::string& name);

private:
    StarSteamUserStats() = default;
    bool stats_loaded_ = false;
    std::unordered_map<std::string, AchievementState> achievements_;
    std::unordered_map<std::string, StatValue> stats_;
    std::vector<LeaderboardInfo> leaderboards_;
    std::mutex mutex_;

    LeaderboardInfo* find_leaderboard(SteamLeaderboard_t handle);
    SteamLeaderboard_t get_or_create_leaderboard(const std::string& name, ELeaderboardSortMethod sort, ELeaderboardDisplayType display);
};
