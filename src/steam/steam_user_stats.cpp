#include "steam/steam_user_stats.h"
#include "core/callbacks.h"
#include "core/settings.h"
#include "core/storage.h"
#include "steam/steam_utils.h"
#include "overlay/overlay.h"
#include "steam/isteamuserstats.h"
#include <thread>
#include <mmsystem.h>

StarSteamUserStats& StarSteamUserStats::get()
{
    static StarSteamUserStats instance;
    return instance;
}

void StarSteamUserStats::load_from_storage()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (stats_loaded_) return;
    stats_loaded_ = true;

    nlohmann::json ach_json;
    if (Storage::get().load_achievements(ach_json) && ach_json.is_object()) {
        for (auto it = ach_json.begin(); it != ach_json.end(); ++it) {
            AchievementState state;
            state.achieved = it.value().value("achieved", false);
            state.unlock_time = it.value().value("unlock_time", 0u);
            achievements_[it.key()] = state;
        }
    }

    nlohmann::json stats_json;
    if (Storage::get().load_stats(stats_json) && stats_json.is_object()) {
        for (auto it = stats_json.begin(); it != stats_json.end(); ++it) {
            StatValue sv;
            std::string type = it.value().value("type", "int");
            if (type == "float") {
                sv.type = StatValue::FLOAT_TYPE;
                sv.float_val = it.value().value("value", 0.0f);
            } else {
                sv.type = StatValue::INT_TYPE;
                sv.int_val = it.value().value("value", 0);
            }
            stats_[it.key()] = sv;
        }
    }
    STAR_LOG("UserStats loaded: %zu achievements, %zu stats", achievements_.size(), stats_.size());
}

bool StarSteamUserStats::RequestCurrentStats()
{
    load_from_storage();

    UserStatsReceived_t cb{};
    cb.m_nGameID = Settings::get().app_id;
    cb.m_eResult = k_EResultOK;
    cb.m_steamIDUser = CSteamID(Settings::get().steam_id);
    STAR_PostCallback(UserStatsReceived_t::k_iCallback, &cb, sizeof(cb));
    STAR_LOG("RequestCurrentStats -> queued UserStatsReceived_t");
    return true;
}

bool StarSteamUserStats::GetStat(const char* pchName, int32* pData)
{
    if (!pchName || !pData) return false;
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = stats_.find(pchName);
    if (it == stats_.end()) { *pData = 0; return false; }
    if (it->second.type == StatValue::FLOAT_TYPE) {
        *pData = (int32)it->second.float_val;
    } else {
        *pData = it->second.int_val;
    }
    return true;
}

bool StarSteamUserStats::GetStat(const char* pchName, float* pData)
{
    if (!pchName || !pData) return false;
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = stats_.find(pchName);
    if (it == stats_.end()) { *pData = 0.0f; return false; }
    if (it->second.type == StatValue::INT_TYPE) {
        *pData = (float)it->second.int_val;
    } else {
        *pData = it->second.float_val;
    }
    return true;
}

bool StarSteamUserStats::SetStat(const char* pchName, int32 nData)
{
    if (!pchName) return false;
    std::lock_guard<std::mutex> lock(mutex_);
    auto& sv = stats_[pchName];
    sv.type = StatValue::INT_TYPE;
    sv.int_val = nData;
    return true;
}

bool StarSteamUserStats::SetStat(const char* pchName, float fData)
{
    if (!pchName) return false;
    std::lock_guard<std::mutex> lock(mutex_);
    auto& sv = stats_[pchName];
    sv.type = StatValue::FLOAT_TYPE;
    sv.float_val = fData;
    return true;
}

bool StarSteamUserStats::UpdateAvgRateStat(const char* pchName, float flCountThisSession, double dSessionLength)
{
    if (!pchName || dSessionLength <= 0.0) return false;
    std::lock_guard<std::mutex> lock(mutex_);
    auto& sv = stats_[pchName];
    sv.type = StatValue::FLOAT_TYPE;

    float session_avg = (float)(flCountThisSession / dSessionLength);
    if (sv.float_val == 0.0f) {
        sv.float_val = session_avg;
    } else {
        sv.float_val = (sv.float_val + session_avg) * 0.5f;
    }
    return true;
}

