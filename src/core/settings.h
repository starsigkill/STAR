#pragma once
#include "core/star_common.h"

struct DlcEntry {
    uint32_t app_id;
    std::string name;
};

struct AchievementDef {
    std::string name;
    std::string display_name;
    std::string description;
    std::string icon_path;
    std::string icon_gray_path;
    bool hidden = false;
};

class Settings {
public:
    static Settings& get();

    void load(const std::string& settings_dir);

    uint32_t app_id = 0;
    std::string account_name = "STAR Player";
    uint64_t steam_id = 76561198000000001ULL;
    std::string language = "english";
    std::vector<std::string> supported_languages;
    std::string supported_languages_str;
    bool unlock_all_dlc = false;
    bool is_beta_branch = false;
    std::string branch_name = "public";
    std::vector<DlcEntry> dlc_list;
    std::vector<AchievementDef> achievements;
    bool overlay_enabled = true;

    std::string settings_dir;

private:
    Settings() = default;
};
