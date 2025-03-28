#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SDL.h>
// Use constexpr to avoid linker error
// Window title 
constexpr const char* title = "Bomber Ace";

// Screen resolution
constexpr const int SCREEN_WIDTH = 960;
constexpr const int SCREEN_HEIGHT = SCREEN_WIDTH;

// Color
constexpr const SDL_Color CYAN = { 0, 255, 255 };
constexpr const SDL_Color BLUE = { 0, 0, 255 };
constexpr const SDL_Color ORANGE = { 255, 165, 0 };
constexpr const SDL_Color YELLOW = { 255, 255, 0 };
constexpr const SDL_Color LIME = { 0, 255, 0 };
constexpr const SDL_Color PURPLE = { 128, 0, 128 };
constexpr const SDL_Color RED = { 255, 0, 0 };
constexpr const SDL_Color WHITE = { 255, 255, 255 };
constexpr const SDL_Color BLACK = { 0, 0, 0 };
constexpr const SDL_Color GREEN = { 0, 128, 0 };

// Main Menu Path
constexpr const char* OPEN_SANS_FONT_FILE = "assets/font/open_sans_font.ttf";
constexpr const char* XIROD_FONT_FILE = "assets/font/xirod_font.ttf";
constexpr const char* MUSIC_FILE = "assets/audio/music.mp3";
constexpr const char* SELECTOR_SFX_FILE = "assets/audio/selector_sfx.ogg";
constexpr const char* SELECTED_SFX_FILE = "assets/audio/selected_sfx.ogg";
constexpr const char* SELECTOR_TEXTURE_FILE = "assets/image/selector.png";
constexpr const char* MAINMENU_BOX = "assets/image/button_rectangle_depth_border.png";

// Background
constexpr const char* MAINMENU_BACKGROUND = "assets/image/mainmenubackground.png";
constexpr const char* GAMEOVER_BACKGROUND = "assets/image/gameoverbackground.png";
constexpr const char* OPTIONSMENU_BACKGROUND = "assets/image/optionsmenubackground.png";

// Tile generation
constexpr const int MAP_ROWS = 20;
constexpr const int MAP_COLS = 20;
constexpr const int TILE_SIZE = SCREEN_WIDTH / 20;

// For animation
constexpr const int EXPLOSION_FRAME = 30;
constexpr const int BOMB_FRAME = 2;
constexpr const int FADE_SPEED = 5;

// SFX
constexpr const char* EXPLOSION_EFFECT = "assets/audio/explosion.mp3";
constexpr const char* GRASS_FOOTSTEP_EFFECT = "assets/audio/footstep_grass.ogg";
constexpr const char* SNOW_FOOTSTEP_EFFECT = "assets/audio/footstep_snow.ogg";

// Spritesheet
constexpr const char* PLAYER_SPRITESHEET = "assets/spritesheet/cat_siamese_spritesheet.png";
constexpr const char* ENEMY_1_SPRITESHEET = "assets/spritesheet/cat_1_spritesheet.png";
constexpr const char* ENEMY_2_SPRITESHEET = "assets/spritesheet/cat_2_spritesheet.png";
constexpr const char* ENEMY_3_SPRITESHEET = "assets/spritesheet/cat_3_spritesheet.png";
constexpr const int SPRITE_TILE = 32;

// Level
constexpr const char* LEVEL_FOLDER = "assets/level/";

// Power-ups
constexpr const char* BOMB_RANGE_FILE = "assets/power-ups/bomb_range.png";
constexpr const char* SHIELD_FILE = "assets/power-ups/shield.png";
constexpr const char* EXTRA_BOMB_FILE = "assets/power-ups/extra_bomb.png";
constexpr const char* SPEED_FILE = "assets/power-ups/speed.png";
constexpr const int POWER_UP_WIDTH = 70;
constexpr const int POWER_UP_HEIGHT = 75;

// Victory
constexpr const char* VICTORY_FILE = "assets/image/victory.png";

#endif