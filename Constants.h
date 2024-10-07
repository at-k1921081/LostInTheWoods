#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "RectMovement.h"

constexpr float FPS = 120.0f;
constexpr float SECONDS_PER_FRAME = 1 / FPS;
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;

static constexpr Bounds BOUNDS = { 
    .left = 0.0f,
    .right = static_cast<float>(WINDOW_WIDTH),
    .top = 0.0f,
    .bottom = static_cast<float>(WINDOW_HEIGHT)
};

enum Textures {
    // Menu backgrounds and textures
    MAIN_MENU_BACKGROUND_TEXTURE, MENU_BACKGROUND_TEXTURE,

    // Widget textures
    BUTTON_BASE_TEXTURE, BUTTON_HOVER_BASE_TEXTURE, LEVEL_SELECT_BG_TEXTURE, LEVEL_SELECT_HOVER_BG_TEXTURE, LEVEL_SELECT_UNAVAILABLE_BG_TEXTURE,
    CHECKBOX_TEXTURE, CHECKBOX_TICK_TEXTURE,

    // Menu textures
    KEYBOARD_DEMO_TEXTURE, MOUSE_DEMO_TEXTURE,

    // Game widget textures
    PAUSE_ICON_TEXTURE, RESET_LEVEL_TEXTURE, LEVEL_BACKGROUND_TEXTURE,

    // Gameplay textures
    MAIN_CHARACTER_TEXTURE, GUN_TEXTURE, ZOMBIE_TEXTURE, BULLET_TEXTURE, WALL_TEXTURE, ENDPOINT_TEXTURE, PROJECTILE_TEXTURE,

    TOTAL_TEXTURES
};

enum Fonts {
    OPENSANS,

    TOTAL_FONTS
};

enum Musics {
    MENU_MUSIC, LEVEL_MUSIC,

    TOTAL_MUSIC
};

enum Sounds {
    GROWLING_ZOMBIE_SOUND, ZOMBIE_DEATH_SOUND, SHOOTING_SOUND, ZOMBIE_ATTACK_SOUND,

    TOTAL_SOUNDS
};

#endif