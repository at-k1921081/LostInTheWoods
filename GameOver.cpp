#include "GameOver.h"
#include "Gameplay.h"
#include "MainMenu.h"
#include "Constants.h"

GameOver::GameOver(App& app, int last_level) :
    title{ "Game Over" },
    background{ MENU_BACKGROUND_TEXTURE, { 0, 0, 1920, 1080 } },
    replay{ "Try Again", 610, 960, [&app, last_level](){ app.SwitchScene(std::make_unique<Gameplay>(app, last_level)); } },
    back_to_menu{ "Back to Menu", 1010, 960, [&app](){ app.SwitchScene(std::make_unique<MainMenu>(app)); } }
{
    app.music[MENU_MUSIC].Play();
}

void GameOver::Logic(App& app)
{

}

void GameOver::HandleEvents(App& app, const SDL_Event& e)
{

}

void GameOver::Render(const App& app)
{
    background.Render(app.context);
    title.Render(app.context);
    replay.Render(app.context);
    back_to_menu.Render(app.context);
}