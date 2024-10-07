#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Scene.h"
#include "App.h"
#include "Image.h"
#include "GameWidgets.h"
#include "Player.h"
#include "Zombie.h"
#include "Projectile.h"

class Gameplay : public Scene {
public:
    Gameplay(App& app, int level);

    virtual void Logic(App& app) override final;
    virtual void HandleEvents(App& app, const SDL_Event& e) override final;
    virtual void Render(const App& app) override final;

private:
    bool paused;
    int current_level;

    // In-game UI
    gw::ClickableImage pause_button, restart_level_button;

    // Pause submenu UI
    GameOptionsSubscreen pause_menu;

    // Gameplay objects
    Player player;
    std::vector<VKKit::Rect> walls;
    std::vector<Zombie> zombies;
    VKKit::Rect end;

    std::vector<Projectile> projectiles;
    std::vector<VKKit::Pos2D> movement_positions; // For pathfinding

    // Helper methods
    void UpdatePlayer(App& app);
    void UpdateProjectiles(App& app);
    void UpdateZombies(App& app);

    // Level information
    void StartLevel(const App& app, int level);
    void GoToNextLevel(App& app);

    // Rendering functions
    void RenderGame(const App& app);
    void RenderGameUI(const App& app);
    void RenderGameLevel(const App& app);
    void RenderPauseMenu(const App& app);
};

#endif