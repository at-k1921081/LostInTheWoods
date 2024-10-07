#include "Player.h"
#include "Constants.h"
#include "Conversions.h"
#include "Zombie.h"

Player::Player(float x, float y) :
    hitbox{ x, y, 30.0f, 30.0f },
    movement{ 0.0f, 0.0f },
    shoot_cooldown{ 0.0f },
    shooting{ false },
    health{ 20 }
{}

void Player::Move(float deltatime, ut::rspan<const VKKit::Rect> walls, const Bounds& bounds)
{
    MoveRect(hitbox, movement.x, movement.y, deltatime, walls, bounds);
}

bool Player::CollidesWithZombies(ut::rspan<const Zombie> zombies)
{
    return TestCollisionWithObjects(hitbox, zombies, CollisionWithZombie());
}

void Player::Render(const VKKit::Context& context) const
{
    context.Render2D(MAIN_CHARACTER_TEXTURE, GetNormalizedHitbox(hitbox));
}