#ifndef GAMEWIDGETS_H
#define GAMEWIDGETS_H

#include "Button.h"
#include "Image.h"
#include "TextLabel.h"
#include "App.h"

// These are widgets that extend or encapsulate functionality and configuration of the basic widget types, and are
// specialized for this game.

// The title of a menu
class Title : public gw::TextLabel {
public:
    Title(std::string_view text);
};

// An option in the options menu
class Option {
public:
    Option(std::string_view option, float y);
    Option(std::string_view option, float y, std::function<void()> oncheck);

    void Render(const VKKit::Context& context);

    void Check() noexcept { checked = !checked; }
    void SetOnCheck(std::function<void()> oncheck);
    void SetActive(bool active = true);

private:
    gw::TextLabel text;
    gw::ClickableImage checkbox;
    bool checked;
};

class MenuButton : public gw::Button {
public:
    MenuButton(std::string_view text, float x, float y, std::function<void()> onclick);
};

class GameOptions {
public:
    GameOptions(App& app);

    void Render(const VKKit::Context& context);
    void SetActive(bool active = true);

private:
    Option mute_sound, mute_music;
};

class GameOptionsSubscreen {
public:
    GameOptionsSubscreen(App& app, bool& paused);

    void Render(const VKKit::Context& context);
    void SetActive(bool active = true);

private:
    gw::Image background;
    Title title;
    GameOptions options;
    MenuButton resume_game_button, back_to_menu_button;
};

MenuButton BackToMenuButton(App& app);

#endif