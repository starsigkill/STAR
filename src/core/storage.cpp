#include "core/storage.h"

Storage& Storage::get()
{
    static Storage instance;
    return instance;
}

void Storage::init(uint32_t app_id, uint64_t steam_id)
{

    char appdata[MAX_PATH] = {};
    DWORD len = GetEnvironmentVariableA("APPDATA", appdata, MAX_PATH);
    std::string roaming = (len > 0) ? std::string(appdata) : "C:\\Users\\Default\\AppData\\Roaming";

    base_path_ = roaming + "\\STAR\\" + std::to_string(app_id) + "\\" + std::to_string(steam_id);
    remote_dir_ = base_path_ + "\\remote";

    ensure_dir(base_path_);
    ensure_dir(remote_dir_);

    STAR_LOG("Storage initialized at: %s", base_path_.c_str());
}

bool Storage::ensure_dir(const std::string& path)
{
    try {
        std::filesystem::create_directories(path);
        return true;
    } catch (...) {
        return false;
    }
}

bool Storage::write_json(const std::string& path, const nlohmann::json& data)
{
    std::ofstream f(path);
    if (!f.is_open()) return false;
    f << data.dump(2);
    return true;
}

bool Storage::read_json(const std::string& path, nlohmann::json& out)
{
    std::ifstream f(path);
    if (!f.is_open()) return false;
    try {
        f >> out;
        return true;
    } catch (...) {
        return false;
    }
}

bool Storage::load_achievements(nlohmann::json& out)
{
    return read_json(base_path_ + "\\achievements.json", out);
}

bool Storage::save_achievements(const nlohmann::json& data)
{
    return write_json(base_path_ + "\\achievements.json", data);
}

bool Storage::load_stats(nlohmann::json& out)
{
    return read_json(base_path_ + "\\stats.json", out);
}

bool Storage::save_stats(const nlohmann::json& data)
{
    return write_json(base_path_ + "\\stats.json", data);
}

std::string Storage::remote_path(const std::string& filename)
{

    std::string safe = filename;
    for (char& c : safe) {
        if (c == '/' || c == '\\') c = '_';
    }
    return remote_dir_ + "\\" + safe;
}

bool Storage::write_remote_file(const std::string& filename, const void* data, size_t size)
{
    std::string path = remote_path(filename);
    std::ofstream f(path, std::ios::binary);
    if (!f.is_open()) return false;
    if (data && size > 0) {
        f.write(reinterpret_cast<const char*>(data), size);
    }
    return f.good();
}

bool Storage::read_remote_file(const std::string& filename, std::vector<uint8_t>& out)
{
    std::string path = remote_path(filename);
    std::ifstream f(path, std::ios::binary | std::ios::ate);
    if (!f.is_open()) return false;
    size_t sz = (size_t)f.tellg();
    f.seekg(0);
    out.resize(sz);
    f.read(reinterpret_cast<char*>(out.data()), sz);
    return true;
}

bool Storage::remote_file_exists(const std::string& filename)
{
    std::string path = remote_path(filename);
    return std::filesystem::exists(path);
}

bool Storage::delete_remote_file(const std::string& filename)
{
    std::string path = remote_path(filename);
    std::error_code ec;
    return std::filesystem::remove(path, ec);
}

std::vector<std::string> Storage::list_remote_files()
{
    std::vector<std::string> files;
    std::error_code ec;
    for (auto& entry : std::filesystem::directory_iterator(remote_dir_, ec)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

int64_t Storage::remote_file_size(const std::string& filename)
{
    std::string path = remote_path(filename);
    std::error_code ec;
    auto sz = std::filesystem::file_size(path, ec);
    if (ec) return -1;
    return (int64_t)sz;
}
