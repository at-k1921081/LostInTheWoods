#include <fstream>
#include <sstream>
#include "LevelInfo.h"
#include "SString.h"

using namespace std::literals;

std::expected<LevelInfo, std::string> LevelInfo::Load(std::string_view filepath)
{
    // Open and load file contents
    std::ifstream file(filepath.data());
    if (!file) return std::unexpected("Failed to load file "s.append(filepath));

    std::stringstream ss;
    ss << file.rdbuf();
    if (ss.fail()) return std::unexpected("Failed to read file contents of "s.append(filepath));

    // Starting position
    LevelInfo info;
    ss >> info.startx >> info.starty;
    if (ss.fail()) return std::unexpected("Failed to read starting position");

    // Walls
    ut::SString<32> token;
    size_t nwalls;
    ss >> token >> nwalls;
    if (token != "WALLS" || ss.fail()) return std::unexpected("Failed to read wall token");

    info.walls.reserve(nwalls);
    for (size_t i = 0; i < nwalls; ++i) {
        VKKit::Rect wall;
        ss >> wall;
        if (ss.fail()) return std::unexpected("Failed to read wall info");
        info.walls.push_back(wall);
    }

    // Zombies
    size_t nzombies;
    ss >> token >> nzombies;
    if (token != "ZOMBIES" || ss.fail()) return std::unexpected("Failed to read zombie info");

    info.zombies.reserve(nzombies);
    for (size_t i = 0; i < nzombies; ++i) {
        VKKit::Pos2D zombie;
        ss >> zombie;
        if (ss.fail()) return std::unexpected("Failed to read zombie info");
        info.zombies.push_back(zombie);
    }

    // End position
    ss >> info.endx >> info.endy;
    if (ss.fail()) return std::unexpected("Failed to get end point position");

    // Success
    return info;
}