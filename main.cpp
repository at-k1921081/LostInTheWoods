#include <iostream>
#include <exception>
#include <chrono>
#include <thread>
#include "InitLibs.h"
#include "App.h"
#include "SDL.h"
#include "Constants.h"
#include "VKKit/Constants.h"
#include "SE/Init.h"

using namespace std::chrono;

int main(int argc, char** args)
{
    try {
        VKKit::SDL sdl;
        se::StealthEngine se;

        App app;
        steady_clock::time_point start, end;

        while (app.scene) {
            start = steady_clock::now();
            app.changed_scene = false;

            app.scene->Logic(app);
            if (app.changed_scene) continue;
            if (!app.scene) break;

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                case SDL_QUIT: app.scene = nullptr; break;
                }

                const float winwscale = app.context.GetWindowWidth() / VKKit::DEFAULT_SCREEN_WIDTH;
                const float winhscale = app.context.GetWindowHeight() / VKKit::DEFAULT_SCREEN_HEIGHT;

                gw::HandleEvent(e, winwscale, winhscale);

                if (!app.scene) break;
                if (app.changed_scene) break;

                app.scene->HandleEvents(app, e);
                if (!app.scene || app.changed_scene) break;
            }
            if (!app.scene) break;
            if (app.changed_scene) continue;

            const auto minimized = app.context.WindowMinimized();
            if (!minimized) { // Only render if the window is visible
                app.context.BeginRendering();

                if (app.scene) app.scene->Render(app);

                app.context.EndRendering();
            }

            app.UpdateTime();
            end = steady_clock::now();
            const auto time_to_sleep = duration<double>(std::max(SECONDS_PER_FRAME - duration<double>(end - start).count(), 0.0));
            std::this_thread::sleep_for(time_to_sleep);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << '\n';
        return -1;
    }
    catch (...) {
        std::cerr << "Unknown error occured\n";
        return -2;
    }

    return 0;
}