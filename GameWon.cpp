#include "GameWon.h"
#include "Constants.h"

GameWon::GameWon(App& app) :
    title{ "You Win" },
    background{ MENU_BACKGROUND_TEXTURE, { 0, 0, 1920, 1080 } },
    back_to_menu{ BackToMenuButton(app) }
{
    app.music[MENU_MUSIC].Play();
}

void GameWon::Logic(App& app)
{

}

void GameWon::HandleEvents(App& app, const SDL_Event& e)
{

}

void GameWon::Render(const App& app)
{
    background.Render(app.context);
    title.Render(app.context);
    back_to_menu.Render(app.context);
}