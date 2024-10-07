#include "Credits.h"
#include "MainMenu.h"
#include "VKKit/Constants.h"
#include "Constants.h"

Credits::Credits(App& app) :
    background{ MENU_BACKGROUND_TEXTURE, { 0, 0, 1920, 1080 } },
    title{ "Credits", OPENSANS, 60, VKKit::YELLOW, { 960, 100, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    programming{ "Programming", OPENSANS, 40, VKKit::WHITE, { 960, 250, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    programming_people{ "Alex Tsvetanov", OPENSANS, 25, VKKit::WHITE, { 960, 300, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    art{ "Art", OPENSANS, 40, VKKit::WHITE, { 960, 375, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    art_people{ "Alex Tsvetanov", OPENSANS, 25, VKKit::WHITE, { 960, 425, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    design{ "Design", OPENSANS, 40, VKKit::WHITE, { 960, 500, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    design_people{ "Alex Tsvetanov", OPENSANS, 25, VKKit::WHITE, { 960, 550, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    sound{ "Sound", OPENSANS, 40, VKKit::WHITE, { 960, 625, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    music{ "Music", OPENSANS, 40, VKKit::WHITE, { 960, 775, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP },
    music_people{
        gw::TextLabel("Timothy Kulig", OPENSANS, 25, VKKit::WHITE, { 960, 825, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP),
        gw::TextLabel("nojisuma", OPENSANS, 25, VKKit::WHITE, { 960, 850, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP)
    },
    sound_people{
        gw::TextLabel("Pixabay", OPENSANS, 25, VKKit::WHITE, { 960, 675, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP),
        gw::TextLabel("666HeroHero", OPENSANS, 25, VKKit::WHITE, { 960, 700, 1920, 0 }, VKKit::HorizontalAlignment::CENTER, VKKit::VerticalAlignment::TOP),
    },
    back_to_menu_button{ "Back to Menu", OPENSANS, 30, VKKit::WHITE, BUTTON_BASE_TEXTURE, BUTTON_HOVER_BASE_TEXTURE, { 810, 960, 300, 60 },
        [&app](){ app.SwitchScene(std::make_unique<MainMenu>(app)); } }
{
    // IMPORTANT: Add the sound/music categories in the credits menu
}

void Credits::Logic(App& app)
{

}

void Credits::HandleEvents(App& app, const SDL_Event& e)
{

}

void Credits::Render(const App& app)
{
    background.Render(app.context);
    title.Render(app.context);
    programming.Render(app.context);
    programming_people.Render(app.context);
    art.Render(app.context);
    art_people.Render(app.context);
    design.Render(app.context);
    design_people.Render(app.context);
    sound.Render(app.context);
    for (const auto& s : sound_people) s.Render(app.context);
    music.Render(app.context);
    for (const auto& m : music_people) m.Render(app.context);
    back_to_menu_button.Render(app.context);
}