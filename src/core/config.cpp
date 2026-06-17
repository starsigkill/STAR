#include "core/config.h"

std::string IniFile::trim(const std::string& s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::string IniFile::to_lower(const std::string& s)
{
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return (char)tolower(c); });
    return r;
}

bool IniFile::load(const std::string& path)
{
    std::ifstream f(path);
    if (!f.is_open()) {
        return false;
    }

    std::string current_section;
    std::string line;
    bool first_line = true;
    while (std::getline(f, line)) {
        if (first_line) {
            first_line = false;
            if (line.size() >= 3 &&
                (unsigned char)line[0] == 0xEF &&
                (unsigned char)line[1] == 0xBB &&
                (unsigned char)line[2] == 0xBF) {
                line = line.substr(3);
            }
        }
        line = trim(line);
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;
        if (line[0] == '[') {
            size_t end = line.find(']');
            if (end != std::string::npos) {
                current_section = trim(line.substr(1, end - 1));
            }
            continue;
        }
        size_t eq = line.find('=');
        if (eq != std::string::npos) {
            std::string key = trim(line.substr(0, eq));
            std::string val = trim(line.substr(eq + 1));

            size_t comment = val.find(';');
            if (comment != std::string::npos) {
                val = trim(val.substr(0, comment));
            }
            if (!key.empty()) {
                data_[current_section][key] = val;
            }
        }
    }
    return true;
}

std::string IniFile::get(const std::string& section, const std::string& key, const std::string& def) const
{
    auto sit = data_.find(section);
    if (sit == data_.end()) return def;
    auto kit = sit->second.find(key);
    if (kit == sit->second.end()) return def;
    return kit->second;
}

int IniFile::get_int(const std::string& section, const std::string& key, int def) const
{
    std::string v = get(section, key, "");
    if (v.empty()) return def;
    try { return std::stoi(v); } catch (...) { return def; }
}

float IniFile::get_float(const std::string& section, const std::string& key, float def) const
{
    std::string v = get(section, key, "");
    if (v.empty()) return def;
    try { return std::stof(v); } catch (...) { return def; }
}

bool IniFile::get_bool(const std::string& section, const std::string& key, bool def) const
{
    std::string v = get(section, key, "");
    if (v.empty()) return def;
    if (v == "1" || v == "true" || v == "yes" || v == "on") return true;
    if (v == "0" || v == "false" || v == "no" || v == "off") return false;
    return def;
}

std::vector<std::pair<std::string, std::string>> IniFile::get_section(const std::string& section) const
{
    std::vector<std::pair<std::string, std::string>> result;
    auto sit = data_.find(section);
    if (sit == data_.end()) return result;
    for (auto& kv : sit->second) {
        result.push_back({kv.first, kv.second});
    }
    return result;
}
