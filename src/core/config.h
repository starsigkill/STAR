#pragma once
#include "core/star_common.h"

class IniFile {
public:
    bool load(const std::string& path);
    std::string get(const std::string& section, const std::string& key, const std::string& def = "") const;
    int get_int(const std::string& section, const std::string& key, int def = 0) const;
    float get_float(const std::string& section, const std::string& key, float def = 0.0f) const;
    bool get_bool(const std::string& section, const std::string& key, bool def = false) const;

    std::vector<std::pair<std::string, std::string>> get_section(const std::string& section) const;

private:

    std::map<std::string, std::map<std::string, std::string>> data_;

    static std::string trim(const std::string& s);
    static std::string to_lower(const std::string& s);
};
