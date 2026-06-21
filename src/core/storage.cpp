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

static bool create_dir_recursive(const std::string& path)
{
    if (path.empty()) return false;
    
    DWORD attr = GetFileAttributesA(path.c_str());
    if (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY)) {
        return true;
    }

    size_t last_slash = path.find_last_of("\\/");
    if (last_slash != std::string::npos) {
        std::string parent = path.substr(0, last_slash);
        if (!parent.empty() && parent.back() != ':') {
            if (!create_dir_recursive(parent)) return false;
        }
    }

    return CreateDirectoryA(path.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS;
}

bool Storage::ensure_dir(const std::string& path)
{
    return create_dir_recursive(path);
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
    DWORD attr = GetFileAttributesA(path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

bool Storage::delete_remote_file(const std::string& filename)
{
    std::string path = remote_path(filename);
    return DeleteFileA(path.c_str()) != 0;
}

std::vector<std::string> Storage::list_remote_files()
{
    std::vector<std::string> files;
    std::string search_path = remote_dir_ + "\\*";
    WIN32_FIND_DATAA find_data;
    HANDLE hFind = FindFirstFileA(search_path.c_str(), &find_data);
    if (hFind == INVALID_HANDLE_VALUE) return files;

    do {
        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        files.push_back(find_data.cFileName);
    } while (FindNextFileA(hFind, &find_data));

    FindClose(hFind);
    return files;
}

int64_t Storage::remote_file_size(const std::string& filename)
{
    std::string path = remote_path(filename);
    WIN32_FILE_ATTRIBUTE_DATA fad;
    if (GetFileAttributesExA(path.c_str(), GetFileExInfoStandard, &fad)) {
        LARGE_INTEGER size;
        size.HighPart = fad.nFileSizeHigh;
        size.LowPart = fad.nFileSizeLow;
        return size.QuadPart;
    }
    return -1;
}
