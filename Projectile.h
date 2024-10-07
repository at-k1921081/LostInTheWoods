#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "RenderData.h"
#include "rspan.h"
#include "Zombie.h"
#include "RectMovement.h"

struct Projectile {
    Projectile() = default;
    Projectile(VKKit::Pos2D mousepos, const VKKit::Rect& shooter_hitbox);

    VKKit::Rect hitbox;
    float speed;
    VKKit::Pos2D direction;

    bool Move(float deltatime, ut::rspan<const VKKit::Rect> walls, const Bounds& bounds);
    bool CollidesWithAZombie(ut::rspan<const Zombie> zombies) const noexcept;

    void Render(const VKKit::Context& context) const;
};

#endif