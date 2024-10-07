#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "RenderData.h"
#include "Context.h"
#include "rspan.h"

struct Player;
struct App;

struct Zombie {
    Zombie() = default;
    Zombie(VKKit::Pos2D pos);

    VKKit::Rect hitbox;
    int health;
    float attack_cooldown;
    void (Zombie::*state)(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions);

    void TakeDamage(int damage);

    void Update(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions);

    void Render(const VKKit::Context& context) const;

    bool IsDead() const noexcept;

private:
    void IdleState(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions);
    void ChaseState(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions);
    void AttackState(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions);
    void DeathState(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions);
};

struct CollisionWithZombie {
    bool operator()(const VKKit::Rect& r, const Zombie& z) const noexcept {
        return VKKit::HasIntersection(r, z.hitbox);
    }
};

struct ZombieDeath {
    bool operator()(const Zombie& z) const noexcept {
        return z.IsDead();
    }
};

#endif