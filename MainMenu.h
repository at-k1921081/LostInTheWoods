#ifndef MAINMENU_H
#define MAINMENU_H

#include "Scene.h"
#include "Image.h"
#include "Button.h"
#include "TextLabel.h"
#include "GameWidgets.h"

class MainMenu : public Scene {
public:
    MainMenu(App& app);

    virtual void Logic(App& app) override final;
    virtual void HandleEvents(App& app, const SDL_Event& e) override final;
    virtual void Render(const App& app) override final;

private:
    gw::Image background;
    Title title;
    MenuButton play_game, instructions, options, credits, quit;
};

#endif