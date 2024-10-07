#ifndef LEVELINFO_H
#define LEVELINFO_H

#include <vector>
#include <expected>
#include <string>
#include "RenderData.h"

struct LevelInfo {
    float startx, starty;
    std::vector<VKKit::Rect> walls;
    std::vector<VKKit::Pos2D> zombies;
    float endx, endy;

    static std::expected<LevelInfo, std::string> Load(std::string_view filepath);
};

#endif