#ifndef PLAYER_H
#define PLAYER_H

#include "RenderData.h"
#include "rspan.h"
#include "Zombie.h"
#include "Context.h"
#include "RectMovement.h"

struct Player {
    Player() = default;
    Player(float x, float y);

    VKKit::Rect hitbox;
    VKKit::Pos2D movement;
    float shoot_cooldown;
    bool shooting;
    int health;

    void Move(float deltatime, ut::rspan<const VKKit::Rect> walls, const Bounds& bounds);
    bool CollidesWithZombies(ut::rspan<const Zombie> zombies);

    void Render(const VKKit::Context& context) const;
};

#endif