bool StarSteamUserStats::GetAchievement(const char* pchName, bool* pbAchieved)
{
    if (!pchName) return false;
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = achievements_.find(pchName);
    if (pbAchieved) {
        *pbAchieved = (it != achievements_.end()) ? it->second.achieved : false;
    }

    auto& defs = Settings::get().achievements;
    for (auto& d : defs) {
        if (d.name == pchName) return true;
    }
    return (it != achievements_.end());
}

bool StarSteamUserStats::SetAchievement(const char* pchName)
{
    if (!pchName) return false;
    load_from_storage();
    bool was_newly_achieved = false;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto& state = achievements_[pchName];
        if (!state.achieved) {
            state.achieved = true;
            state.unlock_time = (uint32_t)time(nullptr);
            was_newly_achieved = true;
        }
    }
    if (was_newly_achieved) {
        {
            nlohmann::json ach_json = nlohmann::json::object();
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto& [name, state] : achievements_) {
                ach_json[name] = {
                    {"achieved", state.achieved},
                    {"unlock_time", state.unlock_time}
                };
            }
            Storage::get().save_achievements(ach_json);
        }

        UserAchievementStored_t cb{};
        cb.m_nGameID = Settings::get().app_id;
        cb.m_bGroupAchievement = false;
        strncpy_s(cb.m_rgchAchievementName, pchName, _TRUNCATE);
        cb.m_nCurProgress = 0;
        cb.m_nMaxProgress = 0;
        STAR_DispatchCallback(UserAchievementStored_t::k_iCallback, &cb, sizeof(cb));

        notify_achievement_unlock(pchName);
        STAR_LOG("Achievement unlocked: %s", pchName);
    }
    return true;
}

static void play_achievement_sound()
{
    std::string sound_path = Settings::get().settings_dir + "\\Sounds\\achievement.mp3";
    DWORD attr = GetFileAttributesA(sound_path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY)) return;

    std::thread([sound_path]() {
        std::string open_cmd = "open \"" + sound_path + "\" type mpegvideo alias star_ach";
        if (mciSendStringA(open_cmd.c_str(), nullptr, 0, nullptr) == 0) {
            mciSendStringA("play star_ach wait", nullptr, 0, nullptr);
            mciSendStringA("close star_ach", nullptr, 0, nullptr);
        }
    }).detach();
}

void StarSteamUserStats::notify_achievement_unlock(const std::string& name)
{

    auto& defs = Settings::get().achievements;
    for (auto& def : defs) {
        if (def.name == name) {

            std::vector<uint8_t> icon_rgba;
            int icon_w = 0, icon_h = 0;
            if (!def.icon_path.empty()) {
                std::string full_path = Settings::get().settings_dir + "\\" + def.icon_path;

                for (char& c : full_path) if (c == '/') c = '\\';
                int handle = StarSteamUtils::get().LoadImageFromFile(full_path);
                if (handle > 0) {
                    uint32 uw = 0, uh = 0;
                    StarSteamUtils::get().GetImageSize(handle, &uw, &uh);
                    icon_w = (int)uw;
                    icon_h = (int)uh;
                    icon_rgba.resize(uw * uh * 4);
                    StarSteamUtils::get().GetImageRGBA(handle, icon_rgba.data(), (int)icon_rgba.size());
                }
            }
            play_achievement_sound();
            StarOverlay::get().push_achievement(def.display_name, def.description, icon_rgba, icon_w, icon_h);
            return;
        }
    }

    play_achievement_sound();
    StarOverlay::get().push_achievement(name, "", {}, 0, 0);
}

