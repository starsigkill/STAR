#include "core/settings.h"
#include "core/config.h"
#include "core/art_stamp.h"
#include <nlohmann/json.hpp>

Settings& Settings::get()
{
    static Settings instance;
    return instance;
}

void Settings::load(const std::string& dir)
{
    settings_dir = dir;
    STAR_LOG("Settings::load from %s", dir.c_str());
    stamp_star_configs(dir);

    {

        std::string appid_path = dir + "\\steam_appid.txt";
        std::ifstream f(appid_path);
        if (f.is_open()) {
            std::string s;
            std::getline(f, s);

            while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' '))
                s.pop_back();
            try { app_id = (uint32_t)std::stoul(s); } catch (...) {}
        }
    }

    if (app_id == 0) {
        std::string stripped = dir;
        while (!stripped.empty() && (stripped.back() == '\\' || stripped.back() == '/'))
            stripped.pop_back();

        std::string parent;
        size_t last_slash = stripped.find_last_of("\\/");
        if (last_slash != std::string::npos) {
            parent = stripped.substr(0, last_slash);
        } else {
            parent = stripped;
        }
        std::string appid_path = parent + "\\steam_appid.txt";
        std::ifstream f(appid_path);
        if (f.is_open()) {
            std::string s;
            std::getline(f, s);
            while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' '))
                s.pop_back();
            try { app_id = (uint32_t)std::stoul(s); } catch (...) {}
        }
    }

    STAR_LOG("App ID: %u", app_id);

    {
        IniFile ini;
        if (ini.load(dir + "\\identity.star")) {
            account_name = ini.get("", "display_name", "STAR Player");
            language     = ini.get("", "locale",       "english");
            std::transform(language.begin(), language.end(), language.begin(), [](unsigned char c) { return (char)tolower(c); });
            std::string sid_str = ini.get("", "xuid", "");
            if (!sid_str.empty()) {
                try {
                    uint64_t parsed = std::stoull(sid_str);
                    if (parsed > 76561190000000000ULL) steam_id = parsed;
                } catch (...) {}
            }
        }
    }

    {
        supported_languages.clear();
        IniFile ini;
        if (ini.load(dir + "\\languages.star")) {
            auto langs = ini.get_section("languages");
            if (langs.empty()) {
                langs = ini.get_section("");
            }
            for (const auto& kv : langs) {
                std::string lang = kv.first;
                std::transform(lang.begin(), lang.end(), lang.begin(), [](unsigned char c) { return (char)tolower(c); });
                if (!lang.empty()) {
                    supported_languages.push_back(lang);
                }
            }
        }

        bool lang_found = false;
        for (const auto& l : supported_languages) {
            if (l == language) {
                lang_found = true;
                break;
            }
        }
        if (!lang_found) {
            if (!supported_languages.empty()) {
                STAR_LOG("Configured language '%s' not found in languages.star. Falling back to '%s'", language.c_str(), supported_languages.front().c_str());
                language = supported_languages.front();
            } else {
                supported_languages.push_back(language);
            }
        }

        supported_languages_str.clear();
        for (size_t i = 0; i < supported_languages.size(); ++i) {
            if (i > 0) {
                supported_languages_str += ",";
            }
            supported_languages_str += supported_languages[i];
        }
    }

    {
        IniFile ini;
        if (ini.load(dir + "\\game.star")) {
            is_beta_branch = ini.get_bool("", "beta",  false);
            branch_name    = ini.get("",     "branch", "public");
            unlock_all_dlc = ini.get_bool("", "dlc.unlock_all", false);

            for (auto& [k, v] : ini.get_section("")) {
                if (k.size() > 4 && k.substr(0, 4) == "dlc." && k != "dlc.unlock_all") {
                    try {
                        uint32_t dlc_id = (uint32_t)std::stoul(k.substr(4));
                        DlcEntry entry; entry.app_id = dlc_id; entry.name = v;
                        dlc_list.push_back(entry);
                    } catch (...) {}
                }
            }
        }
    }

    {
        IniFile ini;
        if (ini.load(dir + "\\overlay.star")) {
            overlay_enabled = ini.get_bool("", "enabled", true);
        }
    }

    {
        std::string ach_path = dir + "\\achievements.json";
        std::ifstream f(ach_path);
        if (f.is_open()) {
            try {
                nlohmann::json j;
                f >> j;
                if (j.is_array()) {
                    for (auto& item : j) {
                        AchievementDef def;
                        def.name = item.value("name", "");
                        def.display_name = item.value("displayName", item.value("display_name", def.name));
                        def.description = item.value("description", "");
                        def.icon_path = item.value("icon", "");
                        def.icon_gray_path = item.value("icongray", item.value("icon_gray", ""));
                        std::string hidden_str = item.value("hidden", "0");
                        def.hidden = (hidden_str == "1" || hidden_str == "true");
                        if (!def.name.empty()) {
                            achievements.push_back(def);
                        }
                    }
                }
            } catch (...) {
                STAR_LOG("Failed to parse achievements.json");
            }
        }
    }

    STAR_LOG("Settings loaded: app_id=%u name='%s' achievements=%zu dlcs=%zu",
        app_id, account_name.c_str(), achievements.size(), dlc_list.size());
}
