#include "Zombie.h"
#include "App.h"
#include "Constants.h"
#include "Conversions.h"
#include "Player.h"
#include "Constants.h"

static constexpr float START_CHASE_DISTANCE = 300.0f;
static constexpr float STOP_CHASE_DISTANCE = 450.0f;
static constexpr float START_ATTACK_DISTANCE = 50.0f;
static constexpr float STOP_ATTACK_DISTANCE = 100.0f;

static constexpr float COOLDOWN = 0.5f;

static constexpr float MOVESPEED = 200.0f;

Zombie::Zombie(VKKit::Pos2D pos) :
    hitbox{ pos.x, pos.y, 30.0f, 30.0f },
    health{ 3 },
    attack_cooldown{ 0.0f },
    state{ &Zombie::IdleState }
{

}

void Zombie::TakeDamage(int damage)
{
    health -= 1;
    if (health <= 0)
        state = &Zombie::DeathState;
}

void Zombie::Update(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions)
{
    std::invoke(state, this, player, app, walls, movement_positions);

    attack_cooldown -= app.GetDeltaTime();
}

void Zombie::Render(const VKKit::Context& context) const
{
    context.Render2D(ZOMBIE_TEXTURE, GetNormalizedHitbox(hitbox));
}

bool Zombie::IsDead() const noexcept
{
    return state == &Zombie::DeathState;
}

void Zombie::IdleState(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions)
{
    if (VKKit::Distance(VKKit::CenterOfRect(player.hitbox), VKKit::CenterOfRect(hitbox)) < START_CHASE_DISTANCE) {
        state = &Zombie::ChaseState;
        app.PlaySound(GROWLING_ZOMBIE_SOUND);
    }
}

void Zombie::ChaseState(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions)
{
    const auto center_of_player = VKKit::CenterOfRect(player.hitbox);
    const auto center_of_zombie = VKKit::CenterOfRect(hitbox);

    const VKKit::Pos2D direction = VKKit::NormalizedPos({center_of_player.x - center_of_zombie.x, center_of_player.y - center_of_zombie.y});

    MoveRect(hitbox, direction.x * MOVESPEED, direction.y * MOVESPEED, app.GetDeltaTime(), walls, BOUNDS);

    const float distance_to_player = VKKit::Distance(center_of_player, center_of_zombie);

    if (distance_to_player <= START_ATTACK_DISTANCE)
        state = &Zombie::AttackState;

    if (distance_to_player >= STOP_CHASE_DISTANCE)
        state = &Zombie::IdleState;
}

void Zombie::AttackState(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions)
{
    if (attack_cooldown <= 0.0f) {
        player.health -= 5;
        attack_cooldown = COOLDOWN;
        app.PlaySound(ZOMBIE_ATTACK_SOUND);
    }

    const auto center_of_player = VKKit::CenterOfRect(player.hitbox);
    const auto center_of_zombie = VKKit::CenterOfRect(hitbox);

    if (VKKit::Distance(center_of_player, center_of_zombie) >= STOP_ATTACK_DISTANCE)
        state = &Zombie::ChaseState;
}

void Zombie::DeathState(Player& player, const App& app, ut::rspan<const VKKit::Rect> walls, ut::rspan<const VKKit::Pos2D> movement_positions)
{
    app.PlaySound(ZOMBIE_DEATH_SOUND);
}