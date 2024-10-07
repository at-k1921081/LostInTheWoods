#include "Options.h"
#include "App.h"
#include "MainMenu.h"
#include "VKKit/Constants.h"
#include "Constants.h"

Options::Options(App& app) :
    background{ MENU_BACKGROUND_TEXTURE, { 0, 0, 1920, 1080 } },
    title{ "Options" },
    options{ app },
    back_to_menu_button{ BackToMenuButton(app) }
{
    
}

void Options::Logic(App& app)
{

}

void Options::HandleEvents(App& app, const SDL_Event& e)
{

}

void Options::Render(const App& app)
{
    background.Render(app.context);
    title.Render(app.context);
    options.Render(app.context);
    back_to_menu_button.Render(app.context);
}