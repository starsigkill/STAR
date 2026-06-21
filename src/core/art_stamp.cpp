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
    std::string search_path = dir + "\\*.star";
    WIN32_FIND_DATAA find_data;
    HANDLE hFind = FindFirstFileA(search_path.c_str(), &find_data);
    if (hFind == INVALID_HANDLE_VALUE) return;

    do {
        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

        std::string file_path = dir + "\\" + find_data.cFileName;
        std::ifstream in(file_path);
        if (!in.is_open()) continue;

        std::string first_line;
        std::getline(in, first_line);
        if (first_line.find(k_sentinel) != std::string::npos) continue;

        std::string rest(first_line + "\n");
        std::string buf((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        in.close();

        std::ofstream out(file_path, std::ios::trunc);
        if (!out.is_open()) {
            STAR_LOG("stamp_star_configs: failed to open for write: %s", file_path.c_str());
            continue;
        }
        out << k_sentinel << "\n" << k_art << "\n" << rest << buf;
    } while (FindNextFileA(hFind, &find_data));

    FindClose(hFind);
}

