#include "Instructions.h"
#include "Constants.h"
#include "MainMenu.h"
#include "VKKit/Constants.h"

Instructions::Instructions(App& app) :
    title{ "How to Play", OPENSANS, 60, VKKit::YELLOW, { 960.0f, 100.0f, 1920.0f, 0.0f }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    keyboard_description{ "WASD to move", OPENSANS, 30, VKKit::WHITE, { 1000.0f, 350.0f, 1920.0f, 0.0f }, VKKit::HorizontalAlignment::LEFT, VKKit::VerticalAlignment::TOP },
    mouse_description{ "Mouse to aim and shoot", OPENSANS, 30, VKKit::WHITE, { 1000.0f, 500.0f, 1920.0f, 0.0f }, VKKit::HorizontalAlignment::LEFT,
        VKKit::VerticalAlignment::TOP },
    back_to_menu{ "Back to Menu", OPENSANS, 30, VKKit::WHITE, BUTTON_BASE_TEXTURE, BUTTON_HOVER_BASE_TEXTURE, { 810.0f, 960.0f, 300.0f, 60.0f },
        [&app]() { app.SwitchScene(std::make_unique<MainMenu>(app)); } },
    keyboard_demo{ KEYBOARD_DEMO_TEXTURE, { 675.0f, 300.0f, 100.0f, 100.0f } },
    mouse_demo{ MOUSE_DEMO_TEXTURE, { 700.0f, 450.0f, 50.0f, 100.0f } }
{

}

void Instructions::Logic(App& app)
{

}

void Instructions::HandleEvents(App& app, const SDL_Event& e)
{
    
}

void Instructions::Render(const App& app)
{
    app.context.Render2D(MENU_BACKGROUND_TEXTURE, { -1.0, -1.0, 2.0, 2.0 });
    title.Render(app.context);
    keyboard_description.Render(app.context);
    mouse_description.Render(app.context);
    back_to_menu.Render(app.context);
    keyboard_demo.Render(app.context);
    mouse_demo.Render(app.context);
}