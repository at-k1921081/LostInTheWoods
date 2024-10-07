#include "LevelSelect.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "VKKit/Constants.h"
#include "Constants.h"

static constexpr size_t GetSelectTexture(int level, int last_level_reached)
{
    return level <= last_level_reached ? LEVEL_SELECT_BG_TEXTURE : LEVEL_SELECT_UNAVAILABLE_BG_TEXTURE;
}

static constexpr size_t GetHoverTexture(int level, int last_level_reached)
{
    return level <= last_level_reached ? LEVEL_SELECT_HOVER_BG_TEXTURE : LEVEL_SELECT_UNAVAILABLE_BG_TEXTURE;
}

LevelSelect::LevelSelect(App& app) :
    background{ MENU_BACKGROUND_TEXTURE, { 0, 0, 1920, 1080 } },
    title{ "Select Level", OPENSANS, 60, VKKit::YELLOW, { 960, 100, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    level1{ "1", OPENSANS, 30, VKKit::WHITE, LEVEL_SELECT_BG_TEXTURE, LEVEL_SELECT_HOVER_BG_TEXTURE, { 700, 500, 100, 100 },
        [&app](){ app.SwitchScene(std::make_unique<Gameplay>(app, 1)); } },
    level2{ "2", OPENSANS, 30, VKKit::WHITE, GetSelectTexture(2, app.last_level_reached), GetHoverTexture(2, app.last_level_reached), {900, 500, 100, 100},
        [&app](){ if (app.last_level_reached >= 2) app.SwitchScene(std::make_unique<Gameplay>(app, 2)); } },
    level3{ "3", OPENSANS, 30, VKKit::WHITE, GetSelectTexture(3, app.last_level_reached), GetHoverTexture(3, app.last_level_reached), { 1100, 500, 100, 100 },
        [&app](){ if (app.last_level_reached >= 3) app.SwitchScene(std::make_unique<Gameplay>(app, 3)); } },
    back_to_menu_button{ "Back to Menu", OPENSANS, 30, VKKit::WHITE, BUTTON_BASE_TEXTURE, BUTTON_HOVER_BASE_TEXTURE, { 810, 960, 300, 60 },
        [&app](){ app.SwitchScene(std::make_unique<MainMenu>(app)); } }
{
    
}

void LevelSelect::Logic(App& app)
{

}

void LevelSelect::HandleEvents(App& app, const SDL_Event& e)
{

}

void LevelSelect::Render(const App& app)
{
    background.Render(app.context);
    title.Render(app.context);
    level1.Render(app.context);
    level2.Render(app.context);
    level3.Render(app.context);
    back_to_menu_button.Render(app.context);
}