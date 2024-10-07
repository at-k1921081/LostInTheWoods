#include "GameWidgets.h"
#include "Constants.h"
#include "VKKit/Constants.h"
#include "Conversions.h"
#include "MainMenu.h"
#include "Gameplay.h"

MenuButton BackToMenuButton(App& app)
{
    return MenuButton("Back to Menu", 810, 960, [&app](){ app.SwitchScene(std::make_unique<MainMenu>(app)); });
}

Title::Title(std::string_view text) :
    gw::TextLabel{ text, OPENSANS, 60, VKKit::YELLOW, { 960, 100, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP }
{}

Option::Option(std::string_view option, float y) :
    text{ option, OPENSANS, 30, VKKit::WHITE, { 800, y, 1920, 0 }, VKKit::HorizontalAlignment::LEFT, VKKit::VerticalAlignment::TOP },
    checkbox{ CHECKBOX_TEXTURE, { 1100, y, 30, 30 } },
    checked{ false }
{}

Option::Option(std::string_view option, float y, std::function<void()> oncheck) :
    text{ option, OPENSANS, 30, VKKit::WHITE, { 800, y, 1920, 0 }, VKKit::HorizontalAlignment::LEFT, VKKit::VerticalAlignment::TOP },
    checkbox{ CHECKBOX_TEXTURE, { 1100, y, 30, 30 } },
    checked{ false }
{
    checkbox.SetOnClick(oncheck);
}

void Option::SetOnCheck(std::function<void()> oncheck)
{
    checkbox.SetOnClick(oncheck);
}

void Option::Render(const VKKit::Context& context)
{
    text.Render(context);
    checkbox.Render(context);
    if (checked)
        context.Render2D(CHECKBOX_TICK_TEXTURE, GetNormalizedHitbox(checkbox.GetHitbox()));
}

void Option::SetActive(bool active)
{
    checkbox.SetActive(active);
}

MenuButton::MenuButton(std::string_view text, float x, float y, std::function<void()> onclick) :
    gw::Button{ text, OPENSANS, 40, VKKit::WHITE, BUTTON_BASE_TEXTURE, BUTTON_HOVER_BASE_TEXTURE, { x, y, 300, 60 }, onclick }
{}

GameOptions::GameOptions(App& app) :
    mute_sound{ "Mute Sound", 300 },
    mute_music{ "Mute Music", 400 }
{
    mute_sound.SetOnCheck([this, &app]() { app.MuteSound(); mute_sound.Check(); });
    mute_music.SetOnCheck([this, &app]() {
        app.MuteMusic();
        mute_music.Check();
        if (!app.settings.music_muted) {
            if (typeid(*app.scene) == typeid(Gameplay))
                app.PlayMusic(LEVEL_MUSIC);
            else
                app.PlayMusic(MENU_MUSIC);
        }
    });
}

void GameOptions::Render(const VKKit::Context& context)
{
    mute_sound.Render(context);
    mute_music.Render(context);
}

void GameOptions::SetActive(bool active)
{
    mute_sound.SetActive(active);
    mute_music.SetActive(active);
}

GameOptionsSubscreen::GameOptionsSubscreen(App& app, bool& paused) :
    background{ MENU_BACKGROUND_TEXTURE, { 0, 0, 1920, 1080 } },
    title{ "Game Paused" },
    options{ app },
    resume_game_button{ "Resume", 610, 960, [this, &paused]() { paused = false; SetActive(false); } },
    back_to_menu_button{ "Back to Menu", 1010, 960, [&app]() { app.PlayMusic(MENU_MUSIC); app.SwitchScene(std::make_unique<MainMenu>(app)); } }
{

}

void GameOptionsSubscreen::Render(const VKKit::Context& context)
{
    background.Render(context);
    title.Render(context);
    options.Render(context);
    resume_game_button.Render(context);
    back_to_menu_button.Render(context);
}

void GameOptionsSubscreen::SetActive(bool active)
{
    options.SetActive(active);
    resume_game_button.SetActive(active);
    back_to_menu_button.SetActive(active);
}