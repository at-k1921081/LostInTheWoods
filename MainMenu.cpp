#include "MainMenu.h"
#include "App.h"
#include "LevelSelect.h"
#include "Instructions.h"
#include "Options.h"
#include "Credits.h"
#include "Constants.h"
#include "VKKit/Constants.h"

MainMenu::MainMenu(App& app) :
    background{ MAIN_MENU_BACKGROUND_TEXTURE, { 0, 0, 1920.0f, 1080.0f } },
    title{ "Lost In The Woods" },
    play_game{ "Play Game", 810, 540, [&app](){ app.SwitchScene(std::make_unique<LevelSelect>(app)); } },
    instructions{ "How to Play", 810, 610, [&app](){ app.SwitchScene(std::make_unique<Instructions>(app)); } },
    options{ "Options", 810.0f, 680.0f, [&app]() { app.scene = std::make_unique<Options>(app); } },
    credits{ "Credits", 810.0f, 750.0f, [&app]() { app.scene = std::make_unique<Credits>(app); } },
    quit{ "Quit",  810.0f, 820.0f, [&app]() { app.scene = nullptr; } }
{
    
}

void MainMenu::Logic(App& app)
{

}

void MainMenu::HandleEvents(App& app, const SDL_Event& e)
{

}

void MainMenu::Render(const App& app)
{
    background.Render(app.context);
    title.Render(app.context);
    play_game.Render(app.context);
    instructions.Render(app.context);
    options.Render(app.context);
    credits.Render(app.context);
    quit.Render(app.context);
}