#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SDL.h>

// Window title (using constexpr to avoid linker error)
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

// Path
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

// Options Menu Path
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
constexpr const char* PLAYER_SPRITESHEET = "assets/spritesheet/cat_siamese.png";
constexpr const int SPRITE_TILE = 32;

#endif