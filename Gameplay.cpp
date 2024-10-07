#include "Gameplay.h"
#include "rspan.h"
#include "VKKit/Constants.h"
#include "ArrayUtils.h"
#include "Conversions.h"
#include "Constants.h"
#include "GameOver.h"
#include "GameWon.h"

#include "SDL.h"

// Global data
static constexpr VKKit::Rect LEVEL_AREA = { 0.0f, 0.0f, 1920.0f, 1080.0f };
static constexpr float PLAYER_SPEED = 300.0f;
static constexpr float FIRERATE = 1.0f / 5.0f;

// Static helper functions

/**
 * @brief Zombies, in level information files, are stored as positions. When loading a level, the positions need to be
 *        converted into actual zombie objects.
 * @param positions The positions of the zombies
 * @return An array of zombies with the given positions
 */
static std::vector<Zombie> GetZombiesFromPositions(ut::rspan<const VKKit::Pos2D> positions)
{
    std::vector<Zombie> zombies;
    zombies.reserve(positions.size());

    for (const auto p : positions) {
        zombies.push_back(Zombie({p.x, p.y}));
    }

    return zombies;
}

// Main functions

Gameplay::Gameplay(App& app, int level) :
    paused{ false },
    current_level{ level },
    pause_button{ PAUSE_ICON_TEXTURE, { 1700, 50, 40, 40 } },
    restart_level_button{ RESET_LEVEL_TEXTURE, { 1800, 50, 40, 40 } },
    pause_menu{ app, paused }
{
    pause_menu.SetActive(false);
    pause_button.SetOnClick([this]() { this->paused = true; pause_menu.SetActive(true); });
    restart_level_button.SetOnClick([this, &app]() { StartLevel(app, current_level); pause_menu.SetActive(false); });

    app.music[LEVEL_MUSIC].Play();

    StartLevel(app, level);
}

void Gameplay::Logic(App& app)
{
    if (!paused) {
        UpdatePlayer(app);
        if (app.changed_scene) return;
        UpdateProjectiles(app);
        if (app.changed_scene) return;
        UpdateZombies(app);
    }
}

void Gameplay::HandleEvents(App& app, const SDL_Event& e)
{
    switch (e.type) {
    case SDL_MOUSEBUTTONDOWN: if (!paused) player.shooting = true; break;
    case SDL_MOUSEBUTTONUP: if (!paused) player.shooting = false; break;
    }
}

void Gameplay::Render(const App& app)
{
    if (paused)
        RenderPauseMenu(app);
    else
        RenderGame(app);
}

// Helper functions

void Gameplay::UpdatePlayer(App& app)
{
    if (player.health <= 0) {
        app.SwitchScene(std::make_unique<GameOver>(app, current_level));
        return;
    }

    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    player.movement = { 0.0f, 0.0f };
    if (keys[SDL_SCANCODE_A]) player.movement.x -= PLAYER_SPEED;
    if (keys[SDL_SCANCODE_D]) player.movement.x += PLAYER_SPEED;
    if (keys[SDL_SCANCODE_W]) player.movement.y -= PLAYER_SPEED;
    if (keys[SDL_SCANCODE_S]) player.movement.y += PLAYER_SPEED;

    player.Move(app.GetDeltaTime(), walls, BOUNDS);

    if (VKKit::HasIntersection(player.hitbox, end))
        GoToNextLevel(app);

    player.shoot_cooldown -= app.GetDeltaTime();
}

void Gameplay::UpdateProjectiles(App& app)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    const VKKit::Pos2D mousepos = { static_cast<float>(x), static_cast<float>(y) };

    if (player.shooting && (player.shoot_cooldown <= 0.0f)) {
        projectiles.push_back(Projectile(mousepos, player.hitbox));
        player.shoot_cooldown = FIRERATE;
        app.PlaySound(SHOOTING_SOUND);
    }

    for (size_t i = 0; i < projectiles.size(); ++i) {
        const auto collision = projectiles[i].Move(app.GetDeltaTime(), walls, BOUNDS);
        if (collision) {
            ut::FastEraseVectorElement(projectiles, i);
            --i;
        }
    }
}

void Gameplay::UpdateZombies(App& app)
{
    for (size_t i = 0; i < zombies.size(); ++i) {
        for (size_t j = 0; j < projectiles.size(); ++j) {
            if (VKKit::HasIntersection(projectiles[j].hitbox, zombies[i].hitbox)) {
                ut::FastEraseVectorElement(projectiles, j);
                --j;
                zombies[i].TakeDamage(1);
            }
        }
    }

    for (auto& z : zombies)
        z.Update(player, app, walls, movement_positions);

    ut::FastEraseVectorElements(zombies, ZombieDeath());
}

void Gameplay::StartLevel(const App& app, int level)
{
    current_level = level;
    
    level -= 1;
    const auto& info = app.level_info[level];

    player = Player(info.startx, info.starty);
    walls = info.walls;
    zombies = GetZombiesFromPositions(info.zombies);
    end = { info.endx, info.endy, 30.0f, 30.0f };
}

void Gameplay::GoToNextLevel(App& app)
{
    if (current_level == 3)
        app.SwitchScene(std::make_unique<GameWon>(app));
    else {
        const int next_level = current_level + 1;
        if (next_level > app.last_level_reached)
            app.last_level_reached = next_level;
        StartLevel(app, next_level);
    }
}

void Gameplay::RenderGame(const App& app)
{
    RenderGameLevel(app);
    RenderGameUI(app);
}

void Gameplay::RenderGameLevel(const App& app)
{
    app.context.Render2D(LEVEL_BACKGROUND_TEXTURE, GetNormalizedHitbox(LEVEL_AREA));

    player.Render(app.context);

    for (const auto& w : walls)
        app.context.Render2D(WALL_TEXTURE, GetNormalizedHitbox(w));

    for (const auto& z : zombies)
        z.Render(app.context);

    app.context.Render2D(ENDPOINT_TEXTURE, GetNormalizedHitbox(end));

    for (const auto& p : projectiles) p.Render(app.context);
}

void Gameplay::RenderGameUI(const App& app)
{
    pause_button.Render(app.context);
    restart_level_button.Render(app.context);

    char health[128];
    snprintf(health, sizeof(health), "Health: %d", player.health);
    app.context.RenderTextRel(health, OPENSANS, VKKit::RED, 30, 1000, 40);
}

void Gameplay::RenderPauseMenu(const App& app)
{
    pause_menu.Render(app.context);
}