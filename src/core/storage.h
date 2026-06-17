#pragma once
#include "core/star_common.h"
#include <nlohmann/json.hpp>

class Storage {
public:
    static Storage& get();

    void init(uint32_t app_id, uint64_t steam_id);

    bool load_achievements(nlohmann::json& out);
    bool save_achievements(const nlohmann::json& data);

    bool load_stats(nlohmann::json& out);
    bool save_stats(const nlohmann::json& data);

    std::string remote_path(const std::string& filename);
    bool write_remote_file(const std::string& filename, const void* data, size_t size);
    bool read_remote_file(const std::string& filename, std::vector<uint8_t>& out);
    bool remote_file_exists(const std::string& filename);
    bool delete_remote_file(const std::string& filename);
    std::vector<std::string> list_remote_files();
    int64_t remote_file_size(const std::string& filename);

    const std::string& base_path() const { return base_path_; }

private:
    Storage() = default;
    std::string base_path_;
    std::string remote_dir_;

    bool ensure_dir(const std::string& path);
    bool write_json(const std::string& path, const nlohmann::json& data);
    bool read_json(const std::string& path, nlohmann::json& out);
};
