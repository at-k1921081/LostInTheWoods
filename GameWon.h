#ifndef GAMEWON_H
#define GAMEWON_H

#include "Scene.h"
#include "GameWidgets.h"

class GameWon : public Scene {
public:
    GameWon(App& app);

    virtual void Logic(App& app) override final;
    virtual void HandleEvents(App& app, const SDL_Event& e) override final;
    virtual void Render(const App& app) override final;

private:
    Title title;
    gw::Image background;
    MenuButton back_to_menu;
};

#endif