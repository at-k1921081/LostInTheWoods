#ifndef CREDITS_H
#define CREDITS_H

#include "Scene.h"
#include "App.h"
#include "Image.h"
#include "TextLabel.h"
#include "Button.h"

class Credits : public Scene {
public:
    Credits(App& app);

    virtual void Logic(App& app) override final;
    virtual void HandleEvents(App& app, const SDL_Event& e) override final;
    virtual void Render(const App& app) override final;

private:
    gw::Image background;
    gw::TextLabel title, programming, programming_people, art, art_people, design, design_people, sound, music;
    std::array<gw::TextLabel, 2> music_people;
    std::array<gw::TextLabel, 2> sound_people;
    gw::Button back_to_menu_button;
};

#endif