bool StarSteamUserStats::ClearAchievement(const char* pchName)
{
    if (!pchName) return false;
    nlohmann::json ach_json = nlohmann::json::object();
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = achievements_.find(pchName);
        if (it != achievements_.end()) {
            it->second.achieved = false;
            it->second.unlock_time = 0;
        }
        for (auto& [name, state] : achievements_) {
            ach_json[name] = {
                {"achieved", state.achieved},
                {"unlock_time", state.unlock_time}
            };
        }
    }
    Storage::get().save_achievements(ach_json);
    return true;
}

bool StarSteamUserStats::GetAchievementAndUnlockTime(const char* pchName, bool* pbAchieved, uint32* punUnlockTime)
{
    if (!pchName) return false;
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = achievements_.find(pchName);
    if (it != achievements_.end()) {
        if (pbAchieved) *pbAchieved = it->second.achieved;
        if (punUnlockTime) *punUnlockTime = it->second.unlock_time;
    } else {
        if (pbAchieved) *pbAchieved = false;
        if (punUnlockTime) *punUnlockTime = 0;
    }
    return true;
}

bool StarSteamUserStats::StoreStats()
{

    {
        nlohmann::json ach_json = nlohmann::json::object();
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& [name, state] : achievements_) {
            ach_json[name] = {
                {"achieved", state.achieved},
                {"unlock_time", state.unlock_time}
            };
        }
        Storage::get().save_achievements(ach_json);

        nlohmann::json stats_json = nlohmann::json::object();
        for (auto& [name, sv] : stats_) {
            if (sv.type == StatValue::FLOAT_TYPE) {
                stats_json[name] = {{"type", "float"}, {"value", sv.float_val}};
            } else {
                stats_json[name] = {{"type", "int"}, {"value", sv.int_val}};
            }
        }
        Storage::get().save_stats(stats_json);
    }

    UserStatsStored_t cb{};
    cb.m_nGameID = Settings::get().app_id;
    cb.m_eResult = k_EResultOK;
    STAR_PostCallback(UserStatsStored_t::k_iCallback, &cb, sizeof(cb));
    STAR_LOG("StoreStats: saved");
    return true;
}

int StarSteamUserStats::GetAchievementIcon(const char* pchName)
{
    if (!pchName) return 0;
    auto& defs = Settings::get().achievements;
    for (auto& def : defs) {
        if (def.name == pchName) {
            if (!def.icon_path.empty()) {
                std::string full = Settings::get().settings_dir + "\\" + def.icon_path;
                for (char& c : full) if (c == '/') c = '\\';
                return StarSteamUtils::get().LoadImageFromFile(full);
            }
        }
    }
    return 0;
}

const char* StarSteamUserStats::GetAchievementDisplayAttribute(const char* pchName, const char* pchKey)
{
    if (!pchName || !pchKey) return "";
    auto& defs = Settings::get().achievements;
    for (auto& def : defs) {
        if (def.name == pchName) {
            std::string k(pchKey);
            if (k == "name") return def.display_name.c_str();
            if (k == "desc") return def.description.c_str();
            if (k == "hidden") return def.hidden ? "1" : "0";
        }
    }
    return "";
}

bool StarSteamUserStats::IndicateAchievementProgress(const char* pchName, uint32 nCurProgress, uint32 nMaxProgress)
{
    if (!pchName) return false;
    UserAchievementStored_t cb{};
    cb.m_nGameID = Settings::get().app_id;
    cb.m_bGroupAchievement = false;
    strncpy_s(cb.m_rgchAchievementName, pchName, _TRUNCATE);
    cb.m_nCurProgress = nCurProgress;
    cb.m_nMaxProgress = nMaxProgress;
    STAR_DispatchCallback(UserAchievementStored_t::k_iCallback, &cb, sizeof(cb));
    return true;
}

uint32 StarSteamUserStats::GetNumAchievements()
{
    return (uint32)Settings::get().achievements.size();
}

const char* StarSteamUserStats::GetAchievementName(uint32 iAchievement)
{
    auto& defs = Settings::get().achievements;
    if (iAchievement >= defs.size()) return "";
    return defs[iAchievement].name.c_str();
}

