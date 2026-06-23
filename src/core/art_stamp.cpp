#include "core/art_stamp.h"
#include "core/star_common.h"
#include <windows.h>
#include <fstream>
#include <string>

static const char* k_art =
    "; \n"
    ";   .-')    .-') _      ('-.     _  .-')   \n"
    ";  ( OO ). (  OO) )    ( OO ).-.( \\( -O )  \n"
    "; (_)---\\_)/     '._   / . --. / ,------.  \n"
    "; /    _ | |'--...__)  | \\-.  \\  |   /`. ' \n"
    "; \\  :` `. '--.  .--'.-'-'  |  | |  /  | | \n"
    ";  '..`''.)   |  |    \\| |_.'  | |  |_.' | \n"
    "; .-._)   \\   |  |     |  .-.  | |  .  '.' \n"
    "; \\       /   |  |     |  | |  | |  |\\  \\  \n"
    ";  `-----'    `--'     `--' `--' `--' '--'  \n"
    "; \n";

static const char* k_sentinel = "; STAR-ART";

void stamp_star_configs(const std::string& dir)
{
    std::wstring search_path = utf8_to_wstring(dir) + L"\\*.star";
    WIN32_FIND_DATAW find_data;
    HANDLE hFind = FindFirstFileW(search_path.c_str(), &find_data);
    if (hFind == INVALID_HANDLE_VALUE) return;

    do {
        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

        std::wstring wfile_path = utf8_to_wstring(dir) + L"\\" + find_data.cFileName;
        std::string file_path = wstring_to_utf8(wfile_path);
        std::ifstream in(wfile_path);
        if (!in.is_open()) continue;

        std::string first_line;
        std::getline(in, first_line);
        if (first_line.find(k_sentinel) != std::string::npos) continue;

        std::string rest(first_line + "\n");
        std::string buf((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        in.close();

        std::ofstream out(wfile_path, std::ios::trunc);
        if (!out.is_open()) {
            STAR_LOG("stamp_star_configs: failed to open for write: %s", file_path.c_str());
            continue;
        }
        out << k_sentinel << "\n" << k_art << "\n" << rest << buf;
    } while (FindNextFileW(hFind, &find_data));

    FindClose(hFind);
}

