#ifndef APP_H
#define APP_H

#include <memory>
#include <array>
#include <chrono>
#include "Context.h"
#include "Scene.h"
#include "WidgetBase.h"
#include "LevelInfo.h"
#include "SE/Audio.h"
#include "Constants.h"
#include "Settings.h"

struct App {
    App();
    ~App();

    const VKKit::Context context;

    std::unique_ptr<Scene> scene;
    bool changed_scene;
    const std::array<LevelInfo, 3> level_info;

    const std::array<se::Sound, TOTAL_SOUNDS> sounds;
    const std::array<se::Music, TOTAL_MUSIC> music;

    Settings settings;
    int last_level_reached;

    void SwitchScene(std::unique_ptr<Scene> newscene);
    float GetDeltaTime() const noexcept;

    void PlaySound(Sounds sound) const;
    void PlayMusic(Musics music) const;

    // Mute the sound if it's not muted, and unmute it if it is muted
    void MuteSound();

    // Mute the music if it's not muted, and unmute it if it is muted
    void MuteMusic();

    void UpdateTime();

private:
    std::chrono::steady_clock::time_point start, end;

    float deltatime;
};

#endif