SteamAPICall_t StarSteamUserStats::RequestUserStats(CSteamID steamIDUser)
{
    UserStatsReceived_t result{};
    result.m_nGameID = Settings::get().app_id;
    result.m_eResult = k_EResultOK;
    result.m_steamIDUser = steamIDUser;
    return STAR_PostCallResult(UserStatsReceived_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamUserStats::GetUserStat(CSteamID steamIDUser, const char* pchName, int32* pData)
{
    if (steamIDUser == CSteamID(Settings::get().steam_id)) {
        return GetStat(pchName, pData);
    }
    if (pData) *pData = 0;
    return false;
}

bool StarSteamUserStats::GetUserStat(CSteamID steamIDUser, const char* pchName, float* pData)
{
    if (steamIDUser == CSteamID(Settings::get().steam_id)) {
        return GetStat(pchName, pData);
    }
    if (pData) *pData = 0.0f;
    return false;
}

bool StarSteamUserStats::GetUserAchievement(CSteamID steamIDUser, const char* pchName, bool* pbAchieved)
{
    if (steamIDUser == CSteamID(Settings::get().steam_id)) {
        return GetAchievement(pchName, pbAchieved);
    }
    if (pbAchieved) *pbAchieved = false;
    return false;
}

bool StarSteamUserStats::GetUserAchievementAndUnlockTime(CSteamID steamIDUser, const char* pchName, bool* pbAchieved, uint32* punUnlockTime)
{
    if (steamIDUser == CSteamID(Settings::get().steam_id)) {
        return GetAchievementAndUnlockTime(pchName, pbAchieved, punUnlockTime);
    }
    if (pbAchieved) *pbAchieved = false;
    if (punUnlockTime) *punUnlockTime = 0;
    return false;
}

bool StarSteamUserStats::ResetAllStats(bool bAchievementsToo)
{
    std::lock_guard<std::mutex> lock(mutex_);
    stats_.clear();
    if (bAchievementsToo) achievements_.clear();

    Storage::get().save_stats(nlohmann::json::object());
    if (bAchievementsToo) Storage::get().save_achievements(nlohmann::json::object());
    return true;
}

LeaderboardInfo* StarSteamUserStats::find_leaderboard(SteamLeaderboard_t handle)
{
    if (handle == 0 || handle > leaderboards_.size()) return nullptr;
    return &leaderboards_[(size_t)(handle - 1)];
}

SteamLeaderboard_t StarSteamUserStats::get_or_create_leaderboard(const std::string& name, ELeaderboardSortMethod sort, ELeaderboardDisplayType display)
{
    for (size_t i = 0; i < leaderboards_.size(); ++i) {
        if (leaderboards_[i].name == name) return (SteamLeaderboard_t)(i + 1);
    }
    LeaderboardInfo info;
    info.name = name;
    info.sort_method = sort;
    info.display_type = display;
    info.entry_count = 0;
    leaderboards_.push_back(std::move(info));
    return (SteamLeaderboard_t)leaderboards_.size();
}

SteamAPICall_t StarSteamUserStats::FindOrCreateLeaderboard(const char* pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType)
{
    if (!pchLeaderboardName) return k_uAPICallInvalid;
    SteamLeaderboard_t handle = get_or_create_leaderboard(pchLeaderboardName, eLeaderboardSortMethod, eLeaderboardDisplayType);
    LeaderboardFindResult_t result{};
    result.m_hSteamLeaderboard = handle;
    result.m_bLeaderboardFound = 1;
    return STAR_PostCallResult(LeaderboardFindResult_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamUserStats::FindLeaderboard(const char* pchLeaderboardName)
{
    if (!pchLeaderboardName) return k_uAPICallInvalid;
    SteamLeaderboard_t handle = get_or_create_leaderboard(pchLeaderboardName, k_ELeaderboardSortMethodDescending, k_ELeaderboardDisplayTypeNumeric);
    LeaderboardFindResult_t result{};
    result.m_hSteamLeaderboard = handle;
    result.m_bLeaderboardFound = 1;
    return STAR_PostCallResult(LeaderboardFindResult_t::k_iCallback, &result, sizeof(result));
}

const char* StarSteamUserStats::GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard)
{
    auto* lb = find_leaderboard(hSteamLeaderboard);
    return lb ? lb->name.c_str() : "";
}

int StarSteamUserStats::GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard)
{
    auto* lb = find_leaderboard(hSteamLeaderboard);
    return lb ? lb->entry_count : 0;
}

ELeaderboardSortMethod StarSteamUserStats::GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard)
{
    auto* lb = find_leaderboard(hSteamLeaderboard);
    return lb ? lb->sort_method : k_ELeaderboardSortMethodNone;
}

ELeaderboardDisplayType StarSteamUserStats::GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard)
{
    auto* lb = find_leaderboard(hSteamLeaderboard);
    return lb ? lb->display_type : k_ELeaderboardDisplayTypeNone;
}

