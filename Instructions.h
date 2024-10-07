#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "Scene.h"
#include "Button.h"
#include "TextLabel.h"
#include "Image.h"

class Instructions : public Scene {
public:
    Instructions(App& app);

    virtual void Logic(App& app) override final;
    virtual void HandleEvents(App& app, const SDL_Event& e) override final;
    virtual void Render(const App& app) override final;

private:
    gw::TextLabel title, keyboard_description, mouse_description;
    gw::Button back_to_menu;
    gw::Image keyboard_demo, mouse_demo;
};

#endif