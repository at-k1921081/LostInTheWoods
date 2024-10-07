#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "Scene.h"
#include "App.h"
#include "Image.h"
#include "TextLabel.h"
#include "Button.h"

class LevelSelect : public Scene {
public:
    LevelSelect(App& app);

    virtual void Logic(App& app) override final;
    virtual void HandleEvents(App& app, const SDL_Event& e) override final;
    virtual void Render(const App& app) override final;

private:
    gw::Image background;
    gw::TextLabel title;
    gw::Button level1, level2, level3, back_to_menu_button;
};

#endif