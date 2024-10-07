#include "Projectile.h"
#include "Constants.h"
#include "Conversions.h"

static constexpr float PROJECTILE_SPEED = 1000.0f;

static VKKit::Pos2D NormalizedPos(VKKit::Pos2D pos)
{
    const auto magnitude = sqrt(pow(pos.x, 2.0f) + pow(pos.y, 2.0f));
    pos.x /= magnitude;
    pos.y /= magnitude;
    return pos;
}

Projectile::Projectile(VKKit::Pos2D mousepos, const VKKit::Rect& shooter_hitbox)
{
    const auto shooter_center = VKKit::CenterOfRect(shooter_hitbox);

    hitbox = { shooter_center.x, shooter_center.y, 5.0f, 5.0f };
    speed = PROJECTILE_SPEED;
    direction = NormalizedPos({ mousepos.x - shooter_center.x, mousepos.y - shooter_center.y });
}

bool Projectile::Move(float deltatime, ut::rspan<const VKKit::Rect> walls, const Bounds& bounds)
{
    const VKKit::Pos2D displacement = { direction.x * speed, direction.y * speed };

    return MoveRect(hitbox, displacement.x, displacement.y, deltatime, walls, bounds);
}

bool Projectile::CollidesWithAZombie(ut::rspan<const Zombie> zombies) const noexcept
{
    return TestCollisionWithObjects(hitbox, zombies, CollisionWithZombie());
}

void Projectile::Render(const VKKit::Context& context) const
{
    context.Render2D(PROJECTILE_TEXTURE, GetNormalizedHitbox(hitbox));
}