SteamAPICall_t StarSteamUserStats::DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd)
{
    STAR_UNREFERENCED(nRangeStart); STAR_UNREFERENCED(nRangeEnd); STAR_UNREFERENCED(eLeaderboardDataRequest);
    LeaderboardScoresDownloaded_t result{};
    result.m_hSteamLeaderboard = hSteamLeaderboard;
    result.m_hSteamLeaderboardEntries = 0;
    result.m_cEntryCount = 0;
    return STAR_PostCallResult(LeaderboardScoresDownloaded_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamUserStats::DownloadLeaderboardEntriesForUsers(SteamLeaderboard_t hSteamLeaderboard, CSteamID* prgUsers, int cUsers)
{
    STAR_UNREFERENCED(prgUsers); STAR_UNREFERENCED(cUsers);
    LeaderboardScoresDownloaded_t result{};
    result.m_hSteamLeaderboard = hSteamLeaderboard;
    result.m_hSteamLeaderboardEntries = 0;
    result.m_cEntryCount = 0;
    return STAR_PostCallResult(LeaderboardScoresDownloaded_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamUserStats::GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t* pLeaderboardEntry, int32* pDetails, int cDetailsMax)
{
    STAR_UNREFERENCED(hSteamLeaderboardEntries); STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(pDetails); STAR_UNREFERENCED(cDetailsMax);
    if (pLeaderboardEntry) memset(pLeaderboardEntry, 0, sizeof(*pLeaderboardEntry));
    return false;
}

SteamAPICall_t StarSteamUserStats::UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32* pScoreDetails, int cScoreDetailsCount)
{
    STAR_UNREFERENCED(eLeaderboardUploadScoreMethod); STAR_UNREFERENCED(pScoreDetails); STAR_UNREFERENCED(cScoreDetailsCount);
    LeaderboardScoreUploaded_t result{};
    result.m_bSuccess = 1;
    result.m_hSteamLeaderboard = hSteamLeaderboard;
    result.m_nScore = nScore;
    result.m_bScoreChanged = 1;
    result.m_nGlobalRankNew = 1;
    result.m_nGlobalRankPrevious = 1;
    return STAR_PostCallResult(LeaderboardScoreUploaded_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamUserStats::AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
{
    STAR_UNREFERENCED(hUGC);
    LeaderboardUGCSet_t result{};
    result.m_eResult = k_EResultOK;
    result.m_hSteamLeaderboard = hSteamLeaderboard;
    return STAR_PostCallResult(LeaderboardUGCSet_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamUserStats::GetNumberOfCurrentPlayers()
{
    NumberOfCurrentPlayers_t result{};
    result.m_bSuccess = 1;
    result.m_cPlayers = 1;
    return STAR_PostCallResult(NumberOfCurrentPlayers_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamUserStats::RequestGlobalAchievementPercentages()
{
    GlobalAchievementPercentagesReady_t result{};
    result.m_nGameID = Settings::get().app_id;
    result.m_eResult = k_EResultOK;
    return STAR_PostCallResult(GlobalAchievementPercentagesReady_t::k_iCallback, &result, sizeof(result));
}

int StarSteamUserStats::GetMostAchievedAchievementInfo(char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved)
{
    STAR_UNREFERENCED(pchName); STAR_UNREFERENCED(unNameBufLen);
    STAR_UNREFERENCED(pflPercent); STAR_UNREFERENCED(pbAchieved);
    return -1;
}

int StarSteamUserStats::GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved)
{
    STAR_UNREFERENCED(iIteratorPrevious); STAR_UNREFERENCED(pchName); STAR_UNREFERENCED(unNameBufLen);
    STAR_UNREFERENCED(pflPercent); STAR_UNREFERENCED(pbAchieved);
    return -1;
}

bool StarSteamUserStats::GetAchievementAchievedPercent(const char* pchName, float* pflPercent)
{
    STAR_UNREFERENCED(pchName);
    if (pflPercent) *pflPercent = 0.0f;
    return false;
}

SteamAPICall_t StarSteamUserStats::RequestGlobalStats(int nHistoryDays)
{
    STAR_UNREFERENCED(nHistoryDays);
    GlobalStatsReceived_t result{};
    result.m_nGameID = Settings::get().app_id;
    result.m_eResult = k_EResultOK;
    return STAR_PostCallResult(GlobalStatsReceived_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamUserStats::GetGlobalStat(const char* pchStatName, int64* pData)
{
    STAR_UNREFERENCED(pchStatName);
    if (pData) *pData = 0;
    return false;
}

bool StarSteamUserStats::GetGlobalStat(const char* pchStatName, double* pData)
{
    STAR_UNREFERENCED(pchStatName);
    if (pData) *pData = 0.0;
    return false;
}

int32 StarSteamUserStats::GetGlobalStatHistory(const char* pchStatName, int64* pData, uint32 cubData)
{
    STAR_UNREFERENCED(pchStatName); STAR_UNREFERENCED(pData); STAR_UNREFERENCED(cubData);
    return 0;
}

int32 StarSteamUserStats::GetGlobalStatHistory(const char* pchStatName, double* pData, uint32 cubData)
{
    STAR_UNREFERENCED(pchStatName); STAR_UNREFERENCED(pData); STAR_UNREFERENCED(cubData);
    return 0;
}

uint32 StarSteamUserStats::GetNumStats(CGameID nGameID)
{
    STAR_UNREFERENCED(nGameID);
    std::lock_guard<std::mutex> lock(mutex_);
    return (uint32)stats_.size();
}

const char* StarSteamUserStats::GetStatName(CGameID nGameID, uint32 iStat)
{
    STAR_UNREFERENCED(nGameID);
    std::lock_guard<std::mutex> lock(mutex_);
    if (iStat >= stats_.size()) return "";
    auto it = stats_.begin();
    std::advance(it, iStat);
    return it->first.c_str();
}

ESteamUserStatType StarSteamUserStats::GetStatType(CGameID nGameID, const char* pchName)
{
    STAR_UNREFERENCED(nGameID);
    if (!pchName) return k_ESteamUserStatTypeINT;
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = stats_.find(pchName);
    if (it != stats_.end() && it->second.type == StatValue::FLOAT_TYPE)
        return k_ESteamUserStatTypeFLOAT;
    return k_ESteamUserStatTypeINT;
}

uint32 StarSteamUserStats::GetNumAchievements(CGameID nGameID) { STAR_UNREFERENCED(nGameID); return GetNumAchievements(); }
const char* StarSteamUserStats::GetAchievementName(CGameID nGameID, uint32 i) { STAR_UNREFERENCED(nGameID); return GetAchievementName(i); }
bool StarSteamUserStats::RequestCurrentStats(CGameID nGameID) { STAR_UNREFERENCED(nGameID); return RequestCurrentStats(); }
bool StarSteamUserStats::GetStat(CGameID nGameID, const char* n, int32* p) { STAR_UNREFERENCED(nGameID); return GetStat(n, p); }
bool StarSteamUserStats::GetStat(CGameID nGameID, const char* n, float* p) { STAR_UNREFERENCED(nGameID); return GetStat(n, p); }
bool StarSteamUserStats::SetStat(CGameID nGameID, const char* n, int32 d) { STAR_UNREFERENCED(nGameID); return SetStat(n, d); }
bool StarSteamUserStats::SetStat(CGameID nGameID, const char* n, float d) { STAR_UNREFERENCED(nGameID); return SetStat(n, d); }
bool StarSteamUserStats::UpdateAvgRateStat(CGameID nGameID, const char* n, float c, double s) { STAR_UNREFERENCED(nGameID); return UpdateAvgRateStat(n, c, s); }
bool StarSteamUserStats::GetAchievement(CGameID nGameID, const char* n, bool* a) { STAR_UNREFERENCED(nGameID); return GetAchievement(n, a); }
bool StarSteamUserStats::SetAchievement(CGameID nGameID, const char* n) { STAR_UNREFERENCED(nGameID); return SetAchievement(n); }
bool StarSteamUserStats::StoreStats(CGameID nGameID) { STAR_UNREFERENCED(nGameID); return StoreStats(); }
bool StarSteamUserStats::ClearAchievement(CGameID nGameID, const char* n) { STAR_UNREFERENCED(nGameID); return ClearAchievement(n); }
int StarSteamUserStats::GetAchievementIcon(CGameID nGameID, const char* n) { STAR_UNREFERENCED(nGameID); return GetAchievementIcon(n); }
const char* StarSteamUserStats::GetAchievementDisplayAttribute(CGameID nGameID, const char* n, const char* k) { STAR_UNREFERENCED(nGameID); return GetAchievementDisplayAttribute(n, k); }
bool StarSteamUserStats::IndicateAchievementProgress(CGameID nGameID, const char* n, uint32 c, uint32 m) { STAR_UNREFERENCED(nGameID); return IndicateAchievementProgress(n, c, m); }

uint32 StarSteamUserStats::GetNumGroupAchievements(CGameID nGameID) { STAR_UNREFERENCED(nGameID); return 0; }
const char* StarSteamUserStats::GetGroupAchievementName(CGameID nGameID, uint32 i) { STAR_UNREFERENCED(nGameID); STAR_UNREFERENCED(i); return ""; }
bool StarSteamUserStats::GetGroupAchievement(CGameID nGameID, const char* n, bool* a) { STAR_UNREFERENCED(nGameID); return GetAchievement(n, a); }
bool StarSteamUserStats::SetGroupAchievement(CGameID nGameID, const char* n) { STAR_UNREFERENCED(nGameID); return SetAchievement(n); }
bool StarSteamUserStats::ClearGroupAchievement(CGameID nGameID, const char* n) { STAR_UNREFERENCED(nGameID); return ClearAchievement(n); }

SteamAPICall_t StarSteamUserStats::UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, int32 nScore, int32* pScoreDetails, int cScoreDetailsCount)
{
    return UploadLeaderboardScore(hSteamLeaderboard, k_ELeaderboardUploadScoreMethodKeepBest, nScore, pScoreDetails, cScoreDetailsCount);
}

bool StarSteamUserStats::GetAchievementProgressLimits(const char* pchName, int32* pnMinProgress, int32* pnMaxProgress)
{
    STAR_UNREFERENCED(pchName);
    if (pnMinProgress) *pnMinProgress = 0;
    if (pnMaxProgress) *pnMaxProgress = 0;
    return false;
}

bool StarSteamUserStats::GetAchievementProgressLimits(const char* pchName, float* pfMinProgress, float* pfMaxProgress)
{
    STAR_UNREFERENCED(pchName);
    if (pfMinProgress) *pfMinProgress = 0.0f;
    if (pfMaxProgress) *pfMaxProgress = 0.0f;
    return false;
}
