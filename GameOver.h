#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Scene.h"
#include "GameWidgets.h"

class GameOver : public Scene {
public:
    GameOver(App& app, int last_level);

    virtual void Logic(App& app) override final;
    virtual void HandleEvents(App& app, const SDL_Event& e) override final;
    virtual void Render(const App& app) override final;

private:
    Title title;
    gw::Image background;
    MenuButton replay, back_to_menu;
};

#endif