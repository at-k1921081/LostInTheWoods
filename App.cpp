#include <string_view>
#include <array>
#include <fstream>
#include <filesystem>

#include "App.h"
#include "MainMenu.h"

#define PATH_APPEND "../"

static constexpr std::string_view SETTINGS_FILE = PATH_APPEND "Data/Settings.txt";
static constexpr std::string_view GAME_PROGRESS_FILE = PATH_APPEND "Data/Savefile.txt";

static constexpr std::array<std::string_view, TOTAL_TEXTURES> GetTexturePaths()
{
    std::array<std::string_view, TOTAL_TEXTURES> paths;

    // Menu widgets
    paths[MAIN_MENU_BACKGROUND_TEXTURE] = PATH_APPEND "Images/MainMenuBG.png";
    paths[MENU_BACKGROUND_TEXTURE] = PATH_APPEND "Images/MenuBG.png";
    paths[BUTTON_BASE_TEXTURE] = PATH_APPEND "Images/ButtonBase.png";
    paths[BUTTON_HOVER_BASE_TEXTURE] = PATH_APPEND "Images/ButtonHoverBase.png";
    paths[LEVEL_SELECT_BG_TEXTURE] = PATH_APPEND "Images/LevelSelectButtonBG.png";
    paths[LEVEL_SELECT_HOVER_BG_TEXTURE] = PATH_APPEND "Images/LevelSelectButtonHoverBG.png";
    paths[LEVEL_SELECT_UNAVAILABLE_BG_TEXTURE] = PATH_APPEND "Images/LevelSelectButtonUnavailableBG.png";
    paths[KEYBOARD_DEMO_TEXTURE] = PATH_APPEND "Images/KeyboardDemo.png";
    paths[MOUSE_DEMO_TEXTURE] = PATH_APPEND "Images/MouseDemo.png";
    paths[CHECKBOX_TEXTURE] = PATH_APPEND "Images/Checkbox.png";
    paths[CHECKBOX_TICK_TEXTURE] = PATH_APPEND "Images/Tick.png";

    // Gameplay widgets
    paths[PAUSE_ICON_TEXTURE] = PATH_APPEND "Images/PauseIcon.png";
    paths[RESET_LEVEL_TEXTURE] = PATH_APPEND "Images/RestartLevelIcon.png";
    paths[MAIN_CHARACTER_TEXTURE] = PATH_APPEND "Images/MainCharacter.png";
    paths[GUN_TEXTURE] = PATH_APPEND "Images/Gun.png";
    paths[ZOMBIE_TEXTURE] = PATH_APPEND "Images/Zombie.png";
    paths[BULLET_TEXTURE] = PATH_APPEND "Images/Bullet.png";
    paths[LEVEL_BACKGROUND_TEXTURE] = PATH_APPEND "Images/LevelBackground.png";
    paths[WALL_TEXTURE] = PATH_APPEND "Images/Wall.png";
    paths[ENDPOINT_TEXTURE] = PATH_APPEND "Images/EndPoint.png";
    paths[PROJECTILE_TEXTURE] = PATH_APPEND "Images/Bullet.png";

    return paths;
}
static constexpr auto TEXTURE_PATHS = GetTexturePaths();

static std::array<se::Sound, TOTAL_SOUNDS> LoadSounds()
{
    std::array<se::Sound, TOTAL_SOUNDS> sounds;

    sounds[GROWLING_ZOMBIE_SOUND] = se::Sound(PATH_APPEND "Sound/growling-zombie.mp3");
    sounds[ZOMBIE_DEATH_SOUND] = se::Sound(PATH_APPEND "Sound/monster-death-grunt.mp3");
    sounds[SHOOTING_SOUND] = se::Sound(PATH_APPEND "Sound/shoot-5.mp3");
    sounds[ZOMBIE_ATTACK_SOUND] = se::Sound(PATH_APPEND "Sound/slash1.mp3");

    return sounds;
}

