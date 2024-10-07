#ifndef OPTIONS_H
#define OPTIONS_H

#include "Scene.h"
#include "GameWidgets.h"

class Options : public Scene {
public:
    Options(App& app);

    virtual void Logic(App& app) override final;
    virtual void HandleEvents(App& app, const SDL_Event& e) override final;
    virtual void Render(const App& app) override final;

private:
    gw::Image background;
    Title title;
    GameOptions options;
    MenuButton back_to_menu_button;
};

#endif