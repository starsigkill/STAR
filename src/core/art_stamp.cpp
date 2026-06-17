#include "core/art_stamp.h"
#include <filesystem>
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
    namespace fs = std::filesystem;
    std::error_code ec;
    for (auto& entry : fs::directory_iterator(dir, ec)) {
        if (entry.path().extension() != ".star") continue;

        std::ifstream in(entry.path());
        if (!in.is_open()) continue;

        std::string first_line;
        std::getline(in, first_line);
        if (first_line.find(k_sentinel) != std::string::npos) continue;

        std::string rest(first_line + "\n");
        std::string buf((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        in.close();

        std::ofstream out(entry.path(), std::ios::trunc);
        if (!out.is_open()) continue;
        out << k_sentinel << "\n" << k_art << "\n" << rest << buf;
    }
}