static std::array<se::Music, TOTAL_MUSIC> LoadMusic()
{
    std::array<se::Music, TOTAL_MUSIC> music;

    music[MENU_MUSIC] = se::Music(PATH_APPEND "Music/done-digging.mp3");
    music[LEVEL_MUSIC] = se::Music(PATH_APPEND "Music/pulsation.mp3");

    return music;
}

static std::array<LevelInfo, 3> LoadLevels()
{
    auto level1 = LevelInfo::Load(PATH_APPEND "Levels/Level1.txt");
    if (!level1.has_value()) throw std::runtime_error(level1.error());

    auto level2 = LevelInfo::Load(PATH_APPEND "Levels/Level2.txt");
    if (!level2.has_value()) throw std::runtime_error(level2.error());

    auto level3 = LevelInfo::Load(PATH_APPEND "Levels/Level3.txt");
    if (!level3.has_value()) throw std::runtime_error(level3.error());

    return { std::move(*level1), std::move(*level2), std::move(*level3) };
}

static Settings LoadSettings()
{
    if (!std::filesystem::exists(SETTINGS_FILE)) {
        std::ofstream file(SETTINGS_FILE.data());
        if (!file)
            throw std::runtime_error("No settings file found and failed to create new one");
        file << DEFAULT_SETTINGS;
        return DEFAULT_SETTINGS;
    }

    std::ifstream file(SETTINGS_FILE.data());
    if (!file)
        throw std::runtime_error("Failed to open settings file");

    Settings settings;
    file >> settings;

    if (file.fail())
        throw std::runtime_error("Failed to parse settings file");

    return settings;
}

static int GetGameProgress()
{
    if (!std::filesystem::exists(GAME_PROGRESS_FILE)) {
        std::ofstream file(GAME_PROGRESS_FILE.data());
        if (!file)
            throw std::runtime_error("No savefile found and failed to create new one");

        file << 1;
        return 1;
    }

    std::ifstream file(GAME_PROGRESS_FILE.data());
    if (!file)
        throw std::runtime_error("Failed to open savefile");

    int last_level_reached;
    file >> last_level_reached;

    if (file.fail())
        throw std::runtime_error("Failed to parse savefile");

    return last_level_reached;
}

App::App() :
    context{ "Lost In The Woods", WINDOW_WIDTH, WINDOW_HEIGHT },
    scene{},
    changed_scene{ false },
    level_info{ LoadLevels() },
    sounds{ LoadSounds() },
    music{ LoadMusic() },
    settings{ LoadSettings() },
    last_level_reached{ GetGameProgress() },
    start{ std::chrono::steady_clock::now() },
    end{},
    deltatime{}
{
    context.LoadTextures(TEXTURE_PATHS);

    context.LoadAlphabet(PATH_APPEND "Fonts/OpenSans-Regular.ttf");

    scene = std::make_unique<MainMenu>(*this);

    music[MENU_MUSIC].Play();
}

App::~App()
{
    // Save the game settings
    std::ofstream settings_file(SETTINGS_FILE.data());
    if (settings_file) {
        settings_file << settings;
    }

    // Save the game progress
    std::ofstream savefile(GAME_PROGRESS_FILE.data());
    if (savefile) {
        savefile << last_level_reached;
    }
}

void App::SwitchScene(std::unique_ptr<Scene> newscene)
{
    scene = std::move(newscene);
    changed_scene = true;
}

float App::GetDeltaTime() const noexcept
{
    return deltatime;
}

void App::PlaySound(Sounds sound) const
{
    if (!settings.sound_muted)
        sounds[sound].Play();
}

void App::PlayMusic(Musics music) const
{
    if (!settings.music_muted)
        this->music[music].Play();
}

void App::MuteSound()
{
    if (!settings.sound_muted) {
        se::Sound::Stop();
        settings.sound_muted = true;
    }
    else {
        settings.sound_muted = false;
    }
}

void App::MuteMusic()
{
    if (!settings.music_muted) {
        se::Music::Stop();
        settings.music_muted = true;
    }
    else {
        settings.music_muted = false;
    }
}

void App::UpdateTime()
{
    end = std::chrono::steady_clock::now();
    deltatime = std::chrono::duration<float>(end - start).count();
    start = std::chrono::steady_clock::now();
}