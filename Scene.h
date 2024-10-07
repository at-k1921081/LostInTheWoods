#ifndef SCENE_H
#define SCENE_H

struct App;
union SDL_Event;

class Scene {
public:
    virtual ~Scene() = default;

    virtual void Logic(App& app) = 0;
    virtual void HandleEvents(App& app, const SDL_Event& e) = 0;
    virtual void Render(const App& app) = 0;
};

#endif